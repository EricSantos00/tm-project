#include "ProcessClientMessage.h"

void NTask_QuestCoveiro(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_Limit2]);
		return;
	}

	int minlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 39 : 39;
	int maxlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 115 : 115;

	if (pMob[a_iConn].MOB.CurrentScore.Level < minlevel || pMob[a_iConn].MOB.CurrentScore.Level >= maxlevel)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_limit]);
		return;
	}

	int i = 0;
	int itemQuest = VELA;
	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex != itemQuest)
			continue;

		STRUCT_ITEM *item = GetFirstItemBag(a_iConn, itemQuest);

		if (item == nullptr)
			continue;

		int amount = BASE_GetItemAmount(item);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);
		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
		break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[itemQuest].Name);
		SendSay(a_iTarget, temp);
		return;
	}
	if (pMob[a_iConn].QuestFlag != 1)
	{
		pMob[a_iConn].QuestFlag = 1;
		pMob[a_iConn].CheckQuest = 600 + pMob[a_iConn].Extra.CheckTimeKersef;
	}

	DoTeleport(a_iConn, 2398 + rand() % 5 - 3, 2105 + rand() % 5 - 3);

	sprintf(temp, "etc,quest256 ticket coveiro name:%s level:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}

void NTask_QuestJardineiro(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_Limit2]);
		return;
	}

	int minlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 115 : 115;
	int maxlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 190 : 190;

	if (pMob[a_iConn].MOB.CurrentScore.Level < minlevel || pMob[a_iConn].MOB.CurrentScore.Level >= maxlevel)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_limit]);
		return;
	}

	int i = 0;
	int itemQuest = COLHEITA;
	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex != itemQuest)
			continue;

		STRUCT_ITEM* item = GetFirstItemBag(a_iConn, itemQuest);

		if (item == nullptr)
			continue;

		int amount = BASE_GetItemAmount(item);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);
		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
		break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[itemQuest].Name);
		SendSay(a_iTarget, temp);
		return;
	}

	if (pMob[a_iConn].QuestFlag != 2)
	{
		pMob[a_iConn].QuestFlag = 2;
		pMob[a_iConn].CheckQuest = 600 + pMob[a_iConn].Extra.CheckTimeKersef;
	}

	DoTeleport(a_iConn, 2234 + rand() % 5 - 3, 1714 + rand() % 5 - 3);

	sprintf(temp, "etc,quest256 ticket jardineiro name:%s level:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}

void NTask_QuestKaizen(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_Limit2]);
		return;
	}

	int minlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 190 : 190;
	int maxlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 265 : 265;

	if (pMob[a_iConn].MOB.CurrentScore.Level < minlevel || pMob[a_iConn].MOB.CurrentScore.Level >= maxlevel)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_limit]);
		return;
	}

	int i = 0;
	int itemQuest = CURA_BATEDOR;
	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex != itemQuest)
			continue;

		STRUCT_ITEM* item = GetFirstItemBag(a_iConn, itemQuest);

		if (item == nullptr)
			continue;

		int amount = BASE_GetItemAmount(item);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);
		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
		break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[itemQuest].Name);
		SendSay(a_iTarget, temp);
		return;
	}
	if (pMob[a_iConn].QuestFlag != 3)
	{
		pMob[a_iConn].QuestFlag = 3;
		pMob[a_iConn].CheckQuest = 600 + pMob[a_iConn].Extra.CheckTimeKersef;
	}

	DoTeleport(a_iConn, 464 + rand() % 5 - 3, 3902 + rand() % 5 - 3);

	sprintf(temp, "etc,quest256 ticket kaizen name:%s level:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}

void NTask_QuestHidra(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_Limit2]);
		return;
	}

	int minlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 265 : 265;
	int maxlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 320 : 320;

	if (pMob[a_iConn].MOB.CurrentScore.Level < minlevel || pMob[a_iConn].MOB.CurrentScore.Level >= maxlevel)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_limit]);
		return;
	}

	int i = 0;
	int itemQuest = MANA_BATEDOR;
	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex != itemQuest)
			continue;

		STRUCT_ITEM* item = GetFirstItemBag(a_iConn, itemQuest);

		if (item == nullptr)
			continue;

		int amount = BASE_GetItemAmount(item);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);
		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
		break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[itemQuest].Name);
		SendSay(a_iTarget, temp);
		return;
	}
	if (pMob[a_iConn].QuestFlag != 4)
	{
		pMob[a_iConn].QuestFlag = 4;
		pMob[a_iConn].CheckQuest = 600 + pMob[a_iConn].Extra.CheckTimeKersef;
	}

	DoTeleport(a_iConn, 668 + rand() % 5 - 3, 3756 + rand() % 5 - 3);

	sprintf(temp, "etc,quest256 ticket hidra name:%s level:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}

void NTask_QuestElfos(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_Limit2]);
		return;
	}

	int minlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 320 : 320;
	int maxlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 370 : 370;

	if (pMob[a_iConn].MOB.CurrentScore.Level < minlevel || pMob[a_iConn].MOB.CurrentScore.Level >= maxlevel)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_limit]);
		return;
	}

	int i = 0;
	int itemQuest = EMBLEMA_GUARDA;
	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex != itemQuest)
			continue;

		STRUCT_ITEM* item = GetFirstItemBag(a_iConn, itemQuest);

		if (item == nullptr)
			continue;

		int amount = BASE_GetItemAmount(item);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);
		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
		break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[itemQuest].Name);
		SendSay(a_iTarget, temp);
		return;
	}
	if (pMob[a_iConn].QuestFlag != 5)
	{
		pMob[a_iConn].QuestFlag = 5;
		pMob[a_iConn].CheckQuest = 600 + pMob[a_iConn].Extra.CheckTimeKersef;
	}

	DoTeleport(a_iConn, 1322 + rand() % 5 - 3, 4041 + rand() % 5 - 3);

	sprintf(temp, "etc,quest256 ticket elfos name:%s level:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}

void NTask_QuestMolarGargula(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_Limit2]);
		return;
	}

	if (pMob[a_iConn].MOB.CurrentScore.Level < 200 || pMob[a_iConn].MOB.CurrentScore.Level >= 204)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_limit]);
		return;
	}

	sprintf(temp, "etc,quest_molar1 npcteleport name:%s conn:%d", pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

	DoTeleport(a_iConn, 817 + rand() % 5 - 3, 4062 + rand() % 5 - 3);
	return;
}

