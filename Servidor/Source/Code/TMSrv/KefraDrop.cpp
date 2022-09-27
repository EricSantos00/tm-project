#include "KefraDrop.h"

void KefraDrop(int killer)
{
	
	DWORD premiado = 0;
	unsigned short guildKilled = pMob[killer].MOB.Guild;

	

	for (size_t i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;

		int PosX = pMob[i].TargetX;
		int PosY = pMob[i].TargetY;

		int sortNum = rand() % MAX_DROP_KEFRA;

		STRUCT_ITEM* drop = &dropKefra[sortNum];

		//drop random 10 players da guild que matou kefra
		if (pMob[i].MOB.Guild == guildKilled 
			&& (PosX >= 2341 && PosX <= 2392)
			&& (PosY >= 3906 && PosY <= 3953))
		{
			if (premiado < MAX_DROP_KEFRA)
			{
				PutItem(i, drop);
				sprintf(temp, "!Você recebeu [%s] como recompensa por ajudar a matar kefra!", g_pItemList[drop->sIndex].Name);
				SendClientMsg(i, temp);
				premiado++;
				continue;
			}

			break;
		}

		//Buff Soul 1hora todos os personagens menos ARCHs

		int sAffect = GetEmptyAffect(i, 29);

		if (sAffect == -1 || pMob[i].Extra.ClassMaster == ARCH)
			continue;
		
			pMob[i].Affect[sAffect].Type = 29;
			pMob[i].Affect[sAffect].Level = 2;
			pMob[i].Affect[sAffect].Value = 0;
			pMob[i].Affect[sAffect].Time = AFFECT_1H;
			pMob[i].GetCurrentScore(i);
			SendScore(i);

			int Guild = pMob[killer].MOB.Guild;
				int Groups = ServerGroup;
				int Server = Guild / MAX_GUILD;

				char Name[256];
				char Buff[256] = "1hr Soul";

				BASE_GetGuildName(Groups, Guild, Name);
			sprintf(temp, "!A Guild [%s] derrotou Kefra,você recebeu [%s] aproveite!", Name,Buff);
			SendClientMsg(i, temp);
	}
	return;

}
