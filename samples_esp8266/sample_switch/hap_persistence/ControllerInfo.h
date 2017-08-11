/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2017-8-5
*
* @file   ControllerInfo.h
*
* @remark
*
*/

#ifndef __CONTROLLER_INFO_H___
#define __CONTROLLER_INFO_H___

#include <tiny_base.h>
#include <data/EntityIdentifier.h>
#include <ed25519/Ed25519.h>

TINY_BEGIN_DECLS


typedef struct _ControllerInfo
{
    uint8_t     id[ENTITY_IDENTIFIER_LENGTH];
    uint8_t     ltpk[ED25519_PUBLIC_KEY_LENGTH];
    uint32      checksum;
} ControllerInfo;

ICACHE_FLASH_ATTR
bool ControllerInfo_Read(ControllerInfo *thiz);

ICACHE_FLASH_ATTR
bool ControllerInfo_Write(ControllerInfo *thiz);


TINY_END_DECLS

#endif /* __CONTROLLER_INFO_H___ */
