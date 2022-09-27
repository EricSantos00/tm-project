#include "BoxPremium.h"

void bagWarrior(MSG_UseItem* m, STRUCT_ITEM* Item, int a_iConn)
{
	int bagSize = sizeof(sbagWarrior) / sizeof(sbagWarrior[0]);
	int slotsVago = GetSlotsVagoBag(a_iConn);

	if (slotsVago <= bagSize)
	{
		SendClientMsg(a_iConn, "Precisa de pelo menos 6 slots vago na mochila.");
		SendItem(a_iConn, m->SourType, m->SourPos, Item);
		return;
	}

	for (size_t i = 0; i < bagSize; i++)
	{
		PutItem(a_iConn, &sbagWarrior[i]);
	}

	memset(Item, 0, sizeof(STRUCT_ITEM));

	SendItem(a_iConn, m->SourType, m->SourPos, Item);

	sprintf(temp, "!Você recebeu os seguintes itens: [%s],[%s],[%s],[%s],[%s],[%s]", g_pItemList[sbagWarrior[0].sIndex].Name,
		g_pItemList[sbagWarrior[1].sIndex].Name, g_pItemList[sbagWarrior[2].sIndex].Name, g_pItemList[sbagWarrior[3].sIndex].Name, 
		g_pItemList[sbagWarrior[4].sIndex].Name, g_pItemList[sbagWarrior[5].sIndex].Name);

	sprintf(temp, "useitem,item contrato type: %d", Item->sIndex);
	MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
	return;
}
