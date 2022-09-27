#include "ProcessClientMessage.h"

void Exec_MSG_CombineItemAgatha(int conn, char *pMsg)
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
			MyLog(LogType::Combines, "err,msg_CombineAgatha - item remove or changed.", pUser[conn].AccountName, 0, pUser[conn].IP);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	int combine = GetMatchCombineAgatha(m->Item);

	if (combine == 0)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		if (i == 1)
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

	int ipos = m->InvenPos[0];

	if (_rand <= combine || LOCALSERVER)
	{
		pMob[conn].MOB.Carry[ipos].sIndex = m->Item[0].sIndex;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect = m->Item[1].stEffect[0].cEffect;
		pMob[conn].MOB.Carry[ipos].stEffect[0].cValue = m->Item[1].stEffect[0].cValue;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect = m->Item[1].stEffect[1].cEffect;
		pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = m->Item[1].stEffect[1].cValue;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect = m->Item[1].stEffect[2].cEffect;
		pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = m->Item[1].stEffect[2].cValue;

		BASE_SetItemSanc(&pMob[conn].MOB.Carry[ipos], 7, 0);

		memset(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);
		SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);
		sprintf(temp, "Agatha: [%s] obteve sucesso ao passar adicional para o item [%s]", pMob[conn].MOB.MobName, g_pItemList[m->Item->sIndex].Name);
		SendNotice(temp);
		char tt[512];

		sprintf(temp, "%s ", pUser[conn].AccountName);
		BASE_GetItemCode(&pMob[conn].MOB.Carry[ipos], tt);
		strcat(temp, tt);

		MyLog(LogType::Combines, "*** combine agatha sucess ***", pUser[conn].AccountName, 0, pUser[conn].IP);
		SendItem(conn, ITEM_PLACE_CARRY, ipos, &pMob[conn].MOB.Carry[ipos]);
		return;
	}
	else
	{
		sprintf(temp, "%s", g_pMessageStringTable[_NN_CombineFailed]);
		SendClientMsg(conn, temp);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		sprintf(temp, "Agatha: [%s] falhou ao passar adicional para o item [%s]", pMob[conn].MOB.MobName, g_pItemList[m->Item->sIndex].Name);
		SendNotice(temp);
		MyLog(LogType::Combines, "*** combine agatha fail ***", pUser[conn].AccountName, 0, pUser[conn].IP);
		return;
	}
}