/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Tlv8.h
 *
 * @remark
 *
 */

#ifndef __TLV8_H__
#define __TLV8_H__

#include <tiny_lor.h>
#include "api/iot_api.h"
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef struct _Tlv8
{
    uint8_t         type;
    uint32_t        length;
    uint8_t       * data;
} Tlv8;

TINY_LOR
Tlv8* Tlv8_New(void);

TINY_LOR
void Tlv8_Delete(Tlv8 *thiz);

TINY_LOR
TinyRet Tlv8_Initialize(Tlv8 *thiz, uint8_t type, uint32_t length, const uint8_t *buf);

TINY_LOR
TinyRet Tlv8_AddData(Tlv8 *thiz, uint32_t dataLength, const uint8_t *data);


TINY_END_DECLS

#endif /* __TLV8_H__ */
