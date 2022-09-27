
#include "ProcessClientMessage.h"

void Exec_MSG_ReqTradeList(int conn, char *pMsg)
{
	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)pMsg;

	int autoID = m->Parm;

	if (pMob[conn].MOB.CurrentScore.Hp == 0 || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		AddCrackError(conn, 10, 87);
		return;
	}

	if (autoID <= 0 || autoID >= MAX_USER)
		return;

	if (pUser[autoID].TradeMode == 0)
		return;

	if (pMob[conn].TargetX >= pMob[autoID].TargetX - VIEWGRIDX && pMob[conn].TargetX <= pMob[autoID].TargetX + VIEWGRIDX
		&& pMob[conn].TargetY >= pMob[autoID].TargetY - VIEWGRIDY && pMob[conn].TargetY <= pMob[autoID].TargetY + VIEWGRIDY)
		SendAutoTrade(conn, autoID);

	else
		Log("err,too far from autotrade - _MSG_ReqTradeList", pUser[conn].AccountName, pUser[conn].IP);
}