#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>
#include "..\Basedef.h"
#include "..\CPSock.h"
#include "..\ItemEffect.h"
#include "Language.h"
#include "CItem.h"
#include "Server.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "ProcessClientMessage.h"
#include "ProcessDBMessage.h"
#include "CReadFiles.h"
#include "WarOfTower.h"

void WarOfTower::Initialize()
{
	TowerCount = 0;
	TowerStage = 0;

	GuildTower = 0;
	GuildScore[MAX_GUILD] = { 0, };
	memset(&GuildScore, 0, sizeof GuildScore);
}


void WarOfTower::Clear()
{
	ClearArea(2445, 1850, 2546, 1920);
}

void WarOfTower::Tower(int a_iMob, int a_iGenerateIndex)
{
	if (a_iGenerateIndex == GTORRE && TowerStage)
	{
		if (GuildTower < 0) { GuildTower = 0; }

		pMob[a_iMob].MOB.Guild = GuildTower;
		pMob[a_iMob].MOB.GuildLevel = 0;
	}
}


bool WarOfTower::AttackTower(int a_iMob, int a_iTarget)
{
	if (pMob[a_iTarget].GenerateIndex != GTORRE) return true;

	if (pMob[a_iMob].MOB.Guild == 0 || pMob[a_iMob].MOB.Guild == pMob[a_iTarget].MOB.Guild) return false;

	return true;
}

void WarOfTower::KilledTower(int a_iConn, int a_iTarget, int a_iPosX, int a_iPosY)
{
	if (TowerStage)
	{
		int TowerId = pMob[a_iConn].GenerateIndex;

		if (TowerId == GTORRE)
		{
			int Guild = pMob[a_iTarget].MOB.Guild;

			if (Guild)
			{
				int Groups = ServerGroup;
				int Server = Guild / MAX_GUILD;

				char Name[256];

				BASE_GetGuildName(Groups, Guild, Name);

				sprintf(temp, "Guilda [%s] avançou no território da batalha.", Name);
				SendNotice(temp);

				if (GuildTower && GuildTower != Guild)
				{
					GuildScore[GuildTower] -= 10;

					if (GuildScore[GuildTower] < 0) 
					{ 
						GuildScore[GuildTower] = 0; 
					}
				}

				GuildScore[Guild] += 10;

				GuildTower = Guild;

				for (int i = 1; i < MAX_USER; i++)
				{
					if (pMob[i].MOB.Guild == GuildTower)
					{
						sprintf(temp, "Sua Guilda agora está com [%d] ponto(s).", GuildScore[Guild]);
					//	SendMsgExp(a_iTarget, temp, TNColor::Goldenrod, false);

					}
				}
			}

			Clear();

			GenerateMob(GTORRE, 0, 0);

			return;
		}

		if (a_iConn < MAX_USER && a_iTarget < MAX_USER)
		{
			int MinPosX = 2450, MinPosY = 1852, MaxPosX = 2543, MaxPosY = 1921;

			auto X = pMob[a_iConn].TargetX;
			auto Y = pMob[a_iConn].TargetY;

			if (X < MinPosX || X > MaxPosX || Y < MinPosY || Y > MaxPosY) return;

			int Guild = pMob[a_iTarget].MOB.Guild;

			if (Guild && pMob[a_iConn].MOB.Guild != Guild)
			{
				if (GuildScore[Guild] < 0) { GuildScore[Guild] = 0; }

				GuildScore[Guild]++;
			}

			Guild = pMob[a_iConn].MOB.Guild;

			if (Guild)
			{
				GuildScore[Guild]--;

				if (GuildScore[Guild] < 0) { GuildScore[Guild] = 0; }
			}

			//sprintf(temp, "Você matou [%s], Guild está com: %d pontos, Guild adversária está com: %d pontos.", pMob[a_iConn].MOB.MobName, GuildScore[pMob[a_iTarget].MOB.Guild], GuildScore[pMob[a_iConn].MOB.Guild]);
			//SendSpkMsg(a_iTarget, temp, TNColor::Goldenrod, false);

			sprintf(temp, "Target: [%s]   Guild Points: %d:   Opponent Points: %d.", pMob[a_iConn].MOB.MobName, GuildScore[pMob[a_iTarget].MOB.Guild], GuildScore[pMob[a_iConn].MOB.Guild]);
			//SendMsgExp(a_iTarget, temp, TNColor::GreenYellow, false);

		}
	}
}

void WarOfTower::CreateTower(int index, int tmob)
{
	if (index == GTORRE && GuildTower)
	{
		pMob[tmob].MOB.Guild = GuildTower;
		pMob[tmob].MOB.GuildLevel = 0;
	}
}

