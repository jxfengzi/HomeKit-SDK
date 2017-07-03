/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_socket.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_SOCKET_H__
#define __TINY_SOCKET_H__


#ifdef LWIP_SOCKET
    #include "tiny_socket_lwip.h"
#else
    #ifdef WIN32
        #include "tiny_socket_windows.h"
    #else
        #include "tiny_socket_linux.h"
    #endif
#endif


#endif /* __TINY_SOCKET_H__ */
