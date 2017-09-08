/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   JsonString.h
 *
 * @remark
 *
 */

#ifndef __JSON_STRING_H__
#define __JSON_STRING_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS


typedef struct _JsonString
{
    char        * value;
    uint32_t      length;
} JsonString;

TINY_LOR
JsonString * JsonString_New(const char *value);

TINY_LOR
void JsonString_Delete(JsonString *thiz);


TINY_END_DECLS

#endif /* __JSON_STRING_H__ */