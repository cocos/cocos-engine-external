message(STATUS "Add dependence target: tommyds...")

# Define target name
set(TARGET_NAME tommyds)

set(INCLUDE_FILES 
  ${COCOS_EXTERNAL_PATH}/tommyds
)

include_directories( ${INCLUDE_FILES} )

set (HEADER_FILES
	tommychain.h
	tommyhash.h
	tommyhashdyn.h
	tommylist.h
	tommytypes.h
)

set (SOURCE_FILES
    tommyhash.c
    tommyhashdyn.c
    tommylist.c
)

add_library(${TARGET_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

if(MSVC)
	set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS "/wd4018 /wd4244 /wd4819 /wd4996")
endif()

if(NOT COCOS_PLATFORM_IOS)
	set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${TARGET_NAME}_d)
endif()
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER External)

message(STATUS "${TARGET_NAME} Configuration completed.")
