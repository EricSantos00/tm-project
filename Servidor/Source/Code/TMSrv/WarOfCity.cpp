#include "WarOfCity.h"

void WarCity()
{
	time_t rawtime;
	tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	if (warsTimer[eCity].Days[timeinfo->tm_wday] > 1)
	{
		sprintf(temp, "warTimer.json,error config days %d [permitido 0 ou 1] ", warsTimer[eCity].Days[timeinfo->tm_wday]);
		MyLog(LogType::System, "War Citys", temp, 0, 0);
	}
	if (warsTimer[eCity].Days[timeinfo->tm_wday])
	{
		GuildDay = timeinfo->tm_wday;
		GuildHour = warsTimer[eCity].Hour;
	}
	int day = GuildDay - 1;

	if (day < 0)
		day += 7;

	int fweek = timeinfo->tm_wday;

	if (ForceWeekMode != -1)
		fweek = -1;

	if (WeekMode || ((fweek != GuildDay) || timeinfo->tm_hour < GuildHour) && ForceWeekMode != 1)
	{
		if (WeekMode != 1 || (fweek != GuildDay || (timeinfo->tm_hour < GuildHour) || timeinfo->tm_min <= 2) && ForceWeekMode != 2)
		{
			if (WeekMode != 2 || ((fweek != GuildDay) || timeinfo->tm_hour < GuildHour || timeinfo->tm_min <= 5) && ForceWeekMode != 3)
			{
				if (WeekMode != 3
					|| (fweek != GuildDay || (timeinfo->tm_hour < GuildHour) || timeinfo->tm_min <= 20) && ForceWeekMode != 4)
				{
					if (WeekMode != 4 || fweek != day && ForceWeekMode != 5)
					{
						if (WeekMode == 5 && (fweek == GuildDay || !ForceWeekMode))
						{
							SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice6]);
							WeekMode = 0;

							for (int i = 0; i < MAX_GUILDZONE; i++)
							{
								if (i == 4)
									continue;

								if (g_pGuildZone[i].ChallangeGuild == 0 && g_pGuildZone[i].Victory < 4)
									g_pGuildZone[i].Victory++;
							}

						}
					}
					else
					{
						SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice5]);
						WeekMode = 5;
					}
				}
				else
				{
					SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice4]);
					DecideWinner();
					ClearGuildPKZone();
					ClearChallanger();
					CReadFiles::WriteChallanger();
					SetArenaDoor(STATE_LOCKED);
					WeekMode = 4;

					GuildZoneReport();
				}
			}
			else
			{
				SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice3]);
				WeekMode = 3;
				SetArenaDoor(STATE_OPEN);
			}
		}
		else
		{
			SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice2]);
			ClearGuildPKZone();
			WeekMode = 2;
			SetArenaDoor(STATE_LOCKED);

			for (int n = 0; n < ValidGuild; n++)
			{
				if (n != 4)
				{
					if (g_pGuildZone[n].ChallangeGuild)
					{
						if (g_pGuildZone[n].ChargeGuild)
							SummonGuild(g_pGuildZone[n].ChargeGuild, g_pGuildZone[n].ChargeWarSpawnX, g_pGuildZone[n].ChargeWarSpawnY, NumGuildBattle, n);
					}
				}
			}

			for (int n = 0; n < ValidGuild; n++)
			{
				if (n != 4)
				{
					if (g_pGuildZone[n].ChallangeGuild)
						SummonGuild(g_pGuildZone[n].ChallangeGuild, g_pGuildZone[n].ChallangeWarSpawnX, g_pGuildZone[n].ChallangeWarSpawnY, NumGuildBattle, n);
				}
			}
		}
	}
	else
	{
		SendNotice(g_pMessageStringTable[_NN_Guild_Battle_Notice1]);
		WeekMode = 1;
	}
}

void ClearGuildPKZone()
{
	int x1 = 128;
	int y1 = 128;

	int x2 = 256;
	int y2 = 256;

	for (int i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (pMob[i].Mode == 0)
			continue;

		if (pMob[i].TargetX >= x1 && pMob[i].TargetX <= x2 && pMob[i].TargetY >= y1 && pMob[i].TargetY <= y2)
			DoRecall(i);
	}
}

