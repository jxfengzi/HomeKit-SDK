/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Unit.h
 *
 * @remark
 *
 */

#ifndef __UNIT_H__
#define __UNIT_H__

#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef enum _Unit
{
    NONE            = 0,
    PERCENTAGE      = 1,
    CELSIUS         = 2,
    LUX             = 3,
    UNITLESS        = 4,
    SECONDS         = 5,
    ARC_DEGREES     = 6,
} Unit;


TINY_END_DECLS

#endif /* __UNIT_H__ */
