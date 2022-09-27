
#include "ProcessClientMessage.h"

void Exec_MSG_CombineItemLindy(int conn, char *pMsg)
{
	MSG_CombineItem *m = (MSG_CombineItem*)pMsg;

	unsigned famaReset370 = 1;

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		int invPos = m->InvenPos[i];

		if (invPos < 0 || invPos >= pMob[conn].MaxCarry)
		{
			RemoveTrade(conn);
			return;
		}

		if (memcmp(&pMob[conn].MOB.Carry[invPos], &m->Item[i], sizeof(STRUCT_ITEM)))
		{
			MyLog(LogType::Combines, "err,msg_CombineLindy - item remove or changed. ", pUser[conn].AccountName, 0, pUser[conn].IP);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	if (pMob[conn].Extra.ClassMaster != ARCH)
	{
		sprintf(temp, "Você não é Arch, não tenho quest para você, saia daqui...");
		SendClientMsg(conn, temp);
		return;
	}

	if (pMob[conn].MOB.CurrentScore.Level != 369 && pMob[conn].MOB.CurrentScore.Level != 354)
	{
		sprintf(temp, "Volte quando estiver no Lv. 355 ou Lv. 370...");
		SendClientMsg(conn, temp);
		return;
	}

	if ((pMob[conn].Extra.QuestInfo.Arch.Level355 == 1) && (pMob[conn].MOB.CurrentScore.Level >= 354 && pMob[conn].MOB.CurrentScore.Level < 369))
	{
		sprintf(temp, "Você já concluiu a quest do Lvl 355, volte no level 370");
		SendClientMsg(conn, temp);
		return;
	}

	if (pMob[conn].Extra.QuestInfo.Arch.Level370 == 0 && pMob[conn].MOB.CurrentScore.Level == 369 && pMob[conn].Extra.Fame <= 0)
	{
		sprintf(temp, "Necessário pelo menos [%d] de fama", famaReset370);
		SendClientMsg(conn, temp);
		return;
	}

	if (pMob[conn].Extra.QuestInfo.Arch.Level370 == 1 && pMob[conn].MOB.CurrentScore.Level == 369)
	{
		sprintf(temp, "Você já concluiu a quest do Lvl 370, suma daqui!!!");
		SendClientMsg(conn, temp);
		return;
	}


	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex)
		{
			char itemlog[2048];
									 
			BASE_GetItemCode(&m->Item[i], itemlog);
									 
			strcat(temp, itemlog);
		}
	}

	if(m->Item[0].sIndex == 413 && BASE_GetItemAmount(&m->Item[0]) == 10 && m->Item[1].sIndex == 413 && BASE_GetItemAmount(&m->Item[1]) == 10
	&& m->Item[2].sIndex == 4127 && m->Item[3].sIndex == 413 && m->Item[4].sIndex == 413 && m->Item[5].sIndex == 413 && m->Item[6].sIndex == 413)
	{

		for (int i = 0; i < MAX_COMBINE; i++)
		{
			if (m->Item[i].sIndex == 0)
				continue;

			memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
		}

		if(pMob[conn].MOB.CurrentScore.Level == 354)
		{
			pMob[conn].Extra.QuestInfo.Arch.Level355 = 1;

			memset(&pMob[conn].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));

			if(pMob[conn].MOB.Clan == 7)
				pMob[conn].MOB.Equip[15].sIndex = 3191;

			else if(pMob[conn].MOB.Clan == 8)
				pMob[conn].MOB.Equip[15].sIndex = 3192;

			else
				pMob[conn].MOB.Equip[15].sIndex = 3193;

			SendItem(conn, ITEM_PLACE_EQUIP, 15, &pMob[conn].MOB.Equip[15]);
		}
								 
		if(pMob[conn].MOB.CurrentScore.Level == 369)
		{
			pMob[conn].Extra.QuestInfo.Arch.Level370 = 1;
			pMob[conn].Extra.Fame -= 1;
		}
		sprintf(temp, "lindy,unlock lv%d", pMob[conn].MOB.CurrentScore.Level);
		MyLog(LogType::Combines, temp, pUser[conn].AccountName, 0, pUser[conn].IP);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		SendEmotion(conn, 14, 3);
		SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);
		return;
	}
}