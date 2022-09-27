#include "Events.h"

void itemJoiasEvent(MSG_UseItem* m, STRUCT_ITEM* Item, int a_iConn)
{

	if (Item->sIndex == 3794)
	{
		std::vector<short> premio{
									2441,//Diamante 
									2442,//Esmeralda 
									2443,//Coral
									2444 //Garnet 
								};
		int slotVago = GetFirstSlotBag(a_iConn);

		if (!slotVago)
		{
			SendClientMsg(a_iConn, "Você não tem espaço suficiente na mochila");
			SendItem(a_iConn, m->SourType, m->SourPos, Item);
			return;
		}
		int sortItem = premio[rand() % 4];
		STRUCT_ITEM itemReceive;

		itemReceive.sIndex = sortItem;
		itemReceive.stEffect[0].cEffect = 0;
		itemReceive.stEffect[0].cValue = 0;
		itemReceive.stEffect[1].cEffect = 0;
		itemReceive.stEffect[1].cValue = 0;
		itemReceive.stEffect[2].cEffect = 0;
		itemReceive.stEffect[2].cValue = 0;

		PutItem(a_iConn, &itemReceive);

		memset(Item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, m->SourType, m->SourPos, Item);


		sprintf(temp, "useitem,item contrato type: %d", Item->sIndex);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
	if (Item->sIndex == 3793)
	{

		std::vector<short> premio{
									2441,//Diamante 
									2442,//Esmeralda 
									2443,//Coral
									2444 //Garnet 
								};
		int slotsVago = GetSlotsVagoBag(a_iConn);

		if (slotsVago < 5)
		{
			SendClientMsg(a_iConn, "Precisa de pelo menos 5 slots vago na mochila.");
			SendItem(a_iConn, m->SourType, m->SourPos, Item);
			return;
		}
		int sortItem = premio[rand() % 4];
		STRUCT_ITEM itemReceive;

		itemReceive.sIndex = sortItem;
		itemReceive.stEffect[0].cEffect = 0;
		itemReceive.stEffect[0].cValue = 0;
		itemReceive.stEffect[1].cEffect = 0;
		itemReceive.stEffect[1].cValue = 0;
		itemReceive.stEffect[2].cEffect = 0;
		itemReceive.stEffect[2].cValue = 0;

		//loop para inserir 5 itens
		for (size_t i = 0; i < 5; i++)
		{
			if (i > 3)
				itemReceive.sIndex = 1774;

			PutItem(a_iConn, &itemReceive);
		}
	
		memset(Item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, m->SourType, m->SourPos, Item);


		sprintf(temp, "useitem,item contrato type: %d", Item->sIndex);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}
}

void boxEvent(MSG_UseItem* m, STRUCT_ITEM* Item, int a_iConn)
{
	DWORD itemRand;

	int slotVago = GetFirstSlotBag(a_iConn);
	if (!slotVago)
	{
		SendClientMsg(a_iConn, "Você não tem espaço suficiente na mochila");
		SendItem(a_iConn, m->SourType, m->SourPos, Item);
		return;
	}
	//Box N
	if (Item->sIndex == 3210)
	{
		itemRand = rand() % MAX_BOX_N;
		
		PutItem(a_iConn, &BoxEvent[0][itemRand]);

		memset(Item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, m->SourType, m->SourPos, Item);

		sprintf(temp, "useitem,item BoxEvent type: %d", Item->sIndex);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;

	}
	//Box M
	if (Item->sIndex == 3211)
	{
		itemRand = rand() % MAX_BOX_M;

		PutItem(a_iConn, &BoxEvent[1][itemRand]);

		memset(Item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, m->SourType, m->SourPos, Item);

		sprintf(temp, "useitem,item BoxEvent type: %d", Item->sIndex);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;

	}
	//Box A
	if (Item->sIndex == 3212)
	{
		itemRand = rand() % MAX_BOX_A;

		PutItem(a_iConn, &BoxEvent[2][itemRand]);

		memset(Item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, m->SourType, m->SourPos, Item);

		sprintf(temp, "useitem,item BoxEvent type: %d", Item->sIndex);
		MyLog(LogType::Itens, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;

	}
}
