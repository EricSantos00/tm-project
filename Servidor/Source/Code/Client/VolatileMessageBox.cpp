#include "main.h"

bool SetVolatileMessageBoxText(int itemID, char* text)
{
	switch (itemID)
	{
	case 3210:
	case 3211:
	case 3212:
		sprintf(text, "Deseja usar essa Box?");
		return true;
	case 3314:
		sprintf(text, "Deseja comer esse delicioso Frango Assado?");
		return true;
	case 3790:
	case 3791:
	case 3792:
		sprintf(text, "Deseja realmente utilizar esse contrato?");
		return true;
		//Bau
	case 3213:
	case 3793:
	case 3794:
		sprintf(text, "Deseja abrir esse Bau?");
		return true;
	case 4038:
	case 4039:
	case 4040:
	case 4041:
	case 4042:
		sprintf(text, "Deseja Teleportar para entrada da Quest?");
		return true;
	default:
		break;
	}

	return false;
}

int AddVolatileMessageItem(int itemID)
{
	switch (itemID)
	{
	case 3210:
	case 3211:
	case 3212:
	case 3213:
	case 3314:
		return 1;
	case 3790:
	case 3791:
	case 3792:
	case 3793:
	case 3794:
		return 1;
	case 4038:
	case 4039:
	case 4040:
	case 4041:
	case 4042:
		return 1;
	}
	return 0;
}