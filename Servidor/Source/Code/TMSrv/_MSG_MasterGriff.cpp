#include "ProcessClientMessage.h"

void Exec_MSG_MasterGriff(int a_iConn, char *pMsg)
{
	MSG_MasterGriff *m = (MSG_MasterGriff*)pMsg;

	if (m->Ty == 1)
	{
		SendClientMsg(a_iConn, "Obrigado por viajar comigo!");
		return;
	}
	switch (m->WarpID)
	{
	case 0:
		DoTeleport(a_iConn, 2112, 2051);
		break;

	case 1:
		DoTeleport(a_iConn, 2372, 2099);
		break;

	case 2:
		DoTeleport(a_iConn, 2220, 1714);
		break;

	case 3:
		DoTeleport(a_iConn, 2365, 2249);
		break;

	case 4:
		DoTeleport(a_iConn, 1826, 1771);
		break;
	}

}
