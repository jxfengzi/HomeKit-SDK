/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Property.h
 *
 * @remark
 *
 */

#ifndef __PROPERTY_H__
#define __PROPERTY_H__

#include "tiny_base.h"
#include "error/IotError.h"
#include "common/typedef_api.h"
#include "unit/Unit.h"
#include "urn/Urn.h"
#include "data/Data.h"
#include "access/AccessType.h"
#include <controlled/PropertyOnControl.h>

TINY_BEGIN_DECLS


struct _Property
{
    uint16_t            aiid;
    uint16_t            siid;
    uint16_t            iid;
    uint16_t            accessType;
    Urn                 type;
    Unit                unit;
    Data                data;
    bool                changed;
    PropertyOnGet       onGet;
    PropertyOnSet       onSet;
    int                 status;
    uint16_t            operation;
};

TYPEDEF_API
TINY_LOR
Property* Property_New(void);

TYPEDEF_API
TINY_LOR
void Property_Delete(Property *thiz);

TYPEDEF_API
TINY_LOR
bool Property_IsReadable(Property *thiz);

TYPEDEF_API
TINY_LOR
bool Property_IsWritable(Property *thiz);

TYPEDEF_API
TINY_LOR
bool Property_IsNotifiable(Property *thiz);


TINY_END_DECLS

#endif /* __PROPERTY_H__ */
