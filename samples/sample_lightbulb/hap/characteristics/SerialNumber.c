/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   SerialNumber.c
 *
 * @remark
 *
 */

#include "SerialNumber.h"

Property * SerialNumber(PropertyOnGet onGet, PropertyOnSet onSet)
{
    Property *thiz = Property_New();
    if (thiz != NULL)
    {
        Urn_Initialize(&thiz->type, "homekit", PROPERTY, "serial-number", 0x30);
        thiz->accessType = ACCESS_READ;
        thiz->data.type = DATATYPE_STRING;
        thiz->onGet = NULL;
        thiz->onSet = NULL;

        Data_SetStringValue(&thiz->data, "2017-6-9");
    }

    return thiz;
}