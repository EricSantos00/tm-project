
#include "ProcessClientMessage.h"

void Exec_MSG_War(int conn, char *pMsg)
{
	MSG_STANDARDPARM2 *m = (MSG_STANDARDPARM2*)pMsg;

	int Guild = m->Parm1;
	int Enemy = m->Parm2;

	if(Guild <= 0 || Guild >= 65536)
		return;

	if(Enemy <= 0 || Enemy >= 65536)
		return;

	if(pMob[conn].MOB.Guild != Guild || pMob[conn].MOB.GuildLevel != 9)
		return;

	MSG_STANDARDPARM2 sm_war;
	memset(&sm_war, 0, sizeof(MSG_STANDARDPARM2));

	sm_war.Size = sizeof(MSG_STANDARDPARM2);
	sm_war.Type = _MSG_War;
	sm_war.ID = conn;

	sm_war.Parm1 = Guild;
	sm_war.Parm2 = Enemy;

	DBServerSocket.SendOneMessage((char*)&sm_war, sizeof(MSG_STANDARDPARM2));
}