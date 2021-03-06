#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<windows.h>
#include<WinSock2.h>
#include<stdio.h>
//#pragma comment(lib, "ws2_32.lib")
int main()
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	// 1.创建一个socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 2.bind 绑定
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);//
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;//inet_addr("127.0.0.1");
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin)))
	{
		printf("error, 绑定失败... \n");
	}
	else
	{
		printf("ok, 绑定成功... \n");
	}

	// 3. listen
	if (SOCKET_ERROR == listen(_sock, 5))
	{
		printf("error, 监听失败... \n");
	}
	else
	{
		printf("ok,  监听成功... \n");
	}

	// 4. accept
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	
	_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
	if (INVALID_SOCKET == _cSock)
	{
		printf("error,  接收到无效客户端socket... \n");
	}
	printf("新的客户端连接：socket = %d, IP = %s \n", (int)_cSock, inet_ntoa(clientAddr.sin_addr));

	char _recvBuf[128] = {};
	while (true)
	{
		// 5.接收客户端请求的数据
		int nLen = recv(_cSock, _recvBuf, 128, 0);
		if (nLen <= 0)
		{
			printf("客户端已退出，任务结束。 \n");
			break;
		}
		printf("收到命令： %s \n", _recvBuf);
		//6.处理请求
		if (0 == strcmp(_recvBuf, "getName"))
		{
			char msgBuf[] = "xiao qiang";
			send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
		}
		else if (0 == strcmp(_recvBuf, "getAge"))
		{
			char msgBuf[] = "80";
			send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);

		}
		else
		{
			char msgBuf[] = "??? ...";
			send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);

		}
	
	}

	//6.close
	closesocket(_sock);
	WSACleanup();
	printf("已退出. \n");
	getchar();
	return 0;


}
