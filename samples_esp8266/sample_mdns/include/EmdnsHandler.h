/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   EmdnsHandler.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __EMDNS_HANDLER_H__
#define __EMDNS_HANDLER_H__

#include <channel/ChannelHandler.h>
#include "ServiceInfo.h"

TINY_BEGIN_DECLS


#define EmdnsHandler_Name "EmdnsHandler"

TINY_LOR
ChannelHandler * EmdnsHandler(void);

TINY_LOR
TinyRet EmdnsHandler_Register(ChannelHandler *thiz, ServiceInfo *info);

TINY_LOR
TinyRet EmdnsHandler_Unregister(ChannelHandler *thiz, ServiceInfo *info);


TINY_END_DECLS

#endif /* __EMDNS_HANDLER_H__ */