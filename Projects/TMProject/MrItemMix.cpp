#include "pch.h"
#include "SControlContainer.h"
#include "SControl.h"
#include "MrItemMix.h"
#include "TMFieldScene.h"
#include "TMGlobal.h"
#include "SGrid.h"
#include "ItemEffect.h"
#include "TMUtil.h"

CItemMix::CItemMix()
{
    m_NPCHead = 0;
    m_dNPCY = 0;
    m_dNPCX = 0;
    m_dResultIndex = -1;

    for (int i = 0; i < 8; ++i)
    {
        m_dNeedRefer[i].bItemListrefer = 0;
        m_dNeedRefer[i].dindex= 0;
        m_dNeedRefer[i].dHavevolume= 0;
    }

    m_stCombineItem = {};

    for (int i = 0; i < 8; ++i)
        m_stCombineItem.CarryPos[i] = -1;

    for (int i = 0; i < 100; ++i)
        stNeed_itemList[i].Textnum = 0;

    // avoid initialization warnings
    m_dwID = 0;
    memset(&stResult_itemList, 0, sizeof stResult_itemList);
    m_pControlContainer = nullptr;
    m_pGridInvList = nullptr;
    m_pMixPanel = nullptr;
    memset(&m_pGridResultItem, 0, sizeof m_pGridResultItem);
    m_dResultIndex = 0;
}

CItemMix::~CItemMix()
{
}

int CItemMix::Read_RMixListFile(const char* filename)
{
    // not used
	return 0;
}

int CItemMix::Read_NMixListFile(const char* filename)
{
    // not used
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
    m_NPCHead = Head;
    m_dNPCX = X;
    m_dNPCY = Y;

    ClearGridList();

    for (int i = 0; i < 24; ++i)
        m_dResultIndexList[i] = 0;

    int count = 0;

    for (int i = 0; i < 100; ++i)
    {
        if (stResult_itemList[i].dNPCHead == Head && stResult_itemList[i].pxy.X == X && stResult_itemList[i].pxy.Y == Y)
        {
            if (Head)
            {
                m_dResultIndexList[count++] = i;
            }
            else if (i < 39 || IsValidSkill(87) == 1)
            {
                m_dResultIndexList[count++] = i;
            }
        }
    }

    count = 0;

    for (int i = 0; i < 24; ++i)
    {
        if (m_dResultIndexList[i])
        {
            auto pstItem = new STRUCT_ITEM();

            pstItem->sIndex = stResult_itemList[m_dResultIndexList[i]].stItemInfor.sIndex;

            for (int j = 0; j < 3; ++j)
            {
                pstItem->stEffect[j].cEffect = stResult_itemList[m_dResultIndexList[i]].stItemInfor.stEffect[j].cEffect;
                pstItem->stEffect[j].cValue = stResult_itemList[m_dResultIndexList[i]].stItemInfor.stEffect[j].cValue;
                pstItem->stEffect[j].sValue = stResult_itemList[m_dResultIndexList[i]].stItemInfor.stEffect[j].sValue;
            }

            m_pGridResultItem[count]->m_eGridType = TMEGRIDTYPE::GRID_ITEMMIXRESULT;
            m_pGridResultItem[count++]->AddItem(new SGridControlItem(0, pstItem, 0.0f, 0.0f), 0, 0);
        }
    }

    memset(&m_stCombineItem, 0, sizeof(m_stCombineItem));

    for (int i = 0; i < 8; ++i)
        m_stCombineItem.CarryPos[i] = -1;
}

void CItemMix::Set_NeedItemList(int Index)
{
    ClearNeedGridList();

    if (Index < 0 || Index > 13000)
        return;

    for (int i = 0; i < 100; ++i)
    {
        if (stResult_itemList[i].dNPCHead == m_NPCHead &&
            stResult_itemList[i].pxy.X == m_dNPCX &&
            stResult_itemList[i].pxy.Y == m_dNPCY &&
            stResult_itemList[i].stItemInfor.sIndex == Index)
        {
            m_dResultIndex = i;

            for (int j = 0; j < 8; ++j)
            {
                int index = stResult_itemList[i].dNeedItemList[j].dINDEX;
                if (index <= 0 || index >= 13000)
                    return;

                m_dNeedRefer[j].dindex = index;

                if (stResult_itemList[i].dNeedItemList[j].Access)
                {
                    if (stResult_itemList[i].dNeedItemList[j].Access == 2)
                    {
                        auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

                        if (pFScene != nullptr)
                        {
                            pFScene->SetVisibleMixPanel(pFScene->m_ItemMixClass.m_pMixPanel->m_bVisible == 0);
                            pFScene->m_ItemMixClass.ResultItemListSet(stResult_itemList[i].dNeedItemList[j].dINDEX, 0, 0);
                            pFScene->SetVisibleMixPanel(pFScene->m_ItemMixClass.m_pMixPanel->m_bVisible == 0);
                        }
                    }
                    else if (stNeed_itemList[index].stGridItem.sIndex > 0)
                    {
                        m_dNeedRefer[j].bItemListrefer = 0;

                        auto pstItem = new STRUCT_ITEM();

                        memcpy(pstItem, &stNeed_itemList[index].stGridItem, sizeof(pstItem));

                        m_pGridNeedItem[j]->AddItem(new SGridControlItem(0, pstItem, 0.0f, 0.0f), 0, 0);
                        m_pGridNeedItem[j]->m_eGridType = TMEGRIDTYPE::GRID_ITEMMIXNEED;
                    }
                }
                else
                {
                    m_dNeedRefer[j].bItemListrefer = 1;

                    auto pstItem = new STRUCT_ITEM();

                    pstItem->sIndex = index;

                    m_pGridNeedItem[j]->AddItem(new SGridControlItem(0, pstItem, 0.0f, 0.0f), 0, 0);
                    m_pGridNeedItem[j]->m_eGridType = TMEGRIDTYPE::GRID_ITEMMIXNEED;
                }
            }
        }
    }
}

void CItemMix::ClearGridList()
{
    ClearResultGridList();
    ClearNeedGridList();

    for (int i = 0; i < 8; ++i)
    {
        m_dNeedRefer[i].bItemListrefer = 0;
        m_dNeedRefer[i].dindex = 0;
        m_dNeedRefer[i].dHavevolume = 0;
    }

    for (int i = 0; i < 8; ++i)
        m_stCombineItem.CarryPos[i] = -1;
}

