set(ohos_lib_dir ${platform_spec_path}/lib)

add_library(freetype STATIC IMPORTED GLOBAL)
set_target_properties(freetype PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libfreetype.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/freetype
)

add_library(jpeg STATIC IMPORTED GLOBAL)
set_target_properties(jpeg PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libjpeg.a
)

add_library(png STATIC IMPORTED GLOBAL)
set_target_properties(png PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libpng.a
)

add_library(zlib STATIC IMPORTED GLOBAL)
set_target_properties(zlib PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libz.a
)

add_library(openssl STATIC IMPORTED GLOBAL)
set_target_properties(openssl PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libssl.a
)

add_library(crypto STATIC IMPORTED GLOBAL)
set_target_properties(crypto PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libcrypto.a
)

add_library(xz STATIC IMPORTED GLOBAL)
set_target_properties(xz PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/liblzma.a
)

add_library(tiff STATIC IMPORTED GLOBAL)
set_target_properties(tiff PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libtiff.a
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

add_library(nghttp2 STATIC IMPORTED GLOBAL)
set_target_properties(nghttp2 PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libnghttp2.a
)

add_library(zstd STATIC IMPORTED GLOBAL)
set_target_properties(zstd PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libzstd.a
)

add_library(curl STATIC IMPORTED GLOBAL)
set_target_properties(curl PROPERTIES
  IMPORTED_LOCATION ${ohos_lib_dir}/libcurl.a
)

if(CC_USE_SE_V8)
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

############################# PhysX #############################
# if(USE_PHYSICS_PHYSX)
#   set(PhysXSDK PhysXCooking PhysXCharacterKinematic PhysXVehicle PhysXExtensions PhysX PhysXPvdSDK PhysXCommon PhysXFoundation)
#   foreach(PX IN LISTS PhysXSDK)
#     add_library(${PX} STATIC IMPORTED GLOBAL)
#     set_target_properties(${PX} PROPERTIES
#       IMPORTED_LOCATION ${ohos_lib_dir}/PhysX/lib${PX}_static.a
#     )
#   endforeach()
# else()
#   set(PhysXSDK)
# endif()

# add_library(MachineIndependent STATIC IMPORTED GLOBAL)
# set_target_properties(MachineIndependent PROPERTIES
#   IMPORTED_LOCATION ${ohos_lib_dir}/libMachineIndependent.a
# )
# add_library(GenericCodeGen STATIC IMPORTED GLOBAL)
# set_target_properties(GenericCodeGen PROPERTIES
#   IMPORTED_LOCATION ${ohos_lib_dir}/libGenericCodeGen.a
# )
# list(APPEND glslang_libs_name MachineIndependent GenericCodeGen)

############################# TBB #############################
# if(USE_JOB_SYSTEM_TBB)
#   add_library(tbb STATIC IMPORTED GLOBAL)
#   set_target_properties(tbb PROPERTIES
#     IMPORTED_LOCATION ${ohos_lib_dir}/libtbb_static.a
#   )
#   add_library(tbbmalloc STATIC IMPORTED GLOBAL)
#   set_target_properties(tbbmalloc PROPERTIES
#     IMPORTED_LOCATION ${ohos_lib_dir}/libtbbmalloc_static.a
#   )
#   add_library(tbbmalloc_proxy STATIC IMPORTED GLOBAL)
#   set_target_properties(tbbmalloc_proxy PROPERTIES
#     IMPORTED_LOCATION ${ohos_lib_dir}/libtbbmalloc_proxy_static.a
#   )
#   set(tbb_libs_name tbbmalloc_proxy tbbmalloc tbb)
#   list(APPEND CC_EXTERNAL_LIBS
#     ${tbb_libs_name}
#   )
# endif()

list(APPEND CC_EXTERNAL_LIBS
    websockets
    openssl
    png
    zlib
    xz
    tiff
    webp
    crypto
    jpeg
    freetype
    nghttp2
    zstd
    curl
    sqlite3
    # ${PhysXSDK}
    ${glslang_libs_name}
)

list(APPEND CC_EXTERNAL_INCLUDES
  ${platform_spec_path}/include
  ${platform_spec_path}/include/sqlite
  ${platform_spec_path}/include/curl
  ${platform_spec_path}/include/png
  ${platform_spec_path}/include/zlib
  ${platform_spec_path}/include/tiff
  ${platform_spec_path}/include/freetype
  ${platform_spec_path}/include/websockets
  ${platform_spec_path}/include/openssl
  ${platform_spec_path}/include/opengles-api
)

if(CC_USE_SE_V8) 
list(APPEND CC_EXTERNAL_LIBS v8_monolith)
list(APPEND CC_EXTERNAL_INCLUDES ${platform_spec_path}/include/v8)
endif()

#TODO: remove in future version
link_directories(${platform_spec_path}/ext/usr/lib)
include_directories(${platform_spec_path}/ext/usr/include)