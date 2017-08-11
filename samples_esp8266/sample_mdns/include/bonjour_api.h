/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   bonjour_api.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __BONJOUR_API_H__
#define __BONJOUR_API_H__


#ifdef _MSC_VER
#   ifdef bonjour_shared_EXPORTS
#       define DLLEXPORT _declspec(dllexport)
#   else
#       define DLLEXPORT _declspec(dllimport)
#   endif
#   define DLLLOCAL
#else
#   ifdef __ANDROID__
#       define DLLEXPORT
#       define DLLLOCAL
#   else
#       define DLLEXPORT __attribute__ ((visibility("default")))
#       define DLLLOCAL __attribute__ ((visibility("hidden")))
#   endif /* __ANDROID__ */
#endif /* _MSC_VER */


#ifdef BONJOUR_STATIC
#   define BONJOUR_API
#else
#   define BONJOUR_API DLLEXPORT
#endif /* BONJOUR_STATIC */


#endif /* __BONJOUR_API_H__ */
