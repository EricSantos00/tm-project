#include "pch.h"
#include "TMEffectBillBoard2.h"
#include "TMGate.h"
#include "TMGlobal.h"
#include "TMUtil.h"
#include "TMFieldScene.h"
#include "TMMesh.h"
#include "TMCamera.h"

TMGate::TMGate()
	: TMItem()
{
	m_sType = 0;
	m_sAuth = 0;
	m_pEffectSpecial = 0;
	m_stItem = {};
}

TMGate::~TMGate()
{
	if (m_pEffectSpecial)
		g_pObjectManager->DeleteObject(m_pEffectSpecial);
}

void TMGate::InitGate(STRUCT_ITEM stItem)
{
    m_eState = EGATE_STATE::EGATE_CLOSED;
    m_dwLastSetTime = 0;
    m_fOpenAngle = 0.0f;
    m_fWidth = 1.2f;
    m_StdMinus = 0.0f;
    m_StdPlus = 2.0f;
    m_RotMinus = 0.0f;
    m_RotPlus = 2.0f;
    if (m_stItem.sIndex >= 0 && m_stItem.sIndex <= 6500)
    {
        m_sItemIndex = stItem.sIndex;
        m_nLeftIndex = g_pItemList[m_sItemIndex].nIndexMesh;
        m_nRightIndex = g_pItemList[m_sItemIndex].nIndexMesh;
        m_stItem = stItem;
        switch (m_nRightIndex)
        {
        case 121:
            m_fWidth = 1.2f;
            m_StdMinus = 1.0f;
            m_StdPlus = 3.0f;
            m_RotMinus = 1.0f;
            m_RotPlus = 3.0f;
            break;
        case 136:
            m_nLeftIndex = 137;
            m_fWidth = 1.1f;
            m_StdMinus = 1.3f;
            m_StdPlus = 2.4f;
            m_RotMinus = 1.3f;
            m_RotPlus = 2.4f;
            break;
        case 141:
            m_StdMinus = 1.0f;
            m_StdPlus = 1.0f;
            m_RotMinus = 1.0f;
            m_RotPlus = 1.0f;
            break;
        case 989:
        case 990:
        case 991:
        case 992:
        {
            m_StdMinus = 1.0f;
            m_StdPlus = 1.0f;
            m_RotMinus = 1.0f;
            m_RotPlus = 1.0f;
            if (m_pEffectSpecial)
            {
                g_pObjectManager->DeleteObject(m_pEffectSpecial);
                m_pEffectSpecial = nullptr;
            }

            m_pEffectSpecial = new TMEffectBillBoard2(2, 0, 1.8f, 1.8f, 1.8f, 0.0f, 0);
            if (m_pEffectSpecial)
            {
                m_pEffectSpecial->m_pOwner = this;
                m_pEffectSpecial->m_bSlope = 0;
                m_pEffectSpecial->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                m_pEffectSpecial->m_nFade = 2;
                m_pEffectSpecial->m_fLocalHeight = 0.3f;
                if (m_nRightIndex == 989)
                    m_pEffectSpecial->SetColor(0xFF004488);
                if (m_nRightIndex == 990)
                    m_pEffectSpecial->SetColor(0xFF666600);
                if (m_nRightIndex == 991)
                    m_pEffectSpecial->SetColor(0xFF008800);
                if (m_nRightIndex == 992)
                    m_pEffectSpecial->SetColor(0xFF880000);
                g_pCurrentScene->m_pEffectContainer->AddChild(m_pEffectSpecial);
            }
        }
        break;
        case 148:
            m_StdMinus = 0.0;
            m_StdPlus = 0.0;
            m_RotMinus = 0.0;
            m_RotPlus = 0.0;
            break;
        case 480:
            m_nLeftIndex = 480;
            m_fWidth = 1.14f;
            m_StdMinus = 1.3f;
            m_StdPlus = 2.4f;
            m_RotMinus = 1.3f;
            m_RotPlus = 2.4f;
            break;
        case 1749:
            m_fWidth = 1.65f;
            break;
        case 2784:
            m_fWidth = 1.0f;
            m_StdMinus = 10.0f;
            m_StdPlus = 10.0f;
            m_RotMinus = 10.0f;
            m_RotPlus = 10.0f;
            break;
        default:
            m_StdMinus = 1.0f;
            m_StdPlus = 3.0f;
            m_RotMinus = 1.0f;
            m_RotPlus = 3.0f;
            break;
        }

        m_sType = m_nLeftIndex == 148 || m_nLeftIndex == 150;
        if (m_nLeftIndex == 141)
            m_sType = 2;
        if (m_nRightIndex >= 989 && m_nRightIndex <= 992)
            m_sType = 1;
        if (m_nRightIndex == 2784)
            m_sType = 1;
    }
}

