#include "SombraNegra.h"

DWORD DropKiller;
DWORD DropParty;
BOOL isDropKiller;
BOOL isDropParty;
void WINAPI initBoss()
{
	time_t rawtime;
	tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (bSombraNegra.Days[timeinfo->tm_wday])
	{
		if (timeinfo->tm_wday != statusSombraNegra.DayKiled && statusSombraNegra.aLive)
		{
			statusSombraNegra.aLive = 0;
			statusSombraNegra.PlayerKiled = "NINGUEM";
			statusSombraNegra.DayKiled = 0;
			statusSombraNegra.HourKiled = 0;
			statusSombraNegra.MinKiled = 0;

			WriteSombraNegra();
		}

		if (timeinfo->tm_hour >= bSombraNegra.StartHour && timeinfo->tm_hour < bSombraNegra.EndHour
			&& !statusSombraNegra.aLive && !bSombraNegra.spawned)
			startBoss();

		if (timeinfo->tm_hour >= bSombraNegra.EndHour && !statusSombraNegra.aLive && bSombraNegra.spawned)
			noKiller();
	
	}
}

void startBoss()
{
	checkBoss();
	sprintf(msgTemp, bSombraNegra.NoticeStart.c_str());
	SendNotice(msgTemp);
	GenerateMob(bSombraNegra.Boss.ID, 3810, 2882);
	bSombraNegra.spawned = TRUE;
	bSombraNegra.hp70 = FALSE;
	bSombraNegra.hp50 = FALSE;
	bSombraNegra.hp10 = FALSE;
}

void checkBoss()
{
	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].GenerateIndex == bSombraNegra.Boss.ID)
		{
			DeleteMob(i, 1);
			//break;
		}
	}

	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].GenerateIndex == bSombraNegra.Guardian.ID)
		{
			DeleteMob(i, 1);
		}
	}
}

void genSombraNegra(int index)
{
	mNPCGen.pList[index].Leader.Equip[0] = bSombraNegra.Boss.FACE;
	mNPCGen.pList[index].Leader.Equip[1] = bSombraNegra.Boss.HELM;
	mNPCGen.pList[index].Leader.Equip[2] = bSombraNegra.Boss.BODY;
	mNPCGen.pList[index].Leader.Equip[3] = bSombraNegra.Boss.LEG;
	mNPCGen.pList[index].Leader.Equip[4] = bSombraNegra.Boss.GLOVE;
	mNPCGen.pList[index].Leader.Equip[5] = bSombraNegra.Boss.BOOT;
	mNPCGen.pList[index].Leader.Equip[6] = bSombraNegra.Boss.WEAPON;
	mNPCGen.pList[index].Leader.Equip[7] = bSombraNegra.Boss.SHIELD;
	mNPCGen.pList[index].Leader.Equip[13] = bSombraNegra.Boss.PIXIE;

	mNPCGen.pList[index].Leader.SPX = bSombraNegra.Boss.StartX;
	mNPCGen.pList[index].Leader.SPY= bSombraNegra.Boss.StartY;

	mNPCGen.pList[index].SegmentListX[0] = bSombraNegra.Boss.DestX;
	mNPCGen.pList[index].SegmentListY[0] = bSombraNegra.Boss.DestY;

	mNPCGen.pList[index].Leader.CurrentScore.Direction = bSombraNegra.Boss.REGEN;
	mNPCGen.pList[index].Leader.CurrentScore.Level = bSombraNegra.Boss.LEVEL;
	mNPCGen.pList[index].Leader.CurrentScore.MaxHp = bSombraNegra.Boss.HP;
	mNPCGen.pList[index].Leader.CurrentScore.Hp = bSombraNegra.Boss.HP;
	mNPCGen.pList[index].Leader.CurrentScore.MaxMp = bSombraNegra.Boss.MP;
	mNPCGen.pList[index].Leader.CurrentScore.Mp = bSombraNegra.Boss.MP;
	mNPCGen.pList[index].Leader.CurrentScore.Ac = bSombraNegra.Boss.AC;
	mNPCGen.pList[index].Leader.CurrentScore.Damage = bSombraNegra.Boss.DAN;
	mNPCGen.pList[index].Leader.Magic = bSombraNegra.Boss.MAGI;
	mNPCGen.pList[index].Leader.CurrentScore.Str = bSombraNegra.Boss.STR;
	mNPCGen.pList[index].Leader.CurrentScore.Int = bSombraNegra.Boss.INT;
	mNPCGen.pList[index].Leader.CurrentScore.Dex = bSombraNegra.Boss.DEX;
	mNPCGen.pList[index].Leader.CurrentScore.Con = bSombraNegra.Boss.CON;

	strcpy(&mNPCGen.pList[index].SegmentAction[0][80], bSombraNegra.Boss.MSG1.c_str());
	strcpy(&mNPCGen.pList[index].SegmentAction[1][80], bSombraNegra.Boss.MSG2.c_str());
	strcpy(&mNPCGen.pList[index].SegmentAction[2][80], bSombraNegra.Boss.MSG3.c_str());


	//strcpy(&mNPCGen.pList[index].FightAction[0][80], bSombraNegra.Boss.MSG1.c_str());
}

