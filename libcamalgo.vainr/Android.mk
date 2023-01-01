# Auto-generated content. DO NOT EDIT.

LOCAL_PATH := $(call my-dir)
MY_MK :=
ifneq (,$(MTK_TARGET_PROJECT))
  ifeq (,$(MTKCAM_TARGET_BOARD_PLATFORM))
    $(error MTKCAM_TARGET_BOARD_PLATFORM is undefined. Please make sure the CameraConfig.mk is correctly included.)
  endif
  MY_MK += $(wildcard $(LOCAL_PATH)/$(MTKCAM_TARGET_BOARD_PLATFORM)/Android.mk)
endif
include $(sort $(MY_MK))
