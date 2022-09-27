
#include "ProcessClientMessage.h"

void Exec_MSG_PKMode(int conn, char *pMsg)
{
	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)pMsg;

	pUser[conn].PKMode = m->Parm != 0 ? 1 : 0;

	if (pUser[conn].Trade.OpponentID)
	{
		if (pUser[pUser[conn].Trade.OpponentID].Mode == USER_PLAY && pUser[pUser[conn].Trade.OpponentID].Trade.OpponentID == conn)
		{
			SendClientMsg(conn, g_pMessageStringTable[_NN_Cant_trade_pkmode]);
			SendClientMsg(pUser[conn].Trade.OpponentID, g_pMessageStringTable[_NN_Cant_trade_pkmode]);

			RemoveTrade(pUser[conn].Trade.OpponentID);
			RemoveTrade(conn);
		}
	}

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

	sprintf(temp, "etc,pkmode %d", pUser[conn].PKMode);
	Log(temp, pUser[conn].AccountName, pUser[conn].IP);
}