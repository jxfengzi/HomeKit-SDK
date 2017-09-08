/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   SerialNumber.h
 *
 * @remark
 *
 */

#ifndef __Characteristic_SerialNumber_H__
#define __Characteristic_SerialNumber_H__

#include <device/Property.h>
#include <tiny_base.h>
#include <tiny_lor.h>

TINY_BEGIN_DECLS

TINY_LOR
Property * SerialNumber(PropertyOnGet onGet, PropertyOnSet onSet);


TINY_END_DECLS

#endif /* __Characteristic_SerialNumber_H__ */
