#include "ProcessClientMessage.h"

void Exec_MSG_ResponseQuiz(int a_iConn, char *pMsg)
{
	STRUCT_ITEM Item;
	int sCoin = goldQuiz;
	long long sExp = expQuiz;
	if (a_iConn <= 0 || a_iConn >= MAX_USER)
		return;

	MSG_ResponseQuiz*m = (MSG_ResponseQuiz*)pMsg;
	
		if (m->response == pMob[a_iConn].CorrectQuiz)
		{
			
			int vCoin = pMob[a_iConn].MOB.Coin + sCoin;
			long long vExp = pMob[a_iConn].MOB.Exp + sExp;
			if (vCoin > MAX_COIN)
			{
				sCoin = 0;
			}
			if (vExp > MAX_EXP)
			{
				sExp = 0;
			}
			pMob[a_iConn].MOB.Coin += sCoin;
			
			pMob[a_iConn].MOB.Exp += sExp;
			SendEtc(a_iConn);

			sprintf(temp, g_pMessageStringTable[_DD_QUIZ], sExp, sCoin);
			SendMsgExp(a_iConn, temp, TNColor::GreenYellow, false);
			SendEmotion(a_iConn, 100, rand() % 5);

			pMob[a_iConn].QuizError = 0;

			switch (pMob[a_iConn].QuizTerritory)
			{
			case 1://N
				DoTeleport(a_iConn, (3639 + rand() % 5 - 3), (3639 + rand() % 5 - 3));
				break;
			case 2://M
				DoTeleport(a_iConn, (3782 + rand() % 5 - 3), (3527 + rand() % 5 - 3));
				break;
			case 3://A
				DoTeleport(a_iConn, (3911 + rand() % 5 - 3), (3655 + rand() % 5 - 3));
				break;
			default:
				break;
			}
				
		}
		else
		{
			sprintf(temp, g_pMessageStringTable[_DD_NOT_QUIZ]);
			SendMsgExp(a_iConn, temp, TNColor::Azure, false);

			pMob[a_iConn].QuizError += 1;

				sprintf(temp, "Errou [%d] de [%d] tentativas", pMob[a_iConn].QuizError, MAX_QUIZ_ERROR);
				SendMsgExp(a_iConn, temp, TNColor::CornBlueName, false);
				Item.sIndex = pMob[a_iConn].ItemQuiz;

				if (pMob[a_iConn].ItemQuiz)
				PutItem(a_iConn, &Item);
		
		}

		pMob[a_iConn].CorrectQuiz = -1;

	return;
}