#include "pch.h"
#include "TMSkillIceSpear.h"
#include "TMShade.h"
#include "TMGlobal.h"
#include "TMUtil.h"
#include "TMFieldScene.h"
#include "TMShade.h"
#include "TMSkillFreezeBlade.h"
#include "TMMesh.h"

TMSkillIceSpear::TMSkillIceSpear(TMVector3 vecStart, TMVector3 vecTarget, int nLevel, TMObject* pOwner) : 
	TMEffect()
{
    m_fAngle = 0.0f;
    m_fProgress = 0.0f;
    m_vecPosition = m_vecStartPos = vecStart;    
    m_vecTargetPos = vecTarget;
    m_nLevel = nLevel;
    m_dwStartTime = g_pTimerManager->GetServerTime();

    GetSoundAndPlay(154, 0, 0);

    TMVector3 vecD{ vecTarget - vecStart };
    float fLength = vecD.Length();

    m_dwLifeTime = 100 * (unsigned int)fLength;
    if (!m_dwLifeTime)
        m_dwLifeTime = 1;
    if (m_dwLifeTime > 5000)
        m_dwLifeTime = 5000;

    m_pLightMap = new TMShade(4, 7, 1.0f);
    if (m_pLightMap)
    {
        m_pLightMap->SetColor(0x33333344);
        m_pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
    }

    m_pOwner = pOwner;
    GetSoundAndPlay(160, 0, 0);    
}

TMSkillIceSpear::~TMSkillIceSpear()
{
    SAFE_DELETE(m_pLightMap);

    if (!g_bHideEffect)
        g_pCurrentScene->m_pEffectContainer->AddChild(new TMSkillFreezeBlade({ m_vecPosition.x, m_vecPosition.y - 1.0f, m_vecPosition.z }, 1, 0, 0));
}

int TMSkillIceSpear::Render()
{
    if (m_fProgress < 0.05f)
        return 1;

    auto pMesh = g_pMeshManager->GetCommonMesh(708, 1, 180000);
    if (!pMesh)
        return 1;

    g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
    g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
    g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
    g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
    g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);

    pMesh->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, m_fAngle, 0, D3DXToRadian(90), 0, 0);

    if (m_pLightMap)
        m_pLightMap->RenderUnder();

    g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
    g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
    g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
    g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
    g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
    return 1;
}

int TMSkillIceSpear::IsVisible()
{
    auto pMesh = g_pMeshManager->GetCommonMesh(708, 1, 180000);
    if (pMesh)
        m_fRadius = pMesh->m_fRadius;
    else
        m_fRadius = 1.0f;

    return TMEffect::IsVisible();
}

int TMSkillIceSpear::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();
    
    auto pMesh = g_pMeshManager->GetCommonMesh(708, 1, 180000);
    if (!IsVisible())
        return 0;

    if (pMesh)
    {
        D3DVERTEXBUFFER_DESC vDesc;
        pMesh->m_pVB->GetDesc(&vDesc);

        RDLVERTEX* pVertex;
        pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);

        int nCount = vDesc.Size / sizeof(RDLVERTEX);
        for (int i = 0; i < nCount; ++i)
            pVertex[i].diffuse = 0xFFFFFFFF;

        pMesh->m_pVB->Unlock();
        pMesh->m_nTextureIndex[0] = 19;
    }

    m_fProgress = (float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime;
    if (m_fProgress > 0.5f && m_pOwner)
        m_pOwner = nullptr;

    if (m_pOwner)
    {
        m_vecTargetPos.x = m_pOwner->m_vecPosition.x;
        m_vecTargetPos.z = m_pOwner->m_vecPosition.y;
        m_vecTargetPos.y = m_pOwner->m_fHeight + 1.0f;
    }

    TMVector3 vecDPos{ m_vecTargetPos - m_vecStartPos };
    m_fAngle = atan2f(vecDPos.x, vecDPos.z) - D3DXToRadian(90);
    if (m_fProgress < 1.0f)
    {
        m_vecPosition = (m_vecStartPos * (1.0f - m_fProgress)) + (m_vecTargetPos * m_fProgress);
        if (m_pLightMap)
            m_pLightMap->SetPosition({ m_vecPosition.x, m_vecPosition.z });
    }
    else
        g_pObjectManager->DeleteObject(this);

    return 1;
}
