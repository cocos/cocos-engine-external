

add_library(cjson 
    ${CMAKE_CURRENT_LIST_DIR}/fpconv.h
    ${CMAKE_CURRENT_LIST_DIR}/lua_cjson.h
    ${CMAKE_CURRENT_LIST_DIR}/strbuf.h
    ${CMAKE_CURRENT_LIST_DIR}/lua_cjson.c
    ${CMAKE_CURRENT_LIST_DIR}/fpconv.c
    ${CMAKE_CURRENT_LIST_DIR}/strbuf.c
)

target_include_directories(cjson PUBLIC ${CMAKE_CURRENT_LIST_DIR})