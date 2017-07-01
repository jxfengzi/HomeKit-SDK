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


Channel * MulticastChannel_New(void);
TinyRet MulticastChannel_Initialize(Channel *thiz, ChannelInitializer initializer, void *ctx);
TinyRet MulticastChannel_Join(Channel *thiz, const char *ip, const char *group, uint16_t port);
TinyRet MulticastChannel_Write(Channel *thiz, const void *data, uint32_t len);
TinyRet MulticastChannel_WriteTo(Channel *thiz, const void *data, uint32_t len, const void *to, uint32_t to_len);


TINY_END_DECLS

#endif /* __MULTICAST_CHANNEL_H__ */