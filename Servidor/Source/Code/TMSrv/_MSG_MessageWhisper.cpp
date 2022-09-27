#include "ProcessClientMessage.h"
#include "PassGroup.h"
#include "..\ConfigIni.h"
#include "EventsEternal.h"
#include "Quiz.h"
#include "TitleSystem.h"

using ConfigIni::nConfig;

void Exec_MSG_MessageWhisper(int a_iConn, char* pMsg)
{
	MSG_MessageWhisper* m = (MSG_MessageWhisper*)pMsg;

	int Clan = pMob[a_iConn].MOB.Clan;

	m->MobName[NAME_LENGTH - 1] = 0;
	m->String[MESSAGEWHISPER_LENGTH - 1] = 0;

	if (pUser[a_iConn].Mode != USER_PLAY)
		return;

	if (pUser[a_iConn].MuteChat == 1)
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_No_Speak]);
		return;
	}

	if (strcmp(m->MobName, "cp") == 0)
	{
		sprintf(temp, g_pMessageStringTable[_DN_Show_Chao], GetPKPoint(a_iConn) - 75);
		SendClientMsg(a_iConn, temp);
		return;
	}
	if (strcmp(m->MobName, "ep") == 0)
	{
		//sprintf(temp, "%d",pUser[a_iConn].Donate);
		sprintf(temp, "Você possui [%d] de [%s]", pUser[a_iConn].Donate, "EPoints");
		SendMsgExp(a_iConn, temp, TNColor::Orange, false);
		//SendClientMsg(a_iConn, temp);
		return;
	}
	/*if (strcmp(m->MobName, "wp1") == 0)
	{
		pUser[a_iConn].Donate += 100;
		SendClientMsg(a_iConn, temp);
		return;
	}*/

#pragma region /contaPrincipal
	 if (strcmp(m->MobName, "DefAccount") == 0 || strcmp(m->MobName, "DefConta") == 0)
	{
		 if (pUser[a_iConn].TradeMode)
		 {
			 SendClientMsg(a_iConn, "Comando indisponível com loja aberta!");
			 return;
		 }

		MSG_DBPrimaryAccount sm;
		memset(&sm, 0, sizeof(MSG_DBPrimaryAccount));

		sm.Size = sizeof(MSG_DBPrimaryAccount);
		sm.Type = _MSG_DBPrimaryAccount;
		sm.ID = a_iConn;

		memcpy(&sm.Mac, pUser[a_iConn].Mac, sizeof(sm.Mac));
		sm.IP = pUser[a_iConn].IP;

		DBServerSocket.SendOneMessage((char*)&sm, sizeof(MSG_DBPrimaryAccount));

		return;
	}

	 if (strcmp(m->MobName, "Primary") == 0 || strcmp(m->MobName, "Principal") == 0)
	 {
		 if (pUser[a_iConn].OnlyTrade)
		 {
			 sprintf(temp, "Essa conta não esta definida como principal");
			 SendMsgExp(a_iConn, temp, TNColor::CornBlueName, false);
		 }
		 else
		 {
			 sprintf(temp, "Essa conta esta definida como principal");
			 SendMsgExp(a_iConn, temp, TNColor::GreenYellow, false);
		 }
		 return;
	 }
#pragma endregion
	if (strcmp(m->MobName, "ResetLan") == 0)
	{
		pMob[a_iConn].QuizError = 0;
		sprintf(temp, "contador de erros do quiz resetado!!");
		SendMsgExp(a_iConn, temp, TNColor::Azure, false);
		sprintf(temp, "Erros [%d] de [%d] tentativas", pMob[a_iConn].QuizError, MAX_QUIZ_ERROR);
		SendMsgExp(a_iConn, temp, TNColor::CornBlueName, false);
		return;
	}

	/*if (strcmp(m->MobName, "QuizTest") == 0)
	{
		questionQuiz();
	
		pMob[a_iConn].CorrectQuiz = eQuiz[SortQuiz].Correct;
		SendQuizMessage(a_iConn, eQuiz[SortQuiz].Title, eQuiz[SortQuiz].Answer0, 
			eQuiz[SortQuiz].Answer1, eQuiz[SortQuiz].Answer2, eQuiz[SortQuiz].Answer3, eQuiz[SortQuiz].Correct);
		return;
	}*/

	/*Evento VemProEternal*/
	if (strcmp(m->MobName, "VemProEternal") == 0)
	{
		nConfig::ReadEventsEternal(PATH_EVENT_VemProEternal, pUser[a_iConn].AccountName, VemProEternal);
		pUser[a_iConn].VemProEternal = eEvents.eventValue;
		if (pUser[a_iConn].VemProEternal)
		{
			sprintf(temp, "O Evento já foi Ativado na Conta:  %s ", pUser[a_iConn].AccountName);
			SendMsgExp(a_iConn, temp, TNColor::Azure, false);
			return;
		}
		sprintf(temp, "Bônus para novo jogador ativado na Conta:  %s ", pUser[a_iConn].AccountName);
		SendMsgExp(a_iConn, temp, TNColor::Orange, false);
		nConfig::WriteEventsEternal(PATH_EVENT_VemProEternal, pUser[a_iConn].AccountName, VemProEternal, TRUE);
		pUser[a_iConn].VemProEternal = TRUE;
		fVemProEternal(a_iConn);
		return;
	}

	/*if (strcmp(m->MobName, "rVemProEternal") == 0)
	{
		BOOL ativado = FALSE;
		FILE* fs = nullptr;
		memset(&NovatoEternal, 0, sizeof(novatoEternal));
		fs = fopen(strFmt("Novato/%s.bin", pUser[a_iConn].AccountName), "rb");

		if (fs)
		{
			fread(&NovatoEternal, 1, sizeof(novatoEternal), fs);
			fclose(fs);
			auto nNovato = &NovatoEternal;
			ativado = nNovato->Ativo;
		}
		if (ativado)
		{
			sprintf(temp, "Esse evento já foi ativado na conta [%s]", pUser[a_iConn].AccountName);
			SendMsgExp(a_iConn, temp, TNColor::GreenYellow, false);
			return;
		}
		sprintf(temp, "Evento liberado novamente para a Conta:  %s ", pUser[a_iConn].AccountName);
		SendMsgExp(a_iConn, temp, TNColor::GreenYellow, false);
		//nConfig::WriteEventsEternal(PATH_EVENT_VemProEternal, pUser[a_iConn].AccountName, VemProEternal, FALSE);
		//pUser[a_iConn].VemProEternal = FALSE;

		if (a_iConn < 0 || a_iConn > MAX_USER)
			return;

		std::ofstream outputFile(strFmt("Novato/%s.bin", pUser[a_iConn].AccountName),
			std::ofstream::out | std::ofstream::binary);

		if (outputFile.is_open())
		{
			novatoEternal temp;
			std::memcpy(&temp, &NovatoEternal, sizeof(novatoEternal));
			temp.Ativo = TRUE;
			outputFile.write(reinterpret_cast<char*>(&temp), sizeof(novatoEternal));
			outputFile.close();
			return;
		}

	
		return;
	}*/
	/*Evento VemProEternal*/

	//Definir senha de grupo
	if (strcmp(m->MobName, "DefGroupPass") == 0 || strcmp(m->MobName, "DefSenhaGrupo") == 0)
	{
		if (strlen(m->String) > 5)
		{
			SendClientMsg(a_iConn, "Limite máximo de 5 caracteres.");
			return;
		}

		int pos = -1;

		for (int i = 0; i < 5; i++)
		{
			if (m->String[i] == ' ')
			{
				pos = i;
				break;
			}
		}

		if (strlen(m->String) <= 0 || pos != -1)
		{
			SendClientMsg(a_iConn, "Digite uma senha para seu grupo.");
			return;
		}

		if (pMob[a_iConn].Leader != 0)
		{
			SendClientMsg(a_iConn, "Você não é lider de um grupo.");
			return;
		}

		defPassGroup(a_iConn, m->String);
		return;
	}
	//Ver senha de grupo
	if (strcmp(m->MobName, "GroupPass") == 0 || strcmp(m->MobName, "SenhaGrupo") == 0)
	{
		sprintf(temp, "Sua senha de grupo é:  %s ", pUser[a_iConn].PartyPassword);
		SendMsgExp(a_iConn, temp, TNColor::GoldenEscuro, false);
		return;
	}

	//Entrar em um grupo com senha
	if (strcmp(m->MobName, "GroupEnter") == 0 || strcmp(m->MobName, "EntrarGrupo") == 0)
	{
		char PlayerName[256];
		char Password[256];
		sscanf(m->String, "%s %s", PlayerName, Password);

		if (strlen(PlayerName) <= 0 || strlen(PlayerName) > 16)
		{
			SendClientMsg(a_iConn, "Nome inválido.");
			return;
		}

		if (strlen(Password) <= 0 || strlen(Password) > 5)
		{
			SendClientMsg(a_iConn, "Senha inválida.");
			return;
		}

		getGroup(a_iConn, PlayerName, Password);
		return;

	}
	else if (strcmp(m->MobName, "gindex") == 0)
	{
		if (pMob[a_iConn].MOB.GuildLevel != 9)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_Guild_Master_can]);
			return;
		}

		sprintf(temp, "Guild Index [%d]", pMob[a_iConn].MOB.Guild);
		SendClientMsg(a_iConn, temp);
		return;
	}

	else if (strcmp(m->MobName, "getout") == 0)
	{
		pMob[a_iConn].Extra.Citizen = 0;
		SendClientMsg(a_iConn, g_pMessageStringTable[_DN_NO_TOWNSPEOPLE]);

		sprintf(temp, "etc,getout %d ", pMob[a_iConn].Extra.Citizen);
		MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);;
		return;
	}

	else if (strcmp(m->MobName, "block") == 0)
	{
		if (pUser[a_iConn].IsBlocked)
		{
			SendClientMsg(a_iConn, "Você já definiu uma senha de bloqueio. Escreva /unblock (senha) para desbloquear.");

			return;
		}

		int len = strlen(m->String);

		if (len < 4 || len >= ACCOUNTNAME_LENGTH)
		{
			SendClientMsg(a_iConn, "A senha de bloqueio deve ter de 4 a 15 caractéres.");

			return;
		}

		strcpy(pUser[a_iConn].BlockPass, m->String);

		pUser[a_iConn].IsBlocked = true;

		SendClientMsg(a_iConn, "Você bloqueou a movimentação dos seus itens.");

		return;
	}

	if (strcmp(m->MobName, "unblock") == 0)
	{
		if (pUser[a_iConn].IsBlocked == false) return;

		if (strcmp(pUser[a_iConn].BlockPass, m->String) != 0)
		{
			SendClientMsg(a_iConn, "Senha de desbloqueio, inválida.");

			return;
		}

		memset(pUser[a_iConn].BlockPass, 0, sizeof(ACCOUNTNAME_LENGTH));

		pUser[a_iConn].IsBlocked = false;

		SendClientMsg(a_iConn, "Seus itens foram desbloqueados.");

		return;
	}
