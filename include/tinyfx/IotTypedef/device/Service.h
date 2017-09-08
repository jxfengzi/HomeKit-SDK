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
#include "api/iot_api.h"
#include "urn/Urn.h"

TINY_BEGIN_DECLS


struct _Service
{
    uint16_t            aiid;
    uint16_t            iid;
    Urn                 type;
    TinyList            properties;
};

typedef struct _Service Service;

IOT_API
TINY_LOR
Service* Service_New(void);

IOT_API
TINY_LOR
void Service_Delete(Service *thiz);


TINY_END_DECLS

#endif /* __SERVICE_H__ */
