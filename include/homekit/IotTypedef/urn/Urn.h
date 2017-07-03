/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2016-7-25
 *
 * @file   Urn.h
 *
 * @remark
 *
 */

#ifndef __URN_H__
#define __URN_H__

#include <tiny_inline.h>
#include "tiny_base.h"
#include "UrnType.h"
#include "constraint/typedef_constraint.h"

TINY_BEGIN_DECLS

/**
 * <URN> ::= "urn:"<namespace>":"<type>":"<name>":"<value>[":"<modified>]
 *
 * urn:homekit-spec:device:Light:00000001
 * urn:homekit-spec:thing:Light:00000001
 * urn:homekit-spec:service:Switch:00000014
 * urn:homekit-spec:property:On:00000030
 *
 * urn:miot-spec:property:On:00000030:philips
 */

struct _Urn
{
    char        namespace[URN_NAMESPACE_LENGTH];
    UrnType     type;
    char        name[URN_NAME_LENGTH];
    uint32_t    value;
};

typedef struct _Urn Urn;

TINY_INLINE
TinyRet Urn_Construct(Urn *thiz)
{
    memset(thiz, 0, sizeof(Urn));
    return TINY_RET_OK;
}

TINY_INLINE
void Urn_Dispose(Urn *thiz)
{
    memset(thiz, 0, sizeof(Urn));
}

TINY_INLINE
void Urn_Initialize(Urn *thiz, const char *ns, UrnType type, const char *name, uint32_t value)
{
    strncpy(thiz->namespace, ns, URN_NAMESPACE_LENGTH);
    thiz->type = type;
    strncpy(thiz->name, name, URN_NAME_LENGTH);
    thiz->value = value;
}


TINY_END_DECLS

#endif /* __URN_H__ */