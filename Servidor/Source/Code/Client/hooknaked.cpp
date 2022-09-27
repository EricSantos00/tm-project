#include "main.h"

auto& WYD = HookMgr::instance();

bool HookNaked::Start()
{
	try
	{
		DWORD dwOldProtectFlag_text;
		VirtualProtect((int*)0x0401000, 0x5F0FFF - 0x0401000, 0x40, &dwOldProtectFlag_text);

		WYD.SetHook(eHookType::JGE, 0x004252D6, WYD.GetPtr(&HookNaked::NKD_ClientReceiver), 0);
		WYD.SetHook(eHookType::JMP, 0x00425887, WYD.GetPtr(&HookNaked::NKD_ClientSended), 0);

		strcpy((char*)0x622CDA, "  Eternal WYD");
		// strcpy((char*)0x5F3CB1, "ClientPatch.dll");

		strcpy((char*)0x613EC4, "Monstro"); /* Classe do personagem 'C' */
		strcpy((char*)0x613EB4, "[%s]"); /* Nick do personagem 'C' */

		/* SkillData - CheckSum*/
		WYD.SetValue<BYTE>(0x0053AC6A, 0xEB);

		/* ItemList - CheckSum */
		WYD.SetValue<BYTE>(0x0053ACE2, 0xEB);
		WYD.SetValue<BYTE>(0x0053AE7E, 0xEB);

		/* ExtraItem - CheckSum*/
		WYD.SetValue<BYTE>(0x0053ADA6, 0xEB);

		/* Ataque magico/Ataque Fisico - CheckSum*/
		WYD.SetValue<BYTE>(0x5000, 0x3FF);
		WYD.SetValue<BYTE>(0x5001, 0x5A);

		/* Chat Colorido */
		SpeakChatColor = TNColor::Default;
		
		/* Hook On - Client Speak Message */
		WYD.SetHook(eHookType::JMP, 0x004A0164, WYD.GetPtr(&HookNaked::NKD_SpeakChatColor), 0);

		/* Hook On - Item Description */
		WYD.SetHook(eHookType::JMP, 0x41C468, WYD.GetPtr(&HookNaked::NKD_ItemDescription), 4);

		/* Hook On - Correção Green Time Qualquer Mapa */
		JMP_NEAR(0x047DACA, HookNaked::NKD_GreenTime_NewArea, 1);

		/*  Hook Casas Decimal*/
		JMP_NEAR(0x041D1B4, HookNaked::NKD_ItemPrice_FormatDecimal_03, 1);
		JMP_NEAR(0x041CFD8, HookNaked::NKD_ItemPrice_FormatDecimal_02, 1);
		JMP_NEAR(0x0421356, HookNaked::NKD_ItemPrice_FormatDecimal);

		/* Troca de cor do TAB */
		JMP_NEAR(0x04E21DB, HookNaked::NKD_ChangeTabColor);

		/* Pula checksum dos arquivos trn (mapas) */
		WYD.SetHook(eHookType::JMP, 0x51E621, 0x51E6B4, 1);
		WYD.SetHook(eHookType::JMP, 0x52FB84, 0x52FC3A, 1);

		/* New Itens Day - Time */
		WYD.SetHook(eHookType::JMP, 0x0041A51E, WYD.GetPtr(&HookNaked::NKD_NewItensDays_1));
		WYD.SetHook(eHookType::JMP, 0x0041A535, WYD.GetPtr(&HookNaked::NKD_NewItensDays_2));
		//WYD.SetHook(eHookType::JMP, 0x41A14D, WYD.GetPtr(&Client::NKD_ValidadeFadas), 0);
		WYD.SetHook(eHookType::JMP, 0x41A87D, WYD.GetPtr(&HookNaked::NKD_ValidadeTrajes), 0);
		WYD.SetHook(eHookType::JMP, 0x41A56E, WYD.GetPtr(&HookNaked::NKD_Validade), 0);

		/* Item Price String */
		WYD.SetHook(eHookType::JMP, 0x41CFCD, WYD.GetPtr(&HookNaked::NKD_ItemPriceString), 1);

		/* Fix Pacote 0x3BB */
		JMP_NEAR(0x0048B04F, HookNaked::NKD_ProcessClientMessage_03BBh, 1);

		// ReadMessage
		//JGE_NEAR(0x4252D6, NKD_ReadMessage);

		/*New mounts day */
		JMP_NEAR(0x50C2EB, HookNaked::NKD_montaria, 2);
		JMP_NEAR(0x50ABB8, HookNaked::NKD_montaria2, 2);
		WYD.SetHook(eHookType::JMP, 0x50C52A, WYD.GetPtr(&HookNaked::NKD_noSancFace));
		WYD.SetHook(eHookType::JMP, 0x50C574, WYD.GetPtr(&HookNaked::NKD_noSancID));

		// ITEM BOX
		JMP_NEAR(0x422007, NKD_AddVolatileMessageItem, 2); //421F1A
		JMP_NEAR(0x41FB30, NKD_AddVolatileMessageBox, 5);

		WYD.SetHook(eHookType::JMP, 0x4205FC, WYD.GetPtr(&HookNaked::NKD_AddAmountItem), 4);

		WYD.SetHook(eHookType::JMP, 0x4676C5, WYD.GetPtr(&HookNaked::NKD_SendChat));

		/* Modificações nos atributos da esferas.*/
		JMP_NEAR(0x005385AC, HookNaked::NKD_GetItemAbility_Esfera, 3);

		/* Adicionar novos pots hp/mp no macro */
		//JMP_NEAR(0x0045169A, HookNaked::NKD_Macro_NewPotions_HP);
		//JMP_NEAR(0x00451BA0, HookNaked::NKD_Macro_NewPotions_MP);

		/* Fix Macro Mage */
		JE_NEAR(0x04974C7, HookNaked::NKD_FixMageMacro);
		JE_NEAR(0x04974D7, HookNaked::NKD_FixMageMacro);


		/* KeyPress_NewButton */
		JMP_NEAR(0x045488D, HookNaked::NKD_KeyPress_NewButton, 1);

		/* Pula limit dos news buff */
		*(char*)(0x005495A8) = 100;
		*(char*)(0x0047B0AB) = 100;
		*(char*)(0x0044B476) = 100;
		*(char*)(0x00476CF1) = 100;

		/*DNS*/
		//WYD.SetHook(eHookType::JMP, 0x0053A3A7, WYD.GetPtr(&HookNaked::NKD_DNS), 0);

		VirtualProtect((int*)0x0401000, 0x5F0FFF - 0x0401000, dwOldProtectFlag_text, &dwOldProtectFlag_text);

		return TRUE;
	}
	catch (...)
	{
		return FALSE;
	}
}

