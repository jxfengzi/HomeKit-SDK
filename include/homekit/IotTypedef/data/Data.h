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
#include "common/typedef_api.h"
#include "DataType.h"
#include "DataValue.h"


TINY_BEGIN_DECLS

typedef struct _Data
{
    DataType        type;
    DataValue       value;
} Data;

TYPEDEF_API TinyRet Data_Construct(Data *thiz);
TYPEDEF_API void Data_Dispose(Data *thiz);

#if 0
TYPEDEF_API void Data_Copy(Data *dst, Data *src);
#endif

TYPEDEF_API TinyRet Data_SetMaxLength(Data *thiz, uint32_t length);
TYPEDEF_API TinyRet Data_SetUint8ValueRange(Data *thiz, uint8_t min, uint8_t max, uint8_t step);
TYPEDEF_API TinyRet Data_SetUint16ValueRange(Data *thiz, uint16_t min, uint16_t max, uint16_t step);
TYPEDEF_API TinyRet Data_SetUint32ValueRange(Data *thiz, uint32_t min, uint32_t max, uint32_t step);
TYPEDEF_API TinyRet Data_SetUint64ValueRange(Data *thiz, uint64_t min, uint64_t max, uint64_t step);
TYPEDEF_API TinyRet Data_SetIntValueRange(Data *thiz, int32_t min, int32_t max, int32_t step);
TYPEDEF_API TinyRet Data_SetFloatValueRange(Data *thiz, float min, float max, float step);

#if 0
TYPEDEF_API TinyRet Data_GetValue(Data *thiz, char *value, uint32_t len);
TYPEDEF_API TinyRet Data_SetValue(Data *thiz, const char *value);
#endif

TYPEDEF_API TinyRet Data_SetBoolValue(Data *thiz, bool value);
TYPEDEF_API TinyRet Data_SetUint8Value(Data *thiz, uint8_t value);
TYPEDEF_API TinyRet Data_SetUint16Value(Data *thiz, uint16_t value);
TYPEDEF_API TinyRet Data_SetUint32Value(Data *thiz, uint32_t value);
TYPEDEF_API TinyRet Data_SetUint64Value(Data *thiz, uint64_t value);
TYPEDEF_API TinyRet Data_SetIntValue(Data *thiz, int32_t value);
TYPEDEF_API TinyRet Data_SetFloatValue(Data *thiz, float value);
TYPEDEF_API TinyRet Data_SetStringValue(Data *thiz, const char * value);
TYPEDEF_API TinyRet Data_SetTlv8Value(Data *thiz, const char * value, uint32_t len);
TYPEDEF_API TinyRet Data_SetDataValue(Data *thiz, const char * value);

TYPEDEF_API bool Data_GetBoolValue(Data *thiz);
TYPEDEF_API uint8_t Data_GetUint8Value(Data *thiz);
TYPEDEF_API uint16_t Data_GetUint16Value(Data *thiz);
TYPEDEF_API uint32_t  Data_GetUint32Value(Data *thiz);
TYPEDEF_API uint64_t  Data_GetUint64Value(Data *thiz);
TYPEDEF_API int32_t  Data_GetIntValue(Data *thiz);
TYPEDEF_API float Data_GetFloatValue(Data *thiz);
TYPEDEF_API const char * Data_GetStringValue(Data *thiz);

#if 0
TYPEDEF_API const char * Data_GetTlv8Value(Data *thiz);
TYPEDEF_API const char * Data_GetDataValue(Data *thiz);
#endif


TINY_END_DECLS

#endif /* __DATA_H__ */
