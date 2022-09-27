#include "ProcessClientMessage.h"

void Exec_MSG_CombinetemDedekinto(int conn, char *pMsg)
{
	MSG_CombineItem *m = (MSG_CombineItem*)pMsg;

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
			MyLog(LogType::Combines, "err,msg_CombineDedekinto - item remove or changed.", pUser[conn].AccountName, 0, pUser[conn].IP);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	int combine = GetMatchCombineDedekinto(m->Item);

	//Pedra Amunra
	if (combine == 1 && (pMob[conn].MOB.Exp < 4020000000 || pMob[conn].Extra.ClassMaster == MORTAL || pMob[conn].Extra.ClassMaster == ARCH || pMob[conn].MOB.CurrentScore.Level <= 198))
	{	
		SendClientMsg(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	//Proteção Divina
	if (combine == 2 && (pMob[conn].Extra.ClassMaster == MORTAL || pMob[conn].Extra.ClassMaster == ARCH || pMob[conn].MOB.CurrentScore.Level <= 238))
	{	 
		SendClientMsg(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	for (int i = 0; i < MAX_COMBINE; i++)
	{
		if (m->Item[i].sIndex == 0)
			continue;

		memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
		SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
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


	int _rand = rand() % 115;
	if (_rand >= 100)
		_rand -= 15;

	int rate = g_pEhreRate[combine];

	if (_rand <= rate || LOCALSERVER)
	{
		if (combine == 1)
		{
			if (pMob[conn].Extra.ClassMaster >= CELESTIAL && pMob[conn].Extra.ClassMaster <= SCELESTIAL)
			{
				pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 3464;

				char tt[512];

				SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

				SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

				sprintf(temp, "%s ", pUser[conn].AccountName);
				BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);

				pMob[conn].MOB.BaseScore.Level = 0;
				pMob[conn].MOB.Exp = 0;

				pMob[conn].MOB.BaseScore.Str = BaseSIDCHM[pMob[conn].MOB.Class][0];
				pMob[conn].MOB.BaseScore.Int = BaseSIDCHM[pMob[conn].MOB.Class][1];
				pMob[conn].MOB.BaseScore.Dex = BaseSIDCHM[pMob[conn].MOB.Class][2];
				pMob[conn].MOB.BaseScore.Con = BaseSIDCHM[pMob[conn].MOB.Class][3];

				pMob[conn].MOB.BaseScore.Special[0] = 0;
				pMob[conn].MOB.BaseScore.Special[1] = 0;
				pMob[conn].MOB.BaseScore.Special[2] = 0;
				pMob[conn].MOB.BaseScore.Special[3] = 0;

				pMob[conn].MOB.BaseScore.Ac = 1004;
				pMob[conn].MOB.BaseScore.Damage = 400;
				pMob[conn].MOB.BaseScore.Hp = BaseSIDCHM[pMob[conn].MOB.Class][4];
				pMob[conn].MOB.BaseScore.MaxHp = BaseSIDCHM[pMob[conn].MOB.Class][4];
				pMob[conn].MOB.BaseScore.Mp = BaseSIDCHM[pMob[conn].MOB.Class][5];
				pMob[conn].MOB.BaseScore.MaxMp = BaseSIDCHM[pMob[conn].MOB.Class][5];

				pMob[conn].MOB.SpecialBonus = 855;

				SendEtc(conn);
				SendScore(conn);

				strcat(temp, tt);

				for (int i = 1; i < MAX_COMBINE; i++)
				{
					if (m->Item[i].sIndex == 0)
						continue;

					memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
					SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
				}

				MyLog(LogType::Combines, "*** combine dedekinto sucess ***", pUser[conn].AccountName, 0, pUser[conn].IP);
				SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);

				CharLogOut(conn);

				SendClientSignalParm(conn, ESCENE_FIELD, _MSG_SendArchEffect, pUser[conn].Slot);
				return;
			}

		}

		else if (combine == 2)
		{
			pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 679;

			char tt[512];

			SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);

			strcat(temp, tt);

			for (int i = 1; i < MAX_COMBINE; i++)
			{
				if (m->Item[i].sIndex == 0)
					continue;

				memset(&pMob[conn].MOB.Carry[m->InvenPos[i]], 0, sizeof(STRUCT_ITEM));
				SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[i], &pMob[conn].MOB.Carry[m->InvenPos[i]]);
			}

			MyLog(LogType::Combines, "*** combine dedekinto sucess ***", pUser[conn].AccountName, 0, pUser[conn].IP);
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);

			return;
		}

		char tt[256];
		SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);
		strcat(temp, tt);

		MyLog(LogType::Combines, "*** combine dedekinto falhou ***", pUser[conn].AccountName, 0, pUser[conn].IP);
		return;
	}
	else
	{

		sprintf(temp, "%s(%d/%d)", g_pMessageStringTable[_NN_CombineFailed], _rand, rate);
		SendClientMsg(conn, temp);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		MyLog(LogType::Combines, "*** combine dedekinto falhou ***", pUser[conn].AccountName, 0, pUser[conn].IP);
		return;
	}
}