#
# Copyright (C) 2021 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
project(paddleboat C CXX)

include_directories(${CMAKE_CURRENT_LIST_DIR}/paddleboat/include)

set( PADDLEBOAT_SRCS
        ${CMAKE_CURRENT_LIST_DIR}/InternalControllerTable.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GameController.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GameControllerDeviceInfo.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GameControllerLog.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GameControllerManager.cpp
        ${CMAKE_CURRENT_LIST_DIR}/GameControllerMappingUtils.cpp
        ${CMAKE_CURRENT_LIST_DIR}/paddleboat_c.cpp)

# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Os")
# set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")
# set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g0")

add_library(paddleboat_static STATIC ${PADDLEBOAT_SRCS})

set_target_properties( paddleboat_static PROPERTIES
     LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build )

add_library(paddleboat SHARED ${CMAKE_CURRENT_LIST_DIR}/paddleboat_c.cpp)

target_link_libraries(paddleboat
  paddleboat_static
  android
  atomic
  log)
