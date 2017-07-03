/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ThingManager.h
 *
 * @remark
 *
 */

#ifndef __THING_MANAGER_H__
#define __THING_MANAGER_H__

#include "tiny_base.h"
#include "thing_api.h"
#include "ThingRuntime.h"
#include <device/Device.h>

TINY_BEGIN_DECLS


struct _ThingManager
{
    bool                    started;
    ThingRuntime            runtime;
};

typedef struct _ThingManager ThingManager;

//THING_API
//TINY_LOR
//ThingManager * ThingManager_New(void);
//
//THING_API
//TINY_LOR
//void ThingManager_Delete(ThingManager *thiz);

THING_API
TINY_LOR
TinyRet ThingManager_Construct(ThingManager *thiz);

THING_API
TINY_LOR
void ThingManager_Dispose(ThingManager *thiz);

THING_API
TINY_LOR
TinyRet ThingManager_SetRuntimeImpl(ThingManager *thiz, ThingRuntime *impl);

THING_API
TINY_LOR
TinyRet ThingManager_Run(ThingManager *thiz, Device *device);

THING_API
TINY_LOR
TinyRet ThingManager_Stop(ThingManager *thiz);



TINY_END_DECLS

#endif /* __THING_MANAGER_H__ */
