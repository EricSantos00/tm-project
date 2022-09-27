#include "main.h"

//void SendMsgExp(char* Msg, TNColor Color32)
//{
//	if (Client.m_DisabledExpMsg)
//	{
//		DWORD dwOldProtectFlag_text;
//		VirtualProtect((void*)0x401000, 0x1F3000, PAGE_READWRITE, &dwOldProtectFlag_text);
//
//		*(DWORD*)(0x497667 + 1) = Color32;
//
//		static int sendClientMenssage_OL2 = 0x4975F4;
//
//		int *dat = *(int**)_PTR_DATA_;
//
//		__asm
//		{
//			PUSH Msg
//				MOV ECX, dat
//				CALL sendClientMenssage_OL2
//		}
//
//		*(DWORD*)(0x497667 + 1) = 0xFFFFAAAA;
//
//		VirtualProtect((void*)0x401000, 0x1F3000, dwOldProtectFlag_text, &dwOldProtectFlag_text);
//	}
//}

void SendMsgExp(TNColor Color, char* msg, ...)
{
	char buffer[256];
	va_list arglist;
	va_start(arglist, msg);
	vsprintf(buffer, msg, arglist);
	va_end(arglist);

	/*if (Client.m_DisabledExpMsg)
	{*/
	__asm
	{
		PUSH 0E54h

		MOV EAX, 005C5DD3h
		CALL EAX

		ADD ESP, 04h

		MOV ECX, EAX

		PUSH 00h
		PUSH 01h
		PUSH 077777777h
		PUSH 00h
		PUSH 041800000h
		PUSH 043960000h
		PUSH 00h
		PUSH 00h
		PUSH Color

		LEA EDX, DWORD PTR SS : [buffer]
		PUSH EDX

		MOV EAX, 0040739Bh
		CALL EAX

		PUSH EAX

		MOV ECX, DWORD PTR SS : [0x6F0AB0]
		MOV ECX, DWORD PTR DS : [ECX + 027CB4h]

		MOV EAX, 00408E53h
		CALL EAX
	}
	/*}*/
}