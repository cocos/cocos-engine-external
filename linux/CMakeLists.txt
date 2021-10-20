set(linux_lib_dir ${platform_spec_path}/lib)
MESSAGE(STATUS "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx ${platform_spec_path}")
add_library(uv STATIC IMPORTED GLOBAL)
set_target_properties(uv PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libuv_a.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/libuv
)

add_library(mpg123 SHARED IMPORTED GLOBAL)
set_target_properties(mpg123 PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libmpg123.so
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/mpg123
)

add_library(ogg STATIC IMPORTED GLOBAL)
set_target_properties(ogg PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libogg.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/ogg
)

add_library(vorbisfile STATIC IMPORTED GLOBAL)
set_target_properties(vorbisfile PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libvorbisfile.a
)

add_library(vorbis STATIC IMPORTED GLOBAL)
set_target_properties(vorbis PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libvorbis.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/vorbis
)

add_library(libz SHARED IMPORTED GLOBAL)
set_target_properties(libz PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libz.so.1.2.11
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/libz
)

add_library(sqlite3 SHARED IMPORTED GLOBAL)
set_target_properties(sqlite3 PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libsqlite3.so.0.8.6
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/sqlite
)

add_library(v8 STATIC IMPORTED GLOBAL)
set_target_properties(v8 PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libv8_monolith.a
)

add_library(openal SHARED IMPORTED GLOBAL)
set_target_properties(openal PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libopenal.so.1.21.1
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/openal-soft
)

add_library(jpeg STATIC IMPORTED GLOBAL)
set_target_properties(jpeg PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libjpeg.a
)

add_library(png STATIC IMPORTED GLOBAL)
set_target_properties(png PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libpng16.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/libpng
)

add_library(ssl STATIC IMPORTED GLOBAL)
set_target_properties(ssl PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libssl.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/openssl
)

add_library(crypto STATIC IMPORTED GLOBAL)
set_target_properties(crypto PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libcrypto.a
)

add_library(websockets STATIC IMPORTED GLOBAL)
set_target_properties(websockets PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libwebsockets.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/libwebsockets
)

add_library(curl SHARED IMPORTED GLOBAL)
set_target_properties(curl PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libcurl.so
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/curl
)

add_library(webp STATIC IMPORTED GLOBAL)
set_target_properties(webp PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libwebp.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/libwebp
)

add_library(tbb STATIC IMPORTED GLOBAL)
set_target_properties(tbb PROPERTIES
  IMPORTED_LOCATION ${linux_lib_dir}/libtbb_static.a
  INTERFACE_INCLUDE_DIRECTORIES ${platform_spec_path}/include/tbb
)

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
    ssl
    crypto
    curl
    webp
    tbb
)
