/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ChannelIdleStateHandler.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __CHANNEL_IDLE_STATE_HANDLER_H__
#define __CHANNEL_IDLE_STATE_HANDLER_H__

#include <channel/ChannelHandler.h>
#include <common/Netty_api.h>

TINY_BEGIN_DECLS


#define ChannelIdleStateHandler_Name    "ChannelIdleStateHandler"

NETTY_API ChannelHandler * ChannelIdleStateHandler(uint32_t readerIdle, uint32_t writerIdle, uint32_t allIdle);


TINY_END_DECLS

#endif /* __CHANNEL_IDLE_STATE_HANDLER_H__ */
