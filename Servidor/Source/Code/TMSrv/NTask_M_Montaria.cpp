#include "ProcessClientMessage.h"

void NTask_M_Montaria(int a_iConn, int a_iTarget, int confirm)
{
	int mountIndex = pMob[a_iConn].MOB.Equip[14].sIndex;

	if (mountIndex < 2330 || mountIndex >= 2390)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Cure_animals]);
		return;
	}

	if (pMob[a_iConn].MOB.Equip[14].stEffect[0].sValue > 0)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Cure_animals]);
		return;
	}

	int price = g_pItemList[mountIndex].Price;

	if (confirm == 0)
	{
		sprintf(temp, g_pMessageStringTable[_DS_S_cure_price_D], g_pItemList[mountIndex].Name, price);
		SendSay(a_iTarget, temp);
		return;
	}

	if (pMob[a_iConn].MOB.Coin < price)
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Enough_Money]);
		return;
	}

	if (price < 0 || price > 2000000000)
		return;

	pMob[a_iConn].MOB.Coin -= price;

	int vit = BASE_GetItemAbility(&pMob[a_iConn].MOB.Equip[14], EF_MOUNTLIFE);

	vit -= rand() % 3;

	if (vit > 0)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Cured]);
		pMob[a_iConn].MOB.Equip[14].stEffect[1].cValue = vit;
		pMob[a_iConn].MOB.Equip[14].stEffect[0].sValue = 20;
		pMob[a_iConn].MOB.Equip[14].stEffect[2].cEffect = 5;
	
	}
	else
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Cure_failed]);
		memset(&pMob[a_iConn].MOB.Equip[14], 0, sizeof(STRUCT_ITEM));
	}

	pMob[a_iConn].GetCurrentScore(a_iConn);
	SendItem(a_iConn, ITEM_PLACE_EQUIP, 14, &pMob[a_iConn].MOB.Equip[14]);
	MountProcess(a_iConn, &pMob[a_iConn].MOB.Equip[14]);
	SendEtc(a_iConn);

	sprintf(temp, "etc,mount ressurect index:%d vit:%d - %d", pMob[a_iConn].MOB.Equip[14].sIndex, vit, pMob[a_iConn].MOB.Equip[14].stEffect[1].cEffect);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}