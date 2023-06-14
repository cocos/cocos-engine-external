
set(ohos_lib_dir ${platform_spec_path}/lib)

add_library(crypto STATIC IMPORTED GLOBAL)
set_target_properties(crypto PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libcrypto.a
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

add_library(ssl STATIC IMPORTED GLOBAL)
set_target_properties(ssl PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libssl.a
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

set(se_libs_name)

if(USE_SE_V8)
    add_library(v8_monolith STATIC IMPORTED GLOBAL)
    set_target_properties(v8_monolith PROPERTIES
      IMPORTED_LOCATION ${ohos_lib_dir}/libv8_monolith.a
    )

    set(OHOS_ARM64_MACROS
        V8_TYPED_ARRAY_MAX_SIZE_IN_HEAP=64
        ENABLE_MINOR_MC
        V8_INTL_SUPPORT
        V8_CONCURRENT_MARKING
        V8_ENABLE_LAZY_SOURCE_POSITIONS
        V8_EMBEDDED_BUILTINS
        V8_WIN64_UNWINDING_INFO
        V8_ENABLE_REGEXP_INTERPRETER_THREADED_DISPATCH
        V8_SNAPSHOT_COMPRESSION
        V8_31BIT_SMIS_ON_64BIT_ARCH
        V8_DEPRECATION_WARNINGS
        V8_IMMINENT_DEPRECATION_WARNINGS
        V8_TARGET_ARCH_ARM64
        V8_HAVE_TARGET_OS
        V8_TARGET_OS_LINUX
        DISABLE_UNTRUSTED_CODE_MITIGATIONS
        V8_COMPRESS_POINTERS
        U_USING_ICU_NAMESPACE=0
        U_ENABLE_DYLOAD=0
        USE_CHROMIUM_ICU=1
        U_STATIC_IMPLEMENTATION
    )

    if(OHOS_ARCH STREQUAL "arm64-v8a")
       set_property(TARGET v8_monolith
         APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS ${OHOS_ARM64_MACROS}
       )
    endif()

    add_library(v8_inspector STATIC IMPORTED GLOBAL)
    set_target_properties(v8_inspector PROPERTIES
      IMPORTED_LOCATION ${ohos_lib_dir}/libinspector.a
      INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/v8
    )

    set(se_libs_name v8_monolith v8_inspector)
endif()

if(USE_SOCKET)
    list(APPEND CC_EXTERNAL_LIBS
        websockets
        ssl
        crypto
    )
endif()

if(USE_SE_V8 AND USE_V8_DEBUGGER)
    list(APPEND CC_EXTERNAL_LIBS
        v8_inspector
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
# Unable to link MachineIndependent with GenericCodeGen
set(glslang_libs_name glslang OGLCompiler OSDependent SPIRV glslang-default-resource-limits)

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
    ${PhysXSDK}
    ${glslang_libs_name}
)

list(APPEND CC_EXTERNAL_LIBS
${se_libs_name}
OpenALSoft
mpg123
)

set(ZLIB z)
if(NOT USE_MODULES)
  list(APPEND CC_EXTERNAL_LIBS ${ZLIB})
endif()

if(USE_V8_DEBUGGER OR USE_WEBSOCKET_SERVER)
  list(APPEND CC_EXTERNAL_LIBS
    uv
  )
endif()

list(APPEND CC_EXTERNAL_INCLUDES
  ${platform_spec_path}/include
  ${platform_spec_path}/include/v8
  ${platform_spec_path}/include/sqlite
  ${platform_spec_path}/include/png16
  # Will conflict with the header file of harmonyos' standard library (error.h).
  # ${platform_spec_path}/include/uv
)

#TODO: remove in future version
link_directories(${platform_spec_path}/ext/usr/lib)
include_directories(${platform_spec_path}/ext/usr/include)
