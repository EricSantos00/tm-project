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
#include "TMCamera.h"
#include "TMMesh.h"
#include "Structures.h"

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
    m_nItemType = BASE_GetItemAbility(&m_stItem, 38);
    int nSanc = BASE_GetItemSanc(&m_stItem);
    unsigned int dwTextColor = BASE_GetItemColor(&m_stItem);
    if (m_nItemType == 10)
        m_bBonusEffect = 1;
    if (dwTextColor != 0xFFAAAAFF)
        m_bBonusEffect = 1;

    auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    int usGuild = BASE_GetItemAbility(&m_stItem, 57) | BASE_GetItemAbility(&m_stItem, 56) << 8;
    if (m_nItemType == 2)
    {
        unsigned char coin = (unsigned char)BASE_GetItemAbility(&m_stItem, 36) << 8;
        char tempb = BASE_GetItemAbility(&m_stItem, 37);
        coin += (unsigned char)tempb;

        char szValue[64]{};
        sprintf(szValue, g_pMessageStringTable[65], coin);
        if (m_pNameLabel)
            m_pNameLabel->SetText(szValue, 0);
    }
    else if (!usGuild)
    {
        char szStrName[128]{};
        if (m_stItem.sIndex >= 0)
            sprintf(szStrName, "%s", g_pItemList[m_stItem.sIndex].Name);
        if (m_pNameLabel)
        {
            m_pNameLabel->SetText(szStrName, 0);
            m_pNameLabel->SetTextColor(0xFFAAAAFF);
        }
    }
    else
    {
        m_stGuildMark.nGuild = usGuild & 0xFFF;
        m_stGuildMark.nSubGuild = 0;
        m_stGuildMark.nGuildChannel = ((int)usGuild >> 12) & 0xF;
        m_stGuildMark.sGuildIndex = 1;
        if (pFScene)
            pFScene->Guildmark_Create(&m_stGuildMark);
        
        char szValue[64]{};
        strcat(szValue, g_pItemList[m_stItem.sIndex].Name);
        if (m_pNameLabel)
        {
            m_pNameLabel->SetText(szValue, 0);
            if (m_stItem.sIndex >= 3145 && m_stItem.sIndex <= 3149)
                m_pNameLabel->SetTextColor(0xFFFFFFAA);
            else
                m_pNameLabel->SetTextColor(0xFFAAAAAA);
        }
    }

    m_pEffectSpecial = new TMEffectBillBoard2(2, 0, 0.8f, 0.8f, 0.8f, 0.0f, 0);
    if (m_pEffectSpecial && pFScene != nullptr)
    {
        m_pEffectSpecial->m_pOwner = this;
        m_pEffectSpecial->m_bSlope = 1;
        m_pEffectSpecial->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        m_pEffectSpecial->m_nFade = 2;
        m_pEffectSpecial->m_fLocalHeight = 0.1f;

        if (m_nItemType > 0 && m_nItemType <= 5)
        {
            switch (m_nItemType)
            {
            case 1:
                if (BASE_GetItemAbility(&m_stItem, 4) <= 0)
                    m_pEffectSpecial->SetColor(0xFF000066);
                else
                {
                    m_bHPotion = 1;
                    if (m_stItem.sIndex == 1739)
                        m_pEffectSpecial->SetColor(0xFFAA8888);
                    else
                        m_pEffectSpecial->SetColor(0xFF660000);
                }
                break;
            case 2:
                m_pEffectSpecial->SetColor(0xFF666600);
                break;
            case 3:
                m_pEffectSpecial->SetColor(0xFF666600);
                break;
            case 4:
                if (m_pNameLabel)
                    m_pNameLabel->SetTextColor(0xFFFFFFAA);
                m_pEffectSpecial->SetColor(0xFF774400);
                break;
            case 5:
                if (m_pNameLabel)
                    m_pNameLabel->SetTextColor(0xFFFFFFAA);
                m_pEffectSpecial->SetColor(0xFF440077);
                break;
            }

            pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
        }
        else if (m_nItemType == 10)
        {
            m_pEffectSpecial->SetColor(0xFF006600);
            pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
        }
        else if (m_stItem.sIndex == 747)
        {
            if (m_pNameLabel)
                m_pNameLabel->SetTextColor(0xFFFFAA00);
            m_pEffectSpecial->SetColor(0xFF884400);
            pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
        }
        else if (m_stItem.sIndex >= 777 && m_stItem.sIndex <= 784
            || m_stItem.sIndex >= 3170 && m_stItem.sIndex <= 3199)
        {
            m_pEffectSpecial->SetColor(0xFF660000);
            pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
            if (m_pNameLabel)
                m_pNameLabel->SetTextColor(0xFFFFFFAA);
        }
        else if (m_stItem.sIndex != 3914 && m_stItem.sIndex != 3915)
        {
            if (m_stItem.sIndex >= 3310 && m_stItem.sIndex <= 3550)
            {
                m_pEffectSpecial->SetColor(0xFF664466);
                pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
                if (m_pNameLabel)
                    m_pNameLabel->SetTextColor(0xFFFFFFAA);
            }
            else if (m_stItem.sIndex == 5135)
            {
                m_pEffectSpecial->SetColor(0xFF664466);
                pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
                if (m_pNameLabel)
                    m_pNameLabel->SetTextColor(0xFFFFFFAA);
            }
            else if (m_stItem.sIndex >= 4012 && m_stItem.sIndex <= 4050)
            {
                m_pEffectSpecial->SetColor(0xFF666644);
                pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
                if (m_pNameLabel)
                    m_pNameLabel->SetTextColor(0xFFFFFFAA);
            }
            else if (m_stItem.sIndex == 5316)
            {
                m_pEffectSpecial->SetColor(0xFF444488);
                pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
                if (m_pNameLabel)
                    m_pNameLabel->SetTextColor(0xFFFFFFAA);
            }
            else if (m_stItem.sIndex >= 4101 && m_stItem.sIndex < 4150 && m_stItem.sIndex != 4143)
            {
                m_pEffectSpecial->SetColor(0xFF444488);
                pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
                if (m_pNameLabel)
                    m_pNameLabel->SetTextColor(0xFFFFFFAA);
            }
            else if (m_stItem.sIndex >= 4010 && m_stItem.sIndex <= 4011 || m_stItem.sIndex >= 4026 && m_stItem.sIndex <= 4029)
            {
                m_pEffectSpecial->SetColor(0xFF666666);
                pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
                if (m_pNameLabel)
                    m_pNameLabel->SetTextColor(0xFFFFFFAA);
            }
            else if (m_stItem.sIndex == 785)
            {
                m_pEffectSpecial->SetColor(0xFF555533);
                pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
            }
            else if (m_stItem.sIndex >= 788 && m_stItem.sIndex <= 794)
            {
                m_pEffectSpecial->SetColor(0xFF555533);
                pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
            }
            else if (m_stItem.sIndex == 661)
            {
                m_pEffectSpecial->SetColor(0xFF660000);
                pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
            }
            else if (m_stItem.sIndex == 662)
            {
                m_pEffectSpecial->SetColor(0xFF000066);
                pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
            }
            else if (m_stItem.sIndex == 663)
            {
                m_pEffectSpecial->SetColor(0xFF006600);
                pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
            }
            else if (m_stItem.sIndex == 667)
            {
                m_pEffectSpecial->m_vecScale.x = 1.4f;
                m_pEffectSpecial->m_vecScale.y = 1.4f;
                m_pEffectSpecial->m_vecScale.z = 1.4f;
                m_pEffectSpecial->SetColor(0xFF000066);
                pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
            }
            else if (m_stItem.sIndex >= 436 && m_stItem.sIndex <= 441)
            {
                m_pEffectSpecial->m_vecScale.x = 1.4f;
                m_pEffectSpecial->m_vecScale.y = 1.4f;
                m_pEffectSpecial->m_vecScale.z = 1.4f;
                if (m_stItem.sIndex >= 439)
                    m_pEffectSpecial->SetColor(0xFF660000);
                else
                    m_pEffectSpecial->SetColor(0xFF000066);
                pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
            }
            else if (m_stItem.sIndex < 1744 || m_stItem.sIndex > 1751)
            {
                if (m_stItem.sIndex >= 5110 && m_stItem.sIndex <= 5133)
                {
                    m_pEffectSpecial->m_vertex[0].position = { -0.5f, 0.0f, -0.8f };
                    m_pEffectSpecial->m_vertex[1].position = { 0.89999998f, 0.0f, -0.8f };
                    m_pEffectSpecial->m_vertex[2].position = { 0.89999998f, 0.0f, 0.5f };
                    m_pEffectSpecial->m_vertex[3].position = { -0.5f, 0.0f, 0.5f };
                    m_pEffectSpecial->m_vecScale.x = 1.0f;
                    m_pEffectSpecial->m_vecScale.y = 1.0f;
                    m_pEffectSpecial->m_vecScale.z = 1.0f;
                    m_pEffectSpecial->m_fLocalHeight = -0.029999999f;
                    m_pEffectSpecial->SetColor(0xFF774400);
                    pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
                }
                else if (m_bBonusEffect == 1)
                {
                    switch (m_stItem.sIndex)
                    {
                    case 419:
                        m_pEffectSpecial->SetColor(0xFF774400);
                        pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
                        break;
                    case 420:
                        m_pEffectSpecial->SetColor(0xFF440077);
                        pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
                        break;
                    case 753:
                        m_pEffectSpecial->SetColor(0xFF660000);
                        pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
                        break;
                    default:
                        m_pEffectSpecial->m_fLocalHeight = 0.05f;
                        unsigned int dwEffectColor = 0xFF003300;
                        if (dwTextColor == 0xFFFFFFAA)
                            dwEffectColor = 0xFF555533;
                        else if (dwTextColor == 0xFFFFAA00)
                            dwEffectColor = 0xFF884400;

                        m_pEffectSpecial->SetColor(dwEffectColor);
                        pFScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
                        break;
                    }
                    if (m_pNameLabel)
                        m_pNameLabel->SetTextColor(dwTextColor);
                }
                else
                {
                    if (m_pNameLabel)
                        m_pNameLabel->SetTextColor(dwTextColor);
                    SAFE_DELETE(m_pEffectSpecial);
                }
            }
        }
    }
    if (m_stItem.sIndex == 1727)
    {
        for (int i = 0; i < 28; ++i)
        {
            if (m_pEffectBill[i])
            {
                g_pObjectManager->DeleteObject(m_pEffectBill[i]);
                m_pEffectBill[i] = nullptr;
            }
            m_pEffectBill[i] = new TMEffectBillBoard(56, 0, 1.5f, 1.5f, 1.5f, 0.0f, 1, 80);
            if (m_pEffectBill[i])
            {
                m_pEffectBill[i]->m_nFade = 2;
                if (i < 14)
                    m_pEffectBill[i]->SetColor(0xFFAAAA00);
                else if (i < 23)
                    m_pEffectBill[i]->SetColor(0xFF0088FF);
                else
                    m_pEffectBill[i]->SetColor(0xFFFF5500);

                m_pEffectBill[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

                if(pFScene)
                    pFScene->m_pEffectContainer->AddChild(m_pEffectBill[i]);
            }
        }
    }

    if(m_pNameLabel)
        m_dwNameColor = m_pNameLabel->m_GCText.pFont->m_dwColor;

    return TMObject::InitObject();
}

