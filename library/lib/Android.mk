# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

ifeq ($(TARGET_CPU_VARIANT2),s5p6818)

LOCAL_PATH := $(call my-dir)

ifneq ($(TARGET_ARCH),arm64)

include $(CLEAR_VARS)
LOCAL_MODULE := libnxvidrc_android
LOCAL_MODULE_OWNER := samsung
LOCAL_SRC_FILES := libnxvidrc_android.so
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_SUFFIX := .so
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
include $(BUILD_PREBUILT)

endif  # !arm64

include $(call all-makefiles-under,$(LOCAL_PATH))

endif
