/**
 *
 * Copyright (C) 2007-2012 jxfengzi
 *
 * @author jxfengzi@gmail.com
 * @date   2010-5-25
 *
 * @file   TinyList.h
 *
 * @version 2010.5.25

 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_LIST_H__
#define __TINY_LIST_H__

#include <tiny_api.h>
#include <tiny_base.h>
#include <tiny_lor.h>
#include "TinyContainerListener.h"

TINY_BEGIN_DECLS

struct _TinyNode;
typedef struct _TinyNode TinyNode;

typedef struct _TinyList
{
    void                                * additionalData;
    uint32_t                              size;
    TinyNode                            * first;
    TinyContainerItemDeleteListener       data_delete_listener;
    void                                * data_delete_listener_ctx;
} TinyList;

TINY_API
TINY_LOR
TinyRet TinyList_Construct(TinyList *thiz);

TINY_API
TINY_LOR
TinyRet TinyList_Dispose(TinyList *thiz);

//TINY_API
//TINY_LOR
//TinyList * TinyList_New(void);
//
//TINY_API
//TINY_LOR
//void TinyList_Delete(TinyList *thiz);
//
//TINY_API
//TINY_LOR
//TinyRet TinyList_AddRef(TinyList *thiz);
//
//TINY_API
//TINY_LOR
//TinyRet TinyList_Release(TinyList *thiz);
//
//TINY_API
//TINY_LOR
//TinyList * TinyList_Clone(TinyList *other);

TINY_API
TINY_LOR
int TinyList_Foreach(TinyList * thiz, TinyContainerItemVisit visit, void * ctx);

TINY_API
TINY_LOR
void TinyList_SetDeleteListener(TinyList * thiz, TinyContainerItemDeleteListener listener, void *ctx);

TINY_API
TINY_LOR
void * TinyList_GetHead(TinyList * thiz);

TINY_API
TINY_LOR
void * TinyList_GetTail(TinyList * thiz);

TINY_API
TINY_LOR
TinyRet TinyList_AddHead(TinyList * thiz, void *data);

TINY_API
TINY_LOR
TinyRet TinyList_AddTail(TinyList * thiz, void *data);

TINY_API
TINY_LOR
TinyRet TinyList_RemoveAll(TinyList * thiz);

TINY_API
TINY_LOR
TinyRet TinyList_RemoveHead(TinyList * thiz);

TINY_API
TINY_LOR
TinyRet TinyList_RemoveTail(TinyList * thiz);

//TINY_API
//TINY_LOR
//int TinyList_GetHeadPosition(TinyList * thiz);
//
//TINY_API
//TINY_LOR
//int TinyList_GetTailPosition(TinyList * thiz);
//
//TINY_API
//TINY_LOR
//void * TinyList_GetNext(TinyList * thiz, int pos);
//
//TINY_API
//TINY_LOR
//void * TinyList_GetPrev(TinyList * thiz, int pos);

TINY_API
TINY_LOR
void * TinyList_GetAt(const TinyList * thiz, int pos);

TINY_API
TINY_LOR
TinyRet TinyList_RemoveAt(TinyList * thiz, int pos);

//TINY_API
//TINY_LOR
//TinyRet TinyList_SetAt(TinyList * thiz, int pos, void * data);

TINY_API
TINY_LOR
TinyRet TinyList_InsertAfter(TinyList * thiz, int pos, void * data);

TINY_API
TINY_LOR
TinyRet TinyList_InsertBefore(TinyList * thiz, int pos, void * data);

//TINY_API
//TINY_LOR
//void * TinyList_FindIndex(TinyList * thiz, int index);

//TINY_API
//TINY_LOR
//int TinyList_GetCount(TinyList * thiz);
//
//TINY_API
//TINY_LOR
//int TinyList_GetSize(TinyList * thiz);

//TINY_API
//TINY_LOR
//bool TinyList_IsEmpty(TinyList * thiz);


TINY_END_DECLS


#endif /* __TINY_LIST_H__ */
