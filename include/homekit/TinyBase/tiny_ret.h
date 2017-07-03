/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_ret.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 *
 * @description
 *
 *  Values are 32 bit values layed out as follows:
 *  
 *   7 65 43210  76543210  76543210  76543210 |
 *  +-+--+------------------------------------+
 *  |S|EL|             Code                   |
 *  +-+--+------------------------------------+
 *
 *  S - Severity - indicates success/fail
 *      0 - Success
 *      1 - Fail
 *
 *  EL - Error level
 *      00 - General Error
 *      01 - Serious Error
 *      10 - Fatal Error
 *
 * 1. return value
 *      return TINY_RET_OK;
 *      return TINY_RET_E_SOCKET_FD;
 *      return TINY_RET_E_SOCKET_WRITE;
 *
 * 2. get return status
 *      TinyRet ret = tiny_tcp_async_connect(...);
 *      if (RET_SUCCEEDED(ret))
 *      {
 *          if (ret == TINY_RET_SOCKET_CONNECTED)
 *          {
 *              ...
 *          }
 *
 *          else if (ret == TINY_RET_SOCKET_CONNECTING)
 *          {
 *              ...
 *          }
 *      }
 *      else
 *      {
 *        ...
 *      }
 *
 *      if (RET_FAILED(ret))
 *      {
 *          if (ret == TINY_RET_SOCKET_CONNECT_FAILED)
 *          {
 *              ...
 *          }
 *      }
 *
 * 3. get return code
 *      uint32_t code = TINY_RET_GET_CODE(ret);
 *      LOG_D(TAG, "%s", tiny_ret_to_str(ret));
 */

#ifndef __TINY_RET_H__
#define __TINY_RET_H__

#include "tiny_typedef.h"
#include "tiny_api.h"
#include <tiny_lor.h>

TINY_BEGIN_DECLS


typedef int32_t TinyRet;

#ifdef TINY_DEBUG
TINY_API
TINY_LOR
const char * tiny_ret_to_str(TinyRet ret);
#endif

#define RET_SUCCEEDED(r)                    (((TinyRet)(r)) >= 0)
#define RET_FAILED(r)                       (((TinyRet)(r)) < 0)

/* Severity Value */
#define SV_OK                               (0)
#define SV_ERR                              (1)

/* Error Level */
#define EL_NULL                             (0)
#define EL_GENERAL                          (1)
#define EL_SERIOUS                          (2)
#define EL_FATAL                            (3)

/* Code */
#define CODE_OK                             0
#define CODE_PENDING                        1
#define CODE_INTERNAL                       2
#define CODE_OUT_OF_MEMORY                  3
#define CODE_ARG_NULL                       4
#define CODE_ARG_INVALID                    5
#define CODE_NOT_IMPLEMENTED                6
#define CODE_NEW                            7
#define CODE_CONSTRUCT                      8
#define CODE_TIMEOUT                        9
#define CODE_NOT_FOUND                      10
#define CODE_STARTED                        11
#define CODE_STOPPED                        12
#define CODE_POSITION_INVALID               13
#define CODE_SELECT                         14
#define CODE_SOCKET_FD                      15
#define CODE_SOCKET_BIND                    16
#define CODE_SOCKET_SETSOCKOPT              17
#define CODE_SOCKET_LISTEN                  18
#define CODE_SOCKET_READ                    19
#define CODE_SOCKET_WRITE                   20
#define CODE_SOCKET_CONNECTING              21
#define CODE_SOCKET_CONNECTED               22
#define CODE_SOCKET_DISCONNECTED            23
#define CODE_SOCKET_ASCEPT                  24
#define CODE_UUID_INVALID                   25
#define CODE_HTTP_MSG_INVALID               26
#define CODE_HTTP_TYPE_INVALID              27
#define CODE_STATUS                         28
#define CODE_ITEM_EXIST                     29
#define CODE_URL_INVALID                    30
#define CODE_URL_GET_FAILED                 31
#define CODE_XML_INVALID                    32
#define CODE_INITIALIZED                    41
#define CODE_NOT_INITIALIZED                42
#define CODE_FULL                           43
#define CODE_EMPTY                          44

/* Return the error level */
#define ERR_LEVEL(r)                        (((uint32_t)(r) & 0x7FFFFFFF) >> 29)

/* Return the code */
#define TINY_RET_CODE(r)                    ((r) & 0x1FFFFFFF)

/* Create an TinyRet value from component pieces */
#define MAKE_RET(s, el, code)               (TinyRet)(((uint32_t)(s) << 31) | ((uint32_t)(el) << 29) | ((uint32_t)(code)))