__declspec(naked) void HookNaked::NKD_KeyPress_NewButton()
{
	__asm
	{
		CMP EAX, 01h
		JE lbl_end

		XOR EAX, EAX
		MOV AL, BYTE PTR SS : [EBP + 08h]
		PUSH EAX

		CALL HKD_KeyPress_NewButton

		TEST EAX, EAX
		JE lbl_xor

		MOV EAX, 01h
		JMP lbl_end

		lbl_xor :
		XOR EAX, EAX

			lbl_end :
		MOV ESP, EBP
			POP EBP

			RETN 08h
	}
}

__declspec(naked) void HookNaked::NKD_SendChat()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x98]
		MOV EDX, DWORD PTR DS : [EAX]
		MOV ECX, DWORD PTR SS : [EBP - 0x98]
		CALL DWORD PTR DS : [EDX + 0x88]

		PUSH EAX
		CALL HKD_SendChat
		ADD ESP, 0x08

		TEST EAX, EAX
		JNZ chk_other_cmd

		MOV EAX, 0x01
		MOV ECX, 0x473794
		JMP ECX

		chk_other_cmd :

		MOV ECX, 0x467740
			JMP ECX
	}
}

__declspec(naked) void HookNaked::NKD_Macro_NewPotions_MP()
{
	__asm
	{
		CMP DWORD PTR SS : [EBP - 018h] , 00h
		JE lbl_continueLoop

		PUSH 02h

		MOV ECX, DWORD PTR SS : [EBP - 018h]
		MOV EDX, DWORD PTR DS : [ECX + 0670h]

		PUSH EDX

		CALL HKD_Macro_NewPotions
		ADD ESP, 08h

		TEST EAX, EAX
		JE lbl_continueLoop

		MOV EAX, 00451688h
		JMP EAX

		lbl_continueLoop :
		MOV EAX, 00451588h
			JMP EAX
	}
}

