/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   example_registry.c
 *
 * @remark
 *
 */

#include <bootstrap/Bootstrap.h>
#include <channel/multicast/MulticastChannel.h>
#include <channel/SocketChannel.h>
#include <codec/DnsMessageCodec.h>
#include <MdnsHandler.h>
#include <MdnsConstant.h>

#include "esp_common.h"

//#include <time.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <lwip/lwip/sys.h>

#define DEMO_WIFI_SSID      "airport-milink"
#define DEMO_WIFI_PASSWORD  "milink123"

// os_timer_t sntp_read_timer;
//
// ICACHE_FLASH_ATTR
// static void sntp_read_timer_callback(void *arg)
// {
//     uint32_t time = sntp_get_current_timestamp();
//     os_printf("time:%d\r\n",time);
//     os_printf("date:%s\r\n",sntp_get_real_time(time));
// }
//
// ICACHE_FLASH_ATTR
// static void my_sntp_init(void)
// {
//     sntp_setservername(0,"0.cn.pool.ntp.org");
//     sntp_setservername(1,"1.cn.pool.ntp.org");
//     sntp_setservername(2,"2.cn.pool.ntp.org");
//     sntp_init();
//
//     os_timer_disarm(&sntp_read_timer);
//     os_timer_setfn(&sntp_read_timer, sntp_read_timer_callback , NULL);
//     os_timer_arm(&sntp_read_timer,5000,1);
// }

ICACHE_FLASH_ATTR
void tiny_print_stack_info(const char *tag, const char *function)
{
    unsigned portBASE_TYPE uxHighWaterMark;
    uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
    printf("[%s/%s] stack = %d]\n", tag, function, uxHighWaterMark);
}

ICACHE_FLASH_ATTR
static void MdnsInitializer(Channel *channel, void *ctx)
{
    ChannelHandler *handler = MdnsHandler();
    MdnsHandler_Register(handler, (ServiceInfo *) ctx);

    printf("MdnsInitializer\n");

    SocketChannel_AddLast(channel, DnsMessageCodec());
    SocketChannel_AddLast(channel, handler);
}

ICACHE_FLASH_ATTR
static void _start_registry(void *pvParameters)
{
    int i = 0;
    Channel *mdns = NULL;
    Bootstrap sb;
    ServiceInfo info;
    uint16_t port = 8080;

    tiny_print_stack_info("registry", "_start_registry");

    ServiceInfo_Construct(&info);
    ServiceInfo_Initialize(&info, "hello", SERVICE_TYPE_HAP, "10.0.1.25", 8080);
    TinyMap_Insert(&info.txt, "pv", "1.0");                 // protocol version
    TinyMap_Insert(&info.txt, "sf", "1");                   // discoverable ? "1" : "0"
    TinyMap_Insert(&info.txt, "id", "AA:BB:CC:00:11:22");
    TinyMap_Insert(&info.txt, "md", "test");
    TinyMap_Insert(&info.txt, "c#", "2");                   // configurationNumber
    TinyMap_Insert(&info.txt, "s#", "1");                   // currentStateNumber
    TinyMap_Insert(&info.txt, "ff", "0");                   // featureFlags
    TinyMap_Insert(&info.txt, "ci", "8");                   // switch

    mdns = MulticastChannel_New();
    if (mdns == NULL)
    {
        printf("MulticastChannel_New failed\n");
        return;
    }

    MulticastChannel_Initialize(mdns, MdnsInitializer, &info);

    if (RET_FAILED(MulticastChannel_Join(mdns, "10.0.1.25", MDNS_GROUP, MDNS_PORT, false)))
    {
        printf("MulticastChannel_Join failed\n");
    }

    if (RET_FAILED(Bootstrap_Construct(&sb)))
    {
        printf("Bootstrap_Construct failed\n");
        return;
    }

    if (RET_FAILED(Bootstrap_AddChannel(&sb, mdns)))
    {
        printf("Bootstrap_AddChannel failed\n");
        return;
    }

    if (RET_FAILED(Bootstrap_Sync(&sb)))
    {
        printf("Bootstrap_Sync failed\n");
        return;
    }

#if 0
    Bootstrap_Shutdown(&sb);
    Bootstrap_Dispose(&sb);
    ServiceInfo_Dispose(&info);
#endif

    for (i = 0; i < 300; i++)
    {
        sys_msleep(1000 * 1);
        printf("hello\n");
    }
}

/******************************************************************************
 * FunctionName : wifi_event_handler_cb
 * Description  : wifi event callback
 * Parameters   : system event
 * Returns      : none
 *******************************************************************************/
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
            xTaskCreate(_start_registry, "start_registry", 1024 * 4, NULL, 4, NULL);
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
