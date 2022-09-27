
#include "ProcessClientMessage.h"

void Exec_MSG_AccountSecure(int conn, char *pMsg)
{
	MSG_AccountSecure *m = (MSG_AccountSecure*)pMsg;

	if (conn <= 0 || conn >= MAX_USER)
		return;

	m->ID = conn;

	DBServerSocket.SendOneMessage((char*)m, sizeof(MSG_AccountSecure));
}