__declspec(naked) void HookNaked::NKD_Macro_NewPotions_HP()
{
	__asm
	{
		CMP DWORD PTR SS : [EBP - 018h] , 00h
		JE lbl_continueLoop

		PUSH 01h

		MOV ECX, DWORD PTR SS : [EBP - 018h]
		MOV EDX, DWORD PTR DS : [ECX + 0670h]

		PUSH EDX

		CALL HKD_Macro_NewPotions
		ADD ESP, 08h

		TEST EAX, EAX
		JE lbl_continueLoop

		MOV EAX, 00451688h
		JMP EAX

		lbl_continueLoop :
		MOV EAX, 00451588h
			JMP EAX
	}
}

__declspec(naked) void HookNaked::NKD_GetItemAbility_Esfera()
{
	static const DWORD dwContinue[2] = { 0x005385B4, 0x005388BF };
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 0Ch]
		AND EAX, 0FFh

		PUSH EAX

		PUSH DWORD PTR SS : [EBP + 08h]

		CALL HKD_GetItemAbility_Esferas
		ADD ESP, 08h

		TEST EAX, EAX
		JE lbl_continue

		JMP dwContinue + 04h

		lbl_continue :
		MOV EAX, DWORD PTR SS : [EBP + 0Ch]
			AND EAX, 0FFh

			JMP dwContinue
	}
}

__declspec(naked) void HookNaked::NKD_Validade()
{
	__asm {

		MOV EDX, DWORD PTR SS : [EBP - 0x8]
		MOV EAX, DWORD PTR DS : [EDX + 0x670]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0xAC]
		PUSH ECX
		CALL FormataValidade // validade global
		ADD ESP, 0xC
		PUSH 0x41A7BC
		RETN
	}


}

__declspec(naked) void HookNaked::NKD_ValidadeTrajes()
{
	__asm {
		MOV EDX, DWORD PTR SS : [EBP - 0x8]
		MOV EAX, DWORD PTR DS : [EDX + 0x670]
		PUSH EAX
		LEA ECX, DWORD PTR SS : [EBP - 0xAC]
		PUSH ECX
		CALL FormataValidadeTraje // to falando oq agr? ouvi
		ADD ESP, 0xC
		PUSH 0x41AACB
		RETN
	}
}

__declspec(naked) void HookNaked::NKD_ValidadeFadas()
{
	__asm {
		// 3 argumentoss  msg ta certa?
		LEA ECX, DWORD PTR SS : [EBP - 0xA18]
		PUSH ECX
		LEA ECX, DWORD PTR SS : [EBP - 0xAC] // msg ta certo?
		PUSH ECX
		CALL FormataValidadeFada // to falando oq agr? ouvi
		ADD ESP, 0xC
		PUSH 0x41A176
		RETN

	}
}

__declspec(naked) void HookNaked::NKD_AddAmountItem()
{
	__asm {
		MOV EAX, DWORD PTR SS : [EBP - 0x60]
		MOV ECX, DWORD PTR DS : [EAX + 0x670]
		MOVSX EDX, WORD PTR DS : [ECX]
		CMP EDX, 0xC80
		JL lblNext
		CMP EDX, 0xC94
		JG lblNext
		JMP lblContinueExec

		lblNext :
		PUSH EDX
			CALL AddAmountItem
			TEST AL, AL
			JE lblContinueExec
			MOV BYTE PTR SS : [EBP - 0x5C] , 1
			JMP lblContinueExec

			lblContinueExec :
		PUSH 0x420626
			RETN
	}
}

