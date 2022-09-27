#include "ProcessClientMessage.h"

void Exec_MSG_GuildAlly(int conn, char *pMsg)
{
	MSG_GuildAlly *m = (MSG_GuildAlly*)pMsg;

	int Guild = m->Guild;
	int Ally = m->Ally;

	if(Guild <= 0 || Guild >= 65536)
		return;

	if(Ally <= 0 || Ally >= 65536)
		return;

	if(pMob[conn].MOB.Guild != Guild || pMob[conn].MOB.GuildLevel != 9)
		return;

	MSG_STANDARDPARM2 sm_ga;
	memset(&sm_ga, 0, sizeof(MSG_STANDARDPARM2));

	sm_ga.Size = sizeof(MSG_STANDARDPARM2);
	sm_ga.Type = _MSG_GuildAlly;
	sm_ga.ID = conn;

	sm_ga.Parm1 = Guild;
	sm_ga.Parm2 = Ally;

	DBServerSocket.SendOneMessage((char*)&sm_ga, sizeof(MSG_STANDARDPARM2));
}