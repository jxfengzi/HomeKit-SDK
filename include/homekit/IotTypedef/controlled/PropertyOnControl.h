/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   PropertyOnControl.h
 *
 * @remark
 *
 */

#ifndef __PROPERTY_ON_CONTROL_H__
#define __PROPERTY_ON_CONTROL_H__

#include "tiny_base.h"

TINY_BEGIN_DECLS


struct _Property;
typedef struct _Property Property;

typedef void (*PropertyOnGet)(Property *property);
typedef void (*PropertyOnSet)(Property *property);


TINY_END_DECLS

#endif /* __PROPERTY_ON_CONTROL_H__ */