/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   JsonObject.h
 *
 * @remark
 *
 */

#ifndef __JSON_OBJECT_H__
#define __JSON_OBJECT_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <TinyMap.h>
#include "JsonValue.h"

TINY_BEGIN_DECLS


typedef struct _JsonObject
{
    TinyMap         data;
    char          * string;
    uint32_t        size;
} JsonObject;

TINY_LOR
TINY_API
JsonObject * JsonObject_New(void);

TINY_LOR
TINY_API
JsonObject * JsonObject_NewString(const char *string);

TINY_LOR
TINY_API
void JsonObject_Delete(JsonObject *thiz);

TINY_LOR
TINY_API
TinyRet JsonObject_Construct(JsonObject *thiz);

TINY_LOR
TINY_API
void JsonObject_Dispose(JsonObject *thiz);

TINY_LOR
TINY_API
TinyRet JsonObject_Encode(JsonObject *thiz, bool pretty);

TINY_LOR
TINY_API
int JsonObject_ToString(JsonObject *thiz, bool pretty, int depth, char *buf, uint32_t length, uint32_t offset);

TINY_LOR
TINY_API
bool JsonObject_ContainsKey(JsonObject *thiz, const char *key);

TINY_LOR
TINY_API
JsonValue * JsonObject_GetValue(JsonObject *thiz, const char *key);

TINY_LOR
TINY_API
TinyRet JsonObject_PutString(JsonObject *thiz, const char *key, const char *value);

TINY_LOR
TINY_API
TinyRet JsonObject_PutInteger(JsonObject *thiz, const char *key, int value);

TINY_LOR
TINY_API
TinyRet JsonObject_PutFloat(JsonObject *thiz, const char *key, float value);

TINY_LOR
TINY_API
TinyRet JsonObject_PutBoolean(JsonObject *thiz, const char *key, bool value);

TINY_LOR
TINY_API
TinyRet JsonObject_PutNull(JsonObject *thiz, const char *key);

TINY_LOR
TINY_API
TinyRet JsonObject_PutObject(JsonObject *thiz, const char *key, JsonObject *value);

TINY_LOR
TINY_API
TinyRet JsonObject_PutArray(JsonObject *thiz, const char *key, JsonArray *value);

TINY_LOR
TINY_API
TinyRet JsonObject_PutNumber(JsonObject *thiz, const char *key, JsonNumber *value);

TINY_LOR
TINY_API
TinyRet JsonObject_PutValue(JsonObject *thiz, const char *key, JsonValue *value);


TINY_END_DECLS

#endif /* __JSON_OBJECT_H__ */