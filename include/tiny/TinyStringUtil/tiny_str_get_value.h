/**
* Copyright (C) 2013-2015
*
* @author jxfengzi@gmail.com
* @date   2013-11-19
*
* @file   str_get_value.h
*
* @remark
*		set tabstop=4
*		set shiftwidth=4
*		set expandtab
*/

#ifndef __STR_GET_VALUE_H__
#define __STR_GET_VALUE_H__

#include <tiny_lor.h>
#include "tiny_base.h"
#include "tiny_api.h"

TINY_BEGIN_DECLS

#if 0
/**
 * usage:
 *     char *s = "server_port=100;control_port=2000;timing_port=30000"
 *     char v0[128];
 *     char v1[128];
 *     char v2[128];
 *     int r0 = str_get_value(s, strlen(s), "server_port=", ";", v0, 128);
 *     int r1 = str_get_value(s, strlen(s), "control_port=", ";", v1, 128);
 *     int r2 = str_get_value(s, strlen(s), "timing_port=", NULL, v2, 128);
 *
 *     result:
 *       r0 = 3;
 *       v0 = 100;
 *       r1 = 4;
 *       v1 = 2000;
 *       r2 = 5;
 *       v2 = 30000;
 */
TINY_API
TINY_LOR
int str_get_value(const char *buf, uint32_t buf_len, const char *start_tag, const char *end_tag, char *value, uint32_t value_len);
#endif


TINY_END_DECLS

#endif /* __STR_GET_VALUE_H__ */
