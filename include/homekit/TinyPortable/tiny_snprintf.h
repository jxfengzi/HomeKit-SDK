/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_snprintf.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_SNPRINTF_H__
#define __TINY_SNPRINTF_H__

#ifdef ESP
    #include "tiny_snprintf_esp.h"
#else
    #ifdef WIN32
        #include "tiny_snprintf_windows.h"
    #else
        #include "tiny_snprintf_linux.h"
    #endif
#endif


#endif /* __TINY_SNPRINTF_H__ */