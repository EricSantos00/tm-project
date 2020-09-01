#include "pch.h"
#include "TMSkillCure.h"
#include "TMGlobal.h"
#include "TMEffectParticle.h"
#include "TMEffectBillBoard.h"
#include "TMShade.h"
#include "TMUtil.h"

TMSkillCure::TMSkillCure(TMVector3 vecPosition, int nType)
    : TMEffect()
{
    m_nType = nType;
    m_vecPosition = vecPosition;
    m_dwStartTime = g_pTimerManager->GetServerTime();
    m_dwLifeTime = 3000;

    int nCount = 16;
    if (g_pDevice->m_fFPS < 10.0f)
        nCount = 2;
    else if (g_pDevice->m_fFPS < 20.0f)
        nCount = 8;
    else if (g_pDevice->m_fFPS < 30.0f)
        nCount = 12;

    if (!g_bHideEffect)
    {
        auto pParticle = new TMEffectParticle(vecPosition, 0, nCount, 0.1f, 0, 1, 56, 1.0f, 1, {}, 1000);
        g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);
    }

    float fSize = 0.3f;
    nCount = 5;
    if (g_pDevice->m_fFPS < 10.0f)
        nCount = 2;
    else if (g_pDevice->m_fFPS < 25.0f)
        nCount = 4;

    if (!g_bHideEffect)
    {
        for (int i = 0; i < nCount; ++i)
        {
            auto pEffect = new TMEffectBillBoard(
                56,
                300 * i + 2000,
                ((float)(i % 2) * fSize) + 0.3f,
                ((float)(i % 2) * fSize) + 0.3f,
                ((float)(i % 2) * fSize) + 0.3f,
                0.0f,
                1,
                80);

            pEffect->m_fParticleH = 0.69f;
            pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            pEffect->m_nParticleType = 3;

            float fScale = ((float)(rand() % 5 - 3) * 0.3f) + vecPosition.z;
            float iZ = ((float)(rand() % 5 - 3) * 0.1f) + vecPosition.y;

            pEffect->m_vecStartPos = { (float)((float)(rand() % 5 - 3) * 0.3f) + vecPosition.x, iZ, fScale };
            pEffect->m_vecPosition = pEffect->m_vecStartPos;
            pEffect->SetColor(0xFFFFFFFF);
            g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
        }
    }

    auto pLightMap = new TMShade(4, 7, 1.0f);

    pLightMap->SetColor(0x55555555);
    pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
    pLightMap->SetPosition({ m_vecPosition.x, m_vecPosition.z });
    pLightMap->m_dwLifeTime = 3000;
    g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);

    GetSoundAndPlay(4, 0, 0);
}

TMSkillCure::~TMSkillCure()
{
}

int TMSkillCure::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();
    IsVisible();

    if (((float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime) > 1.0f)
        g_pObjectManager->DeleteObject(this);

    return 1;
}
