/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DataBlobValue.h
 *
 * @remark
 *
 */

#ifndef __DATA_BLOB_VALUE_H__
#define __DATA_BLOB_VALUE_H__

#include "common/typedef_api.h"
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef struct _DataBlobValue
{
    char          * value;
    uint32_t        length;
} DataBlobValue;

TYPEDEF_API
TINY_LOR
TinyRet DataBlobValue_Set(DataBlobValue *thiz, const char *dataBlob);

TYPEDEF_API
TINY_LOR
TinyRet DataBlobValue_Clear(DataBlobValue *thiz);

TYPEDEF_API
TINY_LOR
TinyRet DataBlobValue_Copy(DataBlobValue *thiz, DataBlobValue *other);


TINY_END_DECLS

#endif /* __DATA_BLOB_VALUE_H__ */