void NTask_QuestCapaVerde(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_Limit2]);
		return;
	}

	if (pMob[a_iConn].MOB.CurrentScore.Level < 99 || pMob[a_iConn].MOB.CurrentScore.Level >= 150)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_limit]);
		return;
	}

	DoTeleport(a_iConn, 2245 + rand() % 5 - 3, 1576 + rand() % 5 - 3);

	sprintf(temp, "etc,quest_aprendiz1 npcteleport name:%s conn:%d", pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}


void NTask_QuestLeakyZakum(int a_iConn, int a_iTarget)
{
	char UserNameArea[128];

	int count = GetUserInArea(2180, 1160, 2296, 1270, UserNameArea);

	if (count < 1)
		sprintf(temp, g_pMessageStringTable[_NN_Zakum_Quest_empty]);
	else
		sprintf(temp, g_pMessageStringTable[_SD_Zakum_Quest_by_S_N], UserNameArea, count - 1);

	SendSay(a_iTarget, temp);
	return;
}

void NTask_QuestChefeTreina(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_Limit2]);
		return;
	}

	if (pMob[a_iConn].MOB.CurrentScore.Level < 99 || pMob[a_iConn].MOB.CurrentScore.Level >= 150)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_limit]);
		return;
	}

	if (pMob[a_iConn].MOB.Equip[13].sIndex != 4080)
	{
		sprintf(temp, g_pMessageStringTable[_SN_WANTEQUIPITEM], g_pItemList[4080].Name);
		SendSay(a_iTarget, temp);
		return;
	}

	if (pMob[a_iConn].MOB.Equip[15].sIndex != 0)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Youve_Done_It_Already]);
		return;
	}

	sprintf(temp, "etc,quest_aprendiz2 complete name:%s conn:%d", pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

	BASE_ClearItem(&pMob[a_iConn].MOB.Equip[13]);
	SendItem(a_iConn, ITEM_PLACE_EQUIP, 13, &pMob[a_iConn].MOB.Equip[13]);

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

void NTask_SacerdoteKruno(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL && pMob[a_iConn].Extra.ClassMaster != ARCH)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_Limit2]);
		return;
	}

	int minlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 69 : 69;
	int maxlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 74 : 74;

	if (pMob[a_iConn].MOB.CurrentScore.Level < minlevel || pMob[a_iConn].MOB.CurrentScore.Level >= maxlevel)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_limit]);
		return;
	}

	int i = 0;

	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex != 4123)
			continue;

		BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);
		SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
		break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[4123].Name);
		SendSay(a_iTarget, temp);
		return;
	}

	STRUCT_ITEM Item;
	memset(&Item, 0, sizeof(STRUCT_ITEM));

	Item.sIndex = 4124;

	PutItem(a_iConn, &Item);
	sprintf(temp, "etc,questkruno ticket chance name:%s level:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}

void NTask_SacerdoteAmelia(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL && pMob[a_iConn].Extra.ClassMaster != ARCH)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_Limit2]);
		return;
	}

	int minlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 119 : 119;
	int maxlevel = pMob[a_iConn].Extra.ClassMaster == MORTAL ? 124 : 124;

	if (pMob[a_iConn].MOB.CurrentScore.Level < minlevel || pMob[a_iConn].MOB.CurrentScore.Level >= maxlevel)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_limit]);
		return;
	}

	int i = 0;

	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex != 4125)
			continue;

		BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);
		SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
		break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[4123].Name);
		SendSay(a_iTarget, temp);
		return;
	}

	STRUCT_ITEM Item;
	memset(&Item, 0, sizeof(STRUCT_ITEM));

	Item.sIndex = 4126;

	PutItem(a_iConn, &Item);
	sprintf(temp, "etc,questamelia ticket chance name:%s level:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}

void NTask_QuestGuardaReal(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].Extra.ClassMaster != MORTAL)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_Limit2]);
		return;
	}

	if (pMob[a_iConn].MOB.CurrentScore.Level < 219 || pMob[a_iConn].MOB.CurrentScore.Level >= 249)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_limit]);
		return;
	}

	SendSay(a_iTarget, "A quest [Cavaleiro Real] foi iniciada.");
	DoTeleport(a_iConn, 1740 + rand() % 5 - 3, 1725 + rand() % 5 - 3);
	return;
}

