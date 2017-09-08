/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   JsonNumber.h
 *
 * @remark
 *
 */

#ifndef __JSON_NUMBER_H__
#define __JSON_NUMBER_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS


typedef enum _JsonNumberType
{
    JSON_NUMBER_INTEGER  = 0,
    JSON_NUMBER_FLOAT    = 1,
} JsonNumberType;

typedef union _JsonNumberValue
{
    int     intValue;
    float   floatValue;
} JsonNumberValue;

typedef struct _JsonNumber
{
    JsonNumberType      type;
    JsonNumberValue     value;
} JsonNumber;

TINY_LOR
JsonNumber * JsonNumber_NewInteger(int value);

TINY_LOR
JsonNumber * JsonNumber_NewFloat(float value);

TINY_LOR
void JsonNumber_Delete(JsonNumber *thiz);

TINY_LOR
int JsonNumber_ToString(JsonNumber *thiz, char *buf, uint32_t length, uint32_t offset);


TINY_END_DECLS

#endif /* __JSON_NUMBER_H__ */