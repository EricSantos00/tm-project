#include "AltarOfKing.h"

void startKing()
{

	time_t rawtime;
	tm* timeinfo;
	int minDefine = 5;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	int checkMin;
	int priorHour;
	int hourNotice;
	int minNotice;
	int notHour = FALSE;
	size_t StartNum;
	if (altarKing.Days[timeinfo->tm_wday])
	{
		

		for ( StartNum = 0; StartNum < 3; StartNum++)
		{
			if (altarKing.Hour[StartNum] < timeinfo->tm_hour)
				continue;

			if (altarKing.Min[StartNum] < 5)
			{
				priorHour = altarKing.Hour[StartNum] - 1;
				//checkMin = (60 - minDefine) + altarKing.Min[StartNum];
			}
			else
				priorHour = altarKing.Hour[StartNum];

			if (altarKing.Hour[StartNum] == priorHour)
			{
				hourNotice = priorHour;
				//StartAltarKing = TRUE;
				notHour = FALSE;
				break;
			}
			else
			 notHour = TRUE;
			
		}

		if (notHour)
			return;

		if (!altarKing.Min[StartNum])
			minNotice = 60 - minDefine;

		hourNotice = altarKing.Hour[StartNum];
		if (altarKing.Min[StartNum] < 5)
		{
			hourNotice -= 1;
			minNotice = (60 - minDefine) + altarKing.Min[StartNum];
		}
		else
			minNotice = altarKing.Min[StartNum] - minDefine;


		if (timeinfo->tm_hour == hourNotice && timeinfo->tm_min >= minNotice 
			&& !altarKing.Notice && timeinfo->tm_min < altarKing.Min[StartNum])
		{
			int minRest = altarKing.Min[StartNum] - timeinfo->tm_min;
			altarKing.Notice = TRUE;

			sprintf(temp, "Evento Altar of King iniciará em[%d] min(s)", minRest);
			SendNotice(temp);
		}

		if (timeinfo->tm_hour == altarKing.Hour[StartNum] && timeinfo->tm_min >= altarKing.Min[StartNum]
			&& !StartAltarKing && altarKing.HourFinish != 1 << altarKing.Hour[StartNum])
		{
			StartAltarKing = TRUE;
			altarKing.Notice = FALSE;
			altarKing.HourFinish = 1 << altarKing.Hour[StartNum];
			altarKing.nTimer = altarKing.Duration;
			sprintf(temp, "Evento Altar of King Começou hr(s):[%d] min(s):[%d]", timeinfo->tm_hour, timeinfo->tm_min);
			SendNotice(temp);
			GenerateMob(altarKing.BossStatus.ID, 1106, 1731);
			clearKing();
		}
	}
	
}

void Winner(int conn)
{
	//int Guild = pMob[conn].MOB.Guild;
	StartAltarKing = FALSE;
	pUser[playerAltar].AltarStatus = 0;
	srand(time(NULL));
	int itemRand = rand() % 5;
	clearKing();
	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].GenerateIndex == altarKing.BossStatus.ID)
		{
			DeleteMob(i, 1);
			break;
		}
	}
	PutItem(conn, &altarKing.Rewards[itemRand]);
	sprintf(temp, "!Você recebeu [%s] como recompensa por conquistar o altar do Rei!", g_pItemList[altarKing.Rewards[itemRand].sIndex].Name);
	SendClientMsg(conn, temp);
	
}

void noWinner()
{
	StartAltarKing = FALSE;
	pUser[playerAltar].AltarStatus = 0;
	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].GenerateIndex == altarKing.BossStatus.ID)
		{
			DeleteMob(i, 1);
			break;
		}
	}
	clearKing();

}

void clearKing()
{
	ClearArea(1065, 1714, 1128, 1742);
}

void dominatorKing(int conn)
{
	if (conn > 0 && conn < MAX_USER && pMob[conn].MOB.CurrentScore.Hp > 0)
	{

		if (!StartAltarKing || pMob[conn].TargetX != 1106 || pMob[conn].TargetY != 1731)
		{
			pUser[conn].AltarStatus = 0;

			if (playerAltar == conn)
				playerAltar = 0;

			else
				SendClientSignalParm(conn, ESCENE_FIELD, _MSG_StartTime,
					pUser[playerAltar].AltarStatus);

		}

		else
		{
			
			if (pUser[conn].AltarStatus == 0)
				{
					playerAltar = conn;
					sprintf(temp, "O Jogador [%s] esta tentando dominar o Altar do Rei", pMob[conn].MOB.MobName);
					SendNotice(temp);

				}
				MSG_STANDARDPARM sm;
				memset(&sm, 0, sizeof(MSG_STANDARDPARM));

				sm.Type = _MSG_SendCastleState2;
				sm.Size = sizeof(MSG_STANDARDPARM);
				sm.ID = conn;
				sm.Parm = 1;

				GridMulticast(pMob[conn].TargetX, pMob[conn].TargetY, (MSG_STANDARD*)&sm, 0);

				SendClientSignalParm(conn, ESCENE_FIELD, _MSG_StartTime, pUser[conn].AltarStatus++);
				
				if (pUser[conn].AltarStatus >= altarKing.TimerAltar)//Dominou o Altar
				{
					sprintf(temp, "O Jogador [% s] dominou o Altar do Rei, Evento encerrado!!!", pMob[conn].MOB.MobName);
					SendNotice(temp);
					Sleep(2000);
					Winner(conn);

				}
			
		}
	}
}
