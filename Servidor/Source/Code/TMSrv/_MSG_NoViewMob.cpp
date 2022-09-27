
#include "ProcessClientMessage.h"

void Exec_MSG_NoViewMob(int conn, char *pMsg)
{
	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)pMsg;

	int MobID = m->Parm;

	if (MobID <= 0 || MobID >= MAX_MOB)
	{
		Log("err,reqmobbyid MobId Out of range", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	if (pMob[MobID].Mode == MOB_EMPTY)
	{
		SendRemoveMob(conn, MobID, 0, 0);
		return;
	}

	if (MobID >= MAX_USER || pUser[MobID].Mode == USER_PLAY)
	{
		if (GetInView(conn, MobID))
		{
			SendCreateMob(conn, MobID, 1);
			SendPKInfo(conn, MobID);
		}
		else
			SendRemoveMob(conn, MobID, 0, 0);
	}
	else
		SendRemoveMob(conn, MobID, 0, 0);
}