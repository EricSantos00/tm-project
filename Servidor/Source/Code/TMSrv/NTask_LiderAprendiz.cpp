#include "ProcessClientMessage.h"

void NTask_LiderAprendiz(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != ARCH)
	{
		sprintf(temp, g_pMessageStringTable[_SN_NEEDCLASS], "Arch");
		SendSay(a_iTarget, temp);
		return;
	}

	if (pMob[a_iConn].MOB.BaseScore.Level < 99 || pMob[a_iConn].MOB.BaseScore.Level > 149)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_Limit2]);
		return;
	}

	if (pMob[a_iConn].MOB.Equip[15].sIndex)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Youve_Done_It_Already]);
		return;
	}

	sprintf(temp, "etc,quest_aprendiz_arch complete name:%s conn:%d", pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

	memset(&pMob[a_iConn].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));
	pMob[a_iConn].MOB.Equip[15].sIndex = 4006;

	SendItem(a_iConn, ITEM_PLACE_EQUIP, 15, &pMob[a_iConn].MOB.Equip[15]);

	pMob[a_iConn].GetCurrentScore(a_iConn);
	SendScore(a_iConn);

	SendEmotion(a_iConn, 14, 3);

	sprintf(temp, g_pMessageStringTable[_DN_Play_Quest], "Formatura Aprendiz");
	SendClientMsg(a_iConn, temp);
	return;
}