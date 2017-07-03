/**
 * Copyright (C) 2013-2015
 *
 * @author coding.tom@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_malloc_esp.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 *
 */

#ifndef __TINY_MALLOC_ESP_H__
#define __TINY_MALLOC_ESP_H__

#include "tiny_base.h"
#include <espressif/esp_libc.h>


#define tiny_malloc         malloc
#define tiny_calloc         calloc
#define tiny_realloc        realloc
#define tiny_free           free


#endif /* __TINY_MALLOC_ESP_H__ */