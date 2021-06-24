// OHOS 

#pragma once

#ifndef GL_KHR_debug
    #define GL_KHR_debug 1
typedef void(GL_APIENTRY *GLDEBUGPROCKHR)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
    #define GL_SAMPLER                              0x82E6
    #define GL_DEBUG_OUTPUT_SYNCHRONOUS_KHR         0x8242
    #define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH_KHR 0x8243
    #define GL_DEBUG_CALLBACK_FUNCTION_KHR          0x8244
    #define GL_DEBUG_CALLBACK_USER_PARAM_KHR        0x8245
    #define GL_DEBUG_SOURCE_API_KHR                 0x8246
    #define GL_DEBUG_SOURCE_WINDOW_SYSTEM_KHR       0x8247
    #define GL_DEBUG_SOURCE_SHADER_COMPILER_KHR     0x8248
    #define GL_DEBUG_SOURCE_THIRD_PARTY_KHR         0x8249
    #define GL_DEBUG_SOURCE_APPLICATION_KHR         0x824A
    #define GL_DEBUG_SOURCE_OTHER_KHR               0x824B
    #define GL_DEBUG_TYPE_ERROR_KHR                 0x824C
    #define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_KHR   0x824D
    #define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_KHR    0x824E
    #define GL_DEBUG_TYPE_PORTABILITY_KHR           0x824F
    #define GL_DEBUG_TYPE_PERFORMANCE_KHR           0x8250
    #define GL_DEBUG_TYPE_OTHER_KHR                 0x8251
    #define GL_DEBUG_TYPE_MARKER_KHR                0x8268
    #define GL_DEBUG_TYPE_PUSH_GROUP_KHR            0x8269
    #define GL_DEBUG_TYPE_POP_GROUP_KHR             0x826A
    #define GL_DEBUG_SEVERITY_NOTIFICATION_KHR      0x826B
    #define GL_MAX_DEBUG_GROUP_STACK_DEPTH_KHR      0x826C
    #define GL_DEBUG_GROUP_STACK_DEPTH_KHR          0x826D
    #define GL_BUFFER_KHR                           0x82E0
    #define GL_SHADER_KHR                           0x82E1
    #define GL_PROGRAM_KHR                          0x82E2
    #define GL_VERTEX_ARRAY_KHR                     0x8074
    #define GL_QUERY_KHR                            0x82E3
    #define GL_PROGRAM_PIPELINE_KHR                 0x82E4
    #define GL_SAMPLER_KHR                          0x82E6
    #define GL_MAX_LABEL_LENGTH_KHR                 0x82E8
    #define GL_MAX_DEBUG_MESSAGE_LENGTH_KHR         0x9143
    #define GL_MAX_DEBUG_LOGGED_MESSAGES_KHR        0x9144
    #define GL_DEBUG_LOGGED_MESSAGES_KHR            0x9145
    #define GL_DEBUG_SEVERITY_HIGH_KHR              0x9146
    #define GL_DEBUG_SEVERITY_MEDIUM_KHR            0x9147
    #define GL_DEBUG_SEVERITY_LOW_KHR               0x9148
    #define GL_DEBUG_OUTPUT_KHR                     0x92E0
    #define GL_CONTEXT_FLAG_DEBUG_BIT_KHR           0x00000002
    #define GL_STACK_OVERFLOW_KHR                   0x0503
    #define GL_STACK_UNDERFLOW_KHR                  0x0504
