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
#include <device/DeviceConfig.h>
#include <controlled/PropertyOnControl.h>
#include <controlled/DeviceIdentifyListener.h>
#include <data/Data.h>
#include <HapPersistence.h>

TINY_BEGIN_DECLS


struct _AccessoryHost;
typedef struct _AccessoryHost AccessoryHost;

AccessoryHost * AccessoryHost_New(DeviceConfig *config, PropertyOnGet onGet, PropertyOnSet onSet, DeviceIdentifyListener onIdentify);
void AccessoryHost_Delete(AccessoryHost *thiz);

TinyRet AccessoryHost_Initialize(AccessoryHost *thiz, HapPersistence *persistence);
TinyRet AccessoryHost_Run(AccessoryHost *thiz);
TinyRet AccessoryHost_Stop(AccessoryHost *thiz);

TinyRet AccessoryHost_SetBoolValue(AccessoryHost *thiz, uint16_t aid, uint16_t iid, bool value);
TinyRet AccessoryHost_SetUint8Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, uint8_t value);
TinyRet AccessoryHost_SetUint16Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, uint16_t value);
TinyRet AccessoryHost_SetUint32Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, uint32_t value);
TinyRet AccessoryHost_SetUint64Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, uint64_t value);
TinyRet AccessoryHost_SetIntValue(AccessoryHost *thiz, uint16_t aid, uint16_t iid, int32_t value);
TinyRet AccessoryHost_SetFloatValue(AccessoryHost *thiz, uint16_t aid, uint16_t iid, float value);
TinyRet AccessoryHost_SetStringValue(AccessoryHost *thiz, uint16_t aid, uint16_t iid, const char * value);
TinyRet AccessoryHost_SetTlv8Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, const char * value, uint32_t len);

int AccessoryHost_SendEvents(AccessoryHost *thiz);


TINY_END_DECLS

#endif /* __AccessoryHost_H__ */