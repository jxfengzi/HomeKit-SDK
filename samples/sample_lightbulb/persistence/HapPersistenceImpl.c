/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HapPersistenceImpl.c
 *
 * @remark
 *
 */

#include "HapPersistenceImpl.h"

static bool __keypairSaved;
static uint8_t __privateKey[ED25519_PRIVATE_KEY_LENGTH];
static uint8_t __publicKey[ED25519_PUBLIC_KEY_LENGTH];

static uint8_t __id[ENTITY_IDENTIFIER_LENGTH];
static uint8_t __ltpk[ED25519_PUBLIC_KEY_LENGTH];

static TinyRet Storage_Initialize(void)
{
    printf("Storage_Initialize\n");

    __keypairSaved = false;
    memset(__privateKey, 0, ED25519_PRIVATE_KEY_LENGTH);
    memset(__publicKey, 0, ED25519_PUBLIC_KEY_LENGTH);

    memset(__id, 0, ENTITY_IDENTIFIER_LENGTH);
    memset(__ltpk, 0, ED25519_PUBLIC_KEY_LENGTH);

    return TINY_RET_OK;
}

static TinyRet Storage_Destroy(void)
{
    printf("Storage_Destroy\n");

    return TINY_RET_OK;
}

static TinyRet Storage_SaveKeyPair(Ed25519KeyPair *keys)
{
    printf("Storage_SaveKeyPair\n");

    __keypairSaved = true;
    memcpy(__privateKey, keys->privateKey.value, keys->privateKey.length);
    memcpy(__publicKey, keys->publicKey.value, keys->publicKey.length);

    return TINY_RET_OK;
}

static TinyRet Storage_LoadKeyPair(Ed25519KeyPair *keys)
{
    printf("Storage_LoadKeyPair\n");

    if (__keypairSaved)
    {
        memcpy(keys->privateKey.value, __privateKey, ED25519_PRIVATE_KEY_LENGTH);
        keys->privateKey.length = ED25519_PRIVATE_KEY_LENGTH;

        memcpy(keys->publicKey.value, __publicKey, ED25519_PUBLIC_KEY_LENGTH);
        keys->publicKey.length = ED25519_PUBLIC_KEY_LENGTH;
        return TINY_RET_OK;
    }

    return TINY_RET_E_NOT_FOUND;
}

static TinyRet Storage_CleanLTPK(void)
{
    printf("Storage_CleanLTPK\n");

    memset(__id, 0, ENTITY_IDENTIFIER_LENGTH);
    memset(__ltpk, 0, ED25519_PUBLIC_KEY_LENGTH);

    return TINY_RET_OK;
}

static TinyRet Storage_SaveLTPK(EntityIdentifier *id, ED25519PublicKey *LTPK)
{
    printf("Storage_SaveLTPK\n");

    memcpy(__id, id->value, id->length);
    memcpy(__ltpk, LTPK->value, LTPK->length);

    return TINY_RET_OK;
}

static TinyRet Storage_RemoveLTPK(EntityIdentifier *id)
{
    printf("Storage_RemoveLTPK\n");

    memset(__id, 0, ENTITY_IDENTIFIER_LENGTH);
    memset(__ltpk, 0, ED25519_PUBLIC_KEY_LENGTH);

    return TINY_RET_OK;
}

static TinyRet Storage_LoadLTPK(EntityIdentifier *id, ED25519PublicKey *LTPK)
{
    printf("Storage_LoadLTPK\n");

    if (strncmp((const char *)__id, (const char *)(id->value), id->length) == 0)
    {
        memcpy(LTPK->value, __ltpk, ED25519_PUBLIC_KEY_LENGTH);
        LTPK->length = ED25519_PUBLIC_KEY_LENGTH;
        return TINY_RET_OK;
    }

    return TINY_RET_E_NOT_FOUND;
}

uint32_t Storage_GetLTPKCount(void)
{
    printf("Storage_GetLTPKCount\n");

    return 1;
}

TinyRet Storage_LoadLTPKAt(int index, EntityIdentifier *id, ED25519PublicKey *LTPK)
{
    printf("Storage_LoadLTPKAt: %d\n", index);

    memcpy(LTPK->value, __ltpk, ED25519_PUBLIC_KEY_LENGTH);
    LTPK->length = ED25519_PUBLIC_KEY_LENGTH;
    return TINY_RET_OK;
}

static HapPersistence _impl =
        {
                .Initialize     = Storage_Initialize,
                .Destroy        = Storage_Destroy,
                .SaveKeyPair    = Storage_SaveKeyPair,
                .LoadKeyPair    = Storage_LoadKeyPair,
                .CleanLTPK      = Storage_CleanLTPK,
                .SaveLTPK       = Storage_SaveLTPK,
                .RemoveLTPK     = Storage_RemoveLTPK,
                .LoadLTPK       = Storage_LoadLTPK,
                .GetLTPKCount   = Storage_GetLTPKCount,
                .LoadLTPKAt     = Storage_LoadLTPKAt,
        };

HapPersistence * HapPersistenceImpl_GetInstance(void)
{
    return &_impl;
}
