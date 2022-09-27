
#include "ProcessClientMessage.h"

void Exec_MSG_Withdraw(int a_iConn, char *pMsg)
{
	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)pMsg;

	if (pMob[a_iConn].MOB.CurrentScore.Hp == 0 || pUser[a_iConn].Mode != USER_PLAY)
	{
		SendHpMode(a_iConn);
		AddCrackError(a_iConn, 10, 2);
		return;
	}

	int coin = m->Parm;

	if (pUser[a_iConn].Coin >= coin && coin >= 0 && coin <= 2000000000)
	{
		int tcoin = coin + pMob[a_iConn].MOB.Coin;

		if (tcoin >= 0 && tcoin <= 2000000000)
		{
			pMob[a_iConn].MOB.Coin = tcoin;
			pUser[a_iConn].Coin -= coin;

			m->ID = 30000;

			pUser[a_iConn].cSock.AddMessage((char*)m, sizeof(MSG_STANDARDPARM));
			SendCargoCoin(a_iConn);

			sprintf(temp, "etc,retirada do bau V:%d R:%d", coin, pUser[a_iConn].Coin);
			Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);
		}
		else
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_get_more_than_2G]);
	}
	else
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Withdraw_That_Much]);
}