/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   AccessoryHost.h
*
* @remark
*
*/

#ifndef __AccessoryHost_H__
#define __AccessoryHost_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <device/Device.h>
#include <device/DeviceConfig.h>
#include <controlled/PropertyOnControl.h>
#include <controlled/DeviceIdentifyListener.h>
#include <data/Data.h>
#include <HapPersistence.h>

TINY_BEGIN_DECLS


struct _AccessoryHost
{
    ThingManager        manager;
    Device            * device;
};

typedef struct _AccessoryHost AccessoryHost;

TINY_LOR
AccessoryHost * AccessoryHost_New(DeviceConfig *config, PropertyOnGet onGet, PropertyOnSet onSet, DeviceIdentifyListener onIdentify);

TINY_LOR
void AccessoryHost_Delete(AccessoryHost *thiz);

TINY_LOR
TinyRet AccessoryHost_Construct(AccessoryHost *thiz,
                                DeviceConfig *config,
                                PropertyOnGet onGet,
                                PropertyOnSet onSet,
                                DeviceIdentifyListener onIdentify);
TINY_LOR
void AccessoryHost_Dispose(AccessoryHost *thiz);

TINY_LOR
TinyRet AccessoryHost_Initialize(AccessoryHost *thiz, HapPersistence *persistence);

TINY_LOR
TinyRet AccessoryHost_Run(AccessoryHost *thiz);

TINY_LOR
TinyRet AccessoryHost_Stop(AccessoryHost *thiz);

TINY_LOR
TinyRet AccessoryHost_SetBoolValue(AccessoryHost *thiz, uint16_t aid, uint16_t iid, bool value);

TINY_LOR
TinyRet AccessoryHost_SetUint8Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, uint8_t value);

TINY_LOR
TinyRet AccessoryHost_SetUint16Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, uint16_t value);

TINY_LOR
TinyRet AccessoryHost_SetUint32Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, uint32_t value);

TINY_LOR
TinyRet AccessoryHost_SetUint64Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, uint64_t value);

TINY_LOR
TinyRet AccessoryHost_SetIntValue(AccessoryHost *thiz, uint16_t aid, uint16_t iid, int32_t value);

TINY_LOR
TinyRet AccessoryHost_SetFloatValue(AccessoryHost *thiz, uint16_t aid, uint16_t iid, float value);

TINY_LOR
TinyRet AccessoryHost_SetStringValue(AccessoryHost *thiz, uint16_t aid, uint16_t iid, const char * value);

TINY_LOR
TinyRet AccessoryHost_SetTlv8Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, const char * value, uint32_t len);

TINY_LOR
int AccessoryHost_SendEvents(AccessoryHost *thiz);


TINY_END_DECLS

#endif /* __AccessoryHost_H__ */
