#include "ProcessClientMessage.h"

void NTask_DragãoArmia(int a_iConn, int a_iTarget)
{
	int treasure = CombineTreasureMap(a_iConn);

	if (treasure)
		return;

	for (int i = 0; i < 8; i++)
	{
		if (g_pTreasure[i].Source == 0)
			continue;

		int x = 0;

		for (x = 0; x < pMob[a_iConn].MaxCarry; x++)
		{
			if (pMob[a_iConn].MOB.Carry[x].sIndex == g_pTreasure[i].Source)
				break;
		}

		if (x != pMob[a_iConn].MaxCarry)
		{
			char itemlog[1024];

			sprintf(temp, "tra,_gold_ 0");

			BASE_GetItemCode(&pMob[a_iConn].MOB.Carry[x], itemlog);
			strcat(temp, itemlog);

			Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);

			memset(&pMob[a_iConn].MOB.Carry[x], 0, sizeof(STRUCT_ITEM));

			SendItem(a_iConn, ITEM_PLACE_CARRY, x, &pMob[a_iConn].MOB.Carry[x]);

			int _rand = rand() % 1000;

			STRUCT_ITEM Item;

			memset(&Item, 0, sizeof(STRUCT_ITEM));

			if (_rand < g_pTreasure[i].Rate[0])
				memcpy(&Item, &g_pTreasure[i].Target[0], sizeof(STRUCT_ITEM));

			else if (_rand < g_pTreasure[x].Rate[1])
				memcpy(&Item, &g_pTreasure[i].Target[1], sizeof(STRUCT_ITEM));

			else if (_rand < g_pTreasure[i].Rate[2])
				memcpy(&Item, &g_pTreasure[i].Target[2], sizeof(STRUCT_ITEM));

			else if (_rand < g_pTreasure[i].Rate[3])
				memcpy(&Item, &g_pTreasure[i].Target[3], sizeof(STRUCT_ITEM));

			else if (_rand < g_pTreasure[i].Rate[4])
				memcpy(&Item, &g_pTreasure[i].Target[4], sizeof(STRUCT_ITEM));

			if (Item.sIndex == 0)
			{
				SendSay(a_iTarget, g_pMessageStringTable[_NN_Next_Chance]);
				return;
			}

			sprintf(temp, "tra,%s 0", pUser[a_iConn].AccountName);

			BASE_GetItemCode(&Item, itemlog);
			strcat(temp, itemlog);

			Log(temp, "_gold_", pUser[a_iConn].IP);

			PutItem(a_iConn, &Item);

			SendSay(a_iTarget, g_pMessageStringTable[_NN_Congratulations]);
			return;
		}
	}

	int Cristais[7] = { -1, -1, -1, -1, -1, -1, -1 };
	int NumCristal = 0;

	for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		int ItemId = pMob[a_iConn].MOB.Carry[i].sIndex;

		if (ItemId >= 421 && ItemId <= 427 && Cristais[ItemId - 421] == -1)
		{
			Cristais[ItemId - 421] = i;
			NumCristal++;
		}
	}

	if (Cristais[0] != -1 && Cristais[1] != -1 && Cristais[2] != -1 && Cristais[3] != -1 && Cristais[4] != -1 && Cristais[5] != -1 && Cristais[6] != -1)
	{
		if (pMob[a_iConn].MOB.Equip[6].sIndex == 0)
		{
			SendSay(a_iTarget, g_pMessageStringTable[_NN_Equip_Weapon_To_Enchant]);
			return;
		}

		int sanc = BASE_GetItemSanc(&pMob[a_iConn].MOB.Equip[6]);

		if (sanc > 0)
		{
			SendSay(a_iTarget, g_pMessageStringTable[_NN_Only_Nomal_Weapons]);
			return;
		}

		if ((pMob[a_iConn].MOB.Equip[0].sIndex / 10) == 0)
			SendEmotion(a_iConn, 23, 0);

		else
			SendEmotion(a_iConn, 15, 0);

		int cEffect1 = pMob[a_iConn].MOB.Equip[6].stEffect[0].cEffect;
		int cEffect2 = pMob[a_iConn].MOB.Equip[6].stEffect[1].cEffect;
		int cEffect3 = pMob[a_iConn].MOB.Equip[6].stEffect[2].cEffect;

		int cValue1 = pMob[a_iConn].MOB.Equip[6].stEffect[0].cValue;
		int cValue2 = pMob[a_iConn].MOB.Equip[6].stEffect[1].cValue;
		int cValue3 = pMob[a_iConn].MOB.Equip[6].stEffect[2].cValue;

		pMob[a_iConn].MOB.Equip[6].stEffect[0].cEffect = 0;
		pMob[a_iConn].MOB.Equip[6].stEffect[0].cValue = 0;

		pMob[a_iConn].MOB.Equip[6].stEffect[1].cEffect = 0;
		pMob[a_iConn].MOB.Equip[6].stEffect[1].cValue = 0;

		pMob[a_iConn].MOB.Equip[6].stEffect[2].cEffect = 0;
		pMob[a_iConn].MOB.Equip[6].stEffect[2].cValue = 0;

		SetItemBonus(&pMob[a_iConn].MOB.Equip[6], (25 * NumCristal / 10) + g_pItemList[pMob[a_iConn].MOB.Equip[6].sIndex].ReqLvl, 1, pMob[a_iConn].DropBonus);

		for (int i = 0; i < 7; i++)
			memset(&pMob[a_iConn].MOB.Carry[Cristais[i]], 0, sizeof(STRUCT_ITEM));

		SendCarry(a_iConn);

		sprintf(temp, g_pMessageStringTable[_SN_I_Wwill_Enchant_Your_Weapon], g_pItemList[pMob[a_iConn].MOB.Equip[6].sIndex].Name);
		SendClientMsg(a_iConn, temp);

		SendItem(a_iConn, ITEM_PLACE_EQUIP, 6, &pMob[a_iConn].MOB.Equip[6]);

		sprintf(temp, g_pMessageStringTable[_SN_Now_I_Will_Enchant_Your], pMob[a_iConn].MOB.MobName);
		SendSay(a_iTarget, temp);

		SetAffect(a_iConn, 44, 200, 200);
		SendScore(a_iConn);

		return;
	}
	else
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Gather_7_Clistals]);

}
void NTask_DragãoArzan(int a_iConn, int a_iTarget)
{

	if (pMob[a_iConn].MOB.Coin < 2000000)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_snowimp_need_2MGold]);
		return;
	}

	int Materiais[5] = { 0, 0, 0, 0, 0 };

	for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex < 1721 || pMob[a_iConn].MOB.Carry[i].sIndex > 1725)
			continue;

		int Id = pMob[a_iConn].MOB.Carry[i].sIndex - 1721;

		Materiais[Id]++;
	}

	if (Materiais[0] < 10 || Materiais[1] < 2 || Materiais[2] < 4 || Materiais[3] < 1 || Materiais[4] < 1)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Need_5_materials]);
		return;
	}

	if (Materiais[0] > 10)
		Materiais[0] = 10;

	if (Materiais[1] > 2)
		Materiais[1] = 2;

	if (Materiais[2] > 4)
		Materiais[2] = 4;

	if (Materiais[3] > 1)
		Materiais[3] = 1;

	if (Materiais[4] > 1)
		Materiais[4] = 1;

	for (int x = 0; x < 5; x++)
	{
		for (int i = 0; i < pMob[a_iConn].MaxCarry && Materiais[x] > 0; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex == (1721 + x))
			{
				memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
				SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
				Materiais[x]--;
			}
		}
	}

	int TargetVillage = BASE_GetVillage(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY);

	if (TargetVillage >= 0 && TargetVillage < 5)
	{
		if (GuildImpostoID[TargetVillage] >= MAX_USER && GuildImpostoID[TargetVillage] < MAX_MOB && pMob[GuildImpostoID[TargetVillage]].Mode != USER_EMPTY && pMob[GuildImpostoID[TargetVillage]].MOB.Guild == g_pGuildZone[TargetVillage].ChargeGuild)
		{
			if (pMob[GuildImpostoID[TargetVillage]].MOB.Exp < 200000000000)
				pMob[GuildImpostoID[TargetVillage]].MOB.Exp += 2000000 / 10;
		}
	}

	pMob[a_iConn].MOB.Coin -= 2000000;
	SendEtc(a_iConn);

	STRUCT_ITEM Item;

	memset(&Item, 0, sizeof(STRUCT_ITEM));

	Item.sIndex = 1726;
	Item.stEffect[0].cEffect = 43;
	Item.stEffect[0].cValue = rand() % 4;

	PutItem(a_iConn, &Item);

	SendClientMsg(a_iConn, g_pMessageStringTable[_NN_snowimp_create_success]);

	sprintf(temp, "etc,arzan_dragon snowimp create name:%s level:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
	Log(temp, "-system", 0);
	return;
}
