/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   Ed25519.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __ED25519_H__
#define __ED25519_H__

#include <tiny_base.h>
#include <stddef.h>
#include <tiny_lor.h>
#include "common/crypto_api.h"

TINY_BEGIN_DECLS


#define ED25519_PRIVATE_KEY_LENGTH      64
#define ED25519_PUBLIC_KEY_LENGTH       32
#define ED25519_SIGNATURE_LENGTH        64

typedef struct _ED25519PrivateKey
{
    uint8_t value[ED25519_PRIVATE_KEY_LENGTH];
    uint32_t length;
} ED25519PrivateKey;

typedef struct _ED25519PublicKey
{
    uint8_t value[ED25519_PUBLIC_KEY_LENGTH];
    uint32_t length;
} ED25519PublicKey;

typedef struct _ED25519Signature
{
    uint8_t value[ED25519_SIGNATURE_LENGTH];
    uint32_t length;
} ED25519Signature;

typedef struct _Ed25519KeyPair
{
    ED25519PrivateKey privateKey;
    ED25519PublicKey publicKey;
} Ed25519KeyPair;

CRYPTO_API
TINY_LOR
void Ed25519_GenerateKeyPair(Ed25519KeyPair *thiz);

CRYPTO_API
TINY_LOR
void Ed25519KeyPair_Copy(Ed25519KeyPair *dst, Ed25519KeyPair *src);

CRYPTO_API
TINY_LOR
TinyRet Ed25519_Verify(ED25519PublicKey *key,
                       ED25519Signature *signature,
                       const uint8_t *data,
                       uint32_t length);

CRYPTO_API
TINY_LOR
void Ed25519_Sign(Ed25519KeyPair *keys,
                  ED25519Signature *signature,
                  const uint8_t *data,
                  uint32_t length);


TINY_END_DECLS

#endif /* __ED25519_H__ */