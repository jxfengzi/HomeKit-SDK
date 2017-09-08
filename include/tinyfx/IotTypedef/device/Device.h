/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Device.h
 *
 * @remark
 *
 */

#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <controlled/DeviceIdentifyListener.h>
#include "tiny_base.h"
#include "api/iot_api.h"
#include "urn/Urn.h"
#include "DeviceConfig.h"
#include "Property.h"
#include "Service.h"


TINY_BEGIN_DECLS


struct _Device
{
    DeviceConfig                config;
    TinyList                    accessories;
    TinyList                    changedObservers;
    DeviceIdentifyListener      identifyListener;
    void                      * ctx;
};

typedef struct _Device Device;

IOT_API
TINY_LOR
Device* Device_New(void);

IOT_API
TINY_LOR
void Device_Delete(Device *thiz);

IOT_API
TINY_LOR
void Device_InitializeInstanceID(Device *thiz);

IOT_API
TINY_LOR
Device* Device_Build(DeviceConfig *thiz);

IOT_API
TINY_LOR
Property * Device_GetProperty(Device *device, uint16_t aid, uint16_t iid);

IOT_API
TINY_LOR
int Device_NotifyPropertiesChanged(Device *thiz);


TINY_END_DECLS

#endif /* __DEVICE_H__ */