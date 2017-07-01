#include <channel/stream/StreamServerChannel.h>
#include <channel/SocketChannel.h>
#include <channel/ChannelIdleStateHandler.h>
#include <channel/multicast/MulticastChannel.h>
#include <bootstrap/Bootstrap.h>
#include <codec-http/HttpMessageCodec.h>
#include "ExampleSsdpHandler.h"


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

static void SsdpInitializer(Channel *channel, void *ctx)
{
    printf("SsdpInitializer: %s\n", channel->id);
//    SocketChannel_AddLast(channel, ChannelIdleStateHandler(0, 0, 3));
    SocketChannel_AddLast(channel, ExampleSsdpHandler());
    SocketChannel_AddBefore(channel, ExampleSsdpHandler_Name, HttpMessageCodec());
}

static void timeout(Timer *timer, void *ctx)
{
    Channel *ssdp = (Channel *)ctx;
    const char *data = "hello, world";
    size_t len = strlen(data);
    printf("timeout\n");

    MulticastChannel_Write(ssdp, data, (uint32_t)len);
}

int main()
{
    Channel *ssdp = NULL;
    Timer *timer = NULL;
    Bootstrap sb;

    my_socket_init();

    // SSDP
    ssdp = MulticastChannel_New();
    if (RET_FAILED(MulticastChannel_Initialize(ssdp, SsdpInitializer, NULL)))
    {
        printf("MulticastChannel_Initialize failed\n");
        return 0;
    }

    if (RET_FAILED(MulticastChannel_Join(ssdp, "10.0.1.9", "239.255.255.250", 1900)))
    {
        printf("MulticastChannel_Join failed\n");
        return 0;
    }

    // new Timer
    timer = Timer_New("mytimer", 3 * 1000000, ssdp, timeout);

    // Bootstrap
    if (RET_FAILED(Bootstrap_Construct(&sb)))
    {
        printf("Bootstrap_Construct failed\n");
        return 0;
    }

    if (RET_FAILED(Bootstrap_AddChannel(&sb, ssdp)))
    {
        printf("Bootstrap_AddChannel failed\n");
        return 0;
    }

    Bootstrap_AddTimer(&sb, timer);

    if (RET_FAILED(Bootstrap_Sync(&sb)))
    {
        printf("Bootstrap_Sync failed\n");
        return 0;
    }

    if (RET_FAILED(Bootstrap_Shutdown(&sb)))
    {
        printf("Bootstrap_Shutdown failed\n");
        return 0;
    }

    Bootstrap_Dispose(&sb);

    return 0;
}
