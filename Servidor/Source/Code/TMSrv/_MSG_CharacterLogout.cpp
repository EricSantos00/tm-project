
#include "ProcessClientMessage.h"

void Exec_MSG_CharacterLogout(int conn, char *pMsg)
{
	RemoveParty(conn);
	CharLogOut(conn);

	pUser[conn].cSock.SendMessageA();
}