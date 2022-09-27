#include "ProcessClientMessage.h"

void NTask_CarbuncleWind(int a_iConn, int a_iTarget)
{
	if (pMob[a_iConn].MOB.CurrentScore.Level > 200 || pMob[a_iConn].Extra.ClassMaster != MORTAL)
	{
		sprintf(temp, "Ajudo apenas iniciantes, %s !", pMob[a_iConn].MOB.MobName);
		SendSay(a_iTarget, temp);
		return;
	}

	SetAffect(a_iConn, 41, 320, 320);
	SetAffect(a_iConn, 43, 320, 320);
	SetAffect(a_iConn, 44, 320, 320);
	SetAffect(a_iConn, 45, 320, 320);

	pMob[a_iConn].GetCurrentScore(a_iConn);
	SendScore(a_iConn);

	sprintf(temp, "Sente-se mais forte, %s?", pMob[a_iConn].MOB.MobName);
	SendSay(a_iTarget, temp);

	sprintf(temp, "etc,carbuncle buff name:%s conn:%d", pMob[a_iConn].MOB.MobName, a_iConn);
	MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);
	return;
}