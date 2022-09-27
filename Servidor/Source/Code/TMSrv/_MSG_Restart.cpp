
#include "ProcessClientMessage.h"

void Exec_MSG_Restart(int conn, char *pMsg)
{
	MSG_STANDARD *m = (MSG_STANDARD*)pMsg;

	if (pUser[conn].Mode == USER_PLAY)
	{
		pMob[conn].MOB.CurrentScore.Hp = 2;

		pUser[conn].NumError = 0;

		for (int i = 0; i < MAX_AFFECT; i++)
		{
			int Type = pMob[conn].Affect[i].Type;

			if (Type == eSpeel_FM_Cancelamento || Type == eSpeel_FM_Veneno || Type == eSpeel_TK_Perseguicao)
			{
				pMob[conn].Affect[i].Type = 0;
			}
		}


		SendScore(conn);
		SendSetHpMp(conn);

		if(pMob[conn].TargetX >= 1017 && pMob[conn].TargetX <= 1290 && pMob[conn].TargetY >= 1911 && pMob[conn].TargetY <= 2183 && pMob[conn].MOB.Clan == 7)
			DoTeleport(conn, 1061+ rand()%3, 2129+rand()%3);
			
		else if(pMob[conn].TargetX >= 1017 && pMob[conn].TargetX <= 1290 && pMob[conn].TargetY >= 1911 && pMob[conn].TargetY <= 2183 && pMob[conn].MOB.Clan == 8)
			DoTeleport(conn, 1237+ rand()%3, 1966+rand()%3);
			
		else
			DoRecall(conn);

		sprintf(temp, "etc,restart char:%s hp:%d", pMob[conn].MOB.MobName, pMob[conn].MOB.CurrentScore.Hp);
		Log(temp, pUser[conn].AccountName, pUser[conn].IP);

		SendEtc(conn);
	}
	else
		SendHpMode(conn);
}