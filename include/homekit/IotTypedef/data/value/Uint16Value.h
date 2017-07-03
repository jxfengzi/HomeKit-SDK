/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Uint16Value.h
 *
 * @remark
 *
 */

#ifndef __UINT16_VALUE_H__
#define __UINT16_VALUE_H__

#include <tiny_lor.h>
#include "common/typedef_api.h"
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef struct _Uint16Value
{
    uint16_t            value;
    bool                hasRange;
    struct
    {
        uint16_t        max;
        uint16_t        min;
        uint16_t        step;
        bool            hasStep;
    } range;
} Uint16Value;

TYPEDEF_API
TINY_LOR
TinyRet Uint16Value_SetRange(Uint16Value *thiz, uint16_t min, uint16_t max, uint16_t step);

TYPEDEF_API
TINY_LOR
TinyRet Uint16Value_Set(Uint16Value *thiz, uint16_t value);


TINY_END_DECLS

#endif /* __UINT16_VALUE_H__ */
