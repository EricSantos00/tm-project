
#include "ProcessClientMessage.h"

void Exec_MSG_CombineItemOdin(int conn, char *pMsg)
{
	MSG_CombineItem *m = (MSG_CombineItem*)pMsg;

	if (!NPCBlock[Odin])
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_NPCBLOCKED]);
		return;
	}

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
			MyLog(LogType::Combines, "err,msg_CombineOdin - item remove or changed.", pUser[conn].AccountName, 0, pUser[conn].IP);
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	int combine = GetMatchCombineOdin(m->Item);

	if (combine == 2)
	{
		int sAgua = 0;
		int sTerra = 0;
		int sSol = 0;
		int sVento = 0;

		if(m->Item[3].sIndex == 5334 || m->Item[4].sIndex == 5334 || m->Item[5].sIndex == 5334 || m->Item[6].sIndex == 5334)
			sAgua = 1;

		if(m->Item[3].sIndex == 5335 || m->Item[4].sIndex == 5335 || m->Item[5].sIndex == 5335 || m->Item[6].sIndex == 5335)
			sTerra = 1;

		if(m->Item[3].sIndex == 5336 || m->Item[4].sIndex == 5336 || m->Item[5].sIndex == 5336 || m->Item[6].sIndex == 5336)
			sSol = 1;

		if(m->Item[3].sIndex == 5337 || m->Item[4].sIndex == 5337 || m->Item[5].sIndex == 5337 || m->Item[6].sIndex == 5337)
			sVento = 1;

		if((sAgua && (sTerra == 0 || sSol == 0 || sVento == 0)) || (sTerra && (sAgua == 0 || sSol == 0 || sVento == 0)) || (sSol && (sAgua == 0 || sTerra == 0 || sVento == 0)) || (sVento && (sAgua == 0 || sTerra == 0 || sSol == 0)))
		{
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}
	}

	if (combine == 2 && (BASE_GetItemSanc(&m->Item[2]) >= REF_15 || BASE_GetItemAbility(&m->Item[2], EF_MOBTYPE) == 3))
	{
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	if (combine == 4 && (pMob[conn].MOB.CurrentScore.Level != 39 || pMob[conn].Extra.QuestInfo.Celestial.Lv40 == 1 || pMob[conn].Extra.ClassMaster != CELESTIAL))
	{
		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
		return;
	}

	if (combine == 11 && (pMob[conn].Extra.ClassMaster == MORTAL || pMob[conn].Extra.ClassMaster == ARCH || BASE_GetItemSanc(&pMob[conn].MOB.Equip[15]) >= 9))
	{								 
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


	if (combine == 1)//Item celestial
	{
		if (_rand <= g_pOdinRate[combine] || LOCALSERVER)
		{
			memcpy(&pMob[conn].MOB.Carry[m->InvenPos[1]], &m->Item[1], sizeof(STRUCT_ITEM));

			pMob[conn].MOB.Carry[m->InvenPos[1]].sIndex = g_pItemList[m->Item[0].sIndex].Extra;
			BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[1]], 0, 0);

			char tt[256];
			sprintf(temp, "Odin: [%s] combinou com sucesso item celestial [%s]", pMob[conn].MOB.MobName,g_pItemList[m->Item->sIndex].Name);
			SendNotice(temp);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[1]], tt);
			strcat(temp, tt);

			MyLog(LogType::Combines, "*** Combine odin item celestial sucess ***", pUser[conn].AccountName, 0, pUser[conn].IP);
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

			return;
		}
		else
		{
			memcpy(&pMob[conn].MOB.Carry[m->InvenPos[1]], &m->Item[1], sizeof(STRUCT_ITEM));
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[1], &pMob[conn].MOB.Carry[m->InvenPos[1]]);

			sprintf(temp, "Odin: [%s] falhou na combinação do item celestial [%s]", pMob[conn].MOB.MobName, g_pItemList[m->Item->sIndex].Name);
			SendNotice(temp);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			MyLog(LogType::Combines, "*** Combine odin item celestial fail ***", pUser[conn].AccountName, 0, pUser[conn].IP);
			return;
		}
	}

	else if (combine == 2)//Item +12+
	{
		int rate = 1;

		int protect = 0;

		for (int i = 0; i < MAX_COMBINE; i++)
		{
			if (m->Item[i].sIndex >= 5334 && m->Item[i].sIndex <= 5337)
				rate += g_pItemSancRate12[0];

			if (m->Item[i].sIndex == 4043)
				protect++;

			if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 0)
				rate += g_pItemSancRate12[1];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 1)
				rate += g_pItemSancRate12[2];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 2)
				rate += g_pItemSancRate12[3];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 3)
				rate += g_pItemSancRate12[4];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 4)
				rate += g_pItemSancRate12[5];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 5)
				rate += g_pItemSancRate12[6];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 6)
				rate += g_pItemSancRate12[7];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 7)
				rate += g_pItemSancRate12[8];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 8)
				rate += g_pItemSancRate12[9];

			else if (m->Item[i].sIndex == 3338 && BASE_GetItemSanc(&m->Item[i]) == 9)
				rate += g_pItemSancRate12[10];
		}

		if (BASE_GetItemSanc(&m->Item[2]) <= REF_10 || BASE_GetItemSanc(&m->Item[2]) >= REF_15)
		{
			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 0);
			return;
		}

		if (BASE_GetItemSanc(&m->Item[2]) == REF_12)
			rate -= g_pItemSancRate12Minus[0];
									
		else if (BASE_GetItemSanc(&m->Item[2]) == REF_13)
			rate -= g_pItemSancRate12Minus[1];
									 
		else if (BASE_GetItemSanc(&m->Item[2]) == REF_14)
			rate -= g_pItemSancRate12Minus[2];
									 
		else if (BASE_GetItemSanc(&m->Item[2]) == REF_15)
			rate -= g_pItemSancRate12Minus[3];

		if (rate >= _rand || LOCALSERVER)
		{
			memcpy(&pMob[conn].MOB.Carry[m->InvenPos[2]], &m->Item[2], sizeof(STRUCT_ITEM));

			int sanc = BASE_GetItemSanc(&m->Item[2]);
			int gem = BASE_GetItemGem(&m->Item[2]);

			int NewSanc = 0;

			if (sanc == REF_11)
			{
				BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 12, gem);
				NewSanc = 12;
			}
			else if (sanc == REF_12)
			{
				BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 13, gem);
				NewSanc = 13;
			}
			else if (sanc == REF_13)
			{
				BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 14, gem);
				NewSanc = 14;
			}
			else if (sanc == REF_14)
			{ 
				BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 15, gem);
				NewSanc = 15;
			}
			char tt[256];

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[2]], tt);
			strcat(temp, tt);

			MyLog(LogType::Combines, "*** Combine odin item +12+ sucess ***", pUser[conn].AccountName, 0, pUser[conn].IP);

			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[2], &pMob[conn].MOB.Carry[m->InvenPos[2]]);

			sprintf(temp, "Odin: [%s] combinou [+%d] com sucesso o item [%s]", pMob[conn].MOB.MobName, NewSanc, g_pItemList[m->Item[2].sIndex].Name);
			SendNotice(temp);

			return;
		}
		else
		{
			if(rate <= 9 && BASE_GetItemAbility(&m->Item[2], EF_MOBTYPE) == 1)
			{//Possivel quebra

				//Escudos
				if(g_pItemList[m->Item[2].sIndex].nPos == 128)
					goto Label_VoltaRef;

				if(rate <= 9)//Tentou com secretas
				{
					if(rand()%1 == 0)
					{
						if(protect == 2)
						{
							memcpy(&pMob[conn].MOB.Carry[m->InvenPos[2]], &m->Item[2], sizeof(STRUCT_ITEM));

							pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex = 3021;

							pMob[conn].MOB.Carry[m->InvenPos[2]].stEffect[0].cEffect = EF_ITEMLEVEL;
							pMob[conn].MOB.Carry[m->InvenPos[2]].stEffect[0].cValue = 5;

							//se tiver add de critico 42 converte para 71 para se adequar ao visual da extração
							int effect = 0;
							int value = 0;
							for (int i = 0; i < 3; i++)
							{
								if (m->Item[2].stEffect[i].cEffect == EF_CRITICAL)
								{
									effect = EF_CRITICAL2;
									value = m->Item[2].stEffect[i].cValue + 45;
									
									break;
								}
							}

							//pega adds do item que irá virar extração
							pMob[conn].MOB.Carry[m->InvenPos[2]].stEffect[1].cEffect = m->Item[2].stEffect[0].cEffect == EF_CRITICAL ? effect : m->Item[2].stEffect[0].cEffect;
							pMob[conn].MOB.Carry[m->InvenPos[2]].stEffect[1].cValue = m->Item[2].stEffect[0].cEffect == EF_CRITICAL ? value : m->Item[2].stEffect[0].cValue;
							pMob[conn].MOB.Carry[m->InvenPos[2]].stEffect[2].cEffect = m->Item[2].stEffect[1].cEffect == EF_CRITICAL ? effect : m->Item[2].stEffect[1].cEffect;
							pMob[conn].MOB.Carry[m->InvenPos[2]].stEffect[2].cValue = m->Item[2].stEffect[1].cEffect == EF_CRITICAL ? value : m->Item[2].stEffect[1].cValue;
														 
							if(g_pItemList[m->Item[2].sIndex].nPos == 4)
							pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex++;

							else if(g_pItemList[m->Item[2].sIndex].nPos == 8)
							pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex += 2;

							else if(g_pItemList[m->Item[2].sIndex].nPos == 16)
							pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex += 3;

							else if(g_pItemList[m->Item[2].sIndex].nPos == 32)
							pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex += 4;
														 
							else
							{
								pMob[conn].MOB.Carry[m->InvenPos[2]].sIndex = 3026;
								pMob[conn].MOB.Carry[m->InvenPos[2]].stEffect[0].cValue = 6;
							}

			

							SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[2], &pMob[conn].MOB.Carry[m->InvenPos[2]]);
						}
						else
						{
							memset(&pMob[conn].MOB.Carry[m->InvenPos[2]], 0, sizeof(STRUCT_ITEM));
							SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[2], &pMob[conn].MOB.Carry[m->InvenPos[2]]);
						}
					}
					else
						goto Label_VoltaRef;
				}
			}
			else
			{
Label_VoltaRef:
				memcpy(&pMob[conn].MOB.Carry[m->InvenPos[2]], &m->Item[2], sizeof(STRUCT_ITEM));

				int sanc = BASE_GetItemSanc(&m->Item[2]);
				int gem = BASE_GetItemGem(&m->Item[2]);
				//int NewSanc = sanc + 1;
				if (sanc == REF_11)
					BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 10, gem);

				else if (sanc == REF_12)
					BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 11, gem);

				else if (sanc == REF_13)
					BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 12, gem);

				else if (sanc == REF_14)
					BASE_SetItemSanc(&pMob[conn].MOB.Carry[m->InvenPos[2]], 13, gem);

				SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[2], &pMob[conn].MOB.Carry[m->InvenPos[2]]);
			}

			int sanc = BASE_GetItemSanc(&m->Item[2]);
			int new_sanc = 0;
			switch (sanc)
			{
			case REF_11:
				new_sanc = 12;
				break;
			case REF_12:
				new_sanc = 13;
				break;
			case REF_13:
				new_sanc = 14;
				break;
			case REF_14:
				new_sanc = 15;
				break;
			default:
				break;
			}
			
			sprintf(temp, "Odin: [%s] falhou [+%d] na composição do item [%s]", pMob[conn].MOB.MobName, new_sanc, g_pItemList[m->Item[2].sIndex].Name);
			SendNotice(temp);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			MyLog(LogType::Combines, "*** Combine odin item +12+ fail ***", pUser[conn].AccountName, 0, pUser[conn].IP);
			return;
		}
									 
	}

	else if (combine == 3)//Pista de runas
	{
		if (_rand <= g_pOdinRate[combine] || LOCALSERVER)
		{
			pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 5134;

			char tt[256];

			SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);
			strcat(temp, tt);

			MyLog(LogType::Combines, "*** Combine odin pista runas sucess ***", pUser[conn].AccountName, 0, pUser[conn].IP);
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);

			return;
		}
		else
		{
			SendClientMsg(conn, g_pMessageStringTable[_NN_CombineFailed]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			MyLog(LogType::Combines, "*** Combine odin pista runas fail ***", pUser[conn].AccountName, 0, pUser[conn].IP);

			return;
		}
	}

	else if (combine == 4)//Destrave Lv40
	{
		if (_rand <= g_pOdinRate[combine] || LOCALSERVER)
		{
			SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			MyLog(LogType::Combines, "*** Combine odin destrave40 sucess ***", pMob[conn].MOB.MobName, 0, pUser[conn].IP);

			pMob[conn].Extra.QuestInfo.Celestial.Lv40 = 1;

			return;
		}
		else
		{
			SendClientMsg(conn, g_pMessageStringTable[_NN_CombineFailed]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			MyLog(LogType::Combines, "*** Combine odin destrave40 fail ***", pMob[conn].MOB.MobName, 0, pUser[conn].IP);

			return;
		}
	}

	else if (combine == 5)//Pedra da fúria
	{
		if (_rand <= g_pOdinRate[combine] || LOCALSERVER)
		{
			pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 3020;

			char tt[512];

			SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);
			strcat(temp, tt);

			MyLog(LogType::Combines, "*** Combine odin furia sucess ***", pMob[conn].MOB.MobName, 0, pUser[conn].IP);

			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);

			return;
		}
		else
		{
			SendClientMsg(conn, g_pMessageStringTable[_NN_CombineFailed]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			MyLog(LogType::Combines, "*** Combine odin furia fail ***", pMob[conn].MOB.MobName, 0, pUser[conn].IP);

			return;
		}
	}

	else if (combine >= 6 && combine <= 9)//Pedra da agua - terra - sol - vento
	{
		if (_rand <= g_pOdinRate[combine] || LOCALSERVER)
		{
			pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 5334 + (combine - 6);

			char tt[512];

			SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);
			strcat(temp, tt);

			MyLog(LogType::Combines, "*** Combine odin secret sucess ***", pMob[conn].MOB.MobName, 0, pUser[conn].IP);
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);

			return;
		}
		else
		{
			SendClientMsg(conn, g_pMessageStringTable[_NN_CombineFailed]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			MyLog(LogType::Combines, "*** Combine odin secret fail ***", pMob[conn].MOB.MobName, 0, pUser[conn].IP);

			return;
		}
	}

	else if (combine == 10)//Semente de cristal
	{
		if (_rand <= g_pOdinRate[combine] || LOCALSERVER)
		{
			pMob[conn].MOB.Carry[m->InvenPos[0]].sIndex = 4032;

			char tt[512];

			SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);
			strcat(temp, tt);

			MyLog(LogType::Combines, "*** Combine odin semente sucess ***", pMob[conn].MOB.MobName, 0, pUser[conn].IP);
			SendItem(conn, ITEM_PLACE_CARRY, m->InvenPos[0], &pMob[conn].MOB.Carry[m->InvenPos[0]]);

			return;
		}
		else
		{
			SendClientMsg(conn, g_pMessageStringTable[_NN_CombineFailed]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			MyLog(LogType::Combines, "*** Combine odin semente fail ***", pMob[conn].MOB.MobName, 0, pUser[conn].IP);

			return;
		}
	}

	else if (combine == 11)//Capa celestial
	{
		if (_rand <= g_pOdinRate[combine] || LOCALSERVER)
		{
			int sanc = BASE_GetItemSanc(&pMob[conn].MOB.Equip[15]);

			if (sanc == 0)
			{
				if (pMob[conn].MOB.Equip[15].stEffect[0].cEffect && pMob[conn].MOB.Equip[15].stEffect[0].cEffect != 43 && (pMob[conn].MOB.Equip[15].stEffect[0].cEffect && pMob[conn].MOB.Equip[15].stEffect[0].cEffect < 116 || pMob[conn].MOB.Equip[15].stEffect[0].cEffect && pMob[conn].MOB.Equip[15].stEffect[0].cEffect > 125))
				{
					if (pMob[conn].MOB.Equip[15].stEffect[1].cEffect && pMob[conn].MOB.Equip[15].stEffect[1].cEffect != 43 && (pMob[conn].MOB.Equip[15].stEffect[1].cEffect && pMob[conn].MOB.Equip[15].stEffect[1].cEffect < 116 || pMob[conn].MOB.Equip[15].stEffect[1].cEffect && pMob[conn].MOB.Equip[15].stEffect[1].cEffect > 125))
					{
						if (pMob[conn].MOB.Equip[15].stEffect[2].cEffect && pMob[conn].MOB.Equip[15].stEffect[2].cEffect != 43 && (pMob[conn].MOB.Equip[15].stEffect[2].cEffect && pMob[conn].MOB.Equip[15].stEffect[2].cEffect < 116 || pMob[conn].MOB.Equip[15].stEffect[2].cEffect && pMob[conn].MOB.Equip[15].stEffect[2].cEffect > 125))
						{
							SendClientMsg(conn, g_pMessageStringTable[_NN_Cant_Refine_More]);
							return;
						}
						pMob[conn].MOB.Equip[15].stEffect[2].cEffect = 43;
						pMob[conn].MOB.Equip[15].stEffect[2].cValue = 0;
					}
					else
					{
						pMob[conn].MOB.Equip[15].stEffect[1].cEffect = 43;
						pMob[conn].MOB.Equip[15].stEffect[1].cValue = 0;
					}
				}
				else
				{
					pMob[conn].MOB.Equip[15].stEffect[0].cEffect = 43;
					pMob[conn].MOB.Equip[15].stEffect[0].cValue = 0;
				}
			}

			BASE_SetItemSanc(&pMob[conn].MOB.Equip[15], sanc + 1, 0);

			char tt[256];

			SendClientMsg(conn, g_pMessageStringTable[_NN_Processing_Complete]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 1);

			sprintf(temp, "%s ", pUser[conn].AccountName);
			BASE_GetItemCode(&pMob[conn].MOB.Carry[m->InvenPos[0]], tt);
			strcat(temp, tt);

			MyLog(LogType::Combines, "*** Combine odin capa sucesso ***", pMob[conn].MOB.MobName, 0, pUser[conn].IP);
			SendItem(conn, ITEM_PLACE_EQUIP, 15, &pMob[conn].MOB.Equip[15]);

			return;
		}
		else
		{
			SendClientMsg(conn, g_pMessageStringTable[_NN_CombineFailed]);

			SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
			MyLog(LogType::Combines, "*** Combine odin capa fail ***", pMob[conn].MOB.MobName, 0, pUser[conn].IP);

			return;
		}
	}

	else
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_CombineFailed]);

		SendClientSignalParm(conn, ESCENE_FIELD, _MSG_CombineComplete, 2);
		MyLog(LogType::Combines, "*** Combine odin fail ***", pUser[conn].AccountName, 0, pUser[conn].IP);
		return;
	}
}