
#include "ProcessClientMessage.h"

void Exec_MSG_DeleteItem(int conn, char *pMsg)
{
	MSG_DeleteItem *m = (MSG_DeleteItem*)pMsg;

	if (m->Slot < 0 || m->Slot >= MAX_CARRY - 4)
		return;

	if (m->sIndex <= 0 || m->sIndex >= MAX_ITEMLIST)
		return;

	if (pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		RemoveTrade(conn);
		return;
	}

	if (pUser[conn].IsBlocked)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		SendClientMsg(conn, "Sua conta está com o bloqueio ativo para essa operação.");
		RemoveTrade(conn);
		return;
	}

	char itemtmp[2048];
	BASE_GetItemCode(&pMob[conn].MOB.Carry[m->Slot], itemtmp);

	sprintf(temp, "deleteitem, %s", itemtmp);
	MyLog(LogType::Itens, pMob[conn].MOB.MobName, temp, 0, pUser[conn].IP);

	memset(&pMob[conn].MOB.Carry[m->Slot], 0, sizeof(STRUCT_ITEM));
}