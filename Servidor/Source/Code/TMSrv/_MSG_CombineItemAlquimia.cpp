#include "ProcessClientMessage.h"

void Exec_MSG_CombineItemAlquimia(int conn, char *pMsg)
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
			MyLog(LogType::Combines, "err,msg_CombineAlquimia - item remove or changed.", pUser[conn].AccountName, 0, pUser[conn].IP);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	int combine = GetMatchCombineAlquimia(m->Item);

	if (combine == -1 || pMob[conn].MOB.Class != 3)
	{
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

	int chance = (pMob[conn].MOB.CurrentScore.Special[2] + 1) / 6;

	if (_rand <= chance || LOCALSERVER)
	{
		pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 3200 + combine;
		pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[0].cEffect = 0;
		pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[0].cValue = 0;
		pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[1].cEffect = 0;
		pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[1].cValue = 0;
		pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[2].cEffect = 0;
		pMob[conn].MOB.Carry[m->InvenPos[0]].stEffect[2].cValue = 0;

		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);
		SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);
    	SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		sprintf(temp, "%s ", pUser[conn].AccountName);
		MyLog(LogType::Combines, "*** Item combine ht_skill_alquimia sucess *** ", pUser[conn].AccountName, 0, pUser[conn].IP);

		return;
	}
	else
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_CombineFailed]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		MyLog(LogType::Combines, "*** Item combine ht_skill_alquimia fail *** ", pUser[conn].AccountName, 0, pUser[conn].IP);
		return;
	}
}