/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_inline.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_INLINE_H__
#define __TINY_INLINE_H__


#ifdef ESP
    #include "tiny_inline_esp.h"
#else
    #ifdef WIN32
        #include "tiny_inline_windows.h"
    #else
        #include "tiny_inline_linux.h"
    #endif
#endif


#endif /* __TINY_INLINE_H__ */