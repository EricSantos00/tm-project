
#include "ProcessClientMessage.h"

void Exec_MSG_Deposit(int a_iConn, char *pMsg)
{
	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)pMsg;

	if (pMob[a_iConn].MOB.CurrentScore.Hp == 0 || pUser[a_iConn].Mode != USER_PLAY)
	{
		SendHpMode(a_iConn);
		AddCrackError(a_iConn, 10, 1);
		return;
	}

	int coin = m->Parm;

	if (pMob[a_iConn].MOB.Coin >= coin && coin >= 0 && coin <= 2000000000)
	{
		int tcoin = coin + pUser[a_iConn].Coin;

		if (tcoin >= 0 && tcoin <= 2000000000)
		{
			pMob[a_iConn].MOB.Coin -= coin;
			pUser[a_iConn].Coin = tcoin;

			m->ID = ESCENE_FIELD;

			pUser[a_iConn].cSock.AddMessage((char*)m, sizeof(MSG_STANDARDPARM));

			SendCargoCoin(a_iConn);

			sprintf(temp, "etc,deposito no bau D:%d R:%d", coin, tcoin);
			Log(temp, pUser[a_iConn].AccountName, pUser[a_iConn].IP);
		}
		else
			SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_get_more_than_2G]);
	}
	else
		SendClientMsg(a_iConn, g_pMessageStringTable[_NN_Cant_Deposit_That_Much]);
}