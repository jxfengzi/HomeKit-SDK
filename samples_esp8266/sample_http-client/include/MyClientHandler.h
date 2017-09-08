/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-11-19
 *
 * @file   MyClientHandler.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __MY_CLIENT_HANDLER_H__
#define __MY_CLIENT_HANDLER_H__

#include <channel/ChannelHandler.h>

TINY_BEGIN_DECLS


#define MyClientHandler_Name "MyClientHandler"

ChannelHandler * MyClientHandler(void);


TINY_END_DECLS

#endif /* __MY_CLIENT_HANDLER_H__ */