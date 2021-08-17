
add_library(z STATIC IMPORTED GLOBAL)
set_target_properties(z PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libz.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/zlib
)

set(se_libs_name)

############################# glslang #############################

# add_library(GenericCodeGen STATIC IMPORTED GLOBAL)
# set_target_properties(GenericCodeGen PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libGenericCodeGen.a
# )

# # add_library(glslang STATIC IMPORTED GLOBAL)
# # set_target_properties(glslang PROPERTIES
# #   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libglslang.a
# # )

# add_library(glslang-default-resource-limits STATIC IMPORTED GLOBAL)
# set_target_properties(glslang-default-resource-limits PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libglslang-default-resource-limits.a
# )

# add_library(MachineIndependent STATIC IMPORTED GLOBAL)
# set_target_properties(MachineIndependent PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libMachineIndependent.a
# )

# add_library(OGLCompiler STATIC IMPORTED GLOBAL)
# set_target_properties(OGLCompiler PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libOGLCompiler.a
# )

# add_library(OSDependent STATIC IMPORTED GLOBAL)
# set_target_properties(OSDependent PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libOSDependent.a
# )

# add_library(SPIRV STATIC IMPORTED GLOBAL)
# set_target_properties(SPIRV PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libSPIRV.a
# )

# add_library(SPIRV-Tools STATIC IMPORTED GLOBAL)
# set_target_properties(SPIRV-Tools PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libSPIRV-Tools.a
# )

# add_library(SPIRV-Tools-opt STATIC IMPORTED GLOBAL)
# set_target_properties(SPIRV-Tools-opt PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libSPIRV-Tools-opt.a
# )

# add_library(SPVRemapper STATIC IMPORTED GLOBAL)
# set_target_properties(SPVRemapper PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/glslang/libSPVRemapper.a
# )

# set(glslang_libs_name glslang glslang-default-resource-limits MachineIndependent OGLCompiler OSDependent SPIRV SPIRV-Tools SPIRV-Tools-opt SPVRemapper GenericCodeGen)

############################# SPIRV-Cross #############################

# add_library(spirv-cross-core STATIC IMPORTED GLOBAL)
# set_target_properties(spirv-cross-core PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libspirv-cross-core.a
# )
# add_library(spirv-cross-msl STATIC IMPORTED GLOBAL)
# set_target_properties(spirv-cross-msl PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libspirv-cross-msl.a
# )
# add_library(spirv-cross-glsl STATIC IMPORTED GLOBAL)
# set_target_properties(spirv-cross-glsl PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libspirv-cross-glsl.a
# )
# set(spirv-cross_libs_name spirv-cross-core spirv-cross-glsl spirv-cross-msl)

############################# TBB #############################

# add_library(tbb STATIC IMPORTED GLOBAL)
# set_target_properties(tbb PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libtbb_static.a
# )
# add_library(tbbmalloc STATIC IMPORTED GLOBAL)
# set_target_properties(tbbmalloc PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libtbbmalloc_static.a
# )
# add_library(tbbmalloc_proxy STATIC IMPORTED GLOBAL)
# set_target_properties(tbbmalloc_proxy PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libtbbmalloc_proxy_static.a
# )
# set(tbb_libs_name tbb tbbmalloc tbbmalloc_proxy)

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

list(APPEND CC_EXTERNAL_LIBS
    #freetype
    #jpeg
    #png
    #webp
    #curl
    #crypto
    #ssl
    #${glslang_libs_name}
    #${spirv-cross_libs_name}
    #${tbb_libs_name}
    ${PhysXSDK}
)

set(ZLIB z)
if(NOT USE_MODULES)
  list(APPEND CC_EXTERNAL_LIBS ${ZLIB} ${se_libs_name})
endif()


list(APPEND CC_EXTERNAL_INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}/include
)
