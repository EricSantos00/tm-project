#include "pch.h"
#include "CPSock.h"
#include <WinSock2.h>
#include "Basedef.h"
#include "TMGlobal.h"
#include "TMLog.h"

int ConnectPort = 0;

unsigned char pKeyWord[512] = {
	0x84, 0x87, 0x37, 0xd7, 0xea, 0x79, 0x91, 0x7d, 0x4b, 0x4b, 0x85, 0x7d, 0x87, 0x81, 0x91, 0x7c, 0x0f, 0x73, 0x91, 0x91, 0x87, 0x7d, 0x0d, 0x7d, 0x86, 0x8f, 0x73, 0x0f, 0xe1, 0xdd, 0x85, 0x7d,
	0x05, 0x7d, 0x85, 0x83, 0x87, 0x9c, 0x85, 0x33, 0x0d, 0xe2, 0x87, 0x19, 0x0f, 0x79, 0x85, 0x86, 0x37, 0x7d, 0xd7, 0xdd, 0xe9, 0x7d, 0xd7, 0x7d, 0x85, 0x79, 0x05, 0x7d, 0x0f, 0xe1, 0x87, 0x7e,
	0x23, 0x87, 0xf5, 0x79, 0x5f, 0xe3, 0x4b, 0x83, 0xa3, 0xa2, 0xae, 0x0e, 0x14, 0x7d, 0xde, 0x7e, 0x85, 0x7a, 0x85, 0xaf, 0xcd, 0x7d, 0x87, 0xa5, 0x87, 0x7d, 0xe1, 0x7d, 0x88, 0x7d, 0x15, 0x91,
	0x23, 0x7d, 0x87, 0x7c, 0x0d, 0x7a, 0x85, 0x87, 0x17, 0x7c, 0x85, 0x7d, 0xac, 0x80, 0xbb, 0x79, 0x84, 0x9b, 0x5b, 0xa5, 0xd7, 0x8f, 0x05, 0x0f, 0x85, 0x7e, 0x85, 0x80, 0x85, 0x98, 0xf5, 0x9d,
	0xa3, 0x1a, 0x0d, 0x19, 0x87, 0x7c, 0x85, 0x7d, 0x84, 0x7d, 0x85, 0x7e, 0xe7, 0x97, 0x0d, 0x0f, 0x85, 0x7b, 0xea, 0x7d, 0xad, 0x80, 0xad, 0x7d, 0xb7, 0xaf, 0x0d, 0x7d, 0xe9, 0x3d, 0x85, 0x7d,
	0x87, 0xb7, 0x23, 0x7d, 0xe7, 0xb7, 0xa3, 0x0c, 0x87, 0x7e, 0x85, 0xa5, 0x7d, 0x76, 0x35, 0xb9, 0x0d, 0x6f, 0x23, 0x7d, 0x87, 0x9b, 0x85, 0x0c, 0xe1, 0xa1, 0x0d, 0x7f, 0x87, 0x7d, 0x84, 0x7a,
	0x84, 0x7b, 0xe1, 0x86, 0xe8, 0x6f, 0xd1, 0x79, 0x85, 0x19, 0x53, 0x95, 0xc3, 0x47, 0x19, 0x7d, 0xe7, 0x0c, 0x37, 0x7c, 0x23, 0x7d, 0x85, 0x7d, 0x4b, 0x79, 0x21, 0xa5, 0x87, 0x7d, 0x19, 0x7d,
	0x0d, 0x7d, 0x15, 0x91, 0x23, 0x7d, 0x87, 0x7c, 0x85, 0x7a, 0x85, 0xaf, 0xcd, 0x7d, 0x87, 0x7d, 0xe9, 0x3d, 0x85, 0x7d, 0x15, 0x79, 0x85, 0x7d, 0xc1, 0x7b, 0xea, 0x7d, 0xb7, 0x7d, 0x85, 0x7d,
	0x85, 0x7d, 0x0d, 0x7d, 0xe9, 0x73, 0x85, 0x79, 0x05, 0x7d, 0xd7, 0x7d, 0x85, 0xe1, 0xb9, 0xe1, 0x0f, 0x65, 0x85, 0x86, 0x2d, 0x7d, 0xd7, 0xdd, 0xa3, 0x8e, 0xe6, 0x7d, 0xde, 0x7e, 0xae, 0x0e,
	0x0f, 0xe1, 0x89, 0x7e, 0x23, 0x7d, 0xf5, 0x79, 0x23, 0xe1, 0x4b, 0x83, 0x0c, 0x0f, 0x85, 0x7b, 0x85, 0x7e, 0x8f, 0x80, 0x85, 0x98, 0xf5, 0x7a, 0x85, 0x1a, 0x0d, 0xe1, 0x0f, 0x7c, 0x89, 0x0c,
	0x85, 0x0b, 0x23, 0x69, 0x87, 0x7b, 0x23, 0x0c, 0x1f, 0xb7, 0x21, 0x7a, 0x88, 0x7e, 0x8f, 0xa5, 0x7d, 0x80, 0xb7, 0xb9, 0x18, 0xbf, 0x4b, 0x19, 0x85, 0xa5, 0x91, 0x80, 0x87, 0x81, 0x87, 0x7c,
	0x0f, 0x73, 0x91, 0x91, 0x84, 0x87, 0x37, 0xd7, 0x86, 0x79, 0xe1, 0xdd, 0x85, 0x7a, 0x73, 0x9b, 0x05, 0x7d, 0x0d, 0x83, 0x87, 0x9c, 0x85, 0x33, 0x87, 0x7d, 0x85, 0x0f, 0x87, 0x7d, 0x0d, 0x7d,
	0xf6, 0x7e, 0x87, 0x7d, 0x88, 0x19, 0x89, 0xf5, 0xd1, 0xdd, 0x85, 0x7d, 0x8b, 0xc3, 0xea, 0x7a, 0xd7, 0xb0, 0x0d, 0x7d, 0x87, 0xa5, 0x87, 0x7c, 0x73, 0x7e, 0x7d, 0x86, 0x87, 0x23, 0x85, 0x10,
	0xd7, 0xdf, 0xed, 0xa5, 0xe1, 0x7a, 0x85, 0x23, 0xea, 0x7e, 0x85, 0x98, 0xad, 0x79, 0x86, 0x7d, 0x85, 0x7d, 0xd7, 0x7d, 0xe1, 0x7a, 0xf5, 0x7d, 0x85, 0xb0, 0x2b, 0x37, 0xe1, 0x7a, 0x87, 0x79,
	0x84, 0x7d, 0x73, 0x73, 0x87, 0x7d, 0x23, 0x7d, 0xe9, 0x7d, 0x85, 0x7e, 0x02, 0x7d, 0xdd, 0x2d, 0x87, 0x79, 0xe7, 0x79, 0xad, 0x7c, 0x23, 0xda, 0x87, 0x0d, 0x0d, 0x7b, 0xe7, 0x79, 0x9b, 0x7d,
	0xd7, 0x8f, 0x05, 0x7d, 0x0d, 0x34, 0x8f, 0x7d, 0xad, 0x87, 0xe9, 0x7c, 0x85, 0x80, 0x85, 0x79, 0x8a, 0xc3, 0xe7, 0xa5, 0xe8, 0x6b, 0x0d, 0x74, 0x10, 0x73, 0x33, 0x17, 0x0d, 0x37, 0x21, 0x19
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
	unsigned char KeyWord = pKeyWord[iKeyWord * 2];
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

	unsigned char Sum1 = 0;
	unsigned char Sum2 = 0;
	int pos = KeyWord;
	for (int i = sizeof(int); i < Size; i++, pos++)
	{
		Sum2 += pMsg[i];

		int rst = pos % 256;
		unsigned char Trans = pKeyWord[rst * 2 + 1];

		int mod = i & 0x3;

		if (mod == 0) 
			pMsg[i] = pMsg[i] - (Trans << 1);
		if (mod == 1) 
			pMsg[i] = pMsg[i] + (Trans >> 3);
		if (mod == 2) 
			pMsg[i] = pMsg[i] - (Trans << 2);
		if (mod == 3) 
			pMsg[i] = pMsg[i] + (Trans >> 5);

		Sum1 += pMsg[i];
	}

	if ((unsigned char)(Sum2 - Sum1) != CheckSum)
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
	int Keyword = 0;
	if (SendQueue[0])
	{
		if (SendCount > 15)
		{
			if (EncodeByte)
			{
				// we don't need this now... maaybe we can decompile later...
			}
			else
			{
				if (SendQueue[15] % 2)
					Keyword = SendQueue[11] + SendQueue[13] - SendQueue[9] + 4;
				else
					Keyword = SendQueue[3] + SendQueue[1] + SendQueue[5] - 87;

				Keyword ^= 0xFF;
			}
		}
		else if(SendQueue[0])
		{
			if (SendCount > 15)
			{
				if (SendQueue[15] % 2)
					Keyword = SendQueue[11] + SendQueue[13] - SendQueue[9] + 4;
				else
					Keyword = SendQueue[3] + SendQueue[1] + SendQueue[5] - 87;

				Keyword ^= 0xFF;
			}
			else
				Keyword = SendQueue[SendCount++] ^ 0xFF;
		}
	}

	return AddMessage(pMsg, Size, Keyword);
}

