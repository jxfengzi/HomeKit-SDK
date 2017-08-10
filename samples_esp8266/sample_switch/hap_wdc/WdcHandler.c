/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   WdcHandler.c
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#include <tiny_malloc.h>
#include <codec-http/HttpMessage.h>
#include <channel/SocketChannel.h>
#include "WdcHandler.h"
#include "hap/wdc/WdcInfo.h"

ICACHE_FLASH_ATTR
static TinyRet WdcHandler_Construct(ChannelHandler *thiz);

ICACHE_FLASH_ATTR
static TinyRet WdcHandler_Dispose(ChannelHandler *thiz);

ICACHE_FLASH_ATTR
static void WdcHandler_Delete(ChannelHandler *thiz);

ICACHE_FLASH_ATTR
static bool _channelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len);

ICACHE_FLASH_ATTR
static void _channelEvent(ChannelHandler *thiz, Channel *channel, void *event);

ICACHE_FLASH_ATTR
ChannelHandler * WdcHandler(void)
{
    ChannelHandler *thiz = NULL;

    do
    {
        thiz = (ChannelHandler *)tiny_malloc(sizeof(ChannelHandler));
        if (thiz == NULL)
        {
            break;
        }

        if (RET_FAILED(WdcHandler_Construct(thiz)))
        {
            WdcHandler_Dispose(thiz);
            thiz = NULL;
            break;
        }
    } while (0);

    return thiz;
}

ICACHE_FLASH_ATTR
static void WdcHandler_Delete(ChannelHandler *thiz)
{
    printf("WdcHandler_Delete\n");

    WdcHandler_Dispose(thiz);
    tiny_free(thiz);
}

ICACHE_FLASH_ATTR
static TinyRet WdcHandler_Construct(ChannelHandler *thiz)
{
    printf("WdcHandler_Construct\n");

    memset(thiz, 0, sizeof(ChannelHandler));

    strncpy(thiz->name, WdcHandler_Name, CHANNEL_HANDLER_NAME_LEN);
	thiz->onRemove = WdcHandler_Delete;
	thiz->inType = DATA_HTTP_MESSAGE;
    thiz->outType = DATA_HTTP_MESSAGE;
    thiz->channelRead = _channelRead;
    thiz->channelWrite = NULL;
    thiz->channelEvent = NULL;

    return TINY_RET_OK;
}

ICACHE_FLASH_ATTR
static TinyRet WdcHandler_Dispose(ChannelHandler *thiz)
{
    RETURN_VAL_IF_FAIL(thiz, TINY_RET_E_ARG_NULL);

    memset(thiz, 0, sizeof(ChannelHandler));

    return TINY_RET_OK;
}

ICACHE_FLASH_ATTR
static void sendResponse(ChannelHandler *thiz, Channel *channel, int code, const char *status)
{
    HttpMessage response;

    if (RET_SUCCEEDED(HttpMessage_Construct(&response)))
    {
        HttpMessage_SetResponse(&response, code, status);
        HttpMessage_SetVersion(&response, 1, 1);

        HttpHeader_Set(&response.header, "Content-Type", "text/json");
        HttpHeader_SetInteger(&response.header, "Content-Length", 0);

        SocketChannel_StartWrite(channel, DATA_RAW, HttpMessage_GetBytesWithoutContent(&response), HttpMessage_GetBytesSizeWithoutContent(&response));

		if (response.content.buf != NULL)
		{
			SocketChannel_StartWrite(channel, DATA_RAW, response.content.buf, response.content.buf_size);
		}

        Channel_Close(channel);
        HttpMessage_Dispose(&response);
    }
}

ICACHE_FLASH_ATTR
static bool _channelRead(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len)
{
    HttpMessage *request = (HttpMessage *)data;
    printf("_channelRead: %s %s\n", request->request_line.method, request->request_line.uri);

    // uri: /wdc?ssid=airport&password=hello

    do
    {
        char path[5];
        WdcInfo info;
        const char *start = NULL;
        const char *end = NULL;

        memset(path, 0, 5);
        memset(&info, 0, sizeof(WdcInfo));

        start = request->request_line.uri;
        end = strstr(request->request_line.uri, "?");
        if (end == NULL)
        {
            sendResponse(thiz, channel, 400, "BAD REQUEST");
            break;
        }

        if ((end - start) != 4)
        {
            sendResponse(thiz, channel, 400, "BAD REQUEST");
            break;
        }

        strncpy(path, start, 4);
        printf("path: %s\n", path);

        if (strcmp(path, "/wdc") != 0)
        {
            sendResponse(thiz, channel, 400, "BAD REQUEST");
            break;
        }

        start = end + 1;
        end = strstr(start, "ssid=");
        if (end != start)
        {
            sendResponse(thiz, channel, 400, "BAD REQUEST");
            break;
        }

        start = end + strlen("ssid=");
        end = strstr(start, "&");
        if (end == NULL)
        {
            sendResponse(thiz, channel, 400, "BAD REQUEST");
            break;
        }

        strncpy(info.ssid, start, end - start);

        start = end + 1;
        end = strstr(start, "password=");
        if (end != start)
        {
            sendResponse(thiz, channel, 400, "BAD REQUEST");
            break;
        }

        start = end + strlen("password=");
        if (strlen(start) > 32)
        {
            sendResponse(thiz, channel, 400, "BAD REQUEST");
            break;
        }

        strncpy(info.password, start, 32);

        sendResponse(thiz, channel, 200, "OK");

        WdcInfo_Write(&info);

        system_restart();
    } while (0);

    return true;
}
