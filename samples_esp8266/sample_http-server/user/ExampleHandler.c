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
static bool _channelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len);

ICACHE_FLASH_ATTR
static void _channelEvent(ChannelHandler *thiz, Channel *channel, ChannelTimer *timer);

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
static bool _channelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    HttpMessage *request = (HttpMessage *)data;

    printf("_channelRead: %s %s\n", request->request_line.method, request->request_line.uri);
    printf("write response to: %s\n", channel->id);

#if 0

    const char * resp = "HTTP/1.1 200 OK\r\nContent-Type: text/json\r\nContent-Length: 0\r\n\r\n";
    lwip_send(channel->fd, resp, strlen(resp), 0);
    Channel_Close(channel);

#else
    HttpMessage response;

    if (RET_SUCCEEDED(HttpMessage_Construct(&response)))
    {
        HttpMessage_SetResponse(&response, 200, "OK");
        HttpMessage_SetVersion(&response, 1, 1);

        HttpHeader_Set(&response.header, "Content-Type", "text/json");
        HttpHeader_SetInteger(&response.header, "Content-Length", 0);

        SocketChannel_StartWrite(channel,
             DATA_HTTP_MESSAGE,
             HttpMessage_GetBytesWithoutContent(&response),
              HttpMessage_GetBytesSizeWithoutContent(&response));

        Channel_Close(channel);
        HttpMessage_Dispose(&response);
    }
#endif

    return true;
}

ICACHE_FLASH_ATTR
static void _channelEvent(ChannelHandler *thiz, Channel *channel, ChannelTimer *timer)
{
    printf("_channelEvent: %s\n", channel->id);

    Channel_Close(channel);
}
