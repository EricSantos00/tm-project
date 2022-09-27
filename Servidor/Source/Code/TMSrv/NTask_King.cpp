#include "ProcessClientMessage.h"
#include "../ConfigIni.h"

void NTask_King(int a_iConn, int a_iTarget, int confirm)
{
	int ReiClan = pMob[a_iTarget].MOB.Clan;

	int Clan = pMob[a_iConn].MOB.Clan;
	int cLevel = pMob[a_iConn].MOB.CurrentScore.Level;
	int CapeMode = 0;

	STRUCT_ITEM *Capa = &pMob[a_iConn].MOB.Equip[15];

	if (Capa->sIndex == 543 || Capa->sIndex == 545)
		Clan = 7;

	if (Capa->sIndex == 544 || Capa->sIndex == 546)
		Clan = 8;

	if (Capa->sIndex == 734 || Capa->sIndex == 736)
		Clan = 7;

	if (Capa->sIndex == 735 || Capa->sIndex == 737)
		Clan = 8;

	if (Capa->sIndex == 3191 || Capa->sIndex == 3194)
		Clan = 7;

	if (Capa->sIndex == 3192 || Capa->sIndex == 3195)
		Clan = 8;

	if (Capa->sIndex == 3197)
		Clan = 7;

	if (Capa->sIndex == 3198)
		Clan = 8;

	if (Capa->sIndex == 543 || Capa->sIndex == 544 || Capa->sIndex == 3191 || Capa->sIndex == 3194 || Capa->sIndex == 3192 || Capa->sIndex == 3195 || Capa->sIndex == 3197 || Capa->sIndex == 3198)
		CapeMode = 2;

	if (Capa->sIndex == 545 || Capa->sIndex == 546 || Capa->sIndex == 549)
		CapeMode = 1;

	if (Capa->sIndex == 3193)
		CapeMode = 1;

	if (Capa->sIndex == 3196)
		CapeMode = 1;

	if (Clan != 0 && Clan != ReiClan)
		return;

	int Saphire = Sapphire;

	if (ReiClan == 8)
	{
		if (Sapphire == 1)
			Saphire = 60;
		if (Sapphire == 2)
			Saphire = 32;
		if (Sapphire == 4)
			Saphire = 16;
		if (Sapphire == 16)
			Saphire = 4;
		if (Sapphire == 32)
			Saphire = 2;
		if (Sapphire == 64)
			Saphire = 1;
	}

	if (confirm == 0)
	{
		sprintf(temp, g_pMessageStringTable[_DN_Need_D_Sapphire], Saphire);
		SendClientMsg(a_iConn, temp);
		return;
	}

	if (pMob[a_iConn].MOB.Equip[10].sIndex == 1742 && pMob[a_iConn].MOB.Equip[11].sIndex >= 1760 && pMob[a_iConn].MOB.Equip[11].sIndex <= 1763)
	{
		int sAgua = 0;
		int sTerra = 0;
		int sSol = 0;
		int sVento = 0;


		for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex == 5334)
				sAgua = 1;

			if (pMob[a_iConn].MOB.Carry[i].sIndex == 5335)
				sTerra = 1;

			if (pMob[a_iConn].MOB.Carry[i].sIndex == 5336)
				sSol = 1;

			if (pMob[a_iConn].MOB.Carry[i].sIndex == 5337)
				sVento = 1;
		}

		if (sAgua == 1 && sTerra == 1 && sSol == 1 && sVento == 1)
		{
			for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
			{
				if (pMob[a_iConn].MOB.Carry[i].sIndex == 5334 && sAgua == 1)
				{
					memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));

					pMob[a_iConn].MOB.Carry[i].sIndex = 5338;

					SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
					sAgua = 0;
				}

				if (pMob[a_iConn].MOB.Carry[i].sIndex == 5335 && sTerra == 1)
				{
					memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
					SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
					sTerra = 0;
				}

				if (pMob[a_iConn].MOB.Carry[i].sIndex == 5336 && sSol == 1)
				{
					memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
					SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
					sSol = 0;
				}

				if (pMob[a_iConn].MOB.Carry[i].sIndex == 5337 && sVento == 1)
				{
					memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
					SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
					sVento = 0;
				}
			}

			memset(&pMob[a_iConn].MOB.Equip[10], 0, sizeof(STRUCT_ITEM));
			SendItem(a_iConn, ITEM_PLACE_EQUIP, 10, &pMob[a_iConn].MOB.Equip[10]);

			memset(&pMob[a_iConn].MOB.Equip[11], 0, sizeof(STRUCT_ITEM));
			SendItem(a_iConn, ITEM_PLACE_EQUIP, 11, &pMob[a_iConn].MOB.Equip[11]);

			SendSay(a_iTarget, g_pMessageStringTable[_NN_My_King_Bless1]);

			sprintf(temp, "etc,king make ideal_stone name:%s level:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].MOB.BaseScore.Level);
			MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

			return;
		}
		//Criar Arch
		using namespace ConfigIni;
		if (pMob[a_iConn].Extra.ClassMaster == MORTAL && pMob[a_iConn].MOB.CurrentScore.Level >= 299 && pMob[a_iConn].Mode != MOB_WAITDB)
		{
			int retconfig = nConfig::ReadExtra(PATH_SETTINGS, "extra.json", ARCH);
			int cls = pMob[a_iConn].MOB.Equip[11].sIndex - 1760;

			MSG_DBCreateArchCharacter sm_ca;
			memset(&sm_ca, 0, sizeof(MSG_DBCreateArchCharacter));

			sm_ca.Size = sizeof(MSG_DBCreateArchCharacter);
			sm_ca.Type = _MSG_DBCreateArchCharacter;
			sm_ca.ID = a_iConn;

			sm_ca.MobClass = cls;
			sm_ca.MortalFace = pMob[a_iConn].Extra.MortalFace;
			sm_ca.MortalSlot = pUser[a_iConn].Slot;

			strncpy(sm_ca.MobName, pMob[a_iConn].MOB.MobName, NAME_LENGTH);

			for (int i = 0; i < MAX_AFFECT; i++)
			{
				auto Core = pMob[a_iConn].Affect[i];

				if (Core.Type <= 0) continue;

				if (Core.Type == 34 && Core.Level == TRUE)
				{
					sm_ca.isDivina = true;
					sm_ca.DivinaTimer = Core.Time;
					sm_ca.DivinaEndTimer = pMob[a_iConn].Extra.DivineEnd;
					break;
				}
			}

			pMob[a_iConn].Mode = MOB_WAITDB;
			SendClientMsg(a_iConn, "Você criou o Arch. Que a glória de Sephira esteja com você.");
			sprintf(temp, "Parabens!!![  %s  ] por ser o [ %dº ] jogador a criar Arch no EternalWYD",pMob[a_iConn].MOB.MobName, CharaCreate[ARCH]);
			SendNotice(temp);
			DBServerSocket.SendOneMessage((char*)&sm_ca, sizeof(MSG_DBCreateArchCharacter));

			sprintf(temp, "etc,king_arch name:%s class:%d mortalface:%d mortalslot:%d", pMob[a_iConn].MOB.MobName, cls, pMob[a_iConn].Extra.MortalFace, pUser[a_iConn].Slot);
			MyLog(LogType::Quests, pUser[a_iConn].AccountName, temp, 0, pUser[a_iConn].IP);

			if (retconfig)
				retconfig = nConfig::WriteExtra(PATH_SETTINGS, "extra.json", ARCH);
			
			return;
		}
	}

	if (CapeMode >= 2)
	{
		if (ReiClan == 7)
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_My_King_Bless1]);
		else
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_My_King_Bless2]);

		return;
	}

	if ((pMob[a_iConn].Extra.ClassMaster == CELESTIAL || pMob[a_iConn].Extra.ClassMaster == CELESTIALCS || pMob[a_iConn].Extra.ClassMaster == SCELESTIAL))
	{
		if (Capa->sIndex != 3199)
			return;

		int NumSepInv = 0;

		for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex == 697)
				NumSepInv++;

			else if (pMob[a_iConn].MOB.Carry[i].sIndex == 4131)
				NumSepInv += 10;
		}

		if (NumSepInv < Saphire)
		{
			sprintf(temp, g_pMessageStringTable[_DN_Need_D_Sapphire], Saphire);
			SendClientMsg(a_iConn, temp);
			return;
		}

		MSG_STANDARDPARM sm_us;
		memset(&sm_us, 0, sizeof(MSG_STANDARDPARM));

		sm_us.ID = 0;
		sm_us.Type = _MSG_DBUpdateSapphire;

		sm_us.Size = sizeof(MSG_STANDARDPARM);

		sm_us.Parm = ReiClan == 7;

		DBServerSocket.SendOneMessage((char*)&sm_us, sizeof(MSG_STANDARD));

		for (int i = 0; i < pMob[a_iConn].MaxCarry && Saphire > 0; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex == 697)
			{
				memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
				SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
				Saphire--;
			}

			else if (pMob[a_iConn].MOB.Carry[i].sIndex == 4131)
			{
				memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
				SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);

				if ((Saphire - 10) < 0)
					Saphire = 0;

				else
					Saphire -= 10;
			}
		}


		if (ReiClan == 7)
			pMob[a_iConn].MOB.Equip[15].sIndex = 3197;
		else
			pMob[a_iConn].MOB.Equip[15].sIndex = 3198;

		SendItem(a_iConn, ITEM_PLACE_EQUIP, 15, &pMob[a_iConn].MOB.Equip[15]);

		if (ReiClan == 7)
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_My_King_Bless1]);
		else
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_My_King_Bless2]);

		int Guild = pMob[a_iConn].MOB.Guild;
		int Group = ServerGroup;
		int Server = Guild / MAX_GUILD;
		int usGuild = Guild & MAX_GUILD - 1;

		if (Guild && pMob[a_iConn].MOB.GuildLevel == 9)
		{
			MSG_GuildInfo sm_gi;
			memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

			sm_gi.Type = _MSG_GuildInfo;
			sm_gi.Size = sizeof(MSG_GuildInfo);
			sm_gi.ID = a_iConn;

			sm_gi.Guild = Guild;

			GuildInfo[Guild].Clan = ReiClan;
			GuildInfo[Guild].Fame = 0;

			sm_gi.GuildInfo = GuildInfo[Guild];

			DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));
		}

		sprintf(temp, "etc,get mantle %d - sapphire:%d", pMob[a_iConn].MOB.Equip[15].sIndex, Saphire);
		MyLog(LogType::Quests, pUser[a_iConn].AccountName, temp, 0, pUser[a_iConn].IP);
		return;
	}

	if (cLevel < 219)
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Need_Level]);
		return;
	}

	if (CapeMode != 1 || cLevel >= 255)
	{
		int NumSepInv = 0;

		for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex == 697)
				NumSepInv++;

			else if (pMob[a_iConn].MOB.Carry[i].sIndex == 4131)
				NumSepInv += 10;
		}

		if (NumSepInv < Saphire && pMob[a_iConn].MOB.Equip[13].sIndex != 4081)
		{
			sprintf(temp, g_pMessageStringTable[_DN_Need_D_Sapphire], Saphire);
			SendClientMsg(a_iConn, temp);
			return;
		}

		MSG_STANDARDPARM sm_us;
		memset(&sm_us, 0, sizeof(MSG_STANDARDPARM));

		sm_us.ID = 0;
		sm_us.Type = _MSG_DBUpdateSapphire;

		sm_us.Size = sizeof(MSG_STANDARDPARM);

		sm_us.Parm = ReiClan == 7;

		DBServerSocket.SendOneMessage((char*)&sm_us, sizeof(MSG_STANDARD));

		for (int i = 0; i < pMob[a_iConn].MaxCarry && Saphire > 0 && pMob[a_iConn].MOB.Equip[13].sIndex != 4081; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex == 697)
			{
				memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
				SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
				Saphire--;
			}

			else if (pMob[a_iConn].MOB.Carry[i].sIndex == 4131)
			{
				memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
				SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);

				if ((Saphire - 10) < 0)
					Saphire = 0;

				else
					Saphire -= 10;
			}
		}

		if (pMob[a_iConn].MOB.Equip[13].sIndex == 4081)
		{
			memset(&pMob[a_iConn].MOB.Equip[13], 0, sizeof(STRUCT_ITEM));
			SendItem(a_iConn, ITEM_PLACE_EQUIP, 13, &pMob[a_iConn].MOB.Equip[13]);
		}

		if (CapeMode == 0)
		{
			if (Capa->sIndex != 548)
				memset(&pMob[a_iConn].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));

			if (ReiClan == 7)
				pMob[a_iConn].MOB.Equip[15].sIndex = 545;
			else
				pMob[a_iConn].MOB.Equip[15].sIndex = 546;
		}

		if (CapeMode == 1)
		{
			if (Capa->sIndex == 3193)
			{
				if (ReiClan == 7)
					pMob[a_iConn].MOB.Equip[15].sIndex = 3191;
				else
					pMob[a_iConn].MOB.Equip[15].sIndex = 3192;
			}

			else if (Capa->sIndex == 3196)
			{
				if (ReiClan == 7)
					pMob[a_iConn].MOB.Equip[15].sIndex = 3194;
				else
					pMob[a_iConn].MOB.Equip[15].sIndex = 3195;
			}

			else
			{
				if (Capa->sIndex != 549)
					memset(&pMob[a_iConn].MOB.Equip[15], 0, sizeof(STRUCT_ITEM));

				if (ReiClan == 7)
					pMob[a_iConn].MOB.Equip[15].sIndex = 543;
				else
					pMob[a_iConn].MOB.Equip[15].sIndex = 544;
			}
		}


		SendItem(a_iConn, ITEM_PLACE_EQUIP, 15, &pMob[a_iConn].MOB.Equip[15]);

		if (ReiClan == 7)
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_My_King_Bless1]);
		else
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_My_King_Bless2]);

		int Guild = pMob[a_iConn].MOB.Guild;
		int Group = ServerGroup;
		int Server = Guild / MAX_GUILD;
		int usGuild = Guild & MAX_GUILD - 1;

		if (Guild && pMob[a_iConn].MOB.GuildLevel == 9)
		{
			MSG_GuildInfo sm_gi;
			memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

			sm_gi.Type = _MSG_GuildInfo;
			sm_gi.Size = sizeof(MSG_GuildInfo);
			sm_gi.ID = a_iConn;

			sm_gi.Guild = Guild;

			GuildInfo[Guild].Clan = ReiClan;

			sm_gi.GuildInfo = GuildInfo[Guild];

			DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));
		}

		sprintf(temp, "etc,get mantle %d - sapphire:%d", pMob[a_iConn].MOB.Equip[15].sIndex, Saphire);
		MyLog(LogType::Quests, pUser[a_iConn].AccountName, temp, 0, pUser[a_iConn].IP);
		return;
	}
	else
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Need_Level]);
		return;
	}
}

