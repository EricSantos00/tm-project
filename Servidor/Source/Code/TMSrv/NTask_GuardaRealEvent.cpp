#include "ProcessClientMessage.h"

void NTask_QuestGuardaEventos(int a_iConn, int a_iTarget)
{
	int Level = pMob[a_iTarget].MOB.BaseScore.Level;

	if (Level < FALSE || Level >= MAX_NPC_GUARD_COUT) return;

	if (g_pGuard[Level].Req.Parm0 <= 0)
	{
		SendSay(a_iTarget, "Desculpe. Fui desativado.");

		return;
	}

	srand(time(NULL) / 5 * (rand() % 500) * 5);

	int Drawly = rand() % 115;
	if (Drawly >= 100)
		Drawly -= 15;

	//int Drawly = rand() % 100 + 1;

	int Parm0 = g_pGuard[Level].Req.Parm0;
	int Slot0 = -1;

	for (int i = 0; i < MAX_CARRY - 4; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex != Parm0) continue;

		Slot0 = i;

		break;
	}

	int Parm1 = g_pGuard[Level].Req.Parm1;
	int Slot1 = -1;

	if (Parm1 > 0)
	{
		for (int i = 0; i < MAX_CARRY - 4; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex != Parm1) continue;

			Slot1 = i;

			break;
		}
	}

	int Parm2 = g_pGuard[Level].Req.Parm2;
	int Slot2 = -1;

	if (Parm2 > 0)
	{
		for (int i = 0; i < MAX_CARRY - 4; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex != Parm2) continue;

			Slot2 = i;

			break;
		}
	}

	int Parm3 = g_pGuard[Level].Req.Parm3;
	int Slot3 = -1;

	if (Parm3 > 0)
	{
		for (int i = 0; i < MAX_CARRY - 4; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex != Parm3) continue;

			Slot3 = i;

			break;
		}
	}

	int Parm4 = g_pGuard[Level].Req.Parm4;
	int Slot4 = -1;

	if (Parm4 > 0)
	{
		for (int i = 0; i < MAX_CARRY - 4; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex != Parm4) continue;

			Slot4 = i;

			break;
		}
	}

	if (Parm0 > 0 && Slot0 == -1)
	{
		sprintf(temp, "Traga-me o item, [%s].", g_pItemList[Parm0].Name);
		SendSay(a_iTarget, temp);

		return;
	}

	if (Parm1 > 0 && Slot1 == -1)
	{
		sprintf(temp, "Hum... Ainda falta você me trazer, [%s].", g_pItemList[Parm1].Name);
		SendSay(a_iTarget, temp);

		return;
	}

	if (Parm2 > 0 && Slot2 == -1)
	{
		sprintf(temp, "Estamos quase lá! Me traga o item [%s].", g_pItemList[Parm2].Name);
		SendSay(a_iTarget, temp);

		return;
	}

	if (Parm3 > 0 && Slot3 == -1)
	{
		sprintf(temp, "Estou quase concluindo a troca, traga-me o item [%s].", g_pItemList[Parm3].Name);
		SendSay(a_iTarget, temp);

		return;
	}

	if (Parm4 > 0 && Slot4 == -1)
	{
		sprintf(temp, "Agora para finalizar, traga-me o item [%s].", g_pItemList[Parm4].Name);
		SendSay(a_iTarget, temp);

		return;
	}

	for (int j = MAX_NPC_GUARD_ITEM; j >= FALSE; j--)
	{
		if (g_pGuard[Level].Sub.Item[j].sIndex <= 330 || g_pGuard[Level].Sub.Item[j].sIndex >= MAX_ITEMLIST) continue;

		if (Drawly <= g_pGuard[Level].Sub.Ratting[j] || LOCALSERVER)
		{
			if (Slot0 >= 0) { BASE_ClearItem(&pMob[a_iConn].MOB.Carry[Slot0]); SendItem(a_iConn, ITEM_PLACE_CARRY, Slot0, &pMob[a_iConn].MOB.Carry[Slot0]); }
			if (Slot1 >= 0) { BASE_ClearItem(&pMob[a_iConn].MOB.Carry[Slot1]); SendItem(a_iConn, ITEM_PLACE_CARRY, Slot1, &pMob[a_iConn].MOB.Carry[Slot1]); }
			if (Slot2 >= 0) { BASE_ClearItem(&pMob[a_iConn].MOB.Carry[Slot2]); SendItem(a_iConn, ITEM_PLACE_CARRY, Slot2, &pMob[a_iConn].MOB.Carry[Slot2]); }
			if (Slot3 >= 0) { BASE_ClearItem(&pMob[a_iConn].MOB.Carry[Slot3]); SendItem(a_iConn, ITEM_PLACE_CARRY, Slot3, &pMob[a_iConn].MOB.Carry[Slot3]); }
			if (Slot4 >= 0) { BASE_ClearItem(&pMob[a_iConn].MOB.Carry[Slot4]); SendItem(a_iConn, ITEM_PLACE_CARRY, Slot4, &pMob[a_iConn].MOB.Carry[Slot4]); }

			memcpy(&pMob[a_iConn].MOB.Carry[Slot0], &g_pGuard[Level].Sub.Item[j], sizeof(STRUCT_ITEM));

			SendItem(a_iConn, ITEM_PLACE_CARRY, Slot0, &pMob[a_iConn].MOB.Carry[Slot0]);

			sprintf(temp, "Parabéns, %s.", pMob[a_iConn].MOB.MobName);

			SendSay(a_iTarget, temp);

			sprintf(temp, g_pMessageStringTable[_SN_Item_Arrived], g_pItemList[g_pGuard[Level].Sub.Item[j].sIndex].Name);

			SendClientMsg(a_iConn, temp);

			return;
		}
	}


	sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[g_pGuard[Level].Req.Parm0].Name);
	SendSay(a_iTarget, temp);

	return;
}
