LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

common_SRC_FILES := \
    ../../../../3rdparty/libpng-1.6.23/png.c \
    ../../../../3rdparty/libpng-1.6.23/pngerror.c \
    ../../../../3rdparty/libpng-1.6.23/pngget.c \
    ../../../../3rdparty/libpng-1.6.23/pngmem.c \
    ../../../../3rdparty/libpng-1.6.23/pngpread.c \
    ../../../../3rdparty/libpng-1.6.23/pngread.c \
    ../../../../3rdparty/libpng-1.6.23/pngrio.c \
    ../../../../3rdparty/libpng-1.6.23/pngrtran.c \
    ../../../../3rdparty/libpng-1.6.23/pngrutil.c \
    ../../../../3rdparty/libpng-1.6.23/pngset.c \
    ../../../../3rdparty/libpng-1.6.23/pngtrans.c \
    ../../../../3rdparty/libpng-1.6.23/pngwio.c \
    ../../../../3rdparty/libpng-1.6.23/pngwrite.c \
    ../../../../3rdparty/libpng-1.6.23/pngwtran.c \
    ../../../../3rdparty/libpng-1.6.23/pngwutil.c

common_CFLAGS := ## -fomit-frame-pointer

common_C_INCLUDES += $(LOCAL_PATH)/../../../../3rdparty/libpng-1.6.23/

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

