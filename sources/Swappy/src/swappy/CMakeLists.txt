project(swappy C CXX)
set(IgnoreOldToolchainWarning "${ANDROID_UNIFIED_HEADERS}")

# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wthread-safety" )
# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D _LIBCPP_ENABLE_THREAD_SAFETY_ANNOTATIONS -O3 -fPIC" )
# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions" )
# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti" )
# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections" )
# set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g0")
# if ( DEFINED GAMESDK_THREAD_CHECKS )
#   set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGAMESDK_THREAD_CHECKS=${GAMESDK_THREAD_CHECKS}" )
# endif()

# set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections" )
# set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-s" )
# set( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--hash-style=both" )

#no statistics log
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG" )

set ( SOURCE_LOCATION ${CMAKE_CURRENT_LIST_DIR})
set ( SOURCE_LOCATION_COMMON "${SOURCE_LOCATION}/common" )
set ( SOURCE_LOCATION_OPENGL "${SOURCE_LOCATION}/opengl" )
set ( SOURCE_LOCATION_VULKAN "${SOURCE_LOCATION}/vulkan" )

include_directories( ${CMAKE_CURRENT_LIST_DIR}/../../include )
include_directories( ${CMAKE_CURRENT_LIST_DIR}/../common )
include_directories( ${CMAKE_CURRENT_LIST_DIR}/common )

if(CC_USE_GLES3 OR CC_USE_GLES2)
    include_directories( ${CMAKE_CURRENT_LIST_DIR}/opengl )
endif()

if(CC_USE_VULKAN)
    include_directories( ${CMAKE_CURRENT_LIST_DIR}/vulkan )
    include_directories( ${ANDROID_NDK}/sources/third_party/vulkan/src/common )
endif()

message( STATUS "Building swappy_static to ${CMAKE_CURRENT_BINARY_DIR}/build" )

# Dex linking requires an extra option for later versions of clang lld
if (ANDROID_NDK_MAJOR GREATER 18)
    if ( ANDROID_NDK_ABI_NAME MATCHES "armeabi-v7a")
        set (LINKER_TARGET_EMULATION_OPTION "-m" "armelf_linux_eabi")
    elseif(ANDROID_NDK_ABI_NAME MATCHES "arm64-v8a")
        set (LINKER_TARGET_EMULATION_OPTION "-m" "aarch64linux")
    elseif(ANDROID_NDK_ABI_NAME MATCHES "x86_64")
        set (LINKER_TARGET_EMULATION_OPTION "-m" "elf_x86_64")
    elseif(ANDROID_NDK_ABI_NAME MATCHES "x86")
        set (LINKER_TARGET_EMULATION_OPTION "-m" "elf_i386")
    endif()
endif()

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/classes_dex.o
        COMMAND ${ANDROID_TOOLCHAIN_ROOT}/bin/ld.lld${ANDROID_TOOLCHAIN_SUFFIX} ${LINKER_TARGET_EMULATION_OPTION} -r -b binary -o ${CMAKE_CURRENT_BINARY_DIR}/classes_dex.o classes.dex
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        )

set_source_files_properties(SwappyDisplayManager
        classes_dex.o
        PROPERTIES
        EXTERNAL_OBJECT true
        GENERATED true
)

set(SRC_FILE
        ${SOURCE_LOCATION_COMMON}/ChoreographerFilter.cpp
        ${SOURCE_LOCATION_COMMON}/ChoreographerThread.cpp
        ${SOURCE_LOCATION_COMMON}/CpuInfo.cpp
        ${SOURCE_LOCATION_COMMON}/Settings.cpp
        ${SOURCE_LOCATION_COMMON}/Thread.cpp
        ${SOURCE_LOCATION_COMMON}/SwappyCommon.cpp
        ${SOURCE_LOCATION_COMMON}/swappy_c.cpp
        ${SOURCE_LOCATION_COMMON}/SwappyDisplayManager.cpp
        ${SOURCE_LOCATION_COMMON}/CPUTracer.cpp
        ${SOURCE_LOCATION}/../common/system_utils.cpp)

set(SWAPPY_C_SRC)
if(CC_USE_GLES3 OR CC_USE_GLES2)
    list(APPEND SRC_FILE
            ${SOURCE_LOCATION_OPENGL}/EGL.cpp
            ${SOURCE_LOCATION_OPENGL}/swappyGL_c.cpp
            ${SOURCE_LOCATION_OPENGL}/SwappyGL.cpp
            ${SOURCE_LOCATION_OPENGL}/FrameStatisticsGL.cpp)
    list(APPEND SWAPPY_C_SRC
            ${SOURCE_LOCATION_OPENGL}/swappyGL_c.cpp)
endif()

if(CC_USE_VULKAN)
    list(APPEND SRC_FILE
            ${SOURCE_LOCATION_VULKAN}/swappyVk_c.cpp
            ${SOURCE_LOCATION_VULKAN}/SwappyVk.cpp
            ${SOURCE_LOCATION_VULKAN}/SwappyVkBase.cpp
            ${SOURCE_LOCATION_VULKAN}/SwappyVkFallback.cpp
            ${SOURCE_LOCATION_VULKAN}/SwappyVkGoogleDisplayTiming.cpp)
    list(APPEND SWAPPY_C_SRC
            ${SOURCE_LOCATION_VULKAN}/swappyVk_c.cpp)
endif()

add_library( swappy_static
                STATIC
                ${SRC_FILE}
                ${CMAKE_CURRENT_BINARY_DIR}/classes_dex.o
                # Add new source files here
        )


set_target_properties( swappy_static PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build )

add_library(swappy
                SHARED
                ${SWAPPY_C_SRC})

set(LIBS
        swappy_static
        android
        log
        atomic)

if(CC_USE_GLES3 OR CC_USE_GLES2)
    list(APPEND LIBS GLESv2)
endif()

target_link_libraries( swappy ${LIBS})
