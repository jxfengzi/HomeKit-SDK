/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   AccessoryInformation.c
 *
 * @remark
 *
 */

#include "AccessoryInformation.h"
#include "Identify.h"
#include "Manufacturer.h"
#include "Model.h"
#include "Name.h"
#include "SerialNumber.h"
#include "FirmwareRevision.h"

TINY_LOR
Service * AccessoryInformation(PropertyOnGet onGet, PropertyOnSet onSet)
{
    Service *thiz = Service_New();
    if (thiz != NULL)
    {
        Urn_Initialize(&thiz->type, "homekit", SERVICE, "accessory-information", 0x3E);

        TinyList_AddTail(&thiz->properties, Identify(onGet, onSet));
        TinyList_AddTail(&thiz->properties, Manufacturer(onGet, onSet));
        TinyList_AddTail(&thiz->properties, Model(onGet, onSet));
        TinyList_AddTail(&thiz->properties, Name(onGet, onSet));
        TinyList_AddTail(&thiz->properties, SerialNumber(onGet, onSet));
        TinyList_AddTail(&thiz->properties, FirmwareRevision(onGet, onSet));
    }

    return thiz;
}
