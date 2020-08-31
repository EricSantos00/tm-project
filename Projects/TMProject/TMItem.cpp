#include "pch.h"
#include "TMEffectBillBoard.h"
#include "TMEffectBillBoard2.h"
#include "SControl.h"
#include "TMItem.h"

TMItem::TMItem() 
	: TMObject()
{
}

TMItem::~TMItem()
{
}

void TMItem::InitItem(STRUCT_ITEM stItem)
{
}

int TMItem::InitObject()
{
	return 1;
}

void TMItem::InitPosition(float fX, float fY, float fZ)
{
}

int TMItem::Render()
{
	return 1;
}

int TMItem::IsMouseOver()
{
	return 1;
}

int TMItem::FrameMove(unsigned int dwServerTime)
{
	return 1;
}

void TMItem::LabelPosition()
{
}
