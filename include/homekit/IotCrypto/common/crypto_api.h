/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   crypto_api.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __CRYPTO_API_H__
#define __CRYPTO_API_H__


#ifdef _MSC_VER
#   if  (defined iot_crypto_shared_EXPORTS)
#       define CRYPTO_EXPORT _declspec(dllexport)
#   else
#       define CRYPTO_EXPORT _declspec(dllimport)
#   endif
#   define CRYPTO_LOCAL
#else
#   ifdef __ANDROID__
#       define CRYPTO_EXPORT
#       define CRYPTO_LOCAL
#   else
#       define CRYPTO_EXPORT __attribute__ ((visibility("default")))
#       define CRYPTO_LOCAL __attribute__ ((visibility("hidden")))
#   endif /* __ANDROID__ */
#endif /* _MHAP_VER */


#ifdef IOT_CRYPTO_STATIC
#   define CRYPTO_API
#else
#   define CRYPTO_API CRYPTO_EXPORT
#endif /* IOT_CRYPTO_STATIC */


#endif /* __CRYPTO_API_H__ */
