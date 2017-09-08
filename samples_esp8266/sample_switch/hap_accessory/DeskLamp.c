/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Lightbulb.c
 *
 * @remark
 *
 */

#include "hap/accessories/DeskLamp.h"
#include "hap/services/Lightbulb.h"
#include "AccessoryInformation.h"

TINY_LOR
Accessory * DeskLamp(PropertyOnGet onGet, PropertyOnSet onSet)
{
    Accessory * thiz = Accessory_New();
    if (thiz != NULL)
    {
        TinyList_AddTail(&thiz->services, AccessoryInformation(onGet, onSet));
        TinyList_AddTail(&thiz->services, Lightbulb(onGet, onSet));
    }

    return thiz;
}