void DecideWinner()
{
	for (int i = 0; i < ValidGuild; i++)
	{
		if (/*i == 3 ||*/ i == 4)
			continue;

		int ChargeSurvivor = 0;
		int ChallangeSurvivor = 0;

		int ChargeGuild = g_pGuildZone[i].ChargeGuild;
		int ChallangeGuild = g_pGuildZone[i].ChallangeGuild;

		if (ChallangeGuild == 0)
			continue;

		char GuildChargeName[256];
		char GuildChallangeName[256];

		BASE_GetGuildName(ServerGroup, g_pGuildZone[i].ChargeGuild, GuildChargeName);
		BASE_GetGuildName(ServerGroup, ChallangeGuild, GuildChallangeName);

		for (int j = g_pGuildZone[i].WarAreaY1; j <= g_pGuildZone[i].WarAreaY2; j++)
		{
			for (int k = g_pGuildZone[i].WarAreaX1; k <= g_pGuildZone[i].WarAreaX2; k++)
			{
				if (j < 0 || j >= MAX_GRIDY || k < 0 || k >= MAX_GRIDX)
					continue;

				int tmob = pMobGrid[j][k];

				if (tmob <= 0 || tmob >= MAX_USER)
					continue;

				if (pUser[tmob].Mode != USER_PLAY)
					continue;

				if (pMob[tmob].Mode == MOB_EMPTY)
					continue;

				if (pMob[tmob].MOB.CurrentScore.Hp <= 0)
					continue;

				int Guild = pMob[tmob].MOB.Guild;
				int Level = pMob[tmob].Extra.ClassMaster != MORTAL && pMob[tmob].Extra.ClassMaster != MORTAL ? pMob[tmob].MOB.CurrentScore.Level + MAX_LEVEL : pMob[tmob].MOB.CurrentScore.Level;

				if (Guild == 0)
					continue;

				if (Guild == ChargeGuild || Guild == ChallangeGuild)
				{
					sprintf(temp, "sys,guild war survive %s(%d-%d)", pMob[tmob].MOB.MobName, Guild, Level);
					Log(temp, "-system", 0);

					if (Guild == ChargeGuild)
						ChargeSurvivor += Level;

					else if (Guild == ChallangeGuild)
						ChallangeSurvivor += Level;

					else
						Log("err, more than 3 guild, at same guild zone", "-system", 0);
				}
			}
		}

		sprintf(temp, "sys,guild war %d result %d(%d) %d(%d)", i, ChargeGuild, ChargeSurvivor, ChallangeGuild, ChallangeSurvivor);
		Log(temp, "-system", 0);

		if (ChargeSurvivor < ChallangeSurvivor)
		{
			sprintf(temp, g_pMessageStringTable[_SSNN_GuildWarResult], GuildChallangeName, GuildChargeName, ChallangeSurvivor, ChargeSurvivor);
			SendGuildNotice(ChargeGuild, temp);
			SendGuildNotice(ChallangeGuild, temp);

			g_pGuildZone[i].ChargeGuild = ChallangeGuild;
			g_pGuildZone[i].Victory = 0;
		}
		else
		{
			sprintf(temp, g_pMessageStringTable[_SSNN_GuildWarResult], GuildChargeName, GuildChallangeName, ChargeSurvivor, ChallangeSurvivor);
			SendGuildNotice(ChargeGuild, temp);
			SendGuildNotice(ChallangeGuild, temp);

			if (g_pGuildZone[i].Victory < 4)
				g_pGuildZone[i].Victory++;
		}

		g_pGuildZone[i].ChallangeGuild = 0;
	}

	if (g_pGuildZone[1].ChargeGuild == g_pGuildZone[0].ChargeGuild && g_pGuildZone[2].ChargeGuild == g_pGuildZone[0].ChargeGuild && g_pGuildZone[3].ChargeGuild == g_pGuildZone[0].ChargeGuild)
		g_pGuildZone[4].ChargeGuild = g_pGuildZone[0].ChargeGuild;

	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].Mode == MOB_EMPTY)
			continue;

		if (pMob[i].MOB.Equip[0].sIndex == 219 ||
			strncmp(pMob[i].MOB.MobName, "Balmus", NAME_LENGTH) == 0 ||
			strncmp(pMob[i].MOB.MobName, "Bruce", NAME_LENGTH) == 0 ||
			strncmp(pMob[i].MOB.MobName, "Empis", NAME_LENGTH) == 0 ||
			strncmp(pMob[i].MOB.MobName, "Kara", NAME_LENGTH) == 0 )
			DeleteMob(i, 2);
	}
}

void ClearChallanger()
{
	for (int i = 0; i < ValidGuild; i++)
	{
		g_pGuildZone[i].ChallangeGuild = 0;
		pChallangerMoney[i] = 0;
	}
}

void SetArenaDoor(int state)
{
	for (int i = 0; i < ValidGuild; i++)
	{
		if (i == 4)
			continue;

		for (int j = 0; j < 3; j++)
		{
			int gate = 3 * i + j + 1;
			int height = 0;

			if (pItem[gate].ITEM.sIndex <= 0 || pItem[gate].ITEM.sIndex >= MAX_ITEMLIST)
				continue;

			if (pItem[gate].State == state)
				continue;

			UpdateItem(gate, state, &height);

			if (state == STATE_OPEN)
			{
				MSG_UpdateItem sm;
				memset(&sm, 0, sizeof(MSG_UpdateItem));

				sm.ID = ESCENE_FIELD;
				sm.Type = _MSG_UpdateItem;

				sm.ItemID = gate + 10000;

				sm.Size = sizeof(MSG_UpdateItem);

				//sm.Height = height;
				sm.State = pItem[gate].State;

				GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
			}
			else
			{
				MSG_CreateItem sm;
				memset(&sm, 0, sizeof(MSG_CreateItem));

				GetCreateItem(gate, &sm);

				GridMulticast(pItem[gate].PosX, pItem[gate].PosY, (MSG_STANDARD*)&sm, 0);
			}
			pItem[gate].Delay = 0;
		}
	}
}
