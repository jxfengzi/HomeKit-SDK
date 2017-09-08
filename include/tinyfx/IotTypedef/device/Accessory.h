/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Accessory.h
 *
 * @remark
 *
 */

#ifndef __ACCESSORY_H__
#define __ACCESSORY_H__

#include "tiny_base.h"
#include "api/iot_api.h"
#include "urn/Urn.h"
#include <TinyList.h>

TINY_BEGIN_DECLS


struct _Accessory
{
    uint16_t            iid;
    TinyList            services;
};

typedef struct _Accessory Accessory;

IOT_API
TINY_LOR
Accessory* Accessory_New(void);

IOT_API
TINY_LOR
void Accessory_Delete(Accessory *thiz);

IOT_API
TINY_LOR
void Accessory_InitializeInstanceID(Accessory *thiz, uint16_t aid);


TINY_END_DECLS

#endif /* __ACCESSORY_H__ */