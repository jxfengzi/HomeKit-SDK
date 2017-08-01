/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_socket_linux.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_SOCKET_LINUX_H__
#define __TINY_SOCKET_LINUX_H__

#include <tiny_typedef.h>
#include <tiny_inline.h>

/* According to POSIX.1-2001, POSIX.1-2008 */
#include <sys/select.h>

/* According to earlier standards */
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

TINY_BEGIN_DECLS


#define tiny_socket_initialize()
#define tiny_socket_finalize()
#define tiny_select                 select
#define tiny_socket_close           close
#define tiny_socket                 socket
#define tiny_setsockopt             setsockopt
#define tiny_bind                   bind
#define tiny_listen                 listen
#define tiny_accept                 accept
#define tiny_recv                   recv
#define tiny_send                   send
#define tiny_setsockopt             setsockopt
#define tiny_recvfrom               recvfrom
#define tiny_sendto                 sendto
#define tiny_connect                connect

int tiny_socket_set_block(int fd, bool block);


TINY_END_DECLS

#endif /* __TINY_SOCKET_LINUX_H__ */