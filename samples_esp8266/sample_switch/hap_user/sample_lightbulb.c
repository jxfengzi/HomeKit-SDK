#include <thing/ThingManager.h>
#include <HapAccessoryImpl.h>
#include "hap/persistence/HapPersistenceImpl.h"
#include "hap/AccessoryCategoryIdentifier.h"
#include "hap/AccessoryHost.h"
#include "hap/wdc/Wdc.h"
#include "hap/wdc/WdcInfo.h"

#include "esp_common.h"
#include "gpio.h"

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static WdcInfo *wdcInfo = NULL;

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

// GPIO12
#if 1
#define LED_IO_NUM   12
#define LED_IO_PIN   GPIO_Pin_12
#else
#define LED_IO_NUM   8
#define LED_IO_PIN   GPIO_Pin_8
#endif

ICACHE_FLASH_ATTR
static int get_gpio(void)
{
#if 1
    GPIO_ConfigTypeDef cfg;
    cfg.GPIO_IntrType = GPIO_PIN_INTR_NEGEDGE;
    cfg.GPIO_Mode = GPIO_Mode_Input;
    cfg.GPIO_Pin = LED_IO_PIN;
    cfg.GPIO_Pullup = GPIO_PullUp_EN;
    gpio_config(&cfg);

    return GPIO_INPUT_GET(LED_IO_NUM);
#else
    return GPIO_INPUT_GET(LED_IO_NUM);
#endif
}

ICACHE_FLASH_ATTR
static void set_gpio(int value)
{
    printf("[ TURN %s ] \n", value == 1 ? "ON" : "OFF");

#if 1
    // PW
    GPIO_ConfigTypeDef cfg;
    cfg.GPIO_IntrType = GPIO_PIN_INTR_DISABLE;
    cfg.GPIO_Mode = GPIO_Mode_Output;
    cfg.GPIO_Pin = LED_IO_PIN;
    cfg.GPIO_Pullup = GPIO_PullUp_DIS;
    gpio_config(&cfg);

    GPIO_OUTPUT_SET(LED_IO_NUM, value);

#else
    GPIO_OUTPUT_SET(LED_IO_NUM, value);
#endif
}

ICACHE_FLASH_ATTR
static void OnCharacteristicGet(Property *property)
{
    printf("OnGet: characteristics.name = %s, aid=[%d] iid = [%d]\n", property->type.name, property->aiid, property->iid);

    switch (property->iid)
    {
        // on
        case 9:
            property->data.value.boolValue.value = (get_gpio() == 1);
            printf("[ SWITCH STATUS ] %s\n", property->data.value.boolValue.value ? "ON" : "OFF");
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
            set_gpio(property->data.value.boolValue.value ? 1 : 0);
            break;

        default:
            break;
    }
}

//ICACHE_FLASH_ATTR

