#include "BossCamp.h"

DWORD DropKillerBossCamp;
DWORD DropPartyBossCamp;
void WINAPI initBossCamp(unsigned char boss)
{
	time_t rawtime;
	tm* timeinfo;
	unsigned char isHourStart;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (bossCamp[boss].Days[timeinfo->tm_wday])
	{
		isHourStart = FALSE;
		if ((timeinfo->tm_hour > statusBossCamp[boss].HourKiled  || 
			timeinfo->tm_wday != statusBossCamp[boss].DayKiled) && 
			statusBossCamp[boss].aLive)
		{
			statusBossCamp[boss].aLive = 0;
			statusBossCamp[boss].PlayerKiled = "NINGUEM";
			statusBossCamp[boss].DayKiled = 0;
			statusBossCamp[boss].HourKiled = 0;
			statusBossCamp[boss].MinKiled = 0;

			WriteBossCamp(boss);
		}
		for (size_t i = 0; i < 5; i++)
		{
			if (timeinfo->tm_hour == bossCamp[boss].StartHour[i])
			{
				isHourStart = TRUE;
				break;
			}
		}

		if (isHourStart && !statusBossCamp[boss].aLive && !bossCamp[boss].spawned)
			startBossCamp(boss);

	}
}

void startBossCamp(unsigned char boss)
{
	srand(time(NULL));
	DWORD randXY;
	randXY = rand() % 4;
	checkBossCamp(boss);
	sprintf(msgTemp, bossCamp[boss].NoticeStart.c_str());
	SendNotice(msgTemp);
	GenerateMob(bossCamp[boss].Boss.ID, locationBossCamp[boss][randXY][0], locationBossCamp[boss][randXY][1]);
	//CreateMob("Freak", bossCamp[boss].Boss.StartX, bossCamp[boss].Boss.StartY, "npc", 0);
	bossCamp[boss].spawned = TRUE;
	bossCamp[boss].hp50 = FALSE;
	bossCamp[boss].hp10 = FALSE;
}

void checkBossCamp(unsigned char boss)
{
	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].GenerateIndex == bossCamp[boss].Boss.ID)
			DeleteMob(i, 1);
	
	}

	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].GenerateIndex == bossCamp[boss].Guardian.ID)
			DeleteMob(i, 1);
	}
}

void genBossCamp(int index, unsigned char boss)
{
	
	mNPCGen.pList[index].Leader.Equip[0] =						bossCamp[boss].Boss.FACE;
	mNPCGen.pList[index].Leader.Equip[1] =						bossCamp[boss].Boss.HELM;
	mNPCGen.pList[index].Leader.Equip[2] =						bossCamp[boss].Boss.BODY;
	mNPCGen.pList[index].Leader.Equip[3] =						bossCamp[boss].Boss.LEG;
	mNPCGen.pList[index].Leader.Equip[4] =						bossCamp[boss].Boss.GLOVE;
	mNPCGen.pList[index].Leader.Equip[5] =						bossCamp[boss].Boss.BOOT;
	mNPCGen.pList[index].Leader.Equip[6] =						bossCamp[boss].Boss.WEAPON;
	mNPCGen.pList[index].Leader.Equip[7] =						bossCamp[boss].Boss.SHIELD;
	mNPCGen.pList[index].Leader.Equip[13] =						bossCamp[boss].Boss.PIXIE;

	mNPCGen.pList[index].Leader.SPX =							bossCamp[boss].Boss.StartX;
	mNPCGen.pList[index].Leader.SPY =							bossCamp[boss].Boss.StartY;

	mNPCGen.pList[index].SegmentListX[0] =						bossCamp[boss].Boss.DestX;
	mNPCGen.pList[index].SegmentListY[0] =						bossCamp[boss].Boss.DestY;

	mNPCGen.pList[index].Leader.CurrentScore.Direction =		bossCamp[boss].Boss.REGEN;
	mNPCGen.pList[index].Leader.CurrentScore.Level =			bossCamp[boss].Boss.LEVEL;
	mNPCGen.pList[index].Leader.CurrentScore.MaxHp =			bossCamp[boss].Boss.HP;
	mNPCGen.pList[index].Leader.CurrentScore.Hp =				bossCamp[boss].Boss.HP;
	mNPCGen.pList[index].Leader.CurrentScore.MaxMp =			bossCamp[boss].Boss.MP;
	mNPCGen.pList[index].Leader.CurrentScore.Mp =				bossCamp[boss].Boss.MP;
	mNPCGen.pList[index].Leader.CurrentScore.Ac =				bossCamp[boss].Boss.AC;
	mNPCGen.pList[index].Leader.CurrentScore.Damage =			bossCamp[boss].Boss.DAN;
	mNPCGen.pList[index].Leader.Magic =							bossCamp[boss].Boss.MAGI;
	mNPCGen.pList[index].Leader.CurrentScore.Str =				bossCamp[boss].Boss.STR;
	mNPCGen.pList[index].Leader.CurrentScore.Int =				bossCamp[boss].Boss.INT;
	mNPCGen.pList[index].Leader.CurrentScore.Dex =				bossCamp[boss].Boss.DEX;
	mNPCGen.pList[index].Leader.CurrentScore.Con =				bossCamp[boss].Boss.CON;

	strcpy(&mNPCGen.pList[index].SegmentAction[0][80], bossCamp[boss].Boss.MSG1.c_str());
	strcpy(&mNPCGen.pList[index].SegmentAction[1][80], bossCamp[boss].Boss.MSG2.c_str());
	strcpy(&mNPCGen.pList[index].SegmentAction[2][80], bossCamp[boss].Boss.MSG3.c_str());

}

