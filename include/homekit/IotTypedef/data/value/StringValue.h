/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   StringValue.h
 *
 * @remark
 *
 */

#ifndef __STRING_VALUE_H__
#define __STRING_VALUE_H__

#include <tiny_lor.h>
#include "common/typedef_api.h"
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef struct _StringValue
{
    char              * value;
    uint32_t            length;
    bool                hasMaxLength;
    uint32_t            maxLength;
} StringValue;

TYPEDEF_API
TINY_LOR
TinyRet StringValue_SetMaxLength(StringValue *thiz, uint32_t length);

TYPEDEF_API
TINY_LOR
TinyRet StringValue_Set(StringValue *thiz, const char *string);

TYPEDEF_API
TINY_LOR
TinyRet StringValue_Clear(StringValue *thiz);

TYPEDEF_API
TINY_LOR
TinyRet StringValue_Copy(StringValue *thiz, StringValue *other);


TINY_END_DECLS

#endif /* __STRING_VALUE_H__ */
