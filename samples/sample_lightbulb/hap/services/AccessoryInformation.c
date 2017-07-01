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
#include "../characteristics/Identify.h"
#include "../characteristics/Manufacturer.h"
#include "../characteristics/Model.h"
#include "../characteristics/Name.h"
#include "../characteristics/SerialNumber.h"
#include "../characteristics/FirmwareRevision.h"

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