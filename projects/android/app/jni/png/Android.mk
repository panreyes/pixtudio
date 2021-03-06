LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

common_SRC_FILES := \
    ../../../../../3rdparty/libpng-1.6.36/png.c \
    ../../../../../3rdparty/libpng-1.6.36/pngerror.c \
    ../../../../../3rdparty/libpng-1.6.36/pngget.c \
    ../../../../../3rdparty/libpng-1.6.36/pngmem.c \
    ../../../../../3rdparty/libpng-1.6.36/pngpread.c \
    ../../../../../3rdparty/libpng-1.6.36/pngread.c \
    ../../../../../3rdparty/libpng-1.6.36/pngrio.c \
    ../../../../../3rdparty/libpng-1.6.36/pngrtran.c \
    ../../../../../3rdparty/libpng-1.6.36/pngrutil.c \
    ../../../../../3rdparty/libpng-1.6.36/pngset.c \
    ../../../../../3rdparty/libpng-1.6.36/pngtrans.c \
    ../../../../../3rdparty/libpng-1.6.36/pngwio.c \
    ../../../../../3rdparty/libpng-1.6.36/pngwrite.c \
    ../../../../../3rdparty/libpng-1.6.36/pngwtran.c \
    ../../../../../3rdparty/libpng-1.6.36/pngwutil.c

common_CFLAGS := ## -fomit-frame-pointer

common_C_INCLUDES += $(LOCAL_PATH)/../../../../../3rdparty/libpng-1.6.36/

# For the host
# =====================================================

LOCAL_SRC_FILES := $(common_SRC_FILES)
LOCAL_CFLAGS += -O3 $(common_CFLAGS)
LOCAL_C_INCLUDES += $(common_C_INCLUDES)

LOCAL_MODULE:= png

LOCAL_COPY_HEADERS_TO := $(common_COPY_HEADERS_TO)
LOCAL_COPY_HEADERS := $(common_COPY_HEADERS)

# LOCAL_LDLIBS := -lz -lc

include $(BUILD_STATIC_LIBRARY)
# include $(BUILD_SHARED_LIBRARY)

