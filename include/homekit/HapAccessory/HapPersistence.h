/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HapPersistence.h
 *
 * @remark
 *
 */

#ifndef __HAP_PERSISTENCE_H__
#define __HAP_PERSISTENCE_H__

#include <data/EntityIdentifier.h>
#include <ed25519/Ed25519.h>
#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef TinyRet (* HapPersistence_Initialize)(void);
typedef TinyRet (* HapPersistence_Destroy)(void);
typedef TinyRet (* HapPersistence_SaveKeyPair)(Ed25519KeyPair *keys);
typedef TinyRet (* HapPersistence_LoadKeyPair)(Ed25519KeyPair *keys);
typedef TinyRet (* HapPersistence_CleanLTPK)(void);
typedef TinyRet (* HapPersistence_SaveLTPK)(EntityIdentifier *id, ED25519PublicKey *LTPK);
typedef TinyRet (* HapPersistence_RemoveLTPK)(EntityIdentifier *id);
typedef TinyRet (* HapPersistence_LoadLTPK)(EntityIdentifier *id, ED25519PublicKey *LTPK);
typedef uint32_t (* HapPersistence_GetLTPKCount)(void);
typedef TinyRet (* HapPersistence_LoadLTPKAt)(int index, EntityIdentifier *id, ED25519PublicKey *LTPK);


typedef struct _HapPersistence
{
    HapPersistence_Initialize           Initialize;
    HapPersistence_Destroy              Destroy;
    HapPersistence_SaveKeyPair          SaveKeyPair;
    HapPersistence_LoadKeyPair          LoadKeyPair;
    HapPersistence_CleanLTPK            CleanLTPK;
    HapPersistence_SaveLTPK             SaveLTPK;
    HapPersistence_RemoveLTPK           RemoveLTPK;
    HapPersistence_LoadLTPK             LoadLTPK;
    HapPersistence_GetLTPKCount         GetLTPKCount;
    HapPersistence_LoadLTPKAt           LoadLTPKAt;
} HapPersistence;


TINY_END_DECLS

#endif /* __HAP_PERSISTENCE_H__ */