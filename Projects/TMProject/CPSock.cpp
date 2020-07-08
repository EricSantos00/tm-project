#include "pch.h"
#include "CPSock.h"
#include <WinSock2.h>
#include "Basedef.h"

int ConnectPort = 0;

unsigned char pKeyWord[256][2] = {
	235,125,  215,124,  135,105,  235,121,  235,121,  235,127,  135,125,  135,102,  205,125,  235,125,
	115,115,   35, 55,  215,145,  205,121,  225,125,  235,115,   35,125,  225,123,  135,145,  135,229,
	125,215,  115, 47,  135,105,   35,124,  205,123,  235,121,   35,125,  115,125,   32,212,  235,120,
	131,225,  235,144,   35,195,   15,135,  145,121,   35,121,  135,120,  135,132,   27,125,  235,128,
	130,110,  145,124,  135,187,  235,121,  255,  5,  235,105,  105,111,  235,121,  235, 25,    5, 47,
	194, 95,   25, 65,  235,145,  113,123,  167, 75,  230,125,  164,125,  135, 25,   33,194,  135, 22,
	235,112,  235,125,   35,125,  235,125,  235, 23,   35,128,  205,120,  235,125,  135,125,  235,123,
	139,195,  235,122,  135,125,  112,131,  209,221,  235,120,  246,126,  135,125,  136, 25,  135,245,
	135,125,  215,225,  155,135,  235,155,  205,123,   35,108,  131,127,  235, 20,  235,125,   31,115,
	235,125,  233, 15,   35, 22,  235, 25,  215,155,  141,155,  163,125,  202,115,  131,122,  135,125,

	231,125,  235,125,  231,125,  235,125,  235,125,  215,103,  235,125,  135,125,  235,125,  235,125,
	132,125,  235,125,  135,125,  231,125,  135,121,  235,152,  245,102,  235,128,  135, 26,  135,225,
	232,111,  209,121,  131,155,  225,133,  141,123,   15,121,  225,121,  235,107,  135,125,  235,124,
	 45,125,  215,221,  233,115,  235,134,   15,121,  232,121,   05,125,  215,205,  235,225,  135,221,
	215,143,    5,125,  235,122,  231,115,  235,155,  111,135,  233,124,  205, 15,  235,128,  235,121,
	132,135,   55,215,  234,121,  141,145,   11,115,   75, 25,  235,105,  145, 35,  135,129,  235,224,
	 35,225,   75,131,  163,161,  245,121,   33,125,  230,105,   35,126,  174,124,   15,225,  135,106,
	231,121,  155,125,    2,145,  235,123,  134,113,  221, 45,  135,111,  231,121,  215,124,   35, 28,
	 35,125,  235,127,  175,121,   55,104,  195,121,  205,125,  235,122,   33,125,  235, 25,  235,149,
	135,125,  225,120,  205,125,  135,125,  215,125,   35,125,  135,124,  221,145,  235,122,  235,175,

	135, 35,  235, 16,  205,223,  135,134,  135,165,  135,124,  115,126,  237,125,  215,125,  235,125,
	 15,125,  215,125,  225,122,  104,121,  214,126,  235,152,  235,121,  245,125,  225,122,  235, 35,
	 55,111,   35,124,  135,123,  215,122,  125,128,  231,103,  235,122,   35,125,  135,106,  235,165,
	 35,125,  235,127,  175,121,   55,124,  195,121,  205,125,  235,122,   33,125,  235, 25,  235,149,
	 35,125,   35,121,  213,125,  115,125,  225,122,  135,121,  235,125,  235,125,  205,122,  235, 55,
	235,115,  215,135,  231,227,  235,108,  124,145,  235,125
};

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

	SOCKET tSock = socket(2, 1, 0);
	
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

	return 1;
}

