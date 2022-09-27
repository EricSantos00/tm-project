#include "../Basedef.h"

#ifndef _HOOKNAKED_H_
#define _HOOKNAKED_H_

class HookNaked
{
private:

	HookNaked() = delete;
	virtual ~HookNaked() = delete;
	HookNaked(const HookNaked&) = delete;
	HookNaked& operator=(const HookNaked&) = delete;
public:

	static bool Start();
	static void NKD_ClientReceiver();
	static void NKD_ClientSended();
	static void NKD_ItemDescription();
	static void NKD_GreenTime_NewArea();
	static void NKD_ItemPrice_FormatDecimal_03();
	static void NKD_ItemPrice_FormatDecimal_02();
	static void NKD_ItemPrice_FormatDecimal();
	static void NKD_ChangeTabColor();
	static void NKD_NewItensDays_1();
	static void NKD_NewItensDays_2();
	static void NKD_NewFaceComp();
	static void NKD_FixMageMacro();
	static void NKD_ItemPriceString();
	static void NKD_ProcessClientMessage_03BBh();
	static void NKD_AddAmountItem();
	static void NKD_ValidadeFadas();
	static void NKD_ValidadeTrajes();
	static void NKD_Validade();
	static void NKD_GetItemAbility_Esfera();
	static void NKD_Macro_NewPotions_HP();
	static void NKD_Macro_NewPotions_MP();
	static void NKD_SendChat();
	static void NKD_DescValidadeBag01();
	static void NKD_DescValidadeBag02();
	static void NKD_KeyPress_NewButton();
	static void NKD_SpeakChatColor();
	static void NKD_montaria();
	static void NKD_montaria2();
	static void NKD_noSancFace();
	static void NKD_noSancID();
	static void NKD_AddVolatileMessageItem();
	static void NKD_AddVolatileMessageBox();
	static void NKD_DNS();
};


#endif