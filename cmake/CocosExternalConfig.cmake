
# set friendly platform define
if(IOS)
    set(platform_name ios)
    set(platform_spec_path ios)
elseif(ANDROID)
    set(platform_name android)
    set(platform_spec_path android/${ANDROID_ABI})
elseif(WINDOWS)
    set(platform_name win32)
    set(platform_spec_path win32)
elseif(MACOSX)
    set(platform_name mac)
    set(platform_spec_path mac)
endif()

set(platform_spec_path "${CMAKE_CURRENT_LIST_DIR}/../${platform_spec_path}")
