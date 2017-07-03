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

#include <tiny_lor.h>
#include "tiny_base.h"

TINY_BEGIN_DECLS


#define HTTP_CONTENT_MAX_SIZE   (1024 * 1024 * 8)

typedef struct _HttpContent
{
    char       * buf;
    uint32_t     buf_size;
    uint32_t     data_size;
} HttpContent;

TINY_LOR
TinyRet HttpContent_Construct(HttpContent *thiz);

TINY_LOR
TinyRet HttpContent_Dispose(HttpContent *thiz);

//TINY_LOR
//HttpContent * HttpContent_New(void);
//
//TINY_LOR
//void HttpContent_Delete(HttpContent *thiz);
//
//TINY_LOR
//void HttpContent_Copy(HttpContent *dst, HttpContent *src);

TINY_LOR
TinyRet HttpContent_SetSize(HttpContent *thiz, uint32_t size);

TINY_LOR
uint32_t HttpContent_AddBytes(HttpContent *thiz, const char *data, uint32_t size);

TINY_LOR
bool HttpContent_IsFull(HttpContent *thiz);

TINY_LOR
uint32_t HttpContent_GetSize(HttpContent * thiz);

TINY_LOR
const char * HttpContent_GetObject(HttpContent * thiz);


TINY_END_DECLS

#endif /* __HTTP_CONTENT_H__ */