int TMGate::Render()
{
    if (m_stItem.sIndex == 359)
        return 1;
    if (IsVisible() == 1)
    {
        g_pDevice->m_pd3dDevice->SetMaterial(&m_Materials);
        if (m_stItem.sIndex >= 3145 && m_stItem.sIndex <= 3149)
            return TMItem::Render();

        if (g_pDevice->m_bVoodoo != 1)
        {
            auto pMesh = g_pMeshManager->MeshManager::GetCommonMesh(m_nLeftIndex, 0, 180000);
            if (!pMesh)
                return 0;
            if (g_pTextureManager->m_stModelTextureList[pMesh->m_nTextureIndex[0]].cAlpha == 78)
            {
                g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 0);
                g_pDevice->SetTexture(1u, g_pTextureManager->GetEffectTexture(6, 5000));
                g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 4u);
            }
            g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
        }
        else
        {
            g_pDevice->SetTexture(1u, nullptr);
            g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
        }

        if (!m_sType)
        {
            float fDetail = 0.0f;
            if (m_nRightIndex == 136)
                fDetail = 0.2f;
            else if (m_nRightIndex == 1749)
                fDetail = 0.75f;
            if (m_sItemIndex == 773)
                fDetail = 0.61f;
            if (m_sItemIndex == 800)
                fDetail = 0.61f;

            D3DXMATRIX mat;
            D3DXMATRIX matPosition;
            D3DXMATRIX mat2;
            D3DXMATRIX matPosition2;
            D3DXMatrixIdentity(&mat);
            D3DXMatrixIdentity(&mat2);
            D3DXMatrixTranslation(&matPosition, m_vecPosition.x, m_fHeight, m_vecPosition.y);
            D3DXMatrixRotationYawPitchRoll(&mat, m_fAngle, 0, 0);
            D3DXMatrixMultiply(&mat, &mat, &matPosition);
            D3DXMatrixTranslation(&matPosition2, m_fWidth + fDetail, 0, 0);
            D3DXMatrixRotationYawPitchRoll(&mat2, -m_fOpenAngle + D3DXToRadian(180), -D3DXToRadian(90), 0);
            D3DXMatrixMultiply(&mat2, &mat2, &matPosition2);
            D3DXMatrixMultiply(&mat, &mat2, &mat);
            g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLD, &mat);
            
            auto pMesh1 = g_pMeshManager->GetCommonMesh(m_nLeftIndex, 0, 180000);
            if (!pMesh1)
                return 0;

            pMesh1->Render(0, 0);
            D3DXMatrixIdentity(&mat);
            D3DXMatrixIdentity(&mat2);
            D3DXMatrixTranslation(&matPosition, m_vecPosition.x, m_fHeight, m_vecPosition.y);
            D3DXMatrixRotationYawPitchRoll(&mat, m_fAngle, 0, 0);
            D3DXMatrixMultiply(&mat, &mat, &matPosition);
            D3DXMatrixTranslation(&matPosition2, (float)(-2.0f * m_fWidth) + fDetail, 0, 0);
            D3DXMatrixRotationYawPitchRoll(&mat2, m_fOpenAngle, -D3DXToRadian(90), 0);
            D3DXMatrixMultiply(&mat2, &mat2, &matPosition2);
            D3DXMatrixMultiply(&mat, &mat2, &mat);
            g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLD, &mat);
            
            auto pMesh2 = g_pMeshManager->GetCommonMesh(m_nRightIndex, 0, 180000);
            if (!pMesh2)
                return 0;

            pMesh2->Render(0, 0);
        }
        else if (m_sType == 1)
        {
            float fDetail = 1.2f;
            float fDetail2 = 0.0f;
            float fHeight = m_fHeight - m_fOpenAngle;
            if (m_nRightIndex >= 989 && m_nRightIndex <= 992)
            {
                fDetail = 0.0f;
                fDetail2 = -1.2f;
                fHeight = (float)(m_fHeight - m_fOpenAngle) - 0.89999998f;
                if (m_pEffectSpecial)
                    m_pEffectSpecial->m_fLocalHeight = -m_fOpenAngle + 0.2f;
            }
            else if (m_nRightIndex == 2784)
                return 1;

            D3DXMATRIX pOut;
            D3DXMATRIX matPosition;
            D3DXMATRIX mat2;
            D3DXMATRIX matPosition2;
            D3DXMatrixIdentity(&pOut);
            D3DXMatrixIdentity(&mat2);
            D3DXMatrixTranslation(&matPosition, m_vecPosition.x + fDetail2, fHeight, m_vecPosition.y + fDetail);
            D3DXMatrixRotationYawPitchRoll(&pOut, m_fAngle, 0, 0);
            D3DXMatrixMultiply(&pOut, &pOut, &matPosition);
            D3DXMatrixTranslation(&matPosition2, m_fWidth, 0, 0);
            D3DXMatrixRotationYawPitchRoll(&mat2, D3DXToRadian(180), -D3DXToRadian(90), 0);
            D3DXMatrixMultiply(&mat2, &mat2, &matPosition2);
            D3DXMatrixMultiply(&pOut, &mat2, &pOut);
            g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLD, &pOut);
            
            auto pMesh = g_pMeshManager->GetCommonMesh(m_nLeftIndex, 0, 180000);
            if (!pMesh)
                return 0;
            pMesh->Render(0, 0);
        }
        else if (m_sType == 2)
        {
            D3DXMATRIX pOut;
            D3DXMATRIX matPosition;
            D3DXMATRIX mat2;
            D3DXMATRIX matPosition2;
            D3DXMatrixIdentity(&pOut);
            D3DXMatrixIdentity(&mat2);
            D3DXMatrixTranslation(&matPosition, m_vecPosition.x + 0.3f, m_fHeight + m_fOpenAngle, m_vecPosition.y + 1.2f);
            D3DXMatrixRotationYawPitchRoll(&pOut, m_fAngle, 0, 0);
            D3DXMatrixMultiply(&pOut, &pOut, &matPosition);
            D3DXMatrixTranslation(&matPosition2, m_fWidth, 0, 0);
            D3DXMatrixRotationYawPitchRoll(&mat2, D3DXToRadian(180), -D3DXToRadian(90), 0);
            D3DXMatrixMultiply(&mat2, &mat2, &matPosition2);
            D3DXMatrixMultiply(&pOut, &mat2, &pOut);
            g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLD, &pOut);
            auto pMesh = g_pMeshManager->GetCommonMesh(m_nLeftIndex, 0, 180000);
            if (!pMesh)
                return 0;
            pMesh->Render(0, 0);
        }

        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
        g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
    }
    auto pFocused = g_pCurrentScene->m_pMyHuman;
    if (pFocused && 
        ((float)(pFocused->m_vecTargetPos.x - 33) > m_vecPosition.x || m_vecPosition.x > (float)(pFocused->m_vecTargetPos.x + 33) || 
         (float)(pFocused->m_vecTargetPos.y - 33) > m_vecPosition.y || m_vecPosition.y > (float)(pFocused->m_vecTargetPos.y + 33))
         && (TMGate*)g_pCurrentScene->m_pMouseOverItem == this)
    {
        g_pCurrentScene->m_pMouseOverItem = nullptr;
    }

    return 1;
}

