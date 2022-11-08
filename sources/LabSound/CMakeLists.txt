include_guard()

set(LABSOUND_ROOT "${CMAKE_CURRENT_LIST_DIR}")

# default backend set up

if (LINUX)
    set(LABSOUND_PULSE ON)
    set(LIBNYQUIST_PULSE ON)
endif()

# NOTE: This configuration is build for debug level 4, as debug into libnyquist decode procedure.
# include(${CMAKE_CURRENT_LIST_DIR}/third_party/libnyquist/CMakeLists.txt)

# suppress testing of libsamplerate
# include(${CMAKE_CURRENT_LIST_DIR}/third_party/libsamplerate/CMakeLists.txt)

include(${CMAKE_CURRENT_LIST_DIR}/LabSound.cmake)
