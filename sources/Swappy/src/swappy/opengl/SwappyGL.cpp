/*
 * Copyright 2018 The Android Open Source Project
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

#include "SwappyGL.h"

#include <cinttypes>
#include <cmath>
#include <cstdlib>

#include "Log.h"
#include "Thread.h"
#include "Trace.h"
#include "system_utils.h"

#define LOG_TAG "Swappy"

namespace swappy {

using std::chrono::milliseconds;
using std::chrono::nanoseconds;

std::mutex SwappyGL::sInstanceMutex;
std::unique_ptr<SwappyGL> SwappyGL::sInstance;

bool SwappyGL::init(JNIEnv *env, jobject jactivity) {
    std::lock_guard<std::mutex> lock(sInstanceMutex);
    if (sInstance) {
        ALOGE("Attempted to initialize SwappyGL twice");
        return false;
    }
    sInstance = std::make_unique<SwappyGL>(env, jactivity, ConstructorTag{});
    if (!sInstance->mEnableSwappy) {
        ALOGE("Failed to initialize SwappyGL");
        return false;
    }

    return true;
}

void SwappyGL::onChoreographer(int64_t frameTimeNanos) {
    TRACE_CALL();

    SwappyGL *swappy = getInstance();
    if (!swappy) {
        return;
    }

    swappy->mCommonBase.onChoreographer(frameTimeNanos);
}

bool SwappyGL::setWindow(ANativeWindow *window) {
    TRACE_CALL();

    SwappyGL *swappy = getInstance();
    if (!swappy) {
        ALOGE("Failed to get SwappyGL instance in setWindow");
        return false;
    }

    swappy->mCommonBase.setANativeWindow(window);
    return true;
}

bool SwappyGL::swap(EGLDisplay display, EGLSurface surface) {
    TRACE_CALL();

    SwappyGL *swappy = getInstance();
    if (!swappy) {
        return EGL_FALSE;
    }

    if (swappy->enabled()) {
        return swappy->swapInternal(display, surface);
    } else {
        return swappy->getEgl()->swapBuffers(display, surface) == EGL_TRUE;
    }
}

bool SwappyGL::lastFrameIsComplete(EGLDisplay display) {
    if (!getEgl()->lastFrameIsComplete(display)) {
        gamesdk::ScopedTrace trace("lastFrameIncomplete");
        ALOGV("lastFrameIncomplete");
        return false;
    }
    return true;
}

bool SwappyGL::swapInternal(EGLDisplay display, EGLSurface surface) {
    const SwappyCommon::SwapHandlers handlers = {
        .lastFrameIsComplete = [&]() { return lastFrameIsComplete(display); },
        .getPrevFrameGpuTime =
            [&]() { return getEgl()->getFencePendingTime(); },
    };

    mCommonBase.onPreSwap(handlers);

    if (mCommonBase.needToSetPresentationTime()) {
        bool setPresentationTimeResult = setPresentationTime(display, surface);
        if (!setPresentationTimeResult) {
            return setPresentationTimeResult;
        }
    }

    resetSyncFence(display);

    bool swapBuffersResult =
        (getEgl()->swapBuffers(display, surface) == EGL_TRUE);

    mCommonBase.onPostSwap(handlers);

    return swapBuffersResult;
}

void SwappyGL::addTracer(const SwappyTracer *tracer) {
    SwappyGL *swappy = getInstance();
    if (!swappy) {
        return;
    }
    if (swappy->enabled() && tracer != nullptr)
        swappy->mCommonBase.addTracerCallbacks(*tracer);
}

void SwappyGL::removeTracer(const SwappyTracer *tracer) {
    SwappyGL *swappy = getInstance();
    if (!swappy) {
        return;
    }
    if (swappy->enabled() && tracer != nullptr)
        swappy->mCommonBase.removeTracerCallbacks(*tracer);
}

nanoseconds SwappyGL::getSwapDuration() {
    SwappyGL *swappy = getInstance();
    if (!swappy || !swappy->enabled()) {
        return -1ns;
    }
    return swappy->mCommonBase.getSwapDuration();
};

void SwappyGL::setAutoSwapInterval(bool enabled) {
    SwappyGL *swappy = getInstance();
    if (!swappy) {
        return;
    }
    if (swappy->enabled()) swappy->mCommonBase.setAutoSwapInterval(enabled);
}

void SwappyGL::setAutoPipelineMode(bool enabled) {
    SwappyGL *swappy = getInstance();
    if (!swappy) {
        return;
    }
    if (swappy->enabled()) swappy->mCommonBase.setAutoPipelineMode(enabled);
}

void SwappyGL::setMaxAutoSwapDuration(std::chrono::nanoseconds maxDuration) {
    SwappyGL *swappy = getInstance();
    if (!swappy) {
        return;
    }
    if (swappy->enabled())
        swappy->mCommonBase.setMaxAutoSwapDuration(maxDuration);
}

void SwappyGL::enableStats(bool enabled) {
    SwappyGL *swappy = getInstance();
    if (!swappy) {
        return;
    }

    if (!swappy->enabled()) {
        return;
    }

    if (!swappy->getEgl()->statsSupported()) {
        ALOGI("stats are not suppored on this platform");
        return;
    }

    if (enabled) {
        if (!swappy->mFrameStatistics ||
            swappy->mFrameStatistics->isEssential()) {
            swappy->mFrameStatistics = std::make_shared<FullFrameStatisticsGL>(
                *swappy->mEgl, swappy->mCommonBase);
            ALOGI("Enabling stats");
        } else {
            ALOGI("Stats already enabled");
        }
    } else {
        swappy->mFrameStatistics = std::make_shared<LatencyFrameStatisticsGL>(
            *swappy->mEgl, swappy->mCommonBase);
        ALOGI("Disabling stats");
    }
    swappy->mCommonBase.setFrameStatistics(swappy->mFrameStatistics);
}

void SwappyGL::recordFrameStart(EGLDisplay display, EGLSurface surface) {
    TRACE_CALL();
    SwappyGL *swappy = getInstance();
    if (!swappy) {
        return;
    }

    if (swappy->mFrameStatistics)
        swappy->mFrameStatistics->capture(display, surface);
}

void SwappyGL::getStats(SwappyStats *stats) {
    SwappyGL *swappy = getInstance();
    if (!swappy) {
        return;
    }

    if (swappy->mFrameStatistics && !swappy->mFrameStatistics->isEssential())
        *stats = swappy->mFrameStatistics->getStats();
}

SwappyGL *SwappyGL::getInstance() {
    std::lock_guard<std::mutex> lock(sInstanceMutex);
    return sInstance.get();
}

bool SwappyGL::isEnabled() {
    SwappyGL *swappy = getInstance();
    if (!swappy) {
        // This is a case of error.
        // We do not log anything here, so that we do not spam
        // the user when this function is called each frame.
        return false;
    }
    return swappy->enabled();
}

void SwappyGL::destroyInstance() {
    std::lock_guard<std::mutex> lock(sInstanceMutex);
    sInstance.reset();
}

void SwappyGL::setFenceTimeout(std::chrono::nanoseconds t) {
    SwappyGL *swappy = getInstance();
    if (!swappy || !swappy->enabled()) {
        return;
    }
    swappy->mCommonBase.setFenceTimeout(t);
}

std::chrono::nanoseconds SwappyGL::getFenceTimeout() {
    SwappyGL *swappy = getInstance();
    if (!swappy || !swappy->enabled()) {
        return std::chrono::nanoseconds(0);
    }
    return swappy->mCommonBase.getFenceTimeout();
}

EGL *SwappyGL::getEgl() {
    static thread_local EGL *egl = nullptr;
    if (!egl) {
        std::lock_guard<std::mutex> lock(mEglMutex);
        egl = mEgl.get();
    }
    return egl;
}

SwappyGL::SwappyGL(JNIEnv *env, jobject jactivity, ConstructorTag)
    : mFrameStatistics(nullptr), mCommonBase(env, jactivity) {
    {
        std::lock_guard<std::mutex> lock(mEglMutex);
        mEgl = EGL::create(mCommonBase.getFenceTimeout());
        if (!mEgl) {
            ALOGE("Failed to load EGL functions");
            mEnableSwappy = false;
            return;
        }
    }

    if (!mCommonBase.isValid()) {
        ALOGE("SwappyCommon could not initialize correctly.");
        mEnableSwappy = false;
        return;
    }

    mEnableSwappy =
        !gamesdk::GetSystemPropAsBool(SWAPPY_SYSTEM_PROP_KEY_DISABLE, false);
    if (!enabled()) {
        ALOGI("Swappy is disabled");
        return;
    }

    ALOGI("SwappyGL initialized successfully");
}

void SwappyGL::resetSyncFence(EGLDisplay display) {
    getEgl()->resetSyncFence(display);
}

bool SwappyGL::setPresentationTime(EGLDisplay display, EGLSurface surface) {
    TRACE_CALL();

    auto displayTimings = Settings::getInstance()->getDisplayTimings();

    // if we are too close to the vsync, there is no need to set presentation
    // time
    if ((mCommonBase.getPresentationTime() - std::chrono::steady_clock::now()) <
        (mCommonBase.getRefreshPeriod() - displayTimings.sfOffset)) {
        return EGL_TRUE;
    }
    return getEgl()->setPresentationTime(display, surface,
                                         mCommonBase.getPresentationTime());
}

void SwappyGL::setBufferStuffingFixWait(int32_t n_frames) {
    TRACE_CALL();
    SwappyGL *swappy = getInstance();
    if (!swappy) {
        return;
    }
    swappy->mCommonBase.setBufferStuffingFixWait(n_frames);
}

}  // namespace swappy
