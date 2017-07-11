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

TINY_BEGIN_DECLS


#define SERVICE_TYPE_HTTP           "_http._tcp"
#define SERVICE_TYPE_DACP           "_dacp._tcp"
#define SERVICE_TYPE_AIRPLAY        "_airplay._tcp"
#define SERVICE_TYPE_HAP            "_hap._tcp"

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

TINY_LOR
TinyRet ServiceInfo_Construct(ServiceInfo *thiz);

TINY_LOR
void ServiceInfo_Dispose(ServiceInfo *thiz);

#if 0
TINY_LOR
ServiceInfo * ServiceInfo_New(void);

TINY_LOR
void ServiceInfo_Delete(ServiceInfo *thiz);
#endif

TINY_LOR
void ServiceInfo_Initialize(ServiceInfo *thiz, const char *name, const char *type, const char *ip, uint16_t port);

#if 0
TINY_LOR
bool ServiceInfo_Equals(ServiceInfo *thiz, ServiceInfo *other);

TINY_LOR
bool ServiceInfo_Is(ServiceInfo *thiz, const char *type);
#endif


TINY_END_DECLS

#endif /* __SERVICE_INFO_H__ */