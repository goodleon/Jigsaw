LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)



LOCAL_MODULE := cocos2dcpp_shared
LOCAL_MODULE_FILENAME := libcocos2dcpp

ALL_HEADER_DIR := $(shell find $(shell pwd)/jni/../../Classes -type d)
ALL_SRC_FILE := $(shell find $(shell pwd)/jni/../../Classes  -name '*.cpp' -o -name '*.c')

# $(warning 'LOCAL_PATH1', $(shell pwd))
# $(warning 'LOCAL_PATH2', $(call my-dir))
# $(warning 'LOCAL_PATH3', $(LOCAL_PATH))
# $(warning 'ALL_HEADER_DIR' $(ALL_HEADER_DIR))
# $(warning 'ALL_SRC_DIR' $(ALL_SRC_FILE))


LOCAL_SRC_FILES := ./hellocpp/main.cpp \
				$(ALL_SRC_FILE)


LOCAL_C_INCLUDES := $(ALL_HEADER_DIR)

LOCAL_CFLAGS += -Baidu_Pay

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
