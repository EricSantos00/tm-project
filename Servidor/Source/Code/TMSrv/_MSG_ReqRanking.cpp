
#include "ProcessClientMessage.h"

void Exec_MSG_ReqRanking(int conn, char *pMsg)
{
	MSG_STANDARDPARM2 *m = (MSG_STANDARDPARM2*)pMsg;

	int tDuel = m->Parm1;
	int DuelParm = m->Parm2;

	if (DuelParm < 0 || DuelParm > 4 || tDuel <= 0 || tDuel >= MAX_USER)
		return;

	if (pUser[tDuel].Whisper)
	{
		SendClientMsg(conn, g_pMessageStringTable[_NN_Deny_Whisper]);
		return;
	}

	if (DuelParm != 4)
	{
		if (DuelParm != 1 && DuelParm != 2 || pMob[conn].MOB.GuildLevel && pMob[tDuel].MOB.GuildLevel)
		{
			pUser[conn].RankingTarget = tDuel;
			pUser[conn].RankingType = DuelParm;
									
			m->Parm1 = conn;
			m->ID = tDuel;
									
			pUser[tDuel].cSock.AddMessage((char*)m, sizeof(MSG_STANDARDPARM2));
			return;
		}
	}

	else
	{
		if (pUser[tDuel].Mode != USER_PLAY)
			return;

		if (pUser[tDuel].RankingTarget != conn)
			return;

		if (RankingProgress)
		{
			SendClientMsg(conn, g_pMessageStringTable[_NN_Battle_In_Progress]);
			SendClientMsg(tDuel, g_pMessageStringTable[_NN_Battle_In_Progress]);
			return;
		}

		if (pUser[tDuel].RankingType >= 0 && pUser[tDuel].RankingType <= 3)
		{
			SendEtc(conn);
			SendEtc(tDuel);
			DoRanking(pUser[tDuel].RankingType, conn, tDuel);

			sprintf(temp, "etc,reqranking %s vs %s type:%d", pMob[conn].MOB.MobName, pMob[tDuel].MOB.MobName, DuelParm);
			Log(temp, pUser[conn].AccountName, pUser[conn].IP);
			return;
		}
	}
}