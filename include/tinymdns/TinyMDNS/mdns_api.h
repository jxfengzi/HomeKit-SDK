/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   mdns_api.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __MDNS_API_H__
#define __MDNS_API_H__


#ifdef _MSC_VER
#   if (defined tinymdns_EXPORTS)
#       define MDNS_EXPORT _declspec(dllexport)
#   else
#       define MDNS_EXPORT _declspec(dllimport)
#   endif
#   define MDNS_LOCAL
#else
#   ifdef __ANDROID__
#       define MDNS_EXPORT
#       define MDNS_LOCAL
#   else
#       define MDNS_EXPORT __attribute__ ((visibility("default")))
#       define MDNS_LOCAL __attribute__ ((visibility("hidden")))
#   endif /* __ANDROID__ */
#endif /* _MSC_VER */


#ifdef TINYMDNS_STATIC
#   define MDNS_API
#else
#   define MDNS_API MDNS_EXPORT
#endif /* TINYMDNS_STATIC */


#endif /* __MDNS_API_H__ */
