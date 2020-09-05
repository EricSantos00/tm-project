#include "pch.h"
#include "SControlContainer.h"
#include "SControl.h"
#include "MrItemMix.h"
#include "TMFieldScene.h"
#include "TMGlobal.h"
#include "SGrid.h"
#include "ItemEffect.h"

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
	return 0;
}

int CItemMix::Read_NMixListFile(const char* filename)
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
