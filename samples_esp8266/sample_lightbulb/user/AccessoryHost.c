/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   AccessoryHost.c
 *
 * @remark
 *
 */

#include <device/Device.h>
#include <thing/ThingManager.h>
#include <HapAccessoryImpl.h>
#include "hap/accessories/DeskLamp.h"
#include "hap/AccessoryHost.h"

TINY_LOR
static TinyRet AccessoryHost_Construct(AccessoryHost *thiz,
                                       DeviceConfig *config,
                                       PropertyOnGet onGet,
                                       PropertyOnSet onSet,
                                       DeviceIdentifyListener onIdentify);

TINY_LOR
static void AccessoryHost_Dispose(AccessoryHost *thiz);

struct _AccessoryHost
{
    ThingManager        manager;
    Device            * device;
};

TINY_LOR
AccessoryHost * AccessoryHost_New(DeviceConfig *config,
                                  PropertyOnGet onGet,
                                  PropertyOnSet onSet,
                                  DeviceIdentifyListener onIdentify)
{
    AccessoryHost * thiz = NULL;

    RETURN_VAL_IF_FAIL(config, NULL);

    do
    {
        thiz = (AccessoryHost *)malloc(sizeof(AccessoryHost));
        if (thiz == NULL)
        {
            printf("OUT OF MEMORY!\n");
            break;
        }

        if (RET_FAILED(AccessoryHost_Construct(thiz, config, onGet, onSet, onIdentify)))
        {
            printf("LightbulbOnControl_Construct failed\n");
            AccessoryHost_Delete(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

TINY_LOR
static TinyRet AccessoryHost_Construct(AccessoryHost *thiz,
                                       DeviceConfig *config,
                                       PropertyOnGet onGet,
                                       PropertyOnSet onSet,
                                       DeviceIdentifyListener onIdentify)
{
    TinyRet ret = TINY_RET_OK;

    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    do
    {
        memset(thiz, 0, sizeof(AccessoryHost));

        ret = ThingManager_Construct(&thiz->manager);
        if (RET_FAILED(ret))
        {
            printf("ThingManager_Construct FAILED: %s\n", TINY_RET_CODE(ret));
            break;
        }

        thiz->device = Device_Build(config);
        if (thiz->device == NULL)
        {
            printf("DeviceConfig_Build failed\n");
            ret = TINY_RET_E_CONSTRUCT;
            break;
        }

        thiz->device->identifyListener = onIdentify;
        TinyList_AddTail(&thiz->device->accessories, DeskLamp(onGet, onSet));

        Device_InitializeInstanceID(thiz->device);
    } while (0);

    return ret;
}

TINY_LOR
static void AccessoryHost_Dispose(AccessoryHost *thiz)
{
    RETURN_IF_FAIL(thiz);

    if (thiz->device != NULL)
    {
        Device_Delete(thiz->device);
        thiz->device = NULL;
    }

    ThingManager_Dispose(&thiz->manager);
}

TINY_LOR
void AccessoryHost_Delete(AccessoryHost *thiz)
{
    RETURN_IF_FAIL(thiz);

    AccessoryHost_Dispose(thiz);
    free(thiz);
}

TINY_LOR
TinyRet AccessoryHost_Initialize(AccessoryHost *thiz, HapPersistence *persistence)
{
    return ThingManager_SetRuntimeImpl(&thiz->manager, HapAccessoryImpl_GetInstance(persistence));
}

TINY_LOR
TinyRet AccessoryHost_Run(AccessoryHost *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    return ThingManager_Run(&thiz->manager, thiz->device);
}

TINY_LOR
TinyRet AccessoryHost_Stop(AccessoryHost *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    return ThingManager_Stop(&thiz->manager);
}

TINY_LOR
TinyRet AccessoryHost_SetBoolValue(AccessoryHost *thiz, uint16_t aid, uint16_t iid, bool value)
{
    TinyRet ret = TINY_RET_OK;

    Property *p = Device_GetProperty(thiz->device, aid, iid);
    if (p == NULL)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    ret = Data_SetBoolValue(&p->data, value);
    if (RET_SUCCEEDED(ret))
    {
        p->changed = true;
    }

    return ret;
}

TINY_LOR
TinyRet AccessoryHost_SetUint8Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, uint8_t value)
{
    TinyRet ret = TINY_RET_OK;

    Property *p = Device_GetProperty(thiz->device, aid, iid);
    if (p == NULL)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    ret = Data_SetUint8Value(&p->data, value);
    if (RET_SUCCEEDED(ret))
    {
        p->changed = true;
    }

    return ret;
}

TINY_LOR
TinyRet AccessoryHost_SetUint16Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, uint16_t value)
{
    TinyRet ret = TINY_RET_OK;

    Property *p = Device_GetProperty(thiz->device, aid, iid);
    if (p == NULL)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    ret = Data_SetUint16Value(&p->data, value);
    if (RET_SUCCEEDED(ret))
    {
        p->changed = true;
    }

    return ret;
}

TINY_LOR
TinyRet AccessoryHost_SetUint32Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, uint32_t value)
{
    TinyRet ret = TINY_RET_OK;

    Property *p = Device_GetProperty(thiz->device, aid, iid);
    if (p == NULL)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    ret = Data_SetUint32Value(&p->data, value);
    if (RET_SUCCEEDED(ret))
    {
        p->changed = true;
    }

    return ret;
}

TINY_LOR
TinyRet AccessoryHost_SetUint64Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, uint64_t value)
{
    TinyRet ret = TINY_RET_OK;

    Property *p = Device_GetProperty(thiz->device, aid, iid);
    if (p == NULL)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    ret = Data_SetUint64Value(&p->data, value);
    if (RET_SUCCEEDED(ret))
    {
        p->changed = true;
    }

    return ret;
}