void genGuardianBossCamp(int index, unsigned char boss)
{
	mNPCGen.pList[index].Leader.Equip[0] = bossCamp[boss].Guardian.FACE;
	mNPCGen.pList[index].Leader.Equip[1] = bossCamp[boss].Guardian.HELM;
	mNPCGen.pList[index].Leader.Equip[2] = bossCamp[boss].Guardian.BODY;
	mNPCGen.pList[index].Leader.Equip[3] = bossCamp[boss].Guardian.LEG;
	mNPCGen.pList[index].Leader.Equip[4] = bossCamp[boss].Guardian.GLOVE;
	mNPCGen.pList[index].Leader.Equip[5] = bossCamp[boss].Guardian.BOOT;
	mNPCGen.pList[index].Leader.Equip[6] = bossCamp[boss].Guardian.WEAPON;
	mNPCGen.pList[index].Leader.Equip[7] = bossCamp[boss].Guardian.SHIELD;
	mNPCGen.pList[index].Leader.Equip[13] = bossCamp[boss].Guardian.PIXIE;

	for (size_t i = MAX_USER; i < MAX_MOB; i++)
	{
		if (!strcmp(pMob[i].MOB.MobName, bossCamp[boss].Boss.NAME.c_str()))
		{
			mNPCGen.pList[index].Leader.SPX = pMob[i].TargetX;
			mNPCGen.pList[index].Leader.SPY = pMob[i].TargetY;

			mNPCGen.pList[index].SegmentListX[0] = pMob[i].TargetX;
			mNPCGen.pList[index].SegmentListY[0] = pMob[i].TargetY;

		}
	}

	mNPCGen.pList[index].Leader.CurrentScore.Direction = bossCamp[boss].Guardian.REGEN;
	mNPCGen.pList[index].Leader.CurrentScore.Level = bossCamp[boss].Guardian.LEVEL;
	mNPCGen.pList[index].Leader.CurrentScore.MaxHp = bossCamp[boss].Guardian.HP;
	mNPCGen.pList[index].Leader.CurrentScore.Hp = bossCamp[boss].Guardian.HP;
	mNPCGen.pList[index].Leader.CurrentScore.MaxMp = bossCamp[boss].Guardian.MP;
	mNPCGen.pList[index].Leader.CurrentScore.Mp = bossCamp[boss].Guardian.MP;
	mNPCGen.pList[index].Leader.CurrentScore.Ac = bossCamp[boss].Guardian.AC;
	mNPCGen.pList[index].Leader.CurrentScore.Damage = bossCamp[boss].Guardian.DAN;
	mNPCGen.pList[index].Leader.Magic = bossCamp[boss].Guardian.MAGI;
	mNPCGen.pList[index].Leader.CurrentScore.Str = bossCamp[boss].Guardian.STR;
	mNPCGen.pList[index].Leader.CurrentScore.Int = bossCamp[boss].Guardian.INT;
	mNPCGen.pList[index].Leader.CurrentScore.Dex = bossCamp[boss].Guardian.DEX;
	mNPCGen.pList[index].Leader.CurrentScore.Con = bossCamp[boss].Guardian.CON;

	strcpy(&mNPCGen.pList[index].SegmentAction[0][80], bossCamp[boss].Guardian.MSG1.c_str());
	strcpy(&mNPCGen.pList[index].SegmentAction[1][80], bossCamp[boss].Guardian.MSG2.c_str());
	strcpy(&mNPCGen.pList[index].SegmentAction[2][80], bossCamp[boss].Guardian.MSG3.c_str());

	mNPCGen.pList[index].MaxNumMob = bossCamp[boss].numGuardian;
}

