#include <thing/ThingManager.h>
#include <HapAccessoryImpl.h>
#include "hap/persistence/HapPersistenceImpl.h"
#include "hap/AccessoryCategoryIdentifier.h"
#include "hap/AccessoryHost.h"

#include "esp_common.h"
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define DEMO_WIFI_SSID      "airport-milink"
#define DEMO_WIFI_PASSWORD  "milink123"

ICACHE_FLASH_ATTR
void tiny_print_mem_info(const char *tag, const char *function)
{
    printf("[%s/%s] stack = %d, free heap size: %d\n", tag, function,
      uxTaskGetStackHighWaterMark(NULL), system_get_free_heap_size());
}

ICACHE_FLASH_ATTR
static void print_version_info(void)
{
    printf("HomeKit Lightbulb\n");
    printf("Version 0.1\n");
    printf("Author: ouyang\n");
    printf("Wechat: 178915185\n");
    printf("PIN-CODE: 031-45-154\n");
}

ICACHE_FLASH_ATTR
void print_value(Property *property)
{
    switch (property->data.type)
    {
        case DATATYPE_BOOL:
            printf("value: %s\n", property->data.value.boolValue.value ? "true": "false");
            break;

        case DATATYPE_UINT8:
            printf("value: %d\n", property->data.value.uint8Value.value);
            break;

        case DATATYPE_UINT16:
            printf("value: %d\n", property->data.value.uint16Value.value);
            break;

        case DATATYPE_UINT32:
            printf("value: %d\n", property->data.value.uint32Value.value);
            break;

        case DATATYPE_UINT64:
            printf("value: %ld\n", property->data.value.uint64Value.value);
            break;

        case DATATYPE_INT:
            printf("value: %d\n", property->data.value.intValue.value);
            break;

        case DATATYPE_FLOAT:
            printf("value: %f\n", property->data.value.floatValue.value);
            break;

        case DATATYPE_STRING:
            printf("value: %s\n", property->data.value.stringValue.value);
            break;

        case DATATYPE_TLV8:
            break;

        case DATATYPE_DATA:
            break;

        default:
            break;
    }
}

ICACHE_FLASH_ATTR
static void OnIdentify(void)
{
    printf("OnIdentify\n");
}

ICACHE_FLASH_ATTR
static void OnCharacteristicGet(Property *property)
{
    printf("OnGet: characteristics.name = %s, aid=[%d] iid = [%d]\n", property->type.name, property->aiid, property->iid);

    switch (property->iid)
    {
        // on
        case 9:
            break;

        default:
            break;
    }
}

ICACHE_FLASH_ATTR
static void OnCharacteristicSet(Property *property)
{
    printf("OnSet: characteristics.name = %s, aid=[%d] iid = [%d]\n", property->type.name, property->aiid, property->iid);
    print_value(property);

    switch (property->iid)
    {
        // identify
        case 2:
            OnIdentify();
            break;

        // on
        case 9:
            // property->data.value.boolValue.value;
            break;

        default:
            break;
    }
}

ICACHE_FLASH_ATTR
static void MyAccessoryInitializer(DeviceConfig *thiz, void *ctx)
{
    DeviceConfig_SetIp(thiz, "10.0.1.25");
    DeviceConfig_SetPort(thiz, 9090);
    DeviceConfig_SetName(thiz, "OOO");
    DeviceConfig_SetId(thiz, "18:FE:34:CE:22:15");
    DeviceConfig_SetModelName(thiz, "light");
    DeviceConfig_SetConfigurationNumber(thiz, 2);
    DeviceConfig_SetCurrentStateNumber(thiz, 1);
    DeviceConfig_SetFeatureFlags(thiz, 0);
    DeviceConfig_SetCategoryIdentifier(thiz, ACCESSORY_CATEGORY_OTHER);
    DeviceConfig_SetPinCode(thiz, "031-45-154");
}

