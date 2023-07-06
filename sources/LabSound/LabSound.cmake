
# LabSound
#
# SPDX-License-Identifier: BSD-3-Clause
# Copyright (C) 2020, The LabSound Authors. All rights reserved.
#
# Will create a target named LabSound

file(GLOB labsnd_core_h     "${LABSOUND_ROOT}/include/LabSound/core/*")
file(GLOB labsnd_extended_h "${LABSOUND_ROOT}/include/LabSound/extended/*")
file(GLOB labsnd_core       "${LABSOUND_ROOT}/src/core/*")
file(GLOB labsnd_extended   "${LABSOUND_ROOT}/src/extended/*")
file(GLOB labsnd_int_h      "${LABSOUND_ROOT}/src/internal/*")
file(GLOB labsnd_int_src    "${LABSOUND_ROOT}/src/internal/src/*")
file(GLOB ooura_src         "${LABSOUND_ROOT}/third_party/ooura/src/*")

# backend selection

if (IOS)
    option(LABSOUND_USE_MINIAUDIO "Use miniaudio" ON)
    option(LABSOUND_USE_RTAUDIO "Use RtAudio" OFF)
elseif (APPLE)
    option(LABSOUND_USE_MINIAUDIO "Use miniaudio" OFF)
    option(LABSOUND_USE_RTAUDIO "Use RtAudio" ON)
elseif (WIN32)
    option(LABSOUND_USE_MINIAUDIO "Use miniaudio" OFF)
    option(LABSOUND_USE_RTAUDIO "Use RtAudio" ON)
elseif (ANDROID)
    option(LABSOUND_USE_MINIAUDIO "Use miniaudio" ON)
    option(LABSOUND_USE_RTAUDIO "Use RtAudio" OFF)
elseif (LINUX)
    option(LABSOUND_USE_MINIAUDIO "Use miniaudio" OFF)
    option(LABSOUND_USE_RTAUDIO "Use RtAudio" ON)
else ()
    # For Harmony OS, we should not link this library.
    # message(FATAL, " Untested platform. Please try miniaudio and report results on the LabSound issues page")
endif()


if (LABSOUND_USE_MINIAUDIO)
    message(STATUS "Using miniaudio backend")
    if (IOS)
        set(labsnd_backend
            "${LABSOUND_ROOT}/src/backends/miniaudio/AudioDevice_Miniaudio.mm"
            "${LABSOUND_ROOT}/src/backends/miniaudio/AudioDevice_Miniaudio.h"
            "${LABSOUND_ROOT}/third_party/miniaudio/miniaudio.h"
        )
    else()
        set(labsnd_backend
            "${LABSOUND_ROOT}/src/backends/miniaudio/AudioDevice_Miniaudio.cpp"
            "${LABSOUND_ROOT}/src/backends/miniaudio/AudioDevice_Miniaudio.h"
            "${LABSOUND_ROOT}/third_party/miniaudio/miniaudio.h"
        )
    endif()
elseif (LABSOUND_USE_RTAUDIO)
    message(STATUS "Using RtAudio backend")
    set(labsnd_backend
        "${LABSOUND_ROOT}/src/backends/RtAudio/AudioDevice_RtAudio.cpp"
        "${LABSOUND_ROOT}/src/backends/RtAudio/AudioDevice_RtAudio.h"
        "${LABSOUND_ROOT}/src/backends/RtAudio/RtAudio.cpp"
        "${LABSOUND_ROOT}/src/backends/RtAudio/RtAudio.h"
    )
endif()


# FFT
if (APPLE)
    set(labsnd_fft_src "${LABSOUND_ROOT}/src/backends/FFTFrameAppleAcclerate.cpp")
else()
    file(GLOB labsnd_fft_src "${LABSOUND_ROOT}/third_party/kissfft/src/*")
endif()

# TODO ooura or kissfft? benchmark and choose. Then benchmark vs FFTFrameAppleAcclerate
set(ooura_src
    "${LABSOUND_ROOT}/third_party/ooura/src/fftsg.cpp"
    "${LABSOUND_ROOT}/third_party/ooura/fftsg.h")

set(LABSOUND_SOURCES
    "${LABSOUND_ROOT}/include/LabSound/LabSound.h"
    ${labsnd_core_h}
    ${labsnd_core}
    ${labsnd_extended_h}
    ${labsnd_extended}
    ${labsnd_int_h}
    ${labsnd_int_src}
    ${labsnd_backend}
    ${labsnd_fft_src}
    ${ooura_src}
)

# LABSOUND_INCLUDE: Export for cocos
list(APPEND LABSOUND_INCLUDE
    ${LABSOUND_ROOT}/src
    ${LABSOUND_ROOT}/include
    ${LABSOUND_ROOT}/third_party
    ${LABSOUND_ROOT}/third_party/libnyquist/include
    ${LABSOUND_ROOT}/third_party/ooura
    ${LABSOUND_ROOT}/third_party/ooura/src
    ${LABSOUND_ROOT}/third_party/kissfft/src
    ${LABSOUND_ROOT}/third_party/miniaudio
)
