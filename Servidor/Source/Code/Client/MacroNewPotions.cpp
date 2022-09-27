#include "main.h"

INT32 HKD_Macro_NewPotions(STRUCT_ITEM* item, INT32 type)
{
	if (type == 1) // pots de hp
	{
		switch (item->sIndex)
		{
		case 3431:
			return TRUE;
		default:
			return FALSE;
		}
	}

	 if (type == 2) // pots mp
	{
		switch (item->sIndex)
		{
		//case 3431:
		//	return TRUE;
		default:
			return FALSE;
		}
	}

	return FALSE;
}