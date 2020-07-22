#include "pch.h"
#include "TMEffectBillBoard.h"
#include "TMEffectBillBoard2.h"
#include "SControl.h"
#include "TMItem.h"

TMItem::TMItem()
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
	return 0;
}

void TMItem::InitPosition(float fX, float fY, float fZ)
{
}

int TMItem::Render()
{
	return 0;
}

int TMItem::IsMouseOver()
{
	return 0;
}

int TMItem::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMItem::LabelPosition()
{
}
