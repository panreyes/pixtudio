LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := tre

common_C_INCLUDES := $(LOCAL_PATH) \
					 $(LOCAL_PATH)/lib

common_SRC_FILES := $(LOCAL_PATH)/lib/tre-ast.c \
					$(LOCAL_PATH)/lib/tre-compile.c \
					$(LOCAL_PATH)/lib/tre-match-backtrack.c \
					$(LOCAL_PATH)/lib/tre-match-parallel.c \
					$(LOCAL_PATH)/lib/tre-mem.c \
					$(LOCAL_PATH)/lib/tre-parse.c \
					$(LOCAL_PATH)/lib/tre-stack.c \
					$(LOCAL_PATH)/lib/regcomp.c \
					$(LOCAL_PATH)/lib/regexec.c \
					$(LOCAL_PATH)/lib/regerror.c \
					$(LOCAL_PATH)/lib/tre-match-approx.c

common_CFLAGS := -fPIC -ffast-math -DHAVE_CONFIG_H

# For the host
# =====================================================

LOCAL_SRC_FILES := $(common_SRC_FILES)
LOCAL_CFLAGS += -O3 $(common_CFLAGS)
LOCAL_C_INCLUDES += $(common_C_INCLUDES)

LOCAL_LDLIBS :=

include $(BUILD_STATIC_LIBRARY)
# include $(BUILD_SHARED_LIBRARY)
