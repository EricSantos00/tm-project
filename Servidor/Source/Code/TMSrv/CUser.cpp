
#include <Windows.h>

#include "CUser.h"
#include "Server.h"
#include "CReadFiles.h"


CUser::CUser()
{	
	Mode		     = USER_EMPTY;
	Unk3			 = 0;
	IsBillConnect    = 0;
	LastReceiveTime  = 0;

	memset(Cargo, 0, sizeof(Cargo));

	Admin			 = 0;
	CastleStatus	 = 0;
	MuteChat		 = 0;
	UseItemTime		 = 0;
	Message			 = 0;
	AttackTime		 = 0;
	LastClientTick	 = 0;
	PotionTime		 = 0;

	OnlyTrade		 = 0;
}

CUser::~CUser()
{

}

BOOL CUser::AcceptUser(int ListenSocket)
{
	SOCKADDR_IN acc_sin; 
	int Size = sizeof(acc_sin);

	int tSock = accept(ListenSocket, (struct sockaddr FAR *)&acc_sin, (int FAR *)&(Size));

	if(tSock < 0) 
		return FALSE;

	if(WSAAsyncSelect(tSock, hWndMain, WSA_READ, FD_READ | FD_CLOSE ) > 0) 
	{	
		closesocket(tSock);

		return FALSE;
	}

	cSock.Sock          = tSock;
	cSock.nRecvPosition = 0;
	cSock.nProcPosition = 0;
	cSock.nSendPosition = 0;

	char *tmp  = inet_ntoa(acc_sin.sin_addr);
	IP		   = acc_sin.sin_addr.S_un.S_addr;
	Mode	   = USER_ACCEPT;
	Unk3	   = 0;

	return TRUE;
}

int CUser::CloseUser()
{
     cSock.CloseSocket();
	 cSock.Sock		= 0;
	 IsBillConnect  = 0;
	 
	 Mode = USER_EMPTY;

	 AccountName[0] = 0;

	 CReadFiles::WriteCountPlayer();
	 return TRUE;
}