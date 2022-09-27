#include "FadaDourada.h"


BOOL AutoAmmount(int conn, STRUCT_ITEM* item)
{
	if (conn <= 0 || conn >= MAX_USER)
		return FALSE;

	if (pUser[conn].Mode != USER_PLAY)
		return FALSE;

	for (int i = 0; i < pMob[conn].MaxCarry; i++)
	{
		if (pMob[conn].MOB.Carry[i].sIndex == item->sIndex)
		{
			int ammount = BASE_GetItemAmount(&pMob[conn].MOB.Carry[i]);

			if (ammount < 1)
				ammount++;

			if (ammount < 120)
			{
				BASE_SetItemAmount(&pMob[conn].MOB.Carry[i], ammount + 1);
				SendItem(conn, ITEM_PLACE_CARRY, i, &pMob[conn].MOB.Carry[i]);
				return TRUE;
			}
			
		
		}
	}
	return FALSE;

}
