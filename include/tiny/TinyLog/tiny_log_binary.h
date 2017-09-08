/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   tiny_log_binary.h
 *
 * @remark
 *
 */

#ifndef __TINY_LOG_BINARY_H__
#define __TINY_LOG_BINARY_H__

#include "tiny_base.h"

TINY_BEGIN_DECLS

#ifdef TINY_DEBUG
    TINY_LOR
    TINY_API
    void tiny_print_binary(const char *title, const uint8_t *data, size_t len, bool wrapLines);
    #define LOG_BINARY(T, D, L, W) tiny_print_binary(T, D, L, W)
#else
    #define LOG_BINARY(T, D, L, W)
#endif /* TINY_DEBUG */


TINY_END_DECLS

#endif /* __TINY_LOG_BINARY_H__ */
