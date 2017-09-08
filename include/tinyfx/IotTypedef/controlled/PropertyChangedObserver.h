/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   PropertyChangedObserver.h
 *
 * @remark
 *
 */

#ifndef __PROPERTY_CHANGED_OBSERVER_H__
#define __PROPERTY_CHANGED_OBSERVER_H__

#include <tiny_base.h>
#include "api/iot_api.h"
#include "PropertyChangedListener.h"

TINY_BEGIN_DECLS


typedef struct _PropertyChangedObserver
{
    PropertyChangedListener       listener;
    void                        * data;
    void                        * ctx;
} PropertyChangedObserver;

IOT_API
TINY_LOR
PropertyChangedObserver* PropertyChangedObserver_New(void);

IOT_API
TINY_LOR
void PropertyChangedObserver_Delete(PropertyChangedObserver *thiz);


TINY_END_DECLS

#endif /* __PROPERTY_CHANGED_OBSERVER_H__ */