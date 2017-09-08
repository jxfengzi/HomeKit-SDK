/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   url_split.h
*
* @remark
*		set tabstop=4
*		set shiftwidth=4
*		set expandtab
*/

#ifndef __URL_SPLIT_H__
#define __URL_SPLIT_H__

#include <tiny_lor.h>
#include "tiny_base.h"
#include "tiny_api.h"

TINY_BEGIN_DECLS


TINY_API
TINY_LOR
TinyRet url_split(const char *url, char ip[], uint32_t ip_len, uint16_t *port, char uri[], uint32_t uri_len);


TINY_END_DECLS

#endif /* __URL_SPLIT_H__ */
