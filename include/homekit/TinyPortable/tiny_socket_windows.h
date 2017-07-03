/**
 * Copyright (C) 2013-2015
 *
 * @author jxfengzi@gmail.com
 * @date   2013-7-9
 *
 * @file   tiny_socket_windows.h
 *
 * @remark
 *      set tabstop=4
 *      set shiftwidth=4
 *      set expandtab
 */

#ifndef __TINY_SOCKET_WINDOWS_H__
#define __TINY_SOCKET_WINDOWS_H__

#include <tiny_typedef.h>
#include <tiny_inline.h>
#include <WinSock2.h>

TINY_BEGIN_DECLS


#define tiny_select                 select
#define tiny_socket_close           closesocket
#define tiny_socket                 socket
#define tiny_setsockopt             setsockopt
#define tiny_accept                 accept

TINY_INLINE
int tiny_socket_set_block(int fd, bool block)
{
    unsigned long ul = block ? 0 : 1;
    return ioctlsocket(fd, FIONBIO, &ul);
}

TINY_INLINE
int tiny_bind(int fd, const struct sockaddr *addr, socklen_t len)
{
    return (bind(fd, addr, len) == SOCKET_ERROR) ? -1 : 0;
}

TINY_INLINE
int tiny_listen(int fd, int backlog)
{
    return (listen(fd, backlog) == SOCKET_ERROR) ? -1 : 0;
}

TINY_INLINE
int tiny_recv(int fd, void *mem, size_t len, int flags)
{
//    if (n == SOCKET_ERROR)
//    {
//        DWORD e = GetLastError();
//            LOGI("GetLastError: %d", e);
//
//            if (e == WSAEWOULDBLOCK)
//            {
//                break;
//                air_usleep(100);
//                continue;
//            }
//            else
//            {
//                break;
//            }
//    }

    return (int) recv(fd, (char *)mem, len, flags);
}

TINY_INLINE
int tiny_send(int fd, const void *data, size_t size, int flags)
{
    return send(fd, data, size, 0);
}

TINY_END_DECLS

#endif /* __TINY_SOCKET_WINDOWS_H__ */