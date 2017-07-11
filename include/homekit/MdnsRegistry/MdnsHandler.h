/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   MdnsHandler.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __MDNS_HANDLER_H__
#define __MDNS_HANDLER_H__

#include <channel/ChannelHandler.h>
#include "ServiceInfo.h"

TINY_BEGIN_DECLS


#define MdnsHandler_Name "MdnsHandler"

TINY_LOR
ChannelHandler * MdnsHandler(void);

TINY_LOR
TinyRet MdnsHandler_Register(ChannelHandler *thiz, ServiceInfo *info);

TINY_LOR
TinyRet MdnsHandler_Unregister(ChannelHandler *thiz, ServiceInfo *info);


TINY_END_DECLS

#endif /* __MDNS_HANDLER_H__ */