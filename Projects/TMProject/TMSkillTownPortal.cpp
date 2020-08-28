#include "pch.h"
#include "TMSkillTownPortal.h"
#include "TMMesh.h"
#include "TMGlobal.h"

TMSkillTownPortal::TMSkillTownPortal(TMVector3 vecPosition, int nType)
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
	return 0;
}

void TMSkillTownPortal::SetColor(unsigned int dwColor)
{
}
