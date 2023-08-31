
add_library(crypto STATIC IMPORTED GLOBAL)
set_target_properties(crypto PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libcrypto.a
)

add_library(curl STATIC IMPORTED GLOBAL)
set_target_properties(curl PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libcurl.a
)

if (USE_DEBUG_RENDERER)
add_library(freetype STATIC IMPORTED GLOBAL)
set_target_properties(freetype PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libfreetype.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/freetype
)
endif()

add_library(glfw3 STATIC IMPORTED GLOBAL)
set_target_properties(glfw3 PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libglfw3.a
)


add_library(jpeg STATIC IMPORTED GLOBAL)
set_target_properties(jpeg PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libjpeg.a
)

add_library(png STATIC IMPORTED GLOBAL)
set_target_properties(png PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libpng.a
)

add_library(ssl STATIC IMPORTED GLOBAL)
set_target_properties(ssl PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libssl.a
)

add_library(uv STATIC IMPORTED GLOBAL)
set_target_properties(uv PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libuv_a.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/uv
)

add_library(webp STATIC IMPORTED GLOBAL)
set_target_properties(webp PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libwebp.a
)

add_library(websockets STATIC IMPORTED GLOBAL)
set_target_properties(websockets PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libwebsockets.a
)

add_library(z STATIC IMPORTED GLOBAL)
set_target_properties(z PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libz.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/zlib
)

add_library(v8_monolith STATIC IMPORTED GLOBAL)
set_target_properties(v8_monolith PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libv8_monolith.a
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/v8
    INTERFACE_COMPILE_DEFINITIONS V8_COMPRESS_POINTERS
)

add_library(inspector STATIC IMPORTED GLOBAL)
set_target_properties(inspector PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libinspector.a
)
add_library(EGL SHARED IMPORTED GLOBAL)
set_target_properties(EGL PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libEGL.dylib
)

add_library(GLESv2 SHARED IMPORTED GLOBAL)
set_target_properties(GLESv2 PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libGLESv2.dylib
)

add_library(SDL2 SHARED IMPORTED GLOBAL)
set_target_properties(SDL2 PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libSDL2.a
)

set(se_libs_name)

if(CC_EDITOR)
  message(STATUS "CC_EDITOR USE V8 FROM NODEJS")
elseif(USE_SE_V8)
  list(APPEND se_libs_name
  v8_monolith
  uv
  )
  if(USE_V8_DEBUGGER)
  list(APPEND se_libs_name inspector)
  endif()
endif()

if(USE_SOCKET)
  list(APPEND CC_EXTERNAL_LIBS
      ssl
      crypto
      )
endif()

if(USE_WEBSOCKET_SERVER)
  list(APPEND CC_EXTERNAL_LIBS
      websockets
      )
endif()

############################# glslang #############################

add_library(GenericCodeGen STATIC IMPORTED GLOBAL)
set_target_properties(GenericCodeGen PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libGenericCodeGen.a
)

add_library(glslang STATIC IMPORTED GLOBAL)
set_target_properties(glslang PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libglslang.a
)

add_library(glslang-default-resource-limits STATIC IMPORTED GLOBAL)
set_target_properties(glslang-default-resource-limits PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libglslang-default-resource-limits.a
)

add_library(MachineIndependent STATIC IMPORTED GLOBAL)
set_target_properties(MachineIndependent PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libMachineIndependent.a
)

add_library(OGLCompiler STATIC IMPORTED GLOBAL)
set_target_properties(OGLCompiler PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libOGLCompiler.a
)

add_library(OSDependent STATIC IMPORTED GLOBAL)
set_target_properties(OSDependent PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libOSDependent.a
)

add_library(SPIRV STATIC IMPORTED GLOBAL)
set_target_properties(SPIRV PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libSPIRV.a
)

add_library(SPIRV-Tools STATIC IMPORTED GLOBAL)
set_target_properties(SPIRV-Tools PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libSPIRV-Tools.a
)

add_library(SPIRV-Tools-opt STATIC IMPORTED GLOBAL)
set_target_properties(SPIRV-Tools-opt PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libSPIRV-Tools-opt.a
)


set(glslang_libs_name glslang glslang-default-resource-limits MachineIndependent OGLCompiler OSDependent SPIRV SPIRV-Tools SPIRV-Tools-opt GenericCodeGen)

############################# SPIRV-Cross #############################

add_library(spirv-cross-core STATIC IMPORTED GLOBAL)
set_target_properties(spirv-cross-core PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libspirv-cross-core.a
)
add_library(spirv-cross-msl STATIC IMPORTED GLOBAL)
set_target_properties(spirv-cross-msl PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libspirv-cross-msl.a
)
add_library(spirv-cross-glsl STATIC IMPORTED GLOBAL)
set_target_properties(spirv-cross-glsl PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libspirv-cross-glsl.a
)
set(spirv-cross_libs_name spirv-cross-core spirv-cross-glsl spirv-cross-msl)

############################# TBB #############################

add_library(tbb STATIC IMPORTED GLOBAL)
set_target_properties(tbb PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libtbb_static.a
)
set(tbb_libs_name tbb)

if(USE_PHYSICS_PHYSX)
  set(PhysXSDK PhysX PhysXCommon PhysXFoundation PhysXExtensions PhysXCooking PhysXCharacterKinematic PhysXVehicle PhysXPvdSDK)
  foreach(PX IN LISTS PhysXSDK)
    add_library(${PX} STATIC IMPORTED GLOBAL)
    set_target_properties(${PX} PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/PhysX/lib${PX}_static_64.a
    )
  endforeach()
else()
  set(PhysXSDK)
endif()

if (USE_DEBUG_RENDERER)
list(APPEND CC_EXTERNAL_LIBS
    freetype
)
endif()

list(APPEND CC_EXTERNAL_LIBS
    jpeg
    png
    webp
    curl
    SDL2
    # sdl2 depends on the following two libraries.
    "-framework IOKit"
    "-framework Carbon"
    ${glslang_libs_name}
    ${spirv-cross_libs_name}
    ${tbb_libs_name}
    ${PhysXSDK}
)

set(ZLIB z)
if(NOT USE_MODULES)
  list(APPEND CC_EXTERNAL_LIBS ${ZLIB} ${se_libs_name})
endif()


list(APPEND CC_EXTERNAL_INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}/include
)
