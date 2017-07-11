/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ChannelHandler.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __CHANNEL_HANDLER_H__
#define __CHANNEL_HANDLER_H__

#include <tiny_typedef.h>
#include <tiny_ret.h>
#include <common/Netty_api.h>
#include "Channel.h"

TINY_BEGIN_DECLS


#define CHANNEL_HANDLER_NAME_LEN    32

typedef enum _ChannelDataType
{
    DATA_RAW = 0,
    DATA_HTTP_MESSAGE = 1,
	DATA_MDNS_MESSAGE = 2,
    DATA_USER_DEFINED = 100,
} ChannelDataType;

typedef struct _ChannelIdle
{
    uint32_t                    readerIdleTimeSeconds;
    uint32_t                    writerIdleTimeSeconds;
    uint32_t                    allIdleTimeSeconds;
} ChannelIdle;

struct _ChannelHandler;
typedef struct _ChannelHandler ChannelHandler;

typedef void (* ChannelHandlerRemoved)(ChannelHandler *thiz);
typedef void (* ChannelActive)(ChannelHandler *thiz, Channel *channel);
typedef void (* ChannelInactive)(ChannelHandler *thiz, Channel *channel);
// TODO: emdns需要非const数据
//typedef bool (* ChannelRead)(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len);
typedef bool (* ChannelRead)(ChannelHandler *thiz, Channel *channel, ChannelDataType type, void *data, uint32_t len);
typedef bool (* ChannelWrite)(ChannelHandler *thiz, Channel *channel, ChannelDataType type, const void *data, uint32_t len);
typedef void (* ChannelEvent)(ChannelHandler *thiz, Channel *channel, void *event);

struct _ChannelHandler
{
	char 					    name[CHANNEL_HANDLER_NAME_LEN];
    ChannelHandlerRemoved       onRemove;
    ChannelDataType             inType;
    ChannelDataType             outType;
    ChannelActive               channelActive;
    ChannelInactive             channelInactive;
    ChannelRead                 channelRead;
    ChannelWrite                channelWrite;
    ChannelEvent				channelEvent;
	ChannelTimeout              nextTimeout;
	ChannelIdle                 idle;
    void                      * data;
};


TINY_END_DECLS

#endif /* __CHANNEL_HANDLER_H__ */
