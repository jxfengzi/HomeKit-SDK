/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DNSDnsMessage.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __DNS_MESSAGE_H__
#define __DNS_MESSAGE_H__

#include <tiny_base.h>
#include <TinyList.h>

TINY_BEGIN_DECLS


/**
 * https://tools.ietf.org/html/rfc1035
 * 4. MESSAGES
 *
 * 4.1. Format
 *
 * All communications inside of the domain protocol are carried in a single
 * format called a message.  The top level format of message is divided
 * into 5 sections (some of which are empty in certain cases) shown below:
 *
 *     +---------------------+
 *     |        Header       |
 *     +---------------------+
 *     |       Question      | the question for the name server
 *     +---------------------+
 *     |        Answer       | RRs answering the question
 *     +---------------------+
 *     |      Authority      | RRs pointing toward an authority
 *     +---------------------+
 *     |      Additional     | RRs holding additional information
 *     +---------------------+
 *
 * The header section is always present.  The header includes fields that
 * specify which of the remaining sections are present, and also specify
 * whether the message is a query or a response, a standard query or some
 * other opcode, etc.
 *
 * The names of the sections after the header are derived from their use in
 * standard queries.  The question section contains fields that describe a
 * question to a name server.  These fields are a query type (QTYPE), a
 * query class (QCLASS), and a query domain name (QNAME).  The last three
 * sections have the same format: a possibly empty list of concatenated
 * resource records (RRs).  The answer section contains RRs that answer the
 * question; the authority section contains RRs that point toward an
 * authoritative name server; the additional records section contains RRs
 * which relate to the query, but are not strictly answers for the
 * question.
 */

typedef struct _FlagBits
{
    uint16_t        RCODE:4;        // Response code
    uint16_t        Z:3;            // Reserved for future use.  Must be zero in all queries and responses.
    uint16_t        RA:1;           // Recursion Available
    uint16_t        RD:1;           // Recursion Desired
    uint16_t        TC:1;           // Truncated
    uint16_t        AA:1;           // Authoritative Answer
    uint16_t        Opcode:4;       // QUERY | IQUERY | STATUS
    uint16_t        QR:1;           // query (0), or a response (1).
} FlagBits;

typedef union _DnsFlag
{
    FlagBits    bits;
    uint16_t    value;
} DnsFlag;

typedef struct _Header
{
    uint16_t        ID;
    DnsFlag         FLAG;
    uint16_t        QDCOUNT;        // the number of entries in the question section.
    uint16_t        ANCOUNT;        // the number of resource records in the answer section.
    uint16_t        NSCOUNT;        // the number of name server resource records in the authority records section.
    uint16_t        ARCOUNT;        // the number of resource records in the additional records section.
} Header;

/**
 * https://tools.ietf.org/html/rfc1035
 * QR: query (0), or a response (1).
 */
#define QR_QUERY                0
#define QR_RESPONSE             1

/**
 * https://tools.ietf.org/html/rfc1035
 * OPCODE          A four bit field that specifies kind of query in this
 *                 message.  This value is set by the originator of a query
 *                 and copied into the response.  The values are:
 *
 *                 0               a standard query (QUERY)
 *                 1               an inverse query (IQUERY)
 *                 2               a server status request (STATUS)
 *                 3-15            reserved for future use
 */
#define QPCODE_QUERY            0
#define QPCODE_IQUERY           1
#define QPCODE_STATUS           2
#define OPCODE_UNASSIGNED       3   // Unassigned
#define OPCODE_NOTIFY           4   // [RFC1996]
#define OPCODE_UPDATE           5   // [RFC2136]

/**
 * https://tools.ietf.org/html/rfc1035
 * RCODE           Response code - this 4 bit field is set as part of
 *                 responses.  The values have the following
 *                 interpretation:
 *
 *                 0               No error condition
 *                 1               Format error - The name server was
 *                                 unable to interpret the query.
 *                 2               Server failure - The name server was
 *                                 unable to process this query due to a
 *                                 problem with the name server.
 *                 3               Name Error - Meaningful only for
 *                                 responses from an authoritative name
 *                                 server, this code signifies that the
 *                                 domain name referenced in the query does
 *                                 not exist.
 *                 4               Not Implemented - The name server does
 *                                 not support the requested kind of query.
 *                 5               Refused - The name server refuses to
 *                                 perform the specified operation for
 *                                 policy reasons.  For example, a name
 *                                 server may not wish to provide the
 *                                 information to the particular requester,
 *                                 or a name server may not wish to perform
 *                                 a particular operation (e.g., zone
 *                                 transfer) for particular data.
 *                 6-15            Reserved for future use.
 */
#define RCODE_NO_ERROR          0
#define RCODE_FORMAT_ERROR      1
#define RCODE_SERVER_FAILURE    2
#define RCODE_NAME_ERROR        3
#define RCODE_NOT_IMPLEMENTED   4
#define RCODE_REFUSED           5

typedef struct _DnsMessage
{
    Header            header;
    TinyList          questions;
    TinyList          answers;
    TinyList          authorities;
    TinyList          additionals;
} DnsMessage;


TINY_LOR
TinyRet DnsMessage_Construct(DnsMessage *thiz);

TINY_LOR
void DnsMessage_Dispose(DnsMessage *thiz);

TINY_LOR
TinyRet DnsMessage_Parse(DnsMessage *thiz, const void *buf, uint32_t len);

TINY_LOR
uint32_t DnsMessage_ToBytes(DnsMessage *thiz, uint8_t *buf, uint32_t length, uint32_t offset);


TINY_END_DECLS

#endif /* __DNS_MESSAGE_H__ */