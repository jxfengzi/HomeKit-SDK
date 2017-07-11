/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DnsRecord.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __DNS_RECORD_H__
#define __DNS_RECORD_H__

#include <tiny_base.h>
#include <TinyList.h>
#include <ServiceInfo.h>
#include "DnsName.h"
#include "DnsTypedef.h"

TINY_BEGIN_DECLS


///**
// * https://tools.ietf.org/html/rfc1035
// * 3.2. RR definitions
// * 3.2.1. Format
// * All RRs have the same top level format shown below:
// *                                   1  1  1  1  1  1
// *     0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
// *   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
// *   |                                               |
// *   /                                               /
// *   /                      NAME                     /
// *   |                                               |
// *   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
// *   |                      TYPE                     |
// *   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
// *   |                     CLASS                     |
// *   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
// *   |                      TTL                      |
// *   |                                               |
// *   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
// *   |                   RDLENGTH                    |
// *   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--|
// *   /                     RDATA                     /
// *   /                                               /
// *   +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
// *
// *
// * where:
// *
// * NAME            an owner name, i.e., the name of the node to which this
// *                 resource record pertains.
// *
// * TYPE            two octets containing one of the RR TYPE codes.
// *
// * CLASS           two octets containing one of the RR CLASS codes.
// *
// * TTL             a 32 bit signed integer that specifies the time interval
// *                 that the resource record may be cached before the source
// *                 of the information should again be consulted.  Zero
// *                 values are interpreted to mean that the RR can only be
// *                 used for the transaction in progress, and should not be
// *                 cached.  For example, SOA records are always distributed
// *                 with a zero TTL to prohibit caching.  Zero values can
// *                 also be used for extremely volatile data.
// *
// * RDLENGTH        an unsigned 16 bit integer that specifies the length in
// *                 octets of the RDATA field.
// *
// * RDATA           a variable length string of octets that describes the
// *                 resource.  The format of this information varies
// *                 according to the TYPE and CLASS of the resource record.
// *
// */
//typedef struct _RR
//{
//    const char        * name;
//    uint16_t            type;
//    uint16_t            clazz;
//    uint32_t            ttl;
//    uint16_t            rdlength;
//    uint8_t           * rdata;
//} RR;

/**
 * https://tools.ietf.org/html/rfc1035
 * 4.1.3. DnsRecord record format
 * The answer, authority, and additional sections all share the same
 * format: a variable number of resource records, where the number of
 * records is specified in the corresponding count field in the header.
 * Each resource record has the following format:
 *                               1  1  1  1  1  1
 * 0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |                                               |
 * /                                               /
 * /                      NAME                     /
 * |                                               |
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |                      TYPE                     |
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |                     CLASS                     |
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |                      TTL                      |
 * |                                               |
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |                   RDLENGTH                    |
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--|
 * /                     RDATA                     /
 * /                                               /
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *
 * where:
 * NAME            a domain name to which this resource record pertains.
 *
 * TYPE            two octets containing one of the RR type codes.  This
 *                 field specifies the meaning of the data in the RDATA field.
 *
 * CLASS           two octets which specify the class of the data in the RDATA field.
 *
 * TTL             a 32 bit unsigned integer that specifies the time
 *                 interval (in seconds) that the resource record may be
 *                 cached before it should be discarded.  Zero values are
 *                 interpreted to mean that the RR can only be used for the
 *                 transaction in progress, and should not be cached.
 *
 * RDLENGTH        an unsigned 16 bit integer that specifies the length in
 *                 octets of the RDATA field.
 *
 * RDATA           a variable length string of octets that describes the
 *                 resource.  The format of this information varies
 *                 according to the TYPE and CLASS of the resource record.
 *                 For example, the if the TYPE is A and the CLASS is IN,
 *                 the RDATA field is a 4 octet ARPA Internet address.
 */

typedef struct _DataAddress
{
    uint32_t            address;
    char                ip[TINY_IP_LEN];
} DataAddress;

typedef struct _DataSrv
{
    uint16_t            priority;
    uint16_t            weight;
    uint16_t            port;
    DnsName             name;
} DataSrv;

typedef struct _DataTxt
{
    uint8_t           * value;
    uint32_t            length;
} DataTxt;

typedef union _ResourceData
{
    DataAddress         a;
    DnsName             ns;
    DnsName             cname;
    DnsName             ptr;
    DataSrv             srv;
    DataTxt             txt;
} ResourceData;

typedef struct _DnsRecord
{
    DnsName             name;
    DnsRecordType       type;
    DNSRecordClass      clazz;
    uint32_t            ttl;
    ResourceData        data;
    bool                cacheFlush;
} DnsRecord;

TINY_LOR
DnsRecord * DnsRecord_New(void);

TINY_LOR
void DnsRecord_Delete(DnsRecord *thiz);

TINY_LOR
TinyRet DnsRecord_Copy(DnsRecord *thiz, DnsRecord *other);

TINY_LOR
TinyRet DnsRecord_Initialize(DnsRecord *thiz, DnsRecordType type, ServiceInfo *info);

TINY_LOR
int DnsRecord_Parse(DnsRecord *thiz, const uint8_t *buf, uint32_t len, uint32_t offset);

TINY_LOR
uint32_t DnsRecord_ToBytes(DnsRecord *thiz, uint8_t *buf, uint32_t length, uint32_t offset);


TINY_END_DECLS

#endif /* __DNS_RECORD_H__ */