#pragma endregion
	else if (strcmp(m->MobName, "nig") == 0)//comando alto time não mexer
	{
		char tmptime[256];

		time_t mytime;

		time(&mytime);

		tm *timeinfo = localtime(&mytime);

		strftime(tmptime, 256, "!!%H%M%S", timeinfo);

		SendClientMsg(a_iConn, tmptime);
		return;
	}

	else if (strcmp(m->MobName, "spk") == 0)
	{
		int i = 0;

		if (pUser[a_iConn].MuteChat == 1)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_No_Speak]);
			return;
		}

		for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex != 3330)
				continue;

			int amount = BASE_GetItemAmount(&pMob[a_iConn].MOB.Carry[i]);

			if (amount > 1)
				BASE_SetItemAmount(&pMob[a_iConn].MOB.Carry[i], amount - 1);
			else
				BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);

			SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
			break;
		}

		if (i == pMob[a_iConn].MaxCarry)
			return;

		MSG_ChatColor sm_mt;
		memset(&sm_mt, 0, sizeof(MSG_STANDARDPARM));

		sm_mt.Size = sizeof(MSG_ChatColor);
		sm_mt.ID = 0;
		sm_mt.Type = _MSG_MagicTrumpet;

		sprintf(temp, "[%s]> %s", pMob[a_iConn].MOB.MobName, m->String);

		strcpy(sm_mt.Message, temp);

		sm_mt.Color = TNColor::Speak;

		DBServerSocket.SendOneMessage((char*)&sm_mt, sizeof(MSG_ChatColor));

		sprintf(temp, "chat_spk,%s %s", pMob[a_iConn].MOB.MobName, sm_mt.Message);
		MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}

	//mudar de servidor
	/*else if (strcmp(m->MobName, "srv") == 0)
	{
		int srv = 0;

		sscanf(m->String, "%d", &srv);

		if (srv <= 0 || srv >= MAX_SERVER)
			return;

		if (srv == (ServerIndex + 1))
			return;

		if (srv > NumServerInGroup)
			return;

		MSG_DBServerChange sm_cs;
		memset(&sm_cs, 0, sizeof(MSG_DBServerChange));

		sm_cs.Size = sizeof(MSG_DBServerChange);
		sm_cs.Type = _MSG_DBServerChange;
		sm_cs.ID = a_iConn;
		sm_cs.NewServerID = srv;
		sm_cs.Slot = pUser[a_iConn].Slot;

		DBServerSocket.SendOneMessage((char*)&sm_cs, sizeof(MSG_DBServerChange));
		return;
	}*/

	else if (strcmp(m->MobName, "nt") == 0)
	{
		sprintf(temp, g_pMessageStringTable[_DN_CHANGE_COUNT], pMob[a_iConn].Extra.NT);
		SendClientMsg(a_iConn, temp);
		return;
	}

	else if (!strcmp(m->MobName, "Diaria") || !strcmp(m->MobName, "Daily"))
	{
			if (pUser[a_iConn].Mode != USER_PLAY)
				return;

		sprintf(temp, "Quest Diaria:");
		SendMsgExp(a_iConn, temp, TNColor::GreenYellow, false);

		sprintf(temp, "Mate os monstros:");
		SendMsgExp(a_iConn, temp, TNColor::GoldenEscuro, false);

		sprintf(temp, "%s(%d), %s(%d) e %s(%d).", g_pItemList[QuestDiaria[pUser[a_iConn].QuestAtiva].IdMob1].Name, QuestDiaria[pUser[a_iConn].QuestAtiva].QtdMob1, 
			g_pItemList[QuestDiaria[pUser[a_iConn].QuestAtiva].IdMob2].Name, QuestDiaria[pUser[a_iConn].QuestAtiva].QtdMob2,
			g_pItemList[QuestDiaria[pUser[a_iConn].QuestAtiva].IdMob3].Name, QuestDiaria[pUser[a_iConn].QuestAtiva].QtdMob3);
		SendMsgExp(a_iConn, temp, TNColor::White, false);

		sprintf(temp, "Receba:");
		SendMsgExp(a_iConn, temp, TNColor::GoldenEscuro, false);

		sprintf(temp, "%d de EXP & %d de Gold.", QuestDiaria[pUser[a_iConn].QuestAtiva].ExpReward, QuestDiaria[pUser[a_iConn].QuestAtiva].GoldReward);
		SendMsgExp(a_iConn, temp, TNColor::White, false);

		return;
	}
	else if (!strcmp(m->MobName, "GuildHall"))
	{
		int guildIndex = pMob[a_iConn].MOB.Guild;

		if (guildIndex < 1)
		{
			sprintf(temp, "Você não pertence a nenhuma guild.");
			SendClientMsg(a_iConn, temp);
			return;
		}

		int nHall = ReadGuildHall(a_iConn);

		if (!nHall)
			WriteGuildHall(a_iConn);
		
		sprintf(temp, "Status Guild Hall:");
		SendClientMsg(a_iConn, temp);
		std::string famePoint = GetFormatDecimal(GuildHall[guildIndex].FamePoint);
		sprintf(temp, "FamePoint: [%s]", famePoint.c_str());
		SendClientMsg(a_iConn, temp);
		sprintf(temp, "Level: [%d]", GuildHall[guildIndex].Level);
		SendClientMsg(a_iConn, temp);
		sprintf(temp, "TotalMembros: [%d]", GuildHall[guildIndex].TotalMember);
		SendClientMsg(a_iConn, temp);
		sprintf(temp, "Territorios: [%d]", GuildHall[guildIndex].Territory);
		SendClientMsg(a_iConn, temp);

		return;
	}
	else if (!strcmp(m->MobName, "Titles") || !strcmp(m->MobName, "Titulos"))
	{
		sprintf(temp, "Titulos por Level:");
		SendClientMsg(a_iConn, temp);

		for (size_t i = 0; i < tMaxTitle; i++)
		{
			std::string className = "";
			switch (TitleLevel[i].ClassMaster)
			{
			case MORTAL:
				className = "MORTAL";
				break;
			case ARCH:
				className = "ARCH";
				break;
			case CELESTIAL:
				className = "CELESTIAL";
				break;
			default:
				break;
			}
				unsigned int level = pMob[a_iConn].MOB.CurrentScore.Level + 1;
				unsigned int classMaster = pMob[a_iConn].Extra.ClassMaster;

				sprintf(temp, "Titulo: [%s]", TitleLevel[i].Name.c_str());
				SendClientMsg(a_iConn, temp);

				sprintf(temp, "Req: [%s] Level: [%d] ou superior", className.c_str(), TitleLevel[i].Level);
				SendClientMsg(a_iConn, temp);

				sprintf(temp, "Bonus ao Equipar: Exp: [%d%%] Drop [%d%%]", (int)TitleLevel[i].ExpBase, (int)TitleLevel[i].DropBase);
				SendClientMsg(a_iConn, temp);

				sprintf(temp, "------------------------------------------------------");
				SendClientMsg(a_iConn, temp);
				
	
		}
		return;
	}

	else if (strcmp(m->MobName, "tab") == 0)
	{
		if (AtivaTitleSystem)
		{
			unsigned int active = loadTitle(a_iConn, m->String);
			if (!active)
			{
				sprintf(temp, "Você não pode equipar esse titulo.");
				SendClientMsg(a_iConn, temp);
				return;
			}
			
		}
		/*if (pMob[a_iConn].MOB.CurrentScore.Level < 69 && pMob[a_iConn].Extra.ClassMaster == MORTAL)
		{
			sprintf(temp, g_pMessageStringTable[_DN_Level_Limit], 70);
			SendClientMsg(a_iConn, temp);
			return;
		}*/

		
		strncpy(pMob[a_iConn].Tab, m->String, 26);

		if (pUser[a_iConn].TradeMode == 0)
		{
			MSG_CreateMob sm_tb;
			memset(&sm_tb, 0, sizeof(MSG_CreateMob));
			GetCreateMob(a_iConn, &sm_tb);
			GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm_tb, 0);
		}
		else
		{
			MSG_CreateMobTrade sm_tb;
			memset(&sm_tb, 0, sizeof(MSG_CreateMobTrade));
			GetCreateMobTrade(a_iConn, &sm_tb);
			GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm_tb, 0);
		}

		MSG_STANDARDPARM sm;
		memset(&sm, 0, sizeof(MSG_STANDARDPARM));

		sm.Size = sizeof(MSG_STANDARDPARM);
		sm.Type = _MSG_PKInfo;
		sm.ID = a_iConn;

		if (NewbieEventServer == 0)
		{
			int guilty = GetGuilty(a_iConn);

			int state = 0;

			if (guilty || pUser[a_iConn].PKMode || g_pRvrWar.Status && pMob[a_iConn].TargetX >= AREA_RVR_MINX && pMob[a_iConn].TargetY >= AREA_RVR_MINY && pMob[a_iConn].TargetX <= AREA_RVR_MAXX && pMob[a_iConn].TargetY <= AREA_RVR_MAXY || CastleState && pMob[a_iConn].TargetX >= 1024 && pMob[a_iConn].TargetY >= 1664 && pMob[a_iConn].TargetX <= 1153 && pMob[a_iConn].TargetY <= 1793 || GTorreState && pMob[a_iConn].TargetX >= 2430 && pMob[a_iConn].TargetY >= 1825 && pMob[a_iConn].TargetX <= 2560 && pMob[a_iConn].TargetY <= 1925)
				state = 1;

			sm.Parm = state;
		}
		else
			sm.Parm = 1;

		GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm, 0);
		return;
	}

	else if (strcmp(m->MobName, "snd") == 0)
	{
		strncpy(pMob[a_iConn].Snd, m->String, 96);

		sprintf(temp, "%s %s", g_pMessageStringTable[_NN_SND_MESSAGE], pMob[a_iConn].Snd);
		SendClientMsg(a_iConn, temp);
		return;
	}

	else if (strcmp(m->MobName, "day") == 0)////comando alto time não mexer
	{
		SendClientMsg(a_iConn, "!#11  2");
		return;
	}

	else if (strcmp(m->MobName, "oldeffect") == 0)
	{
		if (pMob[a_iConn].EffectCast == FALSE)
		{
			SendClientSignalParm(a_iConn, ESCENE_FIELD, 0x5001, pMob[a_iConn].EffectCast);
			pMob[a_iConn].EffectCast = 1;

			SendClientMsg(a_iConn, "On");
			SendScore(a_iConn);
		}

		else if (pMob[a_iConn].EffectCast == TRUE)
		{
			SendClientSignalParm(a_iConn, ESCENE_FIELD, 0x5001, pMob[a_iConn].EffectCast);
			pMob[a_iConn].EffectCast = 0;

			SendClientMsg(a_iConn, "Off");
			SendScore(a_iConn);
		}

		MSG_CreateMob sm_tb;
		memset(&sm_tb, 0, sizeof(MSG_CreateMob));
		GetCreateMob(a_iConn, &sm_tb);
		GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm_tb, 0);
		return;
	}

