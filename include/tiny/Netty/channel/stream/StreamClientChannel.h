/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   StreamClientChannel.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __STREAM_CLIENT_CHANNEL_H__
#define __STREAM_CLIENT_CHANNEL_H__

#include <tiny_typedef.h>
#include <tiny_ret.h>
#include "channel/Channel.h"
#include "channel/ChannelInitializer.h"

TINY_BEGIN_DECLS


TINY_LOR
Channel * StreamClientChannel_New(void);

TINY_LOR
void StreamClientChannel_Delete(Channel *thiz);

TINY_LOR
TinyRet StreamClientChannel_Construct(Channel *thiz);

TINY_LOR
void StreamClientChannel_Dispose(Channel *thiz);

TINY_LOR
TinyRet StreamClientChannel_Initialize(Channel *thiz, ChannelInitializer initializer, void *ctx);

TINY_LOR
TinyRet StreamClientChannel_Connect(Channel *thiz, const char *ip, uint16_t port, uint32_t timeout);

TINY_LOR
TinyRet StreamClientChannel_Close(Channel *thiz);

TINY_LOR
bool StreamClientChannel_IsConnected(Channel* thiz);


TINY_END_DECLS

#endif /* __STREAM_CLIENT_CHANNEL_H__ */