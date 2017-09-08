/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   str_split.h
*
* @remark
*		set tabstop=4
*		set shiftwidth=4
*		set expandtab
*/

#ifndef __STR_SPLIT_H__
#define __STR_SPLIT_H__

#include <tiny_lor.h>
#include "tiny_base.h"
#include "tiny_api.h"

TINY_BEGIN_DECLS


/**
 * usage:
 *     char *s = "urn:schemas-upnp-org:device:mediaserver:1"
 *     char group[10][128];
 *     uint32_t ret = str_split(s, ":", group, 10);
 *
 *     result:  (ret > 0)
 *       ret = 5;
 *       group[0] = "urn"
 *       group[1] = "schemas-upnp-org"
 *       group[2] = "device"
 *       group[3] = "mediaserver"
 *       group[4] = "1"
 */
TINY_API
TINY_LOR
uint32_t str_split(const char *str, const char *c, char group[][128], uint32_t groupCount);


TINY_END_DECLS

#endif /* __STR_SPLIT_H__ */
