/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   BoolValue.h
*
* @remark
*
*/

#ifndef __BOOL_VALUE_H__
#define __BOOL_VALUE_H__

#include <tiny_lor.h>
#include "common/typedef_api.h"
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef struct _BoolValue
{
    bool            value;
} BoolValue;

TYPEDEF_API
TINY_LOR
TinyRet BoolValue_Set(BoolValue *thiz, bool value);

//TYPEDEF_API
//TINY_LOR
//TinyRet BoolValue_Retrieve(BoolValue *thiz, const char *string);
//
//TYPEDEF_API
//TINY_LOR
//const char * BoolValue_ToString(BoolValue *thiz);


TINY_END_DECLS

#endif /* __BOOL_VALUE_H__ */
