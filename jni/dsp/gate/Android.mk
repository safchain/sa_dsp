LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# sources.mk adds c source files to LOCAL_SRC_FILES
include $(LOCAL_PATH)/sources.mk


LOCAL_C_INCLUDES := $(LOCAL_PATH) 

LOCAL_MODULE := gate
LOCAL_CLFAGS := -std=c99 -DHAVE_CONFIG_H=1
LOCAL_EXPORT_CFLAGS := -DHAVE_CONFIG_H=1
LOCAL_LDLIBS := -llog

include $(BUILD_SHARED_LIBRARY)
