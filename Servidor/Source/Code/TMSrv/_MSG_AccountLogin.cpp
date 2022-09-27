
#include "ProcessClientMessage.h"
#include "StatusServer.h"

void Exec_MSG_AccountLogin(int conn, char *pMsg)
{
	MSG_AccountLogin *m = (MSG_AccountLogin*)pMsg;

	int Size = m->Size;
	int ClientVersion = APP_VERSION;

	pUser[conn].AccountName[NAME_LENGTH - 1] = 0;

	if (conn <= 0 || (conn >= (MAX_USER - ADMIN_RESERV)))
	{
		sprintf(temp, g_pMessageStringTable[_NN_Reconnect]);
		SendClientMsg(conn, temp);

		pUser[conn].cSock.SendMessageA();

		CloseUser(conn);
		return;
	}
		
	if (Size != sizeof(MSG_AccountLogin) /*|| m->ClientVersion != ClientVersion*/)
	{
		sprintf(temp, g_pMessageStringTable[_NN_Version_Not_Match_Rerun]);
		SendClientMsg(conn, temp);

		pUser[conn].cSock.SendMessageA();

		CloseUser(conn);
		return;
	}

	unsigned char sServer = GetStatusServer(conn, m->AccountName);
	switch (sServer)
	{
	case sOff:
	case sMaintenance:
	case sStaff:
		pUser[conn].cSock.SendMessageA();
		CloseUser(conn);
		return;
	case sFree:
		break;
	default:
		break;
	}

			
	if(pUser[conn].Mode != USER_ACCEPT)
	{
		SendClientMsg(conn, "Login now, wait a moment.");

		CrackLog(conn, " accountlogin");
		pUser[conn].cSock.SendMessageA(); 
		return;
	}

	time_t rawnow = time(NULL);
	struct tm* now = localtime(&rawnow);

	auto min = now->tm_min;
	auto sec = now->tm_sec;
	auto hour = now->tm_hour;

	FILE* fs = nullptr;
	fs = fopen(strFmt("Ban/%s.bin", m->AccountName), "rb");

	if (fs)
	{
		fread(&BannedUser[conn], 1, sizeof(AccountBanned), fs);
		fclose(fs);
		memcpy(&BannedUser[conn], &BannedUser[conn], sizeof(AccountBanned));
		auto account = &BannedUser[conn];

		if (account->Permanente)
		{
			SendClientMsg(conn, "Conta banida permanentemente. Entre em contato com o suporte para mais informações.");
			pUser[conn].cSock.SendMessageA();
			return;
		}

		if (account->Analyze)
		{
			SendClientMsg(conn, "Estamos analizando a sua conta. Entre em contato com o suporte.");
			pUser[conn].cSock.SendMessageA();
			return;
		}

		if (account->Ativa)
		{
			SendClientMsg(conn, "Conta aguardando ativação por email.");
			pUser[conn].cSock.SendMessageA();
			return;
		}

		if (now->tm_mon < account->mes || now->tm_mon == account->mes &&
			now->tm_mday < account->dia || now->tm_mon == account->mes &&
			now->tm_mday == account->dia && now->tm_hour < account->hora ||
			now->tm_mon == account->mes && now->tm_mday == account->dia &&
			now->tm_hour == account->hora && now->tm_min < account->min)
		{
			SendClientMsg(conn, strFmt("Conta bloqueada até as: [%02d:%02d] de [%02d/%02d/%04d] ", account->hora, account->min, account->dia, account->mes + 1, account->ano + 1900));
			pUser[conn].cSock.SendMessageA();
			return ;
		}
		remove(strFmt("Ban/%s.bin", m->AccountName));
	}
	char arrayMac[20];
	memcpy(arrayMac, m->AdapterName, sizeof(pUser[conn].Mac));
	int tMac = ReadBanMac(arrayMac, sizeof(pUser[conn].Mac));

	if (tMac)
	{
		SendClientMsg(conn, strFmt("Esse computador foi banido, entre em contato com a Staff Eternal "));
		pUser[conn].cSock.SendMessageA();
		return;
	}

	if (m->Size < sizeof(MSG_AccountLogin))
		memset(pUser[conn].Mac, 0xFF, sizeof(pUser[conn].Mac));
	else
		memcpy(pUser[conn].Mac, m->AdapterName, sizeof(pUser[conn].Mac));


	m->Type = _MSG_DBAccountLogin;
	m->ID = conn;

	sscanf(m->AccountName, "%s", pUser[conn].AccountName);

	_strupr(pUser[conn].AccountName);

	strncpy(m->AccountName, pUser[conn].AccountName, NAME_LENGTH);

	int check = CheckFailAccount(m->AccountName);

	if(check >= 3)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_3_Tims_Wrong_Pass]);

		pUser[conn].cSock.SendMessageA();
		return;
	}

	DBServerSocket.SendOneMessage((char*)m, sizeof(MSG_AccountLogin));

	pUser[conn].Mode = USER_LOGIN;
	pMob[conn].Mode = MOB_EMPTY;
}