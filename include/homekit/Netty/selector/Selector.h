/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   Selector.h
*
* @remark
*		set tabstop=4
*		set shiftwidth=4
*		set expandtab
*/

#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include "tiny_base.h"

TINY_BEGIN_DECLS


struct _Selector;
typedef struct _Selector Selector;

typedef TinyRet (*Selector_P_PreSelect)(Selector *thiz, void *ctx);
typedef TinyRet (*Selector_P_PostSelect)(Selector *thiz, void *ctx);
typedef TinyRet (*Selector_P_SelectTimeout)(Selector *thiz, void *ctx);

struct _Selector
{
    int                             max_fd;
    fd_set                          read_set;
    fd_set                          write_set;
    Selector_P_PreSelect            onPreSelect;
    Selector_P_PostSelect           onPostSelect;
    Selector_P_SelectTimeout        onSelectTimeout;
    int64_t                         us;
    void                          * ctx;
};

typedef enum _SelectorOperation
{
    SELECTOR_OP_READ = 0,
    SELECTOR_OP_WRITE = 1,
} SelectorOperation;

//Selector * Selector_New(void);
//void Selector_Delete(Selector *thiz);
TinyRet Selector_Construct(Selector *thiz);
TinyRet Selector_Dispose(Selector *thiz);

TinyRet Selector_Loop(Selector *thiz);
void Selector_Register(Selector *thiz, int fd, SelectorOperation op);
bool Selector_IsReadable(Selector *thiz, int fd);
bool Selector_IsWriteable(Selector *thiz, int fd);


TINY_END_DECLS

#endif /* __SELECTOR_H__ */
