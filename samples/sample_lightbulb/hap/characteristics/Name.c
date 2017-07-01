/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Name.c
 *
 * @remark
 *
 */

#include "Name.h"

Property * Name(PropertyOnGet onGet, PropertyOnSet onSet)
{
    Property *thiz = Property_New();
    if (thiz != NULL)
    {
        Urn_Initialize(&thiz->type, "homekit", PROPERTY, "name", 0x23);
        thiz->accessType = ACCESS_READ;
        thiz->data.type = DATATYPE_STRING;
        thiz->onGet = NULL;
        thiz->onSet = NULL;

        Data_SetStringValue(&thiz->data, "OySwitch");
    }

    return thiz;
}