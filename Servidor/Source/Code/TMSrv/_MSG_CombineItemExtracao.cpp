
#include "ProcessClientMessage.h"

void Exec_MSG_CombineItemExtracao(int conn, char *pMsg)
{
	MSG_STANDARDPARM2 *m = (MSG_STANDARDPARM2*)pMsg;

	int ItemSlot = m->Parm2;

	if (ItemSlot < 0 || ItemSlot >= pMob[conn].MaxCarry)
		return;

	int item = pMob[conn].MOB.Carry[ItemSlot].sIndex;

	if(item <= 0 || item >= MAX_ITEMLIST)
		return;

	int itemlevel = BASE_GetItemAbility(&pMob[conn].MOB.Carry[ItemSlot], EF_ITEMLEVEL);

	if (itemlevel >= 5)
		return;

	/*if(BASE_GetItemSanc(&pMob[conn].MOB.Carry[ItemSlot]) < 9)
		return;*/

	if((g_pItemList[item].nPos != 2 && g_pItemList[item].nPos != 4 && g_pItemList[item].nPos != 8 && g_pItemList[item].nPos != 16 && g_pItemList[item].nPos != 32) || BASE_GetItemAbility(&pMob[conn].MOB.Carry[ItemSlot], EF_MOBTYPE) != 0)
		return;

	int i = 0;

	for (i = 0; i < pMob[conn].MaxCarry; i++)
	{
		if (pMob[conn].MOB.Carry[i].sIndex != 1774)
			continue;

		BASE_ClearItem(&pMob[conn].MOB.Carry[i]);
		SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
		break;
	}

	if (i == pMob[conn].MaxCarry)
		return;
		
	int _rnd = rand()%115;

	if(_rnd > 100)
		_rnd -= 15;

	int rate = (pMob[conn].MOB.CurrentScore.Special[2] + 1) / 3;
	
	if(_rnd < rate)
	{
		pMob[conn].MOB.Carry[ItemSlot].stEffect[0].cEffect = EF_ITEMLEVEL;
		pMob[conn].MOB.Carry[ItemSlot].stEffect[0].cValue = itemlevel;

		if(pMob[conn].MOB.Carry[ItemSlot].stEffect[1].cEffect == EF_DAMAGE)
			pMob[conn].MOB.Carry[ItemSlot].stEffect[1].cValue += BASE_GetStaticItemAbility(&pMob[conn].MOB.Carry[ItemSlot], EF_DAMAGE);

		if(pMob[conn].MOB.Carry[ItemSlot].stEffect[2].cEffect == EF_DAMAGE)
			pMob[conn].MOB.Carry[ItemSlot].stEffect[2].cValue += BASE_GetStaticItemAbility(&pMob[conn].MOB.Carry[ItemSlot], EF_DAMAGE);

		pMob[conn].MOB.Carry[ItemSlot].sIndex = 3021;

		if(g_pItemList[item].nPos == 4)
			pMob[conn].MOB.Carry[ItemSlot].sIndex++;

		else if(g_pItemList[item].nPos == 8)
			pMob[conn].MOB.Carry[ItemSlot].sIndex += 2;

		else if(g_pItemList[item].nPos == 16)
			pMob[conn].MOB.Carry[ItemSlot].sIndex += 3;

		else if(g_pItemList[item].nPos == 32)
			pMob[conn].MOB.Carry[ItemSlot].sIndex += 4;

		SendItem(conn, ITEM_PLACE_CARRY, ItemSlot, &pMob[conn].MOB.Carry[ItemSlot]);

		char tt[256];
		sprintf(temp, "%s ", pUser[conn].AccountName);
		BASE_GetItemCode(&pMob[conn].MOB.Carry[ItemSlot], tt);
		strcat(temp, tt);
		MyLog(LogType::Combines, "*** Combine ht_skill_Extração sucess *** ", pUser[conn].AccountName, 0, pUser[conn].IP);
	}
	else
	{
		BASE_ClearItem(&pMob[conn].MOB.Carry[ItemSlot]);
		SendItem(conn, ITEM_PLACE_CARRY, ItemSlot, &pMob[conn].MOB.Carry[ItemSlot]);
		MyLog(LogType::Combines, "*** Combine ht_skill_Extração fail *** ", pUser[conn].AccountName, 0, pUser[conn].IP);

	}
}