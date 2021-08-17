
set(CC_EXTERNAL_LIBS)
set(CC_EXTERNAL_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/sources)
set(CC_EXTERNAL_PRIVATE_INCLUDES)
set(CC_EXTERNAL_PRIVATE_DEFINITIONS)

list(APPEND CC_EXTERNAL_PRIVATE_DEFINITIONS
    TBB_USE_EXCEPTIONS=0 # no rtti for now
)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/CocosExternalConfig.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/sources/CMakeLists.txt)

if(WINDOWS)
    if(${CMAKE_SIZEOF_VOID_P} STREQUAL "4")
        include(${CMAKE_CURRENT_LIST_DIR}/win32/CMakeLists.txt)    
    else()
        include(${CMAKE_CURRENT_LIST_DIR}/win64/CMakeLists.txt)
    endif()
elseif(ANDROID)
    include(${CMAKE_CURRENT_LIST_DIR}/android/CMakeLists.txt)
elseif(APPLE)
    if(MACOSX)
        include(${CMAKE_CURRENT_LIST_DIR}/mac/CMakeLists.txt)
    elseif(IOS)
        # include(${CMAKE_CURRENT_LIST_DIR}/ios-m1-simulator/CMakeLists.txt) # Uncomment this line and comment next line if using M1 simulator
        include(${CMAKE_CURRENT_LIST_DIR}/ios/CMakeLists.txt)
    endif()
elseif(OHOS)
    include(${CMAKE_CURRENT_LIST_DIR}/ohos/CMakeLists.txt)
elseif(EMSCRIPTEN)
    include(${CMAKE_CURRENT_LIST_DIR}/emscripten/CMakeLists.txt)
endif()
