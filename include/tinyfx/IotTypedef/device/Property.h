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
#include "api/iot_api.h"
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
    uint8_t             operation;
};

IOT_API
TINY_LOR
Property* Property_New(void);

IOT_API
TINY_LOR
void Property_Delete(Property *thiz);

IOT_API
TINY_LOR
bool Property_IsReadable(Property *thiz);

IOT_API
TINY_LOR
bool Property_IsWritable(Property *thiz);

IOT_API
TINY_LOR
bool Property_IsNotifiable(Property *thiz);


TINY_END_DECLS

#endif /* __PROPERTY_H__ */
