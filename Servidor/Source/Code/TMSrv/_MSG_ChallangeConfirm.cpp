
#include "ProcessClientMessage.h"

void Exec_MSG_ChallangeConfirm(int a_iConn, char *pMsg)
{
	MSG_STANDARDPARM2 *m = (MSG_STANDARDPARM2*)pMsg;

	int target = m->Parm1;

	if (target <= 0 || target >= MAX_MOB)
		return;

	int zone = pMob[target].MOB.Merchant - 6;

	if (zone >= 0 && zone < ValidGuild && zone != 4)
		Challange(a_iConn, target, 0);
}