void TMItem::InitPosition(float fX, float fY, float fZ)
{
    TMObject::InitPosition(fX, fY, fZ);
    if (m_stItem.sIndex == 1727)
    {
        for (int i = 0; i < 28; ++i)
        {
            if (m_pEffectBill[i])
            {
                m_pEffectBill[i]->m_vecPosition.x = g_vecItemBillPos[i].x + m_vecPosition.x;
                m_pEffectBill[i]->m_vecPosition.y = g_vecItemBillPos[i].y + m_fHeight;
                m_pEffectBill[i]->m_vecPosition.z = g_vecItemBillPos[i].z + m_vecPosition.y;
            }
        }
    }
}

int TMItem::Render()
{
    if (m_dwObjType == -1)
        return 1;
    if (!m_stItem.sIndex)
        return 1;

    auto pCamera = g_pObjectManager->m_pCamera;
    if (IsVisible() != 1)
        return 1;

    int nMeshIndex = g_pItemList[m_stItem.sIndex].nIndexMesh;
    if (nMeshIndex < 737 || nMeshIndex > 739)
    {
        if (m_sMultiTexture > 0 && !g_pDevice->m_bVoodoo)
        {
            m_Materials.Diffuse.r = m_Materials.Diffuse.r / 2.0f;
            m_Materials.Diffuse.g = m_Materials.Diffuse.g / 2.4f;
            m_Materials.Diffuse.b = m_Materials.Diffuse.b / 2.8f;            
            m_Materials.Specular = m_Materials.Diffuse;
        }

        g_pDevice->m_pd3dDevice->SetMaterial(&m_Materials);
        auto pMesh = g_pMeshManager->GetCommonMesh(m_dwObjType, 0, 180000);
        if (pMesh)
        {
            float fHeight = 0.0f;
            float fAxisAngle = D3DXToRadian(90);
            if (m_nItemType == 4 || m_nItemType == 5)
                fAxisAngle = 0.0f;
            if (BASE_GetItemAbility(&m_stItem, 38) == 2 || BASE_GetItemAbility(&m_stItem, 38) == 1)
                fAxisAngle = 0.0f;
            if (g_pItemList[m_stItem.sIndex].nIndexMesh == 45)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex == 419 || m_stItem.sIndex == 420)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex == 747)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex >= 1701 && m_stItem.sIndex <= 1712)
                fAxisAngle = -D3DXToRadian(90);
            else if (m_stItem.sIndex == 1727)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex >= 1733 && m_stItem.sIndex <= 1736)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex == 1752 || m_stItem.sIndex >= 1760 && m_stItem.sIndex <= 1763)
            {
                fAxisAngle = 0.0f;
                fHeight = 0.1f;
            }
            else if (m_stItem.sIndex >= 1744 && m_stItem.sIndex <= 1751)
            {
                fAxisAngle = 0.0f;
                fHeight = 0.3f;
            }
            else if (m_stItem.sIndex >= 2300 && m_stItem.sIndex <= 2329)
            {
                fAxisAngle = 0.0f;
                fHeight = 0.3f;
            }
            else if (m_stItem.sIndex >= 2330 && m_stItem.sIndex <= 2359)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex >= 2360 && m_stItem.sIndex <= 2389)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex >= 2390 && m_stItem.sIndex <= 2449)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex >= 2960 && m_stItem.sIndex <= 2999)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex >= 5110 && m_stItem.sIndex <= 5133)
                fAxisAngle = -D3DXToRadian(90);
            else if (m_stItem.sIndex == 3443 || m_stItem.sIndex == 3444 || m_stItem.sIndex == 5135)
            {
                fAxisAngle = 0.0f;
                fHeight = -0.13f;
            }
            else if (m_stItem.sIndex >= 3197 && m_stItem.sIndex <= 3199)
                fAxisAngle = -D3DXToRadian(90);
            else if (m_stItem.sIndex >= 3500 && m_stItem.sIndex <= 3502)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex >= 3140 && m_stItem.sIndex <= 3550)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex >= 3145 && m_stItem.sIndex <= 3149)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex >= 3980 && m_stItem.sIndex <= 3999)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex == 4013)
                fAxisAngle = -D3DXToRadian(90);
            else if (m_stItem.sIndex >= 4106 && m_stItem.sIndex <= 4109)
                fAxisAngle = 0.0f;
            else if (m_stItem.sIndex == 5338)
            {
                fAxisAngle = 0.0f;
                fHeight = -0.15f;
            }
            else if (m_stItem.sIndex == 5134)
            {
                fAxisAngle = 0.0f;
                fHeight = -0.1f;
            }
            else if (m_stItem.sIndex == 3447 || m_stItem.sIndex == 3448)
                fHeight = -0.1f;
            else if (m_stItem.sIndex == 5137)
                fAxisAngle = -D3DXToRadian(90);
            if (m_dwObjType == 405 || m_dwObjType == 1607)
                fAxisAngle = 0.0f;

            int nIndexTexture = g_pItemList[m_stItem.sIndex].nIndexTexture;
            if (nMeshIndex == 27)
            {
                if (g_pItemList[m_stItem.sIndex].nIndexTexture >= 6 && g_pItemList[m_stItem.sIndex].nIndexTexture <= 9)
                    nIndexTexture = g_pItemList[m_stItem.sIndex].nIndexTexture - 1;
                else if (g_pItemList[m_stItem.sIndex].nIndexTexture >= 11 && g_pItemList[m_stItem.sIndex].nIndexTexture <= 17)
                    nIndexTexture = g_pItemList[m_stItem.sIndex].nIndexTexture - 2;
                else if (g_pItemList[m_stItem.sIndex].nIndexTexture == 19)
                    nIndexTexture = g_pItemList[m_stItem.sIndex].nIndexTexture - 3;
                else if (g_pItemList[m_stItem.sIndex].nIndexTexture == 21 || g_pItemList[m_stItem.sIndex].nIndexTexture == 22)
                    nIndexTexture = g_pItemList[m_stItem.sIndex].nIndexTexture - 4;
            }
            if (m_sMultiTexture > 0 || m_sLegendType >= 4 && m_sLegendType <= 8)
            {
                if (m_sLegendType == 4)
                {
                    int nBaseIndex = 179;
                    g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(m_sMultiTexture + 179, 5000));
                    g_pDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 1);
                    if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
                    {
                        g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 4u);
                    }
                    else
                    {
                        g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 5u);
                        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 4u);
                    }

                    pMesh->Render(
                        m_vecPosition.x,
                        m_fHeight + fHeight,
                        m_vecPosition.y,
                        m_fAngle,
                        fAxisAngle,
                        0,
                        1,
                        nIndexTexture);
                }
                else if (m_sLegendType > 4 && m_sLegendType <= 8)
                {
                    int nBaseIndex = 153;
                    if (m_sLegendType == 6)
                        nBaseIndex = 166;
                    if (m_sLegendType == 7)
                        nBaseIndex = 246;
                    if (m_sLegendType == 8)
                        nBaseIndex = 260;

                    g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(m_sMultiTexture + nBaseIndex, 5000));
                    if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
                    {
                        g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 7u);
                    }
                    else
                    {
                        g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 0xBu);
                    }

                    pMesh->Render(
                        m_vecPosition.x,
                        m_fHeight + fHeight,
                        m_vecPosition.y,
                        m_fAngle,
                        fAxisAngle,
                        0,
                        1,
                        nIndexTexture);
                }
                else if (m_sLegendType >= 9 && m_sLegendType <= 12)
                {
                    int nBaseIndex = 153;
                    if (m_sLegendType == 10)
                        nBaseIndex = 166;
                    if (m_sLegendType == 11)
                        nBaseIndex = 246;
                    if (m_sLegendType == 12)
                        nBaseIndex = 260;

                    g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(m_sMultiTexture + nBaseIndex, 5000));
                    if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
                    {
                        g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 7u);
                    }
                    else
                    {
                        g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 5u);
                        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 0xBu);
                    }

                    pMesh->Render(
                        m_vecPosition.x,
                        m_fHeight + fHeight,
                        m_vecPosition.y,
                        m_fAngle,
                        fAxisAngle,
                        0,
                        1,
                        nIndexTexture);
                }
                else if (m_sLegendType >= 116 && m_sLegendType <= 125 && m_sMultiTexture > 0)
                {
                    int nBaseIndex = 275;
                    if (m_sLegendType == 116)
                        nBaseIndex = 275;
                    if (m_sLegendType == 117)
                        nBaseIndex = 288;
                    if (m_sLegendType == 118)
                        nBaseIndex = 301;
                    if (m_sLegendType == 119)
                        nBaseIndex = 314;
                    if (m_sLegendType == 120)
                        nBaseIndex = 327;
                    if (m_sLegendType == 121)
                        nBaseIndex = 340;
                    if (m_sLegendType == 122)
                        nBaseIndex = 353;
                    if (m_sLegendType == 123)
                        nBaseIndex = 366;
                    if (m_sLegendType == 124)
                        nBaseIndex = 425;
                    if (m_sLegendType == 125)
                        nBaseIndex = 392;

                    g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(nBaseIndex + m_sMultiTexture - 1, 5000));
                    if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400 || g_pDevice->m_bTNT)
                    {
                        g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 7u);
                    }
                    else
                    {
                        g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, 1u);
                        g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 0x18u);
                        if (m_sLegendType == 120)
                            g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 4u);
                        else if (m_sLegendType == 119)
                            g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 8u);
                        else
                            g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 6u);
                    }

                    pMesh->Render(
                        m_vecPosition.x,
                        m_fHeight + fHeight,
                        m_vecPosition.y,
                        m_fAngle,
                        fAxisAngle,
                        0,
                        1,
                        nIndexTexture);
                }
                else
                {
                    g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(m_sMultiTexture + 233, 5000));
                    g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
                    if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
                    {
                        g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 7u);
                    }
                    else
                    {
                        if (m_sMultiTexture < 7)
                            g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                        else
                            g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 5u);
                        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 0xBu);
                    }

                    pMesh->Render(
                        m_vecPosition.x,
                        m_fHeight + fHeight,
                        m_vecPosition.y,
                        m_fAngle,
                        fAxisAngle,
                        0,
                        1,
                        nIndexTexture);
                }
                g_pDevice->SetTexture(1u, nullptr);
                g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
                g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
            }
            else
            {
                g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
                if (m_stItem.sIndex == 169)
                {
                     pMesh->Render(
                        m_vecPosition.x,
                        m_fHeight + fHeight,
                        m_vecPosition.y,
                        m_fAngle,
                        fAxisAngle,
                        0,
                        0,
                        -4);
                }
                else
                {
                    pMesh->Render(
                        m_vecPosition.x,
                        m_fHeight + fHeight,
                        m_vecPosition.y,
                        m_fAngle,
                        fAxisAngle,
                        0,
                        0,
                        nIndexTexture);
                }
            }
        }
        return 1;
    }

    g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
    g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
    g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);

    auto pMesh = g_pMeshManager->GetCommonMesh(nMeshIndex, 1, 180000);
    if (pMesh)
    {
        const static unsigned int dwColor[3]{ 0xFFFF4400, 0xFF3366FF, 0xFF00FF00 };

        D3DVERTEXBUFFER_DESC vDesc;
        pMesh->m_pVB->GetDesc(&vDesc);
        RDLVERTEX* pVertex;
        pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);

        int nCount = vDesc.Size / sizeof(RDLVERTEX);
        // TODO: review this loops, very strange
        for (int i = 0; i < nCount; ++i)
            pVertex[i].diffuse = dwColor[nMeshIndex - 2980];

        pMesh->m_pVB->Unlock();
        pMesh->m_nTextureIndex[0] = 204;
        pMesh->Render(
            m_vecPosition.x,
            m_fHeight,
            m_vecPosition.y,
            m_fAngle,
            0,
            0,
            0,
            0);
    }

    g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
    return 1;
}

