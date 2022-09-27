
#include "ProcessClientMessage.h"

void Exec_MSG_CapsuleInfo(int conn, char *pMsg)
{
	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)pMsg;

	int Index = m->Parm;

	m->ID = conn;
	m->Type = _MSG_DBCapsuleInfo;

	DBServerSocket.SendOneMessage((char*)m, sizeof(MSG_STANDARDPARM));
}