void NTask_KingdonBroker(int a_iConn, int a_iTarget, int confirm, int ClientTick)
{
	int Clan = pMob[a_iConn].MOB.Clan;


	time_t rawtime;
	tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (timeinfo->tm_wday == 6 || timeinfo->tm_wday == 0)
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_NotEquip_Saturday]);
		return;
	}

	if (Clan != 7 && Clan != 8)
	{
		if (Clan == 7)
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_My_King_Bless1]);
		else
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_My_King_Bless2]);

		return;
	}

	if (confirm == 0)
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Leaving_kingdom]);

		return;
	}
	int Saphire = 6;
	int NumSepInv = 0;

	for (int i = 0; i < pMob[a_iConn].MaxCarry; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex == 697)
			NumSepInv++;

		else if (pMob[a_iConn].MOB.Carry[i].sIndex == 4131)
			NumSepInv += 10;
	}

	if (NumSepInv < Saphire)
	{
		sprintf(temp, g_pMessageStringTable[_DN_Need_D_Sapphire], Saphire);
		SendClientMsg(a_iConn, temp);
		return;
	}

	for (int i = 0; i < pMob[a_iConn].MaxCarry && Saphire > 0; i++)
	{
		if (pMob[a_iConn].MOB.Carry[i].sIndex == 697)
		{
			memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
			SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
			Saphire--;
		}

		else if (pMob[a_iConn].MOB.Carry[i].sIndex == 4131)
		{
			memset(&pMob[a_iConn].MOB.Carry[i], 0, sizeof(STRUCT_ITEM));
			SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);

			if ((Saphire - 10) < 0)
				Saphire = 0;

			else
				Saphire -= 10;
		}
	}


	if (pMob[a_iConn].MOB.Equip[15].sIndex == 543 || pMob[a_iConn].MOB.Equip[15].sIndex == 544)
		pMob[a_iConn].MOB.Equip[15].sIndex = 549;

	if (pMob[a_iConn].MOB.Equip[15].sIndex == 545 || pMob[a_iConn].MOB.Equip[15].sIndex == 546)
		pMob[a_iConn].MOB.Equip[15].sIndex = 548;

	if (pMob[a_iConn].MOB.Equip[15].sIndex == 3191 || pMob[a_iConn].MOB.Equip[15].sIndex == 3192)
		pMob[a_iConn].MOB.Equip[15].sIndex = 3193;

	if (pMob[a_iConn].MOB.Equip[15].sIndex == 3194 || pMob[a_iConn].MOB.Equip[15].sIndex == 3195)
		pMob[a_iConn].MOB.Equip[15].sIndex = 3196;

	if (pMob[a_iConn].MOB.Equip[15].sIndex == 3197 || pMob[a_iConn].MOB.Equip[15].sIndex == 3198)
		pMob[a_iConn].MOB.Equip[15].sIndex = 3199;

	if (Clan == 7)
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_My_King_Bless1]);
	else
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_My_King_Bless2]);

	SendItem(a_iConn, ITEM_PLACE_EQUIP, 15, &pMob[a_iConn].MOB.Equip[15]);

	pMob[a_iConn].GetCurrentScore(a_iConn);

	MSG_STANDARDPARM sm_scl; 
	memset(&sm_scl, 0, sizeof(MSG_STANDARDPARM));

	sm_scl.Type = _MSG_SetClan;
	sm_scl.Size = sizeof(MSG_STANDARDPARM);
	sm_scl.ID = a_iConn;
	sm_scl.Parm = pMob[a_iConn].MOB.Clan;
	ClientTick = CurrentTime;

	GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm_scl, 0);

	SendEquip(a_iConn, a_iConn);
	sprintf(temp, "etc,remove mantle");
	MyLog(LogType::Quests, pUser[a_iConn].AccountName, temp, 0, pUser[a_iConn].IP);
	return;
}