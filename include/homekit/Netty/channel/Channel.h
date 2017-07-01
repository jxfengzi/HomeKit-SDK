/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Channel.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include <tiny_typedef.h>
#include <TinyList.h>
#include <selector/Selector.h>

TINY_BEGIN_DECLS


#define CHANNEL_ID_LEN              64
#define IP_LEN                      32

typedef enum _ChannelType
{
    TYPE_RS232,
    TYPE_RS485,
    TYPE_UDP,
    TYPE_TCP_SERVER,
    TYPE_TCP_CONNECTION,
} ChannelType;

typedef struct _Socket
{
    uint32_t                address;
    char                    ip[IP_LEN];
    uint16_t                port;
} Socket;

typedef struct _RS232
{
    uint16_t                port;
} RS232;

typedef struct _RS485
{
    uint16_t                port;
} RS485;

typedef union _ChannelAddress
{
    Socket                  socket;
    RS232                   rs232;
    RS485                   rs485;
} ChannelAddress;

struct _Channel;
typedef struct _Channel Channel;

typedef void (* ChannelHandleRegister)(Channel *channel, Selector *selector);
typedef void (* ChannelHandleRemove)(Channel *channel);
typedef void (* ChannelHandleActive)(Channel *thiz);
typedef void (* ChannelHandleInactive)(Channel *thiz);
typedef void (* ChannelHandleEventTriggered)(Channel *thiz, void *event);
typedef TinyRet (* ChannelHandleRead)(Channel *channel, Selector *selector);
typedef int64_t (* ChannelTimeout)(Channel *thiz, void *ctx);

struct _Channel
{
    char                            id[CHANNEL_ID_LEN];
    int                             fd;
    ChannelType                     type;
    ChannelAddress                  local;
    ChannelAddress                  remote;
    ChannelHandleRegister           onRegister;
    ChannelHandleRemove             onRemove;
    ChannelHandleActive             onActive;
    ChannelHandleInactive           onInactive;
    ChannelHandleRead               onRead;
    ChannelHandleEventTriggered     onEventTriggered;
    ChannelTimeout                  getNextTimeout;
    TinyList                        handlers;
    int                             currentReader;
    int                             currentWriter;
    void                          * ctx;
};

bool Channel_IsActive(Channel *thiz);
bool Channel_IsClosed(Channel *thiz);
void Channel_Close(Channel *thiz);


TINY_END_DECLS

#endif /* __CHANNEL_H__ */