__declspec(naked) void HookNaked::NKD_ProcessClientMessage_03BBh()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 04h]
		XOR EDX, EDX

		MOV DX, WORD PTR DS : [ECX + 0Eh]

		MOV DWORD PTR SS : [EBP - 08Ch] , EDX

		MOV EAX, DWORD PTR SS : [EBP - 04h]
		XOR ECX, ECX

		MOV CX, WORD PTR DS : [EAX + 0Ch]

		MOV DWORD PTR SS : [EBP - 088h] , ECX

		MOV EAX, 0048B076h
		JMP EAX
	}
}

__declspec(naked) void HookNaked::NKD_ItemPriceString()
{
	__asm
	{
		LEA EAX, DWORD PTR SS : [EBP - 0x11D4] // MSG
		PUSH EAX
		MOV EAX, DWORD PTR SS : [EBP - 0x8]
		MOV ECX, DWORD PTR DS : [EAX + 0x670]
		PUSH ECX
		CALL SetItemPriceString
		TEST AL, AL
		JE lblContinueExec
		PUSH 0x41D05B
		RETN

		lblContinueExec :
		FLD DWORD PTR SS : [EBP - 0x11E4]
			PUSH 0x41CFD3
			RETN
	}
}

__declspec(naked) void HookNaked::NKD_FixMageMacro()
{
	__asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x11C]
		// Diferente do Macro Continuo, então pula
		CMP DWORD PTR DS : [ECX + 0x8A3A0] , 0x0
		JNZ lbl_JMP
		PUSH 0x004970F9
		RETN

		lbl_JMP :
		PUSH 0x004972E5
			RETN
	}
}


__declspec(naked) void HookNaked::NKD_NewItensDays_1()
{
	__asm
	{
		CMP EAX, 0x0F8C
		JL LoopOriginal
		PUSH 0x41A529
		RETN
		LoopOriginal :
		PUSH EAX
			CALL NewItensDay
			TEST AL, AL
			JE VoltaOriginal
			PUSH 0x41A56E
			RETN

			VoltaOriginal :
		PUSH 0x41A825
			RETN
	}
}

__declspec(naked) void HookNaked::NKD_NewItensDays_2()
{
	__asm
	{
		CMP EAX, 0x0F9F
		JG LoopOriginal
		PUSH 0x41A540
		RETN

		LoopOriginal :
		PUSH EAX
			CALL NewItensDay
			TEST AL, AL
			JE VoltaOriginal
			PUSH 0x41A56E
			RETN
			VoltaOriginal :
		PUSH 0x41A825
			RETN
	}
}

__declspec(naked) void HookNaked::NKD_ChangeTabColor()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 0x1B4]
		ADD EDX, 0x100
		PUSH EDX

		CALL HKD_ChangeTabColor

		ADD ESP, 04h

		PUSH EAX

		MOV EDX, 0x04E21E0

		JMP EDX
	}
}

__declspec(naked) void HookNaked::NKD_ItemPrice_FormatDecimal_03()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 011F4h]
		PUSH EDX

		LEA EAX, DWORD PTR SS : [EBP - 01278h]
		PUSH EAX

		CALL HKD_ItemPrice_FormatDecimal_03
		ADD ESP, 08h

		MOV EAX, 0x041D1CF
		JMP EAX
	}

}

__declspec(naked) void HookNaked::NKD_ItemPrice_FormatDecimal_02()
{
	{
		static int retn = 0;
		__asm
		{

			//LEA EAX, DWORD PTR SS : [EBP - 01278]
			//PUSH EAX

			MOV EDX, DWORD PTR SS : [EBP - 01154h]
			ADD EDX, EAX
			PUSH EDX

			LEA EAX, DWORD PTR SS : [EBP - 011D4h]
			PUSH EAX

			CALL HKD_ItemPrice_FormatDecimal_02
			ADD ESP, 08h


			MOV EAX, 0x041CFF5
			JMP EAX
		}
	}
}

__declspec(naked) void HookNaked::NKD_ItemPrice_FormatDecimal()
{
	__asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 08Ch]
		MOV ECX, DWORD PTR DS : [EAX + 058Ch]
		PUSH ECX

		MOV EAX, DWORD PTR SS : [EBP + 08h]
		PUSH EAX

		CALL HKD_ItemPrice_FormatDecimal_AutoTrade
		ADD ESP, 08h

		MOV EAX, 0x04213DA
		JMP EAX
	}
}

