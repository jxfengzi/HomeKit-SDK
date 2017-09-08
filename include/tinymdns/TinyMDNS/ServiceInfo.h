/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ServiceInfo.h
 *
 * @remark
 *
 */

#ifndef __SERVICE_INFO_H__
#define __SERVICE_INFO_H__

#include <TinyMap.h>
#include "mdns_api.h"

TINY_BEGIN_DECLS


//#define SERVICE_TYPE_HTTP           "_http._tcp"
//#define SERVICE_TYPE_DACP           "_dacp._tcp"
//#define SERVICE_TYPE_AIRPLAY        "_airplay._tcp"
//#define SERVICE_TYPE_HAP            "_hap._tcp"

#define SERVICE_TYPE_HAP            "._hap._tcp.local"

#define MDNS_NAME_LEN   32
#define MDNS_IP_LEN     32
#define MDNS_TYPE_LEN   64


typedef struct _ServiceInfo
{
    char            name[MDNS_NAME_LEN];
    char            ip[MDNS_IP_LEN];
    char            type[MDNS_TYPE_LEN];
    uint16_t        port;
    TinyMap         txt;
} ServiceInfo;

MDNS_API
TINY_LOR
TinyRet ServiceInfo_Construct(ServiceInfo *thiz);

MDNS_API
TINY_LOR
void ServiceInfo_Dispose(ServiceInfo *thiz);

MDNS_API
TINY_LOR
ServiceInfo * ServiceInfo_New(void);

MDNS_API
TINY_LOR
void ServiceInfo_Delete(ServiceInfo *thiz);

MDNS_API
TINY_LOR
void ServiceInfo_Initialize(ServiceInfo *thiz, const char *name, const char *type, const char *ip, uint16_t port);

MDNS_API
TINY_LOR
TinyRet ServiceInfo_SetTXTByString(ServiceInfo *thiz, const char *key, const char *value);

MDNS_API
TINY_LOR
TinyRet ServiceInfo_SetTXTByInteger(ServiceInfo *thiz, const char *key, uint32_t value);


TINY_END_DECLS

#endif /* __SERVICE_INFO_H__ */