TINY_LOR
TinyRet AccessoryHost_SetIntValue(AccessoryHost *thiz, uint16_t aid, uint16_t iid, int32_t value)
{
    TinyRet ret = TINY_RET_OK;

    Property *p = Device_GetProperty(thiz->device, aid, iid);
    if (p == NULL)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    ret = Data_SetIntValue(&p->data, value);
    if (RET_SUCCEEDED(ret))
    {
        p->changed = true;
    }

    return ret;
}

TINY_LOR
TinyRet AccessoryHost_SetFloatValue(AccessoryHost *thiz, uint16_t aid, uint16_t iid, float value)
{
    TinyRet ret = TINY_RET_OK;

    Property *p = Device_GetProperty(thiz->device, aid, iid);
    if (p == NULL)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    ret = Data_SetFloatValue(&p->data, value);
    if (RET_SUCCEEDED(ret))
    {
        p->changed = true;
    }

    return ret;
}

TINY_LOR
TinyRet AccessoryHost_SetStringValue(AccessoryHost *thiz, uint16_t aid, uint16_t iid, const char * value)
{
    TinyRet ret = TINY_RET_OK;

    Property *p = Device_GetProperty(thiz->device, aid, iid);
    if (p == NULL)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    ret = Data_SetStringValue(&p->data, value);
    if (RET_SUCCEEDED(ret))
    {
        p->changed = true;
    }

    return ret;
}

TINY_LOR
TinyRet AccessoryHost_SetTlv8Value(AccessoryHost *thiz, uint16_t aid, uint16_t iid, const char * value, uint32_t len)
{
    TinyRet ret = TINY_RET_OK;

    Property *p = Device_GetProperty(thiz->device, aid, iid);
    if (p == NULL)
    {
        return TINY_RET_E_ARG_INVALID;
    }

    ret = Data_SetTlv8Value(&p->data, value, len);
    if (RET_SUCCEEDED(ret))
    {
        p->changed = true;
    }

    return ret;
}

TINY_LOR
TinyRet AccessoryHost_SendEvents(AccessoryHost *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, 0);

    return Device_NotifyPropertiesChanged(thiz->device);
}