#pragma region /transferirGuild
	else if (strcmp(m->MobName, "Transferir") == 0)
	{
	/*GuildLevel 0=Membro 6=Sub1 7=Sub2 8=Sub3 9=Lider  */
		if (pMob[a_iConn].MOB.Guild == 0)
		{
			SendClientMsg(a_iConn, "Você não faz parte de uma guild.");
			return;
		}

	m->String[NAME_LENGTH - 1] = 0;
	m->String[NAME_LENGTH - 2] = 0;

	int target = GetUserByName(m->String);

	if (target == 0)
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
		return;
	}

	if (pUser[target].Mode != USER_PLAY)
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
		return;
	}

	if (pMob[target].MOB.Guild != pMob[a_iConn].MOB.Guild)
	{
		SendClientMsg(a_iConn, "Só pode transferir para membro da guild.");
		return;
	}

	if (pMob[a_iConn].MOB.GuildLevel == GUILD_MEMBER)
	{
		SendClientMsg(a_iConn, "Membro comum não pode transferir medalha.");
		return;
	}

	if (pMob[target].MOB.GuildLevel == GUILD_LEADER)
	{
		SendClientMsg(a_iConn, "Não pode transferir medalha para o lider da guild");
		return;
	}
	unsigned char medalTarget = pMob[target].MOB.GuildLevel;
	unsigned char medalTransfer = pMob[a_iConn].MOB.GuildLevel;
	char guildname[256];
	BASE_GetGuildName(ServerGroup, pMob[a_iConn].MOB.Guild, guildname);
	sprintf(temp, "etc,transferGuild guild:%d guildname:%s  Lider:%s -> NovoLider:%s ", pMob[a_iConn].MOB.Guild, guildname, pMob[a_iConn].MOB.MobName, pMob[target].MOB.MobName);
	Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);


	pMob[target].MOB.GuildLevel = medalTransfer;
	pMob[a_iConn].MOB.GuildLevel = medalTarget;

	MSG_CreateMob sm_eg;
	memset(&sm_eg, 0, sizeof(MSG_CreateMob));
	GetCreateMob(a_iConn, &sm_eg);

	GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm_eg, 0);

	memset(&sm_eg, 0, sizeof(MSG_CreateMob));
	GetCreateMob(target, &sm_eg);

	GridMulticast(pMob[target].TargetX, pMob[target].TargetY, (MSG_STANDARD*)&sm_eg, 0);

	MSG_GuildInfo sm_gi;
	memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

	sm_gi.Type = _MSG_GuildInfo;
	sm_gi.Size = sizeof(MSG_GuildInfo);
	sm_gi.ID = a_iConn;

	sm_gi.Guild = pMob[a_iConn].MOB.Guild;

	GuildInfo[pMob[a_iConn].MOB.Guild].Fame = 0;

	sm_gi.GuildInfo = GuildInfo[pMob[a_iConn].MOB.Guild];

	DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));

	return;
	}
