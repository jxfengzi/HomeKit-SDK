/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Tlv8Value.h
 *
 * @remark
 *
 */

#ifndef __TLV8_VALUE_H__
#define __TLV8_VALUE_H__

#include "api/iot_api.h"
#include "tiny_base.h"
#include "Tlv8.h"
#include <TinyList.h>

TINY_BEGIN_DECLS


typedef struct _Tlv8Value
{
    TinyList            values;
    uint8_t           * _bytes;
    uint32_t            _size;
    uint32_t            _available;
} Tlv8Value;

IOT_API
TINY_LOR
TinyRet Tlv8Value_Construct(Tlv8Value *thiz);

IOT_API
TINY_LOR
void Tlv8Value_Dispose(Tlv8Value *thiz);

//IOT_API TinyRet Tlv8Value_Clear(Tlv8Value *thiz);
//IOT_API TinyRet Tlv8Value_Copy(Tlv8Value *thiz, Tlv8Value *other);

IOT_API
TINY_LOR
TinyRet Tlv8Value_Parse(Tlv8Value *thiz, const uint8_t *buf, uint32_t len, bool mergeValue);

IOT_API
TINY_LOR
const uint8_t * Tlv8Value_GetBytes(Tlv8Value *thiz);

IOT_API
TINY_LOR
uint32_t  Tlv8Value_GetBytesSize(Tlv8Value *thiz);

IOT_API
TINY_LOR
Tlv8 * Tlv8Value_Get(Tlv8Value *thiz, uint8_t type);

IOT_API
TINY_LOR
TinyRet Tlv8Value_AddByte(Tlv8Value *thiz, uint8_t type, uint8_t value, bool mergeValue);

IOT_API
TINY_LOR
TinyRet Tlv8Value_AddBytes(Tlv8Value *thiz, uint8_t type, const uint8_t *value, uint32_t length, bool mergeValue);

IOT_API
TINY_LOR
TinyRet Tlv8Value_AddSeparator(Tlv8Value *thiz);


TINY_END_DECLS

#endif /* __TLV8_VALUE_H__ */