__declspec(naked) void HookNaked::NKD_GreenTime_NewArea()
{
	__asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 07B8h]
		MOV EAX, DWORD PTR DS : [EDX + 040h]

		PUSH DWORD PTR DS : [EAX + 020A24h]

		MOV EDX, DWORD PTR SS : [EBP - 07B8h]
		MOV EAX, DWORD PTR DS : [EDX + 040h]

		PUSH DWORD PTR DS : [EAX + 020A20h]

		CALL HKD_GreenTime_NewArea
		ADD ESP, 08h

		TEST EAX, EAX
		JE lbl_retn

		MOV EAX, 0047DD1Ah
		JMP EAX

		lbl_retn :
		MOV EAX, 0047DAF2h
			JMP EAX
	}
}

__declspec(naked) void HookNaked::NKD_ItemDescription()
{
	static COLORREF line1Color = 0, line2Color = 0, line3Color = 0, line4Color = 0, line5Color = 0, line6Color = 0, line7Color = 0, line8Color = 0, line9Color = 0, line10Color = 0;

	static int lineCounter = 0, index = 0;

	static char line2[128] = { 0 }, line3[128] = { 0 }, line4[128]{ 0, }, line5[128] = { 0 }, line6[128] = { 0 }, line7[128]{ 0, }, line8[128] = { 0 }, line9[128] = { 0 }, line10[128]{ 0, };

	__asm
	{
		LEA EAX, line10Color
		PUSH EAX
		LEA EAX, line9Color
		PUSH EAX
		LEA EAX, line8Color
		PUSH EAX
		LEA EAX, line7Color
		PUSH EAX
		LEA EAX, line6Color
		PUSH EAX
		LEA EAX, line5Color
		PUSH EAX
		LEA EAX, line4Color
		PUSH EAX
		LEA EAX, line3Color
		PUSH EAX
		LEA EAX, line2Color
		PUSH EAX
		LEA EAX, line1Color
		PUSH EAX
		LEA ECX, line10
		PUSH ECX
		LEA ECX, line9
		PUSH ECX
		LEA ECX, line8
		PUSH ECX
		LEA ECX, line7
		PUSH ECX
		LEA ECX, line6
		PUSH ECX
		LEA ECX, line5
		PUSH ECX
		LEA ECX, line4
		PUSH ECX
		LEA ECX, line3
		PUSH ECX
		LEA ECX, line2
		PUSH ECX
		LEA EDX, DWORD PTR SS : [EBP - 0xAC]
		PUSH EDX
		MOV ECX, DWORD PTR SS : [EBP - 0x8]
		MOV EDX, DWORD PTR DS : [ECX + 0x670]
		PUSH EDX
		CALL CreateObjectText
		TEST EAX, EAX
		JE lblContinueExec

		MOV lineCounter, EAX // 2
		MOV index, 0
		JMP LoopStart

		LoopEnd :
		MOV EAX, index
			ADD EAX, 1
			MOV index, EAX
			LoopStart :
		MOV EAX, index
			CMP EAX, lineCounter
			JGE lblContinueExec


			PUSH 0
			CMP index, 0
			JG lblLine2
			LEA ECX, DWORD PTR SS : [EBP - 0xAC]
			PUSH ECX
			JMP lblContinuePush
			lblLine2 :
		CMP index, 1
			JG  lblLine3
			LEA ECX, line2
			PUSH ECX
			JMP lblContinuePush
			lblLine3 :
		CMP index, 2
			JG  lblLine4
			LEA ECX, line3
			PUSH ECX
			JMP lblContinuePush
			lblLine4 :
		CMP index, 3
			JG  lblLine5
			LEA ECX, line4
			PUSH ECX
			JMP lblContinuePush
			lblLine5 :
		CMP index, 4
			JG  lblLine6
			LEA ECX, line5
			PUSH ECX
			JMP lblContinuePush
			lblLine6 :
		CMP index, 5
			JG  lblLine7
			LEA ECX, line6
			PUSH ECX
			JMP lblContinuePush
			lblLine7 :
		CMP index, 6
			JG  lblLine8
			LEA ECX, line7
			PUSH ECX
			JMP lblContinuePush
			lblLine8 :
		CMP index, 7
			JG  lblLine9
			LEA ECX, line8
			PUSH ECX
			JMP lblContinuePush
			lblLine9 :
		CMP index, 8
			JG  lblLine10
			LEA ECX, line9
			PUSH ECX
			JMP lblContinuePush
			lblLine10 :
		CMP index, 9
			JG  lblEmptyLine
			LEA ECX, line10
			PUSH ECX
			JMP lblContinuePush
			lblEmptyLine :
		PUSH 0
			JMP lblContinuePush
			lblContinuePush :
		MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV ECX, DWORD PTR DS : [EAX + EDX * 4 + 0x27A10]
			MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV EDX, DWORD PTR DS : [EAX + EDX * 4 + 0x27A10]
			MOV EAX, DWORD PTR DS : [EDX]
			CALL DWORD PTR DS : [EAX + 0x80]


			CMP index, 0
			JG lblColorLine2
			PUSH line1Color
			JMP lblContinueFuncCall

			lblColorLine2 :
		CMP index, 1
			JG lblColorLine3
			PUSH line2Color
			JMP lblContinueFuncCall

			lblColorLine3 :
		CMP index, 2
			JG lblColorLine4
			PUSH line3Color
			JMP lblContinueFuncCall

			lblColorLine4 :
		CMP index, 3
			JG lblColorLine5
			PUSH line4Color
			JMP lblContinueFuncCall

			lblColorLine5 :
		CMP index, 4
			JG lblColorLine6
			PUSH line5Color
			JMP lblContinueFuncCall

			lblColorLine6 :
		CMP index, 5
			JG lblColorLine7
			PUSH line6Color
			JMP lblContinueFuncCall

			lblColorLine7 :
		CMP index, 6
			JG lblColorLine8
			PUSH line7Color
			JMP lblContinueFuncCall

			lblColorLine8 :
		CMP index, 7
			JG lblColorLine9
			PUSH line8Color
			JMP lblContinueFuncCall

			lblColorLine9 :
		CMP index, 8
			JG lblColorLine10
			PUSH line9Color
			JMP lblContinueFuncCall

			lblColorLine10 :
		CMP index, 9
			JG lblNoColor
			PUSH line10Color
			JMP lblContinueFuncCall

			lblNoColor :
		PUSH 0
			JMP lblContinueFuncCall

			lblContinueFuncCall :
		MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV ECX, DWORD PTR DS : [EAX + EDX * 4 + 0x27A10]
			MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV EAX, DWORD PTR SS : [EBP - 0x10]
			MOV EDX, DWORD PTR DS : [EAX + EDX * 4 + 0x27A10]
			MOV EAX, DWORD PTR DS : [EDX]
			CALL DWORD PTR DS : [EAX + 0x84]

			MOV ECX, DWORD PTR SS : [EBP - 0x28]
			ADD ECX, 0x1
			MOV DWORD PTR SS : [EBP - 0x28] , ECX

			JMP LoopEnd

			lblContinueExec :
		MOV EDX, DWORD PTR SS : [EBP - 0x8]
			MOV EAX, DWORD PTR DS : [EDX + 0x670]

			PUSH 0x41C471 //0x041C484// | . 8B45 F8        MOV EAX, DWORD PTR SS : [EBP - 8]

			RETN
	}
}

