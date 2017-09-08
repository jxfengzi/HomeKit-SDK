/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   FirmwareRevision.c
 *
 * @remark
 *
 */

#include "FirmwareRevision.h"

TINY_LOR
Property * FirmwareRevision(PropertyOnGet onGet, PropertyOnSet onSet)
{
    Property *thiz = Property_New();
    if (thiz != NULL)
    {
        Urn_Initialize(&thiz->type, "homekit", PROPERTY, "firmware-revision", 0x52);
        thiz->accessType = ACCESS_READ;
        thiz->data.type = DATATYPE_STRING;
        thiz->onGet = NULL;
        thiz->onSet = NULL;

        Data_SetStringValue(&thiz->data, "1.0.0");
    }

    return thiz;
}
