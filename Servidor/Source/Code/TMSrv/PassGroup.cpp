#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>
#include <io.h>
#include <errno.h>
#include "..\Basedef.h"
#include "..\CPSock.h"
#include "..\ItemEffect.h"
#include "Language.h"
#include "CItem.h"
#include "Server.h"
#include "GetFunc.h"
#include "SendFunc.h"
#include "ProcessClientMessage.h"
#include "PassGroup.h"

void defPassGroup(int CliendID, char password[6])
{
	//pUser[CliendID].PartyPassword[6] = password[6];
	memmove(pUser[CliendID].PartyPassword, password, sizeof(pUser[CliendID].PartyPassword));
	char tmp[128];
	sprintf(tmp, "Senha [%s] foi definida com sucesso!", password);
	SendMsgExp(CliendID, tmp, TNColor::GoldenEscuro, false);
	//SendClientMsg(CliendID, tmp);

}

void getGroup(int CLientID, char PlayerName[256], char Password[6])
{
	int idUser = GetUserByName(PlayerName);
	size_t partCount;

	if (idUser == CLientID)
	{
		SendClientMsg(CLientID, "Você é lider desse grupo");
		return;
	}

	if (pUser[idUser].Mode != USER_PLAY)
	{
		SendClientMsg(CLientID, g_pMessageStringTable[_NN_Not_Connected]);
		return;
	}

	if (pMob[idUser].Leader != 0)
	{
		SendClientMsg(CLientID, "Este personagem não é lider do grupo.");
		return;
	}

	if (pMob[CLientID].Leader)
	{
		SendClientMsg(CLientID, g_pMessageStringTable[_NN_Dropped_Current_Party_First]);
		return;
	}


	if (strcmp(pUser[idUser].PartyPassword, Password) != 0)
	{
		SendClientMsg(CLientID, "Senha do grupo incorreta.");
		return;
	}

	int slot = 0;
	for (size_t i = 0; i < MAX_PARTY; i++)
	{
		if (pMob[idUser].PartyList[i])
			slot++;
	}


	for (partCount = 0; partCount < MAX_PARTY && pMob[idUser].PartyList[partCount]; partCount++)
	;

	if (partCount == MAX_PARTY)
	{
		SendClientMsg(CLientID, g_pMessageStringTable[_NN_Partys_Full]);
		return;
	}
	
	GetMobFromIndex(idUser)->PartyList[partCount] = CLientID;
	GetMobFromIndex(CLientID)->Leader = idUser;

	partCount++;

	if (!slot)
		SendAddParty(idUser, idUser, 0);

	if (!slot)
		SendAddParty(CLientID, CLientID, partCount);

	SendAddParty(CLientID, idUser, 0);
	SendAddParty(idUser, CLientID, partCount);

	for (int j = 0; j < MAX_PARTY; j++)
	{
		int pt = pMob[idUser].PartyList[j];

		if (pt)
		{
			if (pt != CLientID)
				SendAddParty(CLientID, pt, partCount);

			SendAddParty(pt, CLientID, j + partCount);
		}
	}

	char temp[256];
	sprintf(temp, "!Você entrou no grupo do jogador [%s]!", GetMobFromIndex(idUser)->MOB.MobName);
	SendClientMsg(CLientID, temp);

	sprintf(temp, "!Jogador [%s] entrou no seu grupo!", GetMobFromIndex(CLientID)->MOB.MobName);
	SendClientMsg(idUser, temp);

	return;


}