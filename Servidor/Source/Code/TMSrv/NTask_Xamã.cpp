#include "ProcessClientMessage.h"

void NTask_Xamã(int a_iConn, int a_iTarget, int confirm)
{
	struct tm when;
	time_t now;
	time(&now);
	when = *localtime(&now);

	if (confirm == 0)
		return;

	if (nColiseu[0].Days[when.tm_wday])
	{

		//int i = 0;

		STRUCT_ITEM* reqItem = GetFirstItemBag(a_iConn, 3170);

		//for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
		//{
			//if (pMob[a_iConn].MOB.Carry[i].sIndex != 3170)
				//continue;

			//break;
		//}

	//	if (i == pMob[a_iConn].MaxCarry)
		if (reqItem == nullptr)
		{
			sprintf(temp, g_pMessageStringTable[_SN_BRINGITEM], g_pItemList[3170].Name);
			SendSay(a_iTarget, temp);
			return;
		}

		int amount = BASE_GetItemAmount(reqItem);
		//if (NewbieEventServer)
		//{
		if ((when.tm_hour == nColiseu->Hour[0] || when.tm_hour == nColiseu->Hour[1]) && when.tm_min <= 9)
		{
			DoTeleport(a_iConn, 3522 + rand() % 5 - 3, 1471 + rand() % 5 - 3);

			MSG_STANDARDPARM sm;
			memset(&sm, 0, sizeof(MSG_STANDARDPARM));

			sm.Type = _MSG_StartTime;
			sm.ID = ESCENE_FIELD;
			sm.Size = sizeof(MSG_STANDARDPARM);
			sm.Parm = 1200;

			MapaMulticast(27, 11, (MSG_STANDARD*)&sm, 0);
		}
		else
		{
			sprintf(temp, "Volte ás [%d] ou [%d] minuto 0 á 9", nColiseu->Hour[0], nColiseu->Hour[1]);
			SendSay(a_iTarget, temp);
			return;
		}
		//}
		//else
		//{
		//	SendSay(a_iTarget, g_pMessageStringTable[_NN_NEWBIEEVENTSERVER]);
		//	return;
		//}

		sprintf(temp, "etc,questColiseuN ticket xamã name:%s level:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
		MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

		//BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);
		if (amount > 1)
			BASE_SetItemAmount(reqItem, amount - 1);

		else
			memset(reqItem, 0, sizeof(STRUCT_ITEM));

		//SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
		return;
	}
	return;
}
