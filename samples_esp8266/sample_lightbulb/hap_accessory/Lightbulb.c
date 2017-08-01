/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Lightbulb.h
 *
 * @remark
 *
 */

#include "hap/services/Lightbulb.h"
#include "hap/characteristics/On.h"

TINY_LOR
Service * Lightbulb(PropertyOnGet onGet, PropertyOnSet onSet)
{
    Service *thiz = Service_New();
    if (thiz != NULL)
    {
        Urn_Initialize(&thiz->type, "homekit", SERVICE, "lightbulb", 0x43);
        TinyList_AddTail(&thiz->properties, On(onGet, onSet));
    }

    return thiz;
}
