#include <Windows.h>

#include "CUser.h"
/* revisado */
extern HWND hWndMain; // Server.cpp

CUser::CUser()
{
	Mode = USER_EMPTY;
	IP   = 0;
	Count = 0;
	DisableID = 0;
	Level = -1;
	Encode1 = 0;
	Encode2 = 0;
	Year = 0;
	YearDay = 0;
	Name[0] = 0;
}

CUser::~CUser()
{
}

BOOL CUser::AcceptUser(int ListenSocket, int wsa)
{
	SOCKADDR_IN acc_sin; 
	int Size = sizeof(acc_sin);

	int tSock = accept(ListenSocket, (struct sockaddr FAR *)&acc_sin, (int FAR *)&(Size));

	if(tSock < 0) 
		return FALSE;

	if(WSAAsyncSelect(tSock, hWndMain, wsa , FD_READ | FD_CLOSE) > 0)
	{ 
		closesocket(tSock);
		return FALSE;
	}

	cSock.Sock          = tSock;
	cSock.nRecvPosition = 0;
	cSock.nProcPosition = 0;
	cSock.nSendPosition = 0;

	char * tmp = inet_ntoa(acc_sin.sin_addr);
	IP		   = acc_sin.sin_addr.S_un.S_addr;
	Mode	   = USER_ACCEPT;

	return TRUE;
}