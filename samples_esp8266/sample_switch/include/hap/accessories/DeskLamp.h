/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DeskLamp.h
 *
 * @remark
 *
 */

#ifndef __DeskLamp_H__
#define __DeskLamp_H__

#include <device/Accessory.h>
#include <controlled/PropertyOnControl.h>
#include <tiny_base.h>
#include <tiny_lor.h>

TINY_BEGIN_DECLS

TINY_LOR
Accessory * DeskLamp(PropertyOnGet onGet, PropertyOnSet onSet);


TINY_END_DECLS

#endif /* __DeskLamp_H__ */
