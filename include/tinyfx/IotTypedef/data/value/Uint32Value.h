/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Uint32Value.h
 *
 * @remark
 *
 */

#ifndef __UINT32_VALUE_H__
#define __UINT32_VALUE_H__

#include <tiny_lor.h>
#include "api/iot_api.h"
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef struct _Uint32Value
{
    uint32_t            value;
    bool                hasRange;
    struct
    {
        uint32_t        max;
        uint32_t        min;
        uint32_t        step;
        bool            hasStep;
    } range;
} Uint32Value;

IOT_API
TINY_LOR
TinyRet Uint32Value_SetRange(Uint32Value *thiz, uint32_t min, uint32_t max, uint32_t step);

IOT_API
TINY_LOR
TinyRet Uint32Value_Set(Uint32Value *thiz, uint32_t value);


TINY_END_DECLS

#endif /* __UINT32_VALUE_H__ */
