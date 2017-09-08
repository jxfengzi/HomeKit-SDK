/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   DnsMessageCodec.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __DNS_MESSAGE_CODEC_H__
#define __DNS_MESSAGE_CODEC_H__

#include <channel/ChannelHandler.h>
#include "mdns_api.h"

TINY_BEGIN_DECLS


#define DnsMessageCodec_Name    "DnsMessageCodec"

MDNS_API
TINY_LOR
ChannelHandler * DnsMessageCodec(void);


TINY_END_DECLS

#endif /* __DNS_MESSAGE_CODEC_H__ */