
add_library(crypto STATIC IMPORTED GLOBAL)
set_target_properties(crypto PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libcrypto.a
)

if (USE_DEBUG_RENDERER)
add_library(freetype STATIC IMPORTED GLOBAL)
set_target_properties(freetype PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libfreetype.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/freetype
)
endif()

add_library(jpeg STATIC IMPORTED GLOBAL)
set_target_properties(jpeg PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libjpeg.a
)

add_library(png STATIC IMPORTED GLOBAL)
set_target_properties(png PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libpng.a
)

add_library(ssl STATIC IMPORTED GLOBAL)
set_target_properties(ssl PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libssl.a
)

add_library(uv STATIC IMPORTED GLOBAL)
set_target_properties(uv PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libuv.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/uv
)

add_library(webp STATIC IMPORTED GLOBAL)
set_target_properties(webp PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libwebp.a
)

add_library(websockets STATIC IMPORTED GLOBAL)
set_target_properties(websockets PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libwebsockets.a
)

add_library(z STATIC IMPORTED GLOBAL)
set_target_properties(z PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libz.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/zlib
)

add_library(android_platform STATIC
  ${CMAKE_ANDROID_NDK}/sources/android/cpufeatures/cpu-features.c
)
target_include_directories(android_platform PUBLIC
  ${CMAKE_ANDROID_NDK}/sources/android/cpufeatures
  ${CMAKE_ANDROID_NDK}/sources/android/native_app_glue
)

## Settings from  ${CMAKE_ANDROID_NDK}/sources/android/native_app_glue/Android.mk
# set_property(TARGET android_platform APPEND_STRING PROPERTY LINK_FLAGS "-u ANativeActivity_onCreate")
# target_link_libraries(android_platform PUBLIC
#   android log dl
# )

set(se_libs_name)

if(USE_SE_V8)

    add_library(v8_monolith STATIC IMPORTED GLOBAL)
    set_target_properties(v8_monolith PROPERTIES
      IMPORTED_LOCATION ${platform_spec_path}/v8/libv8_monolith.a
      INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/v8
    )

    if(ANDROID_ABI STREQUAL "arm64-v8a" OR ANDROID_ABI STREQUAL "x86_64")
      set_property(TARGET v8_monolith
        APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS V8_COMPRESS_POINTERS
      )
    endif()

    set(se_libs_name v8_monolith)
    set(se_libs_include ${platform_spec_path}/include/v8)
endif()

if(USE_WEBSOCKET_SERVER)
    list(APPEND CC_EXTERNAL_LIBS
        websockets
        ssl
        crypto
    )
endif()

############################# glslang #############################
set(glslang_libs_name glslang glslang-default-resource-limits MachineIndependent OGLCompiler OSDependent SPIRV SPIRV-Tools-opt SPIRV-Tools GenericCodeGen)
foreach(lib IN LISTS glslang_libs_name)
  add_library(${lib} STATIC IMPORTED GLOBAL)
  set_target_properties(${lib} PROPERTIES
    IMPORTED_LOCATION ${platform_spec_path}/glslang/lib${lib}.a
    # INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/glslang
  )
endforeach()

############################# TBB #############################

add_library(tbb STATIC IMPORTED GLOBAL)
set_target_properties(tbb PROPERTIES
  IMPORTED_LOCATION ${platform_spec_path}/libtbb_static.a
)
set(tbb_libs_name tbb)

if(USE_PHYSICS_PHYSX)
  set(PhysXSDK PhysXCooking PhysXCharacterKinematic PhysXVehicle PhysXExtensions PhysX PhysXPvdSDK PhysXCommon PhysXFoundation)
  foreach(PX IN LISTS PhysXSDK)
    add_library(${PX} STATIC IMPORTED GLOBAL)
    set_target_properties(${PX} PROPERTIES
      IMPORTED_LOCATION ${platform_spec_path}/PhysX/lib${PX}_static.a
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
    uv
    android_platform
    ${PhysXSDK}
)

if(USE_JOB_SYSTEM_TBB OR CC_USE_VULKAN) ## VKDevice.cpp use tbb_allocator.h
  list(APPEND CC_EXTERNAL_LIBS
    ${tbb_libs_name}
  )
endif()

if(CC_USE_VULKAN)
  list(APPEND CC_EXTERNAL_LIBS
    ${glslang_libs_name}
  )
endif()

set(ZLIB z)
if(NOT USE_MODULES)
  list(APPEND CC_EXTERNAL_LIBS ${ZLIB} 
   ${se_libs_name}
   )
endif()



list(APPEND CC_EXTERNAL_INCLUDES
  ${platform_spec_path}/include
  ${CMAKE_ANDROID_NDK}/sources/android/native_app_glue
)
