/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   tiny_time.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_TIME_H__
#define __TINY_TIME_H__

#include <tiny_typedef.h>
#include <tiny_lor.h>
#include <tiny_api.h>

#ifdef ESP
    #if LWIP_TIMEVAL_PRIVATE
        #include <lwip/lwip/sockets.h>
        #include <lwip/apps/time.h>
    #else
        #include <sys/time.h>
    #endif
#else
    #ifdef WIN32
	    #include <winsock2.h>
		#include <windows.h>
        #include <time.h>
    #else
        #include <time.h>
        #include <sys/time.h>
    #endif
#endif

TINY_BEGIN_DECLS


TINY_API
TINY_LOR
int tiny_gettimeofday(struct timeval *tv, void *tz);

TINY_API
TINY_LOR
uint64_t tiny_current_microsecond(void);

TINY_API
TINY_LOR
int tiny_getstrtime(char buf[], int len);


TINY_END_DECLS

#endif /* __TINY_TIME_H__ */
