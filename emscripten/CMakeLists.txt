
add_library(z STATIC IMPORTED GLOBAL)
set_target_properties(z PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libz.a
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_LIST_DIR}/include/zlib
)

############################# SPIRV-Cross #############################
# add_library(spirv-cross-core STATIC IMPORTED GLOBAL)
# set_target_properties(spirv-cross-core PROPERTIES
#   IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/libspirv-cross-core.a
#   INTERFACE_INCLUDE_DIRECTORIES "${SPIRV_INCLUDE_DIRS}"
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

#if(USE_PHYSICS_PHYSX)
#  set(PhysXSDK PhysX PhysXCommon PhysXFoundation PhysXExtensions PhysXCooking PhysXCharacterKinematic PhysXVehicle PhysXPvdSDK)
#  foreach(PX IN LISTS PhysXSDK)
#    add_library(${PX} STATIC IMPORTED GLOBAL)
#    set_target_properties(${PX} PROPERTIES
#      IMPORTED_LOCATION ${CMAKE_CURRENT_LIST_DIR}/libs/PhysX/lib${PX}_static_64.a
#    )
#  endforeach()
#else()
#  set(PhysXSDK)
#endif()

list(APPEND CC_EXTERNAL_LIBS
    #freetype
    #jpeg
    #png
    #webp
    #curl
    #crypto
    #ssl
    #${tbb_libs_name}
    #${PhysXSDK}
)

set(ZLIB z)
if(NOT USE_MODULES)
  list(APPEND CC_EXTERNAL_LIBS ${ZLIB})
endif()


list(APPEND CC_EXTERNAL_INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}/include
)
