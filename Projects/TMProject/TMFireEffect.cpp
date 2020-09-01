#include "pch.h"
#include "TMObject.h"
#include "TMFireEffect.h"
#include "TMGlobal.h"
#include "TMUtil.h"
#include "TMEffectBillBoard.h"

TMFireEffect::TMFireEffect(TMVector3 vecStart, TMObject* pTarget, int nTextureIndex) : TreeNode(0)
{
    if (pTarget)
    {
        m_pOwner = 0;
        m_nEntity = 0;
        m_fLen = 1.0f;
        m_vecStartPos = vecStart;
        m_vecTargetPos = { pTarget->m_vecPosition.x, pTarget->m_fHeight + 1.0f, pTarget->m_vecPosition.y };
        m_vecDistance = m_vecTargetPos - m_vecStartPos;
        m_fLen = m_vecDistance.Length();
        m_nTextureIndex = nTextureIndex;

        D3DXVECTOR3 vec{ m_vecDistance.x, m_vecDistance.y, m_vecDistance.z };
        D3DXVec3Normalize(&vec, &vec);
        m_vecDistance = *reinterpret_cast<TMVector3*>(&vec);
        m_dwLifeTime = (unsigned int)((m_fLen * 1000.0f) - 10.0f);
        m_dwCreateTime = g_pTimerManager->GetServerTime();
        if (m_dwLifeTime > 2500)
            m_dwLifeTime = 2500;
        else if (m_dwLifeTime == 0)
            m_dwLifeTime = 1;

        GetSoundAndPlayIfNot(77, 0, 0);
    }
}

TMFireEffect::~TMFireEffect()
{
}

int TMFireEffect::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();
    unsigned int dwTerm = dwServerTime - m_dwCreateTime;
    if (m_dwLifeTime && m_dwLifeTime < dwTerm && dwServerTime > m_dwCreateTime)
    {
        g_pObjectManager->DeleteObject(this);
        return 1;
    }

    float fProgress = (float)dwTerm / (float)m_dwLifeTime;
    if (fProgress < 0.0f || fProgress >= 1.0f)
        return 1;

    if (!g_bHideEffect && (fProgress * 20.0f) > (float)m_nEntity)
    {
        ++m_nEntity;
        auto pEffect = new TMEffectBillBoard(
            m_nTextureIndex + m_nEntity % 2,
            1000,
            0.5f,
            0.5f,
            0.5f,
            ((float)m_nEntity * 0.00019999999f),
            1,
            80);

        pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pEffect->m_vecStartPos = m_vecStartPos;
        pEffect->m_vecPosition = pEffect->m_vecStartPos;
        pEffect->m_nParticleType = 17;
        pEffect->m_vecDir = m_vecDistance;
        g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
    }
    
    return 1;
}
