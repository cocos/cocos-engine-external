/*
 * Copyright 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "FrameStatisticsGL.h"

#define LOG_TAG "FrameStatisticsGL"

#include <inttypes.h>

#include <cmath>
#include <string>

#include "EGL.h"
#include "Log.h"
#include "SwappyCommon.h"
#include "Trace.h"

namespace swappy {

int32_t LatencyFrameStatisticsGL::getFrameDelta(EGLnsecsANDROID start,
                                                EGLnsecsANDROID end) {
    const int64_t deltaTimeNano = end - start;

    int32_t numFrames =
        deltaTimeNano / mSwappyCommon.getRefreshPeriod().count();
    numFrames = std::max(
        0, std::min(numFrames, static_cast<int32_t>(MAX_FRAME_BUCKETS) - 1));
    return numFrames;
}

LatencyFrameStatisticsGL::LatencyFrameStatisticsGL(
    const EGL& egl, const SwappyCommon& swappyCommon)
    : mEgl(egl), mSwappyCommon(swappyCommon) {}

void LatencyFrameStatisticsGL::updateLatency(
    swappy::EGL::FrameTimestamps& frameStats, TimePoint frameStartTime) {
    int latency = getFrameDelta(frameStartTime.time_since_epoch().count(),
                                frameStats.compositionLatched);
    TRACE_INT("FrameLatency", latency);
    mLastLatency = latency;
}

LatencyFrameStatisticsGL::ThisFrame LatencyFrameStatisticsGL::getThisFrame(
    EGLDisplay dpy, EGLSurface surface) {
    const TimePoint frameStartTime = std::chrono::steady_clock::now();

    // first get the next frame id
    std::pair<bool, EGLuint64KHR> nextFrameId =
        mEgl.getNextFrameId(dpy, surface);
    if (nextFrameId.first) {
        mPendingFrames.push_back(
            {dpy, surface, nextFrameId.second, frameStartTime});
    }

    if (mPendingFrames.empty()) {
        return {};
    }

    EGLFrame frame = mPendingFrames.front();
    // make sure we don't lag behind the stats too much
    if (nextFrameId.first && nextFrameId.second - frame.id > MAX_FRAME_LAG) {
        while (mPendingFrames.size() > 1)
            mPendingFrames.erase(mPendingFrames.begin());
        mPrevFrameTime = 0;
        frame = mPendingFrames.front();
    }
#if (not defined ANDROID_NDK_VERSION) || ANDROID_NDK_VERSION >= 14
    std::unique_ptr<EGL::FrameTimestamps> frameStats =
        mEgl.getFrameTimestamps(frame.dpy, frame.surface, frame.id);

    if (!frameStats) {
        return {frame.startFrameTime};
    }

    mPendingFrames.erase(mPendingFrames.begin());

    return {frame.startFrameTime, std::move(frameStats)};
#else
    return {frame.startFrameTime};
#endif
}

// called once per swap
void LatencyFrameStatisticsGL::capture(EGLDisplay dpy, EGLSurface surface) {
    auto frame = getThisFrame(dpy, surface);
    if (!frame.stats) return;
    updateLatency(*frame.stats, frame.startTime);
}

// NB This is only needed for C++14
constexpr std::chrono::nanoseconds FullFrameStatisticsGL::LOG_EVERY_N_NS;

FullFrameStatisticsGL::FullFrameStatisticsGL(const EGL& egl,
                                             const SwappyCommon& swappyCommon)
    : LatencyFrameStatisticsGL(egl, swappyCommon) {}

int32_t FullFrameStatisticsGL::updateFrames(EGLnsecsANDROID start,
                                            EGLnsecsANDROID end,
                                            uint64_t stat[]) {
    int32_t numFrames = getFrameDelta(start, end);
    stat[numFrames]++;
    return numFrames;
}

void FullFrameStatisticsGL::updateIdleFrames(EGL::FrameTimestamps& frameStats) {
    updateFrames(frameStats.renderingCompleted, frameStats.compositionLatched,
                 mStats.idleFrames);
}

void FullFrameStatisticsGL::updateLatencyFrames(
    swappy::EGL::FrameTimestamps& frameStats, TimePoint frameStartTime) {
    int latency =
        updateFrames(frameStartTime.time_since_epoch().count(),
                     frameStats.compositionLatched, mStats.latencyFrames);
    TRACE_INT("FrameLatency", latency);
    mLastLatency = latency;
}

void FullFrameStatisticsGL::updateLateFrames(EGL::FrameTimestamps& frameStats) {
    updateFrames(frameStats.requested, frameStats.presented, mStats.lateFrames);
}

void FullFrameStatisticsGL::updateOffsetFromPreviousFrame(
    swappy::EGL::FrameTimestamps& frameStats) {
    if (mPrevFrameTime != 0) {
        updateFrames(mPrevFrameTime, frameStats.presented,
                     mStats.offsetFromPreviousFrame);
    }
    mPrevFrameTime = frameStats.presented;
}

// called once per swap
void FullFrameStatisticsGL::capture(EGLDisplay dpy, EGLSurface surface) {
    auto frame = getThisFrame(dpy, surface);

    if (!frame.stats) return;

    std::lock_guard<std::mutex> lock(mMutex);
    mStats.totalFrames++;
    updateIdleFrames(*frame.stats);
    updateLateFrames(*frame.stats);
    updateOffsetFromPreviousFrame(*frame.stats);
    updateLatencyFrames(*frame.stats, frame.startTime);

    logFrames();
}

void FullFrameStatisticsGL::logFrames() {
    static auto previousLogTime = std::chrono::steady_clock::now();

    if (std::chrono::steady_clock::now() - previousLogTime < LOG_EVERY_N_NS) {
        return;
    }

    std::string message;
    ALOGI("== Frame statistics ==");
    ALOGI("total frames: %" PRIu64, mStats.totalFrames);
    message += "Buckets:                    ";
    for (int i = 0; i < MAX_FRAME_BUCKETS; i++)
        message += "\t[" + swappy::to_string(i) + "]";
    ALOGI("%s", message.c_str());

    message = "";
    message += "idle frames:                ";
    for (int i = 0; i < MAX_FRAME_BUCKETS; i++)
        message += "\t " + swappy::to_string(mStats.idleFrames[i]);
    ALOGI("%s", message.c_str());

    message = "";
    message += "late frames:                ";
    for (int i = 0; i < MAX_FRAME_BUCKETS; i++)
        message += "\t " + swappy::to_string(mStats.lateFrames[i]);
    ALOGI("%s", message.c_str());

    message = "";
    message += "offset from previous frame: ";
    for (int i = 0; i < MAX_FRAME_BUCKETS; i++)
        message += "\t " + swappy::to_string(mStats.offsetFromPreviousFrame[i]);
    ALOGI("%s", message.c_str());

    message = "";
    message += "frame latency:              ";
    for (int i = 0; i < MAX_FRAME_BUCKETS; i++)
        message += "\t " + swappy::to_string(mStats.latencyFrames[i]);
    ALOGI("%s", message.c_str());

    previousLogTime = std::chrono::steady_clock::now();
}

SwappyStats FullFrameStatisticsGL::getStats() {
    std::lock_guard<std::mutex> lock(mMutex);
    return mStats;
}

}  // namespace swappy
