#include <bootstrap/Bootstrap.h>
#include <channel/stream/StreamClientChannel.h>
#include <channel/stream/StreamClientChannelContext.h>
#include <channel/SocketChannel.h>
#include <channel/ChannelIdleStateHandler.h>
#include <codec-http/HttpMessageCodec.h>
#include "MyClientHandler.h"

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
static void HttpClientInitializer(Channel *channel, void *ctx)
{
    printf("HttpServerInitializer: %s\n", channel->id);
    SocketChannel_AddLast(channel, ChannelIdleStateHandler(3, 4, 5));
    SocketChannel_AddLast(channel, HttpMessageCodec());
    SocketChannel_AddLast(channel, MyClientHandler());
}

static void http_server_task(void *pvParameters)
{
    TinyRet ret = TINY_RET_OK;
    Channel *client = NULL;
    Bootstrap sb;

    printf("Start HTTP Client\n");

    // new TCP Server
    client = StreamClientChannel_New();

    ret = StreamClientChannel_Initialize(client, HttpClientInitializer, NULL);
    if (RET_FAILED(ret))
    {
        printf("StreamClientChannel_Initialize failed: %d\n", TINY_RET_CODE(ret));
        return;
    }

    ret = StreamClientChannel_Connect(client, "10.0.1.9", 8080, 3000);
    if (RET_FAILED(ret))
    {
        printf("StreamClientChannel_Connect failed: %d\n", TINY_RET_CODE(ret));
        return;
    }

    // Starting Bootstrap
    ret = Bootstrap_Construct(&sb);
    if (RET_FAILED(ret))
    {
        printf("Bootstrap_Construct failed: %d\n", TINY_RET_CODE(ret));
        return;
    }

    ret = Bootstrap_AddChannel(&sb, client);
    if (RET_FAILED(ret))
    {
        printf("Bootstrap_AddChannel failed: %d\n", TINY_RET_CODE(ret));
        return;
    }

    printf("Bootstrap running\n");

    ret = Bootstrap_Sync(&sb);
    if (RET_FAILED(ret))
    {
        printf("Bootstrap_Sync failed: %d\n", TINY_RET_CODE(ret));
        return;
    }

    printf("Bootstrap shutdown\n");

    Bootstrap_Shutdown(&sb);
    Bootstrap_Dispose(&sb);
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
            xTaskCreate(http_server_task, "http_server", 1024 * 4, NULL, 4, NULL);
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
