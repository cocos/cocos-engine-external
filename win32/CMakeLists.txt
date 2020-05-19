add_library(dbghelp SHARED IMPORTED GLOBAL)

set_target_properties(dbghelp PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/dbghelp.dll
)

add_library(freetype STATIC IMPORTED GLOBAL)

set_target_properties(freetype PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/freetype.lib
)

add_library(glew32 SHARED IMPORTED GLOBAL)

set_target_properties(glew32 PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glew32.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/glew32.lib
)

add_library(iconv SHARED IMPORTED GLOBAL)

set_target_properties(iconv PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/iconv.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libiconv.lib
)


add_library(crypto STATIC IMPORTED GLOBAL)

set_target_properties(crypto PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libcrypto.lib
  #IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libcrypto.lib
  #IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libcrypto-1_1.dll
)


add_library(curl SHARED IMPORTED GLOBAL)

set_target_properties(curl PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libcurl.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libcurl.lib
)

add_library(jpeg STATIC IMPORTED GLOBAL)

set_target_properties(jpeg PROPERTIES
  #IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libjpeg.lib
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libjpeg-2015.lib
)

add_library(mpg123 SHARED IMPORTED GLOBAL)

set_target_properties(mpg123 PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libmpg123.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libmpg123.lib
)

add_library(ogg SHARED IMPORTED GLOBAL)

set_target_properties(ogg PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libogg.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libogg.lib
)

add_library(png STATIC IMPORTED GLOBAL)

set_target_properties(png PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libpng-2015.lib
  #IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libpng.lib
)


add_library(ssl STATIC IMPORTED GLOBAL)

set_target_properties(ssl PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libssl.lib
  #IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libssl-1_1.dll
)

# add_library(tiff-2015 STATIC IMPORTED GLOBAL)

# set_target_properties(tiff-2015 PROPERTIES
#   IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libtiff-2015.lib
# )

add_library(tiff SHARED IMPORTED GLOBAL)

set_target_properties(tiff PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libtiff.dll
  #IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libtiff.lib
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libtiff-2015.lib
)

add_library(uv STATIC IMPORTED GLOBAL)

set_target_properties(uv PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libuv.lib
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/uv
)


add_library(vorbis SHARED IMPORTED GLOBAL)

set_target_properties(vorbis PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libvorbis.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libvorbis.lib
)

add_library(vorbisfile SHARED IMPORTED GLOBAL)

set_target_properties(vorbisfile PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libvorbisfile.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libvorbisfile.lib
)

add_library(webp STATIC IMPORTED GLOBAL)

set_target_properties(webp PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libwebp.lib
)

add_library(zlib STATIC IMPORTED GLOBAL)

set_target_properties(zlib PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libzlib.lib
  #IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/zlib1.dll
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/zlib
)

add_library(websockets SHARED IMPORTED GLOBAL)

set_target_properties(websockets PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/websockets.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/websockets.lib
)


add_library(OpenAL32 SHARED IMPORTED GLOBAL)

set_target_properties(OpenAL32 PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/OpenAL32.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/OpenAL32.lib
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/OpenalSoft
)

add_library(sqlite3 SHARED IMPORTED GLOBAL)

set_target_properties(sqlite3 PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/sqlite3.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/sqlite3.lib
)


add_library(SDL2 SHARED IMPORTED GLOBAL)
set_target_properties(SDL2 PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/SDL2.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/SDL2.lib
)

add_library(EGL SHARED IMPORTED GLOBAL)
set_target_properties(EGL PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libEGL.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libEGL.lib
)

add_library(GLESv2 SHARED IMPORTED GLOBAL)
set_target_properties(GLESv2 PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libGLESv2.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libGLESv2.lib
)


add_library(GLES_CM SHARED IMPORTED GLOBAL)
set_target_properties(GLES_CM PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libGLES_CM.dll
  IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/libGLES_CM.lib
)
set(se_libs_name)

if(USE_SE_V8)

    add_library(v8 SHARED IMPORTED GLOBAL)
    set_target_properties(v8 PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/v8.dll
      IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/v8.dll.lib
    )

    add_library(v8_libbase SHARED IMPORTED GLOBAL)
    set_target_properties(v8_libbase PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/v8_libbase.dll
      IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/v8_libbase.dll.lib
    )

    add_library(v8_libplatform SHARED IMPORTED GLOBAL)
    set_target_properties(v8_libplatform PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/v8_libplatform.dll
      IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/v8_libplatform.dll.lib
    )

    target_link_libraries(v8 INTERFACE v8_libbase v8_libplatform)

    set_target_properties(v8 PROPERTIES 
      INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/v8
      INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/v8
    )

    set(se_libs_name v8)
    
endif()


if(USE_SE_SM)
    add_library(mozglue STATIC IMPORTED GLOBAL)

    set_target_properties(mozglue PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/mozglue.lib
      # IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/Debug/mozglue.lib
    )

    add_library(mozjs SHARED IMPORTED GLOBAL)

    set_target_properties(mozjs PROPERTIES
      IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/Debug/mozjs-52.dll
      IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/Debug/mozjs-52.lib
      #IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/mozjs-52.dll
      #IMPORTED_IMPLIB ${CMAKE_CURRENT_LIST_DIR}/libs/mozjs-52.lib
      INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/spidermonkey
    )

    # add_library(nspr4 SHARED IMPORTED GLOBAL)
    # set_target_properties(nspr4 PROPERTIES
    #   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/nspr4.dll
    # )

    set(se_libs_name mozglue mozjs)

endif()

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
set(GLSLANG_SUFFIX "d")
endif()

add_library(glslang STATIC IMPORTED GLOBAL)
set_target_properties(glslang PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/glslang${GLSLANG_SUFFIX}.lib
)
add_library(HLSL STATIC IMPORTED GLOBAL)
set_target_properties(HLSL PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/HLSL${GLSLANG_SUFFIX}.lib
)
add_library(OGLCompiler STATIC IMPORTED GLOBAL)
set_target_properties(OGLCompiler PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/OGLCompiler${GLSLANG_SUFFIX}.lib
)
add_library(OSDependent STATIC IMPORTED GLOBAL)
set_target_properties(OSDependent PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/OSDependent${GLSLANG_SUFFIX}.lib
)
add_library(SPIRV STATIC IMPORTED GLOBAL)
set_target_properties(SPIRV PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/SPIRV${GLSLANG_SUFFIX}.lib
)
add_library(SPIRVRemapper STATIC IMPORTED GLOBAL)
set_target_properties(SPIRVRemapper PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/SPIRVRemapper${GLSLANG_SUFFIX}.lib
)
list(APPEND CC_EXTERNAL_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include/glslang)
set(glslang_libs_name glslang OGLCompiler OSDependent SPIRV)

list(APPEND CC_EXTERNAL_LIBS
    freetype
    glew32
    iconv
    crypto
    curl
    jpeg
    mpg123
    ogg
    png
    ssl
    tiff
    uv
    vorbis
    vorbisfile
    webp
    OpenAL32
    sqlite3
    ${se_libs_name}
    zlib
    websockets
    SDL2
    GLESv2
    EGL
    GLES_CM
    ${glslang_libs_name}
)

list(APPEND CC_EXTERNAL_INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}/include
)
