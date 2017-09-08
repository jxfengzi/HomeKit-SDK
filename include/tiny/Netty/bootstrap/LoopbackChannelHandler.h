/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   LoopbackChannelHandler.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __LOOPBACK_CHANNEL_HANDLER_H__
#define __LOOPBACK_CHANNEL_HANDLER_H__

#include <tiny_typedef.h>
#include <tiny_lor.h>
#include <channel/ChannelHandler.h>

TINY_BEGIN_DECLS


#define LoopbackChannelHandler_Name     "LoopbackChannelHandler"
#define BOOTSTRAP_SHUTDOWN              "bootstrap-shutdown"

TINY_LOR
ChannelHandler * LoopbackChannelHandler(void *ctx);


TINY_END_DECLS

#endif /* __LOOPBACK_CHANNEL_HANDLER_H__ */