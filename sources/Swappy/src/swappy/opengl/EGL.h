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

#pragma once

#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>

#include "Thread.h"

namespace swappy {

class EGL {
   private:
    // Allows construction with std::unique_ptr from a static method, but
    // disallows construction outside of the class since no one else can
    // construct a ConstructorTag
    struct ConstructorTag {};

   public:
    struct FrameTimestamps {
        EGLnsecsANDROID requested;
        EGLnsecsANDROID renderingCompleted;
        EGLnsecsANDROID compositionLatched;
        EGLnsecsANDROID presented;
    };

    using eglGetProcAddress_type = void (*(*)(const char *))(void);

    explicit EGL(std::chrono::nanoseconds fenceTimeout,
                 eglGetProcAddress_type getProcAddress, ConstructorTag)
        : mFenceWaiter(fenceTimeout, getProcAddress) {}
    ~EGL();
    static std::unique_ptr<EGL> create(std::chrono::nanoseconds fenceTimeout);

    void resetSyncFence(EGLDisplay display);
    bool lastFrameIsComplete(EGLDisplay display);
    bool setPresentationTime(EGLDisplay display, EGLSurface surface,
                             std::chrono::steady_clock::time_point time);
    std::chrono::nanoseconds getFencePendingTime() const {
        return mFenceWaiter.getFencePendingTime();
    }

    // for stats
    bool statsSupported();
    std::pair<bool, EGLuint64KHR> getNextFrameId(EGLDisplay dpy,
                                                 EGLSurface surface) const;
    std::unique_ptr<FrameTimestamps> getFrameTimestamps(
        EGLDisplay dpy, EGLSurface surface, EGLuint64KHR frameId) const;
    EGLBoolean swapBuffers(EGLDisplay dpy, EGLSurface surface) {
        return this->eglSwapBuffers(dpy, surface);
    }

   private:
    void *eglLib = nullptr;
    eglGetProcAddress_type eglGetProcAddress = nullptr;
    using eglSwapBuffers_type = EGLBoolean (*)(EGLDisplay, EGLSurface);
    eglSwapBuffers_type eglSwapBuffers = nullptr;
    using eglPresentationTimeANDROID_type = EGLBoolean (*)(EGLDisplay,
                                                           EGLSurface,
                                                           EGLnsecsANDROID);
    eglPresentationTimeANDROID_type eglPresentationTimeANDROID = nullptr;
    using eglCreateSyncKHR_type = EGLSyncKHR (*)(EGLDisplay, EGLenum,
                                                 const EGLint *);
    eglCreateSyncKHR_type eglCreateSyncKHR = nullptr;
    using eglDestroySyncKHR_type = EGLBoolean (*)(EGLDisplay, EGLSyncKHR);
    eglDestroySyncKHR_type eglDestroySyncKHR = nullptr;
    using eglGetSyncAttribKHR_type = EGLBoolean (*)(EGLDisplay, EGLSyncKHR,
                                                    EGLint, EGLint *);
    eglGetSyncAttribKHR_type eglGetSyncAttribKHR = nullptr;

    using eglGetError_type = EGLint (*)(void);
    eglGetError_type eglGetError = nullptr;
    using eglSurfaceAttrib_type = EGLBoolean (*)(EGLDisplay, EGLSurface, EGLint,
                                                 EGLint);
    eglSurfaceAttrib_type eglSurfaceAttrib = nullptr;
    using eglGetNextFrameIdANDROID_type = EGLBoolean (*)(EGLDisplay, EGLSurface,
                                                         EGLuint64KHR *);
    eglGetNextFrameIdANDROID_type eglGetNextFrameIdANDROID = nullptr;
    using eglGetFrameTimestampsANDROID_type =
        EGLBoolean (*)(EGLDisplay, EGLSurface, EGLuint64KHR, EGLint,
                       const EGLint *, EGLnsecsANDROID *);
    eglGetFrameTimestampsANDROID_type eglGetFrameTimestampsANDROID = nullptr;

    std::mutex mSyncFenceMutex;
    EGLSyncKHR mSyncFence = EGL_NO_SYNC_KHR;

    class FenceWaiter {
       public:
        FenceWaiter(std::chrono::nanoseconds fenceTimeout,
                    EGL::eglGetProcAddress_type getProcAddress);
        ~FenceWaiter();

        void onFenceCreation(EGLDisplay display, EGLSyncKHR syncFence);
        // Wait and return true if the fence was signalled.
        // The fence will NOT be destroyed in this case.
        bool waitForIdle();
        std::chrono::nanoseconds getFencePendingTime() const;

       private:
        using eglClientWaitSyncKHR_type = EGLBoolean (*)(EGLDisplay, EGLSyncKHR,
                                                         EGLint, EGLTimeKHR);
        eglClientWaitSyncKHR_type eglClientWaitSyncKHR = nullptr;
        using eglDestroySyncKHR_type = EGLBoolean (*)(EGLDisplay, EGLSyncKHR);
        eglDestroySyncKHR_type eglDestroySyncKHR = nullptr;

        void threadMain();
        Thread mFenceWaiter GUARDED_BY(mFenceWaiterLock);
        std::mutex mFenceWaiterLock;
        std::condition_variable_any mFenceWaiterCondition;
        bool mFenceWaiterRunning GUARDED_BY(mFenceWaiterLock) = true;
        bool mFenceWaiterPending GUARDED_BY(mFenceWaiterLock) = false;
        std::atomic<std::chrono::nanoseconds> mFencePendingTime;
        EGLDisplay mDisplay GUARDED_BY(mFenceWaiterLock);
        EGLSyncKHR mSyncFence GUARDED_BY(mFenceWaiterLock) = EGL_NO_SYNC_KHR;
        std::chrono::nanoseconds mFenceTimeout;
    };

    FenceWaiter mFenceWaiter;
};

}  // namespace swappy
