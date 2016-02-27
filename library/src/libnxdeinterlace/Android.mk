LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
# LOCAL_PRELINK_MODULE := false

SLSIAP_INCLUDE := $(TOP)/hardware/samsung_slsi/slsiap/include
LINUX_INCLUDE  := $(TOP)/linux/platform/$(TARGET_CPU_VARIANT2)/library/include

LOCAL_SHARED_LIBRARIES :=

LOCAL_STATIC_LIBRARIES :=

LOCAL_C_INCLUDES :=	\
	system/core/include/ion \
	$(SLSIAP_INCLUDE)		\
	$(LINUX_INCLUDE)

LOCAL_SRC_FILES := \
	merge.c \
	algo_basic.c \
	algo_x.c \
	nx_deinterlace.c

ifeq ($(TARGET_ARCH),arm64)
LOCAL_CFLAGS += -DARM64=1
else
LOCAL_SRC_FILES += \
	merge_arm.s
LOCAL_CFLAGS += -DCAN_COMPILE_ARM -D__ARM_NEON__
LOCAL_CFLAGS += -DARM64=0
endif

LOCAL_LDFLAGS +=

LOCAL_MODULE := libnx_deinterlace

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
