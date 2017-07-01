/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   hap_api.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __HAP_API_H__
#define __HAP_API_H__


#ifdef _MSC_VER
#   if  (defined accessoryimpl_shared_EXPORTS)
#       define ACCESSORY_EXPORT _declspec(dllexport)
#   else
#       define ACCESSORY_EXPORT _declspec(dllimport)
#   endif
#   define ACCESSORY_LOCAL
#else
#   ifdef __ANDROID__
#       define ACCESSORY_EXPORT
#       define ACCESSORY_LOCAL
#   else
#       define ACCESSORY_EXPORT __attribute__ ((visibility("default")))
#       define ACCESSORY_LOCAL __attribute__ ((visibility("hidden")))
#   endif /* __ANDROID__ */
#endif /* _MHAP_VER */


#ifdef HAP_ACCESSORY_STATIC
#   define HAP_API
#else
#   define HAP_API ACCESSORY_EXPORT
#endif /* IOT_STATIC */


#endif /* __HAP_API_H__ */
