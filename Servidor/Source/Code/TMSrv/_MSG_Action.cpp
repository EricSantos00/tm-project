
#include "ProcessClientMessage.h"
#include "IlegalCMD.h"

void Exec_MSG_Action(int a_iConn, char *pMsg)
{
	MSG_Action *m = (MSG_Action*)pMsg;

	if (pUser[a_iConn].Mode != USER_PLAY)
	{
		SendHpMode(a_iConn);

		return;
	}

	if (pMob[a_iConn].MOB.CurrentScore.Hp == 0)
	{
		SendHpMode(a_iConn);

		AddCrackError(a_iConn, 5, 3);
		return;	
	}

	if (pUser[a_iConn].Trade.OpponentID)
	{
		RemoveTrade(pUser[a_iConn].Trade.OpponentID);
		RemoveTrade(a_iConn);
		return;
	}
	if (pUser[a_iConn].TradeMode)
	{
		RemoveTrade(a_iConn);
		return;
	}

	if((pMob[a_iConn].TargetX/128) == 9 && (pMob[a_iConn].TargetY/128) == 1 || (pMob[a_iConn].TargetX/128) == 8 && (pMob[a_iConn].TargetY/128) == 2 || (pMob[a_iConn].TargetX/128) == 10 && (pMob[a_iConn].TargetY/128) == 2)
	{
		if ((pMob[a_iConn].Extra.ClassMaster == CELESTIAL || pMob[a_iConn].Extra.ClassMaster == CELESTIALCS || pMob[a_iConn].Extra.ClassMaster == SCELESTIAL) && pMob[a_iConn].MOB.CurrentScore.Level >= 180)
		{
			DoRecall(a_iConn);

			return;
		}
	}

	if (pMob[a_iConn].TargetX /128 == 13 && pMob[a_iConn].TargetY /128 == 15 && !pMob[a_iConn].MOB.Clan)
	{
		DoRecall(a_iConn);
		return;
	}


	int movetime = m->ClientTick;
	int checktime = 0;

	if (CurrentTime <= 0x1D4C0)
		checktime = 0;
	else
		checktime = CurrentTime - 120000;

	//Skill Ilusão
	if (m->Type == _MSG_Action3)
	{
		if (pMob[a_iConn].MOB.Class != 3 || (pMob[a_iConn].MOB.LearnedSkill & 2) == 0)
		{
			if (pMob[a_iConn].MOB.CurrentScore.Level < MAX_LEVEL)
				if (AddCrackError(a_iConn, 10, 28) == TRUE)
					return;
		}

		/*if (m->Effect != TRUE && m->Speed != 6)
		{
			CloseUser(a_iConn);

			return;
		}*/

		int mana = g_pSpell[73].ManaSpent;

		if (pMob[a_iConn].MOB.CurrentScore.Mp < mana)
		{
			SendSetHpMp(a_iConn);
			return;
		}

		pMob[a_iConn].MOB.CurrentScore.Mp -= mana;
//		pUser[a_iConn].ReqMp -= mana;

		if (pUser[a_iConn].LastActionTick != 235543242 && movetime < pUser[a_iConn].LastIllusionTick + 900)
		{
			sprintf(temp, "err,illusion %d %d 900ms limit", movetime, pUser[a_iConn].LastIllusionTick);

			Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);
			AddCrackError(a_iConn, 1, 105);
			return;
		}
		if ((unsigned int)movetime > CurrentTime + 15000 || movetime < checktime)
		{
			sprintf(temp, "err,illusion %d %d 15000ms limit", movetime, CurrentTime);

			Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);
			Log("err,illution faster than 15 sec - MSG_ACTION", pUser[a_iConn].AccountName, pUser[a_iConn].IP);

			AddCrackError(a_iConn, 1, 104);
			return;
		}
		pUser[a_iConn].LastIllusionTick = movetime;
	}

	else if (m->Type == _MSG_Action)
	{
		if (pUser[a_iConn].LastActionTick != 235543242 && movetime < pUser[a_iConn].LastIllusionTick + 900)
		{
			sprintf(temp, "err,illusion %d %d 900ms limit", movetime, pUser[a_iConn].LastIllusionTick);

			Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);
			AddCrackError(a_iConn, 1, 103);
			return;
		}

		if ((unsigned int)movetime > CurrentTime + 15000 || movetime < checktime)
		{
			sprintf(temp, "err,illusion %d %d 15000ms limit", movetime, CurrentTime);

			Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);
			Log("err,illution faster than 15 sec - MSG_ACTION", pUser[a_iConn].AccountName, pUser[a_iConn].IP);

			AddCrackError(a_iConn, 1, 102);
			return;
		}

		//if (m->Effect != 0) { CloseUser(a_iConn); return; }

		pUser[a_iConn].LastIllusionTick = movetime;
	}

	else if (m->Type == _MSG_Action2)
	{
		if (pUser[a_iConn].LastMove == _MSG_Action2)
		{
			Log("err,can't send MSG_Stop continuously", pUser[a_iConn].AccountName, pUser[a_iConn].IP);
			AddCrackError(a_iConn, 1, 101);

			return;
		}

		//if (m->Effect != 0) { CloseUser(a_iConn); return; }
	}

	if (m->Speed > (pMob[a_iConn].MOB.CurrentScore.AttackRun & 0xF))
	{
		AddCrackError(a_iConn, 5, 4);

		sprintf(temp, "etc,diffrent movement. %d-%d", m->Speed, pMob[a_iConn].MOB.CurrentScore.AttackRun);
		Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);
		if (m->Speed >= 20 || pMob[a_iConn].MOB.CurrentScore.AttackRun >= 300) //speed ou whook detected 6290600
		{
			SendBanAccount(a_iConn, Banned::Analise);
			SaveInfoDetect(a_iConn, temp);
		}
		m->Speed = pMob[a_iConn].MOB.CurrentScore.AttackRun & 0xF;
	}

	int posx = pMob[a_iConn].TargetX;
	int posy = pMob[a_iConn].TargetY;
		
	if (/*m->Effect != 1 && m->Effect != 2 && */(m->TargetX < posx - VIEWGRIDX || m->TargetX  > posx + VIEWGRIDX || m->TargetY < posy - VIEWGRIDY || m->TargetY > posy + VIEWGRIDY))
	{
		if (m->TargetX < posx - VIEWGRIDX * 2 || m->TargetX > posx + VIEWGRIDX * 2 || m->TargetY < posy - VIEWGRIDY * 2 || m->TargetY > posy + VIEWGRIDY * 2)
		{
			MSG_Action sm_action;
			memset(&sm_action, 0, sizeof(MSG_Action));

			GetAction(a_iConn, posx, posy, (MSG_Action*)&sm_action);
			sm_action.Type = _MSG_Action3;
			sm_action.Speed = 6;

			pUser[a_iConn].cSock.SendOneMessage((char*)&sm_action, sizeof(MSG_Action));
		}
		AddCrackError(a_iConn, 1, 5);
		return;
	}

	if (m->TargetX >= 3378 && m->TargetX <= 3398 && m->TargetY >= 1427 && m->TargetY <= 1448)
	{
		int partyleader = pMob[a_iConn].Leader;

		if (partyleader <= 0)
			partyleader = a_iConn;

		//srand(time(NULL));
		if(partyleader != a_iConn || a_iConn != Pista[2].Party[0].LeaderID && a_iConn != Pista[2].Party[1].LeaderID && a_iConn != Pista[2].Party[2].LeaderID)
		{
			int rd = rand()%3;
			DoTeleport(a_iConn, PistaPos[2][rd][0], PistaPos[2][rd][1]);
			return;
		}
	}
		
	if (m->TargetX <= 0 || m->TargetX >= 4096 || m->TargetY <= 0 || m->TargetY >= 4096)
	{
		Log("err,action - viewgrid", pMob[a_iConn].MOB.MobName, pUser[a_iConn].IP);
		return;
	}

	if (m->TargetX != pMob[a_iConn].TargetX || m->TargetY != pMob[a_iConn].TargetY)
	{
		unsigned char mapAttribute = GetAttribute(m->TargetX, m->TargetY);

		if (mapAttribute & 0x80 && (pMob[a_iConn].MOB.CurrentScore.Level >= FREEEXP && pMob[a_iConn].MOB.CurrentScore.Level <= 999 || pMob[a_iConn].Extra.ClassMaster != MORTAL))
		{
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Newbie_zone]);

			DoRecall(a_iConn);
			return;
		}

		if (mapAttribute & 0x20)
		{
			if (pMob[a_iConn].MOB.CurrentScore.Level <= MAX_LEVEL)
			{
				int Zone = BASE_GetGuild(m->TargetX, m->TargetY);

				if (Zone >= 0 && Zone < MAX_GUILDZONE && pMob[a_iConn].MOB.Guild != g_pGuildZone[Zone].ChargeGuild)
				{
					SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Only_Guild_Members]);
					DoRecall(a_iConn);
					return;
				}
			}
		}
		
		CCastleZakum::CheckMove(a_iConn, m->TargetX, m->TargetY);

		pUser[a_iConn].LastMove = m->Type;

		pMob[a_iConn].LastSpeed = 0;

		strncpy(pMob[a_iConn].Route, m->Route, MAX_ROUTE);

		/*m->TargetY = 5000;
		m->TargetX = 5000;*/

		if (pMobGrid[m->TargetY][m->TargetX] && pMobGrid[m->TargetY][m->TargetX] != a_iConn)
		{
			int destx = m->TargetX;
			int desty = m->TargetY;

			int len = strlen(m->Route);

			int i = 0;

			GetEmptyMobGrid(a_iConn, &destx, &desty);

			for (i = len; i >= 0; i--)
			{
				if (pMobGrid[desty][destx] && pMobGrid[desty][destx] != a_iConn)
					continue;

				BASE_GetRoute(m->PosX, m->PosY, &destx, &desty, m->Route, i, (char*)pHeightGrid);
			}

			if (i == -1)
			{
				m->TargetX = destx;
				m->TargetY = desty;

				m->Effect = 0;

				pUser[a_iConn].cSock.SendOneMessage((char*)m, sizeof(m));
				return;
			}
			m->TargetX = destx;
			m->TargetY = desty;

			pUser[a_iConn].cSock.AddMessage((char*)m, sizeof(m));
		}

		memcpy(pMob[a_iConn].Route, m->Route, MAX_ROUTE);

		GridMulticast(a_iConn, m->TargetX, m->TargetY, (MSG_STANDARD*)pMsg);

		if (m->Type == _MSG_Action3)
		{
			pUser[a_iConn].cSock.SendOneMessage((char*)m, sizeof(MSG_Action));
			SendSetHpMp(a_iConn);
		}


		int len = strlen(pMob[a_iConn].Route);
		unsigned char Unk = 0;

		if (len > 0 && len < MAX_ROUTE-3)
		{
			Unk = pMob[a_iConn].Route[len] + 3;
			Unk = Unk - 48;

			if (Unk < 1 || Unk > 9)
				Unk = 0;
			else
				Unk = 16 * Unk;
		}

		pMob[a_iConn].MOB.CurrentScore.Merchant = pMob[a_iConn].MOB.CurrentScore.Merchant | Unk & 0xF0;
		pMob[a_iConn].MOB.BaseScore.Merchant = pMob[a_iConn].MOB.CurrentScore.Merchant;

		
		if (BrState && BRItem > 0)
		{
			int tx = pMob[a_iConn].TargetX;
			int ty = pMob[a_iConn].TargetY;

			int lvl = pMob[a_iConn].MOB.CurrentScore.Level;

			if (tx >= 2604 && ty >= 1708 && tx <= 2648 && ty <= 1744)
			{
				if (!BrGrid && lvl >= 100 && lvl < 1000)
					DoRecall(a_iConn);

				if (BrGrid == 1 && lvl >= 200 && lvl < 1000)
					DoRecall(a_iConn);
			}
		}

		if (Colo150Limit)
		{
			int lvl = pMob[a_iConn].MOB.CurrentScore.Level;

			if (lvl >= 150)
			{
				int tx = pMob[a_iConn].TargetX;
				int ty = pMob[a_iConn].TargetY;

				if (tx >= 2604 && ty >= 1708 && tx <= 2648 && ty <= 1744)
					DoRecall(a_iConn);

			}
		}
	}
}