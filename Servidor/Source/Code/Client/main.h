#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>

#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "hook.h"
#include "hooknaked.h"
#include "sendfunc.h"
#include <tchar.h>
#include <stdio.h>
#include "..\Basedef.h"
#include <mshtmhst.h>
#include <d3d9.h>
#include <tlhelp32.h>
#include "singleton.h"
#include "../ItemEffect.h"
using namespace std;

/* This client sender an protocol to server */
static void(*SendPacket)(char*, int) = (void(__cdecl*)(char*, int)) 0x054DA23;
static int32_t(*BS_GetItemAmount)(STRUCT_ITEM* item) = (int32_t(*)(STRUCT_ITEM*)) 0x539810;

__forceinline STRUCT_MOB GetChar()
{
	__asm
	{
		MOV EAX, DWORD PTR DS : [0x277C024]
		ADD EAX, 0x750
	}
}
__forceinline int GetClientID()
{
	__asm
	{
		MOV ECX, DWORD PTR DS : [0x277C024]
		ADD ECX, 0xDFC
		XOR EAX, EAX
		MOV AX, WORD PTR DS : [ECX]
	}
}
__forceinline short GetInvSlot(int slot)
{
	int pointer = (0x7C8 + (slot * 8));
	__asm
	{
		MOV ECX, DWORD PTR DS : [0x277C024]
		ADD ECX, pointer
		MOV EAX, DWORD PTR DS : [ECX]
	}
}


extern WYDClient Client;
static TNColor SpeakColor;
extern int SpeakChatColor;
extern 		STRUCT_CAPSULE file;
extern STRUCT_QUESTDIARIA QuestDay;
extern STRUCT_CLIENTPAC g_pSendClientPac;


