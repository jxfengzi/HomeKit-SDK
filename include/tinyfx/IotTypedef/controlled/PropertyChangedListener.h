/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   PropertyChangedListener.h
 *
 * @remark
 *
 */

#ifndef __PROPERTY_CHANGED_LISTENER_H__
#define __PROPERTY_CHANGED_LISTENER_H__

#include "tiny_base.h"
#include "device/Property.h"

TINY_BEGIN_DECLS


typedef void (*PropertyChangedListener)(Property *property, void *data, void *ctx);


TINY_END_DECLS

#endif /* __PROPERTY_CHANGED_LISTENER_H__ */