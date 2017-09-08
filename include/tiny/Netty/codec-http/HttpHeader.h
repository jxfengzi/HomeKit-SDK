/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HttpHeader.h
 *
 * @remark
 *		set tabstop=4
 *		set shiftwidth=4
 *		set expandtab
 */

#ifndef __HTTP_HEADER_H__
#define __HTTP_HEADER_H__

#include <tiny_base.h>
#include <tiny_api.h>
#include <TinyList.h>

TINY_BEGIN_DECLS


typedef struct _HttpHeader
{
    TinyList        list;
} HttpHeader;

TINY_API
TINY_LOR
TinyRet HttpHeader_Construct(HttpHeader *thiz);

TINY_API
TINY_LOR
TinyRet HttpHeader_Dispose(HttpHeader *thiz);

//TINY_LOR
//HttpHeader * HttpHeader_New(void);
//
//TINY_LOR
//void HttpHeader_Delete(HttpHeader *thiz);
//
//TINY_LOR
//void HttpHeader_Copy(HttpHeader *dst, HttpHeader *src);

TINY_API
TINY_LOR
void HttpHeader_Set(HttpHeader * thiz, const char *name, const char *value);

TINY_API
TINY_LOR
void HttpHeader_SetInteger(HttpHeader * thiz, const char *name, uint32_t value);

//TINY_LOR
//uint32_t HttpHeader_GetCount(HttpHeader * thiz);

TINY_API
TINY_LOR
const char * HttpHeader_GetValue(HttpHeader * thiz, const char *name);

TINY_API
TINY_LOR
const char * HttpHeader_GetNameAt(HttpHeader * thiz, uint32_t index);

TINY_API
TINY_LOR
const char * HttpHeader_GetValueAt(HttpHeader * thiz, uint32_t index);

TINY_API
TINY_LOR
uint32_t HttpHeader_Parse(HttpHeader *thiz, const char *bytes, uint32_t len);


TINY_END_DECLS

#endif /* __HTTP_HEADER_H__ */
