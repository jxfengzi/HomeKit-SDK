/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DataType.h
 *
 * @remark
 *
 */

#ifndef __DATA_TYPE_H__
#define __DATA_TYPE_H__

#include <tiny_lor.h>
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef enum _DataType
{
    DATATYPE_UNDEFINED  = 0,
    DATATYPE_BOOL       = 1,
    DATATYPE_UINT8      = 2,
    DATATYPE_UINT16     = 3,
    DATATYPE_UINT32     = 4,
    DATATYPE_UINT64     = 5,
    DATATYPE_INT        = 6,
    DATATYPE_FLOAT      = 7,
    DATATYPE_STRING     = 8,

    /* Base64-encoded set of one or more TLV8's */
    DATATYPE_TLV8       = 9,

    /* Base64-encoded data blob, Maximum length is 2,097,152 bytes unless overridden by the 'maxDataLen' property */
    DATATYPE_DATA       = 10,
} DataType;

TINY_LOR
const char * DataType_GetName(DataType type);


TINY_END_DECLS

#endif /* __DATA_TYPE_H__ */
