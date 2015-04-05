LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := theora

common_C_INCLUDES := $(LOCAL_PATH)/../../../../3rdparty/libtheora/ \
    $(LOCAL_PATH)/../../../../3rdparty/libtheora/include/ \
    $(LOCAL_PATH)/../../../../3rdparty/SDL_mixer/external/libogg-1.3.1/include

common_SRC_FILES := \
    ../../../../3rdparty/libtheora/lib/apiwrapper.c \
    ../../../../3rdparty/libtheora/lib/bitpack.c \
    ../../../../3rdparty/libtheora/lib/decapiwrapper.c \
    ../../../../3rdparty/libtheora/lib/decinfo.c \
    ../../../../3rdparty/libtheora/lib/decode.c \
    ../../../../3rdparty/libtheora/lib/dequant.c \
    ../../../../3rdparty/libtheora/lib/fragment.c \
    ../../../../3rdparty/libtheora/lib/huffdec.c \
    ../../../../3rdparty/libtheora/lib/idct.c \
    ../../../../3rdparty/libtheora/lib/info.c \
    ../../../../3rdparty/libtheora/lib/internal.c \
    ../../../../3rdparty/libtheora/lib/quant.c \
    ../../../../3rdparty/libtheora/lib/state.c \
    ../../../../3rdparty/libtheora/lib/encoder_disabled.c

common_CFLAGS := -Wno-parentheses -fforce-addr -fomit-frame-pointer -finline-functions -funroll-loops

# For the host
# =====================================================

LOCAL_SRC_FILES := $(common_SRC_FILES)
LOCAL_CFLAGS += -O3 $(common_CFLAGS)
LOCAL_C_INCLUDES += $(common_C_INCLUDES)

LOCAL_MODULE:= theora

LOCAL_COPY_HEADERS_TO := $(common_COPY_HEADERS_TO)
LOCAL_COPY_HEADERS := $(common_COPY_HEADERS)

LOCAL_LDLIBS := -lz -lc

#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)

