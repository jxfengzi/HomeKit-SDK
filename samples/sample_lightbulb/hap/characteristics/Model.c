/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Model.c
 *
 * @remark
 *
 */

#include "Model.h"

Property * Model(PropertyOnGet onGet, PropertyOnSet onSet)
{
    Property *thiz = Property_New();
    if (thiz != NULL)
    {
        Urn_Initialize(&thiz->type, "homekit", PROPERTY, "model", 0x21);
        thiz->accessType = ACCESS_READ;
        thiz->data.type = DATATYPE_STRING;
        thiz->onGet = NULL;
        thiz->onSet = NULL;

        Data_SetStringValue(&thiz->data, "Switch-2017");
    }

    return thiz;
}