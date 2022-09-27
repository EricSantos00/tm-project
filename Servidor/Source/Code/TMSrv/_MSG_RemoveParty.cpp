
#include "ProcessClientMessage.h"

void Exec_MSG_RemoveParty(int conn, char *pMsg)
{
	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)pMsg;

	int target = m->Parm;

	if(target <= 0 || target >= MAX_USER)
		target = conn;

	if(target != conn)
	{
		int i = 0;
		for(i = 0; i < MAX_PARTY; i++)
		{
			if(pMob[conn].PartyList[i] && pMob[conn].PartyList[i] == target)
				break;
		}

		if(i == MAX_PARTY)
			target = conn;
	}

	if (pMob[conn].Leader != -1 && pMob[conn].Leader)
		RemoveParty(conn);
		
	else
		RemoveParty(target);
}