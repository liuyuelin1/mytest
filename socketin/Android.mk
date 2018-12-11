# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.crg/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)
LOCAL_CFLAGS += -DANDROID
include $(CLEAR_VARS)
LOCAL_MODULE    := client
LOCAL_SRC_FILES := client.c

LOCAL_SHARED_LIBRARIES := \
        libandroid_runtime \
        libnativehelper \
        libcutils

LOCAL_PRELINK_MODULE := false

LOCAL_FORCE_STATIC_EXECUTABLE := true

LOCAL_MODULE_TAGS := eng

LOCAL_STATIC_LIBRARIES := libstdc++ libc libcutils

include $(BUILD_EXECUTABLE)
