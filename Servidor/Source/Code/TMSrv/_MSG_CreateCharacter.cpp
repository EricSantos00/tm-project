
#include "ProcessClientMessage.h"

void Exec_MSG_CreateCharacter(int conn, char *pMsg)
{
	MSG_CreateCharacter *m = (MSG_CreateCharacter*)pMsg;

	m->MobName[NAME_LENGTH - 1] = 0;
	m->MobName[NAME_LENGTH - 2] = 0;

	if(pUser[conn].Mode != USER_SELCHAR)
	{
		sprintf(temp, "err,createchar not user_selchar %d %d", conn, pUser[conn].Mode);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
				
		SendClientSignal(conn, 0, _MSG_NewCharacterFail);
		return;
	} 

	if (BASE_CheckValidString(m->MobName))
	{
		m->Type = _MSG_DBCreateCharacter;
		m->ID = conn;

		pUser[conn].Mode = USER_WAITDB;

		DBServerSocket.SendOneMessage((char*)m, sizeof(MSG_CreateCharacter));

		sprintf(temp, "etc,createchar name:%s %d %d", m->MobName, conn, pUser[conn].Mode);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);
	}
	else
		SendClientSignal(conn, 0, _MSG_NewCharacterFail);
}