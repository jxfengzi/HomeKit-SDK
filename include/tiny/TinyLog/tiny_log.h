/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_log.h
 *
 * @remark
 *
 */

#ifndef __tiny_log_H__
#define __tiny_log_H__


#ifdef __ANDROID__
    #include <android/log.h>
    #define LOG_D(tag, format, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, format, ##__VA_ARGS__)
    #define LOG_E(tag, format, ...) __android_log_print(ANDROID_LOG_ERROR, tag, format, ##__VA_ARGS__)
    #define LOG_I(tag, format, ...) __android_log_print(ANDROID_LOG_INFO, tag, format, ##__VA_ARGS__)
    #define LOG_V(tag, format, ...) __android_log_print(ANDROID_LOG_VERBOSE, tag, format, ##__VA_ARGS__)
    #define LOG_W(tag, format, ...) __android_log_print(ANDROID_LOG_WARN, tag, format, ##__VA_ARGS__)
#else
    #ifdef TINY_DEBUG
        #ifdef ESP
            #define LOG_D(tag, format, ...) {printf(tag); printf("/D "); printf(format, ##__VA_ARGS__); printf("\n");}
            #define LOG_E(tag, format, ...) {printf(tag); printf("/E "); printf(format, ##__VA_ARGS__); printf("\n");}
            #define LOG_I(tag, format, ...) {printf(tag); printf("/I "); printf(format, ##__VA_ARGS__); printf("\n");}
            #define LOG_V(tag, format, ...) {printf(tag); printf("/V "); printf(format, ##__VA_ARGS__); printf("\n");}
            #define LOG_W(tag, format, ...) {printf(tag); printf("/W "); printf(format, ##__VA_ARGS__); printf("\n");}
        #else
            #include "tiny_log_print.h"
            #define LOG_D(tag, format, ...) __tiny_log_print(TINY_LOG_DEBUG, tag, format, ##__VA_ARGS__)
            #define LOG_E(tag, format, ...) __tiny_log_print(TINY_LOG_ERROR, tag, format, ##__VA_ARGS__)
            #define LOG_I(tag, format, ...) __tiny_log_print(TINY_LOG_INFO, tag, format, ##__VA_ARGS__)
            #define LOG_V(tag, format, ...) __tiny_log_print(TINY_LOG_VERBOSE, tag, format, ##__VA_ARGS__)
            #define LOG_W(tag, format, ...) __tiny_log_print(TINY_LOG_WARN, tag, format, ##__VA_ARGS__)
        #endif
    #else
        #ifdef ESP
            #define LOG_D(tag, format, ...)
            #define LOG_E(tag, format, ...) {printf(tag); printf("/E "); printf(format, ##__VA_ARGS__); printf("\n");}
            #define LOG_I(tag, format, ...) {printf(tag); printf("/I "); printf(format, ##__VA_ARGS__); printf("\n");}
            #define LOG_V(tag, format, ...) {printf(tag); printf("/V "); printf(format, ##__VA_ARGS__); printf("\n");}
            #define LOG_W(tag, format, ...) {printf(tag); printf("/W "); printf(format, ##__VA_ARGS__); printf("\n");}
        #else
            #include "tiny_log_print.h"
            #define LOG_D(tag, format, ...)
            #define LOG_E(tag, format, ...) __tiny_log_print(TINY_LOG_ERROR, tag, format, ##__VA_ARGS__)
            #define LOG_I(tag, format, ...) __tiny_log_print(TINY_LOG_INFO, tag, format, ##__VA_ARGS__)
            #define LOG_V(tag, format, ...) __tiny_log_print(TINY_LOG_VERBOSE, tag, format, ##__VA_ARGS__)
            #define LOG_W(tag, format, ...) __tiny_log_print(TINY_LOG_WARN, tag, format, ##__VA_ARGS__)
        #endif
    #endif /* TINY_DEBUG */
#endif /* __ANDROID__ */


#endif /* __tiny_log_H__ */