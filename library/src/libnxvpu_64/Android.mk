ifeq ($(TARGET_ARCH),arm64)
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
# LOCAL_PRELINK_MODULE := false

SLSIAP_INCLUDE := $(TOP)/hardware/samsung_slsi/slsiap/include
LINUX_INCLUDE  := $(TOP)/linux/platform/$(TARGET_CPU_VARIANT2)/library/include
LINUX_LIBRARY  := $(TOP)/linux/platform/$(TARGET_CPU_VARIANT2)/library

LOCAL_SHARED_LIBRARIES :=	\
	liblog \
	libcutils \
	libion \
	libion-nexell

LOCAL_STATIC_LIBRARIES := \
	libnxmalloc

LOCAL_C_INCLUDES := system/core/include/ion \
					$(SLSIAP_INCLUDE) \
					$(LINUX_INCLUDE)

LOCAL_CFLAGS :=
LOCAL_SRC_FILES :=
LOCAL_LDFLAGS +=

LOCAL_MODULE := libnx_vpu

LOCAL_MODULE_TAGS := optional

include $(LOCAL_PATH)/build.arm.mk
include $(LOCAL_PATH)/build.arm64.mk

include $(BUILD_SHARED_LIBRARY)

endif
