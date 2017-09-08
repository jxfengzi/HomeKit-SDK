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

#ifndef __MDNS_REGISTRY_H__
#define __MDNS_REGISTRY_H__

#include <channel/ChannelHandler.h>
#include "ServiceInfo.h"
#include "mdns_api.h"

#ifdef MDNS_DISCOVERY
#include "ServiceListener.h"
#endif

TINY_BEGIN_DECLS


#define MdnsHandler_Name "MdnsHandler"

MDNS_API
TINY_LOR
ChannelHandler * MdnsHandler(void);

MDNS_API
TINY_LOR
TinyRet MdnsHandler_Register(ChannelHandler *thiz, const ServiceInfo *info);

MDNS_API
TINY_LOR
TinyRet MdnsHandler_Unregister(ChannelHandler *thiz, const ServiceInfo *info);

#ifdef MDNS_DISCOVERY
MDNS_API
TINY_LOR
TinyRet MdnsHandler_AddListener(ChannelHandler *thiz, const char *type, ServiceListener listener, void *ctx);
#endif

TINY_END_DECLS

#endif /* __MDNS_REGISTRY_H__ */