int TMGate::FrameMove(unsigned int dwServerTime)
{
    if (m_stItem.sIndex >= 3145 && m_stItem.sIndex <= 3149)
        return TMItem::FrameMove(dwServerTime);

    if (m_dwID == 10054 && m_fHeight < -500.0f)
    {
        m_fHeight = 0.0f;
        m_sAuth = 0;
    }
    auto pFocused = g_pCurrentScene->m_pMyHuman;
    if (pFocused &&
        ((float)(pFocused->m_vecTargetPos.x - 33) > m_vecPosition.x || m_vecPosition.x > (float)(pFocused->m_vecTargetPos.x + 33) ||
         (float)(pFocused->m_vecTargetPos.y - 33) > m_vecPosition.y || m_vecPosition.y > (float)(pFocused->m_vecTargetPos.y + 33)))
    {
        if ((TMGate*)g_pCurrentScene->m_pMouseOverItem == this)
            g_pCurrentScene->m_pMouseOverItem = nullptr;

        m_eState = EGATE_STATE::EGATE_CLOSED;
        m_sAuth = 0;
        if (m_stItem.sIndex == 359)
            g_pObjectManager->DeleteObject(this);
    }
    if (!m_sAuth && m_stItem.sIndex > 0)
    {
        int nMaskIndex = BASE_GetItemAbility(&m_stItem, 34);
        BASE_UpdateItem2(nMaskIndex, 2, 2, (int)m_vecPosition.x, (int)m_vecPosition.y, (char*)g_pCurrentScene->m_HeightMapData, (int)(m_fAngle / D3DXToRadian(90)), 126);
    }
    if (m_eState == EGATE_STATE::EGATE_CLOSED || m_eState == EGATE_STATE::EGATE_LOCKED)
        m_fOpenAngle = 0.0f;
    else if (m_eState == EGATE_STATE::EGATE_CLOSING || m_eState == EGATE_STATE::EGATE_LOCKING)
    {
        m_fOpenAngle = D3DXToRadian(90) - ((((float)(dwServerTime - m_dwLastSetTime) * 0.001f) * D3DXToRadian(180)) / 2.0f);
        if (dwServerTime - m_dwLastSetTime > 1000)
        {
            if (m_eState == EGATE_STATE::EGATE_CLOSING)
                m_eState = EGATE_STATE::EGATE_CLOSED;
            else if (m_eState == EGATE_STATE::EGATE_LOCKING)
                m_eState = EGATE_STATE::EGATE_LOCKED;
        }
    }
    else if (m_eState == EGATE_STATE::EGATE_OPEN)
        m_fOpenAngle = D3DXToRadian(90);
    else if (m_eState == EGATE_STATE::EGATE_OPENING)
    {
        m_fOpenAngle = (((float)(dwServerTime - m_dwLastSetTime) * 0.001f) * D3DXToRadian(180)) / 2.0f;
        if (dwServerTime - m_dwLastSetTime > 1000)
            m_eState = EGATE_STATE::EGATE_OPEN;
    }
    if (m_bVisible == 1)
    {
        LabelPosition();
        
        auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
        auto color = pScene->GroundGetColor(m_vecPosition);

        m_Materials = {};
        if (IsMouseOver() == 1)
        {
            m_Materials.Emissive.r = 1.0f;
            m_Materials.Emissive.g = 1.0f;
            m_Materials.Emissive.b = 1.0f;
        }
        else
        {
            color.r = 0.7f;
            color.g = 0.7f;
            color.b = 0.7f;
            m_Materials.Emissive.r = 0.3f;
            m_Materials.Emissive.g = 0.3f;
            m_Materials.Emissive.b = 0.3f;
        }

        m_Materials.Diffuse = color;
        m_Materials.Specular = m_Materials.Diffuse; 
        m_Materials.Power = 0.0f;
    }

    return 1;
}

