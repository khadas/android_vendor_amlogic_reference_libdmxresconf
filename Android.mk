LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	libdmxresconf.c \
        cJSON.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/

LOCAL_SHARED_LIBRARIES := \
        liblog \
        libcutils \
        libutils
LOCAL_STATIC_LIBRARIES += \


LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= libdmxresconf
LOCAL_MULTILIB := 32
LOCAL_CFLAGS += -O0 -Werror
LOCAL_VENDOR_MODULE := true
LOCAL_LICENSE_KINDS := SPDX-license-identifier-Apache-2.0 legacy_by_exception_only legacy_notice
LOCAL_LICENSE_CONDITIONS := by_exception_only notice restricted

include $(BUILD_SHARED_LIBRARY)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	libdmxresconf.c \
        cJSON.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/

LOCAL_SHARED_LIBRARIES := \
        liblog \
        libcutils \
        libutils
LOCAL_STATIC_LIBRARIES += \

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= libdmxresconf.system
LOCAL_MULTILIB := 32
LOCAL_CFLAGS += -O0 -Werror
LOCAL_SYSTEM_EXT_MODULE := true
LOCAL_LICENSE_KINDS := SPDX-license-identifier-Apache-2.0 legacy_by_exception_only legacy_notice
LOCAL_LICENSE_CONDITIONS := by_exception_only notice restricted

include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_VENDOR_MODULE := true

LOCAL_SRC_FILES:= dmxresconf_test.c
LOCAL_MODULE := dmxresconf
LOCAL_MODULE_TAGS := optional
LOCAL_MULTILIB := 32
LOCAL_CFLAGS += -O0 -Werror
LOCAL_C_INCLUDES := $(LOCAL_PATH)/
LOCAL_SHARED_LIBRARIES := libcutils liblog libc libdmxresconf
LOCAL_LICENSE_KINDS := SPDX-license-identifier-Apache-2.0 legacy_by_exception_only legacy_notice
LOCAL_LICENSE_CONDITIONS := by_exception_only notice restricted

include $(BUILD_EXECUTABLE)