#include "AutoBan.h"
#include "../ConfigIni.h"

using ConfigIni::nConfig;

void ReadAutoBan()
{
	for (size_t i = 0; i < MAX_USER; i++)
	{
		if (pUser[i].Mode != USER_PLAY)
			continue;
		std:string player = pMob[i].MOB.MobName;
		int status = nConfig::ReadAutoBan(PATH_AUTO_BAN, player);
		if (status)
		{
			if (!autoBan.Status)
				continue;

			if (!strcmp(autoBan.BanType.c_str(), "3horas"))
				SendBanAccount(i, Banned::Tempo3horas);
			
			else if (!strcmp(autoBan.BanType.c_str(), "3dias"))
				SendBanAccount(i, Banned::Tempo3dias);
		
			else if (!strcmp(autoBan.BanType.c_str(), "7dias"))
				SendBanAccount(i, Banned::Tempo7dias);
		
			else if (!strcmp(autoBan.BanType.c_str(), "15dias"))
				SendBanAccount(i, Banned::Tempo15dias);
		
			else if (!strcmp(autoBan.BanType.c_str(), "30dias"))
				SendBanAccount(i, Banned::Tempo30dias);
			
			else if (!strcmp(autoBan.BanType.c_str(), "permanente"))
				SendBanAccount(i, Banned::Permanente);
		
			else if (!strcmp(autoBan.BanType.c_str(), "mac"))
				SendBanAccount(i, Banned::Mac);
		
			else if (!strcmp(autoBan.BanType.c_str(), "analise"))
				SendBanAccount(i, Banned::Analise);
		
			else if (!strcmp(autoBan.BanType.c_str(), "ativa"))
				SendBanAccount(i, Banned::Ativa);

			autoBan.Status = FALSE;
			nConfig::WriteAutoBan(PATH_AUTO_BAN, player);
		}
	}
}
