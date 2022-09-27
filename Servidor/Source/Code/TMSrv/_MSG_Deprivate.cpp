
#include "ProcessClientMessage.h"

void Exec_MSG_Deprivate(int conn, char *pMsg)
{
	MSG_STANDARDPARM *m = (MSG_STANDARDPARM*)pMsg;

	DoDeprivate(conn, m->Parm);
}