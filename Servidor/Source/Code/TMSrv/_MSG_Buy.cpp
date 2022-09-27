#include "ProcessClientMessage.h"

void Exec_MSG_Buy(int conn, char *pMsg)
{
	MSG_Buy *m = (MSG_Buy*)pMsg;

	if (pMob[conn].MOB.CurrentScore.Hp == 0 || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		AddCrackError(conn, 10, 21);
		return;
	}

	if (pUser[conn].TradeMode)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		RemoveTrade(conn);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(conn);
		return;
	}

	if (pUser[conn].IsBlocked)
	{
		SendClientMsg(conn, "Sua conta está com o bloqueio ativo para essa operação.");
		return;
	}


	int TargetID = m->TargetID;
	int TargetInvenPos = m->TargetInvenPos;
	int MyInvenPos = m->MyInvenPos;

	if (TargetID < MAX_USER || TargetID >= MAX_MOB || TargetInvenPos < 0 || TargetInvenPos >= MAX_CARRY || MyInvenPos < 0 || MyInvenPos >= pMob[conn].MaxCarry)
	{
		if (TargetID < MAX_USER && TargetID == conn)
		{
			if (TargetInvenPos > 27) return;
			if (TargetInvenPos < 0) return;

			if (TargetInvenPos >= 9) { TargetInvenPos = 27; }
			if (TargetInvenPos == 27) { TargetInvenPos = 9; }

			if (TargetInvenPos < _Max_Recycle_Bin_)
			{
				auto My = pMob[conn].Recycle[TargetInvenPos].Item;

				if (My.sIndex <= 0 || My.sIndex >= MAX_ITEMLIST) return;

				int szPrice = g_pItemList[My.sIndex].Price;

				if (szPrice > pMob[conn].MOB.Coin)
				{
					SendClientMsg(conn, g_pMessageStringTable[_NN_Havent_Money_So_Much]);
					return;
				}

				if (PutItem(conn, &My))
				{
					memset(&pMob[conn].Recycle[TargetInvenPos].Item, 0, sizeof(STRUCT_ITEM));
					pMob[conn].Recycle[TargetInvenPos].Price = 0;
					pMob[conn].Recycle[TargetInvenPos].Ticks = 0;

					SendRecycle(conn);

					pMob[conn].MOB.Coin -= szPrice;

					SendEtc(conn);
				}
			}

			return;
		}

		Log("err,MSG_BUY, target of carrypos outof range", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	if (TargetID < MAX_USER || TargetID >= MAX_MOB || TargetInvenPos < 0 || TargetInvenPos >= MAX_CARRY || MyInvenPos < 0 || MyInvenPos >= MAX_CARRY)
	{
		Log("err,MSG_BUY, target of carrypos outof range", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	if (pMob[TargetID].MOB.Merchant != 1)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Only_Merchant_Sells]);
		return;
	}
	if (!GetInView(conn, TargetID))
	{
		SendClientSignal(conn, ESCENE_FIELD, _MSG_CloseShop);
		return;
	}

	int itemIndex = pMob[TargetID].MOB.Carry[TargetInvenPos].sIndex;

	STRUCT_ITEM *ItemMob = &pMob[TargetID].MOB.Carry[TargetInvenPos];

	if (itemIndex <= 0 || itemIndex >= MAX_ITEMLIST)
		return;

	if (strcmp(pMob[TargetID].MOB.MobName, "Fame FoemaSB") == 0 ||
		strcmp(pMob[TargetID].MOB.MobName, "Fame BeastSB") == 0 ||
		strcmp(pMob[TargetID].MOB.MobName, "Fame HunterSB") == 0 ||
		strcmp(pMob[TargetID].MOB.MobName, "Fame TransSB") == 0)
	{
		if (itemIndex >= 5500 && itemIndex <= 5547)
		{
			if (pMob[conn].Extra.Fame < 2000)
			{
				SendClientMsg(conn, "You need 2000 Fame to complete the purchase!");
				return;
			}
			else
			{
				pMob[conn].Extra.Fame -= 2000;

				char tmplog[2048];
				BASE_GetItemCode(ItemMob, tmplog);
				SendItem(conn, ITEM_PLACE_CARRY, m->MyInvenPos, &pMob[conn].MOB.Carry[m->MyInvenPos]);
			}
		}
	}
#pragma region NPC Bragi
	int Donate = BASE_GetItemAbility(ItemMob, EF_DONATE);

	if (Donate)
	{
		if (Donate > pUser[conn].Donate)
		{
			sprintf(temp, "[%s]> Você precisa de [%d] %s.", pMob[TargetID].MOB.MobName, Donate,"Epoints");
			SendMsgExp(conn, temp, TNColor::White, false);
			return;
		}

		if (itemIndex == 0)
		{
			Log("err,buy request null item from shop donate - MSG_BUY", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}

		if (pMob[conn].MOB.Carry[m->MyInvenPos].sIndex != 0)
		{
			SendItem(conn, ITEM_PLACE_CARRY, m->MyInvenPos, &pMob[conn].MOB.Carry[m->MyInvenPos]);
			return;
		}

		pUser[conn].Donate -= Donate;

		goto DonateBuy;
	}
#pragma endregion

#pragma region NPC Territory
	int FamePoint = BASE_GetItemAbility(ItemMob, EF_FAME_POINT);
	int GuildLevel = BASE_GetItemAbility(ItemMob, EF_GUILD_LEVEL);
	int GuildIndex = pMob[conn].MOB.Guild;

	FamePoint *= (500 * GuildLevel);

	ReadGuildHall(conn);
	if (FamePoint)
	{
		if (!GuildIndex)
		{
			SendSay(TargetID, "Item disponivel somente para guilds");
			return;
		}

		if (pMob[conn].MOB.GuildLevel != GUILD_LEADER)
		{
			SendSay(TargetID, "Somente o Lider da guild pode comprar");
			return;
		}

		if (GuildLevel > GuildHall[GuildIndex].Level)
		{
			sprintf(temp, "[%s]> Sua Guild precisa de level [%d]", pMob[conn].MOB.MobName, GuildLevel);
			SendSay(TargetID, temp);
			return;
		}

		if (FamePoint > GuildHall[GuildIndex].FamePoint)
		{
			sprintf(temp, "[%s]> Sua Guild precisa de [%d] %s.", pMob[conn].MOB.MobName, FamePoint, "FamePoint");
			SendSay(TargetID, temp);
			return;
		}

		if (itemIndex == 0)
		{
			Log("err,buy request null item from shop donate - MSG_BUY", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}

		if (pMob[conn].MOB.Carry[m->MyInvenPos].sIndex != 0)
		{
			SendItem(conn, ITEM_PLACE_CARRY, m->MyInvenPos, &pMob[conn].MOB.Carry[m->MyInvenPos]);
			return;
		}

		GuildHall[GuildIndex].FamePoint -= FamePoint;
		//GuildHall[GuildIndex].Territory++;
		WriteGuildHall(conn);

		goto DonateBuy;
	}
#pragma endregion
	int Price = g_pItemList[itemIndex].Price;
	int Price2 = Price;
	int Village = BASE_GetVillage(pMob[TargetID].TargetX, pMob[TargetID].TargetY);
	int CityTax = g_pGuildZone[Village].CityTax;

	if (Village < 0 || Village >= 5 || CityTax <= 0 || CityTax >= 30)
		goto LABEL_BUY1;

	if (Price < 100000)
		Price += Price * CityTax / 100;

	else
		Price += Price * CityTax / 100;

	if (Price < 0)
		return;

	int GuildTax = (Price - Price2) / 2;
LABEL_BUY1:

	int bPrice = Price;
	int Desconto = 0;
	int TargetVillage = BASE_GetVillage(pMob[TargetID].TargetX, pMob[TargetID].TargetY);
	int Guild = pMob[conn].MOB.Guild;

	if (Price <= 1999999999 && TargetVillage >= 0 && TargetVillage < 5 && Guild > 0 && g_pGuildZone[TargetVillage].ChargeGuild == Guild)
	{
		Desconto = 30;
		Price = 7 * Price / 10;
	}

	if (Price <= 1999999999 && !Desconto && pMob[conn].MOB.Class == 3 && pMob[conn].MOB.LearnedSkill & 0x800)
	{
		int special = (pMob[conn].MOB.CurrentScore.Special[2] / 10) + 6;

		if ((pMob[conn].MOB.CurrentScore.Special[2] / 10) + 6 >= 26)
			special = 26;

		Desconto = special;
		special /= 2;

	}

	if (Price > pMob[conn].MOB.Coin)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Not_Enough_Money]);
		return;
	}

	if (itemIndex == 0)
	{
		Log("err,buy request null item from shop - MSG_BUY", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}
	int ProcSlot = -1;

	for (int i = 0; i < pMob[conn].MaxCarry; i++)
	{
		if (pMob[conn].MOB.Carry[i].sIndex == 0)
		{
			ProcSlot = i;

			break;
		}
	}

	if (ProcSlot == -1)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_You_Have_No_Space_To_Trade]);
		return;
	}

	if (pMob[conn].MOB.Carry[m->MyInvenPos].sIndex != 0)
	{
		SendItem(conn, ITEM_PLACE_CARRY, m->MyInvenPos, &pMob[conn].MOB.Carry[m->MyInvenPos]);
		return;
	}

	if (itemIndex == 508 || itemIndex == 509 || itemIndex == 446 || itemIndex >= 526 && itemIndex <= 531)
	{
		if (ServerIndex == -1)
		{
			Log("err,Buy Guild item, but, Server index undefined", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}

		if (!GuildCounter)
		{
			Log("err,Buy Guild item, but, Guild counter zero", pUser[conn].AccountName, pUser[conn].IP);
			return;
		}

		if (itemIndex == 508 || itemIndex == 446 || itemIndex >= 526 && itemIndex <= 531)
		{
			if (!pMob[conn].MOB.GuildLevel)
			{
				SendClientMsg(conn, g_pMessageStringTable[114]);
				return;
			}
			if (pMob[conn].MOB.GuildLevel < 2 && itemIndex >= 526 && itemIndex <= 531)
			{
				SendClientMsg(conn, g_pMessageStringTable[114]);
				return;
			}

			ItemMob->stEffect[0].cEffect = 56;
			ItemMob->stEffect[0].cValue = Guild;
			ItemMob->stEffect[1].cEffect = 57;
			ItemMob->stEffect[1].cValue = Guild;

			if (itemIndex == 508)
			{
				int sub = BASE_GetSubGuild(pMob[conn].MOB.Equip[12].sIndex);

				ItemMob->stEffect[2].cEffect = 85;
				ItemMob->stEffect[2].cValue = sub;

				if (sub >= 1 && sub <= 3)
					ItemMob->sIndex = sub + 531;
			}
		}

		if (itemIndex == 509)
		{
			ItemMob->stEffect[0].cEffect = 56;
			ItemMob->stEffect[0].cValue = (GuildCounter + (ServerIndex << 12)) >> 8;

			ItemMob->stEffect[1].cEffect = 57;
			ItemMob->stEffect[1].cValue = GuildCounter;

			ItemMob->stEffect[2].cEffect = 59;
			ItemMob->stEffect[2].cValue = rand();

			int GCount = GuildCounter + (ServerIndex << 12);

			sprintf(temp, "sys,guild medal value:%d count:%d", GCount, GuildCounter);
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);

			GuildCounter++;

			if (GuildCounter >= 4096)
			{
				GuildCounter = 2048;
				Log("err,GuildCounter Restarted.", pUser[conn].AccountName, pUser[conn].IP);
			}
			CReadFiles::WriteGuild();
		}
	}


	if (Price >= 0)
	{
		int x = 0;

		for (x = 0; x < MAX_MOB_MERC; x++)
		{
			//Verifica se o vendedor é um mob mercador especial.
			if (pMob[TargetID].GenerateIndex == pMobMerc[x].GenerateIndex)
				break;
		}

		if (x != MAX_MOB_MERC)
		{//O Vendedor é um mob mercador especial, portanto ele verifica se ainda possui unidades daquele item 
		 //se tiver ele diminui do stock caso contrário ele avisa que não tem.
			if (pMobMerc[x].Stock[TargetInvenPos] == 0)
			{
				SendClientMsg(conn, g_pMessageStringTable[_NN_NOSTOCK]);
				return;
			}
			pMobMerc[x].Stock[TargetInvenPos]--;
		}

		if (TargetVillage >= 0 && TargetVillage < 5 && CityTax > 0 && CityTax < 30)
		{
			if (GuildImpostoID[TargetVillage] >= MAX_USER && GuildImpostoID[TargetVillage] < MAX_MOB && pMob[GuildImpostoID[TargetVillage]].Mode != USER_EMPTY && pMob[GuildImpostoID[TargetVillage]].MOB.Guild == g_pGuildZone[TargetVillage].ChargeGuild)
			{
				if (pMob[GuildImpostoID[TargetVillage]].MOB.Exp < 200000000000)
					pMob[GuildImpostoID[TargetVillage]].MOB.Exp += GuildTax / 2; 


			}
			if (GuildImpostoID[4] >= MAX_USER && GuildImpostoID[4] < MAX_MOB && GuildTax > 0 && pMob[GuildImpostoID[4]].Mode != USER_EMPTY && pMob[GuildImpostoID[4]].MOB.Guild == g_pGuildZone[4].ChargeGuild)
			{
				if (pMob[GuildImpostoID[4]].MOB.Exp < 200000000000)
					pMob[GuildImpostoID[4]].MOB.Exp += GuildTax;

			}
		}

		pMob[conn].MOB.Coin -= Price;
						 
		m->Coin = pMob[conn].MOB.Coin;
						 
		m->ID = ESCENE_FIELD;
						 
		pUser[conn].cSock.AddMessage((char*)m, m->Size);

		SendEtc(conn);

	DonateBuy:

		//memcpy(&pMob[conn].MOB.Carry[MyInvenPos], ItemMob, sizeof(STRUCT_ITEM));
		PutItem(conn, ItemMob);

		char tmplog[2048];
		char tempName[256];
		BASE_GetItemCode(ItemMob, tmplog);
		BASE_GetItemName(ItemMob, tempName);
		int nValor = 0;

		if (Donate)
		{
			nValor = Donate;
			TypeCoin = "EPoints";
		}
		else if (FamePoint)
		{
			nValor = FamePoint;
			TypeCoin = "FamePoint";
		}
		else
		{
			nValor = Price;
			TypeCoin = "Gold";
		}
		std::string strValor = GetFormatDecimal(nValor);
		sprintf(temp, "buy_npc,npc:%s price:%s item:%s", pMob[TargetID].MOB.MobName, strValor.c_str(), tmplog);

		sprintf(temp, "Comprou de: %s", pMob[TargetID].MOB.MobName);
		SendMsgExp(conn, temp, TNColor::DeepPink, false);

		sprintf(temp, "Item: %s price: %s %s", tempName, strValor.c_str(), TypeCoin.c_str());
		SendMsgExp(conn, temp, TNColor::DeepPink, false);
		MyLog(LogType::Itens, pMob[conn].MOB.MobName, temp, 0, pUser[conn].IP);

		SendItem(conn, ITEM_PLACE_CARRY, m->MyInvenPos, &pMob[conn].MOB.Carry[m->MyInvenPos]);
						 
		if (FREEEXP == -2)
		{
			sprintf(temp, "%s base:%d tax:%d(%d%%) discount:%d(%d%%)", g_pItemList[itemIndex].Name, 0, 0, CityTax, Donate, 0);
			SendSay(TargetID, temp);
		}

		if (itemIndex == 787 || itemIndex == 481)
		{
			pMob[TargetID].PotionCount++;

			if (pMob[TargetID].PotionCount > POTIONCOUNT)
				DeleteMob(TargetID, 3);
		}
		if (pMob[TargetID].MOB.Equip[0].sIndex == 259 || pMob[TargetID].MOB.Equip[0].sIndex == 230)
			DeleteMob(TargetID, 3);
	}
	else
		Log("err,MSG_ReqBuy  <><><><><><> MINUS <><><><><><>", pUser[conn].AccountName, pUser[conn].IP);
}