#pragma once

#include "Structures.h"
#include "Basedef.h"

class SControlContainer;
class SGridControl;
class SGridControlItem;
class SMessagePanel;
class SPanel;

class CItemMix
{
public:
	CItemMix();
	virtual ~CItemMix();

	int Read_RMixListFile(const char* filename);
	int Read_NMixListFile(const char* filename);
	void TakeItResource(SControlContainer* ControlContainer, unsigned short CharID);
	void ResultItemListSet(unsigned int Head, int X, int Y);
	void Set_NeedItemList(int Index);
	void ClearGridList();
	void ClearResultGridList();
	void ClearNeedGridList();
	void InvClear(SGridControl** GridInvList);
	void CheckInv(SGridControl** GridInvList);
	void SetTextList();
	void ClickInvItem(SGridControlItem* pItem, SGridControl** GridInvList, short Sourpage);
	void DoCombine(SMessagePanel* MessagePanel, SGridControl** GridInvList, int Coin);
	int IsSameItem(STRUCT_MYITEM* Item1, STRUCT_ITEM* Item2, short deep);
	int IsSameItem(STRUCT_ITEM* Item1, STRUCT_ITEM* Item2, short deep);
	int IsItemOption_Satisfaction(int index, STRUCT_ITEM* item);
	void Read_MixListFile();
	void BASE_ReadMixList();
	void BASE_WriteMixItemList();
	int MYGetItemSanc(STRUCT_MYITEM* item);
	int HardCode(SMessagePanel* MessagePanel, SGridControl** GridInvList);

public:
	STRUCT_RESULT_ITEMLIST stResult_itemList[100];
	STRUCT_NEED_ITEMLIST stNeed_itemList[100];
	unsigned int m_NPCHead;
	unsigned int m_dNPCX;
	unsigned int m_dNPCY;
	unsigned int m_dResultIndexList[24];
	STRUCT_REFER m_dNeedRefer[8];
	SControlContainer* m_pControlContainer;
	SGridControl** m_pGridInvList;
	SPanel* m_pMixPanel;
	SGridControl* m_pGridResultItem[24];
	SGridControl* m_pGridNeedItem[8];
	unsigned short m_dwID;
	MSG_CombineItem m_stCombineItem;
	short m_dResultIndex;
};