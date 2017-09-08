/**
 *
 * Copyright (C) 2007-2012 jxfengzi
 *
 * @author jxfengzi@gmail.com
 * @date   2010-5-25
 *
 * @file   TinyContainerListener.h
 *
 * @version 2010.5.25
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_CONTAINER_LISTENER_H__
#define __TINY_CONTAINER_LISTENER_H__

#include "tiny_base.h"

TINY_BEGIN_DECLS


typedef void(*TinyContainerItemDeleteListener) (void * data, void *ctx);
typedef bool(*TinyContainerItemVisit) (void * data, void * ctx);


TINY_END_DECLS


#endif /* __TINY_CONTAINER_LISTENER_H__ */
