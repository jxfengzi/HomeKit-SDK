/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   typedef_api.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TYPEDEF_API_H__
#define __TYPEDEF_API_H__


#ifdef _MSC_VER
#   if  (defined iot_typedef_shared_EXPORTS)
#       define TYPEDEF_EXPORT _declspec(dllexport)
#   else
#       define TYPEDEF_EXPORT _declspec(dllimport)
#   endif
#   define TYPEDEF_LOCAL
#else
#   ifdef __ANDROID__
#       define TYPEDEF_EXPORT
#       define TYPEDEF_LOCAL
#   else
#       define TYPEDEF_EXPORT __attribute__ ((visibility("default")))
#       define TYPEDEF_LOCAL __attribute__ ((visibility("hidden")))
#   endif /* __ANDROID__ */
#endif /* _MHAP_VER */


#ifdef IOT_TYPEDEF_STATIC
#   define TYPEDEF_API
#else
#   define TYPEDEF_API TYPEDEF_EXPORT
#endif /* IOT_TYPEDEF_STATIC */


#endif /* __TYPEDEF_API_H__ */
