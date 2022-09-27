
#include "ProcessClientMessage.h"

void Exec_MSG_CombineItemShany(int conn, char *pMsg)
{
	MSG_CombineItem *m = (MSG_CombineItem*)pMsg;

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		int invPos = m->InvenPos[i];

		if (invPos < 0 || invPos >= pMob[conn].MaxCarry)
		{
			RemoveTrade(conn);
			return;
		}

		if (memcmp(&pMob[conn].MOB.Carry[invPos], &m->Item[i], sizeof(STRUCT_ITEM)))
		{
			MyLog(LogType::Combines, "err,msg_Combineshany - item remove or changed", pUser[conn].AccountName, 0, pUser[conn].IP);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	int combine = GetMatchCombineShany(m->Item);

	if (combine == 0)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}
	if (combine == 0 && (pMob[conn].Extra.ClassMaster == MORTAL || pMob[conn].Extra.ClassMaster == ARCH && pMob[conn].MOB.CurrentScore.Level < 355))
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
	}

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex)
		{
			char itemlog[2048];

			BASE_GetItemCode(&m->Item[i], itemlog);

			strcat(temp, itemlog);
		}
	}

	int _rand = rand() % 115;
	if (_rand >= 100)
		_rand -= 15;

	if (_rand <= g_pShanyBase || LOCALSERVER)
	{
		STRUCT_ITEM Item;
		memset(&Item, 0, sizeof(STRUCT_ITEM));

		Item.sIndex = 633;

		PutItem(conn, &Item);

		SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		MyLog(LogType::Combines, "*** Combine shany sucess ***", pUser[conn].AccountName, 0, pUser[conn].IP);

		return;
	}
	else
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_CombineFailed]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		MyLog(LogType::Combines, "*** Combine shany fail ***", pUser[conn].AccountName, 0, pUser[conn].IP);

		return;
	}
}