/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   ExampleSsdpHandler.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __EXAMPLE_SSDP_HANDLER_H__
#define __EXAMPLE_SSDP_HANDLER_H__

#include <channel/ChannelHandler.h>

TINY_BEGIN_DECLS


#define ExampleSsdpHandler_Name "ExampleSsdpHandler"

ChannelHandler * ExampleSsdpHandler(void);


TINY_END_DECLS

#endif /* __EXAMPLE_SSDP_HANDLER_H__ */