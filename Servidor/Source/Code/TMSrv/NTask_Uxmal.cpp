#include "ProcessClientMessage.h"

void NTask_Uxmal(int a_iConn, int a_iTarget)
{
	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);


	if (!NPCBlock[Uxmall])
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_NPCBLOCKED]);
		return;
	}

	if (when.tm_min >= 0 && when.tm_min <= 15 || when.tm_min >= 20 && when.tm_min <= 35 || when.tm_min >= 40 && when.tm_min <= 55)
	{
		SendSay(a_iTarget, g_pMessageStringTable[_NN_Night_Already]);
		return;
	}

	if (pMob[a_iConn].Leader != -1 && pMob[a_iConn].Leader)
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Party_Leader_Only]);
		return;
	}

	int i = 0;

	int sala = -1;

	for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex != 5134)
			continue;

		sala = BASE_GetItemSanc(&pMob[a_iConn].MOB.Carry[i]);

		if (sala > 6)
			sala = 6;

		if (sala < 0)
			sala = 0;

		break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[5134].Name);
		SendSay(a_iTarget, temp);
		return;
	}
	int j = 0;

	for (j = 0; j < (sala == 0 ? 2 : 3); j++)
	{
		if (Pista[sala].Party[j].LeaderID == 0)
			break;
	}

	if (j == (sala == 0 ? 2 : 3))
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Night_Limited]);
		return;
	}

	int c = 0;
	for (c = 0; c < 3; c++)
	{
		if (Pista[sala].Party[c].LeaderID == a_iConn)
			break;
	}

	if (c != 3)
	{
		SendClientMsg(a_iTarget, g_pMessageStringTable[_NN_Night_Already]);
		return;
	}

	if (Pista[sala].Party[j].LeaderID == a_iConn && strcmp(Pista[sala].Party[j].LeaderName, pMob[a_iConn].MOB.MobName) == 0)
	{
		sprintf(temp, "Quest comecará em breve!.");
		SendClientMsg(a_iConn, temp);
		return;
	}

	sprintf(temp, "%s Registrou RuneQuest type:%d conn:%d  level:%d", pMob[a_iConn].MOB.MobName, sala, a_iConn, pMob[a_iConn].MOB.BaseScore.Level);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

	Pista[sala].Party[j].LeaderID = a_iConn;
	Pista[sala].Party[j].MobCount = 0;
	Pista[sala].Party[j].Sala = sala;
	strncpy(Pista[sala].Party[j].LeaderName, pMob[a_iConn].MOB.MobName, NAME_LENGTH);

	BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);
	SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
	SendClientMsg(a_iConn, g_pMessageStringTable[_NN_TicketUsed]);
	return;
}