int TMItem::IsMouseOver()
{
    if (!m_stItem.sIndex)
    {
        m_bMouseOver = 0;
        return 0;
    }
    if (m_dwObjType == 405)
    {
        m_bMouseOver = 0;
        return 0;
    }

    D3DXVECTOR3 vPickRayDir;
    D3DXVECTOR3 vPickRayOrig;
    g_pDevice->GetPickRayVector(&vPickRayOrig, &vPickRayDir);

    auto vecCam = g_pObjectManager->m_pCamera->m_cameraPos;
    auto pOldOverItem = g_pCurrentScene->m_pMouseOverItem;
    auto pFocusedObject = (TMObject*)g_pCurrentScene->m_pMyHuman;

    bool bMouseOver = false;
    float fRadius = 0.60000002f;
    float fRadius2 = 0.69999999f;

    if (m_dwObjType == 1607)
        fRadius = 1.0f;
    if (m_stItem.sIndex >= 3145 && m_stItem.sIndex <= 3149)
    {
        fRadius = 3.0f;
        fRadius2 = 3.0f;
    }

    D3DXVECTOR3 v0{ m_vecPosition.x - fRadius, m_fHeight + fRadius2, m_vecPosition.y };
    D3DXVECTOR3 v1{ m_vecPosition.x + fRadius, m_fHeight + fRadius2, m_vecPosition.y };
    D3DXVECTOR3 v2( m_vecPosition.x - fRadius, m_fHeight, m_vecPosition.y);
    D3DXVECTOR3 v3{ m_vecPosition.x + fRadius, m_fHeight, m_vecPosition.y };

    if (D3DXIntersectTri(&v0, &v2, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
    {
        if (!pFocusedObject)
            g_pCurrentScene->m_pMouseOverItem = this;
        bMouseOver = 1;
    }
    if (!bMouseOver && D3DXIntersectTri(&v2, &v3, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
    {
        if (!pFocusedObject)
            g_pCurrentScene->m_pMouseOverItem = this;
        bMouseOver = 1;
    }

    v0 = { m_vecPosition.x, m_fHeight + fRadius2, m_vecPosition.y - fRadius };
    v1 = { m_vecPosition.x, m_fHeight + fRadius2, m_vecPosition.y + fRadius };
    v2 = { m_vecPosition.x, m_fHeight, m_vecPosition.y - fRadius };
    v3 = { m_vecPosition.x, m_fHeight, m_vecPosition.y + fRadius };

    if (!bMouseOver && D3DXIntersectTri(&v0, &v2, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
    {
        if (!pFocusedObject)
            g_pCurrentScene->m_pMouseOverItem = this;
        bMouseOver = 1;
    }
    if (!bMouseOver && D3DXIntersectTri(&v2, &v3, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
    {
        if (!pFocusedObject)
            g_pCurrentScene->m_pMouseOverItem = this;
        bMouseOver = 1;
    }

    if (pFocusedObject && bMouseOver == 1 && !pOldOverItem)
        g_pCurrentScene->m_pMouseOverItem = this;

    m_bMouseOver = bMouseOver;
    return bMouseOver;
}

int TMItem::FrameMove(unsigned int dwServerTime)
{
    if (!m_stItem.sIndex)
        return 1;

    m_stGuildMark.pGuildMark->SetVisible(0);
    m_pNameLabel->SetVisible(0);
    auto pFocused = (TMHuman*)g_pObjectManager->m_pCamera->GetFocusedObject();
    if (pFocused && 
        ((float)(pFocused->m_vecTargetPos.x - 18) > m_vecPosition.x || m_vecPosition.x > (float)(pFocused->m_vecTargetPos.x + 18) || 
         (float)(pFocused->m_vecTargetPos.y - 18) > m_vecPosition.y || m_vecPosition.y > (float)(pFocused->m_vecTargetPos.y + 18)))
    {
        if (g_pCurrentScene->m_pMouseOverItem == this)
            g_pCurrentScene->m_pMouseOverItem = nullptr;

        if (m_dwObjType != 405 && m_dwObjType != 1607 && (m_dwObjType < 2723 || m_dwObjType > 2727))
            g_pObjectManager->DeleteObject(this);
    }

    if (m_bVisible == 1)
    {
        LabelPosition();
        auto pScene = (TMFieldScene*)g_pCurrentScene;
        auto color = pScene->GroundGetColor(m_vecPosition);

        m_Materials = {};
        if (IsMouseOver() != 1 || m_stItem.sIndex >= 3145 && m_stItem.sIndex <= 3149)
        {
            if (m_nItemType == 3 || m_nItemType == 2 || m_nItemType == 1)
            {
                m_Materials.Emissive.r = (float)(color.r * 0.2f) + 0.69999999f;
                m_Materials.Emissive.g = (float)(color.g * 0.2f) + 0.69999999f;
                m_Materials.Emissive.b = (float)(color.b * 0.2f) + 0.69999999f;
            }
            else
            {
                m_Materials.Emissive.r = (float)(color.r * 0.3f) + 0.3f;
                m_Materials.Emissive.g = (float)(color.g * 0.3f) + 0.3f;
                m_Materials.Emissive.b = (float)(color.b * 0.3f) + 0.3f;
            }
            if (m_stItem.sIndex == 1727)
            {
                m_Materials.Emissive.r = (float)(color.r * 0.4f) + 0.6f;
                m_Materials.Emissive.g = (float)(color.g * 0.4f) + 0.6f;
                m_Materials.Emissive.b = (float)(color.b * 0.4f) + 0.6f;
            }
        }
        else
        {
            m_Materials.Emissive.r = 1.0f;
            m_Materials.Emissive.g = 1.0f;
            m_Materials.Emissive.b = 1.0f;
        }

        m_Materials.Ambient.r = 1.0f;
        m_Materials.Ambient.g = 1.0f;
        m_Materials.Ambient.b = 1.0f;
        m_Materials.Ambient.a = 1.0f;
        m_Materials.Diffuse = color;


        m_Materials.Specular = m_Materials.Diffuse;
        m_Materials.Power = 0.0f;
    }

    return 1;
}

void TMItem::LabelPosition()
{
    if (m_pNameLabel)
    {
        if (m_pNameLabel->IsVisible() != 1 || m_stGuildMark.pGuildMark->m_GCPanel.nMarkIndex == -1)
            m_stGuildMark.pGuildMark->SetVisible(0);
        else
            m_stGuildMark.pGuildMark->SetVisible(1);

        m_pNameLabel->SetTextColor(m_dwNameColor);
        if (m_bMouseOver != 1 && g_pEventTranslator->m_bCtrl != 1)
            m_pNameLabel->SetVisible(0);
        else
        {
            if (m_bMouseOver == 1 && g_pEventTranslator->m_bCtrl == 1)
                m_pNameLabel->SetTextColor(0xFFFFFFFF);

            D3DXVECTOR3 vTemp;
            D3DXVECTOR3 vPosTransformed;
            D3DXVECTOR3 vecPos;
            vecPos.x = m_vecPosition.x;
            vecPos.z = m_vecPosition.y;
            vecPos.y = m_fHeight + 0.3f;
            D3DXVec3TransformCoord(&vTemp, &vecPos, &g_pDevice->m_matView);
            D3DXVec3TransformCoord(&vPosTransformed, &vTemp, &g_pDevice->m_matProj);
            if (vPosTransformed.z < 0.0f || vPosTransformed.z >= 1.0f)
                m_pNameLabel->SetVisible(0);
            else
            {
                int vPosInX = (int)(((vPosTransformed.x + 1.0f) * (float)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift)) / 2.0f);
                int vPosInY = (int)(((-vPosTransformed.y + 1.0f) * (float)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift)) / 2.0f);
                if (vPosInX <= 0 || vPosInX >= (int)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift) || 
                    vPosInY <= 0 || vPosInY >= (int)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift))
                    m_pNameLabel->SetVisible(0);
                else
                {
                    m_pNameLabel->SetVisible(1);
                    m_pNameLabel->SetRealPos((float)vPosInX - 64.0f, (float)vPosInY);
                    if (m_stGuildMark.pGuildMark)
                    {
                         m_stGuildMark.pGuildMark->SetPos(m_pNameLabel->m_nPosX + 10.0f,
                            m_pNameLabel->m_nPosY + 3.0f);
                        m_stGuildMark.pGuildMark->SetVisible(1);
                    }
                }
            }
        }
    }

    if (m_stGuildMark.nGuild == -1)
        m_stGuildMark.pGuildMark->SetVisible(0);

}