void genGuardianSombraNegra(int index)
{
	mNPCGen.pList[index].Leader.Equip[0] = bSombraNegra.Guardian.FACE;
	mNPCGen.pList[index].Leader.Equip[1] = bSombraNegra.Guardian.HELM;
	mNPCGen.pList[index].Leader.Equip[2] = bSombraNegra.Guardian.BODY;
	mNPCGen.pList[index].Leader.Equip[3] = bSombraNegra.Guardian.LEG;
	mNPCGen.pList[index].Leader.Equip[4] = bSombraNegra.Guardian.GLOVE;
	mNPCGen.pList[index].Leader.Equip[5] = bSombraNegra.Guardian.BOOT;
	mNPCGen.pList[index].Leader.Equip[6] = bSombraNegra.Guardian.WEAPON;
	mNPCGen.pList[index].Leader.Equip[7] = bSombraNegra.Guardian.SHIELD;
	mNPCGen.pList[index].Leader.Equip[13] = bSombraNegra.Guardian.PIXIE;

	for (size_t i = MAX_USER; i < MAX_MOB; i++)
	{
		if (!strcmp(pMob[i].MOB.MobName, "Sombra Negra "))
		{
			mNPCGen.pList[index].Leader.SPX = pMob[i].TargetX;
			mNPCGen.pList[index].Leader.SPY = pMob[i].TargetY;

			mNPCGen.pList[index].SegmentListX[0] = pMob[i].TargetX;
			mNPCGen.pList[index].SegmentListY[0] = pMob[i].TargetY;

			pMob[i].MOB.CurrentScore.Ac += 1000 * bSombraNegra.numGuardian;

			for (size_t i = 0; i < 4; i++)
			{
				pMob[i].MOB.Resist[i] += 50 * bSombraNegra.numGuardian;
			}
			
		}
	}
	
	mNPCGen.pList[index].Leader.CurrentScore.Direction = bSombraNegra.Guardian.REGEN;
	mNPCGen.pList[index].Leader.CurrentScore.Level = bSombraNegra.Guardian.LEVEL;
	mNPCGen.pList[index].Leader.CurrentScore.MaxHp = bSombraNegra.Guardian.HP;
	mNPCGen.pList[index].Leader.CurrentScore.Hp = bSombraNegra.Guardian.HP;
	mNPCGen.pList[index].Leader.CurrentScore.MaxMp = bSombraNegra.Guardian.MP;
	mNPCGen.pList[index].Leader.CurrentScore.Mp = bSombraNegra.Guardian.MP;
	mNPCGen.pList[index].Leader.CurrentScore.Ac = bSombraNegra.Guardian.AC;
	mNPCGen.pList[index].Leader.CurrentScore.Damage = bSombraNegra.Guardian.DAN;
	mNPCGen.pList[index].Leader.Magic = bSombraNegra.Guardian.MAGI;
	mNPCGen.pList[index].Leader.CurrentScore.Str = bSombraNegra.Guardian.STR;
	mNPCGen.pList[index].Leader.CurrentScore.Int = bSombraNegra.Guardian.INT;
	mNPCGen.pList[index].Leader.CurrentScore.Dex = bSombraNegra.Guardian.DEX;
	mNPCGen.pList[index].Leader.CurrentScore.Con = bSombraNegra.Guardian.CON;

	strcpy(&mNPCGen.pList[index].SegmentAction[0][80], bSombraNegra.Guardian.MSG1.c_str());
	strcpy(&mNPCGen.pList[index].SegmentAction[1][80], bSombraNegra.Guardian.MSG2.c_str());
	strcpy(&mNPCGen.pList[index].SegmentAction[2][80], bSombraNegra.Guardian.MSG3.c_str());

	//mNPCGen.pList[index].MaxGroup = 10;
	mNPCGen.pList[index].MaxNumMob = bSombraNegra.numGuardian;
}

