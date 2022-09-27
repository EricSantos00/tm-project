#include "main.h"

bool SetItemPriceString(STRUCT_ITEM* item, char* str)
{
	for (int a = 0; a <= 2; a++)
	{
		if (item->stEffect[a].cEffect == 91)
		{
			sprintf(str, "Epoints: %d", item->stEffect[a].cValue);
			return TRUE;
		}
	}
	return FALSE;
}