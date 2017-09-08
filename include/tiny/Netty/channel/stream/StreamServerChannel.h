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
#include <tiny_api.h>
#include "channel/Channel.h"
#include "channel/ChannelInitializer.h"

TINY_BEGIN_DECLS


TINY_API
TINY_LOR
Channel * StreamServerChannel_New(int maxConnections);

TINY_API
TINY_LOR
void StreamServerChannel_Initialize(Channel *thiz, ChannelInitializer initializer, void *ctx);


TINY_END_DECLS

#endif /* __STREAM_SERVER_CHANNEL_H__ */