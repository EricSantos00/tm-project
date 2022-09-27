
#include "ProcessClientMessage.h"
#include "IlegalCMD.h"

void Exec_MSG_MessageChat(int a_iConn, char *pMsg)
{
	MSG_MessageChat *m = (MSG_MessageChat*)pMsg;

	m->String[MESSAGE_LENGTH - 1] = 0;
	m->String[MESSAGE_LENGTH - 2] = 0;

	m->ID = a_iConn;

	if (pUser[a_iConn].Mode != USER_PLAY) 
		return;

	char szCmd[256];
	char szString[256];
	sscanf(m->String, "%s %s", szCmd, szString);

	if (DetectCMD(szCmd))
	{

		std::string nInfo = szCmd;
		nInfo += " Comando Malicioso utilizado";
		SendBanAccount(a_iConn, Banned::Permanente);
		SaveInfoDetect(a_iConn, nInfo.c_str());
		return;
	}

	if (strcmp(szCmd, "guildon") == 0)
	{
		if (pMob[a_iConn].GuildDisable == 1)
		{
			pMob[a_iConn].GuildDisable = 0;

			SendScore(a_iConn);

			SendClientSignalParm(a_iConn, ESCENE_FIELD, _MSG_GuildDisable, 0);
		}
		return;
	}

	else if (strcmp(szCmd, "guildoff") == 0)
	{
		if (pMob[a_iConn].GuildDisable == 0)
		{
			pMob[a_iConn].GuildDisable = 1;

			SendScore(a_iConn);

			SendClientSignalParm(a_iConn, ESCENE_FIELD, _MSG_GuildDisable, 1);
		}
		return;
	}
	else if (strcmp(szCmd, "guildtax") == 0)
	{
		if (pMob[a_iConn].MOB.GuildLevel != 9)
			return;

		int Guild = pMob[a_iConn].MOB.Guild;

		for (int i = 0; i < MAX_GUILDZONE; i++)
		{
			if (g_pGuildZone[i].ChargeGuild != Guild)
				continue;

			int tax = atoi(szString);

			if (tax < 0 || tax > 30 || szString[0] != 48 && !tax)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Guild_Tax_0_to_30]);
				break;
			}

			if (TaxChanged[i] == 1)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_Once_Per_Day]);
				break;
			}

			g_pGuildZone[i].CityTax = tax;
			TaxChanged[i] = 1;

			sprintf(temp, g_pMessageStringTable[169], tax, 0);
			SendClientMsg(a_iConn, temp);

			CReadFiles::WriteGuild();

			sprintf(temp, "sys,%s", m->String);
			Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);

			break;
		}
		return;
	}

	else if (strcmp(szCmd, "guild") == 0)
	{
		SendGuildList(a_iConn);

		return;
	}

	else if (strcmp(szCmd, "$dropitem") == 0)
	{
		int Index = 0;
		char Item[128];

		if (pMob[a_iConn].CheckDrop == 0)
		{
			SendClientMsg(a_iConn, "Filtro drop está desativado.");
			return;
		}

		sscanf(szString, "%s", Item);

		if (strcmp(Item, "") == 0)
			return;

		if (strcmp(Item, "Poeira de Lactolerium") == 0)
			Index = 413;
	

		pMob[a_iConn].CheckItemDrop = Index;

		sprintf(temp, "Item [%s] adicionado ao filtro de drop.", g_pItemList[Index].Name);
		SendMsgExp(a_iConn, temp, TNColor::GreenYellow, false);
		return;
	}

	//else if (strcmp(szCmd, "$rochluc") == 0)
	//{
	//pMob[a_iConn].MOB.BaseScore.Level = 1010;
	//SendEtc(a_iConn);
	//	return;
	//}

	else if (strcmp(szCmd, "whisper") == 0)
	{
		pUser[a_iConn].Whisper = pUser[a_iConn].Whisper == 0;

		if (pUser[a_iConn].Whisper)
			SendClientMsg(a_iConn, "Whisper : OFF");
		else
			SendClientMsg(a_iConn, "Whisper : ON");

		return;
	}

	else if (strcmp(szCmd, "partychat") == 0)
	{
		pUser[a_iConn].PartyChat = pUser[a_iConn].PartyChat == 0;

		if (pUser[a_iConn].PartyChat)
			SendClientMsg(a_iConn, "Party Chatting : OFF");
		else
			SendClientMsg(a_iConn, "Party Chatting : ON");

		return;
	}

	else if (strcmp(szCmd, "kingdomchat") == 0)
	{
		pUser[a_iConn].KingChat = pUser[a_iConn].KingChat == 0;

		if (pUser[a_iConn].KingChat)
			SendClientMsg(a_iConn, "Kingdom Chatting : OFF");
		else
			SendClientMsg(a_iConn, "Kingdom Chatting : ON");

		return;
	}
	else if (strcmp(szCmd, "$drop") == 0)
	{
		if (pMob[a_iConn].CheckDrop == FALSE)
		{
			pMob[a_iConn].CheckDrop = 1;
			SendClientMsg(a_iConn, "On");
			SendScore(a_iConn);
		}

		else if (pMob[a_iConn].CheckDrop == TRUE)
		{
			pMob[a_iConn].CheckDrop = 0;
			SendClientMsg(a_iConn, "Off");
			SendScore(a_iConn);
		}

		MSG_CreateMob sm_tb;
		memset(&sm_tb, 0, sizeof(MSG_CreateMob));
		GetCreateMob(a_iConn, &sm_tb);
		GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)& sm_tb, 0);
		return;
	}

	else if (strcmp(szCmd, "guildchat") == 0)
	{
		pUser[a_iConn].Guildchat = pUser[a_iConn].Guildchat == 0;

		if (pUser[a_iConn].Guildchat)
			SendClientMsg(a_iConn, "Guild Chatting : OFF");
		else
			SendClientMsg(a_iConn, "Guild Chatting : ON");

		return;
	}

	else if (strcmp(szCmd, "chatting") == 0)
	{
		pUser[a_iConn].Chatting = pUser[a_iConn].Chatting == 0;

		if (pUser[a_iConn].Chatting)
			SendClientMsg(a_iConn, "Chatting : OFF");
		else
			SendClientMsg(a_iConn, "Chatting : ON");

		return;
	}

	if (BrState && a_iConn < MAX_USER && BRItem > 0)
	{
		if (pMob[a_iConn].TargetX >= 2604 && pMob[a_iConn].TargetY >= 1708 && pMob[a_iConn].TargetX <= 2648 && pMob[a_iConn].TargetY <= 1744 || pMob[a_iConn].TargetX >= 896 && pMob[a_iConn].TargetY >= 1405 && pMob[a_iConn].TargetX <= 1150 && pMob[a_iConn].TargetY <= 1538)
			strncpy(m->String, "??????", 6);

	}

	m->String[MESSAGE_LENGTH - 1] = 0;
	m->String[MESSAGE_LENGTH - 2] = 0;

	if(pUser[a_iConn].MuteChat == 1)
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_No_Speak]);
		return;
	}

	if (pUser[a_iConn].Mode == USER_PLAY)
	{
		int leader = pMob[a_iConn].Leader;
		if (!leader)
			leader = a_iConn;

		GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)pMsg, a_iConn);
	}
	else
	{
		SendClientMsg(a_iConn, "DEBUG:Client send chatting message with wrong status");
		Log("err,send chatting message with wrong status", pUser[a_iConn].AccountName, pUser[a_iConn].IP);
	}

	sprintf(temp, "chat, %s : %s", pMob[a_iConn].MOB.MobName, m->String);
	MyLog(LogType::Command, pUser[a_iConn].AccountName, temp, 0, pUser[a_iConn].IP);

}