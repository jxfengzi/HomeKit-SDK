/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   Model.h
 *
 * @remark
 *
 */

#ifndef __Characteristic_Model_H__
#define __Characteristic_Model_H__

#include <device/Property.h>
#include <tiny_base.h>
#include <tiny_lor.h>

TINY_BEGIN_DECLS


TINY_LOR
Property * Model(PropertyOnGet onGet, PropertyOnSet onSet);


TINY_END_DECLS

#endif /* __Characteristic_Model_H__ */
