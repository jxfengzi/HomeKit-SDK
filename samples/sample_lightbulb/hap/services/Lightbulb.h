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

#ifndef __Service_Lightbulb_H__
#define __Service_Lightbulb_H__

#include <device/Service.h>
#include <controlled/PropertyOnControl.h>
#include "tiny_base.h"

TINY_BEGIN_DECLS


Service * Lightbulb(PropertyOnGet onGet, PropertyOnSet onSet);


TINY_END_DECLS

#endif /* __Service_Lightbulb_H__ */
