#include "ProcessClientMessage.h"

void NTask_Skills(int a_iConn, int a_iTarget, int confirm)
{
	if (confirm == 0)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Soul_n_8_Sephera]);
		return;
	}
	int Pedras = 0;

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex != (1744 + j))
				continue;

			Pedras++;
			break;
		}
	}

	if (Pedras < 8)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Need_8_Sephera]);
		return;
	}
	if (pMob[a_iConn].MOB.Coin < 30000000)
	{
		SendSay(a_iTarget, "Traga-me 30.000.000 em Gold. ");
		return;
	}

	pMob[a_iConn].MOB.Coin -= 30000000;
	SendEtc(a_iConn);

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex != (1744 + j))
				continue;

			BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);
			SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);

			Pedras--;
			break;
		}
	}

	STRUCT_ITEM Item;

	memset(&Item, 0, sizeof(STRUCT_ITEM));

	if (pMob[a_iTarget].MOB.Exp == 994)
		Item.sIndex = 1762;

	else if (pMob[a_iTarget].MOB.Exp == 995)
		Item.sIndex = 1761;

	else if (pMob[a_iTarget].MOB.Exp == 996)
		Item.sIndex = 1763;

	else if (pMob[a_iTarget].MOB.Exp == 997)
		Item.sIndex = 1760;

	PutItem(a_iConn, &Item);
	SendSay(a_iTarget, g_pMessageStringTable[_NN_Sepherot_created]);

	sprintf(temp, "etc,sephirot create class:%d name:%s conn:%d", pMob[a_iTarget].MOB.Exp, pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}