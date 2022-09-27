
#include "ProcessClientMessage.h"
#include "GuildHall.h"

void Exec_MSG_Challange(int a_iConn, char *pMsg)
{
	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)pMsg;

	int target = m->Parm;

	if (target <= 0 || target >= MAX_MOB)
		return;

	int zone = pMob[target].MOB.BaseScore.Level;
	int npcStatus = pMob[target].MOB.BaseScore.Str;

	if (npcStatus >= 2000)
	{
		GuardianTerritory(a_iConn, zone, target);
		return;
	}
	if (zone < 0 || zone >= ValidGuild)
		return;

	if (zone != 5)
	{
		char ChargeName[256];
		char ChallName[256];

		int charge = g_pGuildZone[zone].ChargeGuild;
		int chall = g_pGuildZone[zone].ChallangeGuild;

		BASE_GetGuildName(ServerGroup, charge, ChargeName);
		BASE_GetGuildName(ServerGroup, chall, ChallName);

		if (WeekMode && WeekMode != 1 && WeekMode != 2 && WeekMode != 3)
		{
			if (WeekMode == 4)
			{
				time_t rawtime;
				tm *timeinfo;

				time(&rawtime);
				timeinfo = localtime(&rawtime);

				if (timeinfo->tm_wday == 1 && pMob[a_iConn].MOB.Guild && pMob[a_iConn].MOB.Guild == g_pGuildZone[zone].ChargeGuild && pMob[a_iConn].MOB.GuildLevel == 9)
				{
					long long Coin = (pMob[GuildImpostoID[zone]].MOB.Exp+1) / 1000000000;

					if(pMob[GuildImpostoID[zone]].MOB.Exp <= 0)
					{
						sprintf(temp, g_pMessageStringTable[_I64D_TOWN_TAX], pMob[target].MOB.Exp);
						SendMsgExp(a_iConn, temp, TNColor::CornflowerBlue, false);
						return;
					}


					if(Coin == 0)
					{
						long long bGold = pMob[GuildImpostoID[zone]].MOB.Exp;
						long long fGold = pMob[GuildImpostoID[zone]].MOB.Exp + pMob[a_iConn].MOB.Coin;

						if(fGold <= 2000000000)
						{
							SendClientMsg(a_iConn, g_pMessageStringTable[_NN_GIVE_TOWN_TAX]);

							pMob[GuildImpostoID[zone]].MOB.Exp = 0;

							pMob[a_iConn].MOB.Coin = (int)fGold;

							SendEtc(a_iConn);

							sprintf(temp, "etc,imposto recolhido(1) zone:%d coin:%llu", zone, bGold);
							Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);
							return;
						}
						else
						{
							SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_get_more_than_2G]);
							return;
						}
					}

					else
					{
						STRUCT_ITEM Item;
						memset(&Item, 0, sizeof(STRUCT_ITEM));

						Item.sIndex = 4011;

						int i = 0;

						for(i = (int)Coin; i > 0; i--)
						{
							if(PutItem(a_iConn, &Item) == 0)
								return;

							pMob[GuildImpostoID[zone]].MOB.Exp -= 1000000000;

							sprintf(temp, "etc,imposto recolhido(2) zone:%d coin:%d", zone, 1);
							Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);
						}

						SendClientMsg(a_iConn, g_pMessageStringTable[_NN_GIVE_TOWN_TAX]);
						return;
					}
				}
				sprintf(temp, g_pMessageStringTable[_I64D_TOWN_TAX], pMob[target].MOB.Exp);
				SendMsgExp(a_iConn, temp, TNColor::CornflowerBlue, false);
			}
			else if (WeekMode == 5)
				SendClientSignal(a_iConn, 0, _MSG_ReqChallange);
		}

		else
		{
			if (g_pGuildZone[zone].ChallangeGuild)
			{
				sprintf(temp, g_pMessageStringTable[_DS_S_Challanged], pChallangerMoney[zone], ChallName);
				SendSay(target, temp);
				sprintf(temp, g_pMessageStringTable[_SS_Champion_And_Challanger], ChargeName, ChallName);
				SendSay(target, temp);
			}
			else
			{
				sprintf(temp, g_pMessageStringTable[_SN_No_Challanger], ChargeName);
				SendSay(target, temp);
			}
		}
	}
}