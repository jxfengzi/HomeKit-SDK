/**
 *
 * Copyright (C) 2007-2012 coding.tom
 *
 * @author jxfengzi@gmail.com
 * @date   2013-5-25
 *
 * @file   TinyMap.h
 *
 * @version 2013.8.6

 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_MAP_H__
#define __TINY_MAP_H__

#include "tiny_base.h"
#include "TinyContainerListener.h"
#include "TinyList.h"

TINY_BEGIN_DECLS


typedef struct _TinyMap
{
    TinyList                            list;
    TinyContainerItemDeleteListener     data_delete_listener;
    void                              * data_delete_listener_ctx;
} TinyMap;

TINY_API TinyMap * TinyMap_New(void);
TINY_API TinyRet TinyMap_Construct(TinyMap *thiz);
TINY_API TinyRet TinyMap_Dispose(TinyMap *thiz);
TINY_API void TinyMap_Delete(TinyMap *thiz);

TINY_API int TinyMap_Foreach(TinyMap * thiz, TinyContainerItemVisit visit, void * ctx);
TINY_API void TinyMap_SetDeleteListener(TinyMap * thiz, TinyContainerItemDeleteListener listener, void *ctx);

TINY_API int TinyMap_GetSize(TinyMap *thiz);
TINY_API int TinyMap_GetCount(TinyMap *thiz);
TINY_API void * TinyMap_GetValueAt(TinyMap *thiz, uint32_t index);
TINY_API void * TinyMap_GetValue(TinyMap *thiz, const char *key);
TINY_API TinyRet TinyMap_Insert(TinyMap *thiz, const char *key, void *value);
TINY_API TinyRet TinyMap_Erase(TinyMap *thiz, const char *key);
TINY_API void TinyMap_Clear(TinyMap *thiz);


TINY_END_DECLS

#endif /* __TINY_MAP_H__ */
