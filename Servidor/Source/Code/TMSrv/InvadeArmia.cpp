#include "InvadeArmia.h"
#include "FadaDourada.h"

BOOL invadArmiaStart = FALSE;
BOOL invadArmiaNotice = FALSE;
short unsigned waveStart = 0;
unsigned InvadeArmiaMobCount = 0;
int invadArmiaTime = INVADE_ARMIA.Time;
BOOL invadArmiaEnd = FALSE;

void WINAPI StartInvadeArmia()
{
	time_t rawtime;
	tm* timeinfo;
	time(&rawtime);
	int minDefine = 5;
	timeinfo = localtime(&rawtime);

	if (timeinfo->tm_wday == INVADE_ARMIA.nDay)
	{
		int hourNotice = INVADE_ARMIA.nHour;
		int minNotice = 0;

		//if (!warsTimer[eRvR].Minute)
			//minNotice = 60 - minDefine;
		if (INVADE_ARMIA.nMin < 5)
		{
			hourNotice -= 1;
			minNotice = 60 - minDefine + INVADE_ARMIA.nMin;
		}
		else
			minNotice = INVADE_ARMIA.nMin - minDefine;

		if ((timeinfo->tm_hour >= hourNotice && timeinfo->tm_min >= minNotice
			&& !invadArmiaStart && !invadArmiaNotice))
		{
			invadArmiaNotice = TRUE;
			int minRestant = INVADE_ARMIA.nMin - timeinfo->tm_min;
			if (minRestant > 0)
			{
				sprintf(temp, "![Evento] Invasão de armia irá começar em [%d] min(s)", minRestant);
				SendNotice(temp);
			}
			
		}
		
		if (timeinfo->tm_hour == INVADE_ARMIA.nHour && timeinfo->tm_min >= INVADE_ARMIA.nMin
			&& !invadArmiaStart && !invadArmiaEnd)
		{
			invadArmiaStart = TRUE;
			sprintf(temp, "![Evento] Invasão de armia começou [%d]hrs [%d]min(s)", timeinfo->tm_hour, timeinfo->tm_min);
			SendNotice(temp);
			InvadeArmiaStartWave(waveStart);
		}
	}
}

void InvadeArmiaStartWave(int nWave)
{
	short unsigned waveCount = nWave + 1;
	MSG_ChatColor sm_mt;
	memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

	sm_mt.Size = sizeof(MSG_ChatColor);
	sm_mt.ID = 0;
	sm_mt.Type = _MSG_MagicTrumpet;

	sm_mt.Color = TNColor::Yellow;

	sprintf(sm_mt.Message, "Invasao de Armia-> A [%dª] wave de invasores foi liberada na coordenada X(%d) - Y(%d)", 
		waveCount, INVADE_ARMIA.StartX, INVADE_ARMIA.StartY);

	DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));

	for (size_t i = 0; i < INVADE_ARMIA.Group; i++)
	{
		GenerateMob(INVADE_ARMIA.ID[nWave], INVADE_ARMIA.StartX, INVADE_ARMIA.StartY);
	}
	
	
}

void InvadeArmiaWaveKilled(int nMob)
{
	/*short unsigned waveCount = nWave + 1;
	MSG_ChatColor sm_mt;
	memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

	sm_mt.Size = sizeof(MSG_ChatColor);
	sm_mt.ID = 0;
	sm_mt.Type = _MSG_MagicTrumpet;

	sm_mt.Color = TNColor::Green;

	sprintf(sm_mt.Message, "Invasao de Armia-> A [%dª] wave de invasores foi eliminada", waveCount);

	DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));*/
	
	waveStart += 1;

	if (waveStart < 7)
		InvadeArmiaStartWave(waveStart);
	else
		InvadeArmiaStartBoss();
}