unsigned int CPSock::ConnectServer(char* HostAddr, int Port, int ip, int WSA)
{
	sockaddr_in InAddr;
	memset((char*)& InAddr, 0, sizeof(InAddr));
	sockaddr_in local_sin;
	memset((char*)& local_sin, 0, sizeof(local_sin));

	nSendPosition = 0;
	nSentPosition = 0;
	nRecvPosition = 0;
	nProcPosition = 0;

	if (Sock)
		CloseSocket();

	InAddr.sin_addr.S_un.S_addr = inet_addr(HostAddr);
	InAddr.sin_family = AF_INET;
	InAddr.sin_port = htons(Port);
	SOCKET tSock = socket(2, 1, 0);

	if (tSock == -1)
	{
		MessageBoxA(0, "Initialize socket fai", "ERROR", 0);
		return 0;
	}

	local_sin.sin_family = AF_INET;
	local_sin.sin_addr.S_un.S_addr = ip;
	local_sin.sin_port = 0;

	if (bind(tSock, (const struct sockaddr*)&local_sin, 16) != -1
		|| (ConnectPort += 10,
			local_sin.sin_port = htons(ConnectPort + 5000),
			bind(tSock, (const struct sockaddr*)&local_sin, 16) != -1)
		|| (ConnectPort += 10,
			local_sin.sin_port = htons(ConnectPort + 5000),
			bind(tSock, (const struct sockaddr*)&local_sin, 16) != -1))
	{
		if (tSock == -1)
		{
			return 0;
		}
		else if (connect(tSock, (const struct sockaddr*)&InAddr, 16) >= 0)
		{
			if (WSAAsyncSelect(tSock, hWndMain, WSA, 33) <= 0)
			{
				Sock = tSock;
				unsigned int InitCode = INIT_CODE;
				send(tSock, (const char*)&InitCode, 4, 0);
				Init = 1;
				return tSock;
			}
			else
			{
				closesocket(tSock);
				Sock = 0;
				return 0;
			}
		}
		else
		{
			WSAGetLastError();
			closesocket(tSock);
			Sock = 0;
			return 0;
		}
	}
	else
	{
		MessageBoxA(0, "Binding fail", "ERROR", 0);
		closesocket(tSock);
		return 0;
	}

	return 1;
}

unsigned int CPSock::SingleConnect(char* HostAddr, int Port, int ip, int WSA)
{
	sockaddr_in InAddr;
	memset((char*)&InAddr, 0, sizeof(InAddr));
	sockaddr_in local_sin;
	memset((char*)&local_sin, 0, sizeof(local_sin));

	if (Sock)
	{
		closesocket(Sock);
		Sock = NULL;
	}

	InAddr.sin_addr.S_un.S_addr = inet_addr(HostAddr);
	InAddr.sin_family = AF_INET;
	InAddr.sin_port = htons(Port);
	SOCKET tSock = socket(2, 1, 0);

	if (tSock == -1)
	{
		MessageBoxA(0, "Initialize single socket fai", "ERROR", 0);
		return 0;
	}

	local_sin.sin_family = AF_INET;
	local_sin.sin_addr.S_un.S_addr = ip;
	local_sin.sin_port = 0;

	if (bind(tSock, (const struct sockaddr*)&local_sin, 16) != -1
		|| (ConnectPort += 10,
			local_sin.sin_port = htons(ConnectPort + 5000),
			bind(tSock, (const struct sockaddr*)&local_sin, 16) != -1)
		|| (ConnectPort += 10,
			local_sin.sin_port = htons(ConnectPort + 5000),
			bind(tSock, (const struct sockaddr*)&local_sin, 16) != -1))
	{
		if (tSock == -1)
		{
			return 0;
		}
		else if (connect(tSock, (const struct sockaddr*)&InAddr, 16) >= 0)
		{
			if (WSAAsyncSelect(tSock, hWndMain, WSA, 33) <= 0)
			{
				Sock = tSock;
				unsigned int InitCode = INIT_CODE;
				send(tSock, (const char*)& InitCode, 4, 0);
				Init = 1;
				return tSock;
			}
			else
			{
				closesocket(tSock);
				Sock = 0;
				return 0;
			}
		}
		else
		{
			WSAGetLastError();
			closesocket(tSock);
			Sock = 0;
			return 0;
		}
	}
	else
	{
		MessageBoxA(0, "single Binding fail", "ERROR", 0);
		closesocket(tSock);
		return 0;
	}

	return 1;
}

int CPSock::Receive()
{
	int Rest = RECV_BUFFER_SIZE - nRecvPosition;
	int tReceiveSize = recv(Sock, &pRecvBuffer[nRecvPosition], Rest, 0);
	if (tReceiveSize == -1)
		return 0;
	if (tReceiveSize == Rest)
		return -1;

	nRecvPosition += tReceiveSize;
	return 1;
}

