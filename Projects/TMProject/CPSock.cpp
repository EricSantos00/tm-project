#include "pch.h"
#include "CPSock.h"
#include <WinSock2.h>

CPSock::CPSock()
{
	Sock = NULL;
	Init = 0;
	pSendBuffer = (char*)malloc(SEND_BUFFER_SIZE);
	pRecvBuffer = (char*)malloc(RECV_BUFFER_SIZE);

	memset(pSendBuffer, 0, SEND_BUFFER_SIZE);
	memset(pRecvBuffer, 0, RECV_BUFFER_SIZE);

	nSendPosition = 0;
	nSentPosition = 0;
	nRecvPosition = 0;
	nProcPosition = 0;
	memset(SendQueue, 0, MAX_KEYWORD_QUEUE);
	memset(RecvQueue, 0, MAX_KEYWORD_QUEUE);
	SendCount = 0;
	RecvCount = 0;
	ErrCount = 0;
}

CPSock::~CPSock()
{
	if (pSendBuffer)
	{
		free(pSendBuffer);
		pSendBuffer = NULL;
	}
	if (pRecvBuffer)
	{
		free(pRecvBuffer);
		pRecvBuffer = NULL;
	}
}

bool CPSock::WSAInitialize()
{
	WSAData WSAData;

	return WSAStartup(MAKEWORD(1, 1), &WSAData) == 0;
}

unsigned int CPSock::StartListen(HWND hWnd, int ip, int port, int WSA)
{
	sockaddr_in local_sin;
	memset((char*)&local_sin, 0, sizeof(local_sin));

	char Temp[256];
	memset(Temp, 0, sizeof(Temp));

	unsigned int tSock = socket(2, 1, 0);
	
	if (tSock == -1)
	{
		MessageBoxA(hWnd, "Initialize socket fail", "ERROR", 0);
		return 0;
	}

	gethostname(Temp, 256);
	local_sin.sin_family = AF_INET;
	local_sin.sin_addr.S_un.S_addr = ip;
	local_sin.sin_port = htons(port);

	if (bind(tSock, (const struct sockaddr*) & local_sin, 16) == -1)
	{
		MessageBoxA(hWnd, "Binding fail", "ERROR", 0);
		closesocket(tSock);
		return 0;
	}
	else if (listen(tSock, 8) >= 0)
	{
		if (WSAAsyncSelect(tSock, hWnd, WSA, 8) <= 0)
		{
			Sock = tSock;
			return tSock;
		}
		else
		{
			MessageBoxA(hWnd, "WSAAsyncSelect fail", "ERROR", 0);
			closesocket(tSock);
			return 0;
		}
	}
	else
	{
		MessageBoxA(hWnd, "Listen fail", "ERROR", 0);
		closesocket(tSock);
		return 0;
	}
}

unsigned int CPSock::ConnectServer(char* HostAddr, int Port, int ip, int WSA)
{
	sockaddr_in InAddr;
	memset((char*)& InAddr, 0, sizeof(InAddr));
	sockaddr_in local_sin;
	memset((char*)& local_sin, 0, sizeof(local_sin));
}

unsigned int CPSock::SingleConnect(char* HostAddr, int Port, int ip, int WSA)
{
	return 0;
}

int CPSock::Receive()
{
	return 0;
}

char* CPSock::ReadMessage(int* ErrorCode, int* ErrorType)
{
	return nullptr;
}
