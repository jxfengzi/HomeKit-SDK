/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   thing_api.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __THING_API_H__
#define __THING_API_H__


#ifdef _MSC_VER
#   if  (defined iot_thing_shared_EXPORTS)
#       define THING_EXPORT _declspec(dllexport)
#   else
#       define THING_EXPORT _declspec(dllimport)
#   endif
#   define THING_LOCAL
#else
#   ifdef __ANDROID__
#       define THING_EXPORT
#       define THING_LOCAL
#   else
#       define THING_EXPORT __attribute__ ((visibility("default")))
#       define THING_LOCAL __attribute__ ((visibility("hidden")))
#   endif /* __ANDROID__ */
#endif /* _MHAP_VER */


#ifdef IOT_THING_STATIC
#   define THING_API
#else
#   define THING_API THING_EXPORT
#endif /* IOT_THING_STATIC */


#endif /* __THING_API_H__ */
