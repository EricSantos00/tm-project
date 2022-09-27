
#include "ProcessClientMessage.h"

void Exec_MSG_InviteGuild(int conn, char *pMsg)
{
	MSG_STANDARDPARM2 *m = (MSG_STANDARDPARM2*)pMsg;

	

	int TargetID = m->Parm1;
	int InviteType = m->Parm2;

	if (TargetID <= 0 || TargetID >= MAX_USER)
		return;

	if (InviteType < 0 || InviteType >= 4)
		return;

	if (pMob[conn].MOB.Guild == 0)
	{
		SendClientMsg(conn, "Você não possui guild");
		return;
	}


	if (pMob[TargetID].MOB.Guild != 0)
	{
		SendClientMsg(conn, "O convidado já possui guild.");
		return;
	}

	if (pMob[conn].MOB.Clan != pMob[TargetID].MOB.Clan)
	{
		SendClientMsg(conn, "Só é possivel convidar jogadores do mesmo reino.");
		return;
	}


	if (pMob[conn].MOB.GuildLevel == 0)
	{
		SendClientMsg(conn, "Membro comum não pode recrutar jogadores");
		return;
	}

	//controle de população nas guilds
	unsigned int GuildIndex = pMob[conn].MOB.Guild;
	unsigned int ExpandGuild = MAX_GUILD_MEMBER + (MAX_GUILD_MEMBER * ((GuildHall[GuildIndex].Level + 1) / 4));
	unsigned int MaxGuildMember = ExpandGuild;

	if (GuildHall[GuildIndex].TotalMember >= MaxGuildMember)
	{
		sprintf(temp, "Sua guild esta cheia, aumente o level da guild para aumentar o limite maximo de membros");
		SendClientMsg(conn, temp);
		return;
	}

	if (InviteType != 0 && pMob[conn].MOB.GuildLevel != 9)
		return;

	time_t rawtime;
	tm *timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	if (timeinfo->tm_wday == 0)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_NotEquip_Saturday]);
		return;
	}

	if (rawtime < (pMob[TargetID].Extra.LastPenalty + 86400))
	{
		int rtime = (int)((86400 - (rawtime - pMob[TargetID].Extra.LastPenalty)) / 60 / 60);
		int rmin = (int)((86400 - (rawtime - pMob[TargetID].Extra.LastPenalty)) / 60 - (rtime * 60));

		sprintf(temp, "Penalidade ativa, aguarde {%d} horas e {%d} minutos.", rtime, rmin);
		SendClientMsg(TargetID, temp);
		SendClientMsg(conn, "Personagem está com penalidade de guild ativa.");
		return;
	}

	int custo = 4000000;

	if (InviteType != 0)
		custo = 100000000;

	if (pMob[conn].MOB.Coin < custo)
		return;

	pMob[conn].MOB.Coin -= custo;
	SendEtc(conn);

	pMob[TargetID].MOB.Guild = pMob[conn].MOB.Guild;

	int guildLevel = pMob[conn].MOB.GuildLevel;
	int type = 0;

	// Checamos se não é o líder, sendo assim, será o sublíder
	// A contagem de sublíder começa de 6 até 8.
	// Desta forma, fazemos o cálculo de 0~2 para saber de qual sublíder o usuário foi recrutado
	if (guildLevel != 9)
		type = guildLevel - 5;

	pMob[TargetID].MOB.GuildLevel = type;

	sprintf(temp, "etc,inviteguild guild:%d target_name:%s", pMob[conn].MOB.Guild, pMob[TargetID].MOB.MobName);
	Log(temp, pMob[conn].MOB.MobName, pUser[conn].IP);

	int Group = ServerGroup;
	int Server = pMob[conn].MOB.Guild / MAX_GUILD;
	int usGuild = pMob[conn].MOB.Guild;

	char guildname[256];

	BASE_GetGuildName(Group, usGuild, guildname);

	//----------Sistema de GuildHall
	ReadGuildHall(conn);

	GuildHall[GuildIndex].TotalMember++;
	
	WriteGuildHall(conn);

	//-----------------------------------

	sprintf(temp, g_pMessageStringTable[_SN_JOINGUILD], guildname);
	SendClientMsg(TargetID, temp);

	MSG_CreateMob sm_ig;
	memset(&sm_ig, 0, sizeof(MSG_STANDARDPARM2));

	GetCreateMob(TargetID, &sm_ig);

	GridMulticast(pMob[TargetID].TargetX, pMob[TargetID].TargetY, (MSG_STANDARD*)&sm_ig, 0);
}