LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := tremor

LOCAL_C_INCLUDES := $(LOCAL_PATH) $(LOCAL_PATH)/ogg
LOCAL_CFLAGS := -I$(LOCAL_PATH) -DHAVE_ALLOCA_H -DINCLUDE_INTTYPES_H -DINCLUDE_STDINT_H -DINCLUDE_SYS_TYPES_H -DUSE_MEMORY_H -DLITTLE_ENDIAN=1 -DBYTE_ORDER=LITTLE_ENDIAN

#ifeq ($(TARGET_ARCH),arm)
#LOCAL_CFLAGS := -D_ARM_ASSEM_
#endif

# Note this simple makefile var substitution, you can find even simpler examples in different Android projects
LOCAL_SRC_FILES := $(notdir $(wildcard $(LOCAL_PATH)/*.c))

include $(BUILD_STATIC_LIBRARY)

