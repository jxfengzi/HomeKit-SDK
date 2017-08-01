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
#include <common/Netty_api.h>

TINY_BEGIN_DECLS


#define CHANNEL_RECV_BUF_SIZE    (1460)


NETTY_API
TINY_LOR
Channel * SocketChannel_New(void);

NETTY_API
TINY_LOR
void SocketChannel_Delete(Channel *thiz);

//NETTY_API
//TINY_LOR
//void SocketChannel_Initialize(Channel *thiz, ChannelInitializer initializer, void *ctx);

NETTY_API
TINY_LOR
void SocketChannel_InitializeWithRemoteInfo(Channel *thiz, const char *ip, int fd, uint16_t port, ChannelInitializer initializer, void *ctx);

NETTY_API
TINY_LOR
TinyRet SocketChannel_AddBefore(Channel *thiz, const char *name, ChannelHandler *handler);

NETTY_API
TINY_LOR
void SocketChannel_AddLast(Channel *thiz, ChannelHandler *handler);

NETTY_API
TINY_LOR
TinyRet SocketChannel_Open(Channel *thiz, ChannelType type);

NETTY_API
TINY_LOR
TinyRet SocketChannel_Bind(Channel *thiz, uint16_t port, bool reuse);

NETTY_API
TINY_LOR
TinyRet SocketChannel_SetBlock(Channel *thiz, bool block);

NETTY_API
TINY_LOR
TinyRet SocketChannel_Listen(Channel *thiz, int maxConnections);

NETTY_API
TINY_LOR
TinyRet SocketChannel_JoinGroup(Channel *thiz, const char *ip, const char *group);

NETTY_API
TINY_LOR
TinyRet SocketChannel_LeaveGroup(Channel *thiz);

NETTY_API
TINY_LOR
TinyRet SocketChannel_Connect(Channel *thiz, const char *ip, uint8_t port, uint32_t timeout);

TINY_LOR
void SocketChannel_OnActive(Channel *thiz);

TINY_LOR
void SocketChannel_OnInactive(Channel *thiz);

NETTY_API
TINY_LOR
void SocketChannel_StartRead(Channel *thiz, ChannelDataType type, const void *data, uint32_t len);

NETTY_API
TINY_LOR
void SocketChannel_NextRead(Channel *thiz, ChannelDataType type, const void *data, uint32_t len);

NETTY_API
TINY_LOR
void SocketChannel_StartWrite(Channel *thiz, ChannelDataType type, const void *data, uint32_t len);

NETTY_API
TINY_LOR
void SocketChannel_NextWrite(Channel *thiz, ChannelDataType type, const void *data, uint32_t len);


TINY_END_DECLS

#endif /* __SOCKET_CHANNEL_H__ */
