/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   StreamClientChannelContext.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __STREAM_CLIENT_CHANNEL_CONTEXT_H__
#define __STREAM_CLIENT_CHANNEL_CONTEXT_H__

#include <tiny_typedef.h>
#include <tiny_ret.h>
#include <TinyList.h>
#include "channel/ChannelInitializer.h"

TINY_BEGIN_DECLS


typedef struct _StreamClientChannelContext
{
    ChannelInitializer          initializer;
    void                      * initializerContext;
    uint32_t                    connectingTimeout;
    void                      * data;
} StreamClientChannelContext;


TINY_LOR
StreamClientChannelContext * StreamClientChannelContext_New(void);

TINY_LOR
void StreamClientChannelContext_Delete(StreamClientChannelContext *thiz);


TINY_END_DECLS

#endif /* __STREAM_CLIENT_CHANNEL_CONTEXT_H__ */