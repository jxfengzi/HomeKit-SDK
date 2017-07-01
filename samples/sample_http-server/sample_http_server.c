#include <channel/stream/StreamServerChannel.h>
#include <channel/SocketChannel.h>
#include <channel/ChannelIdleStateHandler.h>
#include <bootstrap/Bootstrap.h>
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

int main()
{
    Channel *server1 = NULL;
    Channel *server2 = NULL;
    Bootstrap sb;

    my_socket_init();

    // new TCP Server
    server1 = StreamServerChannel_New(6);
    StreamServerChannel_Initialize(server1, HttpServerInitializer, NULL);
    StreamServerChannel_Bind(server1, 9091);

    // new TCP Server
    server2 = StreamServerChannel_New(2);
    StreamServerChannel_Initialize(server2, HttpServerInitializer, NULL);
    StreamServerChannel_Bind(server2, 9092);

    // Starting Bootstrap
    Bootstrap_Construct(&sb);
    Bootstrap_AddChannel(&sb, server1);
    Bootstrap_AddChannel(&sb, server2);
    Bootstrap_Sync(&sb);
    Bootstrap_Shutdown(&sb);
    Bootstrap_Dispose(&sb);

    return 0;
}
