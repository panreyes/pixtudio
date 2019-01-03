LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libjpeg-turbo

LOCAL_CFLAGS := -O3 \
                -fstrict-aliasing \
                -Werror \
                -Wno-sign-compare \
                -Wno-unused-parameter

LOCAL_ASMFLAGS += -DELF

# LOCAL_C_INCLUDES := $(LOCAL_PATH)/include \
#   $(LOCAL_PATH)/src

LOCAL_SRC_FILES := \
    $(subst $(LOCAL_PATH)/,, \
      $(LOCAL_PATH)/jaricom.c \
      $(LOCAL_PATH)/jcapimin.c \
      $(LOCAL_PATH)/jcapistd.c \
      $(LOCAL_PATH)/jcarith.c \
      $(LOCAL_PATH)/jccoefct.c \
      $(LOCAL_PATH)/jccolor.c \
      $(LOCAL_PATH)/jcdctmgr.c \
      $(LOCAL_PATH)/jchuff.c \
      $(LOCAL_PATH)/jcinit.c \
      $(LOCAL_PATH)/jcmainct.c \
      $(LOCAL_PATH)/jcmarker.c \
      $(LOCAL_PATH)/jcmaster.c \
      $(LOCAL_PATH)/jcomapi.c \
      $(LOCAL_PATH)/jcparam.c \
      $(LOCAL_PATH)/jcphuff.c \
      $(LOCAL_PATH)/jcprepct.c \
      $(LOCAL_PATH)/jcsample.c \
      $(LOCAL_PATH)/jctrans.c \
      $(LOCAL_PATH)/jdapimin.c \
      $(LOCAL_PATH)/jdapistd.c \
      $(LOCAL_PATH)/jdarith.c \
      $(LOCAL_PATH)/jdatadst.c \
      $(LOCAL_PATH)/jdatasrc.c \
      $(LOCAL_PATH)/jdcoefct.c \
      $(LOCAL_PATH)/jdcolor.c \
      $(LOCAL_PATH)/jddctmgr.c \
      $(LOCAL_PATH)/jdhuff.c \
      $(LOCAL_PATH)/jdinput.c \
      $(LOCAL_PATH)/jdmainct.c \
      $(LOCAL_PATH)/jdmarker.c \
      $(LOCAL_PATH)/jdmaster.c \
      $(LOCAL_PATH)/jdmerge.c \
      $(LOCAL_PATH)/jdphuff.c \
      $(LOCAL_PATH)/jdpostct.c \
      $(LOCAL_PATH)/jdsample.c \
      $(LOCAL_PATH)/jdtrans.c \
      $(LOCAL_PATH)/jerror.c \
      $(LOCAL_PATH)/jfdctflt.c \
      $(LOCAL_PATH)/jfdctfst.c \
      $(LOCAL_PATH)/jfdctint.c \
      $(LOCAL_PATH)/jidctflt.c \
      $(LOCAL_PATH)/jidctfst.c \
      $(LOCAL_PATH)/jidctint.c \
      $(LOCAL_PATH)/jidctred.c \
      $(LOCAL_PATH)/jmemmgr.c \
      $(LOCAL_PATH)/jmemnobs.c \
      $(LOCAL_PATH)/jquant1.c \
      $(LOCAL_PATH)/jquant2.c \
      $(LOCAL_PATH)/jutils.c)

ifeq ($(TARGET_ARCH_ABI),x86)
	LOCAL_SRC_FILES += \
	    $(subst $(LOCAL_PATH)/,, \
	      $(LOCAL_PATH)/simd/i386/jccolor-avx2.asm \
          $(LOCAL_PATH)/simd/i386/jccolor-mmx.asm \
          $(LOCAL_PATH)/simd/i386/jccolor-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jcgray-avx2.asm \
          $(LOCAL_PATH)/simd/i386/jcgray-mmx.asm \
          $(LOCAL_PATH)/simd/i386/jcgray-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jchuff-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jcphuff-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jcsample-avx2.asm \
          $(LOCAL_PATH)/simd/i386/jcsample-mmx.asm \
          $(LOCAL_PATH)/simd/i386/jcsample-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jdcolor-avx2.asm \
          $(LOCAL_PATH)/simd/i386/jdcolor-mmx.asm \
          $(LOCAL_PATH)/simd/i386/jdcolor-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jdmerge-avx2.asm \
          $(LOCAL_PATH)/simd/i386/jdmerge-mmx.asm \
          $(LOCAL_PATH)/simd/i386/jdmerge-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jdsample-avx2.asm \
          $(LOCAL_PATH)/simd/i386/jdsample-mmx.asm \
          $(LOCAL_PATH)/simd/i386/jdsample-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jfdctflt-3dn.asm \
          $(LOCAL_PATH)/simd/i386/jfdctflt-sse.asm \
          $(LOCAL_PATH)/simd/i386/jfdctfst-mmx.asm \
          $(LOCAL_PATH)/simd/i386/jfdctfst-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jfdctint-avx2.asm \
          $(LOCAL_PATH)/simd/i386/jfdctint-mmx.asm \
          $(LOCAL_PATH)/simd/i386/jfdctint-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jidctflt-3dn.asm \
          $(LOCAL_PATH)/simd/i386/jidctflt-sse.asm \
          $(LOCAL_PATH)/simd/i386/jidctflt-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jidctfst-mmx.asm \
          $(LOCAL_PATH)/simd/i386/jidctfst-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jidctint-avx2.asm \
          $(LOCAL_PATH)/simd/i386/jidctint-mmx.asm \
          $(LOCAL_PATH)/simd/i386/jidctint-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jidctred-mmx.asm \
          $(LOCAL_PATH)/simd/i386/jidctred-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jquant-3dn.asm \
          $(LOCAL_PATH)/simd/i386/jquant-mmx.asm \
          $(LOCAL_PATH)/simd/i386/jquant-sse.asm \
          $(LOCAL_PATH)/simd/i386/jquantf-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jquanti-avx2.asm \
          $(LOCAL_PATH)/simd/i386/jquanti-sse2.asm \
          $(LOCAL_PATH)/simd/i386/jsimd.c \
          $(LOCAL_PATH)/simd/i386/jsimdcpu.asm)
  	LOCAL_ASMFLAGS += -DPIC
  	LOCAL_C_INCLUDES += $(LOCAL_PATH)/simd \
  	                    $(LOCAL_PATH)/simd/nasm
else ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)
	LOCAL_SRC_FILES += \
        $(subst $(LOCAL_PATH)/,, \
          $(LOCAL_PATH)/simd/arm/jsimd.c \
          $(LOCAL_PATH)/simd/arm/jsimd_neon.S)
endif

include $(BUILD_STATIC_LIBRARY)