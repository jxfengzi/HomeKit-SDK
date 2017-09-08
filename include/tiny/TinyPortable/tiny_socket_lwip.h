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
#include <tiny_lor.h>
#include <tiny_ret.h>

#if LWIP_TIMEVAL_PRIVATE
#else
    #include <sys/time.h>
#endif

#include <lwip/lwip/sockets.h>


TINY_BEGIN_DECLS


#define tiny_socket_initialize()
#define tiny_socket_finalize()
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
#define tiny_recvfrom               lwip_recvfrom
#define tiny_sendto                 lwip_sendto
#define tiny_connect                lwip_connect

TINY_LOR
int tiny_socket_set_block(int fd, bool block);

TINY_LOR
int tiny_socket_join_group(int fd, const char *ip, const char *group);

TINY_LOR
int tiny_socket_leave_group(int fd);

TINY_LOR
TinyRet tiny_async_connect(int fd, const char *ip, uint16_t port);

TINY_LOR
bool tiny_socket_has_error(int fd);

TINY_LOR
int tiny_socket_reuse_port(int fd);

TINY_LOR
int tiny_socket_reuse_address(int fd);

TINY_LOR
uint16_t tiny_socket_get_port(int fd);

#define inet_ntop(af,src,dst,size) \
    (((af) == AF_INET) ? ipaddr_ntoa_r(((struct ip_addr *)src),(dst),(size)) : NULL)

#define inet_pton(af,src,dst) \
    (((af) == AF_INET) ? inet_aton((src),(dst)) : 0)


TINY_END_DECLS

#endif /* __TINY_SOCKET_LWIP_H__ */