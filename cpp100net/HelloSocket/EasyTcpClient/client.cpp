#define WIN32_LEAN_AND_MEAN

#include<windows.h>
#include<WinSock2.h>
#include<stdio.h>
//#pragma comment(lib, "ws2_32.lib")
int main()
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	// 1.建立socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock)
	{
		printf("error, 建立socket失败... \n");
	}
	else
	{
		printf("ok, 建立socket成功... \n");
	}

	//2.connect
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int ret = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (INVALID_SOCKET == ret)
	{
		printf("error, 连接失败... \n");
	}
	else
	{
		printf("ok, 连接成功... \n");
	}

	
	while (true)
	{
		char cmdBuf[128] = {};
		scanf("%s", cmdBuf);
		if (0 == strcmp(cmdBuf, "exit"))
		{
			printf("接收到退出命令，任务结束。 \n");
			break;
		}
		else
		{
			send(_sock, cmdBuf, strlen(cmdBuf) + 1, 0);
		}

		//3.接收服务信息 recv
		char recvBuf[256] = {};
		int nLen = recv(_sock, recvBuf, 256, 0);
		if (nLen > 0)
		{
			printf("接收到的数据: %s \n", recvBuf);
		}

	}


	//4.关闭套接字
	closesocket(_sock);
	WSACleanup();
	printf("客户端任务结束。 \n");
	getchar();
	return 0;


}
