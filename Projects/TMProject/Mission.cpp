#include "pch.h"
#include "SControlContainer.h"
#include "SControl.h"
#include "Mission.h"
#include "TMGlobal.h"
#include "SGrid.h"

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
	m_pControlContainer = ControlContainer;
    m_pMissionPanel = (SPanel*)m_pControlContainer->FindControl(86017);

    if (m_pMissionPanel)
        m_pMissionPanel->SetPos(RenderDevice::m_fWidthRatio * 160.0f,
            RenderDevice::m_fHeightRatio * 35.0f);

    m_pMissionPanel->SetVisible(0);

    for (int i = 0; i < 24; ++i)
    {
        m_pGridResultItem[i] = (SGridControl*)m_pControlContainer->FindControl(i + 86020);
        if (m_pGridResultItem[i])
            m_pGridResultItem[i]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
    }
    for (int i = 0; i < 8; ++i)
    {
        m_pGridNeedItem[i] = (SGridControl*)m_pControlContainer->FindControl(i + 86077);
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
