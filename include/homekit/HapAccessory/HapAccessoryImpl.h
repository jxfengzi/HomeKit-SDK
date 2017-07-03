/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HapAccessoryImpl.h
 *
 * @remark
 *
 */

#ifndef __HAP_ACCESSORY_IMPL_H__
#define __HAP_ACCESSORY_IMPL_H__

#include "tiny_base.h"
#include "hap_api.h"
#include <thing/ThingRuntime.h>
#include "HapPersistence.h"

TINY_BEGIN_DECLS


HAP_API
TINY_LOR
ThingRuntime * HapAccessoryImpl_GetInstance(HapPersistence *persistence);


TINY_END_DECLS

#endif /* __HAP_ACCESSORY_IMPL_H__ */