void CItemMix::ClearResultGridList()
{
    m_dResultIndex = -1;

    for (int i = 0; i < 24; ++i)
    {
        SGridControlItem* pPickedItem = nullptr;
        if (m_pGridResultItem[i])
            pPickedItem = m_pGridResultItem[i]->PickupItem(0, 0);

        if (g_pCursor->m_pAttachedItem && pPickedItem && g_pCursor->m_pAttachedItem == pPickedItem)
            g_pCursor->m_pAttachedItem = nullptr;

        if (pPickedItem)
            delete pPickedItem;
    }

    for (int i = 0; i < 24; ++i)
    {
        m_pGridResultItem[i] = static_cast<SGridControl*>(m_pControlContainer->FindControl(i + G_ITEM_MIX_RESULT_1));

        if (m_pGridResultItem[i])
            m_pGridResultItem[i]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
    }
}

void CItemMix::ClearNeedGridList()
{
    for (int i = 0; i < 8; ++i)
    {
        SGridControlItem* pPickedItem = nullptr;
        if (m_pGridNeedItem[i])
            pPickedItem = m_pGridNeedItem[i]->PickupItem(0, 0);

        if (g_pCursor->m_pAttachedItem && pPickedItem && g_pCursor->m_pAttachedItem == pPickedItem)
            g_pCursor->m_pAttachedItem = nullptr;

        if (pPickedItem)
            delete pPickedItem;
    }

    for (int i = 0; i < 8; ++i)
    {
        m_pGridNeedItem[i] = static_cast<SGridControl*>(m_pControlContainer->FindControl(G_ITEM_MIX_NEED_1 + i));

        if (m_pGridNeedItem[i])
            m_pGridNeedItem[i]->m_eGridType = TMEGRIDTYPE::GRID_DEFAULT;
    }

    for (int i = 0; i < 8; ++i)
    {
        m_dNeedRefer[i].bItemListrefer = 0;
        m_dNeedRefer[i].dindex = 0;
        m_dNeedRefer[i].dHavevolume = 0;
    }

    for (int i = 0; i < 8; ++i)
    {
        auto s_pName = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_NAME_1 + i));
        auto s_pVolume = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_VOLUME_1 + i));
        auto Cost = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_MONEY));

        if (s_pName)
            s_pName->SetText((char*)"", 0);
        if (s_pVolume)
            s_pVolume->SetText((char*)"", 0);
        if (Cost)
            Cost->SetText((char*)"", 0);
    }
}

void CItemMix::InvClear(SGridControl** GridInvList)
{
    m_pGridInvList = GridInvList;
    memset(&m_stCombineItem, 0, sizeof m_stCombineItem);

    for (int i = 0; i < 8; ++i)
        m_stCombineItem.CarryPos[i] = -1;

    for (int i = 0; i < 4; ++i)
    {
        auto pGridInv = m_pGridInvList[i];
        if (!pGridInv)
            break;

        for (int nY = 0; nY < 3; ++nY)
        {
            for (int nX = 0; nX < 5; ++nX)
            {
                auto pItem = pGridInv->GetItem(nX, nY);
                if (pItem)
                    pItem->m_GCObj.dwColor = -1;
            }
        }
    }
}

