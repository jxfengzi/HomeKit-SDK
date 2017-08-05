#include "hap/wac/Wac.h"
#include "esp_common.h"

#if 0
#include <tiny_log.h>
#include <bootstrap/Bootstrap.h>
#include <channel/stream/StreamServerChannel.h>
#include <channel/stream/StreamServerChannelContext.h>
#include <channel/SocketChannel.h>
#include <channel/ChannelIdleStateHandler.h>
#include <codec-http/HttpMessageCodec.h>
#include "ExampleHandler.h"
#endif

#define SOFT_AP_SSID      "HomeKit"

static void wifi_handle_event_cb(System_Event_t *evt)
{
    printf("event %x\n", evt->event_id);

    switch (evt->event_id) {
        case EVENT_STAMODE_CONNECTED:
            printf("connect to ssid %s, channel %d\n", evt->event_info.connected.ssid, evt->event_info.connected.channel);
            break;

        case EVENT_STAMODE_DISCONNECTED:
            printf("disconnect from ssid %s, reason %d\n", evt->event_info.disconnected.ssid, evt->event_info.disconnected.reason);
            break;

        case EVENT_STAMODE_AUTHMODE_CHANGE:
            printf("mode: %d -> %d\n", evt->event_info.auth_change.old_mode, evt->event_info.auth_change.new_mode);
            break;

        case EVENT_STAMODE_GOT_IP:
            printf("ip:" IPSTR ",mask:" IPSTR ",gw:" IPSTR, IP2STR(&evt->event_info.got_ip.ip), IP2STR(&evt->event_info.got_ip.mask), IP2STR(&evt->event_info.got_ip.gw));
            printf("\n");
            break;

        case EVENT_SOFTAPMODE_STACONNECTED:
            printf("station: " MACSTR "join, AID = %d\n", MAC2STR(evt->event_info.sta_connected.mac), evt->event_info.sta_connected.aid);
            break;

        case EVENT_SOFTAPMODE_STADISCONNECTED:
            printf("station: " MACSTR "leave, AID = %d\n", MAC2STR(evt->event_info.sta_disconnected.mac), evt->event_info.sta_disconnected.aid);
            break;

        default:
            break;
    }
}

