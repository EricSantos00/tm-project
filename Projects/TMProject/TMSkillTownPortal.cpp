#include "pch.h"
#include "TMSkillTownPortal.h"
#include "TMMesh.h"
#include "TMEffectBillBoard2.h"
#include "TMGlobal.h"

TMSkillTownPortal::TMSkillTownPortal(TMVector3 vecPosition, int nType) : 
    TMEffect()
{
    m_dwLifeTime = 1000;
    m_fAngle = 0.0f;
    m_fProgress = 0.0f;
    m_vecPosition = vecPosition;
    m_nType = nType;
    m_dwStartTime = g_pTimerManager->GetServerTime();
    m_dwLastTime = 0;

    if (m_nType == 2)
        SetColor(0x55FF);
    else if (m_nType == 3)
        SetColor(0xFF5500);
    else
        SetColor(0xFFFFFFFF);
    
    if (g_pSoundManager)
    {
        auto pSoundData = g_pSoundManager->GetSoundData(159);
        if (pSoundData)
            pSoundData->Play(0, 0);
    }
}

TMSkillTownPortal::~TMSkillTownPortal()
{
}

int TMSkillTownPortal::Render()
{
    if (m_fProgress < 0.050000001f)
        return 1;

    if (m_bVisible == 1)
    {
        TMMesh* pMesh = g_pMeshManager->GetCommonMesh(703, 1, 180000);

        if (!pMesh)
            return 0;

        g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
        g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
        g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
        g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
        g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);

        pMesh->m_fScaleV = m_fAngle;
        pMesh->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, 0, 0, 1.5707964f, 0, 0);

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

int TMSkillTownPortal::IsVisible()
{
    TMMesh* pMesh = g_pMeshManager->GetCommonMesh(703, 1, 180000);
    if (pMesh)
        m_fRadius = pMesh->m_fRadius;
    else
        m_fRadius = 1.0f;
    return TMEffect::IsVisible();
}

int TMSkillTownPortal::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();

    if (!IsVisible())
        return 0;

    m_fProgress = (float)((int)(dwServerTime - m_dwStartTime)) / (float)m_dwLifeTime;
    if (m_fProgress > 1.0f)
    {
        g_pObjectManager->DeleteObject(this);
        return 1;
    }

    TMMesh* pMesh = g_pMeshManager->GetCommonMesh(703, 1, 180000);

    if (!pMesh)
        return 0;

    RDLVERTEX* pVertex;
    D3DVERTEXBUFFER_DESC vDesc;

    pMesh->m_pVB->GetDesc(&vDesc);
    pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);

    int nCount = vDesc.Size / 24;
    float fDif = fabsf(sinf(m_fProgress * D3DXToRadian(180)));

    for (int i = 0; i < nCount; ++i)
    {
        unsigned int dwR = (unsigned int)((float)m_dwR * fDif) << 16;
        unsigned int dwG = (unsigned int)((float)m_dwG * fDif) << 8;
        unsigned int dwB = (unsigned int)((float)m_dwB * fDif);
        pVertex[i].diffuse = dwB | dwG | dwR;
    }

    pMesh->m_pVB->Unlock();
    pMesh->m_nTextureIndex[0] = 58;

    if ((int)(dwServerTime - m_dwLastTime) > 100)
    {
        auto pEffect2 = new TMEffectBillBoard2(94, 700, 1.5f, 1.5f, 1.5f, 0.0f, 0);

        if (pEffect2)
        {
            pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pEffect2->SetColor(m_dwColor);
            pEffect2->m_vecPosition = m_vecPosition;
            pEffect2->m_vecPosition.y += (m_fProgress * 2.0f);

            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect2);
        }
        m_dwLastTime = dwServerTime;
    }

    if (m_nType == 1)
    {
        pMesh->m_fScaleV = (float)(m_fProgress * 0.69999999f) + 0.2f;
        pMesh->m_fScaleH = (float)(m_fProgress * 0.69999999f) + 0.2f;
    }
    else
    {
        pMesh->m_fScaleV = (fDif * 0.5f) + 0.5f;
        pMesh->m_fScaleH = (fDif * 0.5f) + 0.5f;
    }

    m_fAngle = m_fProgress * D3DXToRadian(180);

    return 1;
}

void TMSkillTownPortal::SetColor(unsigned int dwColor)
{
    m_dwColor = dwColor;
    m_dwA = (dwColor & 0xFF000000) >> 24;
    m_dwR = (dwColor & 0xFF0000) >> 16;
    m_dwG = (dwColor & 0xFF00) >> 8;
    m_dwB = static_cast<unsigned char>(dwColor);
}
