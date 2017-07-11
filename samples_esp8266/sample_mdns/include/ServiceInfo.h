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

#include "bonjour_api.h"
#include "TxtRecord.h"

TINY_BEGIN_DECLS


#define EMDNS_HTTP           "_http._tcp"
#define EMDNS_DACP           "_dacp._tcp"
#define EMDNS_AIRPLAY        "_airplay._tcp"
#define EMDNS_HAP            "_hap._tcp"

#define MDNS_NAME_LEN   32
#define MDNS_IP_LEN     32
#define MDNS_TYPE_LEN   32


typedef struct _ServiceInfo
{
    char            name[MDNS_NAME_LEN];
    char            ip[MDNS_IP_LEN];
    char            type[MDNS_TYPE_LEN];
    uint16_t        port;
    TxtRecord     * txtRecord;
} ServiceInfo;

#define ServiceInfo_Initialize(thiz)        (memset(thiz, 0, sizeof(ServiceInfo)))
#define ServiceInfo_SetName(thiz, _name)    (strncpy(thiz->name, _name, MDNS_NAME_LEN))
#define ServiceInfo_GetName(thiz)           (thiz->name)
#define ServiceInfo_SetType(thiz, _type)    (strncpy(thiz->type, _type, MDNS_TYPE_LEN))
#define ServiceInfo_GetType(thiz)           (thiz->type)
#define ServiceInfo_SetIp(thiz, _ip)        (strncpy(thiz->ip, _ip, MDNS_IP_LEN))
#define ServiceInfo_GetIp(thiz)             (thiz->ip)
#define ServiceInfo_SetPort(thiz, _port)    (thiz->port = _port)
#define ServiceInfo_GetPort(thiz)           (thiz->port)


TINY_END_DECLS

#endif /* __EMDS_SERVICE_INFO_H__ */