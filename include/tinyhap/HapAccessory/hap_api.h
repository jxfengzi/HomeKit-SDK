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
#   if  (defined tinyhap_EXPORTS)
#       define HAP_EXPORT _declspec(dllexport)
#   else
#       define HAP_EXPORT _declspec(dllimport)
#   endif
#   define HAP_LOCAL
#else
#   ifdef __ANDROID__
#       define HAP_EXPORT
#       define HAP_LOCAL
#   else
#       define HAP_EXPORT __attribute__ ((visibility("default")))
#       define HAP_LOCAL __attribute__ ((visibility("hidden")))
#   endif /* __ANDROID__ */
#endif /* _MHAP_VER */


#ifdef HAP_STATIC
#   define HAP_API
#else
#   define HAP_API HAP_EXPORT
#endif /* HAP_STATIC */


#endif /* __HAP_API_H__ */
