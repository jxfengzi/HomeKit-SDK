/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   HttpServerCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __HTTP_MESSAGE_CODEC_H__
#define __HTTP_MESSAGE_CODEC_H__

#include <channel/ChannelHandler.h>

TINY_BEGIN_DECLS


#define HttpMessageCodec_Name    "HttpMessageCodec"

TINY_API
TINY_LOR
ChannelHandler * HttpMessageCodec(void);


TINY_END_DECLS

#endif /* __HTTP_MESSAGE_CODEC_H__ */