ICACHE_FLASH_ATTR
static void soft_ap_init(void)
{
    char mac[32];
    memset(mac, 0, 32);

    if (wifi_get_macaddr(STATION_IF, mac))
    {
        printf("WIFI MAC -> %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    }

    wifi_set_event_handler_cb(wifi_handle_event_cb);

    wifi_set_opmode(SOFTAP_MODE);
    struct softap_config *config = (struct softap_config *) zalloc(sizeof(struct softap_config)); // initialization
    wifi_softap_get_config(config); // Get soft-AP config first.
    sprintf(config->ssid, SOFT_AP_SSID);
    // sprintf(config->password, SOFT_AP_PASSWORD);
    config->authmode = AUTH_OPEN;
    config->ssid_len = 0; // or its actual SSID length
    config->max_connection = 4;
    wifi_softap_set_config(config); // Set ESP8266 soft-AP config
    free(config);
    struct station_info * station = wifi_softap_get_station_info();
    while (station) {
        printf("bssid : MACSTR, ip : IPSTR/n", MAC2STR(station->bssid), IP2STR(&station->ip));
        station = STAILQ_NEXT(station, next);
    }

    wifi_softap_free_station_info(); // Free it by calling functionss
    wifi_softap_dhcps_stop(); // disable soft-AP DHCP server
    struct ip_info info;
    IP4_ADDR(&info.ip, 192, 168, 5, 1); // set IP
    IP4_ADDR(&info.gw, 192, 168, 5, 1); // set gateway
    IP4_ADDR(&info.netmask, 255, 255, 255, 0); // set netmask
    wifi_set_ip_info(SOFTAP_IF, &info);
    struct dhcps_lease dhcp_lease;
    IP4_ADDR(&dhcp_lease.start_ip, 192, 168, 5, 100);
    IP4_ADDR(&dhcp_lease.end_ip, 192, 168, 5, 105);
    wifi_softap_set_dhcps_lease(&dhcp_lease);
    wifi_softap_dhcps_start(); // enable soft-AP DHCP server
}

void hap_wac_init()
{
    soft_ap_init();
}

#if 0
static void HttpServerInitializer(Channel *channel, void *ctx)
{
    printf("HttpServerInitializer: %s\n", channel->id);
    SocketChannel_AddLast(channel, HttpMessageCodec());
    SocketChannel_AddLast(channel, ExampleHandler());
}

static TinyRet init_http_server(Channel *server, uint16_t port)
{
    TinyRet ret = TINY_RET_OK;

    StreamServerChannel_Initialize(server, HttpServerInitializer, NULL);

    do
    {
        ret = SocketChannel_Open(server, TYPE_TCP_SERVER);
        if (RET_FAILED(ret))
        {
            printf("SocketChannel_Open failed: %d\n", TINY_RET_CODE(ret));
            break;
        }

        ret = SocketChannel_Bind(server, port, false);
        if (RET_FAILED(ret))
        {
            printf("SocketChannel_Bind failed: %d\n", TINY_RET_CODE(ret));
            break;
        }

        ret = SocketChannel_SetBlock(server, false);
        if (RET_FAILED(ret))
        {
            printf("SocketChannel_SetBlock failed: %d\n", TINY_RET_CODE(ret));
            break;
        }

        ret = SocketChannel_Listen(server, ((StreamServerChannelContext *)server->ctx)->maxConnections);
        if (RET_FAILED(ret))
        {
            printf("SocketChannel_Listen failed: %d\n", TINY_RET_CODE(ret));
            break;
        }
    } while (0);

    return ret;
}

int main()
{
    TinyRet ret = TINY_RET_OK;
    Channel *server1 = NULL;
//    Channel *server2 = NULL;
    Bootstrap sb;

    tiny_socket_initialize();

    // new TCP Server
    server1 = StreamServerChannel_New(6);
    ret = init_http_server(server1, 9091);
    if (RET_FAILED(ret))
    {
        printf("init_http_server 1 failed: %d\n", TINY_RET_CODE(ret));
        return 0;
    }

    // new TCP Server
//    server2 = StreamServerChannel_New(2);
//    ret = init_http_server(server1, 9092);
//    if (RET_FAILED(ret))
//    {
//        printf("init_http_server 2 failed: %s\n", tiny_ret_to_str(ret));
//        return 0;
//    }

    // Starting Bootstrap
    ret = Bootstrap_Construct(&sb);
    if (RET_FAILED(ret))
    {
        printf("Bootstrap_Construct failed: %d\n", TINY_RET_CODE(ret));
        return 0;
    }

    ret = Bootstrap_AddChannel(&sb, server1);
    if (RET_FAILED(ret))
    {
        printf("Bootstrap_AddChannel failed: %d\n", TINY_RET_CODE(ret));
        return 0;
    }

//    ret = Bootstrap_AddChannel(&sb, server2);
//    if (RET_FAILED(ret))
//    {
//        printf("Bootstrap_AddChannel failed: %s\n", tiny_ret_to_str(ret));
//        return 0;
//    }

    ret = Bootstrap_Sync(&sb);
    if (RET_FAILED(ret))
    {
        printf("Bootstrap_Sync failed: %d\n", TINY_RET_CODE(ret));
        return 0;
    }

    ret = Bootstrap_Shutdown(&sb);
    if (RET_FAILED(ret))
    {
        printf("Bootstrap_Shutdown failed: %d\n", TINY_RET_CODE(ret));
        return 0;
    }

    Bootstrap_Dispose(&sb);

    tiny_socket_finalize();

    return 0;
}
#endif
