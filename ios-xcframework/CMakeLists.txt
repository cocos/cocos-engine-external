if(CMAKE_GENERATOR STREQUAL "Xcode")
  # Let Xcode resolve the correct xcframework slice via "Link Binary With Libraries".
  set(CMAKE_XCODE_LINK_BUILD_PHASE_MODE KNOWN_LOCATION)
endif()

function(import_xcframework target xcframework_relpath)
  add_library(${target} INTERFACE IMPORTED GLOBAL)
  target_link_libraries(${target} INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/libs/${xcframework_relpath}"
  )
endfunction()

import_xcframework(crypto libcrypto.xcframework)

if (USE_DEBUG_RENDERER)
  import_xcframework(freetype libfreetype.xcframework)
  set_target_properties(freetype PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include/freetype"
  )
endif()

import_xcframework(jpeg libjpeg.xcframework)
import_xcframework(png libpng.xcframework)
import_xcframework(ssl libssl.xcframework)
import_xcframework(uv libuv.xcframework)
set_target_properties(uv PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include/uv"
)

import_xcframework(webp libwebp.xcframework)
import_xcframework(websockets libwebsockets.xcframework)

add_library(v8_monolith INTERFACE IMPORTED GLOBAL)
set(V8_COMPILE_FLAGS
  V8_TYPED_ARRAY_MAX_SIZE_IN_HEAP=64
  ENABLE_MINOR_MC
  ENABLE_HANDLE_ZAPPING
  V8_ATOMIC_OBJECT_FIELD_WRITES
  V8_ATOMIC_MARKING_STATE
  V8_ENABLE_LAZY_SOURCE_POSITIONS
  V8_SHARED_RO_HEAP
  V8_WIN64_UNWINDING_INFO
  V8_ENABLE_REGEXP_INTERPRETER_THREADED_DISPATCH
  V8_SNAPSHOT_COMPRESSION
  V8_ENABLE_SYSTEM_INSTRUMENTATION
  V8_ENABLE_WEBASSEMBLY
  V8_DEPRECATION_WARNINGS
  V8_IMMINENT_DEPRECATION_WARNINGS
  CPPGC_CAGED_HEAP
  V8_TARGET_ARCH_ARM64
  V8_HAVE_TARGET_OS
  V8_TARGET_OS_IOS
  DISABLE_UNTRUSTED_CODE_MITIGATIONS
)
target_link_libraries(v8_monolith INTERFACE
  "${CMAKE_CURRENT_LIST_DIR}/libs/libv8_monolith.xcframework"
)
set_target_properties(v8_monolith PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/include/v8"
)
set_property(TARGET v8_monolith APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS ${V8_COMPILE_FLAGS})

set(se_libs_name)

if(USE_SE_V8 OR USE_SE_JSVM)
  list(APPEND se_libs_name
    v8_monolith
    uv
  )
endif()

if(USE_SE_JSC)
  find_library(JAVASCRIPT_CORE_LIBRARY JavaScriptCore REQUIRED)
  set(se_libs_name ${JAVASCRIPT_CORE_LIBRARY})
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

import_xcframework(GenericCodeGen glslang/libGenericCodeGen.xcframework)
import_xcframework(glslang glslang/libglslang.xcframework)
import_xcframework(glslang-default-resource-limits glslang/libglslang-default-resource-limits.xcframework)
import_xcframework(MachineIndependent glslang/libMachineIndependent.xcframework)
import_xcframework(OGLCompiler glslang/libOGLCompiler.xcframework)
import_xcframework(OSDependent glslang/libOSDependent.xcframework)
import_xcframework(SPIRV glslang/libSPIRV.xcframework)
import_xcframework(SPIRV-Tools glslang/libSPIRV-Tools.xcframework)
import_xcframework(SPIRV-Tools-opt glslang/libSPIRV-Tools-opt.xcframework)

set(glslang_libs_name
  glslang
  glslang-default-resource-limits
  MachineIndependent
  OGLCompiler
  OSDependent
  SPIRV
  SPIRV-Tools-opt
  SPIRV-Tools
  GenericCodeGen
)

############################# SPIRV-Cross #############################

import_xcframework(spirv-cross-core spirv-cross/libspirv-cross-core.xcframework)
import_xcframework(spirv-cross-msl spirv-cross/libspirv-cross-msl.xcframework)
import_xcframework(spirv-cross-glsl spirv-cross/libspirv-cross-glsl.xcframework)
set(spirv-cross_libs_name spirv-cross-core spirv-cross-glsl spirv-cross-msl)

############################# TBB #############################

import_xcframework(tbb libtbb_static.xcframework)
set(tbb_libs_name tbb)

if(USE_PHYSICS_PHYSX)
  set(PhysXSDK PhysX PhysXCommon PhysXFoundation PhysXExtensions PhysXCooking PhysXCharacterKinematic PhysXVehicle PhysXPvdSDK)
  foreach(PX IN LISTS PhysXSDK)
    add_library(${PX} INTERFACE IMPORTED GLOBAL)
    target_link_libraries(${PX} INTERFACE
      "${CMAKE_CURRENT_LIST_DIR}/libs/PhysX/lib${PX}_static_64.xcframework"
    )
  endforeach()
else()
  set(PhysXSDK)
endif()

list(APPEND CC_EXTERNAL_INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}/include
)

if (USE_DEBUG_RENDERER)
  list(APPEND CC_EXTERNAL_LIBS freetype)
endif()

list(APPEND CC_EXTERNAL_LIBS
  jpeg
  png
  webp
  ${glslang_libs_name}
  ${spirv-cross_libs_name}
  ${tbb_libs_name}
  ${PhysXSDK}
)

set(ZLIB z)
if(NOT USE_MODULES)
  list(APPEND CC_EXTERNAL_LIBS ${se_libs_name})
endif()
