/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   MulticastChannelContext.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __MULTICAST_CHANNEL_CONTEXT_H__
#define __MULTICAST_CHANNEL_CONTEXT_H__

#include <tiny_typedef.h>
#include <tiny_ret.h>
#include <TinyList.h>
#include "channel/ChannelInitializer.h"

TINY_BEGIN_DECLS


typedef struct _MulticastChannelContext
{
    char                          group[TINY_IP_LEN];
    uint16_t                      port;
} MulticastChannelContext;

MulticastChannelContext * MulticastChannelContext_New(void);
void MulticastChannelContext_Delete(MulticastChannelContext *thiz);


TINY_END_DECLS

#endif /* __MULTICAST_CHANNEL_CONTEXT_H__ */