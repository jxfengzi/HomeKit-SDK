/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Name.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __NAME_H__
#define __NAME_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS


typedef struct _DnsName
{
    /**
     * .aaa.bbb.ccc.local\0
     */
    char            * string;

    /**
     * [x]aaa[x]bbb[x]ccc[x]local[0]
     */
    char            * bytes;

    uint32_t          length;
    uint32_t          count;
    int               offset;
} DnsName;


TINY_LOR
TinyRet DnsName_Construct(DnsName *thiz);

TINY_LOR
void DnsName_Dispose(DnsName *thiz);

TINY_LOR
uint32_t DnsName_Parse(DnsName *thiz, const uint8_t *buf, uint32_t len, uint32_t offset);

TINY_LOR
TinyRet DnsName_InitializeHost(DnsName *thiz, const char *name);

TINY_LOR
TinyRet DnsName_InitializeReverseIpv4Host(DnsName *thiz, uint32_t ip);

TINY_LOR
TinyRet DnsName_InitializeServiceHost(DnsName *thiz, const char *name);

TINY_LOR
TinyRet DnsName_InitializeServiceInstance(DnsName *thiz, const char *name, const char *type);

TINY_LOR
TinyRet DnsName_InitializeServiceType(DnsName *thiz, const char *type);

TINY_LOR
TinyRet DnsName_InitializeServiceDnssd(DnsName *thiz);

TINY_LOR
bool DnsName_IsServiceDnssd(DnsName *thiz);

TINY_LOR
TinyRet DnsName_Copy(DnsName *dst, const DnsName *src);

TINY_LOR
uint32_t DnsName_ToBytes(DnsName *thiz, uint8_t *buf, uint32_t length, uint32_t offset);


TINY_END_DECLS

#endif /* __NAME_H__ */