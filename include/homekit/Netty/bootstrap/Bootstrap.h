/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Bootstrap.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __BOOTSTRAP_H__
#define __BOOTSTRAP_H__

#include <common/Netty_api.h>
#include <tiny_typedef.h>
#include <tiny_ret.h>
#include "channel/Channel.h"
#include <selector/Selector.h>
//#include <timer/Timer.h>

TINY_BEGIN_DECLS


typedef enum _TimerType
{
    TIMER_TYPE_NONE             = 0,
    TIMER_TYPE_CHANNEL_TIMER    = 1,
//    TIMER_TYPE_TIMER            = 2,
} TimerType;

typedef struct _TimerConfiguration
{
    TimerType                   type;
    int                         index;
    int64_t                     us;
} TimerConfiguration;

typedef struct _Bootstrap
{
    Selector                    selector;
    TinyList                    channels;
//    TinyList                    timers;
    TimerConfiguration          timerConfiguration;
} Bootstrap;

NETTY_API
TINY_LOR
TinyRet Bootstrap_Construct(Bootstrap *thiz);

NETTY_API
TINY_LOR
void Bootstrap_Dispose(Bootstrap *thiz);

//NETTY_API
//TINY_LOR
//TinyRet Bootstrap_AddTimer(Bootstrap *thiz, Timer *timer);
//
//NETTY_API
//TINY_LOR
//TinyRet Bootstrap_RemoveTimer(Bootstrap *thiz, Timer *timer);

NETTY_API
TINY_LOR
TinyRet Bootstrap_AddChannel(Bootstrap *thiz, Channel *channel);

//NETTY_API
//TINY_LOR
//TinyRet Bootstrap_RemoveChannel(Bootstrap *thiz, Channel *channel);

NETTY_API
TINY_LOR
TinyRet Bootstrap_Sync(Bootstrap *thiz);

NETTY_API
TINY_LOR
TinyRet Bootstrap_Shutdown(Bootstrap *thiz);


TINY_END_DECLS

#endif /* __BOOTSTRAP_H__ */