void CItemMix::CheckInv(SGridControl** GridInvList)
{
    m_pGridInvList = GridInvList;

    InvClear(m_pGridInvList);

    for (int i = 0; i < 8; ++i)
    {
        int index = m_dNeedRefer[i].dindex;

        if (index <= 0)
            continue;

        for (int j = 0; j < 4; ++j)
        {
            for (int nY = 0; nY < 3; ++nY)
            {
                for (int nX = 0; nX < 5; ++nX)
                {
                    SGridControlItem* pItem = m_pGridInvList[j]->GetItem(nX, nY);

                    if (pItem && pItem->m_GCObj.dwColor == 0xFFFFFFFF)
                    {
                        if (m_dNeedRefer[i].bItemListrefer)
                        {
                            if ((pItem->m_pItem->sIndex != 413 && pItem->m_pItem->sIndex != 412
                                || pItem->m_pItem->stEffect[0].cEffect != 61
                                || pItem->m_pItem->stEffect[0].cValue == 1)
                                && m_dNeedRefer[i].dindex == pItem->m_pItem->sIndex
                                && m_dNeedRefer[i].dHavevolume < 1)
                            {
                                pItem->m_GCObj.dwColor = 0xFFFF0000;

                                ++m_dNeedRefer[i].dHavevolume;

                                for (int k = i; k < 8; ++k)
                                {
                                    if (!m_stCombineItem.Item[k].sIndex)
                                    {
                                        memcpy(&m_stCombineItem.Item[k], pItem->m_pItem, sizeof(m_stCombineItem.Item[k]));
                                        m_stCombineItem.CarryPos[k] = 15 * j + 5 * pItem->m_nCellIndexY + pItem->m_nCellIndexX;
                                        break;
                                    }
                                }
                            }
                        }
                        else if (IsSameItem(&stNeed_itemList[index].stGridItem, pItem->m_pItem, 4))
                        {
                            if ((pItem->m_pItem->sIndex == 413 || pItem->m_pItem->sIndex == 412)
                                && stNeed_itemList[index].stGridItem.stEffect[0].cEffect == 61
                                && pItem->m_pItem->stEffect[0].cEffect == 61
                                && stNeed_itemList[index].stGridItem.stEffect[0].cValue == pItem->m_pItem->stEffect[0].cValue
                                && m_dNeedRefer[i].dHavevolume < stNeed_itemList[index].dVolume)
                            {
                                pItem->m_GCObj.dwColor = 0xFFFF0000;

                                ++m_dNeedRefer[i].dHavevolume;

                                for (int k = i; k < 8; ++k)
                                {
                                    if (!m_stCombineItem.Item[k].sIndex)
                                    {
                                        memcpy(&m_stCombineItem.Item[k], pItem->m_pItem, sizeof(m_stCombineItem.Item[k]));
                                        m_stCombineItem.CarryPos[k] = 15 * j + 5 * pItem->m_nCellIndexY + pItem->m_nCellIndexX;
                                        break;
                                    }
                                }
                            }
                            if (m_dNeedRefer[i].dHavevolume < stNeed_itemList[index].dVolume && (pItem->m_pItem->stEffect[0].cEffect != 61 || pItem->m_pItem->stEffect[0].cValue == 1))
                            {
                                pItem->m_GCObj.dwColor = 0xFFFF0000;

                                ++m_dNeedRefer[i].dHavevolume;

                                for (int k = i; k < 8; ++k)
                                {
                                    if (!m_stCombineItem.Item[k].sIndex)
                                    {
                                        memcpy(&m_stCombineItem.Item[k], pItem->m_pItem, sizeof(m_stCombineItem.Item[k]));
                                        m_stCombineItem.CarryPos[k] = 15 * j + 5 * pItem->m_nCellIndexY + pItem->m_nCellIndexX;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    SetTextList();
}

void CItemMix::SetTextList()
{
    for (int i = 0; i < 8; ++i)
    {
        auto s_pName = static_cast<SText*>(m_pControlContainer->FindControl(i + T_ITEM_MIX_NAME_1));
        auto s_pVolume = static_cast<SText*>(m_pControlContainer->FindControl(i + T_ITEM_MIX_VOLUME_1));

        if (s_pName != nullptr)
        {
            s_pName->SetText((char*)"", 0);
            s_pName->SetTextColor(0xFFAA0000);
        }

        if (s_pVolume != nullptr)
        {
            s_pVolume->SetText((char*)"", 0);
            s_pVolume->SetTextColor(0xFFAA0000);
        }
    }

    auto Cost = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_MONEY));

    char cCost[256]{};

    _itoa(stResult_itemList[m_dResultIndex].dCost, cCost, 10);

    if (Cost != nullptr)
    {
        Cost->m_cComma = 1;
        Cost->SetText(cCost, 0);
    }

    for (int i = 0; i < 8; ++i)
    {
        int index = m_dNeedRefer[i].dindex;
        if (index <= 0)
            continue;

        auto s_pName = static_cast<SText*>(m_pControlContainer->FindControl(i + T_ITEM_MIX_NAME_1));
        auto s_pVolume = static_cast<SText*>(m_pControlContainer->FindControl(i + T_ITEM_MIX_VOLUME_1));

        if (s_pName != nullptr)
        {
            if (m_dNeedRefer[i].bItemListrefer)
                s_pName->SetText(g_pItemList[index].Name, 0);
            else
                s_pName->SetText(g_pMessageStringTable[stNeed_itemList[index].Textnum], 0);
        }

        char temp[64]{};
        char Have[64]{};
        char result[128]{};

        strcpy(result, " ");
        _itoa(m_dNeedRefer[i].dHavevolume, temp, 10);
        strcpy(Have, temp);

        if (!m_dNeedRefer[i].bItemListrefer && stNeed_itemList[index].dVolume == 1 || m_dNeedRefer[i].bItemListrefer == 1)
        {
            char buffer[64]{};
            char Need[64]{};

            if (!m_dNeedRefer[i].bItemListrefer)
                _itoa(stNeed_itemList[index].dVolume, buffer, 10);

            strcpy(Need, buffer);
            strcat(result, Have);
            strcat(result, " / ");

            if (m_dNeedRefer[i].bItemListrefer)
                strcat(result, "1");
            else
                strcat(result, Need);

            if (m_dNeedRefer[i].bItemListrefer == 1 && m_dNeedRefer[i].dHavevolume)
            {
                if (s_pName != nullptr)
                    s_pName->SetTextColor(0xFFFFFFFF);

                if (s_pVolume != nullptr)
                    s_pVolume->SetTextColor(0xFFFFFFFF);
            }
            else if (!m_dNeedRefer[i].bItemListrefer
                && m_dNeedRefer[i].dHavevolume
                && stNeed_itemList[index].dVolume
                && m_dNeedRefer[i].dHavevolume == stNeed_itemList[index].dVolume)
            {
                if (s_pName != nullptr)
                    s_pName->SetTextColor(0xFFFFFFFF);

                if (s_pVolume != nullptr)
                    s_pVolume->SetTextColor(0xFFFFFFFF);
            }

            if (s_pVolume != nullptr)
                s_pVolume->SetText(result, 0);
        }

        if (!m_dNeedRefer[i].bItemListrefer && stNeed_itemList[index].dVolume > 1)
        {
            char buffer[64]{};
            char Need[64]{};

            _itoa(stNeed_itemList[index].dVolume, buffer, 10);
            strcpy(Need, buffer);
            strcat(result, Have);
            strcat(result, " / ");
            strcat(result, Need);

            if (m_dNeedRefer[i].dHavevolume == stNeed_itemList[index].dVolume)
            {
                if (s_pName != nullptr)
                    s_pName->SetTextColor(0xFFFFFFFF);

                if (s_pVolume != nullptr)
                    s_pVolume->SetTextColor(0xFFFFFFFF);
            }

            if (s_pVolume != nullptr)
                s_pVolume->SetText(result, 0);
        }
    }
}

void CItemMix::ClickInvItem(SGridControlItem* pItem, SGridControl** GridInvList, short Sourpage)
{
    if (m_dResultIndex != -1 && pItem)
    {
        for (int i = 0; i < 4; ++i)
        {
            auto pGridInv = m_pGridInvList[i];
            if (!pGridInv)
                return;

            for (int nY = 0; nY < 3; ++nY)
            {
                for (int nX = 0; nX < 5; ++nX)
                    if ((int)pGridInv->GetItem(nX, nY) && pItem->m_GCObj.dwColor == -65536)
                        return;
            }
        }

        for (int i = 0; i < 8; ++i)
        {
            auto index = m_dNeedRefer[i].dindex;

            if (m_dNeedRefer[i].bItemListrefer)
            {
                if (index < 100 && stNeed_itemList[index].stGridItem.sIndex > 0 &&
                    IsSameItem(&stNeed_itemList[index].stGridItem, pItem->m_pItem, 1) &&
                    !m_pGridNeedItem[i]->m_pItemList[0])
                {
                    auto newItem = new STRUCT_ITEM(); // v52
                    newItem->sIndex = pItem->m_pItem->sIndex;

                    for (int kh = 0; kh < 3; ++kh)
                    {
                        newItem->stEffect[kh].cEffect = pItem->m_pItem->stEffect[kh].cEffect;
                        newItem->stEffect[kh].cValue = pItem->m_pItem->stEffect[kh].cValue;
                        newItem->stEffect[kh].sValue = pItem->m_pItem->stEffect[kh].sValue;
                    }

                    m_pGridNeedItem[i]->AddItem(new SGridControlItem(nullptr, newItem, 0.0f, 0.0f), 0, 0);

                    for (int j = 0; j < 4; ++j)
                    {
                        auto grid = m_pGridInvList[j];
                        for (int nY = 0; nY < 3; ++nY)
                        {
                            for (int nX = 0; nX < 5; ++nX)
                            {
                                auto item = grid->GetItem(nX, nY);
                                if (item && IsSameItem(item->m_pItem, pItem->m_pItem, 4))
                                    break;
                            }
                        }

                        for (int ki = i; ki < 8; ++ki)
                        {
                            if (!m_stCombineItem.Item[ki].sIndex)
                            {
                                pItem->m_GCObj.dwColor = -65536;
                                memcpy((char*)&m_stCombineItem.Item[ki], pItem->m_pItem, sizeof STRUCT_ITEM);

                                m_stCombineItem.CarryPos[ki] = 15 * Sourpage + 5 * pItem->m_nCellIndexY + pItem->m_nCellIndexX;
                                break;
                            }
                        }

                        auto pName = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_NAME_1 + j));
                        auto pVolume = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_VOLUME_1 + j));

                        pName->SetTextColor(0xFFFFFFFF);
                        pVolume->SetTextColor(0xFFFFFFFF);
                        m_dNeedRefer[i].dHavevolume = 1;

                        SetTextList();
                        return;
                    }
                }
            }
            else if (stNeed_itemList[index].stGridItem.sIndex)
            {
                if (stNeed_itemList[index].stGridItem.sIndex > 0 &&
                    stNeed_itemList[index].stGridItem.sIndex == pItem->m_pItem->sIndex &&
                    IsSameItem(&stNeed_itemList[index].stGridItem, pItem->m_pItem, 4) &&
                    !m_pGridNeedItem[i]->m_pItemList[0])
                {
                    auto newItem = new STRUCT_ITEM(); // v52
                    newItem->sIndex = pItem->m_pItem->sIndex;

                    for (int kh = 0; kh < 3; ++kh)
                    {
                        newItem->stEffect[kh].cEffect = pItem->m_pItem->stEffect[kh].cEffect;
                        newItem->stEffect[kh].cValue = pItem->m_pItem->stEffect[kh].cValue;
                        newItem->stEffect[kh].sValue = pItem->m_pItem->stEffect[kh].sValue;
                    }

                    m_pGridNeedItem[i]->AddItem(new SGridControlItem(nullptr, newItem, 0.0f, 0.0f), 0, 0);

                    for (int j = 0; j < 4; ++j)
                    {
                        auto grid = m_pGridInvList[j];
                        for (int nY = 0; nY < 3; ++nY)
                        {
                            for (int nX = 0; nX < 5; ++nX)
                            {
                                auto item = grid->GetItem(nX, nY);
                                if (item && IsSameItem(item->m_pItem, pItem->m_pItem, 4))
                                    break;
                            }
                        }

                        for (int ki = i; ki < 8; ++ki)
                        {
                            if (!m_stCombineItem.Item[ki].sIndex)
                            {
                                pItem->m_GCObj.dwColor = -65536;
                                memcpy((char*)&m_stCombineItem.Item[ki], pItem->m_pItem, sizeof STRUCT_ITEM);

                                m_stCombineItem.CarryPos[ki] = 15 * Sourpage + 5 * pItem->m_nCellIndexY + pItem->m_nCellIndexX;
                                break;
                            }
                        }

                        auto pName = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_NAME_1 + j));
                        auto pVolume = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_VOLUME_1 + j));

                        pName->SetTextColor(0xFFFFFFFF);
                        pVolume->SetTextColor(0xFFFFFFFF);
                        m_dNeedRefer[i].dHavevolume = 1;

                        SetTextList();
                        return;
                    }
                }
            }
            else if (stNeed_itemList[index].dListIndexArry[0])
            {
                if ((unsigned int)pItem->m_pItem->sIndex >= stNeed_itemList[index].dListIndexArry[0]
                    && (unsigned int)pItem->m_pItem->sIndex <= stNeed_itemList[index].dListIndexArry[1]
                    || (unsigned int)pItem->m_pItem->sIndex >= stNeed_itemList[index].dListIndexArry[2]
                    && (unsigned int)pItem->m_pItem->sIndex <= stNeed_itemList[index].dListIndexArry[3]
                    || (unsigned int)pItem->m_pItem->sIndex >= stNeed_itemList[index].dListIndexArry[4]
                    && (unsigned int)pItem->m_pItem->sIndex <= stNeed_itemList[index].dListIndexArry[5])
                {
                    if (IsSameItem(&stNeed_itemList[index].stGridItem, pItem->m_pItem, 1) &&
                        IsItemOption_Satisfaction(index, pItem->m_pItem))
                    {
                        if (index == 27 && pItem->m_pItem->sIndex == 413 &&
                            pItem->m_pItem->stEffect[0].cEffect == EF_AMOUNT &&
                            pItem->m_pItem->stEffect[0].cValue != 10 ||
                            index == 27 && pItem->m_pItem->sIndex == 413 && pItem->m_pItem->stEffect[0].cEffect != EF_AMOUNT)
                        {
                            return;
                        }

                        if (!m_pGridNeedItem[i]->m_pItemList[0])
                        {
                            auto newItem = new STRUCT_ITEM(); // v52
                            newItem->sIndex = pItem->m_pItem->sIndex;

                            for (int kh = 0; kh < 3; ++kh)
                            {
                                newItem->stEffect[kh].cEffect = pItem->m_pItem->stEffect[kh].cEffect;
                                newItem->stEffect[kh].cValue = pItem->m_pItem->stEffect[kh].cValue;
                                newItem->stEffect[kh].sValue = pItem->m_pItem->stEffect[kh].sValue;
                            }

                            m_pGridNeedItem[i]->AddItem(new SGridControlItem(nullptr, newItem, 0.0f, 0.0f), 0, 0);

                            for (int j = 0; j < 4; ++j)
                            {
                                auto grid = m_pGridInvList[j];
                                for (int nY = 0; nY < 3; ++nY)
                                {
                                    for (int nX = 0; nX < 5; ++nX)
                                    {
                                        auto item = grid->GetItem(nX, nY);
                                        if (item && IsSameItem(item->m_pItem, pItem->m_pItem, 4))
                                            break;
                                    }
                                }

                                for (int ki = i; ki < 8; ++ki)
                                {
                                    if (!m_stCombineItem.Item[ki].sIndex)
                                    {
                                        pItem->m_GCObj.dwColor = -65536;
                                        memcpy((char*)&m_stCombineItem.Item[ki], pItem->m_pItem, sizeof STRUCT_ITEM);

                                        m_stCombineItem.CarryPos[ki] = 15 * Sourpage + 5 * pItem->m_nCellIndexY + pItem->m_nCellIndexX;
                                        break;
                                    }
                                }

                                auto pName = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_NAME_1 + j));
                                auto pVolume = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_VOLUME_1 + j));

                                pName->SetTextColor(0xFFFFFFFF);
                                pVolume->SetTextColor(0xFFFFFFFF);
                                m_dNeedRefer[i].dHavevolume = 1;

                                SetTextList();
                                return;
                            }
                        }
                    }
                }
                else if (stNeed_itemList[index].dListIndexArry[0]
                    && !stNeed_itemList[index].dListIndexArry[1]
                    && stNeed_itemList[index].dListIndexArry[0] == pItem->m_pItem->sIndex
                    && !m_pGridNeedItem[i]->m_pItemList[0]
                    && IsItemOption_Satisfaction(index, pItem->m_pItem))
                {
                    auto newItem = new STRUCT_ITEM(); // v52
                    newItem->sIndex = pItem->m_pItem->sIndex;

                    for (int kh = 0; kh < 3; ++kh)
                    {
                        newItem->stEffect[kh].cEffect = pItem->m_pItem->stEffect[kh].cEffect;
                        newItem->stEffect[kh].cValue = pItem->m_pItem->stEffect[kh].cValue;
                        newItem->stEffect[kh].sValue = pItem->m_pItem->stEffect[kh].sValue;
                    }

                    m_pGridNeedItem[i]->AddItem(new SGridControlItem(nullptr, newItem, 0.0f, 0.0f), 0, 0);

                    for (int j = 0; j < 4; ++j)
                    {
                        auto grid = m_pGridInvList[j];
                        for (int nY = 0; nY < 3; ++nY)
                        {
                            for (int nX = 0; nX < 5; ++nX)
                            {
                                auto item = grid->GetItem(nX, nY);
                                if (item && IsSameItem(item->m_pItem, pItem->m_pItem, 4))
                                    break;
                            }
                        }

                        for (int ki = i; ki < 8; ++ki)
                        {
                            if (!m_stCombineItem.Item[ki].sIndex)
                            {
                                pItem->m_GCObj.dwColor = -65536;
                                memcpy((char*)&m_stCombineItem.Item[ki], pItem->m_pItem, sizeof STRUCT_ITEM);

                                m_stCombineItem.CarryPos[ki] = 15 * Sourpage + 5 * pItem->m_nCellIndexY + pItem->m_nCellIndexX;
                                break;
                            }
                        }

                        auto pName = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_NAME_1 + j));
                        auto pVolume = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_VOLUME_1 + j));

                        pName->SetTextColor(0xFFFFFFFF);
                        pVolume->SetTextColor(0xFFFFFFFF);
                        m_dNeedRefer[i].dHavevolume = 1;

                        SetTextList();
                        return;
                    }
                }
            }
            else if (
                IsSameItem(&stNeed_itemList[index].stGridItem, pItem->m_pItem, 1) &&
                IsItemOption_Satisfaction(index, pItem->m_pItem) &&
                !m_pGridNeedItem[i]->m_pItemList[0]
            )
            {
            auto newItem = new STRUCT_ITEM(); // v52
            newItem->sIndex = pItem->m_pItem->sIndex;

            for (int kh = 0; kh < 3; ++kh)
            {
                newItem->stEffect[kh].cEffect = pItem->m_pItem->stEffect[kh].cEffect;
                newItem->stEffect[kh].cValue = pItem->m_pItem->stEffect[kh].cValue;
                newItem->stEffect[kh].sValue = pItem->m_pItem->stEffect[kh].sValue;
            }

            m_pGridNeedItem[i]->AddItem(new SGridControlItem(nullptr, newItem, 0.0f, 0.0f), 0, 0);

            for (int j = 0; j < 4; ++j)
            {
                auto grid = m_pGridInvList[j];
                for (int nY = 0; nY < 3; ++nY)
                {
                    for (int nX = 0; nX < 5; ++nX)
                    {
                        auto item = grid->GetItem(nX, nY);
                        if (item && IsSameItem(item->m_pItem, pItem->m_pItem, 4))
                            break;
                    }
                }

                for (int ki = i; ki < 8; ++ki)
                {
                    if (!m_stCombineItem.Item[ki].sIndex)
                    {
                        pItem->m_GCObj.dwColor = -65536;
                        memcpy((char*)&m_stCombineItem.Item[ki], pItem->m_pItem, sizeof STRUCT_ITEM);

                        m_stCombineItem.CarryPos[ki] = 15 * Sourpage + 5 * pItem->m_nCellIndexY + pItem->m_nCellIndexX;
                        break;
                    }
                }

                auto pName = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_NAME_1 + j));
                auto pVolume = static_cast<SText*>(m_pControlContainer->FindControl(T_ITEM_MIX_VOLUME_1 + j));

                pName->SetTextColor(0xFFFFFFFF);
                pVolume->SetTextColor(0xFFFFFFFF);
                m_dNeedRefer[i].dHavevolume = 1;

                SetTextList();
                return;
            }
            }

        }
    }
}

