/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_strdup.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_STRDUP_H__
#define __TINY_STRDUP_H__

#include <tiny_lor.h>
#include "tiny_typedef.h"
#include "tiny_api.h"

TINY_BEGIN_DECLS


TINY_API
TINY_LOR
char * tiny_strdup(const char *src);



TINY_END_DECLS

#endif /* __TINY_STRDUP_H__ */