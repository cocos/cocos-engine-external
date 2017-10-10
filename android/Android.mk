LOCAL_PATH := $(call my-dir)
#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_zlib_static
LOCAL_MODULE_FILENAME := zlib
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libz.a

include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_freetype2_static
LOCAL_MODULE_FILENAME := freetype2
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libfreetype.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(TARGET_ARCH_ABI)/include/freetype

include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_jpeg_static
LOCAL_MODULE_FILENAME := jpeg
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libjpeg.a

include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_png_static
LOCAL_MODULE_FILENAME := png
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libpng.a

include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_chipmunk_static
LOCAL_MODULE_FILENAME := chipmunk
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libchipmunk.a

include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_tiff_static
LOCAL_MODULE_FILENAME := tiff
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libtiff.a

include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_webp_static
LOCAL_MODULE_FILENAME := webp
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libwebp.a

LOCAL_WHOLE_STATIC_LIBRARIES := cpufeatures

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
   LOCAL_CFLAGS := -DHAVE_NEON=1
endif

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos_crypto_static
LOCAL_MODULE_FILENAME := crypto
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libcrypto.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(TARGET_ARCH_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := cocos_ssl_static
LOCAL_MODULE_FILENAME := ssl
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libssl.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(TARGET_ARCH_ABI)/include
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := websockets_static
LOCAL_MODULE_FILENAME := libwebsockets_static
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libwebsockets.a

LOCAL_CPPFLAGS := -D__STDC_LIMIT_MACROS=1
LOCAL_EXPORT_CPPFLAGS := -D__STDC_LIMIT_MACROS=1

include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := cocos_mozglue_static
LOCAL_MODULE_FILENAME := mozglue
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libmozglue.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := spidermonkey_static
LOCAL_MODULE_FILENAME := js_static
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libjs_static.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(TARGET_ARCH_ABI)/include/spidermonkey

LOCAL_CPPFLAGS := -D__STDC_LIMIT_MACROS=1 -Wno-invalid-offsetof
LOCAL_EXPORT_CPPFLAGS := -D__STDC_LIMIT_MACROS=1 -Wno-invalid-offsetof
LOCAL_STATIC_LIBRARIES += cocos_mozglue_static
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_builtins_generators
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_builtins_generators.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_builtins_setup
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_builtins_setup.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_libbase
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_libbase.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_libplatform
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_libplatform.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_libsampler
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_libsampler.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_nosnapshot
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_nosnapshot.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)
LOCAL_MODULE := v8_inspector
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libinspector.a
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := v8_static
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libv8_base.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(TARGET_ARCH_ABI)/include/v8

LOCAL_WHOLE_STATIC_LIBRARIES += v8_builtins_generators v8_builtins_setup v8_libbase v8_libplatform v8_libsampler v8_nosnapshot v8_inspector

include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := uv_static
LOCAL_MODULE_FILENAME := libuv
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libuv.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(TARGET_ARCH_ABI)/include/uv
include $(PREBUILT_STATIC_LIBRARY)

#======================================
include $(CLEAR_VARS)

LOCAL_MODULE := PluginProtocolStatic
LOCAL_MODULE_FILENAME := libPluginProtocolStatic
LOCAL_SRC_FILES := $(TARGET_ARCH_ABI)/libPluginProtocolStatic.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/$(TARGET_ARCH_ABI)/include/anysdk
LOCAL_EXPORT_LDLIBS += -llog
LOCAL_EXPORT_LDLIBS += -lz

include $(PREBUILT_STATIC_LIBRARY)
#======================================
#$(call import-module,android/cpufeatures)
