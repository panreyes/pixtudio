LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

common_SRC_FILES := \
	../../../../3rdparty/libpng/png.c \
    ../../../../3rdparty/libpng/pngerror.c \
    ../../../../3rdparty/libpng/pngget.c \
    ../../../../3rdparty/libpng/pngmem.c \
    ../../../../3rdparty/libpng/pngpread.c \
    ../../../../3rdparty/libpng/pngread.c \
    ../../../../3rdparty/libpng/pngrio.c \
    ../../../../3rdparty/libpng/pngrtran.c \
    ../../../../3rdparty/libpng/pngwio.c \
    ../../../../3rdparty/libpng/pngwrite.c \
    ../../../../3rdparty/libpng/pngwtran.c \
    ../../../../3rdparty/libpng/pngwutil.c \
    ../../../../3rdparty/libpng/pngrutil.c \
    ../../../../3rdparty/libpng/pngset.c \
    ../../../../3rdparty/libpng/pngtrans.c

common_CFLAGS := ## -fomit-frame-pointer

common_C_INCLUDES += $(LOCAL_PATH)/../../../../3rdparty/libpng/\

# For the host
# =====================================================

LOCAL_SRC_FILES := $(common_SRC_FILES)
LOCAL_CFLAGS += -O3 $(common_CFLAGS)
LOCAL_C_INCLUDES += $(common_C_INCLUDES)

LOCAL_MODULE:= png

LOCAL_COPY_HEADERS_TO := $(common_COPY_HEADERS_TO)
LOCAL_COPY_HEADERS := $(common_COPY_HEADERS)

LOCAL_LDLIBS := -lz -lc

include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_SHARED_LIBRARY)

