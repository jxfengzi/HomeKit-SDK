/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HttpMessage.h
 *
 * @remark
 *		set tabstop=4
 *		set shiftwidth=4
 *		set expandtab
 */

#ifndef __HTTP_MESSAGE_H__
#define __HTTP_MESSAGE_H__

#include "tiny_base.h"
#include "common/Netty_api.h"
#include "HttpHeader.h"
#include "HttpContent.h"

TINY_BEGIN_DECLS


typedef enum _HttpStatusCode
{
    /* info */
    HTTP_STATUS_CONTINUE                            = 100,
    HTTP_STATUS_SWITCHING_PROTOCOLS                 = 101,

    /* success */
    HTTP_STATUS_OK                                  = 200,
    HTTP_STATUS_CREATED                             = 201,
    HTTP_STATUS_ASCEPT                              = 202,
    HTTP_STATUS_NON_AUTH                            = 203,
    HTTP_STATUS_NO_CONTENT                          = 204,
    HTTP_STATUS_RESET_CONTENT                       = 205,
    HTTP_STATUS_PARTIAL_CONTENT                     = 206,

    /* redirect */
    HTTP_STATUS_MULTIPLE_CHOICES                    = 300,
    HTTP_STATUS_MOVED_PERMANENTLY                   = 301,
    HTTP_STATUS_FOUND                               = 302,
    HTTP_STATUS_SEE_OTHER                           = 303,
    HTTP_STATUS_NOT_MODIFIED                        = 304,
    HTTP_STATUS_USE_PROXY                           = 305,
    HTTP_STATUS_UNUSED_306                          = 306,
    HTTP_STATUS_TEMPORARY_REDIRECT                  = 307,

    /* client error */
    HTTP_STATUS_BAD_REQUEST                         = 400,
    HTTP_STATUS_UNAUTH                              = 401,
    HTTP_STATUS_PAYMENT_REQUIRED                    = 402,
    HTTP_STATUS_FORBIDDEN                           = 403,
    HTTP_STATUS_NOT_FOUND                           = 404,
    HTTP_STATUS_METHOD_NOT_ALLOWED                  = 405,
    HTTP_STATUS_NOT_ASCEPTABLE                      = 406,
    HTTP_STATUS_PROXY_AUTH_REQUIRED                 = 407,
    HTTP_STATUS_REQUEST_TIMEOUT                     = 408,
    HTTP_STATUS_CONFLICT                            = 409,
    HTTP_STATUS_GONE                                = 410,
    HTTP_STATUS_LENGTH_REQUIRED                     = 411,
    HTTP_STATUS_PRECODITION_FAILED                  = 412,
    HTTP_STATUS_REQUEST_ENTITY_TOO_LARGE            = 413,
    HTTP_STATUS_REQUEST_URI_TOOL_LONG               = 414,
    HTTP_STATUS_UNSUPPORTED_MEDIA_TYPE              = 415,
    HTTP_STATUS_REQUESTED_RANGE_NOT_SATISFIABLE     = 416,
    HTTP_STATUS_EXPECTATION_FAILED                  = 417,

    /* server error */
    HTTP_STATUS_INTERNAL_SERVER_ERROR               = 500,
    HTTP_STATUS_NOT_IMPLEMENTED                     = 501,
    HTTP_STATUS_BAD_GATEWAY                         = 502,
    HTTP_STATUS_SERVICE_UNAVAILABLE                 = 503,
    HTTP_STATUS_GATEWAY_TIMEOUT                     = 504,
    HTTP_STATUS_VERSION_NOT_SUPPORTED               = 505,
} HttpStatusCode;

typedef enum _HttpType
{
    HTTP_UNDEFINED  = 0,
    HTTP_REQUEST    = 1,
    HTTP_RESPONSE   = 2,
} HttpType;

#define PROTOCOL_HTTP                   "HTTP"
#define PROTOCOL_RTSP                   "RTSP"
#define HTTP_METHOD_LEN                 32
#define HTTP_URI_LEN                    1024
#define HTTP_STATUS_LEN                 256

typedef struct _HttpRequestLine
{
    char method[HTTP_METHOD_LEN];
    char uri[HTTP_URI_LEN];
} HttpRequestLine;

typedef struct _HttpStatusLine
{
    int code;
    char status[HTTP_STATUS_LEN];
} HttpStatusLine;

typedef struct _HttpVersion
{
    int major;
    int minor;
} HttpVersion;

#define PROTOCOL_LEN         8

typedef enum _HttpParserStatus
{
    HttpParserDone              = 0,
    HttpParserError             = 1,
    HttpParserIncomplete        = 2,
    HttpParserHeaderIncomplete  = 3
} HttpParserStatus;

typedef struct _HttpMessage
{
//    uint32_t            ref;

    HttpType            type;
    char                ip[TINY_IP_LEN];
    uint16_t            port;
    char                protocol_identifier[PROTOCOL_LEN];

    HttpRequestLine     request_line;
    HttpStatusLine      status_line;
    HttpVersion         version;

    HttpParserStatus    parser_status;
    uint32_t            consume_length;
    uint32_t            content_length;
    uint32_t            content_length_loaded;

    HttpHeader          header;
    HttpContent         content;

    char              * _bytes;
    uint32_t            _size;
} HttpMessage;

