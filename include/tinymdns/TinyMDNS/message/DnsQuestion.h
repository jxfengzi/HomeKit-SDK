/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DnsQuestion.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __DNS_QUESTION_H__
#define __DNS_QUESTION_H__

#include <tiny_base.h>
#include "DnsName.h"
#include "DnsTypedef.h"

TINY_BEGIN_DECLS


/**
 * https://tools.ietf.org/html/rfc1035
 *
 * 4.1.2. Question section format
 *
 * The question section is used to carry the "question" in most queries,
 * i.e., the parameters that define what is being asked.  The section
 * contains QDCOUNT (usually 1) entries, each of the following format:
 *
 *                                     1  1  1  1  1  1
 *       0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5
 *     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *     |                                               |
 *     /                     QNAME                     /
 *     /                                               /
 *     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *     |                     QTYPE                     |
 *     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *     |                     QCLASS                    |
 *     +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 *
 * where:
 *
 * QNAME           a domain name represented as a sequence of labels, where
 *                 each label consists of a length octet followed by that
 *                 number of octets.  The domain name terminates with the
 *                 zero length octet for the null label of the root.  Note
 *                 that this field may be an odd number of octets; no
 *                 padding is used.
 *
 * example: gemini.tuc.noao.edu =>
 *   [6][g][e][m][i][n][i][3][t][u][c][4][n][o][a][o][3][e][d][u][0]
 *
 *
 * QTYPE           a two octet code which specifies the type of the query.
 *                 The values for this field include all codes valid for a
 *                 TYPE field, together with some more general codes which
 *                 can match more than one type of RR.
 *
 * QCLASS          a two octet code that specifies the class of the query.
 *                 For example, the QCLASS field is IN for the Internet.
 */

typedef struct _DnsQuestion
{
    DnsName             name;
    DnsRecordType       type;
    DnsRecordClass      clazz;
    bool                unicast;
} DnsQuestion;


TINY_LOR
DnsQuestion * DnsQuestion_New(void);

TINY_LOR
void DnsQuestion_Delete(DnsQuestion *thiz);

TINY_LOR
int DnsQuestion_Parse(DnsQuestion *thiz, const uint8_t *buf, uint32_t len, uint32_t offset);

TINY_LOR
uint32_t DnsQuestion_ToBytes(DnsQuestion *thiz, uint8_t *buf, uint32_t length, uint32_t offset);


TINY_END_DECLS

#endif /* __DNS_QUESTION_H__ */