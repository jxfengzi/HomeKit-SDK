/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ServiceObserver.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __SERVICE_OBSERVER_H__
#define __SERVICE_OBSERVER_H__

#include <tiny_base.h>
#include "ServiceListener.h"

TINY_BEGIN_DECLS


#ifdef MDNS_DISCOVERY

#define MDNS_SERVICE_TYPE_LEN       64

typedef struct _ServiceObserver
{
    char                  type[MDNS_SERVICE_TYPE_LEN];
    ServiceListener       listener;
    void                * ctx;
} ServiceObserver;

TINY_LOR
ServiceObserver * ServiceObserver_New(const char *type, ServiceListener listener, void *ctx);

TINY_LOR
void ServiceObserver_Delete(ServiceObserver *thiz);

#endif


TINY_END_DECLS

#endif /* __SERVICE_OBSERVER_H__ */