/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ExampleHandler.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <codec-http/HttpMessage.h>
#include <channel/SocketChannel.h>
#include "ExampleHandler.h"

#include <espressif/c_types.h>
#include <lwip/lwip/sockets.h>

ICACHE_FLASH_ATTR
static TinyRet ExampleHandler_Construct(ChannelHandler *thiz);

ICACHE_FLASH_ATTR
static TinyRet ExampleHandler_Dispose(ChannelHandler *thiz);

ICACHE_FLASH_ATTR
static void ExampleHandler_Delete(ChannelHandler *thiz);

ICACHE_FLASH_ATTR
static bool _channelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, void *data, uint32_t len);

ICACHE_FLASH_ATTR
static void _channelEvent(ChannelHandler *thiz, Channel *channel, void *event);

ICACHE_FLASH_ATTR
ChannelHandler * ExampleHandler(void)
{
    ChannelHandler *thiz = NULL;

    do
    {
        thiz = (ChannelHandler *)malloc(sizeof(ChannelHandler));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(ExampleHandler_Construct(thiz)))
        {
            ExampleHandler_Dispose(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

ICACHE_FLASH_ATTR
static void ExampleHandler_Delete(ChannelHandler *thiz)
{
    printf("ExampleHandler_Delete\n");

    ExampleHandler_Dispose(thiz);
    free(thiz);
}

ICACHE_FLASH_ATTR
static TinyRet ExampleHandler_Construct(ChannelHandler *thiz)
{
    printf("ExampleHandler_Construct\n");

    memset(thiz, 0, sizeof(ChannelHandler));

    strncpy(thiz->name, ExampleHandler_Name, CHANNEL_HANDLER_NAME_LEN);
	thiz->onRemove = ExampleHandler_Delete;
	thiz->inType = DATA_HTTP_MESSAGE;
    thiz->outType = DATA_HTTP_MESSAGE;
    thiz->channelRead = _channelRead;
    thiz->channelWrite = NULL;
    thiz->channelEvent = _channelEvent;

    return TINY_RET_OK;
}

ICACHE_FLASH_ATTR
static TinyRet ExampleHandler_Dispose(ChannelHandler *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(ChannelHandler));

    return TINY_RET_OK;
}

ICACHE_FLASH_ATTR
static bool _channelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, void *data, uint32_t len)
{
    HttpMessage *request = (HttpMessage *)data;
    // HttpMessage response;

    printf("_channelRead: %s %s\n", request->request_line.method, request->request_line.uri);
    printf("write response to: %s:%d\n", channel->remote.socket.ip, channel->remote.socket.address);
    // const char * resp = "HTTP/1.1 200 OK\r\nContent-Type: text/json\r\nContent-Length: 0\r\n\r\n";
    const char * resp = "HTTP/1.1 200 OK\r\nContent-Type: text/json\r\nContent-Length: 0\r\n\r\n";
//    SocketChannel_StartWrite(channel, DATA_HTTP_MESSAGE, resp, strlen(resp));
    lwip_send(channel->fd, resp, strlen(resp), 0);
    Channel_Close(channel);

#if 0
    if (RET_SUCCEEDED(HttpMessage_Construct(&response)))
    {
        response.type = HTTP_RESPONSE;
        HttpMessage_SetVersion(&response, 1, 1);
        HttpMessage_SetResponse(&response, 200, "OK");
        HttpMessage_SetHeader(&response, "Content-Type", "text/json");
        HttpMessage_SetHeaderInteger(&response, "Content-Length", 0);

        SocketChannel_StartWrite(channel, DATA_HTTP_MESSAGE, HttpMessage_GetBytes(&response), HttpMessage_GetBytesSize(&response));

        Channel_Close(channel);
        HttpMessage_Dispose(&response);
    }
#endif

    return true;
}

ICACHE_FLASH_ATTR
static void _channelEvent(ChannelHandler *thiz, Channel *channel, void *event)
{
    printf("_channelEvent: %s\n", channel->id);

    Channel_Close(channel);
}
