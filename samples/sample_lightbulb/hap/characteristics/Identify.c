/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Identify.c
 *
 * @remark
 *
 */

#include "Identify.h"

Property * Identify(PropertyOnGet onGet, PropertyOnSet onSet)
{
    Property *thiz = Property_New();
    if (thiz != NULL)
    {
        Urn_Initialize(&thiz->type, "homekit", PROPERTY, "identify", 0x14);
        thiz->accessType = ACCESS_WRITE;
        thiz->data.type = DATATYPE_BOOL;
        thiz->onGet = onGet;
        thiz->onSet = onSet;

        thiz->data.value.boolValue.value = false;
    }

    return thiz;
}