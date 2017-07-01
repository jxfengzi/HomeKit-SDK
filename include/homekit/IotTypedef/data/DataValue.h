/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   DataValue.h
*
* @remark
*
*/

#ifndef __DATA_VALUE_H__
#define __DATA_VALUE_H__

#include "tiny_base.h"
#include "data/value/BoolValue.h"
#include "data/value/FloatValue.h"
#include "data/value/Uint8Value.h"
#include "data/value/Uint16Value.h"
#include "data/value/Uint32Value.h"
#include "data/value/Uint64Value.h"
#include "data/value/IntValue.h"
#include "data/value/StringValue.h"
#include "data/value/Tlv8Value.h"
#include "data/value/DataBlobValue.h"

TINY_BEGIN_DECLS


typedef union _DataValue
{
    BoolValue           boolValue;
    Uint8Value          uint8Value;
    Uint16Value         uint16Value;
    Uint32Value         uint32Value;
    Uint64Value         uint64Value;
    IntValue            intValue;
    FloatValue          floatValue;
    StringValue         stringValue;
    Tlv8Value           tlv8Value;
    DataBlobValue       dataBlobValue;
} DataValue;


TINY_END_DECLS

#endif /* __DATA_VALUE_H__ */