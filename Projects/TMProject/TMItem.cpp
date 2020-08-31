#include "pch.h"
#include "TMEffectBillBoard.h"
#include "TMEffectBillBoard2.h"
#include "SControl.h"
#include "TMItem.h"
#include "TMGlobal.h"
#include "TMFieldScene.h"
#include "Basedef.h"
#include "TMScene.h"
#include "SControlContainer.h"

TMItem::TMItem() 
	: TMObject()
{
	m_pEffectSpecial = 0;
	m_pNameLabel = 0;
	m_stItem = {};
	memset(m_pEffectBill, 0, sizeof(m_pEffectBill));
	m_stGuildMark.pGuildMark = 0;
	m_stGuildMark.nSubGuild = 0;
	m_stGuildMark.nGuildChannel = 0;
	m_stGuildMark.nGuild = -1;
	memset(m_stGuildMark.strMarkFileName, 0, sizeof(m_stGuildMark.strMarkFileName));
	m_stGuildMark.nMarkIndex = 0;
	m_stGuildMark.bHideGuildmark = 0;
	m_dwNameColor = 0;
	++g_nItemCount;
}

TMItem::~TMItem()
{
	if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD && static_cast<TMFieldScene*>(g_pCurrentScene)->m_pTargetItem == this)
		static_cast<TMFieldScene*>(g_pCurrentScene)->m_pTargetItem = nullptr;

	if (m_pNameLabel)
		g_pObjectManager->DeleteObject(m_pNameLabel);
	m_pNameLabel = nullptr;

	if (m_pEffectSpecial)
		g_pObjectManager->DeleteObject(m_pEffectSpecial);
	m_pEffectSpecial = nullptr;

	SAFE_DELETE(m_stGuildMark.pGuildMark);
	
	for (int i = 0; i < 28; ++i)
	{
		if (m_pEffectBill[i])
		{
			g_pObjectManager->DeleteObject(m_pEffectBill[i]);
			m_pEffectBill[i] = nullptr;
		}
	}

	--g_nItemCount;
}

void TMItem::InitItem(STRUCT_ITEM stItem)
{
    m_dwID = -1;
    m_sMultiTexture = 0;
    m_sLegendType = 0;
    m_bMouseOver = 0;
    m_bHPotion = 0;
    m_nItemType = 0;
    m_stItem = stItem;

    if (m_stItem.sIndex >= 0 && m_stItem.sIndex <= 6500)
    {
        m_dwObjType = BASE_GetMeshIndex(this->m_stItem.sIndex);
        m_sMultiTexture = BASE_GetItemSanc(&stItem);
        if (m_sMultiTexture > 12)
            m_sMultiTexture = 12;

        m_sLegendType = g_pItemList[m_stItem.sIndex].nGrade;

        g_pObjectManager->DeleteObject(m_pNameLabel);
        m_pNameLabel = nullptr;

        m_pNameLabel = new SText(-1, "NoName", 0xFFAAAAFF, 0.0f, 0.0f, 128.0f, 16.0f, 0, 0, 1, 1);
        m_pNameLabel->SetVisible(0);

        g_pCurrentScene->m_pControlContainer->AddItem(m_pNameLabel);
        if (m_pEffectSpecial)
            g_pObjectManager->DeleteObject(m_pEffectSpecial);

        m_pEffectSpecial = 0;
        m_bBonusEffect = 0;

        if (m_stItem.sIndex == 412 || m_stItem.sIndex == 413 || m_stItem.sIndex == 4141 || m_stItem.sIndex == 419 || m_stItem.sIndex == 420 || 
            m_stItem.sIndex == 753 || m_stItem.sIndex == 769 || m_stItem.sIndex == 1726 || m_stItem.sIndex >= 5110 && m_stItem.sIndex <= 5133)
        {
            m_bBonusEffect = 1;
        }

        switch (BASE_GetItemColorEffect(&stItem))
        {
        case 116:
            m_sLegendType = 116;
            break;
        case 117:
            m_sLegendType = 117;
            break;
        case 118:
            m_sLegendType = 118;
            break;
        case 119:
            m_sLegendType = 119;
            break;
        case 120:
            m_sLegendType = 120;
            break;
        case 121:
            m_sLegendType = 121;
            break;
        case 122:
            m_sLegendType = 122;
            break;
        case 123:
            m_sLegendType = 123;
            break;
        case 124:
            m_sLegendType = 124;
            break;
        case 125:
            m_sLegendType = 125;
            break;
        }
        if ((g_pItemList[m_stItem.sIndex].nUnique == 51 || m_sLegendType) && m_sLegendType <= 4 && m_sMultiTexture > 9)
        {
            m_sLegendType = (unsigned char)BASE_GetItemTenColor(&stItem) + 4;
        }
        else if (m_sLegendType == 4 && m_sMultiTexture > 9)
        {
            m_sLegendType = (unsigned char)BASE_GetItemTenColor(&stItem);
        }

        m_stGuildMark.pGuildMark = nullptr;
        if (g_pCurrentScene && g_pCurrentScene->m_pControlContainer)
        {
            m_stGuildMark.pGuildMark = new SPanel(-2, 0.0, 0.0, 10.0, 10.0, 0x77777777u, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
            if (m_stGuildMark.pGuildMark)
                g_pCurrentScene->m_pControlContainer->AddItem(m_stGuildMark.pGuildMark);
        }

        m_pEffectSpecial = nullptr;
    }
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
