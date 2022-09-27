#include "WarOfKingdom.h"

void WarOfKingdom()
{
	time_t rawnow = time(NULL);
	struct tm* now = localtime(&rawnow);
	int minDefine = 5;
	if (warsTimer[eRvR].Days[now->tm_wday] > 1)
	{
		sprintf(temp, "warTimer.json,error config days %d [permitido 0 ou 1] ", warsTimer[eRvR].Days[now->tm_wday]);
		MyLog(LogType::System, "War RvR", temp, 0, 0);
	}

	// Inicia o RvR
	//if (/*now->tm_wday >= 1 && */ now->tm_wday == 6 /*&& NewbieEventServer*/)
	if (warsTimer[eRvR].Days[now->tm_wday])
	{
		int hourNotice = warsTimer[eRvR].Hour;
		int minNotice;

		//if (!warsTimer[eRvR].Minute)
			//minNotice = 60 - minDefine;
		if (warsTimer[eRvR].Minute < 5)
		{
			hourNotice = warsTimer[eRvR].Hour - 1;
			minNotice = (60 - minDefine) + warsTimer[eRvR].Minute;
		}
		else 
			minNotice = warsTimer[eRvR].Minute - minDefine;
		if (now->tm_hour == hourNotice && now->tm_min == minNotice && !g_pRvrWar.Annoucement)
		{
			sprintf(temp, g_pMessageStringTable[_DD_KINGDOMWAR_BEGIN], minDefine);
			SendNotice(temp);

			g_pRvrWar.Annoucement = 1;
		}
		else if (now->tm_hour == warsTimer[eRvR].Hour && now->tm_min == warsTimer[eRvR].Minute && !g_pRvrWar.Status)
		{
			g_pRvrWar.Status = 1;

			sprintf(temp, g_pMessageStringTable[_DD_KINGDOMWAR_START]);
			SendNotice(temp);

			GenerateMob(TORRE_RVR_BLUE, 0, 0);
			GenerateMob(TORRE_RVR_RED, 0, 0);

			
		}

		int minFinish = warsTimer[eRvR].Minute + 30;
		int hourFinish = warsTimer[eRvR].Hour;
		if (minFinish >= 60)
		{
			minFinish = minFinish - 60;
			hourFinish += 1;
		}
		if (hourFinish >= 24)
			hourFinish = 0;
		// Enviará uma mensagem para o servidor a cada 5 minutos a respeito dos pontos atuais
		else if (!(now->tm_min % 5) && g_pRvrWar.Status == 1 && !g_pRvrWar.Annoucement_Point/* && now->tm_hour == hourFinish && now->tm_min < minFinish */)
		{
			MSG_ChatColor sm_mt;
			memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

			sm_mt.Size = sizeof(MSG_ChatColor);
			sm_mt.ID = 0;
			sm_mt.Type = _MSG_MagicTrumpet;

			sm_mt.Color = TNColor::CornflowerBlue;

			//sprintf(sm_mt.Message, "Guerra entre Reinos");
			//DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));

			sprintf(sm_mt.Message, "Rvr Notice-> Red: %d - Blue: %d", g_pRvrWar.Points[1], g_pRvrWar.Points[0]);
			DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));

			g_pRvrWar.Annoucement_Point = 1;
		}
		else if (/*now->tm_hour == hourFinish && now->tm_min < minFinish && */(now->tm_min % 5) && g_pRvrWar.Annoucement_Point && g_pRvrWar.Status == 1)
			g_pRvrWar.Annoucement_Point = 0;

		else if (now->tm_hour >= hourFinish && now->tm_min >= minFinish && g_pRvrWar.Status == 1)
		{
			for (INT32 i = 1000; i < 30000; i++)
			{
				if (pMob[i].GenerateIndex == TORRE_RVR_BLUE || pMob[i].GenerateIndex == TORRE_RVR_RED)
					MobKilled(i, 29999, 0, 0);
			}

			sprintf(temp, g_pMessageStringTable[_DD_KINGDOMWAR_END]);
			SendNotice(temp);
			char* msgWinner = "Empate";
			int winner = 0;
			if (g_pRvrWar.Points[0] > g_pRvrWar.Points[1])
			{
				// Inserir o log que desejar
				//SendNotice("O reino blue foi o vencedora da Guerra entre Reinos");

				winner = 7;
				msgWinner = "BLUE";
			}
			else if (g_pRvrWar.Points[1] > g_pRvrWar.Points[0])
			{
				// Inserir o log que desejar
				//SendNotice("O reino red foi o vencedora da Guerra entre Reinos");

				winner = 8;
				msgWinner = "RED";
			}
			else
				winner = 0;

			sprintf(temp, g_pMessageStringTable[_SN_KINGDOMWAR_DROP_], msgWinner);
			SendNotice(temp);

			g_pRvrWar.Points[0] = 0;
			g_pRvrWar.Points[1] = 0;
			g_pRvrWar.Bonus = winner;

			g_pRvrWar.Status = 0;
			g_pRvrWar.Annoucement = 0;

			//ClearArea(1679, 1940, 1772, 2023);

			DeleteMob(TORRE_RVR_BLUE, 1);
			DeleteMob(TORRE_RVR_RED, 1);
			ClearMapa(RvrMapX, RvrMapY);

			MSG_STANDARDPARM sm;
			memset(&sm, 0, sizeof(MSG_STANDARDPARM));

			sm.Type = 0x899;
			sm.ID = 0;
			sm.Parm = winner;

			DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_STANDARDPARM));

			WriteRvrWinner();

			if (winner != 0)
			{
				for (int i = 1; i < MAX_USER; i++)
				{
					if (pUser[i].Mode != USER_PLAY)
						continue;

					if (pMob[i].MOB.Clan == winner)
					{
						pMob[i].Extra.Fame += 100;
						pMob[i].GetCurrentScore(i);
					}
				}
			}
		}
	}
}

void WarRandTower(int index)
{
	DWORD nRand = rand() % 4;

	if (index == TORRE_RVR_RED)
	{
		mNPCGen.pList[index].Leader.SPX = RandTorreRed[nRand][0];
		mNPCGen.pList[index].Leader.SPY = RandTorreRed[nRand][1];

		mNPCGen.pList[index].SegmentListX[0] = RandTorreRed[nRand][0];
		mNPCGen.pList[index].SegmentListY[0] = RandTorreRed[nRand][1];
	}
	else if (index == TORRE_RVR_BLUE)
	{
		mNPCGen.pList[index].Leader.SPX = RandTorreBlue[nRand][0];
		mNPCGen.pList[index].Leader.SPY = RandTorreBlue[nRand][1];

		mNPCGen.pList[index].SegmentListX[0] = RandTorreBlue[nRand][0];
		mNPCGen.pList[index].SegmentListY[0] = RandTorreBlue[nRand][1];
	}
	
}
