/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   FirmwareRevision.h
 *
 * @remark
 *
 */

#ifndef __Characteristic_FirmwareRevision_H__
#define __Characteristic_FirmwareRevision_H__

#include <device/Property.h>
#include "tiny_base.h"

TINY_BEGIN_DECLS


Property * FirmwareRevision(PropertyOnGet onGet, PropertyOnSet onSet);


TINY_END_DECLS

#endif /* __Characteristic_FirmwareRevision_H__ */
