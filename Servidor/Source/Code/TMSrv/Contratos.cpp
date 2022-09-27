#include "Contratos.h"

void itemContract(MSG_UseItem* m, STRUCT_ITEM* Item, int a_iConn)
{
	int slotVago = GetFirstSlotBag(a_iConn);

	if (!slotVago)
	{
		SendClientMsg(a_iConn, "Você não tem espaço suficiente na mochila");
		SendItem(a_iConn, m->SourType, m->SourPos, Item);
		return;
	}
	STRUCT_ITEM itemReceive;
	switch (Item->sIndex)
	{
	case 3790://Contrato Sem Sela N
		itemReceive.sIndex = 2366;
		itemReceive.stEffect[0].cEffect = 100;
		itemReceive.stEffect[0].cValue = 100;
		itemReceive.stEffect[1].cEffect = 5;
		itemReceive.stEffect[1].cValue = 10;
		itemReceive.stEffect[2].cEffect = 0;
		itemReceive.stEffect[2].cValue = 0;
		break;
	case 3791://Contrato Sem Sela B
		itemReceive.sIndex = 2371;
		itemReceive.stEffect[0].cEffect = 100;
		itemReceive.stEffect[0].cValue = 100;
		itemReceive.stEffect[1].cEffect = 5;
		itemReceive.stEffect[1].cValue = 10;
		itemReceive.stEffect[2].cEffect = 0;
		itemReceive.stEffect[2].cValue = 0;
		break;
	case 3792://Contrato Macro eternal 7d
		itemReceive.sIndex = 3789;
		itemReceive.stEffect[0].cEffect = 0;
		itemReceive.stEffect[0].cValue = 0;
		itemReceive.stEffect[1].cEffect = 0;
		itemReceive.stEffect[1].cValue = 0;
		itemReceive.stEffect[2].cEffect = 0;
		itemReceive.stEffect[2].cValue = 0;
		break;
	default:
		break;
	}

	PutItem(a_iConn, &itemReceive);

	memset(Item, 0, sizeof(STRUCT_ITEM));

	SendItem(a_iConn, m->SourType, m->SourPos, Item);


	sprintf(temp, "useitem,item contrato type: %d", Item->sIndex);
	MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
}
