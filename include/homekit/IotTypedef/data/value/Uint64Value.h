/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Uint64Value.h
 *
 * @remark
 *
 */

#ifndef __UINT64_VALUE_H__
#define __UINT64_VALUE_H__

#include <tiny_lor.h>
#include "common/typedef_api.h"
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef struct _Uint64Value
{
    uint64_t            value;
    bool                hasRange;
    struct
    {
        uint64_t        max;
        uint64_t        min;
        uint64_t        step;
        bool            hasStep;
    } range;
} Uint64Value;

TYPEDEF_API
TINY_LOR
TinyRet Uint64Value_SetRange(Uint64Value *thiz, uint64_t min, uint64_t max, uint64_t step);

TYPEDEF_API
TINY_LOR
TinyRet Uint64Value_Set(Uint64Value *thiz, uint64_t value);


TINY_END_DECLS

#endif /* __UINT64_VALUE_H__ */
