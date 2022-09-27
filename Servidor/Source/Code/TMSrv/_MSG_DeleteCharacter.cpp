
#include "ProcessClientMessage.h"

void Exec_MSG_DeleteCharacter(int conn, char *pMsg)
{
	MSG_DeleteCharacter *m = (MSG_DeleteCharacter*)pMsg;

	m->MobName[NAME_LENGTH - 1] = 0;

	if (pUser[conn].Mode == USER_SELCHAR)
	{
		m->Type = _MSG_DBDeleteCharacter;
		m->ID = conn;

		pUser[conn].Mode = USER_WAITDB;

		DBServerSocket.SendOneMessage((char*)m, sizeof(MSG_DeleteCharacter));

		sprintf(temp, "etc,delchar name:%s %d %d", pMob[conn].MOB.MobName, conn, pUser[conn].Mode);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
	}
	else
	{
		SendClientMsg(conn, "Deleting Character. wait a moment.");

		sprintf(temp, "err,delchar not user_selchar %d %d", conn, pUser[conn].Mode);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
	}
}