void checkHPBossCamp(int idx, unsigned char boss)
{
	int maxHP = pMob[idx].MOB.CurrentScore.MaxHp;
	int HP = pMob[idx].MOB.CurrentScore.Hp;
	int hp50 = 0.5 * maxHP;
	int hp10 = 0.1 * maxHP;

	 if (HP <= hp50 && !bossCamp[boss].hp50)
	{
		 bossCamp[boss].hp50 = TRUE;
		 bossCamp[boss].numGuardian = 2;

		for (size_t i = 0; i < bossCamp[boss].numGuardian; i++)
		{
			GenerateMob(bossCamp[boss].Guardian.ID, 0, 0);
			int sAffect = 0;
			switch (i)
			{
				
			case 0://Saúde
				sAffect = GetEmptyAffect(i, 35);
				pMob[idx].Affect[sAffect].Type = 35;
				pMob[idx].Affect[sAffect].Level = 1;
				pMob[idx].Affect[sAffect].Value = 0;
				pMob[idx].Affect[sAffect].Time = AFFECT_1H;
				break;
			case 1://Trovão
				sAffect = GetEmptyAffect(i, 22);
				pMob[idx].Affect[sAffect].Type = 22;
				pMob[idx].Affect[sAffect].Level = 1;
				pMob[idx].Affect[sAffect].Value = 0;
				pMob[idx].Affect[sAffect].Time = AFFECT_1H;
				break;
			default:
				break;
			}
			
			
		}
		pMob[idx].GetCurrentScore(idx);
		SendScore(idx);
		SendSay(idx, "Kage bunshin no jutsu!!!!");
	}

	else if (HP <= hp10 && !bossCamp[boss].hp10)
	{
		 bossCamp[boss].hp10 = TRUE;
		 bossCamp[boss].numGuardian = 4;

		for (size_t i = 0; i < bossCamp[boss].numGuardian; i++)
		{
			GenerateMob(bossCamp[boss].Guardian.ID, 0, 0);
			int sAffect = 0;
			switch (i)
			{
				
			case 0://Saúde
				sAffect = GetEmptyAffect(i, 35);
				pMob[idx].Affect[sAffect].Type = 35;
				pMob[idx].Affect[sAffect].Level = 1;
				pMob[idx].Affect[sAffect].Value = 0;
				pMob[idx].Affect[sAffect].Time = AFFECT_1H;
				break;
			case 1://Trovão
				sAffect = GetEmptyAffect(i, 22);
				pMob[idx].Affect[sAffect].Type = 22;
				pMob[idx].Affect[sAffect].Level = 1;
				pMob[idx].Affect[sAffect].Value = 0;
				pMob[idx].Affect[sAffect].Time = AFFECT_1H;
				break;
			case 2://Aura de Vida
				sAffect = GetEmptyAffect(i, 17);
				pMob[idx].Affect[sAffect].Type = 17;
				pMob[idx].Affect[sAffect].Level = 1;
				pMob[idx].Affect[sAffect].Value = 0;
				pMob[idx].Affect[sAffect].Time = AFFECT_1H;
				break;
			case 3://Aura Bestial
				sAffect = GetEmptyAffect(i, 23);
				pMob[idx].Affect[sAffect].Type = 23;
				pMob[idx].Affect[sAffect].Level = 1;
				pMob[idx].Affect[sAffect].Value = 0;
				pMob[idx].Affect[sAffect].Time = AFFECT_1H;
				break;
			default:
				break;
			}


		}
		//pMob[idx].GetCurrentScore(idx);
		//SendScore(idx);
		SendSay(idx, "Kage bunshin no jutsu!!!!");
	}
}

void guardianBossCampKilled(unsigned char boss)
{
	for (size_t i = MAX_USER; i < MAX_MOB; i++)
	{
		if (!strcmp(pMob[i].MOB.MobName, bossCamp[boss].Boss.NAME.c_str()))
		{
			unsigned int typeBuff = 35;
			int sAffect = GetEmptyAffect(i, typeBuff);

			if (sAffect == -1)
			{
				typeBuff = 22;
				sAffect = GetEmptyAffect(i, typeBuff);
			}

			if (sAffect == -1)
			{
				typeBuff = 17;
				sAffect = GetEmptyAffect(i, typeBuff);
			}

			if (sAffect == -1)
			{
				typeBuff = 23;
				sAffect = GetEmptyAffect(i, typeBuff);
			}

			if (pMob[i].Affect[sAffect].Type == typeBuff)
			{
				pMob[i].Affect[sAffect].Type = 0;
				pMob[i].Affect[sAffect].Level = 0;
				pMob[i].Affect[sAffect].Time = 0;
				pMob[i].Affect[sAffect].Value = 0;
			}
		//	pMob[i].GetCurrentScore(i);
			SendScore(i);
		}
	}
}

