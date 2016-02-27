LOCAL_SRC_FILES_arm += \
	src/parser_vld.c \
	src/nx_video_api.c

LOCAL_C_INCLUDES_arm += ./src/
LOCAL_CFLAGS_arm += 
LOCAL_LDFLAGS_arm += \
	-L$(TOP)/linux/platform/$(TARGET_CPU_VARIANT2)/library/lib -lnxvidrc_android