void checkHPBoss(int idx)
{
	int maxHP = pMob[idx].MOB.CurrentScore.MaxHp;
	int HP = pMob[idx].MOB.CurrentScore.Hp;
	int hp70 = 0.7 * maxHP;
	int hp50 = 0.5 * maxHP;
	int hp10 = 0.1 * maxHP;

	if (HP <= hp70 && !bSombraNegra.hp70)
	{
		bSombraNegra.hp70 = TRUE;
		bSombraNegra.numGuardian = 2;
		
		for (size_t i = 0; i < bSombraNegra.numGuardian; i++)
		{
			GenerateMob(bSombraNegra.Guardian.ID, 0, 0);
		}
		

		SendNoticeArea("Os Guardians apareceram!!", 3800, 2860, 3833, 2899);
	}
	else if (HP <= hp50 && !bSombraNegra.hp50)
	{
		bSombraNegra.hp50 = TRUE;
		bSombraNegra.numGuardian = 3;

		for (size_t i = 0; i < bSombraNegra.numGuardian; i++)
		{
			GenerateMob(bSombraNegra.Guardian.ID, 0, 0);
		}

		SendNoticeArea("Os Guardians apareceram!!", 3800, 2860, 3833, 2899);
	}

	else if (HP <= hp10 && !bSombraNegra.hp10)
	{
		bSombraNegra.hp10 = TRUE;
		bSombraNegra.numGuardian = 6;

		for (size_t i = 0; i < bSombraNegra.numGuardian; i++)
		{
			GenerateMob(bSombraNegra.Guardian.ID, 0, 0);
		}

		SendNoticeArea("Os Guardians apareceram!!", 3800, 2860, 3833, 2899);
	}
}

void guardianKilled()
{
	for (size_t i = MAX_USER; i < MAX_MOB; i++)
	{
		if (!strcmp(pMob[i].MOB.MobName, "Sombra Negra "))
		{
			pMob[i].MOB.CurrentScore.Ac -= 1000;

			for (size_t i = 0; i < 4; i++)
			{
				pMob[i].MOB.Resist[i] -= 50;
			}
		}
	}
}

