#include "ProcessClientMessage.h"

void NTask_TrainingI(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL || pMob[a_iConn].MOB.CurrentScore.Level >= FREEEXP || pMob[a_iConn].Extra.QuestInfo.Mortal.Newbie != 0)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_NewbieQuest_Already1]);
		return;;
	}
	int i = 0;

	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex == 451)
			break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_NewbieQuest_Cheerup1]);
		return;
	}
	sprintf(temp, "etc,newbiequest1 complete name:%s conn:%d", pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

	pMob[a_iConn].Extra.QuestInfo.Mortal.Newbie = 1;
	SendSay(a_iTarget, g_pMessageStringTable[_NN_NewbieQuest_Complete1]);
	SendMsgExp(a_iConn, "Recebeu Caixa de Poção de Cura (20) como recompensa.", TNColor::White, false);

	STRUCT_ITEM Item;
	memset(&Item, 0, sizeof(STRUCT_ITEM));

	//Pot com 20
	Item.sIndex = 682;
	Item.stEffect[0].cEffect = 61;
	Item.stEffect[0].cValue = 20;

	PutItem(a_iConn, &Item);

	SetAffect(a_iConn, 44, 200, 200);
	SendScore(a_iConn);
	SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
	return;
}

void NTask_TrainingII(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL || pMob[a_iConn].MOB.CurrentScore.Level >= FREEEXP || pMob[a_iConn].Extra.QuestInfo.Mortal.Newbie != 1)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_NewbieQuest_Already2]);
		return;
	}
	int i = 0;

	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex == 452)
			break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_NewbieQuest_Cheerup2]);
		return;
	}
	sprintf(temp, "etc,newbiequest2 complete name:%s conn:%d", pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

	pMob[a_iConn].Extra.QuestInfo.Mortal.Newbie++;
	SendSay(a_iTarget, g_pMessageStringTable[_NN_NewbieQuest_Complete2]);
	SendMsgExp(a_iConn, "Como recompensa, a opção da arma foi alterada.", TNColor::White, false);


	int WeaponId = pMob[a_iConn].MOB.Equip[6].sIndex;
	int cls = pMob[a_iConn].MOB.Class;

	if (WeaponId > 0 && WeaponId < MAX_ITEMLIST)
	{
		int ReqLv = g_pItemList[WeaponId].ReqLvl;

		if (ReqLv > 39)
			return;

		pMob[a_iConn].MOB.Equip[6].stEffect[0].cEffect = 0;
		pMob[a_iConn].MOB.Equip[6].stEffect[0].cValue = 0;
		pMob[a_iConn].MOB.Equip[6].stEffect[1].cEffect = 0;
		pMob[a_iConn].MOB.Equip[6].stEffect[1].cValue = 0;
		pMob[a_iConn].MOB.Equip[6].stEffect[2].cEffect = 0;
		pMob[a_iConn].MOB.Equip[6].stEffect[2].cValue = 0;

		SetItemBonus(&pMob[a_iConn].MOB.Equip[6], 50 + ReqLv, 1, 0);
		SendItem(a_iConn, ITEM_PLACE_EQUIP, 6, &pMob[a_iConn].MOB.Equip[6]);
	}

	SetAffect(a_iConn, 44, 200, 200);
	SendScore(a_iConn);
	SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
	return;
}

void NTask_TrainingIII(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL || pMob[a_iConn].MOB.CurrentScore.Level >= FREEEXP || pMob[a_iConn].Extra.QuestInfo.Mortal.Newbie != 2)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_NewbieQuest_Already3]);
		return;
	}
	int i = 0;

	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex == 453)
			break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_NewbieQuest_Cheerup3]);
		return;
	}
	sprintf(temp, "etc,newbiequest3 complete name:%s conn:%d", pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

	pMob[a_iConn].Extra.QuestInfo.Mortal.Newbie++;
	SendSay(a_iTarget, g_pMessageStringTable[_NN_NewbieQuest_Complete3]);
	SendMsgExp(a_iConn, "Armas e Armaduras foram refinadas.", TNColor::White, false);


	for (int j = 1; j < 8; j++)
	{
		int itemId = pMob[a_iConn].MOB.Equip[6].sIndex;

		if (itemId > 0 && itemId < MAX_ITEMLIST)
		{
			int ReqLv = g_pItemList[itemId].ReqLvl;

			pMob[a_iConn].MOB.Equip[j].stEffect[0].cEffect = 0;
			pMob[a_iConn].MOB.Equip[j].stEffect[0].cValue = 0;
			pMob[a_iConn].MOB.Equip[j].stEffect[1].cEffect = 0;
			pMob[a_iConn].MOB.Equip[j].stEffect[1].cValue = 0;
			pMob[a_iConn].MOB.Equip[j].stEffect[2].cEffect = 0;
			pMob[a_iConn].MOB.Equip[j].stEffect[2].cValue = 0;

			SetItemBonus(&pMob[a_iConn].MOB.Equip[j], 50 + ReqLv, 1, 0);
			BASE_SetItemSanc(&pMob[a_iConn].MOB.Equip[j], 3, 0);

			SendItem(a_iConn, ITEM_PLACE_EQUIP, j, &pMob[a_iConn].MOB.Equip[j]);
		}
	}
	SetAffect(a_iConn, 44, 200, 200);
	SendScore(a_iConn);
	SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
	return;
}

void NTask_TrainingChief(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL || pMob[a_iConn].MOB.CurrentScore.Level >= FREEEXP || pMob[a_iConn].Extra.QuestInfo.Mortal.Newbie != 3)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_NewbieQuest_Already4]);
		return;
	}
	int i = 0;

	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex == 524)
			break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_NewbieQuest_Cheerup4]);
		return;
	}

	sprintf(temp, "etc,newbiequest4 complete name:%s conn:%d", pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

	pMob[a_iConn].Extra.QuestInfo.Mortal.Newbie = 4;
	SendSay(a_iTarget, g_pMessageStringTable[_NN_NewbieQuest_Complete4]);
	SendMsgExp(a_iConn, "Ganhou um prêmio por finalizar a quest.", TNColor::White, false);


	STRUCT_ITEM Item;
	memset(&Item, 0, sizeof(STRUCT_ITEM));

	BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);

	int rd = rand() % 3;

	if (rd == 0)
	{
		Item.sIndex = 682;
		Item.stEffect[0].cEffect = 61;
		Item.stEffect[0].cValue = 20;
	}

	else if (rd == 1)
		Item.sIndex = 481;

	else
		Item.sIndex = 652;


	PutItem(a_iConn, &Item);

	SetAffect(a_iConn, 44, 200, 200);
	SendScore(a_iConn);
	SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
	return;
}