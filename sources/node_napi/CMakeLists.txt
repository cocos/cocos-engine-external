cmake_minimum_required(VERSION 3.10)

project(node_napi CXX)

add_library(node_napi 
js_native_api.h
js_native_api_types.h
js_native_api_v8.cc
js_native_api_v8.h
js_native_api_v8_internals.h
js_native_api_util.h
)
target_include_directories(node_napi PUBLIC ${CMAKE_CURRENT_LIST_DIR})

target_compile_definitions(node_napi
PUBLIC
    NODE_WANT_INTERNALS=1
    NODE_MODULE_VERSION=93
    NAPI_VERSION=8
)

target_link_libraries(node_napi PUBLIC ${se_libs_name})
