if(QNX)
set(platform_spec_path ${platform_spec_path}/qnx)
endif()
set(linux_lib_dir ${platform_spec_path}/lib)
MESSAGE(STATUS "${platform_spec_path}")
add_library(uv STATIC IMPORTED GLOBAL)
set_target_properties(uv PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libuv/libuv_a.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/libuv
)

add_library(mpg123 SHARED IMPORTED GLOBAL)
set_target_properties(mpg123 PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/mpg123/libmpg123.so
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/mpg123
)

add_library(ogg STATIC IMPORTED GLOBAL)
set_target_properties(ogg PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/ogg/libogg.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/ogg
)

add_library(vorbisfile STATIC IMPORTED GLOBAL)
set_target_properties(vorbisfile PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/vorbis/libvorbisfile.a
)

add_library(vorbis STATIC IMPORTED GLOBAL)
set_target_properties(vorbis PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/vorbis/libvorbis.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/vorbis
)

add_library(libz SHARED IMPORTED GLOBAL)
set_target_properties(libz PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libz/libz.so.1.2.11
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/libz
)

add_library(sqlite3 SHARED IMPORTED GLOBAL)
set_target_properties(sqlite3 PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/sqlite/libsqlite3.so.0.8.6
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/sqlite
)

add_library(v8 STATIC IMPORTED GLOBAL)
set_target_properties(v8 PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/v8/libv8_monolith.a
)

add_library(openal SHARED IMPORTED GLOBAL)
set_target_properties(openal PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/openal-soft/libopenal.so.1.21.1
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/openal-soft
)

add_library(jpeg STATIC IMPORTED GLOBAL)
set_target_properties(jpeg PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/jpeg/libjpeg.a
)

add_library(png STATIC IMPORTED GLOBAL)
set_target_properties(png PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libpng/libpng16.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/libpng
)

if(QNX)
#not add ssl
else()
add_library(ssl STATIC IMPORTED GLOBAL)
set_target_properties(ssl PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/openssl/libssl.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/openssl
)
add_library(crypto STATIC IMPORTED GLOBAL)
set_target_properties(crypto PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/openssl/libcrypto.a
)
set(optional_libs_name ssl crypto)
endif()

if(QNX)
add_library(cairo SHARED IMPORTED GLOBAL)
set_target_properties(cairo PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/cairo/libcairo.so
)
set(optional_libs_name ${optional_libs_name} cairo)
endif()

add_library(websockets STATIC IMPORTED GLOBAL)
set_target_properties(websockets PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libwebsockets/libwebsockets.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/libwebsockets
)

add_library(curl SHARED IMPORTED GLOBAL)
set_target_properties(curl PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/curl/libcurl.so
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/curl
)

add_library(webp STATIC IMPORTED GLOBAL)
set_target_properties(webp PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libwebp/libwebp.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/libwebp
)

if(QNX)
#not add to qnx
else()
add_library(tbb STATIC IMPORTED GLOBAL)
set_target_properties(tbb PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/tbb/libtbb_static.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/tbb
)
set(optional_libs_name ${optional_libs_name} tbb)
endif()

add_library(sdl2 SHARED IMPORTED GLOBAL)
set_target_properties(sdl2 PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/sdl2/libSDL2.so
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/sdl2
)

#glslang
add_library(libGenericCodeGen STATIC IMPORTED GLOBAL)
set_target_properties(libGenericCodeGen PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/glslang/libGenericCodeGen.a
)
add_library(libglslang STATIC IMPORTED GLOBAL)
set_target_properties(libglslang PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/glslang/libglslang.a
)
add_library(libglslang-default-resource-limits STATIC IMPORTED GLOBAL)
set_target_properties(libglslang-default-resource-limits PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/glslang/libglslang-default-resource-limits.a
)
add_library(libSPIRV STATIC IMPORTED GLOBAL)
set_target_properties(libSPIRV PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/glslang/libSPIRV.a
)
add_library(libMachineIndependent STATIC IMPORTED GLOBAL)
set_target_properties(libMachineIndependent PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/glslang/libMachineIndependent.a
)
add_library(libOGLCompiler STATIC IMPORTED GLOBAL)
set_target_properties(libOGLCompiler PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/glslang/libOGLCompiler.a
)
add_library(libOSDependent STATIC IMPORTED GLOBAL)
set_target_properties(libOSDependent PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/glslang/libOSDependent.a
)

set(glslang_libs_name libMachineIndependent libGenericCodeGen libglslang libglslang-default-resource-limits libSPIRV libOGLCompiler libOSDependent)


list(APPEND CC_EXTERNAL_INCLUDES
  ${platform_spec_path}/include
  ${platform_spec_path}/include/v8
  ${platform_spec_path}/include/uv
)

list(APPEND CC_EXTERNAL_LIBS
    uv
    vorbisfile
    vorbis
    ogg
    libz
    sqlite3
    v8
    openal
    mpg123
    jpeg
    png
    websockets
    crypto
    curl
    webp
    sdl2
    ${optional_libs_name}
    ${glslang_libs_name}
)
