

set(CC_UNZIP_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/unzip/crypt.h
  ${CMAKE_CURRENT_LIST_DIR}/unzip/ioapi.cpp
  ${CMAKE_CURRENT_LIST_DIR}/unzip/ioapi.h
  ${CMAKE_CURRENT_LIST_DIR}/unzip/ioapi_mem.cpp
  ${CMAKE_CURRENT_LIST_DIR}/unzip/ioapi_mem.h
  ${CMAKE_CURRENT_LIST_DIR}/unzip/unzip.cpp
  ${CMAKE_CURRENT_LIST_DIR}/unzip/unzip.h
)

set(CC_TINYDIR_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/tinyxml2/tinyxml2.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tinyxml2/tinyxml2.h
  ${CMAKE_CURRENT_LIST_DIR}/tinydir/tinydir.h
)

set(CC_UTILS_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/ConvertUTF/ConvertUTF.c
  ${CMAKE_CURRENT_LIST_DIR}/ConvertUTF/ConvertUTF.h
  ${CMAKE_CURRENT_LIST_DIR}/ConvertUTF/ConvertUTFWrapper.cpp
  ${CMAKE_CURRENT_LIST_DIR}/xxtea/xxtea.cpp
  ${CMAKE_CURRENT_LIST_DIR}/xxtea/xxtea.h
)

set(CC_EXTERNAL_SOURCES

  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommy.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommy.h
)

set (CC_MESHOPT_SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/meshopt/meshoptimizer.h
  ${CMAKE_CURRENT_LIST_DIR}/meshopt/vertexcodec.cpp
  ${CMAKE_CURRENT_LIST_DIR}/meshopt/indexcodec.cpp
)

if(NOT USE_MODULES)
  list(APPEND CC_EXTERNAL_SOURCES
    ${CC_UNZIP_SOURCES}
    ${CC_TINYDIR_SOURCES}
    ${CC_UTILS_SOURCES}
    ${CC_MESHOPT_SOURCES}
  )
endif()

# add dependent boost libs
if((NOT NX) AND (NOT EMSCRIPTEN))
  include(${CMAKE_CURRENT_LIST_DIR}/boost-source/boost.cmake)
endif()

if(ANDROID AND CC_ENABLE_SWAPPY)

include(${CMAKE_CURRENT_LIST_DIR}/Swappy/src/swappy/CMakeLists.txt)
list(APPEND CC_EXTERNAL_LIBS
  swappy
)
add_definitions(-DCC_SWAPPY_ENABLED)

endif()


if(ANDROID AND (NOT SURFACE_LESS_SERVICE))
    set(CC_GAME_ACTIVITY_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/android-gamesdk/GameActivity/game-activity/include/game-activity/GameActivity.cpp
        ${CMAKE_CURRENT_LIST_DIR}/android-gamesdk/GameActivity/game-activity/include/game-activity/system_utils.cpp
        ${CMAKE_CURRENT_LIST_DIR}/android-gamesdk/GameActivity/game-activity/include/game-activity/native_app_glue/android_native_app_glue.c
        ${CMAKE_CURRENT_LIST_DIR}/android-gamesdk/GameActivity/game-activity/include/game-text-input/gametextinput.cpp
    )

    include(${CMAKE_CURRENT_LIST_DIR}/android-gamesdk/GameController/CMakeLists.txt)
    list(APPEND CC_EXTERNAL_SOURCES
        ${CC_GAME_ACTIVITY_SOURCES}
    )
    include_directories(${CMAKE_CURRENT_LIST_DIR}/android-gamesdk/GameActivity/game-activity/include)
endif()

if(ANDROID OR OHOS OR NX)

  include(${CMAKE_CURRENT_LIST_DIR}/pvmp3dec/CMakeLists.txt)
  include(${CMAKE_CURRENT_LIST_DIR}/tremolo/CMakeLists.txt)

  list(APPEND CC_EXTERNAL_LIBS
    pvmp3dec
    vorbisidec
  )

elseif(WINDOWS)
  set_source_files_properties(${CMAKE_CURRENT_LIST_DIR}/ConvertUTF/ConvertUTF.c PROPERTIES
    LANGUAGE C
  )
elseif(APPLE)
  if(USE_SOCKET)
      include(${CMAKE_CURRENT_LIST_DIR}/SocketRocket/CMakeLists.txt)
  endif()
elseif(NX_WINDOWS)
  include(${CMAKE_CURRENT_LIST_DIR}/pvmp3dec/CMakeLists.txt)
  list(APPEND CC_EXTERNAL_LIBS
    pvmp3dec
  )
endif()

if((NOT NX_WINDOWS) AND (NOT NX))
  list(APPEND CC_EXTERNAL_INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}
  )
endif()

if(USE_PHYSICS_PHYSX)
  list(APPEND CC_EXTERNAL_INCLUDES
    ${CMAKE_CURRENT_LIST_DIR}/PhysX/PhysX/include
    ${CMAKE_CURRENT_LIST_DIR}/PhysX/PhysX/source
    ${CMAKE_CURRENT_LIST_DIR}/PhysX/PxShared/include
  )
endif()
