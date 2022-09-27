#ifndef _SENDFUNC_ // Last updated 27/01/2013
#define _SENDFUNC_

#include <time.h>
#include <Windows.h>

#define GetItemList(itemId) reinterpret_cast<STRUCT_ITEMLIST*>((itemId * 0x8C) + 0xFB9608)
#define GetItemName(itemId) reinterpret_cast<char*>((itemId * 0x8C) +  0xFB9608)
#define GetItemPrice(itemId) *reinterpret_cast<uint32_t*>((itemId * 0x8C) + 0xFB9688)


void AffectIconLimit();
void BASE_EffectMagic(bool IsEnable);
void AffectIconLimit();
INT32 HKD_GreenTime_NewArea(INT32 posX, INT32 posY);
void HKD_ItemPrice_FormatDecimal_AutoTrade(char* gold, int value);
void HKD_ItemPrice_FormatDecimal_02(char* pointer, int gold);
void HKD_ItemPrice_FormatDecimal_03(char* pointer, int gold);
void HandlerController(char* pBuffer, int a_iSize, int a_iType);
char* ClientReceiver(char* pBuffer, int a_iSize);
char* ClientSended(char* pBuffer, int a_iSize);
char* ReadMessage(char* pMsg, int pSize);
int SendPack(const int conn, char* const pMsg, const int len);
void SendMsgExp(TNColor Color, char* msg, ...);
void CreateMessagePanel(char* msg, int color);
bool NewItensDay(INT32 Item);
bool SetItemPriceString(STRUCT_ITEM* item, char* str);
void FormataValidadeFada(char* msg, STRUCT_ITEM* item);
void FormataValidadeTraje(char* msg, STRUCT_ITEM* item);
void FormataValidade(char* msg, STRUCT_ITEM* item);
INT32 FirstLineValidadeBag(int index, char* pointer, char string, char* v9, char* v13);
INT32 HKD_GetItemAbility_Esferas(STRUCT_ITEM* item, INT32 effectId);
INT32 HKD_Macro_NewPotions(STRUCT_ITEM* item, INT32 type);
int CreateObjectText(STRUCT_ITEM* item, char* line1, char* line2, char* line3, char* line4, char* line5, char* line6, char* line7, char* line8, char* line9, char* line10, int* color1, int* color2, int* color3, int* color4, int* color5, int* color6, int* color7, int* color8, int* color9, int* color10);
bool AddAmountItem(int32_t itemID);
int HKD_ChangeTabColor(char* msg);
int HKD_SendChat(char* command);
INT32 HKD_KeyPress_NewButton(BYTE button);
void NewMount(int32_t index, int32_t* value);
bool SetVolatileMessageBoxText(int itemID, char* text);
int AddVolatileMessageItem(int itemID);
#pragma endregion

#endif
