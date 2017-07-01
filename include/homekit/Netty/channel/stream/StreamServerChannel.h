/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   StreamServerChannel.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __STREAM_SERVER_CHANNEL_H__
#define __STREAM_SERVER_CHANNEL_H__

#include <tiny_typedef.h>
#include <tiny_ret.h>
#include "channel/Channel.h"
#include "channel/ChannelInitializer.h"

TINY_BEGIN_DECLS


Channel * StreamServerChannel_New(int maxConnections);

TinyRet StreamServerChannel_Initialize(Channel *thiz, ChannelInitializer initializer, void *ctx);
TinyRet StreamServerChannel_Bind(Channel *thiz, uint16_t port);


TINY_END_DECLS

#endif /* __STREAM_SERVER_CHANNEL_H__ */