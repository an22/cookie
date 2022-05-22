#ifndef MACRO_H
#define MACRO_H

#define TAG "COOKIE"

#ifndef NDEBUG
#ifdef __ANDROID__

#include <android/log.h>

#define LOG_E(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define LOG_D(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOG_I(...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOG_W(...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)

#else

#include <iostream>

#define LOG_E(...) std::printf("ERROR: %s\n", __VA_ARGS__)
#define LOG_D(...) std::printf("DEBUG: %s\n", __VA_ARGS__)
#define LOG_I(...) std::printf("INFO: %s\n", __VA_ARGS__)
#define LOG_W(...) std::printf("WARNING: %s\n", __VA_ARGS__)

#endif
#else
#define LOG_E(...)
#define LOG_D(...)
#define LOG_I(...)
#define LOG_W(...)
#endif
#endif