__declspec(naked) void HookNaked::NKD_montaria() // mostra a montarias pros outros
{
	__asm
	{
		CMP DWORD PTR SS : [EBP - 0x8] , 0x0F95
		JNE lblContinue
		MOV DWORD PTR SS : [EBP - 0x20] , 0x159
		PUSH 0x50C360
		RETN

		lblContinue :

		LEA ECX, DWORD PTR SS : [EBP - 0x20]
			PUSH ECX
			MOV EDX, DWORD PTR SS : [EBP - 0x8]
			PUSH EDX
			CALL NewMount
			PUSH 0x50C333
			RETN
	}
}

__declspec(naked) void HookNaked::NKD_montaria2() // mostra a montaria p vc
{
	__asm
	{
		CMP DWORD PTR SS : [EBP - 0x30] , 0x0F95
		JNE lblContinue
		MOV DWORD PTR SS : [EBP - 0x34] , 0x159
		PUSH 0x50AC39
		RETN

		lblContinue :
		LEA ECX, DWORD PTR SS : [EBP - 0x34]
			PUSH ECX
			MOV EDX, DWORD PTR SS : [EBP - 0x30]
			PUSH EDX
			CALL NewMount
			PUSH 0x50AC00
			RETN
	}
}

__declspec(naked) void HookNaked::NKD_SpeakChatColor()
{
	static const UINT32 dwContinue = 0x004A016E;

	__asm
	{
		MOV EAX, SpeakChatColor
		MOV DWORD PTR SS : [EBP - 0x87C] , EAX
		JMP dwContinue
	}
}

