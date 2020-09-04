#include "pch.h"
#include "TMSkillFreezeBlade.h"
#include "TMShade.h"
#include "TMGlobal.h"
#include "TMUtil.h"
#include "TMFieldScene.h"
#include "TMShade.h"
#include "TMMesh.h"
#include "TMEffectBillBoard2.h"
#include "TMEffectBillBoard.h"

TMSkillFreezeBlade::TMSkillFreezeBlade(TMVector3 vecPosition, int nType, int nType2, int nType3) : 
	TMEffect()
{
    m_nType = nType;
    m_nType2 = nType2;
    m_nType3 = nType3;
    m_vecPosition = vecPosition;
    m_vecNextD = {0.0f, 0.0f};
    m_dwStartTime = g_pTimerManager->GetServerTime();
    m_dwLifeTime = 2000;
    m_dwLastTime = 0;
    m_fAngle = 0.0f;
    m_fProgress = 0.0f;
    m_bNext = 0;
    m_nMeshIndex = 706;

    if (m_nType == 1)
        m_nMeshIndex = 707;
    if (m_nType2 == 1)
    {
        m_nMeshIndex = 2818;
        m_dwLifeTime = 2000;
        m_dwStartTime = rand() % 500 + g_pTimerManager->GetServerTime();
        m_bNext = 1;
    }
    else if (m_nType > 1 && m_nType < 9)
    {
        m_nMeshIndex = m_nType + 710;
        m_dwLifeTime = 1500;
    }
    else
    {
        auto pEffect20 = new TMEffectBillBoard2(2, 2000, 2.0f, 2.0f, 2.0f, 0.002f, 0);

        pEffect20->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pEffect20->m_vecPosition = m_vecPosition;
        pEffect20->m_bSlope = 1;
        pEffect20->m_vecPosition.y += 0.3f;
        pEffect20->SetColor(0xFF2255AA);
        g_pCurrentScene->m_pEffectContainer->AddChild(pEffect20);
    }

    if (m_nType2 != 1 && g_pSoundManager)
        GetSoundAndPlay(160, 0, 0);
}

TMSkillFreezeBlade::~TMSkillFreezeBlade()
{
}

int TMSkillFreezeBlade::Render()
{
    if (m_fProgress < 0.05f)
        return 1;

    auto pMesh = g_pMeshManager->GetCommonMesh(m_nMeshIndex, m_nType >= 2 ? 0 : 1, 180000);
    if (!pMesh)
        return 0;

    g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
    if (m_nType >= 2)
    {
        g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
        g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
        g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
        g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
    }
    else
    {
        g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
        g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
        g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
        g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
        g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
    }

    if (m_nType3 == 1)
        pMesh->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, (m_fProgress * 5.0f) + D3DXToRadian(90), 0, (m_fProgress * 5.0f) + D3DXToRadian(90), 0, 0);
    else
        pMesh->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, D3DXToRadian(90), 0, D3DXToRadian(90), 0, 0);

    if (m_nType < 2)
    {
        g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
        g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
        g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
        g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
    }
    return 1;
}

int TMSkillFreezeBlade::IsVisible()
{
    auto pMesh = g_pMeshManager->GetCommonMesh(m_nMeshIndex, m_nType >= 2 ? 0 : 1, 180000);
    if (pMesh)
        m_fRadius = pMesh->m_fRadius;

    return TMEffect::IsVisible();
}

