#include "ProcessClientMessage.h"

void Exec_MSG_TradingItem(int conn, char *pMsg)
{
	MSG_SwapItem *m = (MSG_SwapItem*)pMsg;

	if (pMob[conn].MOB.CurrentScore.Hp == 0 || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		AddCrackError(conn, 1, 19);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		RemoveTrade(conn);
		return;
	}

	if (pUser[conn].TradeMode)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_CantWhenAutoTrade]);
		return;
	}


	if ((m->DestType == ITEM_PLACE_CARGO || m->SourType == ITEM_PLACE_CARGO) && (pMob[conn].MOB.Class != 3 || !(pMob[conn].MOB.LearnedSkill & 0x2000)))
	{
		int WarpID = m->TargetID;

		if (WarpID <= MAX_USER && WarpID >= MAX_MOB)
		{
			SendClientSignal(conn, ESCENE_FIELD, 412);
			return;
		}

		if (pMob[WarpID].Mode != MOB_PEACE || pMob[WarpID].MOB.Merchant != 2)
		{
			SendClientSignal(conn, ESCENE_FIELD, 412);
			return;
		}

		int PosX = pMob[conn].TargetX;
		int PosY = pMob[conn].TargetY;
		int tx = pMob[WarpID].TargetX;
		int ty = pMob[WarpID].TargetY;

		if (PosX < tx - VIEWGRIDX || PosX > tx + VIEWGRIDX || PosY < ty - VIEWGRIDY || PosY > ty + VIEWGRIDY)
		{
			SendClientSignal(conn, ESCENE_FIELD, 412);
			return;
		}
	}
	STRUCT_ITEM *Mount = &pMob[conn].MOB.Equip[14];

	int DestType = 0;
	int SourType = 0;

	STRUCT_ITEM *DestItem = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->DestType, m->DestPos);
	STRUCT_ITEM *SrcItem = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->SourType, m->SourPos);

	STRUCT_ITEM *dItem = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->DestType, m->DestPos);
	STRUCT_ITEM *sItem = GetItemPointer(&pMob[conn].MOB, pUser[conn].Cargo, m->SourType, m->SourPos);


	if (m->DestType)
	{
		if (m->DestType == ITEM_PLACE_CARRY)
		{
			if (m->DestPos >= MAX_CARRY - 4)
			{
				Log("err,trading fails.SwapItem-Carry", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
		}
		else
		{
			if (m->DestType != ITEM_PLACE_CARGO)
			{
				Log("err,trading fails.SwapItem source type", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
			if (m->DestPos > MAX_CARGO)
			{
				Log("err,trading fails.SwapItem-Cargo", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
		}
	}
	else
	{
		if (m->DestPos < 0 || m->DestPos >= MAX_EQUIP - 1)
		{
			Log("err,trading fails.SwapItem-Equip", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}
		DestType = 1;
		SourType = 1;
	}
	if (m->SourType)
	{
		if (m->SourType == ITEM_PLACE_CARRY)
		{
			if (m->SourPos >= MAX_CARRY - 4)
			{
				Log("DEBUG:Trading Fails.Swap-Carr", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
		}
		else
		{
			if (m->SourType != ITEM_PLACE_CARGO)
			{
				Log("DEBUG:Trading Fails.SwapItem dest type", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
			if (m->SourPos > MAX_CARGO)
			{
				Log("DEBUG:Trading Fails.Swap-Cargo", pUser[conn].AccountName, pUser[conn].IP);
				return;
			}
		}
	}
	else
	{
		if (m->SourPos <= 0 || m->SourPos >= MAX_EQUIP - 1)
		{
			Log("DEBUG:Trading Fails.Swap-Equip", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}

		DestType = 1;
		SourType = 1;
	}

	if (m->DestType == ITEM_PLACE_CARRY && m->DestPos >= pMob[conn].MaxCarry)
		return;

	if (DestItem == NULL || SrcItem == NULL)
	{
		Log("DEBUG:Trading Fails.Swap-Equip", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	//if ((SrcItem->sIndex >= 4152 && SrcItem->sIndex <= 4188) && ((pMob[conn].MOB.Equip[0].sIndex >= 22 && pMob[conn].MOB.Equip[0].sIndex <= 25) || pMob[conn].MOB.Equip[0].sIndex == 32))
	//{
	//	SendClientMsg(conn, "Não é possível equipar traje quando estiver transformado.");
	//	return;
	//}

	if (DestItem->sIndex != 747 && SrcItem->sIndex != 747 || m->DestType != ITEM_PLACE_CARGO && m->SourType != ITEM_PLACE_CARGO)
	{
		int isGuild = 0;

		if ((DestItem->sIndex == 508 || DestItem->sIndex == 522 || DestItem->sIndex >= 526 && DestItem->sIndex <= 537)
			&& !m->DestType && m->SourType)
			isGuild = 1;

		int isGuildAgain = 0;

		if ((SrcItem->sIndex == 508 || SrcItem->sIndex == 522 || SrcItem->sIndex >= 526 && SrcItem->sIndex <= 537)
			&& !m->DestType && m->SourType)
			isGuildAgain = 1;

		if ((isGuild == 1 || isGuildAgain == 1) && g_Week && pMob[conn].MOB.BaseScore.Level < 1000)
		{
			SendClientMsg(conn, g_pMessageStringTable[_NN_Only_Sunday]);
			return;
		}

		GetGuild(SrcItem);
		GetGuild(DestItem);

		int Can = 1;
		int YouCan = 1;

		if (dItem->sIndex)
		{
			int error = -2;

			if (m->SourType == ITEM_PLACE_EQUIP)
				Can = BASE_CanEquip(dItem, &pMob[conn].MOB.CurrentScore, m->SourPos, pMob[conn].MOB.Class, pMob[conn].MOB.Equip, &pMob[conn].Extra);

			if (m->SourType == ITEM_PLACE_CARRY)
			{
				if (!Can)
				{
					if (error > 0 && error <= pMob[conn].MaxCarry)
					{
						error--;
						SendItem(conn, ITEM_PLACE_CARRY, error, &pMob[conn].MOB.Carry[error]);
					}
				}
			}
		}

		if (sItem->sIndex)
		{
			int error = -2;

			if (m->DestType == ITEM_PLACE_EQUIP)

				YouCan = BASE_CanEquip(sItem, &pMob[conn].MOB.CurrentScore, m->DestPos, pMob[conn].MOB.Class, pMob[conn].MOB.Equip, &pMob[conn].Extra);

			if (m->DestType == ITEM_PLACE_CARRY)
			{
				if (!YouCan)
				{
					if (error > 0 && error <= pMob[conn].MaxCarry)
					{
						error--;
						SendItem(conn, ITEM_PLACE_CARRY, error, &pMob[conn].MOB.Carry[error]);
					}
				}
			}
		}
		if (Can && YouCan)
		{



			STRUCT_ITEM save1;
			STRUCT_ITEM save2;

			save1.sIndex = SrcItem->sIndex;
			save1.stEffect[0].cEffect = SrcItem->stEffect[0].cEffect;
			save1.stEffect[0].cValue = SrcItem->stEffect[0].cValue;
			save1.stEffect[1].cEffect = SrcItem->stEffect[1].cEffect;
			save1.stEffect[1].cValue = SrcItem->stEffect[1].cValue;
			save1.stEffect[2].cEffect = SrcItem->stEffect[2].cEffect;
			save1.stEffect[2].cValue = SrcItem->stEffect[2].cValue;

			save2.sIndex = DestItem->sIndex;
			save2.stEffect[0].cEffect = DestItem->stEffect[0].cEffect;
			save2.stEffect[0].cValue = DestItem->stEffect[0].cValue;
			save2.stEffect[1].cEffect = DestItem->stEffect[1].cEffect;
			save2.stEffect[1].cValue = DestItem->stEffect[1].cValue;
			save2.stEffect[2].cEffect = DestItem->stEffect[2].cEffect;
			save2.stEffect[2].cValue = DestItem->stEffect[2].cValue;

			int isAmmount = FALSE;
			for (size_t i = 0; i < sizeof(groupItens); i++)
			{
				if (save1.sIndex == groupItens[i])
				{
					isAmmount = TRUE;
					break;
				}

			}
			/*if ((save1.sIndex == save2.sIndex && save1.sIndex == 413
				|| save1.sIndex == save2.sIndex && save1.sIndex == 412
				|| save1.sIndex == save2.sIndex && save1.sIndex == 419
				|| save1.sIndex == save2.sIndex && save1.sIndex == 420
				|| save1.sIndex == save2.sIndex && save1.sIndex >= 4016 && save1.sIndex <= 4025
				|| save1.sIndex == save2.sIndex && save1.sIndex >= 2390 && save1.sIndex <= 2419)
				&& BASE_GetItemAmount(&save1) < 120 && BASE_GetItemAmount(&save2) < 120)
			{*/
			if ((save1.sIndex == save2.sIndex && isAmmount)
				&& BASE_GetItemAmount(&save1) < 120 && BASE_GetItemAmount(&save2) < 120)
			{
				int amount1 = BASE_GetItemAmount(&save1);
				int amount2 = BASE_GetItemAmount(&save2);
				int tamount = (amount1 <= 0 ? 1 : amount1) + (amount2 <= 0 ? 1 : amount2);

				if (tamount <= 119)
				{
					save1.stEffect[0].cEffect = 61;
					save1.stEffect[0].cValue = tamount;

					BASE_ClearItem(&save2);

					SendItem(conn, m->SourType, m->SourPos, &save1);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}
				else if (tamount >= 120)
				{
					save1.stEffect[0].cEffect = 61;
					save1.stEffect[0].cValue = 120;

					tamount -= 120;

					if (tamount >= 1)
						BASE_SetItemAmount(&save2, tamount > 120 ? 120 : tamount);

					if (tamount <= 0)
						BASE_ClearItem(&save2);

					SendItem(conn, m->SourType, m->SourPos, &save1);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}


			}
			if (m->DestType == ITEM_PLACE_EQUIP)
			{
				//Macro Eternal(7dias)
				if (save1.sIndex == 3789 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save1, 6);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}
				if (save2.sIndex == 3789 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save2, 6);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}
				//Fada Eternal(15dias)
				/*if (save1.sIndex >= 3790 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save1, 14);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}
				if (save2.sIndex >= 3790 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save2, 14);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}
				//Fada Eternal(30dias)
				if (save1.sIndex >= 3791 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save1, 29);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}
				if (save2.sIndex >= 3791 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save2, 29);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}*/
				//Fada(3dias)
				if (save1.sIndex >= 3900 && save1.sIndex <= 3902 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save1, 2);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}
				if (save2.sIndex >= 3900 && save2.sIndex <= 3902 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save2, 2);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}
				//fada 5dias
				if (save1.sIndex >= 3903 && save1.sIndex <= 3905 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save1, 4);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}
				if (save2.sIndex >= 3903 && save2.sIndex <= 3905 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save2, 4);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}
				//fada 7 dias
				if (save1.sIndex >= 3906 && save1.sIndex <= 3908 || save1.sIndex == 3910 || save1.sIndex == 3911 
					|| save1.sIndex >= 3914 && save1.sIndex <= 3916 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save1, 6);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}
				if (save2.sIndex >= 3906 && save2.sIndex <= 3908 || save2.sIndex == 3910 || save2.sIndex == 3911 
					|| save2.sIndex >= 3914 && save2.sIndex <= 3916 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save2, 6);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}

				// fadas 24h
				if (save1.sIndex == 3909 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save1, 1);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}
				if (save2.sIndex >= 3909 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save2, 1);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}

				//fada 15 dias
				if (save1.sIndex == 3912 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save1, 15);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}
				if (save2.sIndex == 3912 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save2, 30);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}

				//fada 30 dias
				if (save1.sIndex == 3913 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save1, 30);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}
				if (save2.sIndex == 3913 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetDateFairy(&save2, 30);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}
				//trajes
				if (save1.sIndex >= 4150 && save1.sIndex <= 4188 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save1, 30);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}
				if (save2.sIndex >= 4150 && save2.sIndex <= 4188 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save2, 30);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}
				//Montaria 3 dias
				if (save1.sIndex >= 3980 && save1.sIndex <= 3982 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save1, 3);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}
				
				if (save2.sIndex >= 3980 && save2.sIndex <= 3982 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save2, 3);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}
				//Montaria 15 dias
				if (save1.sIndex >= 3983 && save1.sIndex <= 3985 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save1, 15);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}

				if (save2.sIndex >= 3983 && save2.sIndex <= 3985 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save2, 15);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}

				//Montaria 30 dias
				if (save1.sIndex >= 3986 && save1.sIndex <= 3989 && save1.stEffect[0].cEffect == 0 && save1.stEffect[1].cEffect == 0 && save1.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save1, 30);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}

				if (save2.sIndex >= 3986 && save2.sIndex <= 3989 && save2.stEffect[0].cEffect == 0 && save2.stEffect[1].cEffect == 0 && save2.stEffect[2].cEffect == 0)
				{
					BASE_SetItemDate(&save2, 30);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}

				//limpa os itens de cash caso o tempo tenha sido esgotado
				if (save1.sIndex >= 3900 && save1.sIndex <= 3989 && BASE_CheckItemDate(&save1) || save1.sIndex >= 4150 && save1.sIndex <= 4188 && BASE_CheckItemDate(&save1))
				{
					BASE_ClearItem(&save1);
					SendItem(conn, m->SourType, m->SourPos, &save1);
				}

				if (save2.sIndex >= 3900 && save2.sIndex <= 3989 && BASE_CheckItemDate(&save2) || save2.sIndex >= 4150 && save2.sIndex <= 4188 && BASE_CheckItemDate(&save2))
				{
					BASE_ClearItem(&save2);
					SendItem(conn, m->DestType, m->DestPos, &save2);
				}
			}

			char itemLog[2048];
			char itemLog2[2048];

			BASE_GetItemCode(&save1, itemLog);
			BASE_GetItemCode(&save2, itemLog2);

			sprintf(temp, "tradingitem, SrcType:%d SourPos:%d Item:%s DstType:%d DstSlot:%d Item:%s", m->SourType, m->SourPos, itemLog, m->DestType, m->DestPos, itemLog2);
			MyLog(LogType::Itens, pMob[conn].MOB.MobName, temp, 0, pUser[conn].IP);

			memcpy(SrcItem, &save2, sizeof(STRUCT_ITEM));
			memcpy(DestItem, &save1, sizeof(STRUCT_ITEM));


			if (save2.sIndex <= 40)
				GetGuild(SrcItem);

			if (save1.sIndex <= 40)
				GetGuild(DestItem);

			pMob[conn].GetCurrentScore(conn);

			pUser[conn].cSock.AddMessage((char*)m, sizeof(MSG_SwapItem));

			if (!pMob[conn].MOB.Equip[6].sIndex)
			{
				if (pMob[conn].MOB.Equip[7].sIndex)
				{
					int hab = BASE_GetItemAbility(&pMob[conn].MOB.Equip[7], EF_POS);

					if (hab != 128)
					{
						m->DestType = ITEM_PLACE_EQUIP;
						m->DestPos = 6;
						m->SourType = ITEM_PLACE_EQUIP;
						m->SourPos = 7;

						pUser[conn].cSock.AddMessage((char*)m, sizeof(MSG_SwapItem));

						pMob[conn].MOB.Equip[6] = pMob[conn].MOB.Equip[7];

						memset(&pMob[conn].MOB.Equip[7], 0, sizeof(STRUCT_ITEM));
					}
				}
			}

			if (DestType == ITEM_PLACE_CARRY)
				SendEquip(conn, conn);

			if (SourType == ITEM_PLACE_CARRY)
			{
				GetGuild(conn);
				SendScore(conn);
			}

			if (m->DestType == ITEM_PLACE_EQUIP || m->SourType == ITEM_PLACE_EQUIP) { // Correção para poder movimentar as crias com ela summonada e não ficar fazendo ela nascer toda hora
				if (DestItem->sIndex >= 2330 && DestItem->sIndex < 2360 || SrcItem->sIndex >= 2330 && SrcItem->sIndex < 2360)
					MountProcess(conn, Mount);
			}

			STRUCT_ITEM *Storage2 = &pUser[conn].Cargo[MAX_CARGO - 2];
			STRUCT_ITEM *LastStorage = &pUser[conn].Cargo[MAX_CARGO - 1];

			if (m->DestType == ITEM_PLACE_CARGO || m->SourType == ITEM_PLACE_CARGO)
			{
				if (Storage2->sIndex || LastStorage->sIndex)
				{
					for (int i = 0; i < 126; ++i)
					{
						if (Storage2->sIndex)
						{
							int cancargo = BASE_CanCargo(Storage2, pUser[conn].Cargo, i % 9, i / 9);
							if (cancargo)
							{
								memcpy(&pUser[conn].Cargo[i], Storage2, sizeof(STRUCT_ITEM));

								memset(Storage2, 0, sizeof(STRUCT_ITEM));
								SendItem(conn, ITEM_PLACE_CARGO, i, &pUser[conn].Cargo[i]);
							}
						}

						else
						{
							if (LastStorage->sIndex)
							{
								int cancargo = BASE_CanCargo(LastStorage, pUser[conn].Cargo, i % 9, i / 9);
								if (cancargo)
								{
									memcpy(&pUser[conn].Cargo[i], LastStorage, sizeof(STRUCT_ITEM));

									memset(LastStorage, 0, sizeof(STRUCT_ITEM));
									SendItem(conn, ITEM_PLACE_CARGO, i, &pUser[conn].Cargo[i]);
								}
							}
						}
					}
				}
			}
		}
		else
		{
			STRUCT_ITEM save1;
			STRUCT_ITEM save2;

			save1.sIndex = SrcItem->sIndex;
			save1.stEffect[0].cEffect = SrcItem->stEffect[0].cEffect;
			save1.stEffect[0].cValue = SrcItem->stEffect[0].cValue;
			save1.stEffect[1].cEffect = SrcItem->stEffect[1].cEffect;
			save1.stEffect[1].cValue = SrcItem->stEffect[1].cValue;
			save1.stEffect[2].cEffect = SrcItem->stEffect[2].cEffect;
			save1.stEffect[2].cValue = SrcItem->stEffect[2].cValue;

			save2.sIndex = DestItem->sIndex;
			save2.stEffect[0].cEffect = DestItem->stEffect[0].cEffect;
			save2.stEffect[0].cValue = DestItem->stEffect[0].cValue;
			save2.stEffect[1].cEffect = DestItem->stEffect[1].cEffect;
			save2.stEffect[1].cValue = DestItem->stEffect[1].cValue;
			save2.stEffect[2].cEffect = DestItem->stEffect[2].cEffect;
			save2.stEffect[2].cValue = DestItem->stEffect[2].cValue;

			memcpy(SrcItem, &save1, sizeof(STRUCT_ITEM));
			memcpy(DestItem, &save2, sizeof(STRUCT_ITEM));
		}
	}
}
