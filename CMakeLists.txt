
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
    include(${CMAKE_CURRENT_LIST_DIR}/win32/CMakeLists.txt)
elseif(ANDROID)
    include(${CMAKE_CURRENT_LIST_DIR}/android/CMakeLists.txt)
elseif(APPLE)
    if(MACOSX)
        include(${CMAKE_CURRENT_LIST_DIR}/mac/CMakeLists.txt)
    elseif(IOS)
        include(${CMAKE_CURRENT_LIST_DIR}/ios/CMakeLists.txt)
    endif()
endif()
