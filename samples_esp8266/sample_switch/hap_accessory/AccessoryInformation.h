/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   AccessoryInformation.h
 *
 * @remark
 *
 */

#ifndef __Service_AccessoryInformation_H__
#define __Service_AccessoryInformation_H__

#include <device/Service.h>
#include <controlled/PropertyOnControl.h>
#include <tiny_base.h>
#include <tiny_lor.h>

TINY_BEGIN_DECLS


TINY_LOR
Service * AccessoryInformation(PropertyOnGet onGet, PropertyOnSet onSet);


TINY_END_DECLS

#endif /* __Service_AccessoryInformation_H__ */