void sombraNegraKilled(int a_iConn)
{
	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].GenerateIndex == bSombraNegra.Guardian.ID)
		{
			DeleteMob(i, 1);
		}
	}

	if (pUser[a_iConn].Mode != USER_PLAY)
		return;

	randDrop();

	//if (isDropKiller)
	//{
		STRUCT_ITEM* drop = &bSombraNegra.Drop[DropKiller];

		PutItem(a_iConn, drop);
		sprintf(msgTemp, "!Você recebeu [%s] como recompensa por Matar Sombra Negra!", g_pItemList[drop->sIndex].Name);
		SendClientMsg(a_iConn, msgTemp);
	//}

	int partyleader = pMob[a_iConn].Leader;

	if (partyleader <= 0)
		partyleader = a_iConn;

	if (partyleader != a_iConn)
	{
		randDrop();

		STRUCT_ITEM* drop = &bSombraNegra.Drop[DropParty];

		PutItem(partyleader, drop);
		sprintf(msgTemp, "!Você recebeu [%s] como recompensa por Ajudar a matar Sombra Negra!", g_pItemList[drop->sIndex].Name);
		SendClientMsg(partyleader, msgTemp);
		SendClientMsg(partyleader, msgTemp);
	}

	
	for (size_t i = 0; i < MAX_PARTY; i++)
	{
		randDrop();

		int partymember = pMob[partyleader].PartyList[i];

		if (partymember >= MAX_USER)
			continue;

		if (pUser[partymember].Mode != USER_PLAY)
			continue;

		//drop random  do grupo que matou Sombra Negra
		if (pMob[partymember].TargetX >= 3800 && (pMob[partymember].TargetX <= 3833)
			&& (pMob[partymember].TargetY >= 2860 && pMob[partymember].TargetY <= 2899))
		{
			//if (isDropParty)
			//{
				STRUCT_ITEM* drop = &bSombraNegra.DropParty[DropParty];
				PutItem(partymember, drop);
				sprintf(msgTemp, "!Você recebeu [%s] como recompensa por ajudar a matar Sombra Negra!", g_pItemList[drop->sIndex].Name);
				SendClientMsg(partymember, msgTemp);
			//}

		}

	}

	time_t rawtime;
	tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	statusSombraNegra.aLive = 1;
	statusSombraNegra.PlayerKiled = pMob[a_iConn].MOB.MobName;
	statusSombraNegra.DayKiled = timeinfo->tm_wday;
	statusSombraNegra.HourKiled = timeinfo->tm_hour;
	statusSombraNegra.MinKiled = timeinfo->tm_min;
	
	WriteSombraNegra();

	sprintf(msgTemp, bSombraNegra.NoticeEnd1.c_str(), pMob[a_iConn].MOB.MobName);
	SendNotice(msgTemp);
}

void randDrop()
{
	DWORD nRand;
	DWORD hand1 = 49;
	DWORD hand2 = 70;
	DWORD hand3 = 85;
	DWORD hand4 = 94;
	DWORD hand5 = 98;
	DWORD hand6 = 99;
	//DropKiller = rand() % 6; //item sorteado
	//DropParty = rand() % 6; //item sorteado
	
	//rand Drop Killer
	//srand(time(NULL));
		nRand = rand() % 100;
		if (nRand <= hand1)
			DropKiller = 0;
		
		else if (nRand <= hand2)
			DropKiller = 1;
		
		else if (nRand <= hand3)
			DropKiller = 2;
		
		else if (nRand <= hand4)
			DropKiller = 3;
	
		else if (nRand <= hand5)
			DropKiller = 4;

		else if (nRand == hand6)
			DropKiller = 5;
	

		//Rand Drop Party
		//srand(time(NULL));
		nRand = rand() % 100;
		if (nRand <= hand1)
			DropParty = 0;

		else if (nRand <= hand2)
			DropParty = 1;

		else if (nRand <= hand3)
			DropParty = 2;

		else if (nRand <= hand4)
			DropParty = 3;

		else if (nRand <= hand5)
			DropParty = 4;

		else if (nRand == hand6)
			DropParty = 5;
}

void noKiller()
{
	bSombraNegra.spawned = FALSE;
	statusSombraNegra.aLive = 0;
	statusSombraNegra.PlayerKiled = "NINGUEM";
	statusSombraNegra.DayKiled = 0;
	statusSombraNegra.HourKiled = 0;
	statusSombraNegra.MinKiled = 0;

	WriteSombraNegra();

	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].GenerateIndex == bSombraNegra.Boss.ID)
		{
			DeleteMob(i, 1);
		}
	}

	for (int i = MAX_USER; i < MAX_MOB; i++)
	{
		if (pMob[i].GenerateIndex == bSombraNegra.Guardian.ID)
		{
			DeleteMob(i, 1);
		}
	}
	sprintf(msgTemp, bSombraNegra.NoticeEnd2.c_str());
	SendNotice(msgTemp);
}



