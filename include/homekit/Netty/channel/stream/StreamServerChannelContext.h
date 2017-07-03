/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   StreamServerChannelContext.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __STREAM_SERVER_CHANNEL_CONTEXT_H__
#define __STREAM_SERVER_CHANNEL_CONTEXT_H__

#include <tiny_typedef.h>
#include <tiny_ret.h>
#include <TinyList.h>
#include "channel/ChannelInitializer.h"

TINY_BEGIN_DECLS


typedef struct _StreamServerChannelContext
{
    int                         maxConnections;
    TinyList                    channels;
    ChannelInitializer          initializer;
    void                      * initializerContext;
} StreamServerChannelContext;

StreamServerChannelContext * StreamServerChannelContext_New(void);
void StreamServerChannelContext_Delete(StreamServerChannelContext *thiz);


TINY_END_DECLS

#endif /* __STREAM_SERVER_CHANNEL_CONTEXT_H__ */
