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
#include "common/typedef_api.h"
#include "urn/Urn.h"
#include <TinyList.h>

TINY_BEGIN_DECLS


struct _Accessory
{
//    uint16_t            ref;
    uint16_t            iid;
    TinyList            services;
};

typedef struct _Accessory Accessory;

TYPEDEF_API Accessory* Accessory_New(void);
TYPEDEF_API void Accessory_Delete(Accessory *thiz);
TYPEDEF_API void Accessory_InitializeInstanceID(Accessory *thiz, uint16_t aid);

//TYPEDEF_API void Accessory_AddRef(Accessory *thiz);
//TYPEDEF_API void Accessory_Release(Accessory *thiz);


TINY_END_DECLS

#endif /* __ACCESSORY_H__ */