/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeviceConfig.h
 *
 * @remark
 *
 */

#ifndef __DEVICE_CONFIG_H__
#define __DEVICE_CONFIG_H__

#include "tiny_base.h"
#include "common/typedef_api.h"
#include <constraint/typedef_constraint.h>

TINY_BEGIN_DECLS


typedef struct _DeviceConfig
{
    char                ip[TINY_IP_LEN + 1];
    uint16_t            port;

    char                pin[DEVICE_PIN_LENGTH + 1];
    char                id[DEVICE_ID_LENGTH + 1];       // id
    char                name[DEVICE_NAME_LENGTH + 1];   // name
    char                model[DEVICE_MODEL_LENGTH + 1]; // md

    /**
     * Current configuration number. Required.
     * Updates only when an accessory, service, or characteristic is
     * added or removed on the accessory server.
     * This must have a range of 1 - 4294967295 and wrap to 1 when it overflows.
     * This value must persist across reboots, power cycles, etc.
     */
    uint32_t            configurationNumber;        // c#

    /**
     * Accessory Categories
     * 1.   Other
     * 2.   Bridge
     * 3.   Fan
     * 4.   Garage
     * 5.   Lightbulb
     * 6.   Door Lock
     * 7.   Outlet
     * 8.   Switch
     * 9.   Thermostat
     * 10.  Sensor
     * 11.  Security System
     * 12.  Door
     * 13.  Window
     * 14.  Window Covering
     * 15.  Programmable Switch
     * 16.  Range Extender
     * 17+  Reserved
     */
    uint32_t            categoryIdentifier;         // ci

    /**
     * Feature flags.
     * Mask         Bit     Description
     * -------------------------------------------------------------------------------------
     * 0x01         1       Supports HAP Pairing. This flag is required for all accessories.
     * 0x02 - 0x80  2-8     Reserved.
     */
    uint32_t            featureFlags;               // ff

    /**
     * Current state number. Required.
     * This must have a value of "1".
     */
    uint32_t            stateNumber;                // s#

    /**
     * Status flags.
     * Mask         Bit     Description
     * -------------------------------------------------------------------------------------
     * 0x01         1       Accessory has not been paired with any controllers.
     * 0x02         2       Accessory has not been configured to join a Wi-Fi network.
     * 0x04         3       A problem has been detected on the accessory.
     * 0x08 - 0x80  4-8     Reserved.
     */
    uint32_t            statusFlags;                // sf

    /**
     * Protocol version string <major>.<minor>. Required if value is not "1.0"
     */
    uint32_t            protocolVersion;
} DeviceConfig;

typedef void (* DeviceConfigurationInitializer)(DeviceConfig *thiz, void *ctx);

//TYPEDEF_API DeviceConfig * DeviceConfig_New(void);
//TYPEDEF_API void DeviceConfig_Delete(DeviceConfig *thiz);
TYPEDEF_API TinyRet DeviceConfig_Construct(DeviceConfig *thiz);
TYPEDEF_API void DeviceConfig_Dispose(DeviceConfig *thiz);

TINY_INLINE
void DeviceConfig_Initialize(DeviceConfig *thiz, DeviceConfigurationInitializer initializer, void *ctx)
{
    initializer(thiz, ctx);
}

TINY_INLINE
void DeviceConfig_Copy(DeviceConfig *dst, DeviceConfig *src)
{
    if (dst != src)
    {
        strncpy(dst->ip, src->ip, TINY_IP_LEN);
        strncpy(dst->pin, src->pin, DEVICE_PIN_LENGTH);
        strncpy(dst->id, src->id, DEVICE_ID_LENGTH);
        strncpy(dst->name, src->name, DEVICE_NAME_LENGTH);
        strncpy(dst->model, src->model, DEVICE_MODEL_LENGTH);
        dst->port = src->port;
        dst->configurationNumber = src->configurationNumber;
        dst->categoryIdentifier = src->categoryIdentifier;
        dst->featureFlags = src->featureFlags;
        dst->stateNumber = src->stateNumber;
        dst->statusFlags = src->statusFlags;
        dst->protocolVersion = src->protocolVersion;
    }
}

TINY_INLINE
void DeviceConfig_SetIp(DeviceConfig *thiz, const char *ip)
{
    strncpy(thiz->ip, ip, TINY_IP_LEN);
}

TINY_INLINE
void DeviceConfig_SetPort(DeviceConfig *thiz, uint16_t port)
{
    thiz->port = port;
}

TINY_INLINE
void DeviceConfig_SetName(DeviceConfig *thiz, const char *name)
{
    strncpy(thiz->name, name, DEVICE_NAME_LENGTH);
}

TINY_INLINE
void DeviceConfig_SetId(DeviceConfig *thiz, const char *id)
{
    strncpy(thiz->id, id, DEVICE_ID_LENGTH);
}

TINY_INLINE
void DeviceConfig_SetModelName(DeviceConfig *thiz, const char *model)
{
    strncpy(thiz->model, model, DEVICE_MODEL_LENGTH);
}

TINY_INLINE
void DeviceConfig_SetConfigurationNumber(DeviceConfig *thiz, uint32_t value)
{
    thiz->configurationNumber = value;
}

TINY_INLINE
void DeviceConfig_SetCurrentStateNumber(DeviceConfig *thiz, uint32_t value)
{
    thiz->stateNumber = value;
}

TINY_INLINE
void DeviceConfig_SetFeatureFlags(DeviceConfig *thiz, uint32_t value)
{
    thiz->featureFlags = value;
}

TINY_INLINE
void DeviceConfig_SetCategoryIdentifier(DeviceConfig *thiz, uint32_t value)
{
    thiz->categoryIdentifier = value;
}

TINY_INLINE
void DeviceConfig_SetPinCode(DeviceConfig *thiz, const char *pin)
{
    strncpy(thiz->pin, pin, DEVICE_PIN_LENGTH);
}



TINY_END_DECLS

#endif /* __DEVICE_CONFIG_H__ */
