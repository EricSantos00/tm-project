
#include "ProcessClientMessage.h"

void Exec_MSG_SendAutoTrade(int conn, char *pMsg)
{
	MSG_SendAutoTrade *m = (MSG_SendAutoTrade*)pMsg;

	if (pMob[conn].MOB.CurrentScore.Hp <= 0 || pUser[conn].Mode != USER_PLAY)
	{
		SendHpMode(conn);
		AddCrackError(conn, 10, 88);
		RemoveTrade(conn);
		return;
	}

	if (pUser[conn].Trade.OpponentID)
	{
		RemoveTrade(pUser[conn].Trade.OpponentID);
		RemoveTrade(conn);
		return;
	}



	if (pUser[conn].TradeMode)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_CantWhenAutoTrade]);
		return;
	}
	//não verificar servidor novato enquanto tiver somente 1 canal
	/*
	if (NewbieEventServer == 0)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_NEWBIEEVENTSERVER]);
		return;
	}*/

	if (pUser[conn].IsBlocked)
	{
		SendClientMsg(conn, "Sua conta está com o bloqueio ativo para essa operação.");
		return;
	}

	int targetx = pMob[conn].TargetX;
	int targety = pMob[conn].TargetY;

	int Village = BASE_GetVillage(targetx, targety);

	if (targetx >= 2123 && targetx <= 2148 && targety >= 2139 && targety <= 2157)
	{
		RemoveTrade(conn);
		SendClientMsg(conn, g_pMessageStringTable[_NN_OnlyVillage]);
		return;
	}

	if (Village < 0 || Village >= 5)
	{
		RemoveTrade(conn);
		SendClientMsg(conn, g_pMessageStringTable[_NN_OnlyVillage]);
		return;
	}

	if (conn <= 0 || conn >= MAX_USER)
		return;

	for (int i = 0; i < MAX_AUTOTRADE; i++)
	{
		if (m->Coin[i] < 0 || (m->Coin[i] > 1999999999) || !m->Item[i].sIndex && m->Coin[i])
			return;

		if (m->Item[i].sIndex)
		{
			if (!m->Coin[i] || m->Item[i].sIndex == 508 || m->Item[i].sIndex == 3993 || m->Item[i].sIndex == 747 || m->Item[i].sIndex == 509 || m->Item[i].sIndex == 522
				|| m->Item[i].sIndex >= 526 && m->Item[i].sIndex <= 531 || m->Item[i].sIndex == 446 || m->CarryPos[i] < 0 || m->CarryPos[i] >= MAX_CARGO)
				return;

			if (BASE_GetItemAbility(&m->Item[i], EF_NOTRADE) != 0)
			{
				SendClientMsg(conn, g_pMessageStringTable[_NN_Cant_MoveItem]);									   
				return;
			}

			if (memcmp(&pUser[conn].Cargo[m->CarryPos[i]], &m->Item[i], sizeof(STRUCT_ITEM)))
			{
				RemoveTrade(conn);
				return;
			}
		}
	}

	m->Tax = g_pGuildZone[Village].CityTax;

	m->Title[MAX_AUTOTRADETITLE-1] = 0;
	m->Title[MAX_AUTOTRADETITLE-2] = 0;

	strncpy(pUser[conn].AutoTrade.Title, m->Title, MAX_AUTOTRADETITLE);

	pUser[conn].TradeMode = 1;
							   
	memcpy(&pUser[conn].AutoTrade, m, sizeof(MSG_SendAutoTrade));
							   
	m->Size = sizeof(MSG_SendAutoTrade);

	MSG_CreateMobTrade sm_cmt;
	memset(&sm_cmt, 0, sizeof(MSG_CreateMobTrade));

	SendAutoTrade(conn, conn);
	GetCreateMobTrade(conn, &sm_cmt);

	sm_cmt.Score.Con = 0;

	pUser[conn].ISTradTimer = timeGetTime();

	GridMulticast(targetx, targety, (MSG_STANDARD*)&sm_cmt, 0);

	if (pUser[conn].OnlyTrade)
		SendClientMsg(conn, "Somente a Conta principal participarar do evento Loja afk..");
	else
		SendClientMsg(conn, "Essa é sua Conta principal, você estara participando do evento Loja afk.");

	

	//GetUserLojaMac(conn);
		
}