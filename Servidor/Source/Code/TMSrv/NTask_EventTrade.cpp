#include "ProcessClientMessage.h"

void NTask_EventTrade(int a_iConn, int a_iTarget, int NpcGrade)
{
	//srand(time(NULL));
	DWORD npc1Rand = rand() % EventTrade.NPC1.BaseRand;
	DWORD npc2Rand = rand() % EventTrade.NPC2.BaseRand;
	DWORD npc3Rand = rand() % EventTrade.NPC3.BaseRand;
	DWORD npc4Rand = rand() % EventTrade.NPC4.BaseRand;
	DWORD npc5Rand = rand() % EventTrade.NPC5.BaseRand;
	DWORD rate1 = 0;
	DWORD rate2 = 0;
	DWORD rate3 = 0;
	DWORD rate4 = 0;
	DWORD rate5 = 0;
	int idItem = 0;
	//rProcess:
	STRUCT_ITEM itemReceiv;
	memset(&itemReceiv, 0, sizeof(STRUCT_ITEM));
	//memset(temp, 0, 4096);
	switch (NpcGrade)
	{
	case 43:
		rate1 = EventTrade.NPC1.Rates[0];
		rate2 = rate1 + EventTrade.NPC1.Rates[1];
		rate3 = rate2 + EventTrade.NPC1.Rates[2];
		rate4 = rate3 + EventTrade.NPC1.Rates[3];
		rate5 = rate4 + EventTrade.NPC1.Rates[4];
		idItem = EventTrade.NPC1.ItemReceive.sIndex;

		if (npc1Rand < rate1)
			itemReceiv = EventTrade.NPC1.Reward[0];

		else if (npc1Rand <= rate2)
			itemReceiv = EventTrade.NPC1.Reward[1];

		else if (npc1Rand <= rate3)
			itemReceiv = EventTrade.NPC1.Reward[2];

		else if (npc1Rand <= rate4)
			itemReceiv = EventTrade.NPC1.Reward[3];

		else if (npc1Rand <= rate5)
			itemReceiv = EventTrade.NPC1.Reward[4];

		break;
	case 44:
		rate1 = EventTrade.NPC2.Rates[0];
		rate2 = rate1 + EventTrade.NPC2.Rates[1];
		rate3 = rate2 + EventTrade.NPC2.Rates[2];
		rate4 = rate3 + EventTrade.NPC2.Rates[3];
		rate5 = rate4 + EventTrade.NPC2.Rates[4];
		idItem = EventTrade.NPC2.ItemReceive.sIndex;

		if (npc2Rand < rate1)
			itemReceiv = EventTrade.NPC2.Reward[0];

		else if (npc2Rand <= rate2)
			itemReceiv = EventTrade.NPC2.Reward[1];

		else if (npc2Rand <= rate3)
			itemReceiv = EventTrade.NPC2.Reward[2];

		else if (npc2Rand <= rate4)
			itemReceiv = EventTrade.NPC2.Reward[3];

		else if (npc2Rand <= rate5)
			itemReceiv = EventTrade.NPC2.Reward[4];
		break;
	case 45:
		rate1 = EventTrade.NPC3.Rates[0];
		rate2 = rate1 + EventTrade.NPC3.Rates[1];
		rate3 = rate2 + EventTrade.NPC3.Rates[2];
		rate4 = rate3 + EventTrade.NPC3.Rates[3];
		rate5 = rate4 + EventTrade.NPC3.Rates[4];
		idItem = EventTrade.NPC3.ItemReceive.sIndex;

		if (npc3Rand < rate1)
			itemReceiv = EventTrade.NPC3.Reward[0];

		else if (npc3Rand <= rate2)
			itemReceiv = EventTrade.NPC3.Reward[1];

		else if (npc3Rand <= rate3)
			itemReceiv = EventTrade.NPC3.Reward[2];

		else if (npc3Rand <= rate4)
			itemReceiv = EventTrade.NPC3.Reward[3];

		else if (npc3Rand <= rate5)
			itemReceiv = EventTrade.NPC3.Reward[4];

		break;
	case 46:
		rate1 = EventTrade.NPC4.Rates[0];
		rate2 = rate1 + EventTrade.NPC4.Rates[1];
		rate3 = rate2 + EventTrade.NPC4.Rates[2];
		rate4 = rate3 + EventTrade.NPC4.Rates[3];
		rate5 = rate4 + EventTrade.NPC4.Rates[4];
		idItem = EventTrade.NPC4.ItemReceive.sIndex;

		if (npc4Rand < rate1)
			itemReceiv = EventTrade.NPC4.Reward[0];

		else if (npc4Rand <= rate2)
			itemReceiv = EventTrade.NPC4.Reward[1];

		else if (npc4Rand <= rate3)
			itemReceiv = EventTrade.NPC4.Reward[2];

		else if (npc4Rand <= rate4)
			itemReceiv = EventTrade.NPC4.Reward[3];

		else if (npc4Rand <= rate5)
			itemReceiv = EventTrade.NPC4.Reward[4];

		break;
	case 47:
		rate1 = EventTrade.NPC5.Rates[0];
		rate2 = rate1 + EventTrade.NPC5.Rates[1];
		rate3 = rate2 + EventTrade.NPC5.Rates[2];
		rate4 = rate3 + EventTrade.NPC5.Rates[3];
		rate5 = rate4 + EventTrade.NPC5.Rates[4];
		idItem = EventTrade.NPC5.ItemReceive.sIndex;

		if (npc5Rand < rate1)
			itemReceiv = EventTrade.NPC5.Reward[0];

		else if (npc5Rand <= rate2)
			itemReceiv = EventTrade.NPC5.Reward[1];

		else if (npc5Rand <= rate3)
			itemReceiv = EventTrade.NPC5.Reward[2];

		else if (npc5Rand <= rate4)
			itemReceiv = EventTrade.NPC5.Reward[3];

		else if (npc5Rand <= rate5)
			itemReceiv = EventTrade.NPC5.Reward[4];

		break;
	default:
		break;
	}

	for (size_t i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex != idItem)
			continue;

		if (!GetSlotsVagoBag(a_iConn))
		{
			//sprintf(temp, EventTrade.MsgBag);
			SendSay(a_iTarget, strFmt(EventTrade.MsgBag.c_str()));
			SendCarry(a_iConn);
			return;
		}


		STRUCT_ITEM* item = GetFirstItemBag(a_iConn, idItem);

		if (item == nullptr)
			continue;

		int amount = BASE_GetItemAmount(item);

		if (amount > 1)
			BASE_SetItemAmount(item, amount - 1);
		else
			memset(item, 0, sizeof(STRUCT_ITEM));

		SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);

		PutItem(a_iConn, &itemReceiv);

		sprintf(temp, "Parabens voce recebeu [%s] no evento de troca", g_pItemList[itemReceiv.sIndex].Name);
		//SendSay(a_iTarget, temp);
		SendMsgExp(a_iConn, temp, TNColor::CornflowerBlue, false);

		sprintf(temp, "itens,event trade :%s item:%d", pMob[a_iConn].MOB.MobName, itemReceiv.sIndex);
		MyLog(LogType::Itens, temp, 0, 0, pUser[a_iConn].IP);
		break;
		//goto rProcess;
	}

	SendCarry(a_iConn);

	//sprintf(temp, EventTrade.MsgErr, g_pItemList[idItem].Name);
	SendSay(a_iTarget, strFmt(EventTrade.MsgErr.c_str(), g_pItemList[idItem].Name));
	return;


}

