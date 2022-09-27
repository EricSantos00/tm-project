#include "ProcessClientMessage.h"

void Exec_MSG_CombineItemEhre(int conn, char *pMsg)
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
			MyLog(LogType::Combines, "err,msg_CombineEhre - item remove or changed.", pUser[conn].AccountName, 0, pUser[conn].IP);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	int combine = GetMatchCombineEhre(m->Item);

	if (combine == 0)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	//Ref Aben�oada
	if (combine == 5 && (pMob[conn].MOB.Exp < 5000000 || pMob[conn].Extra.ClassMaster == MORTAL || pMob[conn].Extra.ClassMaster == ARCH || pMob[conn].MOB.CurrentScore.Level < 39))
	{	 
		SendClientMsg(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	if ((combine == 6 || combine == 7) && pMob[conn].MOB.Coin < 1000000)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}
			
	if(combine == 3 || combine == 4)
	{
		int hp = BASE_GetItemAbilityNosanc(&m->Item[2], EF_HPADD2);
		int mp = BASE_GetItemAbilityNosanc(&m->Item[2], EF_MPADD2);
		int critico = BASE_GetItemAbilityNosanc(&m->Item[2], EF_CRITICAL2);

		if(hp >= 20 || mp >= 20 || critico >= 100 || hp >= 10 && mp >= 10 || hp >= 10 && critico >= 50 || hp >= 10 && mp >= 10 || mp >= 10 && critico >= 50)
		{
			SendClientMsg(conn, g_pMessageStringTable[_NN_Wrong_Combination]);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
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

	int ipos = -1;

	if (combine >= 1 && combine <= 5)
		ipos = m->InvenPos[2];

	else if (combine == 6 || combine == 7)
		ipos = m->InvenPos[0];

	if (pMob[conn].MOB.Coin >= 1000000 && (combine == 6 || combine == 7))
	{
		pMob[conn].MOB.Coin -= 1000000;
		SendEtc(conn);
	}

	if (pMob[conn].MOB.Exp >= 5000000 && combine == 5)
	{
		pMob[conn].MOB.Exp -= 5000000;
								 
		if(pMob[conn].MOB.CurrentScore.Level < 150)
			rate = 30;

		else if(pMob[conn].MOB.CurrentScore.Level < 160)
			rate = 35;

		else if(pMob[conn].MOB.CurrentScore.Level < 170)
			rate = 40;

		else if(pMob[conn].MOB.CurrentScore.Level < 180)
			rate = 50;

		else if(pMob[conn].MOB.CurrentScore.Level < 190)
			rate = 70;

		else if(pMob[conn].MOB.CurrentScore.Level <= MAX_CLEVEL)
			rate = 100;

		int newlevel = 0;

		for(int i = 0; i < MAX_CLEVEL; i++)
		{
			if(pMob[conn].MOB.Exp >= g_pNextLevel_2[i] && pMob[conn].MOB.Exp <= g_pNextLevel_2[i+1])
				newlevel = i;
		}

		pMob[conn].MOB.BaseScore.Level = newlevel;
		int check = pMob[conn].CheckGetLevel();
								 
		if(check == 4)
			SetCircletSubGod(conn);

		BASE_GetBonusScorePoint(&pMob[conn].MOB, &pMob[conn].Extra);

		pMob[conn].GetCurrentScore(conn);
		SendEtc(conn);
		SendScore(conn);
		SendEmotion(conn, 14, 3);
	}
	
	if (_rand <= rate || LOCALSERVER)
	{

		if (combine == 1)
		{
			pMob[conn].MOB.Carry[ipos].sIndex = 412;
			pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect = 61;
			pMob[conn].MOB.Carry[ipos].stEffect[0].cValue = 10;
		}

		else if (combine == 2)
		{
			pMob[conn].MOB.Carry[ipos].sIndex = 4148;
			pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect = 61;
			pMob[conn].MOB.Carry[ipos].stEffect[0].cValue = 10;
		}

		else if (combine == 3 || combine == 4)
		{
			memcpy(&pMob[conn].MOB.Carry[ipos].sIndex, &m->Item[2], sizeof(STRUCT_ITEM));

			for (int i = 0; i < 2; i++)
			{
				//MP
				if (m->Item[i].sIndex == 661)
				{
					if (pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect == 70)
					{
						pMob[conn].MOB.Carry[ipos].stEffect[1].cValue += 2;

						if (pMob[conn].MOB.Carry[ipos].stEffect[1].cValue >= 100)
							pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 20;
					}
					else if (pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect == 70)
					{
						pMob[conn].MOB.Carry[ipos].stEffect[2].cValue += 2;

						if (pMob[conn].MOB.Carry[ipos].stEffect[2].cValue >= 100)
							pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 20;
					}
					else
					{
						if (pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect == 0)
						{
							pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect = 70;
							pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 2;
						}
						else if (pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect == 0)
						{
							pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect = 70;
							pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 2;
						}
					}
				}

				//HP
				else if (m->Item[i].sIndex == 662)
				{
					if (pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect == 69)
					{
						pMob[conn].MOB.Carry[ipos].stEffect[1].cValue += 2;

						if (pMob[conn].MOB.Carry[ipos].stEffect[1].cValue >= 20)
							pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 20;
					}
					else if (pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect == 69)
					{
						pMob[conn].MOB.Carry[ipos].stEffect[2].cValue += 2;

						if (pMob[conn].MOB.Carry[ipos].stEffect[2].cValue >= 20)
							pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 20;
					}
					else
					{
						if (pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect == 0)
						{
							pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect = 69;
							pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 2;
						}
						else if (pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect == 0)
						{
							pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect = 69;
							pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 2;
						}
					}
				}

				//Critico
				else if (m->Item[i].sIndex == 663)
				{
					if (pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect == 71)
					{
						pMob[conn].MOB.Carry[ipos].stEffect[1].cValue += 10;

						if (pMob[conn].MOB.Carry[ipos].stEffect[1].cValue >= 100)
							pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 100;
					}
					else if (pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect == 71)
					{
						pMob[conn].MOB.Carry[ipos].stEffect[2].cValue += 10;

						if (pMob[conn].MOB.Carry[ipos].stEffect[2].cValue >= 100)
							pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 100;
					}
					else
					{
						if (pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect == 0)
						{
							pMob[conn].MOB.Carry[ipos].stEffect[1].cEffect = 71;
							pMob[conn].MOB.Carry[ipos].stEffect[1].cValue = 10;
						}
						else if (pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect == 0)
						{
							pMob[conn].MOB.Carry[ipos].stEffect[2].cEffect = 71;
							pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 10;
						}
					}
				}
			}

			BASE_SetItemSanc(&pMob[conn].MOB.Carry[ipos], 7, 0);
		}

		else if (combine == 5)
		{
			memcpy(&pMob[conn].MOB.Carry[ipos].sIndex, &m->Item[2], sizeof(STRUCT_ITEM));

			pMob[conn].MOB.Carry[ipos].stEffect[0].cEffect = 43;

			int sanc = BASE_GetItemSanc(&pMob[conn].MOB.Carry[ipos]);
			BASE_SetItemSanc(&pMob[conn].MOB.Carry[ipos], sanc + 1, 0);
		}

		else if (combine == 6)
		{
			memcpy(&pMob[conn].MOB.Carry[ipos].sIndex, &m->Item[0], sizeof(STRUCT_ITEM));

			pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 11 + (m->Item[1].sIndex - 4190);
		}

		else if (combine == 7)
		{
			memcpy(&pMob[conn].MOB.Carry[ipos].sIndex, &m->Item[0], sizeof(STRUCT_ITEM));

			pMob[conn].MOB.Carry[ipos].stEffect[2].cValue = 0;
		}

		else if (combine == 8)
		{
			if (m->Item[0].sIndex == 2441 && m->Item[1].sIndex == 2441 && m->Item[2].sIndex == 2441)
				pMob[conn].Extra.Soul = SOUL_FC;

			else if (m->Item[0].sIndex == 2442 && m->Item[1].sIndex == 2442 && m->Item[2].sIndex == 2442)
				pMob[conn].Extra.Soul = SOUL_IC;

			else if (m->Item[0].sIndex == 2443 && m->Item[1].sIndex == 2443 && m->Item[2].sIndex == 2443)
				pMob[conn].Extra.Soul = SOUL_DC;

			else if (m->Item[0].sIndex == 2444 && m->Item[1].sIndex == 2444 && m->Item[2].sIndex == 2444)
				pMob[conn].Extra.Soul = SOUL_FD;

			else if (m->Item[0].sIndex == 2441 && m->Item[1].sIndex == 2442 && m->Item[2].sIndex == 2443)
				pMob[conn].Extra.Soul = SOUL_ID;

			else if (m->Item[0].sIndex == 2441 && m->Item[1].sIndex == 2443 && m->Item[2].sIndex == 2444)
				pMob[conn].Extra.Soul = SOUL_CD;

			else if (m->Item[0].sIndex == 2442 && m->Item[1].sIndex == 2443 && m->Item[2].sIndex == 2444)
				pMob[conn].Extra.Soul = SOUL_F;

			else if (m->Item[0].sIndex == 2442 && m->Item[1].sIndex == 2441 && m->Item[2].sIndex == 2443)
				pMob[conn].Extra.Soul = SOUL_I;

			else if (m->Item[0].sIndex == 2443 && m->Item[1].sIndex == 2442 && m->Item[2].sIndex == 2444)
				pMob[conn].Extra.Soul = SOUL_C;

			else if (m->Item[0].sIndex == 2444 && m->Item[1].sIndex == 2441 && m->Item[2].sIndex == 2443)
				pMob[conn].Extra.Soul = SOUL_D;

			SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			char tt[256];
			sprintf(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[ipos], tt);
			strcat(temp, tt);
			MyLog(LogType::Combines, "*** Combine ehre soul sucess *** ", pUser[conn].AccountName, 0, pUser[conn].IP);
			return;
		}

		


		char tt[256];

		SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

		sprintf(temp, "%s ", pUser[conn].AccountName);
		BASE_GetItemCode(&pMob[conn].MOB.Carry[ipos], tt);
		strcat(temp, tt);

		MyLog(LogType::Combines, "*** Combine ehre sucess *** ", pUser[conn].AccountName, 0, pUser[conn].IP);
		SendItem(conn, ITEM_PLACE_CARRY, ipos, &pMob[conn].MOB.Carry[ipos]);

		int TargetVillage = BASE_GetVillage(pMob[conn].TargetX, pMob[conn].TargetY);

		if (TargetVillage >= 0 && TargetVillage < 5)
		{
			if (GuildImpostoID[TargetVillage] >= MAX_USER && GuildImpostoID[TargetVillage] < MAX_MOB && pMob[GuildImpostoID[TargetVillage]].Mode != USER_EMPTY && pMob[GuildImpostoID[TargetVillage]].MOB.Guild == g_pGuildZone[TargetVillage].ChargeGuild)
			{
				if (pMob[GuildImpostoID[TargetVillage]].MOB.Exp < 200000000000)
					pMob[GuildImpostoID[TargetVillage]].MOB.Exp += 1000000 / 10;
			}
		}

		return;
	}
	else
	{
		//Ref Aben�oada
		if (combine == 5)
		{
			memcpy(&pMob[conn].MOB.Carry[m->InvenPos[2]], &m->Item[2], sizeof(STRUCT_ITEM));
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[2], &pMob[conn].MOB.Carry[m->InvenPos[2]]);
		}

		sprintf(temp, "%s(%d/%d)", g_pMessageStringTable[_NN_CombineFailed], _rand, rate);
		SendClientMsg(conn, temp);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		MyLog(LogType::Combines, "*** Combine ehre fail *** ", pUser[conn].AccountName, 0, pUser[conn].IP);
		return;
	}
}