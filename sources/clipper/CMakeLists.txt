
add_library(clipper 
    ${CMAKE_CURRENT_LIST_DIR}/clipper.hpp
    ${CMAKE_CURRENT_LIST_DIR}/clipper.cpp
)

target_include_directories(clipper PUBLIC ${CMAKE_CURRENT_LIST_DIR})