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

#pragma once

#include <array>
#include <atomic>
#include <map>
#include <vector>

#include "EGL.h"
#include "FrameStatistics.h"
#include "Thread.h"

using TimePoint = std::chrono::steady_clock::time_point;
using namespace std::chrono_literals;

namespace swappy {

class SwappyCommon;

// Just records latency
class LatencyFrameStatisticsGL : public FrameStatistics {
   public:
    LatencyFrameStatisticsGL(const EGL& egl, const SwappyCommon& swappyCommon);
    ~LatencyFrameStatisticsGL() = default;
    int32_t lastLatencyRecorded() const override { return mLastLatency; }
    bool isEssential() const override { return true; }
    virtual SwappyStats getStats() override { return {}; }

    virtual void capture(EGLDisplay dpy, EGLSurface surface);

   protected:
    static constexpr int MAX_FRAME_LAG = 10;
    int32_t getFrameDelta(EGLnsecsANDROID start, EGLnsecsANDROID end);
    struct ThisFrame {
        TimePoint startTime;
        std::unique_ptr<EGL::FrameTimestamps> stats;
    };
    ThisFrame getThisFrame(EGLDisplay dpy, EGLSurface surface);
    void updateLatency(EGL::FrameTimestamps& frameStats,
                       TimePoint frameStartTime);

    const EGL& mEgl;
    const SwappyCommon& mSwappyCommon;

    struct EGLFrame {
        EGLDisplay dpy;
        EGLSurface surface;
        EGLuint64KHR id;
        TimePoint startFrameTime;
    };
    std::vector<EGLFrame> mPendingFrames;
    EGLnsecsANDROID mPrevFrameTime = 0;
    std::atomic<int32_t> mLastLatency = {0};
};

class FullFrameStatisticsGL : public LatencyFrameStatisticsGL {
   public:
    FullFrameStatisticsGL(const EGL& egl, const SwappyCommon& swappyCommon);
    ~FullFrameStatisticsGL() = default;

    void capture(EGLDisplay dpy, EGLSurface surface) override;

    SwappyStats getStats() override;

    bool isEssential() const override { return false; }

   private:
    static constexpr std::chrono::nanoseconds LOG_EVERY_N_NS = 1s;

    int updateFrames(EGLnsecsANDROID start, EGLnsecsANDROID end,
                     uint64_t stat[]);
    void updateIdleFrames(EGL::FrameTimestamps& frameStats) REQUIRES(mMutex);
    void updateLateFrames(EGL::FrameTimestamps& frameStats) REQUIRES(mMutex);
    void updateOffsetFromPreviousFrame(EGL::FrameTimestamps& frameStats)
        REQUIRES(mMutex);
    void updateLatencyFrames(EGL::FrameTimestamps& frameStats,
                             TimePoint frameStartTime) REQUIRES(mMutex);
    void logFrames() REQUIRES(mMutex);

    std::mutex mMutex;
    SwappyStats mStats GUARDED_BY(mMutex) = {};
};

}  // namespace swappy
