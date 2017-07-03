/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   On.c
 *
 * @remark
 *
 */

#include "hap/characteristics/On.h"

Property * On(PropertyOnGet onGet, PropertyOnSet onSet)
{
    Property *thiz = Property_New();
    if (thiz != NULL)
    {
        Urn_Initialize(&thiz->type, "homekit", PROPERTY, "on", 0x25);
        thiz->accessType = ACCESS_READ | ACCESS_WRITE | ACCESS_NOTIFY;
        thiz->data.type = DATATYPE_BOOL;
        thiz->data.value.boolValue.value = true;
        thiz->onGet = onGet;
        thiz->onSet = onSet;
    }

    return thiz;
}
