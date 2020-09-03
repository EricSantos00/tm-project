#include "pch.h"
#include "TMSkillSpeedUp.h"
#include "TMEffectBillBoard.h"
#include "TMEffectBillBoard2.h"
#include "TMShade.h"
#include "TMGlobal.h"

TMSkillSpeedUp::TMSkillSpeedUp(TMVector3 vecPosition, int nType)
{
    m_nType = nType;
    m_vecPosition = vecPosition;
    m_dwStartTime = g_pTimerManager->GetServerTime();
    m_dwLifeTime = 1000;
    
    auto pEffect2 = new TMEffectBillBoard2(
        8,
        1000,
        ((float)m_nType * 1.5f) + 0.0099999998f,
        ((float)m_nType * 1.5f) + 0.0099999998f,
        ((float)m_nType * 1.5f) + 0.0099999998f,
        0.003f,
        0);

    if (pEffect2 != nullptr)
    {
        pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pEffect2->m_vecPosition = m_vecPosition;
        pEffect2->m_vecPosition.y -= 0.60000002f;
        g_pCurrentScene->m_pEffectContainer->AddChild(pEffect2);
    }
   
    auto pEffect = new TMEffectBillBoard(
        33,
        1000,
        ((float)m_nType * 1.5f) + 1.5f,
        ((float)m_nType * 1.5f) + 1.5f,
        ((float)m_nType * 1.5f) + 1.5f,
        0.0f,
        9,
        111);

    if (pEffect != nullptr)
    {
        pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pEffect->m_nFade = 0;
        pEffect->m_vecPosition = m_vecPosition;
        pEffect->m_vecPosition.y -= 0.5f;
        g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
    }
    
    auto pLightMap = new TMShade(4, 7, 1.0f);

    if (pLightMap != nullptr)
    {
        pLightMap->SetColor(0x70704000);
        pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pLightMap->SetPosition({ m_vecPosition.x, m_vecPosition.z });
        pLightMap->m_dwLifeTime = 1500;
        g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);
    }

    int nSoundIndex = 166;

    if (m_nType == 1)
        nSoundIndex = 154;

    if (g_pSoundManager != nullptr)
    {
        auto pSoundData = g_pSoundManager->GetSoundData(nSoundIndex);

        if (pSoundData)
            pSoundData->Play(0, 0);
    }
}

TMSkillSpeedUp::~TMSkillSpeedUp()
{
}

int TMSkillSpeedUp::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();

    if (!IsVisible())
        return 0;

    if (((float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime) > 1.0f)
        g_pObjectManager->DeleteObject(this);

    return 1;
}
