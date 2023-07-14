#ifndef UTILS
#define UTILS

#include <jni.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include "Logger.h"
namespace base64 {
    inline std::string get_base64_chars() {
        static std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                          "abcdefghijklmnopqrstuvwxyz"
                                          "0123456789+/";
        return base64_chars;
    }

    inline std::string base64_Decoder(std::string const &data) {
        int counter = 0;
        uint32_t bit_stream = 0;
        std::string decoded;
        int offset = 0;
        const std::string base64_chars = get_base64_chars();
        for (auto const &c : data) {
            auto num_val = base64_chars.find(c);
            if (num_val != std::string::npos) {
                offset = 18 - counter % 4 * 6;
                bit_stream += num_val << offset;
                if (offset == 12) {
                    decoded += static_cast<char>(bit_stream >> 16 & 0xff);
                }
                if (offset == 6) {
                    decoded += static_cast<char>(bit_stream >> 8 & 0xff);
                }
                if (offset == 0 && counter != 4) {
                    decoded += static_cast<char>(bit_stream & 0xff);
                    bit_stream = 0;
                }
            } else if (c != '=') {
                return std::string();
            }
            counter++;
        }
        return decoded;
    }
}

void MakeToast(JNIEnv *env, jobject thiz, const char *text, int length) {
    //Add our toast in here so it wont be easy to change by simply editing the smali and cant
    //be cut out because this method is needed to start the hack (Octowolve is smart)
    jstring jstr = env->NewStringUTF(text); //Edit this text to your desired toast message!
    jclass toast = env->FindClass("android/widget/Toast");
    jmethodID methodMakeText =
            env->GetStaticMethodID(
                    toast,
                    "makeText",
                            "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;");
    if (methodMakeText == NULL) {
        return;
    }
    //The last int is the length on how long the toast should be displayed
    //0 = Short, 1 = Long
    jobject toastobj = env->CallStaticObjectMethod(toast, methodMakeText,
                                                   thiz, jstr, length);

    jmethodID methodShow = env->GetMethodID(toast, "show", "()V");
    if (methodShow == NULL) {
        return;
    }
    env->CallVoidMethod(toastobj, methodShow);
}

namespace Toast {
    int LENGTH_LONG = 1;
    int LENGTH_SHORT = 0;
}

#endif
