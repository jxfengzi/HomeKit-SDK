/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_socket_lwip.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_SOCKET_LWIP_H__
#define __TINY_SOCKET_LWIP_H__

#include <tiny_inline.h>
#include <tiny_typedef.h>

#if LWIP_TIMEVAL_PRIVATE
#else
    #include <sys/time.h>
#endif

#include <lwip/lwip/sockets.h>


TINY_BEGIN_DECLS


#define tiny_select                 lwip_select
#define tiny_socket_close           lwip_close
#define tiny_socket                 lwip_socket
#define tiny_setsockopt             lwip_setsockopt
#define tiny_bind                   lwip_bind
#define tiny_listen                 lwip_listen
#define tiny_accept                 lwip_accept
#define tiny_recv                   lwip_recv
#define tiny_send                   lwip_send
#define tiny_setsockopt             lwip_setsockopt

int tiny_socket_set_block(int fd, bool block);

#define inet_ntop(af,src,dst,size) \
    (((af) == AF_INET) ? ipaddr_ntoa_r((src),(dst),(size)) : NULL)

#define inet_pton(af,src,dst) \
    (((af) == AF_INET) ? inet_aton((src),(dst)) : 0)


TINY_END_DECLS

#endif /* __TINY_SOCKET_LWIP_H__ */