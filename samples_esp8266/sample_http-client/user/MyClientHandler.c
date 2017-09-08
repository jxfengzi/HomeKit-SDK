/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   MyClientHandler.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_malloc.h>
#include <tiny_log.h>
#include <codec-http/HttpMessage.h>
#include <channel/SocketChannel.h>
#include "MyClientHandler.h"

#define TAG "MyClientHandler"

static TinyRet MyClientHandler_Construct(ChannelHandler *thiz);
static TinyRet MyClientHandler_Dispose(ChannelHandler *thiz);
static void MyClientHandler_Delete(ChannelHandler *thiz);
static void _channelActive(ChannelHandler *thiz, Channel *channel);
static bool _channelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len);
static void _channelEvent(ChannelHandler *thiz, Channel *channel, ChannelTimer *timer);

ChannelHandler * MyClientHandler(void)
{
    ChannelHandler *thiz = NULL;

    do
    {
        thiz = (ChannelHandler *)tiny_malloc(sizeof(ChannelHandler));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(MyClientHandler_Construct(thiz)))
        {
            MyClientHandler_Dispose(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

static void MyClientHandler_Delete(ChannelHandler *thiz)
{
    LOG_D(TAG, "MyClientHandler_Delete");

    MyClientHandler_Dispose(thiz);
    tiny_free(thiz);
}

static TinyRet MyClientHandler_Construct(ChannelHandler *thiz)
{
    LOG_D(TAG, "MyClientHandler_Construct");

    memset(thiz, 0, sizeof(ChannelHandler));

    strncpy(thiz->name, MyClientHandler_Name, CHANNEL_HANDLER_NAME_LEN);
	thiz->onRemove = MyClientHandler_Delete;
	thiz->inType = DATA_HTTP_MESSAGE;
    thiz->outType = DATA_HTTP_MESSAGE;
    thiz->channelRead = _channelRead;
    thiz->channelWrite = NULL;
    thiz->channelEvent = _channelEvent;
    thiz->channelActive = _channelActive;

    return TINY_RET_OK;
}

static TinyRet MyClientHandler_Dispose(ChannelHandler *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(ChannelHandler));

    return TINY_RET_OK;
}

static void _channelActive(ChannelHandler *thiz, Channel *channel)
{
    HttpMessage request;

    RETURN_IF_FAIL(thiz);
    RETURN_IF_FAIL(channel);

    LOG_D(TAG, "_channelActive");

    if (RET_SUCCEEDED(HttpMessage_Construct(&request)))
    {
        HttpMessage_SetRequest(&request, "GET", "http://10.0.1.9:8080/api/v1/devices");
        HttpMessage_SetVersion(&request, 1, 1);

        HttpHeader_Set(&request.header, "App-Id", "9947163763053218");
        HttpHeader_Set(&request.header, "Access-Token", "SJgbGdtgU3Ybg2kG-dOYWs1k9BBzlBITlDFso-Ib5E7by7jTtV3CUQ0jaS0Io4UsTUeGif1fDO9wwRG1LMxQEZJkEnc6nq0IPw4FrG735Ho");

        SocketChannel_StartWrite(channel, DATA_RAW, HttpMessage_GetBytesWithoutContent(&request), HttpMessage_GetBytesSizeWithoutContent(&request));

        HttpMessage_Dispose(&request);
    }
}

static bool _channelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    HttpMessage *response = (HttpMessage *)data;

    LOG_D(TAG, "_channelRead: %d %s", response->status_line.code, response->status_line.status);

    printf("content length: %d\n", response->content.buf_size);
    printf("content: %s\n", response->content.buf);


    //    if (RET_SUCCEEDED(HttpMessage_Construct(&response)))
//    {
//        HttpMessage_SetResponse(&response, 200, "OK");
//        HttpMessage_SetVersion(&response, 1, 1);
//
//        HttpHeader_Set(&response.header, "Content-Type", "text/json");
//        HttpHeader_SetInteger(&response.header, "Content-Length", 0);
//
//        SocketChannel_StartWrite(channel, DATA_RAW, HttpMessage_GetBytesWithoutContent(&response), HttpMessage_GetBytesSizeWithoutContent(&response));
//
//		if (response.content.buf != NULL)
//		{
//			SocketChannel_StartWrite(channel, DATA_RAW, response.content.buf, response.content.buf_size);
//		}
//
//        Channel_Close(channel);
//        HttpMessage_Dispose(&response);
//    }

//    Channel_Close(channel);

    return true;
}

static void _channelEvent(ChannelHandler *thiz, Channel *channel, ChannelTimer *timer)
{
    LOG_E(TAG, "_channelEvent: %s", channel->id);

    switch (timer->type)
    {
        case CHANNEL_TIMER_READER:
            LOG_E(TAG, "IDLE_READER");
            break;

        case CHANNEL_TIMER_WRITER:
            LOG_E(TAG, "IDLE_WRITER");
            break;

        case CHANNEL_TIMER_ALL:
            LOG_E(TAG, "IDLE_ALL");
            break;
    }

//    printf("connection is timeout, close the connection\n");
//    Channel_Close(channel);
}