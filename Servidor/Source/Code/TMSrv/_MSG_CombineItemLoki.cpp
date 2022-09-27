#include "ProcessClientMessage.h"

void Exec_MSG_CombineItemLoki(int conn, char *pMsg)
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
			MyLog(LogType::Combines, "err,msg_CombineLoki - item remove or changed.", pUser[conn].AccountName, 0, pUser[conn].IP);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	int combine = GetMatchCombineLoki(m->Item);

	if (combine == 0)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	if ((combine == 1) && pMob[conn].MOB.Coin < 10000000)

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

	int rate = g_pLokiRate[combine];

	if (_rand <= rate || LOCALSERVER)
	{
		if (combine == 1)
		{
			if (_rand <= 50)
				pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 1740;

			else
				pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 1741;

			pMob[conn].MOB.Coin -= 10000000;
			SendEtc(conn);

		}

		else if (combine == 2)
		{
			if (pMob[conn].MOB.BaseScore.MaxMp > pMob[conn].MOB.BaseScore.MaxHp)
				pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 5552;

			else if (pMob[conn].MOB.BaseScore.MaxHp > pMob[conn].MOB.BaseScore.MaxMp)
				pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 5559;

		}

			SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);

			MyLog(LogType::Combines, "*** Combine loki sucess ***", pUser[conn].AccountName, 0, pUser[conn].IP);

			int TargetVillage = BASE_GetVillage(pMob[conn].TargetX, pMob[conn].TargetY);

			if (TargetVillage >= 0 && TargetVillage < 5)
			{
				if (GuildImpostoID[TargetVillage] >= MAX_USER && GuildImpostoID[TargetVillage] < MAX_MOB && pMob[GuildImpostoID[TargetVillage]].Mode != USER_EMPTY && pMob[GuildImpostoID[TargetVillage]].MOB.Guild == g_pGuildZone[TargetVillage].ChargeGuild)
				{
					if (pMob[GuildImpostoID[TargetVillage]].MOB.Exp < 200000000000)
						pMob[GuildImpostoID[TargetVillage]].MOB.Exp += 10000000 / 10;
				}
			}

			return;
	}
	else
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_CombineFailed]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		MyLog(LogType::Combines, "*** Combine loki fail ***", pUser[conn].AccountName, 0, pUser[conn].IP);

		return;
	}
}