/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   UrnType.h
 *
 * @remark
 *
 */

#ifndef __URN_TYPE_H__
#define __URN_TYPE_H__

#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef enum _UrnType
{
    UNDEFINED   = 0,
    THING       = 1,
    SERVICE     = 2,
    PROPERTY    = 3,
} UrnType;


TINY_END_DECLS

#endif /* __URN_TYPE_H__ */
