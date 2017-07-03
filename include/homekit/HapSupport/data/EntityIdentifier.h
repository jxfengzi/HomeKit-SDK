/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   EntityIdentifier.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __ENTITY_IDENTIFIER_H__
#define __ENTITY_IDENTIFIER_H__

#include <tiny_base.h>
#include <tiny_lor.h>

TINY_BEGIN_DECLS


/**
 * Identifier => iOSDevicePairingID | AccessoryPairingID
 */
#define ENTITY_IDENTIFIER_LENGTH   64

typedef struct _EntityIdentifier
{
    uint8_t         value[ENTITY_IDENTIFIER_LENGTH];
    uint32_t        length;
} EntityIdentifier;

TINY_LOR
void EntityIdentifier_Initialize(EntityIdentifier *thiz, const char *id);


TINY_END_DECLS

#endif /* __ENTITY_IDENTIFIER_H__ */