ICACHE_FLASH_ATTR
static void _start_accessory(void *pvParameters)
{
    TinyRet ret = TINY_RET_OK;
    DeviceConfig config;
    AccessoryHost *host = NULL;

    print_version_info();

    // 1. init device configuration
    ret = DeviceConfig_Construct(&config);
    if (RET_FAILED(ret))
    {
        printf("DeviceConfig_Construct FAILED\n");
        return;
    }
    DeviceConfig_Initialize(&config, MyAccessoryInitializer, NULL);

    // 2. create AccessoryHost
    host = AccessoryHost_New(&config, OnCharacteristicGet, OnCharacteristicSet, OnIdentify);
    if (host == NULL)
    {
        printf("AccessoryHost_New FAILED\n");
        return;
    }

    // 3. init persistence for accessory
    ret = AccessoryHost_Initialize(host, HapPersistenceImpl_GetInstance());
    if (RET_FAILED(ret))
    {
        printf("AccessoryHost_Initialize FAILED: %d\n", TINY_RET_CODE(ret));
        return;
    }

    // 4. run accessory host
    ret = AccessoryHost_Run(host);
    if (RET_FAILED(ret))
    {
        printf("AccessoryHost_Initialize FAILED: %d\n", TINY_RET_CODE(ret));
        return;
    }

    // 5. destroy AccessoryHost
    AccessoryHost_Delete(host);

    DeviceConfig_Dispose(&config);
}

/******************************************************************************
 * FunctionName : wifi_event_handler_cb
 * Description  : wifi event callback
 * Parameters   : system event
 * Returns      : none
 *******************************************************************************/
ICACHE_FLASH_ATTR
static void wifi_event_handler_cb(System_Event_t * event)
{
    if (event == NULL)
    {
        return;
    }

    switch (event->event_id)
    {
        case EVENT_STAMODE_GOT_IP:
            printf("free heap size %d line %d \n", system_get_free_heap_size(), __LINE__);
            xTaskCreate(_start_accessory, "start_accessory", 1024 * 3, NULL, 4, NULL);
            break;

        default:
            break;
    }

    return;
}


/******************************************************************************
 * FunctionName : wifi_config
 * Description  : wifi_config task
 * Parameters   : task param
 * Returns      : none
 *******************************************************************************/
ICACHE_FLASH_ATTR
static void wifi_config(void *pvParameters)
{
    struct ip_info ip_config;
    struct station_config sta_config;

    memset(&sta_config, 0, sizeof(struct station_config));
    wifi_set_opmode(STATION_MODE);
    memcpy(sta_config.ssid, DEMO_WIFI_SSID, strlen(DEMO_WIFI_SSID));
    memcpy(sta_config.password, DEMO_WIFI_PASSWORD, strlen(DEMO_WIFI_PASSWORD));
    wifi_station_set_config(&sta_config);

    wifi_station_disconnect();
    wifi_station_connect();

    while (1)
    {
        vTaskDelay(10);
    }
}

/******************************************************************************
 * FunctionName : user_rf_cal_sector_set
 * Description  : SDK just reversed 4 sectors, used for rf init data and paramters.
 *                We add this function to force users to set rf cal sector, since
 *                we don't know which sector is free in user's application.
 *                sector map for last several sectors : ABCCC
 *                A : rf cal
 *                B : rf init data
 *                C : sdk parameters
 * Parameters   : none
 * Returns      : rf cal sector
 *******************************************************************************/
uint32 user_rf_cal_sector_set(void)
{
    flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map)
    {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        default:
            rf_cal_sec = 0;
            break;
    }

    return rf_cal_sec;
}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void user_init(void)
{
    printf("SDK version:%s\n", system_get_sdk_version());

    wifi_set_event_handler_cb(wifi_event_handler_cb);
    xTaskCreate(wifi_config, "wfcf", 512, NULL, 4, NULL);
}