void BossCampKilled(int a_iConn, unsigned char boss)
{
	
	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].GenerateIndex == bossCamp[boss].Guardian.ID)
		{
			DeleteMob(i, 1);
		}
	}

	if (pUser[a_iConn].Mode != USER_PLAY)
		return;

	randDropBossCamp();

	STRUCT_ITEM* drop = &bossCamp[boss].Drop[DropKillerBossCamp];

	PutItem(a_iConn, drop);
	sprintf(msgTemp, "!Você recebeu [%s] como recompensa por Matar [%s]!", g_pItemList[drop->sIndex].Name, bossCamp[boss].Boss.NAME.c_str());
	SendClientMsg(a_iConn, msgTemp);

	int partyleader = pMob[a_iConn].Leader;

	if (partyleader <= 0)
		partyleader = a_iConn;

	if (partyleader != a_iConn)
	{
		randDropBossCamp();

		STRUCT_ITEM* drop = &bossCamp[boss].Drop[DropPartyBossCamp];

		PutItem(partyleader, drop);
		sprintf(msgTemp, "!Você recebeu [%s] como recompensa por Ajudar a matar [%s]!", g_pItemList[drop->sIndex].Name, bossCamp[boss].Boss.NAME.c_str());
		SendClientMsg(partyleader, msgTemp);
	}


	for (size_t i = 0; i < MAX_PARTY; i++)
	{
		randDropBossCamp();

		int partymember = pMob[partyleader].PartyList[i];

		
		if (partymember >= MAX_USER)
			continue;


		if (pUser[partymember].Mode != USER_PLAY)
			continue;

		if (partymember == a_iConn)
			continue;


		//drop random  do grupo que matou o Boss
		if (pMob[partymember].TargetX >= pMob[a_iConn].TargetX - 20 && (pMob[partymember].TargetX <= pMob[a_iConn].TargetX + 20)
			&& (pMob[partymember].TargetY >= pMob[a_iConn].TargetY - 20 && pMob[partymember].TargetY <= pMob[a_iConn].TargetY + 20))
		{
			
			STRUCT_ITEM* drop = &bossCamp[boss].DropParty[DropPartyBossCamp];
			PutItem(partymember, drop);
			sprintf(msgTemp, "!Você recebeu [%s] como recompensa por ajudar a matar [%s]!", g_pItemList[drop->sIndex].Name, bossCamp[boss].Boss.NAME.c_str());
			SendClientMsg(partymember, msgTemp);

		}

	}

	time_t rawtime;
	tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	statusBossCamp[boss].aLive = 1;
	statusBossCamp[boss].PlayerKiled = pMob[a_iConn].MOB.MobName;
	statusBossCamp[boss].DayKiled = timeinfo->tm_wday;
	statusBossCamp[boss].HourKiled = timeinfo->tm_hour;
	statusBossCamp[boss].MinKiled = timeinfo->tm_min;

	WriteBossCamp(boss);

	sprintf(msgTemp, bossCamp[boss].NoticeEnd.c_str(), pMob[a_iConn].MOB.MobName);
	SendNotice(msgTemp);
}


void randDropBossCamp()
{
	DWORD nRand;
	DWORD hand1 = 49;
	DWORD hand2 = 70;
	DWORD hand3 = 85;
	DWORD hand4 = 94;
	DWORD hand5 = 98;
	DWORD hand6 = 99;

	//rand Drop Killer
	//srand(time(NULL));
	nRand = rand() % 100;
	if (nRand <= hand1)
		DropKillerBossCamp = 0;

	else if (nRand <= hand2)
		DropKillerBossCamp = 1;

	else if (nRand <= hand3)
		DropKillerBossCamp = 2;

	else if (nRand <= hand4)
		DropKillerBossCamp = 3;

	else if (nRand <= hand5)
		DropKillerBossCamp = 4;

	else if (nRand == hand6)
		DropKillerBossCamp = 5;


	//Rand Drop Party
	//srand(time(NULL));
	nRand = rand() % 100;
	if (nRand <= hand1)
		DropPartyBossCamp = 0;

	else if (nRand <= hand2)
		DropPartyBossCamp = 1;

	else if (nRand <= hand3)
		DropPartyBossCamp = 2;

	else if (nRand <= hand4)
		DropPartyBossCamp = 3;

	else if (nRand <= hand5)
		DropPartyBossCamp = 4;

	else if (nRand == hand6)
		DropPartyBossCamp = 5;
}
