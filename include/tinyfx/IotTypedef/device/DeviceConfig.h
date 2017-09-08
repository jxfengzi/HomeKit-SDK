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
#include "api/iot_api.h"
#include <constraint/typedef_constraint.h>
#include <tiny_lor.h>

TINY_BEGIN_DECLS


#define SRP_salt_LEN            16
#define SRP_v_LEN               384
#define SRP_b_LEN               32
#define SRP_B_LEN               384

typedef struct _SRPPrecomputed
{
    bool        valid;
    uint8_t     s[SRP_salt_LEN];
    uint8_t     v[SRP_v_LEN];
    uint8_t     b[SRP_b_LEN];
    uint8_t     B[SRP_B_LEN];

#if 0
    const char *s;
    const char *v;
    const char *b;
    const char *B;
#endif
} SRPPrecomputed;

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

    /**
     * SRP precomputed values: salt/v/b/B
     */
    SRPPrecomputed      precomputed;
} DeviceConfig;

typedef void (* DeviceConfigurationInitializer)(DeviceConfig *thiz, void *ctx);

//IOT_API DeviceConfig * DeviceConfig_New(void);
//IOT_API void DeviceConfig_Delete(DeviceConfig *thiz);

IOT_API
TINY_LOR
TinyRet DeviceConfig_Construct(DeviceConfig *thiz);

IOT_API
TINY_LOR
void DeviceConfig_Dispose(DeviceConfig *thiz);

IOT_API
TINY_LOR
void DeviceConfig_Initialize(DeviceConfig *thiz, DeviceConfigurationInitializer initializer, void *ctx);

IOT_API
TINY_LOR
void DeviceConfig_Copy(DeviceConfig *dst, DeviceConfig *src);

IOT_API
TINY_LOR
void DeviceConfig_SetIp(DeviceConfig *thiz, const char *ip);

IOT_API
TINY_LOR
void DeviceConfig_SetIpByInt(DeviceConfig *thiz, uint32_t ip);

IOT_API
TINY_LOR
void DeviceConfig_SetPort(DeviceConfig *thiz, uint16_t port);

IOT_API
TINY_LOR
void DeviceConfig_SetName(DeviceConfig *thiz, const char *name);

IOT_API
TINY_LOR
void DeviceConfig_SetId(DeviceConfig *thiz, const char *id);

IOT_API
TINY_LOR
void DeviceConfig_SetIdByInt(DeviceConfig *thiz, const uint8_t *id, uint32_t len);

IOT_API
TINY_LOR
void DeviceConfig_SetModelName(DeviceConfig *thiz, const char *model);

IOT_API
TINY_LOR
void DeviceConfig_SetConfigurationNumber(DeviceConfig *thiz, uint32_t value);

IOT_API
TINY_LOR
void DeviceConfig_SetCurrentStateNumber(DeviceConfig *thiz, uint32_t value);

IOT_API
TINY_LOR
void DeviceConfig_SetFeatureFlags(DeviceConfig *thiz, uint32_t value);

IOT_API
TINY_LOR
void DeviceConfig_SetCategoryIdentifier(DeviceConfig *thiz, uint32_t value);

IOT_API
TINY_LOR
void DeviceConfig_SetPinCode(DeviceConfig *thiz, const char *pin, SRPPrecomputed *precomputed);


TINY_END_DECLS

#endif /* __DEVICE_CONFIG_H__ */
