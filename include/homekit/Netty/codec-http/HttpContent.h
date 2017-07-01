/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HttpContent.h
 *
 * @remark
 *		set tabstop=4
 *		set shiftwidth=4
 *		set expandtab
 */

#ifndef __HTTP_CONTENT_H__
#define __HTTP_CONTENT_H__

#include "tiny_base.h"

TINY_BEGIN_DECLS


#define HTTP_CONTENT_MAX_SIZE   (1024 * 1024 * 8)

typedef struct _HttpContent
{
    char       * buf;
    uint32_t     buf_size;
    uint32_t     data_size;
} HttpContent;

HttpContent * HttpContent_New(void);
TinyRet HttpContent_Construct(HttpContent *thiz);
TinyRet HttpContent_Dispose(HttpContent *thiz);
void HttpContent_Delete(HttpContent *thiz);
void HttpContent_Copy(HttpContent *dst, HttpContent *src);

TinyRet HttpContent_SetSize(HttpContent *thiz, uint32_t size);
uint32_t HttpContent_AddBytes(HttpContent *thiz, const char *data, uint32_t size);
bool HttpContent_IsFull(HttpContent *thiz);

uint32_t HttpContent_GetSize(HttpContent * thiz);
const char * HttpContent_GetObject(HttpContent * thiz);


TINY_END_DECLS

#endif /* __HTTP_CONTENT_H__ */