void NTask_SacerdoteJester(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].MOB.CurrentScore.Level < 69 || pMob[a_iConn].MOB.CurrentScore.Level >= 74)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_limit]);
		return;
	}

	SendSay(a_iTarget, "Que você consiga sua salvação.");

	DoTeleport(a_iConn, 2654 + rand() % 5 - 3, 1988 + rand() % 5 - 3);
	return;
}

void NTask_GuardaHelgardh(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].MOB.CurrentScore.Level < 119 || pMob[a_iConn].MOB.CurrentScore.Level >= 124)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Level_limit]);
		return;
	}

	SendSay(a_iTarget, "Que você consiga sua salvação.");

	DoTeleport(a_iConn, 1961 + rand() % 5 - 3, 1593 + rand() % 5 - 3);
	return;
}


void NTask_Sobrevivente(int a_iConn, int a_iTarget)
{
	int ItemReq = 4127;
	int i = 0;
	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex != ItemReq)
			continue;
		break;
	}
	if (i != pMob[a_iConn].MaxCarry)
	{
		BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);
		SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);

		pMob[a_iConn].Extra.KefraTicket += 100;

		sprintf(temp, g_pMessageStringTable[_DN_CHANGE_COUNT], pMob[a_iConn].Extra.KefraTicket);
		SendClientMsg(a_iConn, temp);
		return;
	}

	sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[ItemReq].Name);
	SendSay(a_iTarget, temp);
	return;
}