/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   MulticastChannel.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __MULTICAST_CHANNEL_H__
#define __MULTICAST_CHANNEL_H__

#include <tiny_typedef.h>
#include <tiny_ret.h>
#include "channel/Channel.h"
#include "channel/ChannelInitializer.h"


TINY_BEGIN_DECLS


TINY_LOR
Channel * MulticastChannel_New(void);

TINY_LOR
void MulticastChannel_Initialize(Channel *thiz, ChannelInitializer initializer, void *ctx);

TINY_LOR
TinyRet MulticastChannel_Join(Channel *thiz, const char *ip, const char *group, uint16_t port, bool reuse);

TINY_LOR
TinyRet MulticastChannel_Write(Channel *thiz, const void *data, uint32_t len);

TINY_LOR
TinyRet MulticastChannel_WriteTo(Channel *thiz, const void *data, uint32_t len, uint32_t ip, uint16_t port);


TINY_END_DECLS

#endif /* __MULTICAST_CHANNEL_H__ */