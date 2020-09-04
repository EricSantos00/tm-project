#include "pch.h"
#include "SControlContainer.h"
#include "SControl.h"
#include "MrItemMix.h"
#include "TMGlobal.h"
#include "SGrid.h"

CItemMix::CItemMix()
{
}

CItemMix::~CItemMix()
{
}

int CItemMix::Read_RMixListFile(char* filename)
{
	return 0;
}

int CItemMix::Read_NMixListFile(char* filename)
{
	return 0;
}

void CItemMix::TakeItResource(SControlContainer* ControlContainer, unsigned short CharID)
{
	m_pControlContainer = ControlContainer;
	m_dwID = CharID;
	m_pMixPanel = (SPanel*)m_pControlContainer->FindControl(81921);

	if (m_pMixPanel)
		m_pMixPanel->SetPos(RenderDevice::m_fWidthRatio * 160.0f,
			RenderDevice::m_fHeightRatio * 35.0f);

	m_pMixPanel->SetVisible(0);
	for (int i = 0; i < 24; ++i)
	{
		m_pGridResultItem[i] = (SGridControl*)m_pControlContainer->FindControl(i + 81924);
		if (m_pGridResultItem[i])
			m_pGridResultItem[i]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	}
	for (int i = 0; i < 8; ++i)
	{
		m_pGridNeedItem[i] = (SGridControl*)m_pControlContainer->FindControl(i + 81981);
		if (m_pGridNeedItem[i])
			m_pGridNeedItem[i]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
	}

	SText* Cost = (SText*)m_pControlContainer->FindControl(81948);
	Cost->SetTextColor(0xFF000000);

	memset(&m_stCombineItem, 0, sizeof(m_stCombineItem));

	for (int i = 0; i < 8; ++i)
		m_stCombineItem.CarryPos[i] = -1;

	m_stCombineItem.Header.ID = CharID;
}

void CItemMix::ResultItemListSet(unsigned int Head, int X, int Y)
{
}

void CItemMix::Set_NeedItemList(int Index)
{
}

void CItemMix::ClearGridList()
{
}

void CItemMix::ClearResultGridList()
{
}

void CItemMix::ClearNeedGridList()
{
}

void CItemMix::InvClear(SGridControl** GridInvList)
{
}

void CItemMix::CheckInv(SGridControl** GridInvList)
{
}

void CItemMix::SetTextList()
{
}

void CItemMix::ClickInvItem(SGridControlItem* pItem, SGridControl** GridInvList, short Sourpage)
{
}

void CItemMix::DoCombine(SMessagePanel* MessagePanel, SGridControl** GridInvList, int Coin)
{
}

int CItemMix::IsSameItem(STRUCT_MYITEM* Item1, STRUCT_ITEM* Item2, short deep)
{
	return 0;
}

int CItemMix::IsSameItem(STRUCT_ITEM* Item1, STRUCT_ITEM* Item2, short deep)
{
	return 0;
}

int CItemMix::IsItemOption_Satisfaction(int index, STRUCT_ITEM* item)
{
	return 0;
}

void CItemMix::Read_MixListFile()
{
	BASE_ReadMixList();
}

void CItemMix::BASE_ReadMixList()
{
	FILE* fp{ nullptr };

	fopen_s(&fp, ".\\Mixlist.bin", "rb");

	if (fp == nullptr)
	{
		MessageBoxA(0, "Can't read Mixlist.bin", "ERROR", 0);
		return;
	}

	fread(stResult_itemList, sizeof(stResult_itemList), 1, fp);
	fread(stNeed_itemList, sizeof(stNeed_itemList), 1, fp);
	fclose(fp);
}

void CItemMix::BASE_WriteMixItemList()
{
	FILE* fp{ nullptr };

	fopen_s(&fp, ".\\Mixlist.bin", "wb");

	if (fp == nullptr)
	{
		MessageBoxA(0, "Can't generate Mixlist.bin file", "ERROR", 0);
		return;
	}

	fwrite(stResult_itemList, sizeof(stResult_itemList), 1, fp);
	fwrite(stNeed_itemList, sizeof(stNeed_itemList), 1, fp);
	fclose(fp);
}

int CItemMix::MYGetItemSanc(STRUCT_ITEM* item)
{
	return 0;
}

int CItemMix::HardCode(SMessagePanel* MessagePanel, SGridControl** GridInvList)
{
	return 0;
}
