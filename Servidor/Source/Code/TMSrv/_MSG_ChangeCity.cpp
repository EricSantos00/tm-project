
#include "ProcessClientMessage.h"

void Exec_MSG_ChangeCity(int a_iConn, char *pMsg)
{
	int tx = pMob[a_iConn].TargetX;
	int ty = pMob[a_iConn].TargetY;

	int city = BASE_GetVillage(tx, ty);

	if (city >= 0 && city <= 4)
	{
		pMob[a_iConn].MOB.Merchant &= 0x3F;
		pMob[a_iConn].MOB.Merchant |= city << 6;
	}

	sprintf(temp, "etc,changecity city:%d X:%d Y:%d", city, tx, ty);
	Log(temp, pUser[a_iConn].AccountName, 0);
}