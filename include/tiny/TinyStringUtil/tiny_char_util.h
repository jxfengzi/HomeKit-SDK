/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   tiny_char_util.h
 *
 * @remark
 *		set tabstop=4
 *		set shiftwidth=4
 *		set expandtab
 */

#include <tiny_lor.h>
#include "tiny_base.h"
#include "tiny_api.h"

#ifndef __TINY_CHAR_UTIL_H__
#define __TINY_CHAR_UTIL_H__


TINY_BEGIN_DECLS


//TINY_API
//TINY_LOR
//int is_space(int c);

TINY_API
TINY_LOR
int is_char(int c);

TINY_API
TINY_LOR
int is_ctl(int c);

TINY_API
TINY_LOR
int is_tspecial(int c);

TINY_API
TINY_LOR
int is_digit(int c);

TINY_LOR
TINY_API
bool is_hex(char c);


TINY_END_DECLS

#endif /* __TINY_CHAR_UTIL_H__ */
