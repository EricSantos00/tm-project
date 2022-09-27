#include "ItensEntradaQuest.h"

void itemEnterQuest(MSG_UseItem* m, STRUCT_ITEM* Item, int a_iConn)
{

	switch (Item->sIndex)
	{
	case VELA:
		DoTeleport(a_iConn, 2370 + rand() % 5 - 3, 2106 + rand() % 5 - 3);
		break;
	case COLHEITA:
		DoTeleport(a_iConn, 2217 + rand() % 5 - 3, 1714 + rand() % 5 - 3);
		break;
	case CURA_BATEDOR:
		DoTeleport(a_iConn, 452 + rand() % 5 - 3, 3912 + rand() % 5 - 3);
		break;
	case MANA_BATEDOR:
		DoTeleport(a_iConn, 667 + rand() % 5 - 3, 3767 + rand() % 5 - 3);
		break;
	case EMBLEMA_GUARDA:
		DoTeleport(a_iConn, 1300 + rand() % 5 - 3, 4036 + rand() % 5 - 3);
		break;
	default:
		break;
	}

	SendItem(a_iConn, m->SourType, m->SourPos, Item);
}