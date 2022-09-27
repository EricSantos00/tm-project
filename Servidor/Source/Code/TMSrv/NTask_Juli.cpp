#include "ProcessClientMessage.h"

void NTask_Juli(int a_iConn, int a_iTarget)
{
	unsigned int tax = 500;
	unsigned int juliX = pMob[a_iTarget].LastX;
	unsigned int juliY = pMob[a_iTarget].LastY;
	int Village = BASE_GetVillage(pMob[a_iTarget].TargetX, pMob[a_iTarget].TargetY);
	int CityTax = g_pGuildZone[Village].CityTax;

	tax += (tax * CityTax) / 100;

	std::string taxFormat = GetFormatDecimal(tax);

	if (pMob[a_iConn].MOB.Coin < tax)
	{
		sprintf(temp, "Taxa de Teleport é de: [%s]", taxFormat.c_str());
		SendSay(a_iTarget, temp);
		return;
	}

	if (juliX >= 2479 && juliX <= 2484 && juliY >= 1644 && juliY <= 1648)//Arzam pra Gelo
	{
		DoTeleport(a_iConn, 3645 + rand() % 3, 3137 + rand() % 3);
		sprintf(temp, "Teleportado Para Gelo Taxa: [%s]", taxFormat.c_str());
		SendClientMsg(a_iConn, temp);
		pMob[a_iConn].MOB.Coin -= tax;
		SendEtc(a_iConn);
		return;
	}
	else //Gelo pra Arzam
	{
		DoTeleport(a_iConn, 2480 + rand() % 3, 1650 + rand() % 3);
		sprintf(temp, "Teleportado Para Arzam Taxa: [%s]", taxFormat.c_str());
		SendClientMsg(a_iConn, temp);
		pMob[a_iConn].MOB.Coin -= tax;
		SendEtc(a_iConn);
		return;
	}
	


	sprintf(temp, "etc,teleport:%s npc:%s ", pMob[a_iConn].MOB.MobName, pMob[a_iTarget].MOB.MobName);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}
