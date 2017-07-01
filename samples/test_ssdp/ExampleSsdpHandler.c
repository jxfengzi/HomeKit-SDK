/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ExampleSsdpHandler.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <codec-http/HttpMessage.h>
#include <channel/SocketChannel.h>
#include "ExampleSsdpHandler.h"

static TinyRet ExampleSsdpHandler_Construct(ChannelHandler *thiz);
static TinyRet ExampleSsdpHandler_Dispose(ChannelHandler *thiz);
static void ExampleSsdpHandler_Delete(ChannelHandler *thiz);
static bool _channelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, void *data, uint32_t len);
static void _channelEvent(ChannelHandler *thiz, Channel *channel, void *event);

ChannelHandler * ExampleSsdpHandler(void)
{
    ChannelHandler *thiz = NULL;

    do
    {
        thiz = (ChannelHandler *)malloc(sizeof(ChannelHandler));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(ExampleSsdpHandler_Construct(thiz)))
        {
            ExampleSsdpHandler_Dispose(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

static void ExampleSsdpHandler_Delete(ChannelHandler *thiz)
{
    printf("ExampleSsdpHandler_Delete\n");

    ExampleSsdpHandler_Dispose(thiz);
    free(thiz);
}

static TinyRet ExampleSsdpHandler_Construct(ChannelHandler *thiz)
{
    printf("ExampleSsdpHandler_Construct\n");

    memset(thiz, 0, sizeof(ChannelHandler));

    strncpy(thiz->name, ExampleSsdpHandler_Name, CHANNEL_HANDLER_NAME_LEN);
	thiz->onRemove = ExampleSsdpHandler_Delete;
	thiz->inType = DATA_HTTP_MESSAGE;
    thiz->outType = DATA_HTTP_MESSAGE;
    thiz->channelRead = _channelRead;
    thiz->channelWrite = NULL;
    thiz->channelEvent = _channelEvent;

    return TINY_RET_OK;
}

static TinyRet ExampleSsdpHandler_Dispose(ChannelHandler *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(ChannelHandler));

    return TINY_RET_OK;
}

static bool _channelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, void *data, uint32_t len)
{
    HttpMessage *request = (HttpMessage *)data;
    HttpMessage response;

    printf("_channelRead: %d\n", request->content_length);

//    if (RET_SUCCEEDED(HttpMessage_Construct(&response)))
//    {
//        HttpMessage_SetType(&response, HTTP_RESPONSE);
//        HttpMessage_SetVersion(&response, 1, 1);
//        HttpMessage_SetResponse(&response, 200, "OK");
//        HttpMessage_SetHeader(&response, "Content-Type", "text/json");
//        HttpMessage_SetHeaderInteger(&response, "Content-Length", 0);
//
//        SocketChannel_StartWrite(channel, DATA_HTTP_MESSAGE, HttpMessage_GetBytes(&response), HttpMessage_GetBytesSize(&response));
//
//        Channel_Close(channel);
//        HttpMessage_Dispose(&response);
//    }

    return true;
}

static void _channelEvent(ChannelHandler *thiz, Channel *channel, void *event)
{
    printf("_channelEvent: %s\n", channel->id);

    Channel_Close(channel);
}
