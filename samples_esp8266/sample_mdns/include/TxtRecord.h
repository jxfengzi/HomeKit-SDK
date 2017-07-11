/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   TxtRecord.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

/*  Simple string->void* hashtable, very static and bare minimal, but efficient */
#ifndef __TXT_RECORD_H__
#define __TXT_RECORD_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include "bonjour_api.h"

TINY_BEGIN_DECLS


struct _TxtRecord;
typedef struct _TxtRecord TxtRecord;

/**
 * must pass a prime#
 */
BONJOUR_API
TINY_LOR
TxtRecord *TxtRecord_New(int prime);

/**
 * free the hashtable and all entries
 */
BONJOUR_API
TINY_LOR
void TxtRecord_Delete(TxtRecord *thiz);

/**
 * caller responsible for key storage, no copies made
 *
 * set val to NULL to clear an entry, memory is reused but never free'd
 * (# of keys only grows to peak usage)
 *
 * Note: don't free it b4 xht_free()!
 */
BONJOUR_API
TINY_LOR
void TxtRecord_Set(TxtRecord *thiz, char *key, void *val);

BONJOUR_API
TINY_LOR
void TxtRecord_SetInteger(TxtRecord *thiz, char *key, int val);

/**
 * returns value of val if found, or NULL
 */
BONJOUR_API
TINY_LOR
void *TxtRecord_Get(TxtRecord *thiz, char *key);

/**
 * Unlike xht_set() where key/val is in caller's mem, here they are
 * copied into xht and free'd when val is 0 or xht_free()
 */
BONJOUR_API
TINY_LOR
void TxtRecord_Store(TxtRecord *thiz, char *key, int klen, void *val, int vlen);

/**
 * pass a function that is called for every key that has a value set
 */
typedef void (*txtrecord_walker_t)(TxtRecord *thiz, char *key, void *val, void *arg);

TINY_LOR
void TxtRecord_Walk(TxtRecord *thiz, txtrecord_walker_t w, void *arg);


TINY_END_DECLS

#endif	/* __TXT_RECORD_H__ */
