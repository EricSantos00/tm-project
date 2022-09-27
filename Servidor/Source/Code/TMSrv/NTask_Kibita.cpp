#include "ProcessClientMessage.h"

void NTask_Kibita(int a_iConn, int a_iTarget)
{
	if (!NPCBlock[Kibita])
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_NPCBLOCKED]);
		return;
	}

	if (pMob[a_iConn].Extra.Citizen == 0 && pMob[a_iConn].MOB.Coin >= 4000000)
	{
		pMob[a_iConn].MOB.Coin -= 4000000;
		pMob[a_iConn].Extra.Citizen = ServerIndex + 1;

		SendClientMsg(a_iConn, g_pMessageStringTable[_DD_JOINTOWNPEP]);

		SendEtc(a_iConn);

		int TargetVillage = BASE_GetVillage(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY);

		if (TargetVillage >= 0 && TargetVillage < 5)
		{
			if (GuildImpostoID[TargetVillage] >= MAX_USER && GuildImpostoID[TargetVillage] < MAX_MOB && pMob[GuildImpostoID[TargetVillage]].Mode != USER_EMPTY && pMob[GuildImpostoID[TargetVillage]].MOB.Guild == g_pGuildZone[TargetVillage].ChargeGuild)
			{
				if (pMob[GuildImpostoID[TargetVillage]].MOB.Exp < 200000000000)
					pMob[GuildImpostoID[TargetVillage]].MOB.Exp += 4000000 / 10;
			}
		}

		int Guild = pMob[a_iConn].MOB.Guild;

		if (Guild && pMob[a_iConn].MOB.GuildLevel == 9)
		{
			MSG_GuildInfo sm_gi;
			memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

			sm_gi.Type = _MSG_GuildInfo;
			sm_gi.Size = sizeof(MSG_GuildInfo);
			sm_gi.ID = a_iConn;

			sm_gi.Guild = Guild;

			GuildInfo[Guild].Citizen = ServerIndex + 1;

			sm_gi.GuildInfo = GuildInfo[Guild];

			DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));
		}

		sprintf(temp, "etc,set citizen server:%d name:%s a_iConn:%d", ServerIndex + 1, pMob[a_iConn].MOB.MobName, a_iConn);
		MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
		return;
	}

	/*struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	if (when.tm_wday != 0 && when.tm_wday != 6 && when.tm_hour == 21 && pMob[a_iConn].Extra.ClassMaster == MORTAL && pMob[a_iConn].MOB.CurrentScore.Level < 369)
	{
		int i = 0;

		for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex != 420)
				continue;

			break;
		}

		if (i != pMob[a_iConn].MaxCarry)
		{
			BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);
			SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);

			SendClientMsg(a_iConn, g_pMessageStringTable[_DN_TOWN_SOUL_BUFF]);

			int sAffect = GetEmptyAffect(a_iConn, 29);

			if (sAffect == -1)
				return;


			pMob[a_iConn].Affect[sAffect].Type = 29;
			pMob[a_iConn].Affect[sAffect].Level = 0;
			pMob[a_iConn].Affect[sAffect].Value = 0;
			pMob[a_iConn].Affect[sAffect].Time = AFFECT_1H;

			pMob[a_iConn].GetCurrentScore(a_iConn);
			SendScore(a_iConn);

			DoTeleport(a_iConn, 2454 + rand() % 3, 1843 + rand() % 3);

			sprintf(temp, "etc,kibita limit of soul mortal name:%s a_iConn:%d", pMob[a_iConn].MOB.MobName, a_iConn);
			MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
			return;
		}

		else
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_DN_TOWN_SOUL_NOBUFF]);
			return;
		}
	}*/

	if (pMob[a_iConn].Extra.ClassMaster == MORTAL && (pMob[a_iConn].MOB.LearnedSkill & (1 << 30)) == 0 && pMob[a_iConn].MOB.CurrentScore.Level >= 369)
	{
		int i = 0;

		int stones[4] = { 5334, 5336, 5335, 5337 };

		for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex != stones[pMob[a_iConn].MOB.Class])
				continue;

			break;
		}

		if (i != pMob[a_iConn].MaxCarry)
		{
			BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);
			SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);

			pMob[a_iConn].MOB.LearnedSkill |= 1 << 30;

			memset(&pMob[a_iConn].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));

			if (pMob[a_iConn].MOB.Clan == 7)
				pMob[a_iConn].MOB.Equip[15].sIndex = 3194;

			else if (pMob[a_iConn].MOB.Clan == 8)
				pMob[a_iConn].MOB.Equip[15].sIndex = 3195;

			else
				pMob[a_iConn].MOB.Equip[15].sIndex = 3196;

			SendItem(a_iConn, ITEM_PLACE_EQUIP, 15, &pMob[a_iConn].MOB.Equip[15]);

			CharLogOut(a_iConn);

			sprintf(temp, "etc,learned limit of soul mortal name:%s a_iConn:%d", pMob[a_iConn].MOB.MobName, a_iConn);
			MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

			SendClientSignalParm(a_iConn, ESCENE_FIELD, _MSG_SendArchEffect, pUser[a_iConn].Slot);
			return;
		}
	}

	SendClientMsg(a_iConn, g_pMessageStringTable[_DN_TOWN_SORRY]);
	return;
}