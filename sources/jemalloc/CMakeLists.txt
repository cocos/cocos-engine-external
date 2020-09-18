message(STATUS "Add dependence target: jemalloc ...")

# Define target name
set(TARGET_NAME jemalloc)

if(MSVC)
	set(INCLUDE_FILES ${COCOS_EXTERNAL_PATH}/jemalloc/include-win ${COCOS_EXTERNAL_PATH}/jemalloc/include-win/msvc_compat)
else()
	set(INCLUDE_FILES ${COCOS_EXTERNAL_PATH}/jemalloc/include-linux)
endif()

include_directories( ${INCLUDE_FILES} )

set (SOURCE_FILES
    src/je_arena.c
    src/je_atomic.c
    src/je_base.c
    src/je_bitmap.c
    src/je_chunk.c
    src/je_chunk_dss.c
    src/je_chunk_mmap.c
    src/je_ckh.c
    src/je_ctl.c
    src/je_extent.c
    src/je_hash.c
    src/je_huge.c
    src/je_jemalloc.c
    src/je_mb.c
    src/je_mutex.c
    src/je_nstime.c
    src/je_pages.c
    src/je_prng.c
    src/je_prof.c
    src/je_quarantine.c
    src/je_rtree.c
    src/je_spin.c
    src/je_stats.c
    src/je_tcache.c
    src/je_ticker.c
    src/je_tsd.c
    src/je_util.c
    src/je_witness.c
)

add_library(${TARGET_NAME} STATIC ${SOURCE_FILES})

if(MSVC)
	set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_FLAGS "/wd4996")
endif()

if(NOT COCOS_PLATFORM_IOS)
	set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME_DEBUG jemalloc_d)
endif()

set_target_properties(${TARGET_NAME} PROPERTIES FOLDER External)

message(STATUS "${TARGET_NAME} Configuration completed.")
