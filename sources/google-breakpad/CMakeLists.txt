
add_library(google-breakpad 
    ${CMAKE_CURRENT_LIST_DIR}/src/client/linux/crash_generation/crash_generation_client.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/client/linux/dump_writer_common/thread_info.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/client/linux/dump_writer_common/ucontext_reader.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/client/linux/handler/exception_handler.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/client/linux/handler/minidump_descriptor.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/client/linux/log/log.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/client/linux/microdump_writer/microdump_writer.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/client/linux/minidump_writer/linux_dumper.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/client/linux/minidump_writer/linux_ptrace_dumper.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/client/linux/minidump_writer/minidump_writer.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/client/minidump_file_writer.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/common/android/breakpad_getcontext.S
    ${CMAKE_CURRENT_LIST_DIR}/src/common/md5.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/common/string_conversion.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/common/linux/elfutils.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/common/linux/file_id.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/common/linux/guid_creator.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/common/linux/linux_libc_support.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/common/linux/memory_mapped_file.cc
    ${CMAKE_CURRENT_LIST_DIR}/src/common/linux/safe_readlink.cc
)

target_include_directories(google-breakpad PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/src/common/android/include
)