__declspec(naked) void HookNaked::NKD_noSancFace() // Se não adicionar a face da Montaria ela fica brilhosa para os outros.
{
	_asm
	{
		CMP DWORD PTR SS : [EBP - 0x20] , 387
		JE correto
		CMP DWORD PTR SS : [EBP - 0x20] , 347
		JE correto
		CMP DWORD PTR SS : [EBP - 0x20] , 348
		JE correto
		CMP DWORD PTR SS : [EBP - 0x20] , 349
		JE correto
		CMP DWORD PTR SS : [EBP - 0x20] , 350
		JE correto
		PUSH 0x50C533
		RETN



	correto:
		PUSH 0x50C53C
			RETN

	}
}

__declspec(naked) void HookNaked::NKD_noSancID() // se não add o ID aqui a montaria fica brilhosa pros outros 
{
	_asm
	{
		CMP DWORD PTR SS : [EBP - 0x8] , 3990
		JE correto
		CMP DWORD PTR SS : [EBP - 0x8] , 3994
		JE correto
		CMP DWORD PTR SS : [EBP - 0x8] , 3999
		JE correto
		CMP DWORD PTR SS : [EBP - 0x8] , 3993
		JE correto
		CMP DWORD PTR SS : [EBP - 0x64] , 3996 //CMP DWORD PTR SS : [EBP - 0x8], 3996
		JE correto
		PUSH 0x50C779
		RETN

		correto :
		MOV ECX, DWORD PTR SS : [EBP - 0x28]
			MOV BYTE PTR DS : [ECX + 0x148] , 0
			MOV ECX, DWORD PTR SS : [EBP - 0x28]
			MOV BYTE PTR DS : [ECX + 0x147] , 0
			MOV EDX, DWORD PTR SS : [EBP - 0x28]
			MOV BYTE PTR DS : [EDX + 0x146] , 0
			PUSH 0x50C779
			RETN

	}
}

__declspec(naked) void HookNaked::NKD_AddVolatileMessageItem()
{
	__asm
	{
		CMP DWORD PTR SS : [EBP + 0xC] , 0x15E2 // 0xFD1
		JNZ lblNext
		JMP lblSuccess
		lblNext :
		PUSH DWORD PTR SS : [EBP + 0xC]
			CALL AddVolatileMessageItem
			TEST EAX, EAX
			JE lblContinueExec
			lblSuccess :
		MOV EAX, 1
			lblContinueExec :
			PUSH 0x422017
			RETN 4
	}
}

