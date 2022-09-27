#include "ProcessClientMessage.h"

void Exec_MSG_CombineItem(int conn, char *pMsg)
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
			MyLog(LogType::Combines, "err,msg_Combine - item remove or changed.", pUser[conn].AccountName, 0, pUser[conn].IP);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	int combine = GetMatchCombine(m->Item);

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

	if (_rand <= combine || LOCALSERVER)
	{
		int itemindex = m->Item[0].sIndex;
		int Extra = g_pItemList[itemindex].Extra;

		if (Extra > 0 && Extra < MAX_ITEMLIST)
		{
			int ipos = m->InvenPos[0];
			int joia = m->Item[1].sIndex - 2441;
									 
			if (joia >= 0 && joia <= 3)
			{
				memcpy(&pMob[conn].MOB.Carry[ipos].sIndex, &m->Item[0], sizeof(STRUCT_ITEM));

				pMob[conn].MOB.Carry[ipos].sIndex = joia + Extra;

				BASE_SetItemSanc(&pMob[conn].MOB.Carry[ipos], 7, 0);

				char tt[256];
				sprintf(tt, g_pMessageStringTable[_SS_CombineSucceed], pMob[conn].MOB.MobName, g_pItemList[Extra].Name);
				sprintf(temp, "%s(%d/%d)", tt, _rand, combine);
				SendNotice(temp);

				SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);
										 
				sprintf(temp, "%s ", pUser[conn].AccountName);
				BASE_GetItemCode(&pMob[conn].MOB.Carry[ipos], tt);
				strcat(temp, tt);
										 
				MyLog(LogType::Combines, "*** combine anct sucess ***", pUser[conn].AccountName, 0, pUser[conn].IP);
				SendItem(conn, ITEM_PLACE_CARRY, ipos, &pMob[conn].MOB.Carry[ipos]);
				return;
			}
			else
			{
				sprintf(temp, "err,msg_combine - stone wrong %d", joia);
				MyLog(LogType::Combines, pUser[conn].AccountName, temp, 0, pUser[conn].IP);
				return;
			}
		}
		else
		{
			sprintf(temp, "err,msg_combine - Extra item index wrong %d", itemindex);
			MyLog(LogType::Combines, pUser[conn].AccountName, temp, 0, pUser[conn].IP);
			return;
		}
	}
	else
	{
		sprintf(temp, "%s(%d/%d)", g_pMessageStringTable[_NN_CombineFailed], _rand, combine);
		SendClientMsg(conn, temp);
								 
		sprintf(temp, "Compositor: [%s], falhou na composição anct do item [%s].", pMob[conn].MOB.MobName, g_pItemList[m->Item->sIndex].Name);
		SendNotice(temp);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		MyLog(LogType::Combines, "*** Combine anct fail ***", pUser[conn].AccountName, 0, pUser[conn].IP);
		return;
	}
}