#include "ProcessClientMessage.h"

void NTask_MestreHaby(int a_iConn, int a_iTarget, int confirm)
{
	if (confirm == 0)
	{
		sprintf(temp, g_pMessageStringTable[_DN_Want_Stat_Init], StatSapphire);
		SendSay(a_iTarget, temp);
		return;
	}

	for (int i = 1; i < 8; i++)
	{
		if (pMob[a_iConn].MOB.Equip[i].sIndex)
		{
			SendSay(a_iTarget, g_pMessageStringTable[_NN_Cant_with_armor]);
			return;
		}
	}

	int NumSappInv = 0;

	int RetornoHab = 0;

	for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex == 697)
			NumSappInv++;

		else if (pMob[a_iConn].MOB.Carry[i].sIndex == 4131)
			NumSappInv += 10;

		else if (pMob[a_iConn].MOB.Carry[i].sIndex == 3336)
			RetornoHab = 1;
	}

	if (NumSappInv < StatSapphire && RetornoHab == 0)
	{
		sprintf(temp, g_pMessageStringTable[_DN_Need_D_Sapphire2], StatSapphire);
		SendSay(a_iTarget, temp);
		return;
	}

	if (RetornoHab == 1)
	{
		for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex == 3336)
			{
				memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
				SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);

				break;
			}
		}

		goto DiretoReset;
	}
	if (NumSappInv > StatSapphire)
		NumSappInv = StatSapphire;

	for (int i = 0; i < pMob[a_iConn].MaxCarry && NumSappInv > 0; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex == 697)
		{
			memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
			SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);

			NumSappInv--;
		}

		else if (pMob[a_iConn].MOB.Carry[i].sIndex == 4131 && NumSappInv >= 10)
		{
			memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
			SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);

			NumSappInv -= 10;
		}
	}
DiretoReset:

	int cls = pMob[a_iConn].MOB.Class;

	if (cls < 0 || cls > 3)
		return;

	int resetp = 100;
	int score = pMob[a_iConn].MOB.ScoreBonus;
	int str = pMob[a_iConn].MOB.BaseScore.Str - BaseSIDCHM[cls][0];
	int _int = pMob[a_iConn].MOB.BaseScore.Int - BaseSIDCHM[cls][1];
	int dex = pMob[a_iConn].MOB.BaseScore.Dex - BaseSIDCHM[cls][2];
	int con = pMob[a_iConn].MOB.BaseScore.Con - BaseSIDCHM[cls][3];

	if (str <= resetp)
	{
		pMob[a_iConn].MOB.BaseScore.Str -= str;
		score += str;
	}
	else
	{
		pMob[a_iConn].MOB.BaseScore.Str -= resetp;
		score += resetp;
	}

	if (_int <= resetp)
	{
		pMob[a_iConn].MOB.BaseScore.Int -= _int;
		score += _int;
	}
	else
	{
		pMob[a_iConn].MOB.BaseScore.Int -= resetp;
		score += resetp;
	}

	if (dex <= resetp)
	{
		pMob[a_iConn].MOB.BaseScore.Dex -= dex;
		score += dex;
	}

	else
	{
		pMob[a_iConn].MOB.BaseScore.Dex -= resetp;
		score += resetp;
	}

	if (con <= resetp)
	{
		pMob[a_iConn].MOB.BaseScore.Con -= con;
		score += con;
	}
	else
	{
		pMob[a_iConn].MOB.BaseScore.Con -= resetp;
		score += resetp;
	}

	sprintf(temp, "etc,mestre_hab resetscore 100 name:%s conn:%d", pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

	BASE_GetBonusScorePoint(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);
	BASE_GetHpMp(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);

	SetAffect(a_iConn, 44, 20, 20);

	SendScore(a_iConn);
	SendEtc(a_iConn);
	SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Stat_Initialized]);
	return;
}