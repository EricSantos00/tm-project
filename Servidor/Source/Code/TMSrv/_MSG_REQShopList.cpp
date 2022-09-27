
#include "ProcessClientMessage.h"

void Exec_MSG_REQShopList(int conn, char *pMsg)
{
	MSG_REQShopList *m = (MSG_REQShopList*)pMsg;

	if (pMob[conn].MOB.CurrentScore.Hp == 0 || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		AddCrackError(conn, 10, 22);
		return;
	}

	int target = m->Target;

	if (target < MAX_USER || target >= MAX_MOB)
	{
		Log("err,MSG_ReqShopList target range", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	if (pMob[target].MOB.Merchant == 0)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_He_Is_Not_Merchant]);
		return;
	}

	int view = GetInView(conn, target);

	if (view == 0)
		return;

	if (pMob[target].MOB.Merchant == 1)
		SendShopList(conn, target, 1);

	else if ((pMob[target].MOB.Merchant) == 19)
		SendShopList(conn, target, 3);
}