typedef void(GL_APIENTRYP PFNGLDEBUGMESSAGECONTROLKHRPROC)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
typedef void(GL_APIENTRYP PFNGLDEBUGMESSAGEINSERTKHRPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
typedef void(GL_APIENTRYP PFNGLDEBUGMESSAGECALLBACKKHRPROC)(GLDEBUGPROCKHR callback, const void *userParam);
typedef GLuint(GL_APIENTRYP PFNGLGETDEBUGMESSAGELOGKHRPROC)(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
typedef void(GL_APIENTRYP PFNGLPUSHDEBUGGROUPKHRPROC)(GLenum source, GLuint id, GLsizei length, const GLchar *message);
typedef void(GL_APIENTRYP PFNGLPOPDEBUGGROUPKHRPROC)(void);
typedef void(GL_APIENTRYP PFNGLOBJECTLABELKHRPROC)(GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
typedef void(GL_APIENTRYP PFNGLGETOBJECTLABELKHRPROC)(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void(GL_APIENTRYP PFNGLOBJECTPTRLABELKHRPROC)(const void *ptr, GLsizei length, const GLchar *label);
typedef void(GL_APIENTRYP PFNGLGETOBJECTPTRLABELKHRPROC)(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
typedef void(GL_APIENTRYP PFNGLGETPOINTERVKHRPROC)(GLenum pname, void **params);
    #ifdef GL_GLEXT_PROTOTYPES
GL_APICALL void GL_APIENTRY glDebugMessageControlKHR(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
GL_APICALL void GL_APIENTRY glDebugMessageInsertKHR(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
GL_APICALL void GL_APIENTRY glDebugMessageCallbackKHR(GLDEBUGPROCKHR callback, const void *userParam);
GL_APICALL GLuint GL_APIENTRY glGetDebugMessageLogKHR(GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
GL_APICALL void GL_APIENTRY glPushDebugGroupKHR(GLenum source, GLuint id, GLsizei length, const GLchar *message);
GL_APICALL void GL_APIENTRY glPopDebugGroupKHR(void);
GL_APICALL void GL_APIENTRY glObjectLabelKHR(GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
GL_APICALL void GL_APIENTRY glGetObjectLabelKHR(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
GL_APICALL void GL_APIENTRY glObjectPtrLabelKHR(const void *ptr, GLsizei length, const GLchar *label);
GL_APICALL void GL_APIENTRY glGetObjectPtrLabelKHR(const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
GL_APICALL void GL_APIENTRY glGetPointervKHR(GLenum pname, void **params);
    #endif
#endif /* GL_KHR_debug */



#ifndef GL_KHR_texture_compression_astc_hdr
    #define GL_KHR_texture_compression_astc_hdr       1
    #define GL_COMPRESSED_RGBA_ASTC_4x4_KHR           0x93B0
    #define GL_COMPRESSED_RGBA_ASTC_5x4_KHR           0x93B1
    #define GL_COMPRESSED_RGBA_ASTC_5x5_KHR           0x93B2
    #define GL_COMPRESSED_RGBA_ASTC_6x5_KHR           0x93B3
    #define GL_COMPRESSED_RGBA_ASTC_6x6_KHR           0x93B4
    #define GL_COMPRESSED_RGBA_ASTC_8x5_KHR           0x93B5
    #define GL_COMPRESSED_RGBA_ASTC_8x6_KHR           0x93B6
    #define GL_COMPRESSED_RGBA_ASTC_8x8_KHR           0x93B7
    #define GL_COMPRESSED_RGBA_ASTC_10x5_KHR          0x93B8
    #define GL_COMPRESSED_RGBA_ASTC_10x6_KHR          0x93B9
    #define GL_COMPRESSED_RGBA_ASTC_10x8_KHR          0x93BA
    #define GL_COMPRESSED_RGBA_ASTC_10x10_KHR         0x93BB
    #define GL_COMPRESSED_RGBA_ASTC_12x10_KHR         0x93BC
    #define GL_COMPRESSED_RGBA_ASTC_12x12_KHR         0x93BD
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR   0x93D0
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR   0x93D1
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR   0x93D2
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR   0x93D3
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR   0x93D4
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR   0x93D5
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR   0x93D6
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR   0x93D7
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR  0x93D8
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR  0x93D9
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR  0x93DA
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR 0x93DB
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR 0x93DC
    #define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR 0x93DD
#endif /* GL_KHR_texture_compression_astc_hdr */
#ifndef GL_KHR_texture_compression_astc_ldr
    #define GL_KHR_texture_compression_astc_ldr 1
#endif /* GL_KHR_texture_compression_astc_ldr */

#ifndef GL_KHR_texture_compression_astc_sliced_3d
    #define GL_KHR_texture_compression_astc_sliced_3d 1
#endif /* GL_KHR_texture_compression_astc_sliced_3d */


#ifndef GL_OES_EGL_image_external_essl3
    #define GL_OES_EGL_image_external_essl3 1
#endif /* GL_OES_EGL_image_external_essl3 */

#ifndef GL_OES_compressed_ETC1_RGB8_sub_texture
    #define GL_OES_compressed_ETC1_RGB8_sub_texture 1
#endif /* GL_OES_compressed_ETC1_RGB8_sub_texture */

#ifndef GL_OES_compressed_ETC1_RGB8_texture
    #define GL_OES_compressed_ETC1_RGB8_texture 1
    #define GL_ETC1_RGB8_OES                    0x8D64
#endif /* GL_OES_compressed_ETC1_RGB8_texture */

#ifndef GL_EXT_texture_compression_astc_decode_mode
    #define GL_EXT_texture_compression_astc_decode_mode 1
    #define GL_TEXTURE_ASTC_DECODE_PRECISION_EXT        0x8F69
#endif /* GL_EXT_texture_compression_astc_decode_mode */

#ifndef GL_EXT_texture_compression_bptc
    #define GL_EXT_texture_compression_bptc           1
    #define GL_COMPRESSED_RGBA_BPTC_UNORM_EXT         0x8E8C
    #define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_EXT   0x8E8D
    #define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_EXT   0x8E8E
    #define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_EXT 0x8E8F
#endif /* GL_EXT_texture_compression_bptc */

#ifndef GL_EXT_texture_compression_dxt1
    #define GL_EXT_texture_compression_dxt1  1
    #define GL_COMPRESSED_RGB_S3TC_DXT1_EXT  0x83F0
    #define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#endif /* GL_EXT_texture_compression_dxt1 */

#ifndef GL_EXT_texture_compression_rgtc
    #define GL_EXT_texture_compression_rgtc          1
    #define GL_COMPRESSED_RED_RGTC1_EXT              0x8DBB
    #define GL_COMPRESSED_SIGNED_RED_RGTC1_EXT       0x8DBC
    #define GL_COMPRESSED_RED_GREEN_RGTC2_EXT        0x8DBD
    #define GL_COMPRESSED_SIGNED_RED_GREEN_RGTC2_EXT 0x8DBE
#endif /* GL_EXT_texture_compression_rgtc */

#ifndef GL_EXT_texture_compression_s3tc
    #define GL_EXT_texture_compression_s3tc  1
    #define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
    #define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3
#endif /* GL_EXT_texture_compression_s3tc */

#ifndef GL_EXT_texture_compression_s3tc_srgb
    #define GL_EXT_texture_compression_s3tc_srgb   1
    #define GL_COMPRESSED_SRGB_S3TC_DXT1_EXT       0x8C4C
    #define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT 0x8C4D
    #define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT 0x8C4E
    #define GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT 0x8C4F
#endif /* GL_EXT_texture_compression_s3tc_srgb */

#ifndef GL_IMG_texture_compression_pvrtc
    #define GL_IMG_texture_compression_pvrtc    1
    #define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG  0x8C00
    #define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG  0x8C01
    #define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG 0x8C02
    #define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG 0x8C03
#endif /* GL_IMG_texture_compression_pvrtc */

#ifndef GL_IMG_texture_compression_pvrtc2
    #define GL_IMG_texture_compression_pvrtc2   1
    #define GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG 0x9137
    #define GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG 0x9138
#endif /* GL_IMG_texture_compression_pvrtc2 */


#ifndef GL_EXT_sRGB
    #define GL_EXT_sRGB                                  1
    #define GL_SRGB_EXT                                  0x8C40
    #define GL_SRGB_ALPHA_EXT                            0x8C42
    #define GL_SRGB8_ALPHA8_EXT                          0x8C43
    #define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT 0x8210
#endif /* GL_EXT_sRGB */

#ifndef GL_EXT_sRGB_write_control
    #define GL_EXT_sRGB_write_control 1
    #define GL_FRAMEBUFFER_SRGB_EXT   0x8DB9
#endif /* GL_EXT_sRGB_write_control */



#ifndef GL_QCOM_perfmon_global_mode
    #define GL_QCOM_perfmon_global_mode 1
    #define GL_PERFMON_GLOBAL_MODE_QCOM 0x8FA0
#endif /* GL_QCOM_perfmon_global_mode */

#ifndef GL_QCOM_shader_framebuffer_fetch_noncoherent
    #define GL_QCOM_shader_framebuffer_fetch_noncoherent 1
    #define GL_FRAMEBUFFER_FETCH_NONCOHERENT_QCOM        0x96A2
typedef void(GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIERQCOMPROC)(void);
    #ifdef GL_GLEXT_PROTOTYPES
GL_APICALL void GL_APIENTRY glFramebufferFetchBarrierQCOM(void);
    #endif
#endif /* GL_QCOM_shader_framebuffer_fetch_noncoherent */

#ifndef GL_QCOM_shader_framebuffer_fetch_rate
    #define GL_QCOM_shader_framebuffer_fetch_rate 1
#endif /* GL_QCOM_shader_framebuffer_fetch_rate */

#ifndef GL_QCOM_shading_rate
    #define GL_QCOM_shading_rate                       1
    #define GL_SHADING_RATE_QCOM                       0x96A4
    #define GL_SHADING_RATE_PRESERVE_ASPECT_RATIO_QCOM 0x96A5
    #define GL_SHADING_RATE_1X1_PIXELS_QCOM            0x96A6
    #define GL_SHADING_RATE_1X2_PIXELS_QCOM            0x96A7
    #define GL_SHADING_RATE_2X1_PIXELS_QCOM            0x96A8
    #define GL_SHADING_RATE_2X2_PIXELS_QCOM            0x96A9
    #define GL_SHADING_RATE_4X2_PIXELS_QCOM            0x96AC
    #define GL_SHADING_RATE_4X4_PIXELS_QCOM            0x96AE
typedef void(GL_APIENTRYP PFNGLSHADINGRATEQCOMPROC)(GLenum rate);
    #ifdef GL_GLEXT_PROTOTYPES
GL_APICALL void GL_APIENTRY glShadingRateQCOM(GLenum rate);
    #endif
#endif /* GL_QCOM_shading_rate */

#ifndef GL_EXT_shader_framebuffer_fetch
    #define GL_EXT_shader_framebuffer_fetch         1
    #define GL_FRAGMENT_SHADER_DISCARDS_SAMPLES_EXT 0x8A52
#endif /* GL_EXT_shader_framebuffer_fetch */

#ifndef GL_EXT_shader_framebuffer_fetch_non_coherent
    #define GL_EXT_shader_framebuffer_fetch_non_coherent 1
typedef void(GL_APIENTRYP PFNGLFRAMEBUFFERFETCHBARRIEREXTPROC)(void);
    #ifdef GL_GLEXT_PROTOTYPES
GL_APICALL void GL_APIENTRY glFramebufferFetchBarrierEXT(void);
    #endif
#endif /* GL_EXT_shader_framebuffer_fetch_non_coherent */

#ifndef GL_EXT_shader_pixel_local_storage
    #define GL_EXT_shader_pixel_local_storage               1
    #define GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_FAST_SIZE_EXT 0x8F63
    #define GL_MAX_SHADER_PIXEL_LOCAL_STORAGE_SIZE_EXT      0x8F67
    #define GL_SHADER_PIXEL_LOCAL_STORAGE_EXT               0x8F64
#endif /* GL_EXT_shader_pixel_local_storage */

#ifndef GL_EXT_shader_pixel_local_storage2
    #define GL_EXT_shader_pixel_local_storage2                                       1
    #define GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_FAST_SIZE_EXT                       0x9650
    #define GL_MAX_SHADER_COMBINED_LOCAL_STORAGE_SIZE_EXT                            0x9651
    #define GL_FRAMEBUFFER_INCOMPLETE_INSUFFICIENT_SHADER_COMBINED_LOCAL_STORAGE_EXT 0x9652
typedef void(GL_APIENTRYP PFNGLFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC)(GLuint target, GLsizei size);
typedef GLsizei(GL_APIENTRYP PFNGLGETFRAMEBUFFERPIXELLOCALSTORAGESIZEEXTPROC)(GLuint target);
typedef void(GL_APIENTRYP PFNGLCLEARPIXELLOCALSTORAGEUIEXTPROC)(GLsizei offset, GLsizei n, const GLuint *values);
    #ifdef GL_GLEXT_PROTOTYPES
GL_APICALL void GL_APIENTRY glFramebufferPixelLocalStorageSizeEXT(GLuint target, GLsizei size);
GL_APICALL GLsizei GL_APIENTRY glGetFramebufferPixelLocalStorageSizeEXT(GLuint target);
GL_APICALL void GL_APIENTRY glClearPixelLocalStorageuiEXT(GLsizei offset, GLsizei n, const GLuint *values);
    #endif
#endif /* GL_EXT_shader_pixel_local_storage2 */