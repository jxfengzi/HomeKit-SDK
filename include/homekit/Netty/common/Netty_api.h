/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   Netty_api.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __NETTY_API_H__
#define __NETTY_API_H__


#ifdef _MSC_VER
#   if (defined netty_shared_EXPORTS)
#       define NETTY_EXPORT _declspec(dllexport)
#   else
#       define NETTY_EXPORT _declspec(dllimport)
#   endif
#   define DLLLOCAL
#else
#   ifdef __ANDROID__
#       define NETTY_EXPORT
#       define NETTY_LOCAL
#   else
#       define NETTY_EXPORT __attribute__ ((visibility("default")))
#       define NETTY_LOCAL __attribute__ ((visibility("hidden")))
#   endif /* __ANDROID__ */
#endif /* _MSC_VER */


#ifdef NETTY_STATIC
#   define NETTY_API
#else
#   define NETTY_API NETTY_EXPORT
#endif /* NETTY_STATIC */


#endif /* __NETTY_API_H__ */
