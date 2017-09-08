/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ThingRuntime.h
 *
 * @remark
 *
 */

#ifndef __THING_RUNTIME_H__
#define __THING_RUNTIME_H__

#include <tiny_base.h>
#include <tiny_lor.h>
#include <device/Device.h>
#include <device/Service.h>

TINY_BEGIN_DECLS


struct _ThingRuntime;
typedef struct _ThingRuntime ThingRuntime;

typedef TinyRet (* Thing_Initialize)(ThingRuntime *thiz);
typedef TinyRet (* Thing_Destroy)(ThingRuntime *thiz);
typedef TinyRet (* Thing_Run)(ThingRuntime *thiz, Device *device);
typedef TinyRet (* Thing_Stop)(ThingRuntime *thiz);

struct _ThingRuntime
{
    const char            * Name;
    Thing_Initialize        Initialize;
    Thing_Run               Run;
    Thing_Stop              Stop;
    Thing_Destroy           Destroy;
    void                  * persistence;
};

TINY_LOR
void ThingRuntime_Copy(ThingRuntime *dst, ThingRuntime *src);


TINY_END_DECLS

#endif /* __THING_RUNTIME_H__ */
