LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

common_SRC_FILES := \
	../../../../3rdparty/Chipmunk-6.1.3/src/chipmunk.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpArbiter.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpArray.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpBB.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpBBTree.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpBody.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpCollision.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpHashSet.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpPolyShape.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpShape.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpSpace.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpSpaceComponent.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpSpaceHash.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpSpaceQuery.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpSpaceStep.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpSpatialIndex.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpSweep1D.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/cpVect.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/constraints/cpConstraint.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/constraints/cpDampedRotarySpring.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/constraints/cpDampedSpring.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/constraints/cpGearJoint.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/constraints/cpGrooveJoint.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/constraints/cpPinJoint.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/constraints/cpPivotJoint.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/constraints/cpRatchetJoint.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/constraints/cpRotaryLimitJoint.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/constraints/cpSimpleMotor.c \
	../../../../3rdparty/Chipmunk-6.1.3/src/constraints/cpSlideJoint.c

common_CFLAGS := ## -fomit-frame-pointer

common_C_INCLUDES += $(LOCAL_PATH)/../../../../3rdparty/Chipmunk-6.1.3/include/chipmunk/ \
	$(LOCAL_PATH)/../../../../3rdparty/Chipmunk-6.1.3/include/chipmunk/constraints/ \
	$(LOCAL_PATH)/../../../../3rdparty/Chipmunk-6.1.3/src/

# For the host
# =====================================================

LOCAL_SRC_FILES := $(common_SRC_FILES)
LOCAL_CFLAGS += -O3 -std=gnu99 -ffast-math -DCP_USE_DOUBLES=0 $(common_CFLAGS)
LOCAL_C_INCLUDES += $(common_C_INCLUDES)

LOCAL_MODULE:= chipmunk

LOCAL_COPY_HEADERS_TO := $(common_COPY_HEADERS_TO)
LOCAL_COPY_HEADERS := $(common_COPY_HEADERS)

LOCAL_LDLIBS :=

include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_SHARED_LIBRARY)

