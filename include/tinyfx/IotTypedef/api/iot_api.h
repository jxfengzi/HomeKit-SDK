/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   iot_api.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __IOT_API_H__
#define __IOT_API_H__


#ifdef _MSC_VER
#   if  (defined tinyfx_EXPORTS)
#       define IOT_EXPORT _declspec(dllexport)
#   else
#       define IOT_EXPORT _declspec(dllimport)
#   endif
#   define IOT_LOCAL
#else
#   ifdef __ANDROID__
#       define IOT_EXPORT
#       define IOT_LOCAL
#   else
#       define IOT_EXPORT __attribute__ ((visibility("default")))
#       define IOT_LOCAL __attribute__ ((visibility("hidden")))
#   endif /* __ANDROID__ */
#endif /* _MSC_VER */


#ifdef IOT_STATIC
#   define IOT_API
#else
#   define IOT_API IOT_EXPORT
#endif /* IOT_STATIC */


#endif /* __IOT_API_H__ */
