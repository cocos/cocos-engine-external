
list(APPEND CC_EXTERNAL_PRIVATE_DEFINITIONS BOOST_ALL_NO_LIB)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/container boost/container)

set(BOOST_LIBS
    boost_container
)

foreach(lib ${BOOST_LIBS})
    set_target_properties(${lib} PROPERTIES FOLDER Utils)
    target_compile_definitions(${lib} PUBLIC
        BOOST_UUID_FORCE_AUTO_LINK
    )
endforeach()

list(APPEND CC_EXTERNAL_LIBS ${BOOST_LIBS})
