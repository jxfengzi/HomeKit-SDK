/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   MdnsHandlerContext.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __MDNS_HANDLER_CONTEXT_H__
#define __MDNS_HANDLER_CONTEXT_H__

#include <tiny_base.h>
#include <message/DnsTypedef.h>
#include <message/DnsMessage.h>
#include "ServiceInfo.h"

TINY_BEGIN_DECLS


typedef struct _MdnsHandlerContext
{
#ifdef MDNS_DISCOVERY
    TinyList            observers;
#endif

    TinyList            dnssdRecords;
    TinyList            aRecords;
    TinyList            txtRecords;
    TinyList            srvRecords;
    TinyList            ptrRecords;

    uint32_t            ttl;
} MdnsHandlerContext;

TINY_LOR
MdnsHandlerContext * MdnsHandlerContext_New(void);

TINY_LOR
TinyRet MdnsHandlerContext_Construct(MdnsHandlerContext *thiz);

TINY_LOR
void MdnsHandlerContext_Dispose(MdnsHandlerContext *thiz);

TINY_LOR
void MdnsHandlerContext_Delete(MdnsHandlerContext *thiz);

TINY_LOR
TinyRet MdnsHandlerContext_Register(MdnsHandlerContext *thiz, const ServiceInfo *info);

TINY_LOR
TinyRet MdnsHandlerContext_Unregister(MdnsHandlerContext *thiz, const ServiceInfo *info);

TINY_LOR
DnsMessage * MdnsHandlerContext_MakeResponse(MdnsHandlerContext *thiz, DnsMessage *request);

TINY_LOR
DnsMessage * MdnsHandlerContext_MakeRequest(MdnsHandlerContext *thiz);

TINY_LOR
DnsMessage * MdnsHandlerContext_MakeRequestByAnswers(MdnsHandlerContext *thiz,  TinyList *answers);



TINY_END_DECLS

#endif /* __MDNS_HANDLER_CONTEXT_H__ */