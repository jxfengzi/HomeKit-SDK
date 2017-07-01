/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_api.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_API_H__
#define __TINY_API_H__


#ifdef _MSC_VER
#   if (defined tiny_shared_EXPORTS)
#       define TINY_EXPORT _declspec(dllexport)
#   else
#       define TINY_EXPORT _declspec(dllimport)
#   endif
#   define DLLLOCAL
#else
#   ifdef __ANDROID__
#       define TINY_EXPORT
#       define TINY_LOCAL
#   else
#       define TINY_EXPORT __attribute__ ((visibility("default")))
#       define TINY_LOCAL __attribute__ ((visibility("hidden")))
#   endif /* __ANDROID__ */
#endif /* _MSC_VER */


#ifdef TINY_STATIC
#   define TINY_API
#else
#   define TINY_API TINY_EXPORT
#endif /* TINY_STATIC */


#endif /* __TINY_API_H__ */