/* return value */
#define TINY_RET_OK                           MAKE_RET(SV_OK, EL_NULL, CODE_OK)
#define TINY_RET_PENDING                      MAKE_RET(SV_OK, EL_NULL, CODE_PENDING)
#define TINY_RET_TIMEOUT                      MAKE_RET(SV_OK, EL_NULL, CODE_TIMEOUT)
#define TINY_RET_E_INITIALIZED                MAKE_RET(SV_ERR, EL_GENERAL, CODE_INITIALIZED)
#define TINY_RET_E_NOT_INITIALIZED            MAKE_RET(SV_ERR, EL_GENERAL, CODE_NOT_INITIALIZED)
#define TINY_RET_E_INTERNAL                   MAKE_RET(SV_ERR, EL_GENERAL, CODE_INTERNAL)
#define TINY_RET_E_OUT_OF_MEMORY              MAKE_RET(SV_ERR, EL_GENERAL, CODE_OUT_OF_MEMORY)
#define TINY_RET_E_ARG_NULL                   MAKE_RET(SV_ERR, EL_GENERAL, CODE_ARG_NULL)
#define TINY_RET_E_ARG_INVALID                MAKE_RET(SV_ERR, EL_GENERAL, CODE_ARG_INVALID)
#define TINY_RET_E_NOT_IMPLEMENTED            MAKE_RET(SV_ERR, EL_GENERAL, CODE_NOT_IMPLEMENTED)
#define TINY_RET_E_NEW                        MAKE_RET(SV_ERR, EL_GENERAL, CODE_NEW)
#define TINY_RET_E_CONSTRUCT                  MAKE_RET(SV_ERR, EL_GENERAL, CODE_CONSTRUCT)
#define TINY_RET_E_TIMEOUT                    MAKE_RET(SV_ERR, EL_GENERAL, CODE_TIMEOUT)
#define TINY_RET_E_NOT_FOUND                  MAKE_RET(SV_ERR, EL_GENERAL, CODE_NOT_FOUND)
#define TINY_RET_E_STARTED                    MAKE_RET(SV_ERR, EL_GENERAL, CODE_STARTED)
#define TINY_RET_E_STOPPED                    MAKE_RET(SV_ERR, EL_GENERAL, CODE_STOPPED)
#define TINY_RET_E_POSITION_INVALID           MAKE_RET(SV_ERR, EL_GENERAL, CODE_POSITION_INVALID)
#define TINY_RET_E_SELECT                     MAKE_RET(SV_ERR, EL_GENERAL, CODE_SELECT)
#define TINY_RET_E_SOCKET_FD                  MAKE_RET(SV_ERR, EL_GENERAL, CODE_SOCKET_FD)
#define TINY_RET_E_SOCKET_BIND                MAKE_RET(SV_ERR, EL_GENERAL, CODE_SOCKET_BIND)
#define TINY_RET_E_SOCKET_SETSOCKOPT          MAKE_RET(SV_ERR, EL_GENERAL, CODE_SOCKET_SETSOCKOPT)
#define TINY_RET_E_SOCKET_LISTEN              MAKE_RET(SV_ERR, EL_GENERAL, CODE_SOCKET_LISTEN)
#define TINY_RET_E_SOCKET_READ                MAKE_RET(SV_ERR, EL_GENERAL, CODE_SOCKET_READ)
#define TINY_RET_E_SOCKET_WRITE               MAKE_RET(SV_ERR, EL_GENERAL, CODE_SOCKET_WRITE)
#define TINY_RET_E_SOCKET_CONNECTING          MAKE_RET(SV_ERR, EL_GENERAL, CODE_SOCKET_CONNECTING)
#define TINY_RET_E_SOCKET_CONNECTED           MAKE_RET(SV_ERR, EL_GENERAL, CODE_SOCKET_CONNECTED)
#define TINY_RET_E_SOCKET_DISCONNECTED        MAKE_RET(SV_ERR, EL_GENERAL, CODE_SOCKET_DISCONNECTED)
#define TINY_RET_E_SOCKET_ASCEPT              MAKE_RET(SV_ERR, EL_GENERAL, CODE_SOCKET_ASCEPT)
#define TINY_RET_E_UUID_INVALID               MAKE_RET(SV_ERR, EL_GENERAL, CODE_UUID_INVALID)
#define TINY_RET_E_HTTP_MSG_INVALID           MAKE_RET(SV_ERR, EL_GENERAL, CODE_HTTP_MSG_INVALID)
#define TINY_RET_E_HTTP_TYPE_INVALID          MAKE_RET(SV_ERR, EL_GENERAL, CODE_HTTP_TYPE_INVALID)
#define TINY_RET_E_STATUS                     MAKE_RET(SV_ERR, EL_GENERAL, CODE_STATUS)
#define TINY_RET_E_ITEM_EXIST                 MAKE_RET(SV_ERR, EL_GENERAL, CODE_ITEM_EXIST)
#define TINY_RET_E_URL_INVALID                MAKE_RET(SV_ERR, EL_GENERAL, CODE_URL_INVALID)
#define TINY_RET_E_URL_GET_FAILED             MAKE_RET(SV_ERR, EL_GENERAL, CODE_URL_GET_FAILED)
#define TINY_RET_E_FULL                       MAKE_RET(SV_ERR, EL_GENERAL, CODE_FULL)


TINY_END_DECLS

#endif /* __TINY_RET_H__ */
