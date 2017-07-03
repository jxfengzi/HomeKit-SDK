/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_typedef.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_TYPEDEF_H__
#define __TINY_TYPEDEF_H__


/**---------------------------------------
 *
 * _DEFAULT_SOURCE: for ip_mreq
 *
 *---------------------------------------*/
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE 1
#endif

/**---------------------------------------
 *
 * _DARWIN_C_SOURCE: for ip_mreq
 *
 *---------------------------------------*/
#if defined __APPLE__
#define _DARWIN_C_SOURCE 1
#endif

#ifdef _WIN32
#include <ws2tcpip.h>
#include <windows.h>
#include <time.h>
#else /* Linux */
#include <unistd.h>
//#include <sys/time.h>
#endif /* _WIN32 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

//#include <errno.h>

#ifdef __cplusplus
    #define TINY_BEGIN_DECLS extern "C" {
    #define TINY_END_DECLS }
#else
    #define TINY_BEGIN_DECLS
    #define TINY_END_DECLS
#endif

#ifndef STR_EQUAL
    #define STR_EQUAL(a, b) (strcmp(a, b) == 0)
#endif

#define DIM(a) (sizeof(a)/sizeof(a[0]))



#endif /* __TINY_TYPEDEF_H__ */