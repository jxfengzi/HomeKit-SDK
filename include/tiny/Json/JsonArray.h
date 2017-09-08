/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   JsonArray.h
 *
 * @remark
 *
 */

#ifndef __JSON_ARRAY_H__
#define __JSON_ARRAY_H__

#include <tiny_base.h>
#include <TinyList.h>
#include "JsonValue.h"

TINY_BEGIN_DECLS


typedef struct _JsonArray
{
    JsonValueType   type;
    TinyList        values;
    char          * string;
} JsonArray;

TINY_LOR
TINY_API
JsonArray * JsonArray_New(JsonValueType type);

TINY_LOR
TINY_API
void JsonArray_Delete(JsonArray *thiz);

TINY_LOR
TINY_API
TinyRet JsonArray_Encode(JsonArray *thiz, bool pretty);

TINY_LOR
TINY_API
int JsonArray_ToString(JsonArray *thiz, bool pretty, int depth, char *buf, uint32_t length, uint32_t offset);

TINY_LOR
TINY_API
TinyRet JsonArray_AddString(JsonArray *thiz, const char *value);

TINY_LOR
TINY_API
TinyRet JsonArray_AddInteger(JsonArray *thiz, int value);

TINY_LOR
TINY_API
TinyRet JsonArray_AddFloat(JsonArray *thiz, float value);

TINY_LOR
TINY_API
TinyRet JsonArray_AddObject(JsonArray *thiz, JsonObject *value);

TINY_LOR
TINY_API
TinyRet JsonArray_AddArray(JsonArray *thiz, JsonArray *value);

TINY_LOR
TINY_API
TinyRet JsonArray_AddValue(JsonArray *thiz, JsonValue *value);


TINY_END_DECLS

#endif /* __JSON_ARRAY_H__ */