/**
 * Copyright (C) 2013-2015
 *
 * @author coding.tom@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_malloc.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 *
 */

#ifndef __TINY_MALLOC_H__
#define __TINY_MALLOC_H__

#include <tiny_typedef.h>
#include "tiny_base.h"
#include "tiny_api.h"

TINY_BEGIN_DECLS


#ifdef ESP
    #include "tiny_malloc_esp.h"
#else
    #ifdef WIN32
        #include "tiny_malloc_windows.h"
    #else
        #include "tiny_malloc_linux.h"
    #endif
#endif


TINY_END_DECLS

#endif /* __TINY_MALLOC_H__ */