#include "ProcessClientMessage.h"

void NTask_GodGovernment(int a_iConn, int a_iTarget)
{
	int curkill = GetCurKill(a_iConn);
	int PKPoint = GetPKPoint(a_iConn);

	if (curkill >= 100)
	{
		PKPoint += 20;

		if (PKPoint >= 150)
			PKPoint = 150;

		SetCurKill(a_iConn, curkill - 100);
		SetPKPoint(a_iConn, PKPoint);

		sprintf(temp, "etc,resetpk curpk:%d name:%s conn:%d", PKPoint, pMob[a_iConn].MOB.MobName, a_iConn);
		MyLog(LogType::Quests, temp, 0, 0, pUser[a_iConn].IP);

		MSG_CreateMob sm_rpk;
		memset(&sm_rpk, 0, sizeof(MSG_CreateMob));
		GetCreateMob(a_iConn, &sm_rpk);

		GridMulticast(pMob[a_iConn].TargetX, pMob[a_iConn].TargetY, (MSG_STANDARD*)&sm_rpk, 0);

		SendEmotion(a_iConn, 14, 3);
		return;
	}

	SendSay(a_iTarget, g_pMessageStringTable[_NN_MOREKILLPOINT]);
	return;
}