void CItemMix::DoCombine(SMessagePanel* MessagePanel, SGridControl** GridInvList, int Coin)
{
    int count = 0;

    for (int i = 0; i < 8; ++i)
    {
        if (m_dNeedRefer[i].dindex)
            ++count;
    }

    if (count)
    {
        if (count != 1 || m_dNeedRefer[0].dHavevolume >= stNeed_itemList[m_dNeedRefer[0].dindex].dVolume)
        {
            for (int i = 0; i < count; ++i)
            {
                if (m_stCombineItem.CarryPos[i] < 0 && m_NPCHead != 54)
                {
                    MessagePanel->SetMessage(g_pMessageStringTable[412], 2000u);
                    MessagePanel->SetVisible(1, 1);

                    return;
                }
            }

            if (stResult_itemList[m_dResultIndex].dCost <= (unsigned int)Coin)
            {
                if (HardCode(MessagePanel, GridInvList))
                {
                    m_stCombineItem.Header.Type = stResult_itemList[m_dResultIndex].sMSG;

                    SendOneMessage((char*)&m_stCombineItem, sizeof m_stCombineItem);
                }
            }
            else
            {
                MessagePanel->SetMessage(g_pMessageStringTable[414], 2000u);
                MessagePanel->SetVisible(1, 1);
            }
        }
        else
        {
            MessagePanel->SetMessage(g_pMessageStringTable[413], 2000u);
            MessagePanel->SetVisible(1, 1);
        }
    }
    else
    {
        MessagePanel->SetMessage(g_pMessageStringTable[412], 2000u);
        MessagePanel->SetVisible(1, 1);
    }
}

