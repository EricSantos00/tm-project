
#include "ProcessClientMessage.h"

void Exec_MSG_Motion(int conn, char *pMsg)
{
	MSG_Motion *m = (MSG_Motion*)pMsg;

	if (pMob[conn].MOB.CurrentScore.Hp == 0 || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);

		AddCrackError(conn, 4, 6);

		return;
	}

	sprintf(temp, "etc,motion motion:%d parm:%d notused:%d", m->Motion, m->Parm, m->NotUsed);
	Log(temp, pUser[conn].AccountName, pUser[conn].IP);

	GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)m, 0);
}