int TMSkillFreezeBlade::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();

    if (((float)dwServerTime - (float)m_dwStartTime) < 0.0f)
        return 1;

    auto pMesh = g_pMeshManager->GetCommonMesh(m_nMeshIndex, m_nType >= 2 ? 0 : 1, 180000);
    if (!pMesh)
        return 0;

    if (!IsVisible())
        return 0;

    m_fProgress = (float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime;
    if (m_fProgress >= 1.0f)
    {
        g_pObjectManager->DeleteObject(this);
        return 1;
    }

    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);

    TMVector2 vecPos{ m_vecPosition.x, m_vecPosition.z };
    int nMask = pScene->GroundGetMask(vecPos);

    m_vecPosition.y = (float)nMask * 0.1f;
    if (m_nType2 != 1)
    {
        if (m_nType < 2)
        {
            unsigned int dwColor = 0x55113366;
            if (m_fProgress >= 0.6f)
            {
                float fAlpha = cosf(((m_fProgress - 0.6f) * 1.25f) * D3DXToRadian(180));
                unsigned int dwA = (unsigned int)(fAlpha * 85.0f);
                unsigned int dwR = (unsigned int)(fAlpha * 17.0f);
                unsigned int dwG = (unsigned int)(fAlpha * 51.0f);
                unsigned int dwB = (unsigned int)(fAlpha * 102.0f);
                dwColor = dwB | (dwG << 8) | (dwR << 16) | (dwA << 24);
            }
            
            D3DVERTEXBUFFER_DESC vDesc;
            pMesh->m_pVB->GetDesc(&vDesc);

            RDLVERTEX* pVertex;
            pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);

            size_t nCount = vDesc.Size / sizeof(RDLVERTEX);
            for (size_t i = 0; i < nCount; ++i)
                pVertex[i].diffuse = dwColor;

            pMesh->m_pVB->Unlock();
            pMesh->m_nTextureIndex[0] = 19;
        }
        else
        {
            char szTexture[64]{};
            sprintf(szTexture, "mesh\\stone01.wys");
            pMesh->m_nTextureIndex[0] = g_pTextureManager->GetModelTextureIndex(szTexture);
        }
    }
    if (m_nType > 1 && m_nType < 9)
    {
        if (m_fProgress < 0.1f)
            pMesh->m_fScaleV = (m_fProgress * 11.0f) + 0.1f;
        if (m_fProgress > 0.89999998f)
            pMesh->m_fScaleV = 1.2f - ((m_fProgress - 0.89999998f) * 11.0f);
    }
    else if (m_fProgress < 0.1f)
    {
        pMesh->m_fScaleV = (m_fProgress * 15.0f) + 0.2f;
    }
    if (m_nType3 == 1)
    {
        pMesh->m_fScaleV = m_fProgress * 3.0f;
        pMesh->m_fScaleH = m_fProgress * 2.0f;
    }

    static unsigned int dwOldTime = 0;
    if (dwServerTime - dwOldTime > 100)
    {
        int nRand = rand() % 5;

        auto pBill = new TMEffectBillBoard(0, 1500, ((float)nRand * 0.3f) + 0.5f, ((float)nRand * 0.3f) + 0.5f, ((float)nRand * 0.3f) + 0.5f, 0.001f, 1, 80);
        pBill->m_vecPosition = { ((float)(rand() % 10 - 5) * 0.2f) + m_vecPosition.x, m_vecPosition.y, ((float)(rand() % 10 - 5) * 0.2f) + m_vecPosition.z };        
        if (m_nType > 1 && m_nType < 9)
        {
            pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
            pBill->SetColor(0xFFAAAAAA);
        }
        else
        {
            pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pBill->SetColor(0xFFAAEEFF);
        }
        pBill->m_bStickGround = 1;
        g_pCurrentScene->m_pEffectContainer->AddChild(pBill);
        dwOldTime = dwServerTime;
    }

    float NextfProgress = 0.2f;
    if (!m_bNext && m_nType > 1 && m_nType < 8 && m_fProgress > NextfProgress)
    {
        TMVector3 vecNext;
        vecNext = m_vecPosition;
        vecNext.x = vecNext.x + m_vecNextD.x;
        vecNext.z = vecNext.z + m_vecNextD.y;

        auto pFreeze = new TMSkillFreezeBlade(vecNext, m_nType + 1, m_nType2, 0);
        pFreeze->m_vecNextD = m_vecNextD;
        g_pCurrentScene->m_pEffectContainer->AddChild(pFreeze);

        m_bNext = 1;
    }

    return 1;
}