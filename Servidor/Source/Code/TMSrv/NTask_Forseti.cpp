#include "ProcessClientMessage.h"

void NTask_Forseti(int a_iConn, int a_iTarget, int confirm)
{
	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	if (confirm == 0)
		return;
	
	for (int i = 0; i < 3; i++)
	{
		if (g_calabouco.Party[i].LeaderID == a_iConn && strcmp(g_calabouco.Party[i].LeaderName, pMob[a_iConn].MOB.MobName) == 0)
		{
			sprintf(temp, "Quest comecará em breve!.");
			SendClientMsg(a_iConn, temp);
			return;
		}
	}

	if (!(when.tm_min >= 56 && when.tm_min <= 59))
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
		if (pMob[a_iConn].MOB.Carry[i].sIndex != 5549)
			continue;

		break;
	}

	if (i == pMob[a_iConn].MaxCarry)
	{
		sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[5549].Name);
		SendSay(a_iTarget, temp);
		return;
	}

	for (int i = 0; i < 3; i++)
	{
		if (g_calabouco.Party[i].LeaderID == 0)
		{
			g_calabouco.Party[i].LeaderID = a_iConn;
			strncpy(g_calabouco.Party[i].LeaderName, pMob[a_iConn].MOB.MobName, NAME_LENGTH);

			break;
		}

		if (i != 3)
		{
			SendClientMsg(a_iTarget, g_pMessageStringTable[_NN_Night_Already]);
			return;
		}
	}

	sprintf(temp, "%s Registrou Calabouço type:%d conn:%d  level:%d", pMob[a_iConn].MOB.MobName, sala, a_iConn, pMob[a_iConn].MOB.BaseScore.Level);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

	BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);
	SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
	SendClientMsg(a_iConn, g_pMessageStringTable[_NN_TicketUsed]);
	return;
}