void WarOfTower::StandByProcess()
{
	struct tm zone;
	time_t now;
	time(&now);
	int minDefine = 5;
	zone = *localtime(&now);

	if (warsTimer[eTower].Days[zone.tm_wday] > 1)
	{
		sprintf(temp, "warTimer.json,error config days %d [permitido 0 ou 1] ", warsTimer[eTower].Days[zone.tm_wday]);
		MyLog(LogType::System, "War Tower", temp, 0, 0);
	}
	//if (zone.tm_wday != 0 && zone.tm_wday != 6)
	if (warsTimer[eTower].Days[zone.tm_wday])
	{
		int hourNotice = warsTimer[eTower].Hour;
		int minNotice;

		/*if (!warsTimer[eTower].Minute)
			minNotice = 60 - minDefine;*/
		if (warsTimer[eTower].Minute < 5)
		{
			hourNotice = warsTimer[eTower].Hour - 1;
			minNotice = (60 - minDefine) + warsTimer[eTower].Minute;
		}
		else
			minNotice = warsTimer[eTower].Minute - minDefine;

		//if (zone.tm_hour == 21 && zone.tm_min >= 55 && TowerStage == 0)
		if (zone.tm_hour == hourNotice && zone.tm_min == minNotice && TowerStage == 0)
		{
			Initialize();

			TowerStage = 1;

			sprintf(temp, g_pMessageStringTable[_DN_CHANNELWAR_BEGIN], minDefine);

			SendNotice(temp);

			return;
		}

		if (zone.tm_hour == warsTimer[eTower].Hour && zone.tm_min == warsTimer[eTower].Minute && TowerStage == 1)
		{
			TowerStage = 2;

			Clear();

			GenerateMob(GTORRE, 0, 0);

			SendNotice(g_pMessageStringTable[_DD__CHANNELWAR_START]);

			return;
		}

		if (TowerStage == 2 && GuildTower == 0)
		{
			TowerCount++;

			if (TowerCount % 200 == 0)
			{
				for (int i = MAX_USER; i < MAX_MOB; i++)
				{
					if (pMob[i].GenerateIndex == GTORRE)
					{
						Clear();

						pMob[i].MOB.CurrentScore.Damage += 1500;
						pMob[i].MOB.CurrentScore.Ac += 1500;

						pMob[i].MOB.CurrentScore.Hp = pMob[i].MOB.CurrentScore.MaxHp;

						SendScore(i);

						sprintf(temp, "[%s], agora está mais forte!", pMob[i].MOB.MobName);
						SendNotice(temp);

						break;
					}
				}
			}
		}
		else
		{
			TowerCount = 100;
		}
		int minFinish = warsTimer[eTower].Minute + 30;
		int hourFinish = warsTimer[eTower].Hour;
		if (minFinish > 30)
		{
			minFinish = 60 - warsTimer[eTower].Minute;
			hourFinish += 1;
		}
		if (hourFinish>=24)
			hourFinish = 00;

		if (zone.tm_hour == hourFinish && zone.tm_min >= minFinish && TowerStage == 2)
		{
			TowerStage = 3;

			Clear();

			int GuildOwn = -1;
			int GuildPtr = 0;

			for (int i = 0; i < MAX_GUILD; i++)
			{
				if (GuildScore[i] && GuildScore[i] > GuildPtr)
				{
					GuildOwn = i;

					GuildPtr = GuildScore[i];
				}
			}

			for (int i = MAX_USER; i < MAX_MOB; i++)
			{
				if (pMob[i].GenerateIndex == GTORRE)
				{
					if (pMob[i].MOB.Guild && pMob[i].MOB.Guild == GuildOwn)
					{
						GuildPtr += 10;
					}

					DeleteMob(i, 1);

					break;
				}
			}

			if (GuildOwn)
			{
				int Group = ServerGroup;
				int Server = GuildOwn / MAX_GUILD;

				char guildname[256];

				BASE_GetGuildName(Group, GuildOwn, guildname);

				MSG_GuildInfo sm;

				sm.Type = _MSG_GuildInfo;
				sm.Size = sizeof(MSG_GuildInfo);
				sm.ID = 0;

				int nPoint = GuildPtr;
				if (GuildPtr > 100) { GuildPtr = 100; }
				else
				{
					GuildPtr = 100;
				}

				sm.Guild = GuildOwn;
				GuildInfo[GuildOwn].Fame += GuildPtr;

				sm.GuildInfo = GuildInfo[GuildOwn];

				DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_GuildInfo));

				sprintf(temp, "etc,war_tower1 guild:%d guild_fame:%d", GuildOwn, GuildInfo[GuildOwn].Fame);
				Log(temp, "-system", 0);


				sprintf(temp, "A guilda [%s] foi a vencedora da Guerra de Canais com [%d] pontos.", guildname, nPoint);
				SendNotice(temp);
			}
			else
			{
				sprintf(temp, "Nenhuma Guild conseguiu ganhar a Guerra entre Canais.");
				SendNotice(temp);
			}

			return;
		}

		if (zone.tm_hour == hourFinish && zone.tm_min == (minFinish + 15) && TowerStage == 3)
		{
			TowerCount = 0;
			TowerStage = 0;
			
			for (int i = MAX_USER; i < MAX_MOB; i++)
			{
				if (pMob[i].GenerateIndex == GTORRE)
				{
				
					DeleteMob(i, 1);

				}
			}

			GuildScore[MAX_GUILD] = { 0, };
			memset(&GuildScore, 0, sizeof GuildScore);

		}
	}
}

