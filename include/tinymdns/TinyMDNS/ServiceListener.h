/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ServiceListener.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __SERVICE_LISTENER_H__
#define __SERVICE_LISTENER_H__

#include <tiny_base.h>
#include <ServiceInfo.h>

TINY_BEGIN_DECLS


#ifdef MDNS_DISCOVERY

typedef enum _ServiceEvent
{
    SERVICE_FOUND = 0,
    SERVICE_LOST = 1,
    SERVICE_UPDATE = 2,
} ServiceEvent;

typedef void (* ServiceListener) (ServiceInfo *info, ServiceEvent event, void *ctx);

#endif


TINY_END_DECLS

#endif /* __SERVICE_LISTENER_H__ */