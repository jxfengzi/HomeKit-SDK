/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   OperationType.h
 *
 * @remark
 *
 */

#ifndef __OPERATION_TYPE_H__
#define __OPERATION_TYPE_H__

#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef enum _OperationType
{
    OPERATION_GET       = 1,
    OPERATION_SET       = 2,
    OPERATION_SUB       = 3,
    OPERATION_UNSUB     = 4,
} OperationType;


TINY_END_DECLS

#endif /* __OPERATION_TYPE_H__ */