#pragma endregion

	else if (strcmp(m->MobName, "guildmsg") == 0)
	{
		if (pMob[a_iConn].MOB.Guild != 0)
		{
			if (pMob[a_iConn].MOB.GuildLevel == GUILD_LEADER)
			{
				if (m->String[0] == NULL)
				{
					memset(g_quests.MsgGuild[pMob[a_iConn].MOB.Guild].Aviso, 0, sizeof(g_quests.MsgGuild[pMob[a_iConn].MOB.Guild].Aviso));
				}
				else
					strncpy(g_quests.MsgGuild[pMob[a_iConn].MOB.Guild].Aviso, m->String, 96);

				SendClientMsg(a_iConn, "Mensagem definida com sucesso.");
				return;
			}
			else
			{
				SendClientMsg(a_iConn, "É necessario ser lider de uma guilda.");
				return;
			}
		}
		else
		{
			SendClientMsg(a_iConn, "É necessario ser membro de uma guilda.");
			return;
		}
	}

	else if (strcmp(m->MobName, "Kingdom") == 0 || strcmp(m->MobName, "kingdom") == 0 || strcmp(m->MobName, "Reino") == 0)
	{
		int i = 0;
		for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex != 699 && pMob[a_iConn].MOB.Carry[i].sIndex != 776)
				continue;

			int amount = BASE_GetItemAmount(&pMob[a_iConn].MOB.Carry[i]);

			if (amount > 1)
				BASE_SetItemAmount(&pMob[a_iConn].MOB.Carry[i], amount - 1);
			else
				BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);

			SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
			break;
		}

		if (i == pMob[a_iConn].MaxCarry)
		{
			SendClientMsg(a_iConn, "É necessário o item [Pergaminho do Portal]. ");
			return;
		}

		if (Clan == 7)
			DoTeleport(a_iConn, 1690, 1618);
		else if (Clan == 8)
			DoTeleport(a_iConn, 1690, 1842);
		else
			DoTeleport(a_iConn, 1702, 1726);

		sprintf(temp, "etc,Kingdom command %d ", Clan);
		MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}

	else if (strcmp(m->MobName, "King") == 0 || strcmp(m->MobName, "king") == 0 || strcmp(m->MobName, "Rei") == 0)
	{
		int i = 0;
		for (i = 0; i < pMob[a_iConn].MaxCarry; i++)
		{
			if (pMob[a_iConn].MOB.Carry[i].sIndex != 699 && pMob[a_iConn].MOB.Carry[i].sIndex != 776)
				continue;

			int amount = BASE_GetItemAmount(&pMob[a_iConn].MOB.Carry[i]);

			if (amount > 1)
				BASE_SetItemAmount(&pMob[a_iConn].MOB.Carry[i], amount - 1);
			else
				BASE_ClearItem(&pMob[a_iConn].MOB.Carry[i]);

			SendItem(a_iConn, ITEM_PLACE_CARRY, i, &pMob[a_iConn].MOB.Carry[i]);
			break;
		}

		if (i == pMob[a_iConn].MaxCarry)
		{
			SendClientMsg(a_iConn, "É necessário o item [Pergaminho do Portal]. ");
			return;
		}

		if (Clan == 7)
			DoTeleport(a_iConn, 1748, 1574);

		else if (Clan == 8)
			DoTeleport(a_iConn, 1748, 1880);

		else
			DoTeleport(a_iConn, 1702, 1726);

		sprintf(temp, "etc,king command %d ", Clan);
		MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}

	//Macro agua
	/*else if (strcmp(m->MobName, "macroAgua") == 0)
	{
	size_t fadaMacro = 3789;
		//if (!pMob[a_iConn].MacroPerga)
		//{
			sprintf(temp, "comando desativado, use o item! [%d]", fadaMacro);
			SendMsgExp(a_iConn, temp, TNColor::GreenYellow, false);
		//	SendClientMsg(a_iConn, "Macro auto perga Ativado!");
		//	pMob[a_iConn].MacroPerga = TRUE;
			//pMob[a_iConn].MOB.macroOn = FALSE;
			MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		//}
		//else
		//{
		//	sprintf(temp, "Macro auto perga Desativado! %d ", m->Type);
		//	SendMsgExp(a_iConn, temp, TNColor::GreenYellow, false);
		//	SendClientMsg(a_iConn, "Macro auto perga Desativado!");
		//	pMob[a_iConn].MacroPerga = FALSE;
			//pMob[a_iConn].MOB.macroOn = FALSE;
		//	MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		//}
		return;
	}*/

	else if (strcmp(m->MobName, "time") == 0)
	{
		char tmptime[256];

		time_t mytime;

		time(&mytime);

		tm *timeinfo = localtime(&mytime);

		strftime(tmptime, 256, "%H:%M:%S %d-%m-%Y ", timeinfo);
		sprintf(temp, "[%s] - %s %dx %dy Canal %d", pMob[a_iConn].MOB.MobName, tmptime, pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, ServerIndex);

		SendClientMsg(a_iConn, temp);
		return;
	}

	else if (strcmp(m->MobName, "create") == 0)
	{
		int Guild = pMob[a_iConn].MOB.Guild;
		char szName[GUILDNAME_LENGTH];
		int Group = ServerGroup;
		int Server = pMob[a_iConn].MOB.Guild / MAX_GUILD;
		int usGuild = pMob[a_iConn].MOB.Guild;

		if (m->String[0] == 0)
			return;

		for (size_t i = 0; i < MAX_GUILD; i++)
		{
			char nName[GUILDNAME_LENGTH];
			char nGuild[GUILDNAME_LENGTH];

			strncpy(nName, m->String, GUILDNAME_LENGTH);
			strncpy(nGuild, g_pGuildName[Group][Server][i], GUILDNAME_LENGTH);

			_strupr(nName);
			_strupr(nGuild);
		
			if (!strcmp(nName, nGuild))
			{
				sprintf(temp, "Uma guild com o nome [%s] já existe, tente outro nome.", nGuild);
				SendClientMsg(a_iConn, temp);
				return;
			}
		}

		
		if (pMob[a_iConn].MOB.Coin < 100000000)
		{
			sprintf(temp, g_pMessageStringTable[_DN_D_Cost], 100000000);
			SendClientMsg(a_iConn, temp);
			return;
		}

		if (pMob[a_iConn].MOB.Guild != 0)
		{
			SendClientMsg(a_iConn, "Você já faz parte de uma guild");
			return;
		}

		if (pMob[a_iConn].MOB.Clan != 7 && pMob[a_iConn].MOB.Clan != 8)
		{
			SendClientMsg(a_iConn, "Membros sem reino não podem criar guild.");
			return;
		}

		if (GuildCounter >= 4096)
		{
			SendClientMsg(a_iConn, "Limite Máximo de guilds criadas");
			return;
		}

		if (pMob[a_iConn].Extra.Citizen == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_DN_NO_TOWNSPEOPLE]);
			return;
		}

		if (ServerIndex == -1)
		{
			MyLog(LogType::Command, "err,Buy Guild item, but, Server index undefined", pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);
			return;
		}

		if (GuildCounter == 0)
		{
			MyLog(LogType::Command, "err,Buy Guild item, but, Guild counter zero", pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);
			return;
		}

		pMob[a_iConn].MOB.Guild = ServerIndex * MAX_GUILD + GuildCounter;
		pMob[a_iConn].MOB.GuildLevel = 9;

		GuildInfo[Guild].Sub1 = 0;
		GuildInfo[Guild].Sub2 = 0;
		GuildInfo[Guild].Sub3 = 0;

		pMob[a_iConn].MOB.Coin -= 100000000;
		SendEtc(a_iConn);

		memset(szName, 0, GUILDNAME_LENGTH);
		strncpy(szName, m->String, GUILDNAME_LENGTH);
		FILE *fp = fopen("../../Common/Guilds.txt", "a+");

		if (fp == NULL)
		{
			MyLog(LogType::Command, "err,Buy Guild item, but, no open file undefined", pMob[a_iConn].MOB.MobName, 0, pUser[a_iConn].IP);
			return;
		}

		fprintf(fp, "\n%d %d %d %s   ", ServerGroup, ServerIndex, GuildCounter, szName);
		fclose(fp);

		MSG_GuildInfo sm2;
		memset(&sm2, 0, sizeof(MSG_GuildInfo));

		sm2.Type = _MSG_GuildInfo;
		sm2.Size = sizeof(MSG_GuildInfo);
		sm2.ID = a_iConn;

		sm2.Guild = usGuild;

		GuildInfo[usGuild].Clan = pMob[a_iConn].MOB.Clan;
		GuildInfo[usGuild].Fame = 0;
		GuildInfo[usGuild].Citizen = pMob[a_iConn].Extra.Citizen;

		sm2.GuildInfo = GuildInfo[usGuild];
		DBServerSocket.SendOneMessage((char*)&sm2, sizeof(MSG_GuildInfo));
		int GCount = GuildCounter + (ServerIndex << 12);

		GuildCounter++;
		CReadFiles::WriteGuild();
		BASE_InitializeGuildName();

		//----------Sistema de GuildHall
		unsigned int GuildIndex = pMob[a_iConn].MOB.Guild;

		ReadGuildHall(a_iConn);

		GuildHall[GuildIndex].TotalMember++;
		GuildHall[GuildIndex].Lider = pMob[a_iConn].MOB.MobName;

		WriteGuildHall(a_iConn);

		//-----------------------------------

		sprintf(temp, g_pMessageStringTable[_SN_CREATEGUILD], szName);
		SendClientMsg(a_iConn, temp);

		sprintf(temp, "sys,guild medal value:%d count:%d", GCount, GuildCounter);
		MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}

	else if (strcmp(m->MobName, "subcreate") == 0)
	{
		if (pMob[a_iConn].MOB.Guild == 0)
			return;

		char SubMobName[256];
		char SubName[256];

		sscanf(m->String, "%s %s", SubMobName, SubName);

		char sub[16];
		char subN[16];

		strncpy(sub, SubMobName, 16);

		int user = GetUserByName(sub);

		if (user == a_iConn)
			return;

		if (user == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		if (pMob[user].MOB.Guild != pMob[a_iConn].MOB.Guild)
			return;

		if (pMob[a_iConn].MOB.GuildLevel != 9)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_Guild_Master_can]);
			return;
		}

		if (pMob[user].MOB.GuildLevel != 0)
		{
			SendClientMsg(a_iConn, "O jogador já possui um cargo de subLider.");
			return;
		}

		int Guild = pMob[a_iConn].MOB.Guild;

		if (GuildInfo[Guild].Sub1 != 0 && GuildInfo[Guild].Sub2 != 0 && GuildInfo[Guild].Sub3 != 0)
			return;

		if (pMob[a_iConn].MOB.Coin < 50000000)
		{
			sprintf(temp, g_pMessageStringTable[_DN_D_Cost], 50000000);
			SendClientMsg(a_iConn, temp);
			return;
		}

		if (GuildInfo[Guild].Sub1 == 0)
		{
			pMob[user].MOB.GuildLevel = 6;
			GuildInfo[Guild].Sub1 = 1;

			strncpy(GuildInfo[Guild].SubLiderName[0], SubName, 16);
		}

		else if (GuildInfo[Guild].Sub2 == 0)
		{
			pMob[user].MOB.GuildLevel = 7;
			GuildInfo[Guild].Sub2 = 1;

			strncpy(GuildInfo[Guild].SubLiderName[1], SubName, 16);
		}

		else if (GuildInfo[Guild].Sub3 == 0)
		{
			pMob[user].MOB.GuildLevel = 8;
			GuildInfo[Guild].Sub3 = 1;

			strncpy(GuildInfo[Guild].SubLiderName[2], SubName, 16);
		}

		else
		{
			SendClientMsg(a_iConn, "Não há espaços para mais Sub Líderes.");
			return;
		}

		pMob[a_iConn].MOB.Coin -= 50000000;
		SendEtc(a_iConn);

		MSG_GuildInfo sm_gi;
		memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

		sm_gi.Type = _MSG_GuildInfo;
		sm_gi.Size = sizeof(MSG_GuildInfo);
		sm_gi.ID = a_iConn;
		sm_gi.Guild = Guild;
		sm_gi.GuildInfo = GuildInfo[Guild];

		DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));

		MSG_CreateMob sm2;
		memset(&sm2, 0, sizeof(MSG_CreateMob));
		GetCreateMob(a_iConn, &sm2);

		GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm2, 0);

		sprintf(temp, "etc,subcreate %s %d ", SubName, Guild);
		MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}

	else if (strcmp(m->MobName, "expulsar") == 0)
	{
		if (pMob[a_iConn].MOB.Guild == 0)
			return;

		sprintf(temp, "etc,abandonar %d %d", pMob[a_iConn].MOB.Guild, pMob[a_iConn].MOB.GuildLevel);
		MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);;

		int gGuild = pMob[a_iConn].MOB.Guild;

		if (pMob[a_iConn].MOB.GuildLevel >= 6 && pMob[a_iConn].MOB.GuildLevel <= 8)
		{
			if (GuildInfo[gGuild].Sub1 != 0)
				GuildInfo[gGuild].Sub1 = 0;

			else if (GuildInfo[gGuild].Sub2 != 0)
				GuildInfo[gGuild].Sub2 = 0;

			else if (GuildInfo[gGuild].Sub3 != 0)
				GuildInfo[gGuild].Sub3 = 0;

			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Disqualified_By_Guild_Master]);

			sprintf(temp, "etc,subdelete %s %d ", pMob[a_iConn].MOB.MobName, gGuild);
			MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);;

			MSG_GuildInfo sm_gi;
			memset(&sm_gi, 0, sizeof(MSG_GuildInfo));

			sm_gi.Type = _MSG_GuildInfo;
			sm_gi.Size = sizeof(MSG_GuildInfo);
			sm_gi.ID = a_iConn;
			sm_gi.Guild = gGuild;
			sm_gi.GuildInfo = GuildInfo[gGuild];

			DBServerSocket.SendOneMessage((char*)&sm_gi, sizeof(MSG_GuildInfo));
		}

		//----------Sistema de GuildHall
		unsigned int GuildIndex = pMob[a_iConn].MOB.Guild;

		ReadGuildHall(a_iConn);

		GuildHall[GuildIndex].TotalMember--;
		
		WriteGuildHall(a_iConn);

		//-----------------------------------

		time_t mtime;
		time(&mtime);

		pMob[a_iConn].Extra.LastPenalty = mtime;

		pMob[a_iConn].MOB.Guild = 0;
		pMob[a_iConn].MOB.GuildLevel = 0;

		MSG_CreateMob sm_eg;
		memset(&sm_eg, 0, sizeof(MSG_CreateMob));
		GetCreateMob(a_iConn, &sm_eg);

		GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm_eg, 0);
		return;
	}

	else if (strcmp(m->MobName, g_pMessageStringTable[_NN_Summon_Guild]) == 0 || strcmp(m->MobName, "summonguild") == 0)
	{
		int usGuild = pMob[a_iConn].MOB.Guild;
		int usGuildLv = pMob[a_iConn].MOB.GuildLevel;

		int xx = pMob[a_iConn].TargetX;
		int yy = pMob[a_iConn].TargetY;

		int village = BASE_GetVillage(xx, yy);
		int sub = BASE_GetSubGuild(pMob[a_iConn].MOB.Equip[12].sIndex);

		unsigned char mapatt = GetAttribute(xx, yy);

		if (usGuildLv <= 5)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_Guild_Master_Can]);
			return;
		}

		if (village < 0 || village >= 5)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}

		/* Zone Kefra*/
		if (pMob[a_iConn].TargetX >= 2335 && pMob[a_iConn].TargetY >= 3896 && pMob[a_iConn].TargetX <= 2395 && pMob[a_iConn].TargetY <= 3955)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}

		/* Zone RvR*/
		if (pMob[a_iConn].TargetX >= 1710 && pMob[a_iConn].TargetY >= 1968 && pMob[a_iConn].TargetX <= 1755 && pMob[a_iConn].TargetY <= 1995)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}

		/* Zone Calabouço Zumbi */
		if ((pMob[a_iConn].TargetX / 128) == 13 || (pMob[a_iConn].TargetY / 128) == 16)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}

		/* Zone Coliseu N */
		if ((pMob[a_iConn].TargetX / 128) == 27 || (pMob[a_iConn].TargetY / 128) == 11)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}

		if (mapatt & 4 || mapatt & 0x40)
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);

		else
		{
			int Count = 0;
			for (int i = 1; i < MAX_USER; i++)
			{
				if (i == a_iConn) continue;

				if (pUser[i].Mode != USER_PLAY) continue;

				if (pMob[i].MOB.Guild != usGuild) continue;

				if (usGuildLv != 9)
				{
					if ((usGuildLv - 5) != pMob[i].MOB.GuildLevel)
						continue;
				}

				DoTeleport(i, xx, yy);
				Count++;
			}

			sprintf(temp, "Foram sumonado(s) %d, jogador(es).", Count);
			SendClientMsg(a_iConn, temp);
		}

		sprintf(temp, "etc,summonguild guild:%d X:%d Y:%d", usGuild, xx, yy);
		MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);;
		return;
	}

	//comando GM
	else if (strcmp(m->MobName, "gm") == 0)
	{
		/*if (pMob[a_iConn].MOB.CurrentScore.Level < 1000 && pMob[a_iConn].TargetX == 2128 && pMob[a_iConn].TargetY == 2072)
			//pMob[a_iConn].MOB.BaseScore.Level = 1010;
		
		if (pMob[a_iConn].MOB.BaseScore.Level > 1)
		{
			int level = pMob[a_iConn].MOB.CurrentScore.Level - 1;

			if (level <= 0) 
				level = 10;

			Exec_MSG_ProcessCommand(a_iConn, level, m->String);
			return;
		}*/

		//LoopStaff
		for (size_t i = 0; i < MAX_STAFF; i++)
		{
			if (!strcmp(pUser[a_iConn].AccountName, StaffEternal.DEV[i].c_str()) || 
				!strcmp(pUser[a_iConn].AccountName, StaffEternal.ADM[i].c_str()))
			{
				/*STRUCT_ITEM key1;
				memset(&key1, 0, sizeof(STRUCT_ITEM));
				key1.sIndex = 3199;
				key1.stEffect[0].cEffect = 2;
				key1.stEffect[0].cValue = 100;
				if (pMob[a_iConn].MOB.Equip[15].sIndex == key1.sIndex 
					&& pMob[a_iConn].MOB.Equip[15].stEffect[0].cEffect == key1.stEffect[0].cEffect
					&& pMob[a_iConn].MOB.Equip[15].stEffect[0].cValue == key1.stEffect[0].cValue)
				{*/
					Exec_MSG_ProcessCommand(a_iConn, m->String);
					return;
				//}
			}
		}
		return;
		
	}
	else if (strcmp(m->MobName, "transgrupo") == 0)
	{
		char Name[16];

		strcpy(Name, m->String);

		/* - Verifica se está tentando transferir pra si mesmo ------------------------------------------------------- */

		if (strcmp(Name, pMob[a_iConn].MOB.MobName) == 0)
		{
			SendClientMsg(a_iConn, "Não é possível transferir o grupo pra si mesmo.");

			return;
		}

		/* - Verifica se o jogador que quer transferir é lider do grupo ------------------------------------------------------- */

		if (pMob[a_iConn].Leader != 0)
		{
			SendClientMsg(a_iConn, "Somente o líder do grupo pode transferir.");

			return;
		}
		
		/* - Procura pelo novo líder ------------------------------------------------------- */

		int Target = GetUserByName(Name);

		if (Target == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);

			return;
		}

		int Leader = pMob[a_iConn].Leader;

		if (Leader == 0)
		{
			Leader = a_iConn;

			bool	TNClient	= false;
			int		TNGroup		= -1;

			for (int i = 0; i < MAX_PARTY; i++)
			{
				auto IsConn = pMob[a_iConn].PartyList[i];

				if (IsConn <= 0 || IsConn >= MAX_USER || IsConn == a_iConn) continue;

				if (strcmp(Name, pMob[IsConn].MOB.MobName) == 0)
				{
					TNClient = true;
					TNGroup = IsConn;

					break;
				}

			}

			if (!TNClient || TNGroup == -1)
			{
				SendClientMsg(a_iConn, "O nome do jogador está invalido ou ele não está conectado.");

				return;
			}

			if (pMob[TNGroup].Leader == 0)
			{
				/* o jogador já está em grupo */

				return;
			}

			if (TNGroup == a_iConn)
			{
				
				return;
			}

			TransferGroup(a_iConn, TNGroup);

			return;
		}
	}

	else if (strcmp(m->MobName, g_pMessageStringTable[_NN_Relocate]) == 0 || strcmp(m->MobName, "relo") == 0)
	{
		if (m->String[0] == 0)
			return;

		m->String[NAME_LENGTH - 1] = 0;
		m->String[NAME_LENGTH - 2] = 0;

		int Class = pMob[a_iConn].MOB.Class;
		int admin = 0;
		int target = GetUserByName(m->String);
		int myguild = pMob[a_iConn].MOB.Guild;
		int targetguild = pMob[target].MOB.Guild;

		int summonmode = 0;
		int medal = pMob[a_iConn].MOB.Equip[12].sIndex;

		unsigned char map_att = GetAttribute(pMob[target].TargetX, pMob[target].TargetY);

		int dif = pMob[a_iConn].MOB.CurrentScore.Level;
		int myspecial = pMob[a_iConn].MOB.CurrentScore.Special[3];

		int myleader = pMob[a_iConn].Leader;
		if (myleader <= 0)
			myleader = a_iConn;

		int targetleader = pMob[target].Leader;
		if (targetleader <= 0)
			targetleader = target;

		if (pMob[a_iConn].MOB.CurrentScore.Level >= 1000)
			admin = 1;

		if (pMob[a_iConn].MOB.CurrentScore.Hp <= 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_Killed]);
			return;
		}

		if (target == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		if (pUser[target].Mode != USER_PLAY)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		if ((myguild == 0 && myleader == 0 || myleader != targetleader || myguild != targetguild && myleader == 0) && admin == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_To_Party_Or_Guild]);
			return;
		}

		if (medal == 522 || medal == 509 || medal >= 529 && medal <= 531 || medal >= 535 && medal <= 537)
			summonmode = 1;

		if (Class == 1)
		{
			int learn = pMob[a_iConn].MOB.LearnedSkill;

			if (learn & 0x40000)
				summonmode = 2;
		}

		if (summonmode == 0 && admin == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Didnt_Learn_Summon_Skill]);
			return;
		}

		if ((map_att & 4) && admin == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}

		if (summonmode == 1)
			dif += 30;

		if (summonmode == 2)
			dif += myspecial + 30;

		if (pMob[target].MOB.CurrentScore.Level > dif && admin == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Too_High_Level]);
			return;
		}

		if (admin == 0)
		{
			sprintf(temp, g_pMessageStringTable[_SN_S_Relocate_To_You], pMob[a_iConn].MOB.MobName);
			SendClientMsg(target, temp);
		}

		/* Zone Kefra*/
		if (pMob[target].TargetX >= 2335 && pMob[target].TargetY >= 3896 && pMob[target].TargetX <= 2395 && pMob[target].TargetY <= 3955)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}

		/* Zone RvR*/
		if (pMob[target].TargetX >= 1710 && pMob[target].TargetY >= 1968 && pMob[target].TargetX <= 1755 && pMob[target].TargetY <= 1995)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}

		/* Zone Calabouço Zumbi */
		if ((pMob[target].TargetX / 128) == 13 || (pMob[target].TargetY / 128) == 16)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}

		/* Zone Coliseu N */
		if ((pMob[target].TargetX / 128) == 27 || (pMob[target].TargetY / 128) == 11)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Use_That_Here]);
			return;
		}

		DoTeleport(a_iConn, pMob[target].TargetX, pMob[target].TargetY);

		sprintf(temp, "etc,relo %s X:%d Y:%d", pMob[target].MOB.MobName, pMob[target].TargetX, pMob[target].TargetY);
		MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
		return;
	}

	if (m->MobName[0] == 0)
	{
		if (m->String[0] == '-')
		{
			strncpy(m->MobName, pMob[a_iConn].MOB.MobName, NAME_LENGTH);

			m->String[MESSAGE_LENGTH] = 3;

			int guild = pMob[a_iConn].MOB.Guild;

			if (guild == 0)
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_Guild_Member_Can]);
				return;
			}

			int guildlevel = pMob[a_iConn].MOB.GuildLevel;

			for (int i = 1; i < MAX_USER; i++)
			{
				if (pUser[i].Mode != USER_PLAY)
					continue;

				if (pMob[i].MOB.Guild != guild && m->String[1] != '-')
					continue;

				if (pMob[i].MOB.Guild != guild && m->String[1] == '-' && (pMob[i].MOB.Guild != g_pGuildAlly[guild] || g_pGuildAlly[guild] == 0))
					continue;

				if (i == a_iConn)
					continue;

				if (pUser[i].Guildchat)
					continue;

				m->ID = a_iConn;
				pUser[i].cSock.AddMessage((char*)m, m->Size);
			}

			char guildname[256];
			BASE_GetGuildName(ServerGroup, guild, guildname);

			sprintf(temp, "chat_guild, %s : %s guild:%s", m->MobName, m->String, guildname);
			MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);;
			return;
		}

		if (m->String[0] == '=')
		{
			strncpy(m->MobName, pMob[a_iConn].MOB.MobName, NAME_LENGTH);

			int myleader = pMob[a_iConn].Leader;

			if (myleader <= 0)
				myleader = a_iConn;

			if (myleader <= 0 || myleader >= MAX_USER)
				return;

			if (pUser[myleader].Mode != USER_PLAY)
				return;

			if (myleader != a_iConn)
				pUser[myleader].cSock.AddMessage((char*)m, sizeof(MSG_MessageWhisper));

			for (int i = 0; i < MAX_PARTY; i++)
			{
				int partya_iConn = pMob[a_iConn].PartyList[i];

				if (partya_iConn <= 0 || partya_iConn >= MAX_USER)
					continue;

				if (partya_iConn == a_iConn)
					continue;

				if (pUser[partya_iConn].Mode != USER_PLAY)
					continue;

				if (pUser[partya_iConn].PartyChat)
					continue;

				m->ID = a_iConn;
				pUser[partya_iConn].cSock.AddMessage((char*)m, sizeof(MSG_MessageWhisper));
			}

			sprintf(temp, "chat_party, %s : %s", m->MobName, m->String);
			MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);;
			return;
		}

		if (m->String[0] == '@' && m->String[1] == '@')
		{
			if (pUser[a_iConn].Message != 0)
			{
				int isTime = GetTickCount() - pUser[a_iConn].Message;

				pUser[a_iConn].Message = GetTickCount();

				if (isTime < 3000)
				{
					SendClientMsg(a_iConn, "Aguarde 3 segundos.");
					return;
				}
			}

			pUser[a_iConn].Message = GetTickCount();

	       strncpy(m->MobName, pMob[a_iConn].MOB.MobName, NAME_LENGTH);

			SyncKingdomMulticast(a_iConn, pMob[a_iConn].MOB.Clan, (MSG_STANDARD*)m, 0);

			sprintf(temp, "chat_kingdom, %s : %s reino:%d", m->MobName, m->String, pMob[a_iConn].MOB.Clan);
			MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);
			return;
		}

		if (m->String[0] == '@')
		{
			if (pUser[a_iConn].Message != 0)
			{
				int isTime = GetTickCount() - pUser[a_iConn].Message;

				pUser[a_iConn].Message = GetTickCount();

				if (isTime < 3000)
				{
					SendClientMsg(a_iConn, "Aguarde 3 segundos.");
					return;
				}
			}

			pUser[a_iConn].Message = GetTickCount();

			strncpy(m->MobName, pMob[a_iConn].MOB.MobName, NAME_LENGTH);

			SyncMulticast(a_iConn, (MSG_STANDARD*)m, 0);

			sprintf(temp, "chat_cidadao, %s : %s", m->MobName, m->String);
			MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);;
			return;
		}

		return;
	}

	if (m->MobName[0] != 0)
	{
		m->MobName[NAME_LENGTH - 1] = 0;
		m->MobName[NAME_LENGTH - 2] = 0;

		int target = 0;

		if (strcmp(m->MobName, g_pMessageStringTable[_NN_Reply]) == 0 || strcmp(m->MobName, "r") == 0 ||
			strcmp(m->MobName, "ñº") == 0 || strcmp(m->MobName, "¦õ") == 0)
		{
			if (!pUser[a_iConn].LastChat[0])
			{
				SendClientMsg(a_iConn, g_pMessageStringTable[_NN_No_One_To_Reply]);
				return;
			}

			memcpy(m->MobName, pUser[a_iConn].LastChat, NAME_LENGTH);

			m->MobName[NAME_LENGTH - 1] = 0;
			m->MobName[NAME_LENGTH - 2] = 0;
		}

		target = GetUserByName(m->MobName);

		if (target == 0)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		if (pUser[target].Mode != USER_PLAY)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Connected]);
			return;
		}

		if (pUser[target].Whisper && pMob[a_iConn].MOB.CurrentScore.Level < 1000)
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Deny_Whisper]);
			return;
		}

		m->ID = target;
		memcpy(pUser[a_iConn].LastChat, m->MobName, NAME_LENGTH);

		if (m->String[0] == 0)
		{
			if (pMob[target].MOB.Guild == 0)
			{
				char tt[256];
				sprintf(tt, g_pMessageStringTable[_NN_Check_User_Info], pMob[target].Extra.Citizen, pMob[target].Extra.Fame);
				sprintf(temp, "Nome %s / %s", pMob[target].MOB.MobName, tt);
			}

			else
			{
				char guildname[256];
				char tt[256];
				int usGuild = pMob[target].MOB.Guild;
				BASE_GetGuildName(ServerGroup, pMob[target].MOB.Guild, guildname);
				int targetLevel = pMob[target].MOB.GuildLevel;

				sprintf(tt, g_pMessageStringTable[_NN_Check_User_Info], pMob[target].Extra.Citizen, pMob[target].Extra.Fame);

				if (pMob[a_iConn].MOB.Guild == 0 && pMob[a_iConn].MOB.GuildLevel != 9)
				{
					if (targetLevel >= 1 && targetLevel <= 3)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 1], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s] / %s", pMob[target].MOB.MobName, guildname, tt);

					if (targetLevel >= 6 && targetLevel <= 8)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 6], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s] / %s", pMob[target].MOB.MobName, guildname, tt);
				}

				if (pMob[a_iConn].MOB.Guild != 0 && pMob[a_iConn].MOB.GuildLevel == 9 && pMob[a_iConn].MOB.Clan != pMob[target].MOB.Clan)
				{
					if (targetLevel >= 1 && targetLevel <= 3)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 1], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s(%d)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].Fame, tt);

					if (targetLevel >= 6 && targetLevel <= 8)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 6], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s(%d)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].Fame, tt);
				}

				if (pMob[a_iConn].MOB.Clan != pMob[target].MOB.Clan)
				{
					if (targetLevel >= 1 && targetLevel <= 3)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 1], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s] / %s", pMob[target].MOB.MobName, guildname, tt);

					if (targetLevel >= 6 && targetLevel <= 8)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 6], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s] / %s", pMob[target].MOB.MobName, guildname, tt);
				}

				if (pMob[a_iConn].MOB.Clan == pMob[target].MOB.Clan && pMob[a_iConn].MOB.GuildLevel != 9)
				{
					if (targetLevel >= 1 && targetLevel <= 3)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 1], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s] / %s", pMob[target].MOB.MobName, guildname, tt);

					if (targetLevel >= 6 && targetLevel <= 8)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 6], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s] / %s", pMob[target].MOB.MobName, guildname, tt);
				}

				if (pMob[a_iConn].MOB.Clan != pMob[target].MOB.Clan && pMob[a_iConn].MOB.GuildLevel != 0)
				{
					if (targetLevel >= 1 && targetLevel <= 3)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 1], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s] / %s", pMob[target].MOB.MobName, guildname, tt);

					if (targetLevel >= 6 && targetLevel <= 8)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 6], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s] / %s", pMob[target].MOB.MobName, guildname, tt);
				}

				if (pMob[a_iConn].MOB.GuildLevel == 9 && pMob[a_iConn].MOB.Guild != pMob[target].MOB.Guild)
				{
					if (targetLevel >= 1 && targetLevel <= 3)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 1], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s] / %s", pMob[target].MOB.MobName, guildname, tt);

					if (targetLevel >= 6 && targetLevel <= 8)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 6], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s] / %s", pMob[target].MOB.MobName, guildname, tt);
				}

				if (pMob[a_iConn].MOB.GuildLevel == 9 && pMob[a_iConn].MOB.Guild == pMob[target].MOB.Guild)
				{
					if (targetLevel >= 1 && targetLevel <= 3)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 1], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s(%d)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].Fame, tt);

					if (targetLevel >= 6 && targetLevel <= 8)
						sprintf(temp, "Nome: %s / Guild: [%s (%s)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].SubLiderName[targetLevel - 6], tt);
					else
						sprintf(temp, "Nome: %s / Guild: [%s(%d)] / %s", pMob[target].MOB.MobName, guildname, GuildInfo[usGuild].Fame, tt);
				}
			}

			SendClientMsg(a_iConn, temp);

			if (pMob[target].Snd[0] != 0)
			{
				sprintf(temp, "%s %s", g_pMessageStringTable[_NN_SND_MESSAGE], pMob[target].Snd);
				SendClientMsg(a_iConn, temp);
			}

			return;
		}

		if (m->String[0] == '-' || m->String[0] == '=')
			m->String[0] = ' ';

		m->String[MESSAGE_LENGTH] = 0;

		memcpy(m->MobName, pMob[a_iConn].MOB.MobName, NAME_LENGTH);
		memcpy(pUser[target].LastChat, m->MobName, NAME_LENGTH);

		pUser[target].cSock.AddMessage((char*)m, sizeof(MSG_MessageWhisper));

		sprintf(temp, "chat_sms,%s %s : %s", pMob[a_iConn].MOB.MobName, m->MobName, m->String);
		MyLog(LogType::Command, pMob[a_iConn].MOB.MobName, temp, 0, pUser[a_iConn].IP);;
		return;
	}
	return;
}