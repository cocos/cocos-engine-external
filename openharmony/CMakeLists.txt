
set(ohos_lib_dir ${platform_spec_path}/lib)
add_library(mbedcrypto STATIC IMPORTED GLOBAL)
set_target_properties(mbedcrypto PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libmbedcrypto.a
)

add_library(mbedx509 STATIC IMPORTED GLOBAL)
set_target_properties(mbedx509 PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libmbedx509.a
)

add_library(mbedtls STATIC IMPORTED GLOBAL)
set_target_properties(mbedtls PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libmbedtls.a
)

if (USE_DEBUG_RENDERER)
add_library(freetype STATIC IMPORTED GLOBAL)
set_target_properties(freetype PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libfreetype.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/freetype
)
endif()

add_library(jpeg STATIC IMPORTED GLOBAL)
set_target_properties(jpeg PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libjpeg.a
)

add_library(png STATIC IMPORTED GLOBAL)
set_target_properties(png PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libpng16.a
)

add_library(uv STATIC IMPORTED GLOBAL)
set_target_properties(uv PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libuv_a.a
)

add_library(webp STATIC IMPORTED GLOBAL)
set_target_properties(webp PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libwebp.a
)

add_library(websockets STATIC IMPORTED GLOBAL)
set_target_properties(websockets PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libwebsockets.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/websockets
)
add_library(sqlite3 STATIC IMPORTED GLOBAL)
set_target_properties(sqlite3 PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libsqlite3.a
)
add_library(z STATIC IMPORTED GLOBAL)
set_target_properties(z PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libz.a
)

add_library(OpenALSoft SHARED IMPORTED GLOBAL)
set_target_properties(OpenALSoft PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libopenal.a
)

add_library(mpg123 SHARED IMPORTED GLOBAL)
set_target_properties(mpg123 PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libmpg123.a
)

add_library(curl STATIC IMPORTED GLOBAL)
set_target_properties(curl PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libcurl.a
)

# curl needs to link the following libraries.  
list(APPEND CC_EXTERNAL_LIBS
    mbedtls
    mbedcrypto
    mbedx509
)

set(se_libs_name)

if(USE_SE_V8)
    add_library(v8_monolith STATIC IMPORTED GLOBAL)
    set_target_properties(v8_monolith PROPERTIES
      IMPORTED_LOCATION ${ohos_lib_dir}/libv8_monolith.a
      INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/v8
    )

    set(OHOS_ARM64_MACROS
        V8_31BIT_SMIS_ON_64BIT_ARCH
        V8_DEPRECATION_WARNINGS
        V8_IMMINENT_DEPRECATION_WARNINGS
        V8_TARGET_ARCH_ARM64
        V8_HAVE_TARGET_OS
        V8_TARGET_OS_LINUX
        V8_COMPRESS_POINTERS
    )

    if(OHOS_ARCH STREQUAL "arm64-v8a")
       set_property(TARGET v8_monolith
         APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS ${OHOS_ARM64_MACROS}
       )
    endif()

    set(se_libs_name v8_monolith)
endif()

if(USE_SOCKET)
    list(APPEND CC_EXTERNAL_LIBS
        websockets
    )
endif()


add_library(glslang STATIC IMPORTED GLOBAL)
set_target_properties(glslang PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libglslang.a
)
add_library(OGLCompiler STATIC IMPORTED GLOBAL)
set_target_properties(OGLCompiler PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libOGLCompiler.a
)
add_library(OSDependent STATIC IMPORTED GLOBAL)
set_target_properties(OSDependent PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libOSDependent.a
)
add_library(SPIRV STATIC IMPORTED GLOBAL)
set_target_properties(SPIRV PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libSPIRV.a
)
add_library(glslang-default-resource-limits STATIC IMPORTED GLOBAL)
set_target_properties(glslang-default-resource-limits PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libglslang-default-resource-limits.a
)
set(glslang_libs_name glslang OGLCompiler OSDependent SPIRV glslang-default-resource-limits MachineIndependent GenericCodeGen)

if(USE_PHYSICS_PHYSX)
  set(PhysXSDK PhysXCooking PhysXCharacterKinematic PhysXVehicle PhysXExtensions PhysX PhysXPvdSDK PhysXCommon PhysXFoundation)
  foreach(PX IN LISTS PhysXSDK)
    add_library(${PX} STATIC IMPORTED GLOBAL)
    set_target_properties(${PX} PROPERTIES
      IMPORTED_LOCATION ${ohos_lib_dir}/PhysX/lib${PX}_static.a
    )
  endforeach()
else()
  set(PhysXSDK)
endif()

add_library(MachineIndependent STATIC IMPORTED GLOBAL)
set_target_properties(MachineIndependent PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libMachineIndependent.a
)
add_library(GenericCodeGen STATIC IMPORTED GLOBAL)
set_target_properties(GenericCodeGen PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libGenericCodeGen.a
)
list(APPEND glslang_libs_name MachineIndependent GenericCodeGen)


############################# TBB #############################
if(USE_JOB_SYSTEM_TBB)
  add_library(tbb STATIC IMPORTED GLOBAL)
  set_target_properties(tbb PROPERTIES
    IMPORTED_LOCATION ${ohos_lib_dir}/libtbb_static.a
  )
  add_library(tbbmalloc STATIC IMPORTED GLOBAL)
  set_target_properties(tbbmalloc PROPERTIES
    IMPORTED_LOCATION ${ohos_lib_dir}/libtbbmalloc_static.a
  )
  add_library(tbbmalloc_proxy STATIC IMPORTED GLOBAL)
  set_target_properties(tbbmalloc_proxy PROPERTIES
    IMPORTED_LOCATION ${ohos_lib_dir}/libtbbmalloc_proxy_static.a
  )
  set(tbb_libs_name tbbmalloc_proxy tbbmalloc tbb)
  list(APPEND CC_EXTERNAL_LIBS
    ${tbb_libs_name}
  )
endif()

if (USE_DEBUG_RENDERER)
list(APPEND CC_EXTERNAL_LIBS
    freetype
)
endif()

list(APPEND CC_EXTERNAL_LIBS
    jpeg
    png
    sqlite3
    webp
    curl
    ${PhysXSDK}
    ${glslang_libs_name}
)

if(NOT USE_MODULES)
  list(APPEND CC_EXTERNAL_LIBS ${se_libs_name})
endif()

list(APPEND CC_EXTERNAL_INCLUDES
  ${platform_spec_path}/include
  ${platform_spec_path}/include/sqlite
  ${platform_spec_path}/include/png16
  ${platform_spec_path}/include/uv
  ${platform_spec_path}/include/mbedtls_wrapper
)

#TODO: remove in future version
link_directories(${platform_spec_path}/ext/usr/lib)
include_directories(${platform_spec_path}/ext/usr/include)
