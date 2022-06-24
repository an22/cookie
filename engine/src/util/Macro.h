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

#define LOG_E(...) std::printf("ERROR: "); std::printf(__VA_ARGS__); std::cout << std::endl
#define LOG_D(...) std::printf("DEBUG: "); std::printf(__VA_ARGS__); std::cout << std::endl
#define LOG_I(...) std::printf("INFO: "); std::printf(__VA_ARGS__); std::cout << std::endl
#define LOG_W(...) std::printf("WARNING: "); std::printf(__VA_ARGS__); std::cout << std::endl

#endif
#else
#define LOG_E(...)
#define LOG_D(...)
#define LOG_I(...)
#define LOG_W(...)
#endif
#endif