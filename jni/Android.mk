LOCAL_PATH := $(call my-dir)
MAIN_LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := Unknow/Unknow.cpp

LOCAL_MODULE := UNKNOW
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := main.cpp \
KittyMemory/KittyMemory.cpp \
KittyMemory/MemoryPatch.cpp \
KittyMemory/MemoryBackup.cpp \
KittyMemory/KittyUtils.cpp \
Substrate/hde64.c \
Unity/Vector2.hpp \
Unity/Vector3.hpp \
Unity/Quaternion.hpp \
And64InlineHook/And64InlineHook.cpp \
Substrate/SubstrateDebug.cpp \
Substrate/SubstrateHook.cpp \
Substrate/SubstratePosixMemory.cpp \
    
LOCAL_MODULE := YourLibName

LOCAL_CFLAGS += -DDEBUG
LOCAL_LDLIBS := -lm -ldl -llog -lGLESv2

include $(BUILD_SHARED_LIBRARY)
