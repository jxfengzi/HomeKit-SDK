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

#include "hap/persistence/HapPersistenceImpl.h"
#include "ControllerInfo.h"

ICACHE_RODATA_ATTR
static uint8_t     __privateKey[ED25519_PRIVATE_KEY_LENGTH] =
{
    0xe1, 0x9c, 0x69, 0x12, 0xa9, 0x19, 0x9e, 0x39,
    0xab, 0x8c, 0x71, 0xad, 0x4f, 0xbe, 0x39, 0xb1,
    0x53, 0x84, 0x12, 0x98, 0x80, 0x0d, 0xa0, 0x10,
    0xc3, 0x99, 0xbf, 0x83, 0x24, 0xd1, 0x48, 0x05,
    0x9e, 0x4c, 0x4a, 0x38, 0x58, 0x43, 0xe4, 0xc3,
    0xfa, 0x2d, 0xfb, 0x8c, 0x69, 0xb9, 0xcc, 0xd8,
    0x39, 0x65, 0xea, 0xd8, 0xce, 0x5f, 0x76, 0x46,
    0xdf, 0xb4, 0xbb, 0xbc, 0x86, 0x95, 0x8d, 0xd3
};

ICACHE_RODATA_ATTR
static uint8_t     __publicKey[ED25519_PUBLIC_KEY_LENGTH] =
{
    0x9e, 0x4c, 0x4a, 0x38, 0x58, 0x43, 0xe4, 0xc3,
    0xfa, 0x2d, 0xfb, 0x8c, 0x69, 0xb9, 0xcc, 0xd8,
    0x39, 0x65, 0xea, 0xd8, 0xce, 0x5f, 0x76, 0x46,
    0xdf, 0xb4, 0xbb, 0xbc, 0x86, 0x95, 0x8d, 0xd3
};

static ControllerInfo info;
static bool __keypairSaved = true;

/* NOTICE---this is for 512KB spi flash.
 * you can change to other sector if you use other size spi flash. */
#define ESP_PARAM_START_SEC     0x3D

TINY_LOR
static void print_binary(const char *tag, const uint8_t *value, uint32_t length)
{
    int i = 0;

    printf("[ %s:%d ] ", tag, length);

    for (i = 0; i < length; ++i)
    {
        printf("%02x ", value[i]);
    }
    printf("\n");
}

TINY_LOR
static TinyRet Storage_Initialize(void)
{
    printf("Storage_Initialize\n");

    memset(&info, 0, sizeof(ControllerInfo));

    ControllerInfo_Read(&info);

    return TINY_RET_OK;
}

TINY_LOR
static TinyRet Storage_Destroy(void)
{
    printf("Storage_Destroy\n");

    return TINY_RET_OK;
}

TINY_LOR
static TinyRet Storage_SaveKeyPair(Ed25519KeyPair *keys)
{
    printf("Storage_SaveKeyPair\n");

    __keypairSaved = true;
    memcpy(__privateKey, keys->privateKey.value, keys->privateKey.length);
    memcpy(__publicKey, keys->publicKey.value, keys->publicKey.length);

    return TINY_RET_OK;
}

TINY_LOR
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

TINY_LOR
static TinyRet Storage_CleanLTPK(void)
{
    printf("Storage_CleanLTPK\n");

    memset(info.id, 0, ENTITY_IDENTIFIER_LENGTH);
    memset(info.ltpk, 0, ED25519_PUBLIC_KEY_LENGTH);

    ControllerInfo_Write(&info);

    return TINY_RET_OK;
}

TINY_LOR
static TinyRet Storage_SaveLTPK(EntityIdentifier *id, ED25519PublicKey *LTPK)
{
    printf("Storage_SaveLTPK: %s\n", id->value);

    memset(&info, 0, sizeof(ControllerInfo));
    memcpy(info.id, id->value, id->length);
    memcpy(info.ltpk, LTPK->value, LTPK->length);

    ControllerInfo_Write(&info);

    return TINY_RET_OK;
}

TINY_LOR
static TinyRet Storage_RemoveLTPK(EntityIdentifier *id)
{
    printf("Storage_RemoveLTPK\n");

    memset(info.id, 0, ENTITY_IDENTIFIER_LENGTH);
    memset(info.ltpk, 0, ED25519_PUBLIC_KEY_LENGTH);
    ControllerInfo_Write(&info);

    return TINY_RET_OK;
}

TINY_LOR
static TinyRet Storage_LoadLTPK(EntityIdentifier *id, ED25519PublicKey *LTPK)
{
    printf("Storage_LoadLTPK: %s\n", id->value);
    printf("id: %s\n", info.id);

    if (strncmp((const char *)info.id, (const char *)(id->value), id->length) == 0)
    {
        memcpy(LTPK->value, info.ltpk, ED25519_PUBLIC_KEY_LENGTH);
        LTPK->length = ED25519_PUBLIC_KEY_LENGTH;
        printf("LoadLTPK OK\n");
        return TINY_RET_OK;
    }

    printf("LoadLTPK FAILED\n");

    return TINY_RET_E_NOT_FOUND;
}

TINY_LOR
uint32_t Storage_GetLTPKCount(void)
{
    printf("Storage_GetLTPKCount\n");

    return 1;
}

TINY_LOR
TinyRet Storage_LoadLTPKAt(int index, EntityIdentifier *id, ED25519PublicKey *LTPK)
{
    printf("Storage_LoadLTPKAt: %d\n", index);

    memcpy(LTPK->value, info.ltpk, ED25519_PUBLIC_KEY_LENGTH);
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

TINY_LOR
HapPersistence * HapPersistenceImpl_GetInstance(void)
{
    return &_impl;
}
