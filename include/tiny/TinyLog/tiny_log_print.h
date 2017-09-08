/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_log_print.h
 *
 * @remark
 *
 */

#ifndef __TINY_LOG_PRINT_H__
#define __TINY_LOG_PRINT_H__

#include <stdarg.h>
#include "tiny_base.h"
#include "tiny_api.h"


TINY_BEGIN_DECLS


#ifndef ESP

/*
 * mi log priority values, in ascending priority order.
 */
typedef enum _tiny_log_priority
{
    TINY_LOG_UNKNOWN = 0,
    TINY_LOG_VERBOSE,
    TINY_LOG_DEBUG,
    TINY_LOG_INFO,
    TINY_LOG_WARN,
    TINY_LOG_ERROR,
} TINY_LOG_priority;

/*
 * Send a simple string to the log.
 */
TINY_API
TINY_LOR
int __tiny_log_write(int prio, const char *tag, const char *text);

/*
 * Send a formatted string to the log, used like printf(fmt,...)
 */
#if defined(__GNUC__)
TINY_API
TINY_LOR
int __tiny_log_print(int prio, const char *tag, const char *fmt, ...) __attribute__((format(printf, 3, 4)));
#else
TINY_API
TINY_LOR
int __tiny_log_print(int prio, const char *tag, const char *fmt, ...);
#endif

/*
 * A variant of __tiny_log_print() that takes a va_list to list
 * additional parameters.
 */
TINY_API
TINY_LOR
int __tiny_log_vprint(int prio, const char *tag, const char *fmt, va_list ap);

#endif /* ESP */


TINY_END_DECLS

#endif /* __TINY_LOG_PRINT_H__ */
