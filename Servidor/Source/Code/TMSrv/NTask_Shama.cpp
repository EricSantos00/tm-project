#include "ProcessClientMessage.h"

void NTask_Shama(int a_iConn, int a_iTarget)
{
	int circle = pMob[a_iConn].MOB.Equip[13].sIndex;

	int ncircle = circle;
	int circlemode = 0;

	if (circle != 448 && circle != 449 && circle != 450)
	{
		if (circle != 693 && circle != 694 && circle != 695)
		{
			SendSay(a_iTarget, g_pMessageStringTable[_NN_Need_Pure_Divine]);
			return;
		}
		ncircle -= 693;
		circlemode = 2;
	}
	else
	{
		ncircle -= 448;
		circlemode = 1;
	}

	if (circlemode == 1 && pMob[a_iConn].Extra.QuestInfo.Circle == 1)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Youve_Done_It_Already]);
		return;
	}

	int specialreset = 50;

	if (circlemode == 2)
		specialreset = 100;

	int special = pMob[a_iConn].MOB.SpecialBonus;

	for (int i = 0; i < 4; i++)
	{
		if (pMob[a_iConn].MOB.BaseScore.Special[i] <= specialreset)
		{
			special += pMob[a_iConn].MOB.BaseScore.Special[i];
			pMob[a_iConn].MOB.BaseScore.Special[i] = 0;
		}
		else
		{
			special += specialreset;
			pMob[a_iConn].MOB.BaseScore.Special[i] -= specialreset;
		}
	}

	pMob[a_iConn].MOB.SpecialBonus = special;

	if (circlemode == 1)
		pMob[a_iConn].Extra.QuestInfo.Circle = 1;

	if (ncircle == 0)
		pMob[a_iConn].MOB.LearnedSkill &= 0xFFFFFF00;

	if (ncircle == 1)
		pMob[a_iConn].MOB.LearnedSkill &= 0xFFFF00FF;

	if (ncircle == 2)
		pMob[a_iConn].MOB.LearnedSkill &= 0xFF00FFFF;

	BASE_GetBonusSkillPoint(&pMob[a_iConn].MOB, &pMob[a_iConn].Extra);

	memset(&pMob[a_iConn].MOB.Equip[13], 0, sizeof(STRUCT_ITEM));

	SendItem(a_iConn, ITEM_PLACE_EQUIP, 13, &pMob[a_iConn].MOB.Equip[13]);
	SendEtc(a_iConn);
	SendSay(a_iTarget, g_pMessageStringTable[_NN_Initialize_Skill]);
	SetAffect(a_iConn, 44, 20, 20);
	SendScore(a_iConn);

	SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Qest06Complete]);
	sprintf(temp, "etc,device circle quest item:%d mode:%d type:%d", circle, circlemode, ncircle);
	MyLog(LogType::Quests, pUser[a_iConn].AccountName, temp, 0, pUser[a_iConn].IP);
	return;
}
