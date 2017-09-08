/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   Data.h
*
* @remark
*
*/

#ifndef __DATA_H__
#define __DATA_H__

#include "tiny_base.h"
#include "api/iot_api.h"
#include "DataType.h"
#include "DataValue.h"


TINY_BEGIN_DECLS

typedef struct _Data
{
    DataType        type;
    DataValue       value;
} Data;

IOT_API
TINY_LOR
TinyRet Data_Construct(Data *thiz);

IOT_API
TINY_LOR
void Data_Dispose(Data *thiz);

IOT_API
TINY_LOR
TinyRet Data_SetMaxLength(Data *thiz, uint32_t length);

IOT_API
TINY_LOR
TinyRet Data_SetUint8ValueRange(Data *thiz, uint8_t min, uint8_t max, uint8_t step);

IOT_API
TINY_LOR
TinyRet Data_SetUint16ValueRange(Data *thiz, uint16_t min, uint16_t max, uint16_t step);

IOT_API
TINY_LOR
TinyRet Data_SetUint32ValueRange(Data *thiz, uint32_t min, uint32_t max, uint32_t step);

IOT_API
TINY_LOR
TinyRet Data_SetUint64ValueRange(Data *thiz, uint64_t min, uint64_t max, uint64_t step);

IOT_API
TINY_LOR
TinyRet Data_SetIntValueRange(Data *thiz, int32_t min, int32_t max, int32_t step);

IOT_API
TINY_LOR
TinyRet Data_SetFloatValueRange(Data *thiz, float min, float max, float step);

IOT_API
TINY_LOR
TinyRet Data_SetBoolValue(Data *thiz, bool value);

IOT_API
TINY_LOR
TinyRet Data_SetUint8Value(Data *thiz, uint8_t value);

IOT_API
TINY_LOR
TinyRet Data_SetUint16Value(Data *thiz, uint16_t value);

IOT_API
TINY_LOR
TinyRet Data_SetUint32Value(Data *thiz, uint32_t value);

IOT_API
TINY_LOR
TinyRet Data_SetUint64Value(Data *thiz, uint64_t value);

IOT_API
TINY_LOR
TinyRet Data_SetIntValue(Data *thiz, int32_t value);

IOT_API
TINY_LOR
TinyRet Data_SetFloatValue(Data *thiz, float value);

IOT_API
TINY_LOR
TinyRet Data_SetStringValue(Data *thiz, const char * value);

IOT_API
TINY_LOR
TinyRet Data_SetTlv8Value(Data *thiz, const char * value, uint32_t len);

IOT_API
TINY_LOR
TinyRet Data_SetDataValue(Data *thiz, const char * value);

IOT_API
TINY_LOR
bool Data_GetBoolValue(Data *thiz);

IOT_API
TINY_LOR
uint8_t Data_GetUint8Value(Data *thiz);

IOT_API
TINY_LOR
uint16_t Data_GetUint16Value(Data *thiz);

IOT_API
TINY_LOR
uint32_t  Data_GetUint32Value(Data *thiz);

IOT_API
TINY_LOR
uint64_t  Data_GetUint64Value(Data *thiz);

IOT_API
TINY_LOR
int32_t  Data_GetIntValue(Data *thiz);

IOT_API
TINY_LOR
float Data_GetFloatValue(Data *thiz);

IOT_API
TINY_LOR
const char * Data_GetStringValue(Data *thiz);


TINY_END_DECLS

#endif /* __DATA_H__ */