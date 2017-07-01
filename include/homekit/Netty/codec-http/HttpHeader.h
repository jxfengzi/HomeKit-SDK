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

#include "tiny_base.h"
#include "TinyList.h"

TINY_BEGIN_DECLS


typedef struct _HttpHeader
{
    TinyList        list;
} HttpHeader;

HttpHeader * HttpHeader_New(void);
TinyRet HttpHeader_Construct(HttpHeader *thiz);
TinyRet HttpHeader_Dispose(HttpHeader *thiz);
void HttpHeader_Delete(HttpHeader *thiz);
void HttpHeader_Copy(HttpHeader *dst, HttpHeader *src);

void HttpHeader_Set(HttpHeader * thiz, const char *name, const char *value);
void HttpHeader_SetInteger(HttpHeader * thiz, const char *name, uint32_t value);
uint32_t HttpHeader_GetCount(HttpHeader * thiz);
const char * HttpHeader_GetValue(HttpHeader * thiz, const char *name);
const char * HttpHeader_GetNameAt(HttpHeader * thiz, uint32_t index);
const char * HttpHeader_GetValueAt(HttpHeader * thiz, uint32_t index);

uint32_t HttpHeader_Parse(HttpHeader *thiz, const char *bytes, uint32_t len);


TINY_END_DECLS

#endif /* __HTTP_HEADER_H__ */
