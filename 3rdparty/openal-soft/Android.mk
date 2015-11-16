LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := openal

common_C_INCLUDES := $(LOCAL_PATH)/include \
					 $(LOCAL_PATH)/OpenAL32/Include \
					 $(LOCAL_PATH)/Alc \
					 $(LOCAL_PATH)

common_SRC_FILES := common/atomic.c \
					common/rwlock.c \
					common/threads.c \
					common/uintmap.c
openal_SRC_FILES :=	OpenAL32/alAuxEffectSlot.c \
					OpenAL32/alBuffer.c \
					OpenAL32/alEffect.c \
					OpenAL32/alError.c \
					OpenAL32/alExtension.c \
					OpenAL32/alFilter.c \
					OpenAL32/alListener.c \
					OpenAL32/alSource.c \
					OpenAL32/alState.c \
					OpenAL32/alThunk.c \
					OpenAL32/sample_cvt.c
alc_SRC_FILES :=	Alc/ALc.c \
					Alc/ALu.c \
					Alc/alcConfig.c \
					Alc/alcRing.c \
					Alc/bs2b.c \
					Alc/effects/autowah.c \
					Alc/effects/chorus.c \
					Alc/effects/compressor.c \
					Alc/effects/dedicated.c \
					Alc/effects/distortion.c \
					Alc/effects/echo.c \
					Alc/effects/equalizer.c \
					Alc/effects/flanger.c \
					Alc/effects/modulator.c \
					Alc/effects/null.c \
					Alc/effects/reverb.c \
					Alc/helpers.c \
					Alc/bsinc.c \
					Alc/hrtf.c \
					Alc/panning.c \
					Alc/mixer.c \
					Alc/mixer_c.c \
					Alc/backends/base.c \
					Alc/backends/loopback.c \
					Alc/backends/null.c \
					Alc/backends/opensl.c

common_CFLAGS := -std=c11 -fPIC -ffast-math -D_GNU_SOURCE=1 -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE=700 -Winline -Wall -Wextra -DAL_BUILD_LIBRARY -DAL_ALEXT_PROTOTYPES

# For the host
# =====================================================

LOCAL_ARM_NEON := true

LOCAL_SRC_FILES := $(common_SRC_FILES) $(openal_SRC_FILES) $(alc_SRC_FILES)
LOCAL_CFLAGS += -O3 $(common_CFLAGS)
LOCAL_C_INCLUDES += $(common_C_INCLUDES)

LOCAL_COPY_HEADERS_TO := $(common_COPY_HEADERS_TO)
LOCAL_COPY_HEADERS := $(common_COPY_HEADERS)

LOCAL_LDLIBS := -lc -lOpenSLES

#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)
