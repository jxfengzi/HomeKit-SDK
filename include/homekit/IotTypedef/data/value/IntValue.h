/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   IntValue.h
 *
 * @remark
 *
 */

#ifndef __INT_VALUE_H__
#define __INT_VALUE_H__

#include <tiny_lor.h>
#include "common/typedef_api.h"
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef struct _IntValue
{
    int32_t             value;
    bool                hasRange;
    struct
    {
        int32_t         max;
        int32_t         min;
        int32_t         step;
        bool            hasStep;
    } range;
} IntValue;

TYPEDEF_API
TINY_LOR
TinyRet IntValue_SetRange(IntValue *thiz, int32_t min, int32_t max, int32_t step);

TYPEDEF_API
TINY_LOR
TinyRet IntValue_Set(IntValue *thiz, int32_t value);


TINY_END_DECLS

#endif /* __INT_VALUE_H__ */
