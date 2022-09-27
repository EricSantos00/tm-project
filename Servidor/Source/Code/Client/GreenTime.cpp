#include "main.h"

// Definir a área X e Y, return 1 para toda kersef.
INT32 HKD_GreenTime_NewArea(INT32 posX, INT32 posY)
{
	if (posX == 2 && posY == 4)
		return TRUE;

	if (posX == 1 && posY == 31)
		return TRUE;

	if (posX == 20 && posY == 13)
		return TRUE;

	if (posX == 13 && posY == 16)
		return TRUE;

	if (posX == 8 && posY == 13)
		return TRUE;

	if (posX == 13 && posY == 15)
		return TRUE;

	if (posX == 27 && posY == 11)
		return TRUE;

	//Quests Mortais
	if (posX == 18 && posY == 16)
		return TRUE;

	if (posX == 17 && posY == 13)
		return TRUE;

	if (posX == 3 && posY == 30)
		return TRUE;

	if (posX == 5 && posY == 29)
		return TRUE;

	if (posX == 10 && posY == 31)
		return TRUE;

	//new coordenada
	if (posX == 20 && posY == 15)
		return TRUE;

	return FALSE;
}