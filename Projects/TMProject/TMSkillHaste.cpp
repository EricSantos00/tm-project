#include "pch.h"
#include "TMSkillHaste.h"
#include "TMEffectBillBoard.h"
#include "TMGlobal.h"

TMSkillHaste::TMSkillHaste(TMVector3 vecPosition, int nType)
{
    m_nType = nType;
    m_vecPosition = vecPosition;
    m_dwStartTime = g_pTimerManager->GetServerTime();
    m_dwLifeTime = 3000;

    float fSize = 0.1f;

    int nCount = 15;

    static unsigned int dwCol[5]{ 0xFFFF0000, 0xFFAA00FF, 0xFF00AA00, 0xFFFFEEFF, 0xFFFFAA00 };
  
    if (!g_bHideEffect)
    {
        for (int i = 0; i < nCount; ++i)
        {
            int nRand = rand();
            
            auto pParticle = new TMEffectBillBoard(
                56,
                300 * i + 2000,
                ((float)(i % 2) * fSize) + 0.1f,
                ((float)(i % 2) * fSize) + 0.1f,
                ((float)(i % 2) * fSize) + 0.1f,
                0.0f,
                1,
                80);

            if (pParticle != nullptr)
            {
                pParticle->m_fParticleH = ((float)(i % 3) * 0.050000001f) + 0.1f;
                pParticle->m_fParticleV = -7.0f;
                pParticle->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
                pParticle->m_nParticleType = 3;

                pParticle->m_vecStartPos = { 
                    ((float)(nRand % 5 - 3) * 0.1f) + vecPosition.x,
                    ((float)(nRand % 5 - 3) * 0.1f) + vecPosition.y + 5.0f,
                    ((float)(nRand % 5 - 3) * 0.1f) + vecPosition.z };

                pParticle->m_vecPosition = pParticle->m_vecStartPos;
                pParticle->SetColor(dwCol[nType]);
                g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);
            }
        }
    }

    int nTexIndex = 52;

    if (nType == 1)
        nTexIndex = 51;

    if (nType == 2 || nType == 3 || nType == 4)
        nTexIndex = 122;
   
    auto pRay = new TMEffectBillBoard(nTexIndex, 4000, 1.5f, 10.0f, 1.5f, 0.0f, 1, 80);

    if (pRay != nullptr)
    {
        pRay->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        pRay->m_fAxisAngle = 2.792527f;
        pRay->m_vecPosition = pRay->m_vecStartPos = { vecPosition.x, vecPosition.y + 2.0f, vecPosition.z };

        if (nType == 2 || nType == 3 || nType == 4)
            pRay->SetColor(dwCol[nType]);

        g_pCurrentScene->m_pEffectContainer->AddChild(pRay);
    }

    if (g_pSoundManager != nullptr)
    {
        auto pSoundData = g_pSoundManager->GetSoundData(159);

        if (pSoundData)
            pSoundData->Play(0, 0);
    }
}

TMSkillHaste::~TMSkillHaste()
{
}

int TMSkillHaste::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();

    if (!IsVisible())
        return 0;

    if (((float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime) > 1.0f)
        g_pObjectManager->DeleteObject(this);

    return 1;
}
