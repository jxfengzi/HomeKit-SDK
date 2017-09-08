/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   tiny_buffer_append.h
*
* @remark
*		set tabstop=4
*		set shiftwidth=4
*		set expandtab
*/

#ifndef __TINY_BUFFER_APPEND_H__
#define __TINY_BUFFER_APPEND_H__

#include <tiny_lor.h>
#include "tiny_base.h"
#include "tiny_api.h"

TINY_BEGIN_DECLS


TINY_API
TINY_LOR
int tiny_buffer_append(char *buf, uint32_t length, uint32_t offset, const char *string);


TINY_END_DECLS

#endif /* __TINY_BUFFER_APPEND_H__ */
