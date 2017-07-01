/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Service.h
 *
 * @remark
 *
 */

#ifndef __SERVICE_H__
#define __SERVICE_H__

#include <TinyList.h>
#include "tiny_base.h"
#include "common/typedef_api.h"
#include "urn/Urn.h"

TINY_BEGIN_DECLS


struct _Service
{
//    uint16_t            ref;
    uint16_t            aiid;
    uint16_t            iid;
    Urn                 type;
    TinyList            properties;
};

typedef struct _Service Service;

TYPEDEF_API Service* Service_New(void);
TYPEDEF_API void Service_Delete(Service *thiz);
//TYPEDEF_API void Service_AddRef(Service *thiz);
//TYPEDEF_API void Service_Release(Service *thiz);


TINY_END_DECLS

#endif /* __SERVICE_H__ */