int CPSock::AddMessage(char* pMsg, int Size, int FixedKeyWord)
{
	if (!Sock)
	{
		ErrCount = 10;

		return 0;
	}

	if (Size + nSendPosition < SEND_BUFFER_SIZE)
	{
		unsigned char iKeyWord = FixedKeyWord;
		if (!FixedKeyWord)
			iKeyWord = rand() % 256;

		unsigned char KeyWord = pKeyWord[iKeyWord * 2];
		
		auto packet = reinterpret_cast<MSG_STANDARD*>(pMsg);
		packet->Size = Size;
		packet->KeyWord = iKeyWord;
		packet->CheckSum = 0;

		packet->Tick = CurrentTime;
		LastSendTime = CurrentTime;

		unsigned char Sum1 = 0;
		unsigned char Sum2 = 0;

		int pos = KeyWord;
		int i = 4;

		while (i < Size)
		{
			Sum1 += pMsg[i];

			int rst = pos % 256;
			unsigned char Trans = pKeyWord[rst * 2 + 1];
			int mod = i & 3;

			if (!mod)
				pSendBuffer[i + nSendPosition] = pMsg[i] + 2 * Trans;
			else if (mod == 1)
				pSendBuffer[i + nSendPosition] = pMsg[i] - ((int)Trans >> 3);
			else if (mod == 2)
				pSendBuffer[i + nSendPosition] = pMsg[i] + 4 * Trans;
			else if (mod == 3)
				pSendBuffer[i + nSendPosition] = pMsg[i] - ((int)Trans >> 5);

			Sum2 += pSendBuffer[i++ + nSendPosition];
			++pos;
		}

		unsigned char checkSum = Sum2 - Sum1;
		packet->CheckSum = checkSum;
		memcpy(&pSendBuffer[nSendPosition], pMsg, 4u);

		nSendPosition += Size;

		SendMessageA();
		return 1;
	}

	ErrCount = 1;
	return 0;
}

