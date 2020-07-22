#include "pch.h"
#include "SControlContainer.h"
#include "SControl.h"
#include "Mission.h"

CMission::CMission()
{
}

CMission::~CMission()
{
}

void CMission::ResultItemListSet()
{
}

void CMission::Set_NeedItemList(int Index)
{
}

void CMission::ResultItemHelpSet()
{
}

void CMission::TakeItResource(SControlContainer* ControlContainer, unsigned short CharID)
{
}

void CMission::InvClear(SGridControl** GridInvList)
{
}

void CMission::CheckInv(SGridControl** GridInvList)
{
}

void CMission::ClickInvItem(SGridControlItem* pItem, SGridControl** GridInvList, short Sourpage)
{
}

void CMission::ClearGridList()
{
}

void CMission::ClearResultGridList()
{
}

void CMission::ClearNeedGridList()
{
}

void CMission::SetTextList()
{
}

void CMission::DoCombine(SMessagePanel* MessagePanel, SGridControl** GridInvList, int Class, int Lev, int Coin)
{
}