ICACHE_RODATA_ATTR
static SRPPrecomputed precomputed =
        {
                .valid = true,
                .s = {0xe1, 0x9c, 0x69, 0x12, 0xa9, 0x19, 0x9e, 0x39, 0xab, 0x8c, 0x71, 0xad, 0x4f, 0xbe, 0x39, 0xb1},
                .v = {0x27, 0x18, 0x19, 0x37, 0x42, 0xc3, 0xcb, 0x64, 0xe3, 0xac, 0xc4, 0x36, 0x7e, 0x8e, 0x5e, 0xa4,
                      0x37, 0x0e, 0x27, 0x36, 0x8b, 0x56, 0x9b, 0xcb, 0xdc, 0xfd, 0x41, 0x66, 0x66, 0xf2, 0xd7, 0xb0,
                      0x53, 0xf9, 0xc8, 0xaa, 0x04, 0xeb, 0x11, 0xf8, 0x6c, 0xef, 0x47, 0xf2, 0x1f, 0xfd, 0xf3, 0x98,
                      0x5f, 0x75, 0x1c, 0x3c, 0xf3, 0x00, 0xfb, 0x31, 0x05, 0x2e, 0x74, 0x05, 0x44, 0xcd, 0xc6, 0xb4,
                      0xd1, 0x84, 0x17, 0xc8, 0x9c, 0x82, 0xa7, 0xf4, 0xb3, 0x03, 0xb1, 0xa9, 0xbe, 0x0d, 0x07, 0x64,
                      0x36, 0x90, 0xab, 0xd6, 0x94, 0xfd, 0x76, 0xd4, 0xed, 0x6b, 0x16, 0xac, 0x21, 0xe3, 0x99, 0x81,
                      0x65, 0x80, 0x60, 0xeb, 0x00, 0x68, 0x19, 0x2f, 0xde, 0x53, 0x4b, 0xb9, 0x1c, 0x19, 0x7f, 0xfa,
                      0x0f, 0x84, 0xeb, 0xa0, 0x26, 0xda, 0x22, 0x6e, 0xa9, 0x17, 0xe3, 0x5b, 0x1d, 0x02, 0x0f, 0xdf,
                      0xec, 0x0b, 0x5b, 0xd2, 0x78, 0x52, 0x0f, 0x34, 0x95, 0xe8, 0x79, 0xe7, 0xaf, 0x0c, 0x88, 0x4b,
                      0xab, 0xee, 0x8a, 0xc4, 0xbe, 0xed, 0x79, 0xc6, 0xe4, 0xa4, 0xba, 0x72, 0xde, 0x9e, 0xf2, 0x3d,
                      0x5e, 0xcb, 0x3b, 0xfa, 0x85, 0xb2, 0x7c, 0xd9, 0xde, 0x4d, 0xa9, 0xd2, 0x85, 0x6d, 0x9f, 0x86,
                      0xac, 0x3a, 0xde, 0x0e, 0xb2, 0xaa, 0x80, 0xb6, 0xdf, 0x96, 0xa5, 0xa2, 0x63, 0x82, 0xaf, 0xf6,
                      0xc6, 0x66, 0x22, 0x23, 0x75, 0x3b, 0xf6, 0xe9, 0x5d, 0x09, 0x0a, 0x54, 0x64, 0x44, 0xb9, 0x21,
                      0xd9, 0xe4, 0x5e, 0xa6, 0xf9, 0xa5, 0x45, 0x7a, 0x53, 0x9b, 0x01, 0x60, 0x27, 0x6f, 0xd7, 0x7e,
                      0xad, 0x41, 0xbb, 0x3d, 0xe0, 0x4b, 0xfa, 0x73, 0x20, 0xac, 0x78, 0xc7, 0x2a, 0x6f, 0x3a, 0xab,
                      0x16, 0x8b, 0x7e, 0x23, 0x8a, 0xd2, 0xa4, 0x0e, 0x9f, 0x81, 0xef, 0xf6, 0x46, 0x56, 0xa3, 0x9a,
                      0xc5, 0x3a, 0x6d, 0xff, 0x05, 0x90, 0x36, 0x9c, 0xd6, 0xff, 0xdc, 0x7b, 0x40, 0x88, 0x21, 0xf5,
                      0x26, 0x4c, 0xa2, 0x65, 0x54, 0xd1, 0xf6, 0x68, 0xe8, 0xc0, 0x98, 0xf0, 0x17, 0x4e, 0xa6, 0xed,
                      0x44, 0x13, 0x42, 0x9a, 0xc3, 0x60, 0x15, 0x36, 0x06, 0x4c, 0x02, 0xa2, 0xa5, 0x22, 0xd5, 0x87,
                      0x73, 0xa0, 0x3f, 0x1f, 0xf4, 0xcc, 0x38, 0xcd, 0xd2, 0xe9, 0x1c, 0x32, 0xc7, 0x7a, 0x71, 0x66,
                      0x8e, 0xa1, 0xd1, 0x5f, 0x7b, 0x93, 0xf8, 0xd1, 0x2c, 0x01, 0xd9, 0xca, 0xa9, 0x82, 0xce, 0x50,
                      0x11, 0x6b, 0xcc, 0x1d, 0x1f, 0xd9, 0xf5, 0xa6, 0x10, 0x30, 0xec, 0x6c, 0x5c, 0x35, 0xa2, 0x04,
                      0x7f, 0x91, 0xc5, 0xf1, 0x14, 0xad, 0x13, 0x92, 0xbb, 0x3c, 0xe7, 0xd2, 0x0d, 0x9c, 0x5e, 0x2b,
                      0x36, 0xec, 0x3d, 0x91, 0x1c, 0xa8, 0xa3, 0xf5, 0x88, 0xcc, 0x26, 0xe3, 0xca, 0x73, 0x79, 0x2d},
                .b = {0xb7, 0x18, 0x9b, 0x1e, 0x85, 0xa3, 0x02, 0xf5, 0x1d, 0x5e, 0x73, 0x2b, 0x89, 0x52, 0x3b, 0x9d,
                      0x29, 0x2a, 0xc4, 0x86, 0xd6, 0x55, 0x6c, 0xf0, 0xc7, 0x59, 0x05, 0x3d, 0x60, 0x05, 0x86, 0x17},
                .B = {0x24, 0xb0, 0x28, 0xeb, 0x7c, 0x6a, 0xd9, 0x6f, 0xb0, 0xf7, 0x38, 0x9e, 0x3e, 0xa1, 0x57, 0x1d,
                      0x46, 0x95, 0xd5, 0xd5, 0x8a, 0xa1, 0x44, 0xce, 0xb3, 0x98, 0x4f, 0x4e, 0x31, 0x6d, 0x4c, 0x98,
                      0xc1, 0xd8, 0xd4, 0x4e, 0xeb, 0x84, 0x85, 0x92, 0x7f, 0x89, 0x95, 0x34, 0x64, 0xc3, 0xa4, 0xb2,
                      0x4e, 0x73, 0xa8, 0x52, 0xda, 0x0b, 0xcc, 0x3b, 0xc6, 0xf2, 0x51, 0x3c, 0xde, 0xfa, 0xb9, 0xef,
                      0x82, 0x45, 0xef, 0x31, 0xef, 0xe4, 0xa6, 0xe3, 0x6b, 0xf1, 0x83, 0x4b, 0x94, 0xa9, 0xf5, 0xfb,
                      0x16, 0x86, 0x0e, 0xe4, 0x99, 0x47, 0x62, 0x4b, 0x15, 0x9b, 0xad, 0x68, 0xc3, 0xe1, 0x30, 0x91,
                      0xc5, 0xbd, 0x22, 0x5f, 0xc5, 0x98, 0x32, 0x42, 0xe9, 0xa8, 0x27, 0x63, 0xb5, 0xf8, 0x38, 0x9f,
                      0x13, 0x71, 0x90, 0x46, 0x5b, 0xb8, 0x0a, 0xa9, 0x8d, 0x8f, 0x0c, 0xf5, 0xfa, 0x4c, 0x26, 0x9a,
                      0xd2, 0xe5, 0xca, 0xa7, 0xd7, 0xcb, 0x02, 0xf5, 0xe7, 0xef, 0x8e, 0x32, 0x80, 0xde, 0xec, 0xed,
                      0xe6, 0x28, 0x2f, 0x07, 0x6f, 0x06, 0x38, 0x8d, 0x00, 0xe8, 0xc4, 0xe3, 0xf6, 0xf7, 0x61, 0x92,
                      0xdd, 0x03, 0xd1, 0x48, 0x9f, 0x2c, 0xf3, 0xf4, 0xb3, 0xfb, 0x55, 0x95, 0x31, 0xb6, 0x48, 0x92,
                      0x24, 0x22, 0xc5, 0x0b, 0x56, 0x42, 0x42, 0xb5, 0xaa, 0x59, 0x34, 0x8f, 0xde, 0x0e, 0xeb, 0x30,
                      0xb6, 0xf8, 0xb7, 0xf6, 0x72, 0x45, 0xd7, 0xae, 0xb2, 0xfa, 0xe6, 0x43, 0x54, 0x79, 0xa8, 0x8f,
                      0xd0, 0x6b, 0xe9, 0x9a, 0x31, 0x64, 0x04, 0x50, 0x6d, 0xb8, 0x4c, 0x1e, 0x51, 0x9c, 0x35, 0xc1,
                      0xda, 0x6f, 0x47, 0x93, 0xa4, 0x75, 0x67, 0xe6, 0xde, 0x1c, 0x69, 0xe7, 0x14, 0x67, 0x27, 0x67,
                      0x3d, 0xe3, 0xa0, 0x3b, 0x1d, 0x19, 0x05, 0x8f, 0x7d, 0xdc, 0x8c, 0xcf, 0x91, 0xde, 0x7f, 0x94,
                      0xae, 0x68, 0xb2, 0x98, 0x09, 0xec, 0x18, 0x32, 0x76, 0x89, 0xe9, 0xe6, 0x29, 0xad, 0xf7, 0x11,
                      0x98, 0xcd, 0xaa, 0x5f, 0x46, 0x1b, 0xfa, 0x24, 0xa1, 0x5d, 0xcf, 0xdb, 0xdf, 0x93, 0x44, 0x23,
                      0x68, 0x71, 0x8a, 0x6f, 0x13, 0x77, 0xda, 0xc0, 0xa3, 0xc0, 0x02, 0x6f, 0x97, 0xba, 0xaa, 0x4a,
                      0xeb, 0xac, 0x02, 0xf6, 0xf3, 0x94, 0xd9, 0xb9, 0xaf, 0xe8, 0x2f, 0x5b, 0x4b, 0xc6, 0x63, 0xe2,
                      0xbe, 0x3c, 0xc7, 0xc0, 0x70, 0xfa, 0xce, 0xf9, 0x40, 0xb1, 0xce, 0x4a, 0x97, 0xca, 0x18, 0xbf,
                      0x3b, 0x92, 0x5e, 0x94, 0xcf, 0x9a, 0xb4, 0x0a, 0xf6, 0x3b, 0x0d, 0xbb, 0xb9, 0x2c, 0x3c, 0xed,
                      0xbd, 0xe3, 0x4f, 0x78, 0x52, 0xa3, 0xaf, 0xf2, 0x59, 0xa2, 0x99, 0x03, 0xb8, 0x37, 0xab, 0xda,
                      0xbf, 0x64, 0xd4, 0xf5, 0x2f, 0xaf, 0xec, 0x5b, 0x10, 0x8a, 0x99, 0x96, 0xc4, 0xc3, 0xb6, 0xbf},
        };

