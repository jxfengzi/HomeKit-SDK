/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ChannelInitializer.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __CHANNEL_INITIALIZER_H__
#define __CHANNEL_INITIALIZER_H__

#include <tiny_typedef.h>
#include "Channel.h"

TINY_BEGIN_DECLS


typedef void (*ChannelInitializer)(Channel *channel, void *ctx);


TINY_END_DECLS

#endif /* __CHANNEL_INITIALIZER_H__ */