#include <bootstrap/Bootstrap.h>
#include <channel/SocketChannel.h>
#include <channel/ChannelIdleStateHandler.h>
#include <channel/stream/StreamServerChannel.h>
#include <channel/stream/StreamServerChannelContext.h>
#include <codec-http/HttpMessageCodec.h>
#include "ExampleHandler.h"


static TinyRet my_socket_init(void)
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
			printf("WSAStartup failed\n");
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

static void HttpServerInitializer(Channel *channel, void *ctx)
{
    printf("HttpServerInitializer: %s\n", channel->id);
    SocketChannel_AddLast(channel, ChannelIdleStateHandler(0, 0, 3));
    SocketChannel_AddLast(channel, ExampleHandler());
    SocketChannel_AddBefore(channel, ExampleHandler_Name, HttpMessageCodec());
}

static TinyRet init_http_server(Channel *server, uint16_t port)
{
    TinyRet ret = TINY_RET_OK;

    StreamServerChannel_Initialize(server, HttpServerInitializer, NULL);

    do
    {
        ret = SocketChannel_Open(server, TYPE_TCP_SERVER);
        if (RET_FAILED(ret))
        {
            printf("SocketChannel_Open failed: %d\n", TINY_RET_CODE(ret));
            break;
        }

        ret = SocketChannel_Bind(server, port, false);
        if (RET_FAILED(ret))
        {
            printf("SocketChannel_Bind failed: %d\n", TINY_RET_CODE(ret));
            break;
        }

        ret = SocketChannel_SetBlock(server, false);
        if (RET_FAILED(ret))
        {
            printf("SocketChannel_SetBlock failed: %d\n", TINY_RET_CODE(ret));
            break;
        }

        ret = SocketChannel_Listen(server, ((StreamServerChannelContext *)server->ctx)->maxConnections);
        if (RET_FAILED(ret))
        {
            printf("SocketChannel_Listen failed: %d\n", TINY_RET_CODE(ret));
            break;
        }
    } while (0);

    return ret;
}

int main()
{
    TinyRet ret = TINY_RET_OK;
    Channel *server1 = NULL;
    Channel *server2 = NULL;
    Bootstrap sb;

    my_socket_init();

    // new TCP Server
    server1 = StreamServerChannel_New(6);
    ret = init_http_server(server1, 9090);
    if (RET_FAILED(ret))
    {
        printf("init_http_server failed: %d\n", TINY_RET_CODE(ret));
        return 0;
    }
    printf("Bind Port: %d\n", server1->local.socket.port);

    // new TCP Server
    server2 = StreamServerChannel_New(2);
    ret = init_http_server(server1, 9090);
    if (RET_FAILED(ret))
    {
        printf("init_http_server failed: %d\n", TINY_RET_CODE(ret));
        return 0;
    }
    printf("Bind Port: %d\n", server1->local.socket.port);

    // Starting Bootstrap
    Bootstrap_Construct(&sb);
    Bootstrap_AddChannel(&sb, server1);
    Bootstrap_AddChannel(&sb, server2);
    Bootstrap_Sync(&sb);
    Bootstrap_Shutdown(&sb);
    Bootstrap_Dispose(&sb);

    return 0;
}
