
#include "ProcessClientMessage.h"

void Exec_MSG_AcceptParty(int conn, char *pMsg)
{
	MSG_AcceptParty *m = (MSG_AcceptParty*)pMsg;

	int myindex = conn;
	int leaderID = m->LeaderID;

	m->MobName[NAME_LENGTH - 1] = 0;

	if (leaderID <= 0 || leaderID >= MAX_USER)
	{
		Log("err,CNFParty leader out of range", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}

	if (m->Type == _MSG_AcceptParty && strcmp(pMob[leaderID].MOB.MobName, m->MobName))
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Not_Connected]);
		return;
	}

	if(leaderID != pMob[myindex].LastReqParty)
	{
		Log("err,CNFParty leader no send reqparty", pUser[conn].AccountName, pUser[conn].IP);
		CrackLog(conn, "PARTYHACK");
		return;
	}

	if (myindex <= 0 || myindex >= MAX_USER || myindex != conn)
	{
		Log("err,CNFParty fol out of range", pUser[conn].AccountName, pUser[conn].IP);
		return;
	}
	if (pMob[leaderID].Leader)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Other_Partys_Member]);
		return;
	}

	if (pUser[leaderID].Mode != USER_PLAY)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Not_Connected]);
		return;
	}
	if (pMob[myindex].Leader)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Dropped_Current_Party_First]);
		return;
	}

	int i = 0;
	for (i = 0; i < MAX_PARTY; i++)
	{
		if (pMob[myindex].PartyList[i] == 0)
			continue;

		SendClientMsg(conn, g_pMessageStringTable[_NN_Dropped_Current_Party_First]);
		return;
	}
	int leaderLV = pMob[leaderID].Extra.ClassMaster == MORTAL || pMob[leaderID].Extra.ClassMaster == ARCH ? pMob[leaderID].MOB.BaseScore.Level : pMob[leaderID].MOB.BaseScore.Level + MAX_CLEVEL + 1;
	int myLV = pMob[conn].Extra.ClassMaster == MORTAL || pMob[conn].Extra.ClassMaster == ARCH ? pMob[conn].MOB.BaseScore.Level : pMob[conn].MOB.BaseScore.Level + MAX_CLEVEL;

	if (myLV >= leaderLV - PARTY_DIF && myLV < leaderLV + PARTY_DIF || leaderLV >= 1000 || myLV >= 1000 || pMob[conn].Extra.ClassMaster == pMob[leaderID].Extra.ClassMaster)
	{
		if (!BrState || conn >= MAX_USER || BRItem <= 0 || pMob[conn].TargetX < 2604
			|| pMob[conn].TargetY < 1708 || pMob[conn].TargetX > 2648 || pMob[conn].TargetY > 1744)
		{
			int slot = 0;
			for (i = 0; i < MAX_PARTY; i++)
			{
				if (pMob[leaderID].PartyList[i])
					slot++;
			}

			for (i = 0; i < MAX_PARTY && pMob[leaderID].PartyList[i]; i++)
				;

			if (i == MAX_PARTY)
			{
				SendClientMsg(conn, g_pMessageStringTable[_NN_Partys_Full]);
				return;
			}

			pMob[leaderID].PartyList[i] = myindex;
			pMob[myindex].Leader = leaderID;
				
			i++;

			if (!slot)
				SendAddParty(leaderID, leaderID, 0);
				
			if (!slot)
				SendAddParty(myindex, myindex, i);
				
			SendAddParty(myindex, leaderID, 0);
			SendAddParty(leaderID, myindex, i);
				
			for (int j = 0; j < MAX_PARTY; j++)
			{
				int pt = pMob[leaderID].PartyList[j];

				if (pt)
				{
					if (pt != myindex)
						SendAddParty(myindex, pt, i);

					SendAddParty(pt, myindex, j + 1);
				}
			}

			sprintf(temp, "accept_party,%s aceitou party de %s.", pMob[myindex].MOB.MobName, pMob[leaderID].MOB.MobName);
			Log(temp, pUser[myindex].AccountName, pUser[myindex].IP);
		}
	}
	else
		SendClientMsg(conn, g_pMessageStringTable[_NN_Party_Level_Limit]);
}