void InvadeArmiaDropMob(int conn)
{
	unsigned int nRand = rand() % 100;
	unsigned int nRate = 100;

	for (size_t i = 0; i < INVADE_ARMIA.Rate.size(); i++)
	{
		if (nRand <= INVADE_ARMIA.Rate[i])
		{
			nRate = i;
			break;
		}
	}

	if (nRate == 100)
		return;

	STRUCT_ITEM ndrop;
	memset(&ndrop, 0, sizeof(STRUCT_ITEM));

	ndrop.sIndex = INVADE_ARMIA.Drop[nRate];

	BOOL isFadaAmmount = FALSE;
	BOOL isReward = FALSE;
	for (size_t i = 0; i < sizeof(fadaAmmount); i++)
	{
		if (ndrop.sIndex == fadaAmmount[i])
		{
			isFadaAmmount = TRUE;
			break;
		}
	}

	if (isFadaAmmount)
	{
		
		isReward = AutoAmmount(conn, &ndrop);

		if (!isReward)
			isReward = PutItem(conn, &ndrop);
	}
	
	if (isReward)
	{
		sprintf(temp, "Adquiriu [%s]", g_pItemList[ndrop.sIndex].Name);
		SendMsgExp(conn, temp, TNColor::GoldenClaro, false);
	}

}

void InvadeArmiaStartBoss()
{
	MSG_ChatColor sm_mt;
	memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

	sm_mt.Size = sizeof(MSG_ChatColor);
	sm_mt.ID = 0;
	sm_mt.Type = _MSG_MagicTrumpet;

	sm_mt.Color = TNColor::GoldenEscuro;

	sprintf(sm_mt.Message, "Invasao de Armia-> O Boss apareceu na coordenada X(%d) - Y(%d)", INVADE_ARMIA.StartX, INVADE_ARMIA.StartY);

	DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));

	GenerateMob(INVADE_ARMIA.IDBoss, INVADE_ARMIA.StartX, INVADE_ARMIA.StartY);
}


void InvadeArmiaBossKilled(int nMob)
{
	invadArmiaStart = FALSE;
	invadArmiaEnd = TRUE;
}



void InvadeArmiaDropBoss(int conn, unsigned int cooX, unsigned int cooY)
{
	MSG_ChatColor sm_mt;
	memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

	sm_mt.Size = sizeof(MSG_ChatColor);
	sm_mt.ID = 0;
	sm_mt.Type = _MSG_MagicTrumpet;

	sm_mt.Color = TNColor::Green;
	STRUCT_ITEM itemKiller;
	memset(&itemKiller, 0, sizeof(STRUCT_ITEM));
	itemKiller.sIndex = 1741;
	sprintf(sm_mt.Message, "Invasão de Armia-> O Jogador [%s] Derrotou o Boss e ganhou [%s]", 
		pMob[conn].MOB.MobName, g_pItemList[itemKiller.sIndex].Name);

	DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));

	for (size_t i = 0; i < MAX_USER; i++)
	{
		unsigned int nRand = rand() % 100;
		unsigned int nRate = 0;

		if (pUser[i].Mode != USER_PLAY)
			continue;

		if (nRand <= INVADE_ARMIA.Rate[i])
		{
			nRate = i;
			break;
		}

		if (pMob[i].LastX >= cooX % 20 && pMob[i].LastX <= cooX % 20 
			&& pMob[i].LastY >= cooY % 20 && pMob[i].LastY <= cooY)
		{

		}
	}
}

void InvadeArmiaTimeNotice()
{
	if (invadArmiaTime > 0)
	{
		int timeMin = invadArmiaTime / 60;
		MSG_ChatColor sm_mt;
		memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

		sm_mt.Size = sizeof(MSG_ChatColor);
		sm_mt.ID = 0;
		sm_mt.Type = _MSG_MagicTrumpet;

		sm_mt.Color = TNColor::GreenYellow;

		sprintf(sm_mt.Message, "Faltam [%d]min(s) para terminar a invasão.", timeMin);

		DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));
	}
	else
	{
		sprintf(temp, "![Evento] Invasão de armia finalizado.");
		SendNotice(temp);
	}
	
}