NETTY_API
TINY_LOR
HttpMessage * HttpMessage_New(void);

NETTY_API
TINY_LOR
TinyRet HttpMessage_Construct(HttpMessage *thiz);

NETTY_API
TINY_LOR
TinyRet HttpMessage_Dispose(HttpMessage *thiz);

NETTY_API
TINY_LOR
void HttpMessage_Delete(HttpMessage *thiz);

//NETTY_API
//TINY_LOR
//void HttpMessage_SetProtocolIdentifier(HttpMessage * thiz, const char *identifier);
//
//NETTY_API
//TINY_LOR
//void HttpMessage_SetIp(HttpMessage *thiz, const char *ip);
//
//NETTY_API
//TINY_LOR
//const char * HttpMessage_GetIp(HttpMessage *thiz);
//
//NETTY_API
//TINY_LOR
//void HttpMessage_SetPort(HttpMessage *thiz, uint16_t port);
//
//NETTY_API
//TINY_LOR
//uint16_t HttpMessage_GetPort(HttpMessage *thiz);

/* Parse bytes & to bytes */
NETTY_API
TINY_LOR
TinyRet HttpMessage_Parse(HttpMessage * thiz, const char *bytes, uint32_t len);

//NETTY_API TinyRet HttpMessage_ToBytes(HttpMessage *thiz, char **bytes, uint32_t *len);
//NETTY_API uint32_t HttpMessage_ToString(HttpMessage *thiz, char *string, uint32_t len);

//NETTY_API
//TINY_LOR
//void HttpMessage_SetType(HttpMessage * thiz, HttpType type);
//
//NETTY_API
//TINY_LOR
//HttpType HttpMessage_GetType(HttpMessage * thiz);

NETTY_API
TINY_LOR
const char * HttpMessage_GetBytesWithoutContent(HttpMessage *thiz);

NETTY_API
TINY_LOR
uint32_t HttpMessage_GetBytesSizeWithoutContent(HttpMessage *thiz);

/* for request */
NETTY_API
TINY_LOR
void HttpMessage_SetMethod(HttpMessage *thiz, const char * method);

NETTY_API
TINY_LOR
void HttpMessage_SetUri(HttpMessage *thiz, const char * uri);

//NETTY_API
//TINY_LOR
//const char * HttpMessage_GetMethod(HttpMessage *thiz);
//
//NETTY_API
//TINY_LOR
//const char * HttpMessage_GetUri(HttpMessage *thiz);

/* for response */
NETTY_API
TINY_LOR
void HttpMessage_SetResponse(HttpMessage *thiz, int code, const char *status);

//NETTY_API
//TINY_LOR
//const char * HttpMessage_GetStatus(HttpMessage *thiz);
//
//NETTY_API
//TINY_LOR
//int HttpMessage_GetStatusCode(HttpMessage *thiz);

/* for version */
NETTY_API
TINY_LOR
void HttpMessage_SetVersion(HttpMessage *thiz, int major, int minor);

//NETTY_API
//TINY_LOR
//int HttpMessage_GetMajorVersion(HttpMessage *thiz);
//
//NETTY_API
//TINY_LOR
//int HttpMessage_GetMinorVersion(HttpMessage *thiz);
//
///* for method */
//NETTY_API
//TINY_LOR
//bool HttpMessage_IsMethodEqual(HttpMessage *thiz, const char *method);

/* for header */
//NETTY_API
//TINY_LOR
//void HttpMessage_SetHeader(HttpMessage *thiz, const char *name, const char *value);

//NETTY_API
//TINY_LOR
//void HttpMessage_SetHeaderInteger(HttpMessage *thiz, const char *name, uint32_t value);

//NETTY_API
//TINY_LOR
//const char * HttpMessage_GetHeaderValue(HttpMessage *thiz, const char *name);
//
//NETTY_API
//TINY_LOR
//uint32_t HttpMessage_GetHeaderCount(HttpMessage * thiz);
//
//NETTY_API
//TINY_LOR
//const char * HttpMessage_GetHeaderNameAt(HttpMessage * thiz, uint32_t index);
//
//NETTY_API
//TINY_LOR
//const char * HttpMessage_GetHeaderValueAt(HttpMessage * thiz, uint32_t index);

/* for content */
NETTY_API
TINY_LOR
bool HttpMessage_IsContentFull(HttpMessage *thiz);

//NETTY_API
//TINY_LOR
//const char * HttpMessage_GetContentObject(HttpMessage *thiz);

//NETTY_API
//TINY_LOR
//uint32_t HttpMessage_GetContentSize(HttpMessage *thiz);

//NETTY_API
//TINY_LOR
//TinyRet HttpMessage_SetContentSize(HttpMessage *thiz, uint32_t size);

//NETTY_API
//TINY_LOR
//TinyRet HttpMessage_AddContentObject(HttpMessage *thiz, const char *bytes, uint32_t size);

/* set request */
NETTY_API
TINY_LOR
TinyRet HttpMessage_SetRequest(HttpMessage *thiz, const char * method, const char *url);


TINY_END_DECLS

#endif /* __HTTP_MESSAGE_H__ */
