LOCAL_SRC_FILES_arm64 += \
	src_arm64/parser_vld.c \
	src_arm64/nx_video_api.c

LOCAL_C_INCLUDES_arm64 += 
LOCAL_CFLAGS_arm64 += 
LOCAL_LDFLAGS_arm64 += \
	-L$(TOP)/linux/platform/$(TARGET_CPU_VARIANT2)/library/lib/arm64 -lnxvidrc_android