int CItemMix::IsSameItem(STRUCT_MYITEM* Item1, STRUCT_ITEM* Item2, short deep)
{
    if (deep > 3)
    {
        if (Item1->sIndex != Item2->sIndex)
            return 0;

        deep = 3;
    }

    for (int i = 0; i < deep; ++i)
    {
        auto value = Item1->stEffect[i].cEffect;
        if (value == EF_SANC)
        {
            auto nItemSanc = MYGetItemSanc(Item1);
            if (nItemSanc > BASE_GetItemSanc(Item2))
                return 0;
        }
        else if (value == EF_AMOUNT)
        {
            if (Item2->stEffect[i].cEffect != EF_AMOUNT)
                return 0;

            if (Item1->stEffect[i].cValue != Item2->stEffect[i].cValue)
                return 0;
        }
    }

    return 1;
}

int CItemMix::IsSameItem(STRUCT_ITEM* Item1, STRUCT_ITEM* Item2, short deep)
{
    if (deep > 3)
    {
        if (Item1->sIndex != Item2->sIndex)
            return 0;

        deep = 3;
    }
    for (int i = 0; i < deep; ++i)
    {
        if (Item1->stEffect[i].cEffect == EF_SANC)
        {
            if (BASE_GetItemSanc(Item1) > BASE_GetItemSanc(Item2))
                return 0;
        }
        else if (Item1->stEffect[i].cEffect == EF_AMOUNT)
        {
            if (Item2->stEffect[i].cEffect != EF_AMOUNT)
                return 0;

            if (Item1->stEffect[i].cValue != Item2->stEffect[i].cValue)
                return 0;
        }
    }
    return 1;
}

