/**
 * Copyright (C) 2013-2015
 *
 * @author coding.tom@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_lor.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 *
 */

#ifndef __TINY_LOR_H__
#define __TINY_LOR_H__

/**
 * TINY_LOR = Load On Runtime
 */

#ifdef ESP
    #ifndef ICACHE_FLASH
        #define ICACHE_FLASH
    #endif
    #include <espressif/c_types.h>
    #define TINY_LOR            ICACHE_FLASH_ATTR
    #define TINY_LOR_VAR        ICACHE_RODATA_ATTR
#else
    #define TINY_LOR
    #define TINY_LOR_VAR
#endif


#endif /* __TINY_LOR_H__ */