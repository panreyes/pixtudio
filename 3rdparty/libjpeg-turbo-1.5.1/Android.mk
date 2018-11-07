LOCAL_PATH := $(abspath $(call my-dir))
include $(CLEAR_VARS)

LOCAL_MODULE := jpeg

ifneq ($(filter $(TARGET_ARCH_ABI), armeabi-v7a armeabi-v7a-hard x86),)
LOCAL_ARM_NEON := true
LOCAL_CFLAGS += -D__ARM_HAVE_NEON
endif

LOCAL_ASMFLAGS += -DELF

ifeq ($(TARGET_ARCH_ABI),x86_64)
LOCAL_SRC_FILES += \
    $(LOCAL_PATH)/simd/jsimd_x86_64.c \
    $(LOCAL_PATH)/simd/jfdctflt-sse-64.asm \
	$(LOCAL_PATH)/simd/jccolor-sse2-64.asm \
	$(LOCAL_PATH)/simd/jcgray-sse2-64.asm \
	$(LOCAL_PATH)/simd/jchuff-sse2-64.asm \
	$(LOCAL_PATH)/simd/jcsample-sse2-64.asm \
	$(LOCAL_PATH)/simd/jdcolor-sse2-64.asm \
	$(LOCAL_PATH)/simd/jdmerge-sse2-64.asm \
	$(LOCAL_PATH)/simd/jdsample-sse2-64.asm \
	$(LOCAL_PATH)/simd/jfdctfst-sse2-64.asm \
	$(LOCAL_PATH)/simd/jfdctint-sse2-64.asm \
	$(LOCAL_PATH)/simd/jidctflt-sse2-64.asm \
	$(LOCAL_PATH)/simd/jidctfst-sse2-64.asm \
	$(LOCAL_PATH)/simd/jidctint-sse2-64.asm \
	$(LOCAL_PATH)/simd/jidctred-sse2-64.asm \
	$(LOCAL_PATH)/simd/jquantf-sse2-64.asm \
	$(LOCAL_PATH)/simd/jquanti-sse2-64.asm \

else ifeq ($(TARGET_ARCH_ABI),x86)
LOCAL_SRC_FILES += \
	$(LOCAL_PATH)/simd/jsimd_i386.c \
	$(LOCAL_PATH)/simd/jsimdcpu.asm \
	$(LOCAL_PATH)/simd/jfdctflt-3dn.asm \
	$(LOCAL_PATH)/simd/jidctflt-3dn.asm \
	$(LOCAL_PATH)/simd/jquant-3dn.asm  \
	$(LOCAL_PATH)/simd/jccolor-mmx.asm \
	$(LOCAL_PATH)/simd/jcgray-mmx.asm \
	$(LOCAL_PATH)/simd/jcsample-mmx.asm  \
	$(LOCAL_PATH)/simd/jdcolor-mmx.asm \
	$(LOCAL_PATH)/simd/jdmerge-mmx.asm \
	$(LOCAL_PATH)/simd/jdsample-mmx.asm \
	$(LOCAL_PATH)/simd/jfdctfst-mmx.asm \
	$(LOCAL_PATH)/simd/jfdctint-mmx.asm \
	$(LOCAL_PATH)/simd/jidctfst-mmx.asm \
	$(LOCAL_PATH)/simd/jidctint-mmx.asm \
	$(LOCAL_PATH)/simd/jidctred-mmx.asm \
	$(LOCAL_PATH)/simd/jquant-mmx.asm \
	$(LOCAL_PATH)/simd/jfdctflt-sse.asm \
	$(LOCAL_PATH)/simd/jidctflt-sse.asm \
	$(LOCAL_PATH)/simd/jquant-sse.asm \
	$(LOCAL_PATH)/simd/jccolor-sse2.asm \
	$(LOCAL_PATH)/simd/jcgray-sse2.asm \
	$(LOCAL_PATH)/simd/jchuff-sse2.asm \
	$(LOCAL_PATH)/simd/jcsample-sse2.asm \
	$(LOCAL_PATH)/simd/jdcolor-sse2.asm \
	$(LOCAL_PATH)/simd/jdmerge-sse2.asm \
	$(LOCAL_PATH)/simd/jdsample-sse2.asm \
	$(LOCAL_PATH)/simd/jfdctfst-sse2.asm \
	$(LOCAL_PATH)/simd/jfdctint-sse2.asm \
	$(LOCAL_PATH)/simd/jidctflt-sse2.asm \
	$(LOCAL_PATH)/simd/jidctfst-sse2.asm \
	$(LOCAL_PATH)/simd/jidctint-sse2.asm \
	$(LOCAL_PATH)/simd/jidctred-sse2.asm \
	$(LOCAL_PATH)/simd/jquantf-sse2.asm \
	$(LOCAL_PATH)/simd/jquanti-sse2.asm \

else ifneq ($(filter $(TARGET_ARCH_ABI), armeabi-v7a armeabi-v7a-hard),)
LOCAL_SRC_FILES += \
    $(LOCAL_PATH)/simd/jsimd_arm.c \
    $(LOCAL_PATH)/simd/jsimd_arm_neon.S \

