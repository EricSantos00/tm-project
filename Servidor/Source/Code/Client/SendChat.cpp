#include "main.h"

/* Não finalizado */
void CreateMessagePanel(char* msg, int color)
{
	static int CallBack = 0x04073CF;

	*(int*)0x04073CA = color;

	int* dat = *(int**)0x6F0AB0;

	__asm
	{
		PUSH msg
		MOV ECX, dat
		CALL CallBack
	}

	*(int*)0x04073CA = 0xFFFFAAAA;
}

int HKD_SendChat(char* command)
{
	//	if (*command != '@')
	//		return TRUE;

	if (strcmp(command, "/testando") == 0)
	{

		SendMsgExp(TNColor::GreenYellow, "testando");
		return FALSE;
	}

	return TRUE;
}