void NTask_StartEventTrade()
{
	time_t rawtime;
	tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (EventTrade.Days[timeinfo->tm_wday])
	{
		if (timeinfo->tm_hour >= EventTrade.HourStart && timeinfo->tm_min >= EventTrade.MinStart
			&& timeinfo->tm_hour < EventTrade.HourEnd && !EventTrade.started)
		{
			EventTrade.started = TRUE;
			int init = EVENT_TRADE_NPC1_INIT;
			int end = EVENT_TRADE_NPC1_END;
			for (int i = init; i <= end; i++)
			{
				GenerateMob(i, 0, 0);
			}

			//sprintf(temp, EventTrade.MSGStart);
			SendNotice(strFmt(EventTrade.MSGStart.c_str()));

		}

		if (timeinfo->tm_hour >= EventTrade.HourEnd && timeinfo->tm_min >= EventTrade.MinEnd
			&& EventTrade.started)
		{
			EventTrade.started = FALSE;

			for (int i = MAX_USER; i < MAX_MOB; i++)
			{
				if (pMob[i].GenerateIndex >= EVENT_TRADE_NPC1_INIT && pMob[i].GenerateIndex <= EVENT_TRADE_NPC1_END)
				{
					DeleteMob(i, 1);

				}
			}

			//sprintf(temp, EventTrade.MSGEnd);
			SendNotice(strFmt(EventTrade.MSGEnd.c_str()));

		}
	}
}