void TMGate::SetState(EGATE_STATE eState)
{
    if ((m_eState != EGATE_STATE::EGATE_OPEN || eState != EGATE_STATE::EGATE_OPENING) &&
        (m_eState != EGATE_STATE::EGATE_CLOSED || eState != EGATE_STATE::EGATE_CLOSING) &&
        (m_eState != EGATE_STATE::EGATE_LOCKED || eState != EGATE_STATE::EGATE_LOCKING))
    {
        if ((eState == EGATE_STATE::EGATE_CLOSING || eState == EGATE_STATE::EGATE_OPENING) && m_nRightIndex == 141 && g_pSoundManager)
            GetSoundAndPlay(57, 0, 0);

        m_dwLastSetTime = g_pTimerManager->GetServerTime();
        m_eState = eState;
    }
}

int TMGate::IsMouseOver()
{
    if (m_stItem.sIndex >= 3145 && m_stItem.sIndex <= 3149)
        return TMItem::IsMouseOver();
    if (m_nRightIndex >= 989 && m_nRightIndex <= 992)
    {
        m_bMouseOver = 0;
        return 0;
    }
    else if (m_nRightIndex == 1749)
    {
        m_bMouseOver = 0;
        return 0;
    }
    else if (m_StdPlus < 0.01f && m_StdPlus > -0.01f)
    {
        m_bMouseOver = 0;
        return 0;
    }
    else if (m_eState != EGATE_STATE::EGATE_LOCKED && m_nRightIndex != 2784)
    {
        m_bMouseOver = 0;
        return 0;
    }

    D3DXVECTOR3 vPickRayDir;
    D3DXVECTOR3 vPickRayOrig;
    g_pDevice->GetPickRayVector(&vPickRayOrig, &vPickRayDir);
    auto vecCam = g_pObjectManager->m_pCamera->m_cameraPos;
    auto pOldOverItem = g_pCurrentScene->m_pMouseOverItem;
    auto pFocusedObject = g_pCurrentScene->m_pMyHuman;
    float HeightPlus = 2.0f;
    float PosXPlus = 0.0f;
    if (m_nRightIndex == 1749)
        HeightPlus = 6.0f;
    else if (m_nRightIndex == 2784)
        PosXPlus = 1.3f;

    bool bMouseOver = false;
    int tAngle = (int)(m_fAngle / D3DXToRadian(90));
    if (!tAngle || tAngle == 2)
    {
        D3DXVECTOR3 v0{ m_vecPosition.x - m_StdMinus, m_fHeight + HeightPlus, m_vecPosition.y };
        D3DXVECTOR3 v1{ m_vecPosition.x + m_StdPlus, m_fHeight + HeightPlus, m_vecPosition.y };
        D3DXVECTOR3 v2{ m_vecPosition.x - m_StdMinus, m_fHeight, m_vecPosition.y };
        D3DXVECTOR3 v3{ m_vecPosition.x + m_StdPlus, m_fHeight, m_vecPosition.y };
        if (D3DXIntersectTri(&v0, &v2, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject || m_nRightIndex == 2784)
                g_pCurrentScene->m_pMouseOverItem = this;

            bMouseOver = 1;
        }
        if (!bMouseOver && D3DXIntersectTri(&v2, &v3, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject || m_nRightIndex == 2784)
                g_pCurrentScene->m_pMouseOverItem = this;

            bMouseOver = 1;
        }
    }
    else
    {
        D3DXVECTOR3 v0{ m_vecPosition.x + PosXPlus, m_fHeight + HeightPlus, m_vecPosition.y - m_RotMinus };
        D3DXVECTOR3 v1{ m_vecPosition.x + PosXPlus, m_fHeight + HeightPlus, m_vecPosition.y + m_RotPlus };
        D3DXVECTOR3 v2{ m_vecPosition.x + PosXPlus, m_fHeight, m_vecPosition.y - m_RotMinus };
        D3DXVECTOR3 v3{ m_vecPosition.x + PosXPlus, m_fHeight, m_vecPosition.y + m_RotPlus };
        if (D3DXIntersectTri(&v0, &v2, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject || m_nRightIndex == 2784)
                g_pCurrentScene->m_pMouseOverItem = this;
            bMouseOver = 1;
        }
        if (!bMouseOver && D3DXIntersectTri(&v2, &v3, &v1, &vPickRayOrig, &vPickRayDir, 0, 0, 0) == 1)
        {
            if (!pFocusedObject || m_nRightIndex == 2784)
                g_pCurrentScene->m_pMouseOverItem = this;
            bMouseOver = 1;
        }
    }
    if (pFocusedObject && bMouseOver == 1)
    {
        if (!pOldOverItem || fabsf(pOldOverItem->m_vecPosition.y - pFocusedObject->m_vecPosition.y) >= fabsf(m_vecPosition.y - pFocusedObject->m_vecPosition.y))
        {
            if (fabsf(m_vecPosition.x - pFocusedObject->m_vecPosition.x) <= 2.0f && fabsf(m_vecPosition.y - pFocusedObject->m_vecPosition.y) <= 2.0)
            {
                g_pCurrentScene->m_pMouseOverItem = this;
            }
        }
    }

    m_bMouseOver = bMouseOver;
    return bMouseOver;
}