ICACHE_FLASH_ATTR
static void MyAccessoryInitializer(DeviceConfig *thiz, void *ctx)
{
    char mac[32];
    struct ip_info info;

    memset(mac, 0, 32);
    memset(&info, 0, sizeof(struct ip_info));

    if (wifi_get_macaddr(STATION_IF, mac))
    {
        DeviceConfig_SetIdByInt(thiz, mac, 32);
    }
    else
    {
        DeviceConfig_SetId(thiz, "18:FE:34:CE:22:15");
    }

    if (wifi_get_ip_info(STATION_IF, &info))
    {
        DeviceConfig_SetIpByInt(thiz, info.ip.addr);
    }
    else
    {
        DeviceConfig_SetIp(thiz, "10.0.1.47");
    }

    DeviceConfig_SetPort(thiz, 9090);
    DeviceConfig_SetName(thiz, "Hello");
    DeviceConfig_SetModelName(thiz, "light");
    DeviceConfig_SetConfigurationNumber(thiz, 2);
    DeviceConfig_SetCurrentStateNumber(thiz, 1);
    DeviceConfig_SetFeatureFlags(thiz, 0);
    DeviceConfig_SetCategoryIdentifier(thiz, ACCESSORY_CATEGORY_OTHER);
    DeviceConfig_SetPinCode(thiz, "031-45-154", &precomputed);
}

