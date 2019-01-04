LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := theora

common_C_INCLUDES := $(LOCAL_PATH)/../../../../../3rdparty/libtheora/ \
    $(LOCAL_PATH)/../../../../../3rdparty/libtheora-1.1.1/include/ \
    $(LOCAL_PATH)/../../../../../3rdparty/SDL2_mixer-2.0.4/external/libogg-1.3.2/include

common_SRC_FILES := \
    ../../../../../3rdparty/libtheora-1.1.1/lib/apiwrapper.c \
    ../../../../../3rdparty/libtheora-1.1.1/lib/bitpack.c \
    ../../../../../3rdparty/libtheora-1.1.1/lib/decapiwrapper.c \
    ../../../../../3rdparty/libtheora-1.1.1/lib/decinfo.c \
    ../../../../../3rdparty/libtheora-1.1.1/lib/decode.c \
    ../../../../../3rdparty/libtheora-1.1.1/lib/dequant.c \
    ../../../../../3rdparty/libtheora-1.1.1/lib/fragment.c \
    ../../../../../3rdparty/libtheora-1.1.1/lib/huffdec.c \
    ../../../../../3rdparty/libtheora-1.1.1/lib/idct.c \
    ../../../../../3rdparty/libtheora-1.1.1/lib/info.c \
    ../../../../../3rdparty/libtheora-1.1.1/lib/internal.c \
    ../../../../../3rdparty/libtheora-1.1.1/lib/quant.c \
    ../../../../../3rdparty/libtheora-1.1.1/lib/state.c \
    ../../../../../3rdparty/libtheora-1.1.1/lib/encoder_disabled.c

common_CFLAGS := -Wno-parentheses -fforce-addr -fomit-frame-pointer -finline-functions -funroll-loops

# For the host
# =====================================================

LOCAL_SRC_FILES := $(common_SRC_FILES)
LOCAL_CFLAGS += -O3 $(common_CFLAGS)
LOCAL_C_INCLUDES += $(common_C_INCLUDES)

LOCAL_COPY_HEADERS_TO := $(common_COPY_HEADERS_TO)
LOCAL_COPY_HEADERS := $(common_COPY_HEADERS)

LOCAL_LDLIBS := -lz -lc

#include $(BUILD_STATIC_LIBRARY)
include $(BUILD_SHARED_LIBRARY)

