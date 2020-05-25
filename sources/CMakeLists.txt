


set(CC_EXTERNAL_SROUCES
  ${CMAKE_CURRENT_LIST_DIR}/tinyxml2/tinyxml2.cpp
  ${CMAKE_CURRENT_LIST_DIR}/tinyxml2/tinyxml2.h

  ${CMAKE_CURRENT_LIST_DIR}/xxtea/xxtea.cpp
  ${CMAKE_CURRENT_LIST_DIR}/xxtea/xxtea.h

  ${CMAKE_CURRENT_LIST_DIR}/unzip/crypt.h
  ${CMAKE_CURRENT_LIST_DIR}/unzip/ioapi.cpp
  ${CMAKE_CURRENT_LIST_DIR}/unzip/ioapi.h
  ${CMAKE_CURRENT_LIST_DIR}/unzip/ioapi_mem.cpp
  ${CMAKE_CURRENT_LIST_DIR}/unzip/ioapi_mem.h
  ${CMAKE_CURRENT_LIST_DIR}/unzip/unzip.cpp
  ${CMAKE_CURRENT_LIST_DIR}/unzip/unzip.h

  
  ${CMAKE_CURRENT_LIST_DIR}/ConvertUTF/ConvertUTF.c
  ${CMAKE_CURRENT_LIST_DIR}/ConvertUTF/ConvertUTF.h
  ${CMAKE_CURRENT_LIST_DIR}/ConvertUTF/ConvertUTFWrapper.cpp

  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommy.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommy.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyalloc.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyalloc.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyarray.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyarray.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyarrayblk.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyarrayblk.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyarrayblkof.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyarrayblkof.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyarrayof.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyarrayof.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommychain.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyhash.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyhash.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyhashdyn.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyhashdyn.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyhashlin.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyhashlin.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyhashtbl.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommyhashtbl.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommylist.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommylist.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommytree.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommytree.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommytrie.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommytrie.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommytrieinp.c
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommytrieinp.h
  ${CMAKE_CURRENT_LIST_DIR}/tommyds/tommytypes.h
)

if(ANDROID)

  include(${CMAKE_CURRENT_LIST_DIR}/pvmp3dec/CMakeLists.txt)
  include(${CMAKE_CURRENT_LIST_DIR}/tremolo/CMakeLists.txt)

  list(APPEND CC_EXTERNAL_LIBS 
    pvmp3dec
    vorbisidec
  )
  
elseif(WINDOWS)
  set_source_files_properties(${CMAKE_CURRENT_LIST_DIR}/ConvertUTF/ConvertUTF.c PROPERTIES
    LANGUAGE C
  )
elseif(APPLE)
  if(USE_SOCKET)
      include(${CMAKE_CURRENT_LIST_DIR}/SocketRocket/CMakeLists.txt)
      list(APPEND CC_EXTERNAL_LIBS
          SocketRocket
      )
  endif()
endif()

list(APPEND CC_EXTERNAL_INCLUDES
 ${CMAKE_CURRENT_LIST_DIR}
)
