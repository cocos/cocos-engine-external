
add_library(ConvertUTF 
    ${CMAKE_CURRENT_LIST_DIR}/ConvertUTF.h
    ${CMAKE_CURRENT_LIST_DIR}/ConvertUTF.c
    ${CMAKE_CURRENT_LIST_DIR}/ConvertUTFWrapper.cpp
)

target_include_directories(ConvertUTF PUBLIC ${CMAKE_CURRENT_LIST_DIR})