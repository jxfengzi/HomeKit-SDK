/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   FloatValue.h
 *
 * @remark
 *
 */

#ifndef __FLOAT_VALUE_H__
#define __FLOAT_VALUE_H__

#include <tiny_lor.h>
#include "common/typedef_api.h"
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef struct _FloatValue
{
    float               value;
    bool                hasRange;
    struct
    {
        float           max;
        float           min;
        float           step;
        bool            hasStep;
    } range;
} FloatValue;

TYPEDEF_API
TINY_LOR
TinyRet FloatValue_SetRange(FloatValue *thiz, float min, float max, float step);

TYPEDEF_API
TINY_LOR
TinyRet FloatValue_Set(FloatValue *thiz, float value);


TINY_END_DECLS

#endif /* __FLOAT_VALUE_H__ */