else ifeq ($(TARGET_ARCH_ABI),arm64-v8a)
LOCAL_SRC_FILES += \
    $(LOCAL_PATH)/simd/jsimd_arm64.c \
    $(LOCAL_PATH)/simd/jsimd_arm64_neon.S \

endif

# libjpeg_la_SOURCES from Makefile.am
LOCAL_SRC_FILES += \
    $(LOCAL_PATH)/jcapimin.c \
    $(LOCAL_PATH)/jcapistd.c\
    $(LOCAL_PATH)/jccoefct.c\
    $(LOCAL_PATH)/jccolor.c\
    $(LOCAL_PATH)/jcdctmgr.c\
    $(LOCAL_PATH)/jchuff.c\
    $(LOCAL_PATH)/jcinit.c\
    $(LOCAL_PATH)/jcmainct.c\
    $(LOCAL_PATH)/jcmarker.c\
    $(LOCAL_PATH)/jcmaster.c\
    $(LOCAL_PATH)/jcomapi.c\
    $(LOCAL_PATH)/jcparam.c\
    $(LOCAL_PATH)/jcphuff.c\
    $(LOCAL_PATH)/jcprepct.c\
    $(LOCAL_PATH)/jcsample.c\
    $(LOCAL_PATH)/jctrans.c\
    $(LOCAL_PATH)/jdapimin.c\
    $(LOCAL_PATH)/jdapistd.c\
    $(LOCAL_PATH)/jdatadst.c\
    $(LOCAL_PATH)/jdatasrc.c\
    $(LOCAL_PATH)/jdcoefct.c\
    $(LOCAL_PATH)/jdcolor.c\
    $(LOCAL_PATH)/jddctmgr.c\
    $(LOCAL_PATH)/jdhuff.c\
    $(LOCAL_PATH)/jdinput.c\
    $(LOCAL_PATH)/jdmainct.c\
    $(LOCAL_PATH)/jdmarker.c\
    $(LOCAL_PATH)/jdmaster.c\
    $(LOCAL_PATH)/jdmerge.c\
    $(LOCAL_PATH)/jdphuff.c\
    $(LOCAL_PATH)/jdpostct.c\
    $(LOCAL_PATH)/jdsample.c\
    $(LOCAL_PATH)/jdtrans.c\
    $(LOCAL_PATH)/jerror.c\
    $(LOCAL_PATH)/jfdctflt.c\
    $(LOCAL_PATH)/jfdctfst.c\
    $(LOCAL_PATH)/jfdctint.c\
    $(LOCAL_PATH)/jidctflt.c\
    $(LOCAL_PATH)/jidctfst.c\
    $(LOCAL_PATH)/jidctint.c\
    $(LOCAL_PATH)/jidctred.c\
    $(LOCAL_PATH)/jquant1.c\
    $(LOCAL_PATH)/jquant2.c\
    $(LOCAL_PATH)/jutils.c\
    $(LOCAL_PATH)/jmemmgr.c\
    $(LOCAL_PATH)/jmemnobs.c\

# if WITH_ARITH_DEC from Makefile.am
LOCAL_SRC_FILES += \
    $(LOCAL_PATH)/jdarith.c \

# libturbojpeg_la_SOURCES from Makefile.am
LOCAL_SRC_FILES += \
    $(LOCAL_PATH)/turbojpeg.c \
    $(LOCAL_PATH)/transupp.c \
    $(LOCAL_PATH)/jdatadst-tj.c \
    $(LOCAL_PATH)/jdatasrc-tj.c \

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/include \

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/$(SOURCE_PATH)/simd \
    $(LOCAL_PATH)/$(SOURCE_PATH) \

LOCAL_EXPORT_C_INCLUDES := \
    $(LOCAL_PATH)/$(SOURCE_PATH) \

LOCAL_CFLAGS += \
    -DBUILD="20161206" \
    -DC_ARITH_CODING_SUPPORTED=1 \
    -DD_ARITH_CODING_SUPPORTED=1 \
    -DBITS_IN_JSAMPLE=8 \
    -DHAVE_DLFCN_H=1 \
    -DHAVE_INTTYPES_H=1 \
    -DHAVE_LOCALE_H=1 \
    -DHAVE_MEMCPY=1 \
    -DHAVE_MEMORY_H=1 \
    -DHAVE_MEMSET=1 \
    -DHAVE_STDDEF_H=1 \
    -DHAVE_STDINT_H=1 \
    -DHAVE_STDLIB_H=1 \
    -DHAVE_STRINGS_H=1 \
    -DHAVE_STRING_H=1 \
    -DHAVE_SYS_STAT_H=1 \
    -DHAVE_SYS_TYPES_H=1 \
    -DHAVE_UNISTD_H=1 \
    -DHAVE_UNSIGNED_CHAR=1 \
    -DHAVE_UNSIGNED_SHORT=1 \
    -DINLINE="inline __attribute__((always_inline))" \
    -DJPEG_LIB_VERSION=80 \
    -DMEM_SRCDST_SUPPORTED=1 \
    -DNEED_SYS_TYPES_H=1 \
    -DSTDC_HEADERS=1 \
    -DWITH_SIMD=1 \

include $(BUILD_STATIC_LIBRARY)