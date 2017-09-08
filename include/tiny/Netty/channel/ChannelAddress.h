/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ChannelAddress.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __CHANNEL_ADDRESS_H__
#define __CHANNEL_ADDRESS_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS


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
    char                    ip[TINY_IP_LEN];
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

TINY_LOR
void ChannelAddress_Set(ChannelAddress *thiz, ChannelType type, uint32_t address, uint16_t port);



TINY_END_DECLS

#endif /* __CHANNEL_ADDRESS_H__ */