int CItemMix::IsItemOption_Satisfaction(int index, STRUCT_ITEM* item)
{
    auto Return = 0;
    if (index == 15)
    {
        if (item->sIndex >= 1901 && item->sIndex <= 1910)
            Return = 1;
        if (item->sIndex >= 1234 && item->sIndex <= 1237)
            Return = 1;
        if (item->sIndex >= 1369 && item->sIndex <= 1372)
            Return = 1;
        if (item->sIndex >= 1519 && item->sIndex <= 1522)
            Return = 1;
        if (item->sIndex >= 1669 && item->sIndex <= 1672)
            Return = 1;
        if (item->sIndex == 1714)
            Return = 1;

        if (!Return)
            return 0;
    }

    if (index == 16)
    {
        if (item->sIndex >= 2491 && item->sIndex <= 2494)
            Return = 1;
        else if (item->sIndex >= 2551 && item->sIndex <= 2554)
            Return = 1;
        else if (item->sIndex >= 2611 && item->sIndex <= 2614)
            Return = 1;
        else if (item->sIndex >= 2671 && item->sIndex <= 2674)
            Return = 1;
        else if (item->sIndex >= 2731 && item->sIndex <= 2734)
            Return = 1;
        else if (item->sIndex >= 2791 && item->sIndex <= 2794)
            Return = 1;
        else if (item->sIndex >= 2859 && item->sIndex <= 2862)
            Return = 1;
        else if (item->sIndex >= 2863 && item->sIndex <= 2866)
            Return = 1;
        else if (item->sIndex >= 2895 && item->sIndex <= 2898)
            Return = 1;
        else if (item->sIndex >= 2935 && item->sIndex <= 2938)
            Return = 1;
        else
        {
            switch (item->sIndex)
            {
            case 1221:
            case 1222:
            case 1223:
            case 1224:
            case 1356:
            case 1357:
            case 1358:
            case 1359:
            case 1506:
            case 1507:
            case 1508:
            case 1509:
            case 1656:
            case 1657:
            case 1658:
            case 1659:
            case 1711:
                Return = 1;
                break;
            }
        }

        if (!Return)
            return 0;
    }
    if (stNeed_itemList[index].stOption.dClass[0])
    {
        if (stNeed_itemList[index].stOption.dClass[0] > (unsigned int)BASE_GetItemAbility(item, 112)
            || stNeed_itemList[index].stOption.dClass[1] < (unsigned int)BASE_GetItemAbility(item, 112))
        {
            return 0;
        }
        Return = 1;
    }

    if (index == 20)
    {
        auto target2grade = g_pItemList[item->sIndex].nUnique % 10;
        auto target2pos = g_pItemList[item->sIndex].nPos;
        auto target2look = BASE_GetItemAbility(item, 18);
        if (!g_pItemList[item->sIndex].nUnique)
            return 0;
        if (target2look == 1 && target2grade <= 6 && target2grade)
            return 0;
        if (target2look != 1 && target2grade <= 5 && target2grade)
            return 0;
    }
    if (stNeed_itemList[index].stOption.dPOS[0])
    {
        if (stNeed_itemList[index].stOption.dPOS[0] > (unsigned int)g_pItemList[item->sIndex].nPos || stNeed_itemList[index].stOption.dPOS[1] < (unsigned int)g_pItemList[item->sIndex].nPos)
            return 0;

        Return = 1;
    }

    auto test = 0;
    for (int i = 0; i < 2; ++i)
    {
        if (!stNeed_itemList[index].stOption.dPOS[i] && !stNeed_itemList[index].stOption.dClass[i])
            ++test;
    }

    if (test >= 2)
        Return = 1;

    return Return;
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

int CItemMix::MYGetItemSanc(STRUCT_MYITEM* item)
{
    if (item->sIndex >= 2330 && item->sIndex < 2390)
        return 0;
    if (item->sIndex >= 3200 && item->sIndex < 3300)
        return 0;
    if (item->sIndex >= 3980 && item->sIndex < 4000)
        return 0;
    
    auto sanc = 0;
    if (item->stEffect[0].cEffect != EF_SANC && item->stEffect[1].cEffect != EF_SANC && item->stEffect[2].cEffect != EF_SANC)
    {
        bool isPainted = item->stEffect[0].cEffect >= EF_STARTCOL && item->stEffect[0].cEffect <= EF_MAXCOL;
        if (isPainted)
            sanc = item->stEffect[0].cValue;
        else
        {
            isPainted = item->stEffect[1].cEffect >= EF_STARTCOL && item->stEffect[1].cEffect <= EF_MAXCOL;
            if (isPainted)
                sanc = item->stEffect[1].cValue;
            else
            {
                isPainted = item->stEffect[2].cEffect >= EF_STARTCOL && item->stEffect[2].cEffect <= EF_MAXCOL;
                if (isPainted)
                    sanc = item->stEffect[2].cValue;
            }
        }
    }
    else if (item->stEffect[0].cEffect == 43)
        sanc = item->stEffect[0].cValue;
    else if (item->stEffect[1].cEffect == 43)
        sanc = item->stEffect[1].cValue;
    else
        sanc = item->stEffect[2].cValue;

    auto isanc = sanc;
    if (item->sIndex != 786 && item->sIndex != 1936 && item->sIndex != 1937)
    {
        if ((signed int)sanc < 230)
            isanc = sanc % 10;
        else
            isanc = sanc - 220;
        if (isanc >= 10 && isanc <= 35)
            isanc = (isanc - 10) / 4 + 10;
    }

    return isanc;
}

int CItemMix::HardCode(SMessagePanel* MessagePanel, SGridControl** GridInvList)
{
    if (m_NPCHead == 54 && m_dNPCX == 19 && m_dNPCY == 13)
    {
        auto Item = GridInvList[m_stCombineItem.CarryPos[0] / 15]->GetItem(
            m_stCombineItem.CarryPos[0] % 15 % 5,
            m_stCombineItem.CarryPos[0] % 15 / 5
        );
        
        auto Item2 = GridInvList[m_stCombineItem.CarryPos[1] / 15]->GetItem(
            m_stCombineItem.CarryPos[1] % 15 % 5,
            m_stCombineItem.CarryPos[1] % 15 / 5
        );
        if (Item
            && (Item->m_pItem->sIndex >= 1901 && Item->m_pItem->sIndex <= 1910
                || Item->m_pItem->sIndex >= 1234 && Item->m_pItem->sIndex <= 1237
                || Item->m_pItem->sIndex >= 1369 && Item->m_pItem->sIndex <= 1372
                || Item->m_pItem->sIndex >= 1519 && Item->m_pItem->sIndex <= 1522
                || Item->m_pItem->sIndex >= 1669 && Item->m_pItem->sIndex <= 1672
                || Item->m_pItem->sIndex == 1714))
        {
            MessagePanel->SetMessage(g_pMessageStringTable[274], 2000u);
            MessagePanel->SetVisible(1, 1);
            return 0;
        }

        if (!Item2)
        {
            MessagePanel->SetMessage(g_pMessageStringTable[274], 2000u);
            MessagePanel->SetVisible(1, 1);

            return 0;
        }
    }
    else if (m_NPCHead == 55)
    {
        for (int i = 0; i < 2; ++i)
        {
            auto Item = GridInvList[m_stCombineItem.CarryPos[i] / 15]->GetItem(
                m_stCombineItem.CarryPos[0] % 15 % 5,
                m_stCombineItem.CarryPos[0] % 15 / 5
            ); // v22

            if (Item)
            {
                if (Item->m_pItem->sIndex >= 1901 && Item->m_pItem->sIndex <= 1910
                    || Item->m_pItem->sIndex >= 1234 && Item->m_pItem->sIndex <= 1237
                    || Item->m_pItem->sIndex >= 1369 && Item->m_pItem->sIndex <= 1372
                    || Item->m_pItem->sIndex >= 1519 && Item->m_pItem->sIndex <= 1522
                    || Item->m_pItem->sIndex >= 1669 && Item->m_pItem->sIndex <= 1672
                    || Item->m_pItem->sIndex == 1714)
                {
                    MessagePanel->SetMessage(g_pMessageStringTable[274], 2000u);
                    MessagePanel->SetVisible(1, 1);
                    return 0;
                }

                if (BASE_GetItemAbility(Item->m_pItem, EF_TRANS) == 3)
                {
                    MessagePanel->SetMessage(g_pMessageStringTable[359], 2000u);
                    MessagePanel->SetVisible(1, 1);
                    return 0;
                }
            }
        }

        auto Item1 = GridInvList[m_stCombineItem.CarryPos[0] / 15]->GetItem(
            m_stCombineItem.CarryPos[0] % 15 % 5,
            m_stCombineItem.CarryPos[0] % 15 / 5
        ); // v22

        auto Item2 = GridInvList[m_stCombineItem.CarryPos[1] / 15]->GetItem(
            m_stCombineItem.CarryPos[1] % 15 % 5,
            m_stCombineItem.CarryPos[1] % 15 / 5
        ); // v22

        if (strcmp(g_pItemList[Item1->m_pItem->sIndex].Name, g_pItemList[Item2->m_pItem->sIndex].Name))
        {
            MessagePanel->SetMessage(g_pMessageStringTable[262], 2000u);
            MessagePanel->SetVisible(1, 1);

            return 0;
        }
    }
    else if (m_NPCHead == 56)
    {
        auto Item = GridInvList[m_stCombineItem.CarryPos[0] / 15]->GetItem(
            m_stCombineItem.CarryPos[0] % 15 % 5,
            m_stCombineItem.CarryPos[0] % 15 / 5
        ); // v7

        auto target1grade = g_pItemList[Item->m_pItem->sIndex].nUnique % 10;
        auto target1pos = g_pItemList[Item->m_pItem->sIndex].nPos;
        auto target1look = BASE_GetItemAbility(Item->m_pItem, EF_CLASS);

        bool bOK = true;
        if (target1look == 1 && target1grade != 9)
            bOK = false;

        if (target1look != 1 && target1grade != 9)
            bOK = 0;

        if (!bOK)
        {
            MessagePanel->SetMessage(g_pMessageStringTable[273], 2000u);
            MessagePanel->SetVisible(1, 1);

            return 0;
        }

        if (!(target1pos & 63))
        {
            MessagePanel->SetMessage(g_pMessageStringTable[276], 2000u);
            MessagePanel->SetVisible(1, 1);

            return 0;
        }

        auto Item2 = GridInvList[m_stCombineItem.CarryPos[1] / 15]->GetItem(
            m_stCombineItem.CarryPos[1] % 15 % 5,
            m_stCombineItem.CarryPos[1] % 15 / 5
        ); // v8

        auto target2grade = g_pItemList[Item2->m_pItem->sIndex].nUnique % 10;
        auto target2pos = g_pItemList[Item2->m_pItem->sIndex].nPos;
        auto target2look = BASE_GetItemAbility(Item2->m_pItem, EF_CLASS);

        bool bOKa = true;
        if (g_pItemList[Item2->m_pItem->sIndex].nUnique)
        {
            if (target2look == 1 && target2grade <= 6 && target2grade)
                bOKa = false;

            if (target2look != 1 && target2grade <= 5 && target2grade)
                bOKa = false;
        }
        else
            bOKa = false;

        if (target2look == 1 && target2grade == 9)
            bOKa = false;
        if (target2look != 1 && target2grade == 9)
            bOKa = false;

        if (!bOKa)
        {
            MessagePanel->SetMessage(g_pMessageStringTable[275], 2000u);
            MessagePanel->SetVisible(1, 1);

            return 0;
        }

        if (target1look != target2look)
            bOKa = false;
        if (target1pos != target2pos)
            bOKa = false;

        if (!bOKa)
        {
            MessagePanel->SetMessage(g_pMessageStringTable[276], 2000u);
            MessagePanel->SetVisible(1, 1);

            return 0;
        }
    }
    else if (m_NPCHead == 67 && m_dNPCX == 25 && m_dNPCY == 13)
    {
        auto Item = GridInvList[m_stCombineItem.CarryPos[0] / 15]->GetItem(
            m_stCombineItem.CarryPos[0] % 15 % 5,
            m_stCombineItem.CarryPos[0] % 15 / 5
        ); // v27

        auto Item2 = GridInvList[m_stCombineItem.CarryPos[1] / 15]->GetItem(
            m_stCombineItem.CarryPos[1] % 15 % 5,
            m_stCombineItem.CarryPos[1] % 15 / 5
        ); // v25

        auto nItemSanc = BASE_GetItemSanc(Item->m_pItem);

        if (Item->m_pItem->sIndex != 413
            && Item->m_pItem->sIndex != 4127
            && (Item->m_pItem->sIndex < 5110 || Item->m_pItem->sIndex > 5133)
            && Item->m_pItem->sIndex != 421
            && Item->m_pItem->sIndex != 4127
            && Item->m_pItem->sIndex != 3448
            && Item->m_pItem->sIndex != 4043
            && ((Item->m_pItem->sIndex < 1901 || Item->m_pItem->sIndex > 1910)
                && (Item->m_pItem->sIndex < 1234 || Item->m_pItem->sIndex > 1237)
                && (Item->m_pItem->sIndex < 1369 || Item->m_pItem->sIndex > 1372)
                && (Item->m_pItem->sIndex < 1519 || Item->m_pItem->sIndex > 1522)
                && (Item->m_pItem->sIndex < 1669 || Item->m_pItem->sIndex > 1672)
                && Item->m_pItem->sIndex != 1714
                || nItemSanc != 9))
        {
            MessagePanel->SetMessage(g_pMessageStringTable[274], 2000u);
            MessagePanel->SetVisible(1, 1);

            return 0;
        }

        if (Item->m_pItem->sIndex >= 1901 && Item->m_pItem->sIndex <= 1910
            || Item->m_pItem->sIndex >= 1234 && Item->m_pItem->sIndex <= 1237
            || Item->m_pItem->sIndex >= 1369 && Item->m_pItem->sIndex <= 1372
            || Item->m_pItem->sIndex >= 1519 && Item->m_pItem->sIndex <= 1522
            || Item->m_pItem->sIndex >= 1669 && Item->m_pItem->sIndex <= 1672
            || Item->m_pItem->sIndex == 1714)
        {
            bool check = false;
            if (BASE_GetItemSanc(Item2->m_pItem) >= 15)
            {
                if (Item->m_pItem->sIndex == 1901 && Item2->m_pItem->sIndex >= 2491 && Item2->m_pItem->sIndex <= 2494)
                    check = true;
                else if (Item->m_pItem->sIndex == 1902 && Item2->m_pItem->sIndex >= 2551 && Item2->m_pItem->sIndex <= 2554)
                    check = true;
                else if (Item->m_pItem->sIndex == 1903 && Item2->m_pItem->sIndex >= 2611 && Item2->m_pItem->sIndex <= 2614)
                    check = true;
                else if (Item->m_pItem->sIndex == 1904 && Item2->m_pItem->sIndex >= 2671 && Item2->m_pItem->sIndex <= 2674)
                    check = true;
                else if (Item->m_pItem->sIndex == 1905 && Item2->m_pItem->sIndex >= 2731 && Item2->m_pItem->sIndex <= 2734)
                    check = true;
                else if (Item->m_pItem->sIndex == 1906 && Item2->m_pItem->sIndex >= 2791 && Item2->m_pItem->sIndex <= 2794)
                    check = true;
                else if (Item->m_pItem->sIndex == 1907 && Item2->m_pItem->sIndex >= 2859 && Item2->m_pItem->sIndex <= 2862)
                    check = true;
                else if (Item->m_pItem->sIndex == 1908 && Item2->m_pItem->sIndex >= 2863 && Item2->m_pItem->sIndex <= 2866)
                    check = true;
                else if (Item->m_pItem->sIndex == 1909 && Item2->m_pItem->sIndex >= 2895 && Item2->m_pItem->sIndex <= 2898)
                    check = true;
                else if (Item->m_pItem->sIndex == 1910 && Item2->m_pItem->sIndex >= 2935 && Item2->m_pItem->sIndex <= 2938)
                    check = true;
                else if (Item->m_pItem->sIndex == 1234 && Item2->m_pItem->sIndex == 1221)
                    check = true;
                else if (Item->m_pItem->sIndex == 1235 && Item2->m_pItem->sIndex == 1222)
                    check = true;
                else if (Item->m_pItem->sIndex == 1236 && Item2->m_pItem->sIndex == 1223)
                    check = true;
                else if (Item->m_pItem->sIndex == 1237 && Item2->m_pItem->sIndex == 1224)
                    check = true;
                else if (Item->m_pItem->sIndex == 1369 && Item2->m_pItem->sIndex == 1356)
                    check = true;
                else if (Item->m_pItem->sIndex == 1370 && Item2->m_pItem->sIndex == 1357)
                    check = true;
                else if (Item->m_pItem->sIndex == 1371 && Item2->m_pItem->sIndex == 1358)
                    check = true;
                else if (Item->m_pItem->sIndex == 1372 && Item2->m_pItem->sIndex == 1359)
                    check = true;
                else if (Item->m_pItem->sIndex == 1519 && Item2->m_pItem->sIndex == 1506)
                    check = true;
                else if (Item->m_pItem->sIndex == 1520 && Item2->m_pItem->sIndex == 1507)
                    check = true;
                else if (Item->m_pItem->sIndex == 1521 && Item2->m_pItem->sIndex == 1508)
                    check = true;
                else if (Item->m_pItem->sIndex == 1522 && Item2->m_pItem->sIndex == 1509)
                    check = true;
                else if (Item->m_pItem->sIndex == 1669 && Item2->m_pItem->sIndex == 1656)
                    check = true;
                else if (Item->m_pItem->sIndex == 1670 && Item2->m_pItem->sIndex == 1657)
                    check = true;
                else if (Item->m_pItem->sIndex == 1671 && Item2->m_pItem->sIndex == 1658)
                    check = true;
                else if (Item->m_pItem->sIndex == 1672 && Item2->m_pItem->sIndex == 1659)
                    check = true;
                else if (Item->m_pItem->sIndex == 1714 && Item2->m_pItem->sIndex == 1711)
                    check = true;
            }
            else
                check = false;

            if (!check)
            {
                MessagePanel->SetMessage(g_pMessageStringTable[274], 2000u);
                MessagePanel->SetVisible(1, 1);

                return 0;
            }

            auto Item3 = GridInvList[m_stCombineItem.CarryPos[2] / 15]->GetItem(
                m_stCombineItem.CarryPos[2] % 15 % 5,
                m_stCombineItem.CarryPos[2] % 15 / 5);

            bool checka = false;
            if (Item->m_pItem->sIndex >= 1901 && Item->m_pItem->sIndex <= 1910 && Item3->m_pItem->sIndex == 772)
                checka = true;
            else if (Item->m_pItem->sIndex >= 1234 && Item->m_pItem->sIndex <= 1237 && Item3->m_pItem->sIndex == 542)
                checka = true;
            else if (Item->m_pItem->sIndex >= 1369 && Item->m_pItem->sIndex <= 1372 && Item3->m_pItem->sIndex == 542)
                checka = true;
            else if (Item->m_pItem->sIndex >= 1519 && Item->m_pItem->sIndex <= 1522 && Item3->m_pItem->sIndex == 542)
                checka = true;
            else if (Item->m_pItem->sIndex >= 1669 && Item->m_pItem->sIndex <= 1672 && Item3->m_pItem->sIndex == 542)
                checka = true;
            else if (Item->m_pItem->sIndex == 1714 && Item3->m_pItem->sIndex == 772)
                checka = true;

            if (!checka)
            {
                MessagePanel->SetMessage(g_pMessageStringTable[274], 2000u);
                MessagePanel->SetVisible(1, 1);
                return 0;
            }
        }
    }

    return 1;
}
