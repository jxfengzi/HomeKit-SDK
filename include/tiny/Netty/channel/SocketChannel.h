/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   SocketChannel.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __SOCKET_CHANNEL_H__
#define __SOCKET_CHANNEL_H__

#include "ChannelHandler.h"
#include "ChannelInitializer.h"
#include <tiny_typedef.h>
#include <tiny_ret.h>
#include <TinyList.h>

TINY_BEGIN_DECLS


#define CHANNEL_RECV_BUF_SIZE    (1460)


TINY_API
TINY_LOR
Channel * SocketChannel_New(void);

TINY_API
TINY_LOR
void SocketChannel_Delete(Channel *thiz);

TINY_API
TINY_LOR
TinyRet SocketChannel_Construct(Channel *thiz);

TINY_API
TINY_LOR
TinyRet SocketChannel_Dispose(Channel *thiz);

TINY_API
TINY_LOR
void SocketChannel_SetRemoteInfo(Channel *thiz, const char *ip, uint16_t port);

TINY_API
TINY_LOR
void SocketChannel_Initialize(Channel *thiz, ChannelInitializer initializer, void *ctx);

TINY_API
TINY_LOR
TinyRet SocketChannel_AddBefore(Channel *thiz, const char *name, ChannelHandler *handler);

TINY_API
TINY_LOR
void SocketChannel_AddLast(Channel *thiz, ChannelHandler *handler);

TINY_API
TINY_LOR
TinyRet SocketChannel_Open(Channel *thiz, ChannelType type);

TINY_API
TINY_LOR
void SocketChannel_Close(Channel *thiz);

TINY_API
TINY_LOR
TinyRet SocketChannel_Bind(Channel *thiz, uint16_t port, bool reuse);

TINY_API
TINY_LOR
TinyRet SocketChannel_SetBlock(Channel *thiz, bool block);

TINY_API
TINY_LOR
TinyRet SocketChannel_Listen(Channel *thiz, int maxConnections);

TINY_API
TINY_LOR
TinyRet SocketChannel_JoinGroup(Channel *thiz, const char *ip, const char *group);

TINY_API
TINY_LOR
TinyRet SocketChannel_LeaveGroup(Channel *thiz);

TINY_API
TINY_LOR
void SocketChannel_OnRegister(Channel *thiz, Selector *selector, ChannelTimer *timer);

TINY_API
TINY_LOR
void SocketChannel_OnEventTriggered(Channel *thiz, ChannelTimer *timer);

TINY_API
TINY_LOR
TinyRet SocketChannel_GetTimeout(Channel *thiz, ChannelTimer *timer, void *ctx);

TINY_API
TINY_LOR
TinyRet SocketChannel_OnReadWrite(Channel *thiz, Selector *selector);

TINY_API
TINY_LOR
void SocketChannel_OnActive(Channel *thiz);

TINY_API
TINY_LOR
void SocketChannel_OnInactive(Channel *thiz);

TINY_API
TINY_LOR
void SocketChannel_StartRead(Channel *thiz, ChannelDataType type, const void *data, uint32_t len);

TINY_API
TINY_LOR
void SocketChannel_NextRead(Channel *thiz, ChannelDataType type, const void *data, uint32_t len);

TINY_API
TINY_LOR
void SocketChannel_StartWrite(Channel *thiz, ChannelDataType type, const void *data, uint32_t len);

TINY_API
TINY_LOR
void SocketChannel_NextWrite(Channel *thiz, ChannelDataType type, const void *data, uint32_t len);


TINY_END_DECLS

#endif /* __SOCKET_CHANNEL_H__ */
