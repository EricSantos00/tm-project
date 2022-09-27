
#include "ProcessClientMessage.h"

void Exec_MSG_SplitItem(int conn, char *pMsg)
{
	MSG_SplitItem *m = (MSG_SplitItem*)pMsg;

	if (m->Slot < 0 || m->Slot >= MAX_CARRY - 4)
		return;

	if (m->Num <= 0 || m->Num >= 120)
		return;

	if (pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(conn);
		return;
	}

	int slot = m->Slot;
	int isAmmount = FALSE;
	for (size_t i = 0; i < 100; i++)
	{
		if (pMob[conn].MOB.Carry[slot].sIndex == groupItens[i])
		{
			isAmmount = TRUE;
			break;
		}

	}

	/*if(pMob[conn].MOB.Carry[slot].sIndex != 413 && pMob[conn].MOB.Carry[slot].sIndex != 412
	&& pMob[conn].MOB.Carry[slot].sIndex != 419 && pMob[conn].MOB.Carry[slot].sIndex != 420
	&& (pMob[conn].MOB.Carry[slot].sIndex < 2390 || pMob[conn].MOB.Carry[slot].sIndex > 2419))
	{
		Log("splititem, no validitem", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}*/

	if (!isAmmount)
	{
		Log("splititem, no validitem", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	int amount = BASE_GetItemAmount(&pMob[conn].MOB.Carry[slot]);

	if(m->Num < 0 || m->Num > 120)
	{
		Log("splititem, invalid num", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	int x = 0;
	int invfree = 0;

	for (x = 0; x < pMob[conn].MaxCarry; x++)
	{
		if(pMob[conn].MOB.Carry[x].sIndex == 0)
			invfree++;
	}

	if(invfree < 1)
		return;

	if(amount == 0 || amount == 1 || amount <= m->Num)
		return;
							 
	sprintf(temp, "splititem, itemindex:%d amount:%d num:%d", pMob[conn].MOB.Carry[slot].sIndex, amount, m->Num);
	MyLog(LogType::Itens, pMob[conn].MOB.MobName, temp, 0, pUser[conn].IP);

	if (amount > 1)
		BASE_SetItemAmount(&pMob[conn].MOB.Carry[slot], amount - m->Num);

	else
		memset(&pMob[conn].MOB.Carry[slot], 0, sizeof(STRUCT_ITEM));

	STRUCT_ITEM nItem;

	memset(&nItem, 0, sizeof(STRUCT_ITEM));

	nItem.sIndex = pMob[conn].MOB.Carry[slot].sIndex;
							 
	BASE_SetItemAmount(&nItem, m->Num);

	PutItem(conn, &nItem);
	SendItem(conn, ITEM_PLACE_CARRY, slot, &pMob[conn].MOB.Carry[slot]);
	return;
}