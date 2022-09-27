#include "ProcessClientMessage.h"

void Exec_MSG_ReqTeleport(int a_iConn, char *pMsg)
{
	int posx = pMob[a_iConn].TargetX;
	int posy = pMob[a_iConn].TargetY;

	int Village = BASE_GetVillage(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY);
	int CityTax = g_pGuildZone[Village].CityTax;

	if ((posx / 4) == 491 && (posy / 4) == 443)
	{
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_By_Water_Scroll]);
		return;
	}

	int reqcoin = GetTeleportPosition(a_iConn, &posx, &posy);

	reqcoin += (reqcoin * CityTax) / 100;

	int clan = pMob[a_iConn].MOB.Clan;

	if (g_pGuildZone[4].Clan == clan)
		goto label_tel;
						
	if (reqcoin <= pMob[a_iConn].MOB.Coin)
	{
		if (reqcoin >= 0)
		{
			pMob[a_iConn].MOB.Coin -= reqcoin;
			SendEtc(a_iConn);

			int master = GuildImpostoID[4];
			if (GuildImpostoID[4] >= MAX_USER && master < MAX_MOB && pMob[master].Mode != MOB_EMPTY && pMob[master].MOB.Guild == g_pGuildZone[4].ChargeGuild)
			{
					if (pMob[master].MOB.Exp < 2000000000000)
						pMob[master].MOB.Exp += reqcoin / 2;
			}
		}

	label_tel:
		if (posx != pMob[a_iConn].TargetX || posy != pMob[a_iConn].TargetY)
		{
			DoTeleport(a_iConn, posx, posy);
			
			sprintf(temp, "etc,reqteleport char:%s X:%d Y:%d price:%d", pMob[a_iConn].MOB.MobName, pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, reqcoin);
			Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);
		}
	}
	else
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Not_Enough_Money]);
}