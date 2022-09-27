#include "ProcessClientMessage.h"

void NTask_BlackOracle(int a_iConn, int a_iTarget)
{
	int i = 0;

	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex == 1740)
			break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Set_Soul]);
		return;
	}

	if (pMob[a_iConn].MOB.Carry[i + 1].sIndex != 1741)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Set_Soul]);
		return;
	}


	int NumSepInv = 0;
	int j = 0;

	for (j = 0; j < pMob[a_iConn].MaxCarry; j++)
	{
		if (pMob[a_iConn].MOB.Carry[j].sIndex == 697)
			NumSepInv++;

		else if (pMob[a_iConn].MOB.Carry[j].sIndex == 4131)
			NumSepInv += 10;
	}

	if (NumSepInv < 10)
	{
		sprintf(temp, g_pMessageStringTable[_DN_Need_D_Sapphire], 10);
		SendSay(a_iTarget, temp);
		return;
	}
	int Saphire = 10;

	for (j = 0; j < pMob[a_iConn].MaxCarry && Saphire > 0; j++)
	{
		if (pMob[a_iConn].MOB.Carry[j].sIndex == 697)
		{
			memset(&pMob[a_iConn].MOB.Carry[j], 0, sizeof(STRUCT_ITEM));
			SendItem(a_iConn, ITEM_PLACE_CARRY, j, &pMob[a_iConn].MOB.Carry[j]);
			Saphire--;
		}

		else if (pMob[a_iConn].MOB.Carry[j].sIndex == 4131)
		{
			memset(&pMob[a_iConn].MOB.Carry[j], 0, sizeof(STRUCT_ITEM));
			SendItem(a_iConn, ITEM_PLACE_CARRY, j, &pMob[a_iConn].MOB.Carry[j]);

			if ((Saphire - 10) < 0)
				Saphire = 0;

			else
				Saphire -= 10;
		}
	}

	memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
	SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);

	memset(&pMob[a_iConn].MOB.Carry[i + 1], 0, sizeof(STRUCT_ITEM));
	SendItem(a_iConn, ITEM_PLACE_CARRY, i + 1, &pMob[a_iConn].MOB.Carry[i + 1]);

	STRUCT_ITEM Item;
	memset(&Item, 0, sizeof(STRUCT_ITEM));

	Item.sIndex = 1742;

	PutItem(a_iConn, &Item);

	SendSay(a_iTarget, g_pMessageStringTable[_NN_Soul_Merged]);

	sprintf(temp, "etc,stone_immortality create name:%s conn:%d", pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}