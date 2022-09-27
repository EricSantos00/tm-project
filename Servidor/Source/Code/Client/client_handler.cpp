#include "main.h"

void HandlerController(char* pBuffer, int a_iSize, int a_iType)
{
	Header* m = (Header*)pBuffer;

	switch (a_iType)
	{
		/* Envia para o servidor */
	case FALSE:
	{
		ClientSended(pBuffer, a_iSize);
		break;
	};

	/* Recebe do servidor */
	case TRUE:
	{
		ClientReceiver(pBuffer, a_iSize);

		break;
	}
	}
}

__declspec(naked) void HookNaked::NKD_ClientSended()
{
	__asm
	{
		PUSH 0
		LEA ECX, DWORD PTR SS : [EBP + 0x0C]
		PUSH ECX
		PUSH DWORD PTR SS : [EBP + 0x08]

		CALL HandlerController

		ADD ESP, 0x0C

		MOV DWORD PTR SS : [EBP - 0x0C] , 0x04

		MOV EAX, 0x0042588E
		JMP EAX
	}
}

__declspec(naked) void HookNaked::NKD_ClientReceiver()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x08]
		AND EAX, 0xFFFF
		MOV DWORD PTR SS : [EBP - 0x08] , EAX

		PUSH 1
		LEA ECX, DWORD PTR SS : [EBP - 0x08]

		PUSH ECX
		PUSH DWORD PTR SS : [EBP - 0x18]

		CALL HandlerController
		ADD ESP, 0x0C

		MOV EAX, 0x004253CC
		JMP EAX
	}
}