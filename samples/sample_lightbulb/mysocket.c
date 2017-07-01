/**
 * Copyright (C) 2013-2015
 *
 * @author ouyangchengfeng@xiaomi.com
 * @date   2013-11-19
 *
 * @file   tiny_socket.c
 *
 * @remark
 *
 */

#include "mysocket.h"

TinyRet my_socket_init(void)
{
    TinyRet ret = TINY_RET_OK;
    static bool is_init = false;

    do
    {
#ifdef _WIN32
        WORD wVersionRequested;
		WSADATA wsaData;
#endif

#ifdef _WIN32
        wVersionRequested = MAKEWORD(2, 0);
		if (WSAStartup(wVersionRequested, &wsaData) != 0)
		{
			LOG_W(TAG, "WSAStartup failed");
			ret = TINY_RET_E_INTERNAL;
			break;
		}
#else
        // Ignore SIGPIPE signal, so if browser cancels the request, it won't kill the whole process.
        //(void)signal(SIGPIPE, SIG_IGN);
#endif

        ret = TINY_RET_OK;
    } while (0);

    return ret;
}