bool CPSock::SendMessageA()
{
	if (!Sock)
	{
		nSendPosition = 0;
		nSentPosition = 0;

		return false;
	}

	if (nSentPosition > 0)
		RefreshSendBuffer();

	char temp[256] = { 0 };
	if (nSendPosition <= SEND_BUFFER_SIZE && nSendPosition >= 0)
	{
		if (nSentPosition > nSendPosition || nSentPosition >= SEND_BUFFER_SIZE || nSentPosition < 0)
		{
			sprintf_s(temp, "err, send2 %d %d %d", nSendPosition, nSentPosition, Sock);

			//Log(temp, "-system", 0);
			nSendPosition = 0;
			nSentPosition = 0;
		}

		for (int i = 0; i < 1; ++i)
		{
			int tSend = send(Sock, &pSendBuffer[nSentPosition], nSendPosition - nSentPosition, 0);
			if (tSend == -1)
				WSAGetLastError();
			else
				nSentPosition += tSend;

			if (nSentPosition >= nSendPosition && tSend != -1)
			{
				nSendPosition = 0;
				nSentPosition = 0;

				return true;
			}
		}

		return nSendPosition < SEND_BUFFER_SIZE;
	}
	
	sprintf_s(temp, "err,send1 %d %d %d", nSendPosition, nSentPosition, Sock);
	//Log(temp, "-system", 0);
	nSendPosition = 0;
	nSentPosition = 0;
	return false;
}

int CPSock::SendOneMessage(char* Msg, int Size)
{
	AddMessage(Msg, Size);

	return SendMessageA();
}

int CPSock::SendOneMessageKeyword(char* Msg, int Size, int Keyword)
{
	AddMessage(Msg, Size, Keyword);

	return SendMessageA();
}

int CPSock::AddMessage2(char* pMsg, int Size)
{
	if (!Sock)
		return 0;

	if (Size + nSendPosition > SEND_BUFFER_SIZE)
		return 0;

	memcpy(&pSendBuffer[nSendPosition], pMsg, Size);
	nSendPosition += Size;

	return 1;
}

char* CPSock::ReadMessage2(int* ErrorCode, int* ErrorType)
{
	*ErrorCode = 0;

	if (nProcPosition >= nRecvPosition)
	{
		nRecvPosition = 0;
		nProcPosition = 0;
	}
	else if ((unsigned int)(nRecvPosition - nProcPosition) >= 12)
	{
		auto pMsg = &pRecvBuffer[nProcPosition];

		nProcPosition += *(WORD*)pMsg;

		if (nRecvPosition <= nProcPosition)
		{
			nRecvPosition = 0;
			nProcPosition = 0;
		}

		return pMsg;
	}

	return nullptr;
}

void CPSock::RefreshRecvBuffer()
{
	int left = nRecvPosition - nProcPosition;

	if (left > 0 && left <= RECV_BUFFER_SIZE)
	{
		memcpy(pRecvBuffer, &pRecvBuffer[nProcPosition], left);

		nProcPosition = 0;
		nRecvPosition -= left;
	}
}

void CPSock::RefreshSendBuffer()
{
	int left = nSendPosition - nSentPosition;

	if (left > 0 && left <= RECV_BUFFER_SIZE)
	{
		memcpy(pSendBuffer, &pRecvBuffer[nSentPosition], left);

		nSentPosition = 0;
		nSendPosition -= left;
	}
}
