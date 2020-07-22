#include "pch.h"
#include "SGrid.h"

SGridControl::SGridControl(unsigned int inTextureSetIndex, int inRowGridCount, int inColumnGridCount, float inX, float inY, float inWidth, float inHeight, TMEITEMTYPE type)
	: SPanel(inTextureSetIndex, inX, inY, inWidth, inHeight, 0xFFFFFFFF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH)
{
}

SGridControl::~SGridControl()
{
}

int SGridControl::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

void SGridControl::FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag)
{
}

int SGridControl::CanItAdd(int* bFilledBuffer, int inCellIndexX, int inCellIndexY, int inCellWidth, int inCellHeight)
{
	return 0;
}

int SGridControl::AddItem(SGridControlItem* ipNewItem, int inCellIndexX, int inCellIndexY)
{
	return 0;
}

int SGridControl::AddSkillItem(SGridControlItem* ipNewItem, int inCellIndexX, int inCellIndexY)
{
	return 0;
}

int SGridControl::SetItem(SGridControlItem* ipNewItem, int inCellIndexX, int inCellIndexY)
{
	return 0;
}

IVector2* SGridControl::AddItemInEmpty(IVector2* result, SGridControlItem* ipNewItem)
{
	return nullptr;
}

IVector2* SGridControl::CanAddItemInEmpty(IVector2* result, int nWidth, int nHeight)
{
	return nullptr;
}

int SGridControl::CanChangeItem(SGridControlItem* ipNewItem, int inCellIndexX, int inCellIndexY, int bOnlyCheck)
{
	return 0;
}

SGridControlItem* SGridControl::PickupItem(int inCellIndexX, int inCellIndexY)
{
	return nullptr;
}

SGridControlItem* SGridControl::PickupAtItem(int inCellIndexX, int inCellIndexY)
{
	return nullptr;
}

SGridControlItem* SGridControl::PickupItem_0(SGridControlItem* ipItem)
{
	return nullptr;
}

SGridControlItem* SGridControl::SelectItem(int inCellIndexX, int inCellIndexY)
{
	return nullptr;
}

SGridControlItem* SGridControl::GetItem(int inCellIndexX, int inCellIndexY)
{
	return nullptr;
}

SGridControlItem* SGridControl::GetAtItem(int inCellIndexX, int inCellIndexY)
{
	return nullptr;
}

SGridControlItem* SGridControl::GetItem_0(int nCount)
{
	return nullptr;
}

int SGridControl::OnKeyDownEvent(unsigned int iKeyCode)
{
	return 0;
}

void SGridControl::Empty()
{
}

short SGridControl::CheckType(TMEITEMTYPE eType, TMEGRIDTYPE eGridType)
{
	return 0;
}

short SGridControl::CheckPos(TMEITEMTYPE eType)
{
	return 0;
}

void SGridControl::BuyItem(int nCellX, int nCellY)
{
}

int SGridControl::TradeItem(int nCellX, int nCellY)
{
	return 0;
}

int SGridControl::SellItem(int nCellX, int nCellY, unsigned int dwFlags, unsigned int wParam)
{
	return 0;
}

int SGridControl::SellItem2()
{
	return 0;
}

void SGridControl::SwapItem(int nCellX, int nCellY, int nCellVWidth, int nCellVHeight, STRUCT_ITEM* pItem)
{
}

int SGridControl::MouseOver(int nCellX, int nCellY, int bPtInRect)
{
	return 0;
}

void SGridControl::RButton(int nCellX, int nCellY, int bPtInRect)
{
}

void SGridControl::UpdateCapsuleInfo(int nIndex)
{
}

char SGridControl::AutoSellShowPrice(char* Price)
{
	return 0;
}

char SGridControl::automove(int nCellX, int nCellY)
{
	return 0;
}

int SGridControl::Check_ItemRightClick(int nType, int nItemSIndex)
{
	return 0;
}

SGridControlItem::SGridControlItem(SGridControl* pParent, STRUCT_ITEM* pItem, float inX, float inY)
	: S3DObj(0, inX, inY, 35.0f, 35.0f)
{
}

SGridControlItem::~SGridControlItem()
{
}

void SGridControlItem::SelectThis(int bSelect)
{
}

int SGridControlItem::IsSelect()
{
	return 0;
}

SGridControl* SGridControlItem::GetGridControl()
{
	return nullptr;
}

void SGridControlItem::SetGridControl(SGridControl* pGridControl)
{
}

STRUCT_ITEM* SGridControlItem::GetItem()
{
	return nullptr;
}

void SGridControlItem::FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag)
{
}

int SGridControlItem::PtInItem(int inPosX, int inPosY)
{
	return 0;
}

int SGridControlItem::PtAtItem(int inPosX, int inPosY)
{
	return 0;
}
