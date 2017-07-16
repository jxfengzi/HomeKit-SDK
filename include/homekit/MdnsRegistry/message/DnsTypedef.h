/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DnsTypedef.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __DNS_TYPEDEF_H__
#define __DNS_TYPEDEF_H__

#include <tiny_base.h>

TINY_BEGIN_DECLS


/**
 * https://tools.ietf.org/html/rfc1035
 * 3.2.2. TYPE values
 * TYPE fields are used in resource records.  Note that these types are a subset of QTYPEs.
 * TYPE            value and meaning
 *
 * A               1 a host address
 * NS              2 an authoritative name server
 * MD              3 a mail destination (Obsolete - use MX)
 * MF              4 a mail forwarder (Obsolete - use MX)
 * CNAME           5 the canonical name for an alias
 * SOA             6 marks the start of a zone of authority
 * MB              7 a mailbox domain name (EXPERIMENTAL)
 * MG              8 a mail group member (EXPERIMENTAL)
 * MR              9 a mail rename domain name (EXPERIMENTAL)
 * NULL            10 a null RR (EXPERIMENTAL)
 * WKS             11 a well known service description
 * PTR             12 a domain name pointer
 * HINFO           13 host information
 * MINFO           14 mailbox or mail list information
 * MX              15 mail exchange
 * TXT             16 text strings
 */

typedef enum _DnsRecordType
{
    TYPE_A          = 1,    // a host address
    TYPE_NS         = 2,    // an authoritative name server
    TYPE_CNAME      = 5,    // the canonical name for an alias
    TYPE_PTR        = 12,   // a domain name pointer
    TYPE_TXT        = 16,   // text strings
    TYPE_AAAA       = 28,   // IP6 Address
    TYPE_SRV        = 33,   // https://tools.ietf.org/html/rfc2782
    TYPE_ANY        = 255,  // Request for all records [RFC1035]
} DnsRecordType;

/**
 * https://tools.ietf.org/html/rfc1035
 * 3.2.4. CLASS values
 *
 * CLASS fields appear in resource records.  The following CLASS mnemonics
 * and values are defined:
 *
 * IN              1 the Internet
 *
 * CS              2 the CSNET class (Obsolete - used only for examples in
 *                 some obsolete RFCs)
 *
 * CH              3 the CHAOS class
 *
 * HS              4 Hesiod [Dyer 87]
 *
 * 3.2.5. QCLASS values
 *
 * QCLASS fields appear in the question section of a query.  QCLASS values
 * are a superset of CLASS values; every CLASS is a valid QCLASS.  In
 * addition to CLASS values, the following QCLASSes are defined:
 *
 * *              255 any class
 */

typedef enum _DnsRecordClass
{
    CLASS_IN            = 1,        // the Internet
    CLASS_CS            = 2,        // the CSNET class (Obsolete - used only for examples in some obsolete RFCs)
    CLASS_CH            = 3,        // the CHAOS class
    CLASS_HS            = 4,        // Hesiod [Dyer 87]
    CLASS_FLUSH         = 0x8000,   // flush bit
    CLASS_FLUSH_IN      = 0x8001,   // flush bit and internet
    CLASS_NONE          = 254,      // Used in DNS UPDATE [RFC 2136]
    CLASS_ANY           = 255,      // any class
} DnsRecordClass;


#ifdef TINY_DEBUG
const char * DnsRecordType_ToString(DnsRecordType v);
const char * DnsRecordClass_ToString(DnsRecordClass v);
#else
#define DnsRecordType_ToString(t)   ""
#define DnsRecordClass_ToString(t)  ""
#endif

TINY_END_DECLS

#endif /* __DNS_TYPEDEF_H__ */