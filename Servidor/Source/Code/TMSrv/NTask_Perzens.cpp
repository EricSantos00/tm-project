#include "ProcessClientMessage.h"

void NTask_Perzens(int a_iConn, int a_iTarget)
{
	int i = 0;

	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex != pMob[a_iTarget].MOB.Carry[0].sIndex)
			continue;

		break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[pMob[a_iTarget].MOB.Carry[0].sIndex].Name);
		SendSay(a_iTarget, temp);
		return;
	}

	BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);

	pMob[a_iConn].MOB.Carry[i].sIndex = pMob[a_iTarget].MOB.Carry[1].sIndex;

	BASE_SetItemDate(&pMob[a_iConn].MOB.Carry[i], 30);

	SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);

	sprintf(temp, "etc,premium mount started type:%d name:%s conn:%d", pMob[a_iTarget].MOB.Carry[1].sIndex, pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}
