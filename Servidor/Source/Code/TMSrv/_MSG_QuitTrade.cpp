
#include "ProcessClientMessage.h"

void Exec_MSG_QuitTrade(int conn, char *pMsg)
{
	if(pMob[conn].MOB.CurrentScore.Hp <= 0 || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		AddCrackError(conn, 10, 17);
		return; 
	}
						   
	RemoveTrade(pUser[conn].Trade.OpponentID);
	RemoveTrade(conn);

	pUser[conn].ISTradTimer = 0;

	MSG_STANDARDPARM sm;
	memset(&sm, 0, sizeof(MSG_STANDARDPARM));

	sm.Size = sizeof(MSG_STANDARDPARM);
	sm.Type = _MSG_PKInfo;
	sm.ID = conn;

	if (NewbieEventServer == 0)
	{
		int guilty = GetGuilty(conn);

		int state = 0;

		if (guilty || pUser[conn].PKMode || CastleState && pMob[conn].TargetX >= 1024 && pMob[conn].TargetY >= 1664 && pMob[conn].TargetX <= 1153 && pMob[conn].TargetY <= 1793 || GTorreState && pMob[conn].TargetX >= 2430 && pMob[conn].TargetY >= 1825 && pMob[conn].TargetX <= 2560 && pMob[conn].TargetY <= 1925)
			state = 1;

		sm.Parm = state;
	}
	else
		sm.Parm = 1;

	GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, 0);
}