char* CPSock::ReadMessage(int* ErrorCode, int* ErrorType)
{
	*ErrorCode = 0;
	if (nProcPosition >= nRecvPosition)
	{
		nRecvPosition = 0;
		nProcPosition = 0;
		return 0;
	}

	if (!Init)
	{
		if (nRecvPosition - nProcPosition < 4)
			return 0;

		unsigned int InitCode = *(unsigned int*)&pRecvBuffer[nProcPosition];
		if (InitCode != INIT_CODE)
		{
			*ErrorCode = 2;
			*ErrorType = InitCode;
			return 0;
		}

		Init = 1;
		nProcPosition += 4;
	}

	if ((unsigned int)(nRecvPosition - nProcPosition) < sizeof(MSG_STANDARD))
		return 0;

	unsigned short Size = *(unsigned short*)&pRecvBuffer[nProcPosition];
	unsigned char iKeyWord = pRecvBuffer[nProcPosition + 2];
	unsigned char KeyWord = pKeyWord[iKeyWord][0];
	unsigned char CheckSum = pRecvBuffer[nProcPosition + 3];
	unsigned int SockType = *(unsigned short*)&pRecvBuffer[nProcPosition + 4];
	unsigned int SockID = *(unsigned short*)&pRecvBuffer[nProcPosition + 6];

	if (RecvQueue[0] != 0)
	{
		char qKeyword;
		if (RecvCount <= 15)
		{
			qKeyword = RecvQueue[RecvCount++];
		}
		else if (EncodeByte != 0)
		{
			char tb = EncodeByte[0];
			if (!tb)
				tb = EncodeByte[3];
			if (!tb)
				tb = 13;
			char Keyword = EncodeByte[2] + EncodeByte[3] - (EncodeByte[1] * tb);
			if (EncodeByte[2] + EncodeByte[3] == tb * EncodeByte[1])
				Keyword = EncodeByte[0];
			qKeyword = Keyword;
		}
		else
		{
			qKeyword = RecvQueue[15] % 2 ? RecvQueue[11] + RecvQueue[13] - this->RecvQueue[9] + 4 
				: RecvQueue[3] + RecvQueue[1] + RecvQueue[5] - 87;
		}

		if (~qKeyword != iKeyWord)
		{
			*ErrorCode = 3;
			*ErrorType = Size;
			return 0;
		}
	}

	if (Size >= RECV_BUFFER_SIZE || Size < sizeof(MSG_STANDARD))
	{
		nRecvPosition = 0;
		nProcPosition = 0;
		*ErrorCode = 2;
		*ErrorType = Size;
		return 0;
	}

	if (Size > nRecvPosition - nProcPosition)
	{
		return 0;
	}

	char* pMsg = &pRecvBuffer[nProcPosition];
	nProcPosition += Size;
	if (nRecvPosition <= nProcPosition)
	{
		nRecvPosition = 0;
		nProcPosition = 0;
	}

	char Sum1 = 0;
	char Sum2 = 0;
	int pos = KeyWord;
	for (int i = sizeof(int); i < Size; i++, pos++)
	{
		Sum2 += pMsg[i];

		int rst = pos % 256;
		unsigned char Trans = pKeyWord[rst][1];

		int mod = i & 0x3;

		if (mod == 0) 
			pMsg[i] = pMsg[i] - (Trans << 2);
		if (mod == 1) 
			pMsg[i] = pMsg[i] + (Trans >> 1);
		if (mod == 2) 
			pMsg[i] = pMsg[i] - (Trans << 1);
		if (mod == 3) 
			pMsg[i] = pMsg[i] + (Trans >> 2);

		Sum1 += pMsg[i];
	}

	if (Sum2 - Sum1 != CheckSum)
	{
		*ErrorCode = 1;
		*ErrorType = Size;
	}

	return pMsg;
}

int CPSock::CloseSocket()
{
	nSendPosition = 0;
	nSentPosition = 0;
	nRecvPosition = 0;
	nProcPosition = 0;
	Init = 0;
	if (Sock)
		closesocket(Sock);
	Sock = 0;

	return 1;
}

int CPSock::AddMessage(char* pMsg, int Size)
{
	if (SendQueue[0] != 0)
	{
		if (SendCount > 15)
		{
			if (EncodeByte)
			{

			}
		}
	}
}

int CPSock::AddMessage_0(char* pMsg, int Size, int FixedKeyWord)
{
	return 0;
}

bool CPSock::SendMessageA()
{
	return false;
}

int CPSock::SendOneMessage(char* Msg, int Size)
{
	return 0;
}

int CPSock::SendOneMessageKeyword(char* Msg, int Size, int Keyword)
{
	return 0;
}

int CPSock::AddMessage2(char* pMsg, int Size)
{
	return 0;
}

char* CPSock::ReadMessage2(int* ErrorCode, int* ErrorType)
{
	return nullptr;
}

void CPSock::RefreshRecvBuffer()
{
}

void CPSock::RefreshSendBuffer()
{
}