__declspec(naked) void HookNaked::NKD_AddVolatileMessageBox()
{
	static char msg[128] = { 0 };

	__asm
	{
		CMP DWORD PTR SS : [EBP - 0x1AC] , 0xD3
		JNZ lblNext
		PUSH 0x41FB3C
		RETN 4

		lblNext :
		LEA ECX, msg
		PUSH ECX
		MOV EAX, DWORD PTR SS : [EBP - 0x1B0]
		PUSH EAX
		CALL SetVolatileMessageBoxText
		TEST AL, AL
		JE lblContinueExec

		MOV EAX, DWORD PTR DS : [0x6F0AB0]
		MOV DWORD PTR SS : [EBP - 0x388] , EAX
		PUSH    0 // 0
		PUSH	0x373 // 0x373
		LEA EAX, msg
		PUSH EAX
		MOV     ECX, DWORD PTR SS : [EBP - 0x388]
		MOV     ECX, DWORD PTR DS : [ECX + 0xCC]
		MOV     EDX, DWORD PTR SS : [EBP - 0x388]
		MOV     EAX, DWORD PTR DS : [EDX + 0xCC]
		MOV     EDX, DWORD PTR DS : [EAX]
		CALL    DWORD PTR DS : [EDX + 0x8C]
		MOV     EAX, DWORD PTR SS : [EBP + 0x8]
		SHL     EAX, 0x10
		OR      EAX, DWORD PTR SS : [EBP + 0xC]
		MOV     ECX, DWORD PTR SS : [EBP - 0x388]
		MOV     EDX, DWORD PTR DS : [ECX + 0xCC]
		MOV     DWORD PTR DS : [EDX + 0x1E8] , EAX
		PUSH    1
		MOV     EAX, DWORD PTR SS : [EBP - 0x388]
		MOV     ECX, DWORD PTR DS : [EAX + 0xCC]
		MOV     EDX, DWORD PTR SS : [EBP - 0x388]
		MOV     EAX, DWORD PTR DS : [EDX + 0xCC]
		MOV     EDX, DWORD PTR DS : [EAX]
		CALL    DWORD PTR DS : [EDX + 0x60]
		PUSH 0x41FCFC
		RETN 4

		lblContinueExec :
		PUSH 0x41FBB2
		RETN 4
	}
}

__declspec(naked) void HookNaked::NKD_DNS() 
{
	static const UINT32 dwBackFix6 = 0x0053A3B5;
	__asm
	{
		MOV DWORD PTR SS : [EBP - 0x8] , 1
		MOV DWORD PTR SS : [EBP - 0x4] , 0
		JMP[dwBackFix6]
	}
}

INT32 g_pAffectId[] = { -1, 1, 41, 16, 165, 119, 105, 19, 161, 44, 51, 43, 84, 11, 3, 45, 71, 5, 46, 76, 40, 77, 37, 54, 13, 53, 89,
75, 95, 102, 163, 85, 47, 96, 164, 125, 92, 81, 87, 162, 96, 26, 121, 129, 99, 114, 130, 147, 140, 165, 103, 103, 104, 169, 170,
31, 171, 172 };

char g_pAffectName[128][24];

void AffectIconLimit()
{
	WYD.SetValue(0x044B0ED + 2, (UINT32)g_pAffectName, 4); // OK
	WYD.SetValue(0x047719C + 2, (UINT32)g_pAffectName, 4); // OK
	WYD.SetValue(0x0478038 + 2, (UINT32)g_pAffectName, 4); // ok
	WYD.SetValue(0x05495B1 + 2, (UINT32)g_pAffectName, 4); // OK

	WYD.SetValue(0x044B4C3 + 3, (UINT32)g_pAffectId, 4); // OK
	WYD.SetValue(0x04776F5 + 3, (UINT32)g_pAffectId, 4); // OK
	WYD.SetValue(0x0477D0D + 3, (UINT32)g_pAffectId, 4); // OK
	WYD.SetValue(0x047B0EF + 3, (UINT32)g_pAffectId, 4); // ok
	WYD.SetValue(0x04968EE + 3, (UINT32)g_pAffectId, 4); // ok
	WYD.SetValue(0x049692B + 3, (UINT32)g_pAffectId, 4); // ok
}
void BASE_EffectMagic(bool IsEnable = false)
{
	/* Enable the Effect Buffs */
	WYD.SetValue<DWORD>(0x0054A331 + 6, IsEnable ? FALSE : TRUE);
	WYD.SetValue<DWORD>(0x0054A331 + 6, IsEnable ? FALSE : TRUE);
	WYD.SetValue<DWORD>(0x00467651 + 6, IsEnable ? FALSE : TRUE);

	/* Disable D3D9 - Buffer */
	WYD.SetValue<DWORD>(0x0277C1C0, IsEnable ? TRUE : FALSE);
	WYD.SetValue<DWORD>(0x0277C1C4, IsEnable ? TRUE : FALSE);

	// Força os graficos
	*(DWORD*)(0x427213 + 6) = 0;
}