ICACHE_FLASH_ATTR
static void _start_accessory(void *pvParameters)
{
    TinyRet ret = TINY_RET_OK;
    AccessoryHost *host;
    DeviceConfig config;

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
    static int retry = 0;

    if (event == NULL)
    {
        return;
    }

    printf("event: %d\n", event->event_id);

    switch (event->event_id)
    {
        case EVENT_STAMODE_DISCONNECTED:
            if (retry > 3)
            {
                hap_wdc_init();
            }
            else
            {
                retry ++;
            }
            break;

        case EVENT_STAMODE_GOT_IP:
            free(wdcInfo);
            wdcInfo = NULL;
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
    memcpy(sta_config.ssid, wdcInfo->ssid, strlen(wdcInfo->ssid));
    memcpy(sta_config.password, wdcInfo->password, strlen(wdcInfo->password));
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

    /**
     * 读取参数
     *   1. 如果有AP信息, 开始连接AP. 如果连接失败, 则进入AP模式.
     *   2. 如果没有AP, 进入AP模式. 如果收到配置请求, 写入AP信息后重启.
     */
    wdcInfo = (WdcInfo *)malloc(sizeof(WdcInfo));

    if (WdcInfo_Read(wdcInfo))
    {
        printf("ssid: %s\n", wdcInfo->ssid);
        printf("password: %s\n", wdcInfo->password);

        wifi_set_event_handler_cb(wifi_event_handler_cb);
        xTaskCreate(wifi_config, "wifi", 512, NULL, 4, NULL);
    }
    else
    {
        hap_wdc_init();
    }
}
