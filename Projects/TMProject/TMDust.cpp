#include "pch.h"
#include "TMDust.h"
#include "TMEffectDust.h"
#include "TMEffectParticle.h"
#include "TMCamera.h"
#include "TMGlobal.h"

TMDust::TMDust(float fScale, int nType) 
	: TMObject()
{
	m_dwLastTime = 0;
	m_nType = nType;
	m_fScaleH = fScale;
	m_fScaleV = fScale;
}

TMDust::~TMDust()
{
}

int TMDust::Render()
{
	return 1;
}

int TMDust::FrameMove(unsigned int dwServerTime)
{
    IsVisible();

    unsigned int dwTerm = 10000;

    if (m_nType == 2)
        dwTerm = 2500;

    dwServerTime = g_pTimerManager->GetServerTime();

    if ((dwServerTime - m_dwLastTime) > dwTerm)
    {
        int nRand = rand() % 5;

        if ((nRand % 2) == 1)
        {
            if (m_nType < 2)
            {
                if (g_pSoundManager != nullptr)
                {
                    auto pSoundData = g_pSoundManager->GetSoundData(2);

                    if (pSoundData != nullptr && !pSoundData->IsSoundPlaying())
                        pSoundData->Play(0, 0);
                }

                for (int i = 0; i < nRand; ++i)
                {
                    TMVector3 vec{ m_vecPosition.x + ((float)(i + nRand - 3) * 0.69999999f), m_fHeight, m_vecPosition.y + ((float)(i + nRand - 3) * 0.5f) };

                    auto pDust = new TMEffectDust(vec, m_fScaleV, m_nType);

                    if (pDust != nullptr)
                        g_pCurrentScene->m_pEffectContainer->AddChild(pDust);
                }
            }
            else if (m_nType == 2)
            {
                auto pParticle = new TMEffectParticle(
                    TMVector3{ m_vecPosition.x, m_fHeight, m_vecPosition.y },
                    0,
                    6,
                    0.00050000002f,
                    0xAAAAAAAA,
                    0,
                    120,
                    1.0f,
                    1,
                    TMVector3{},
                    1000);

                if (pParticle != nullptr)
                    g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);

                TMCamera* pCamera = g_pObjectManager->m_pCamera;

                if (!pCamera->m_pFocusedObject)
                {
                    m_dwLastTime = dwServerTime;
                    return 1;
                }

                float fDis = pCamera->m_pFocusedObject->m_vecPosition.DistanceFrom(m_vecPosition);

                if (fDis < 4.0f && g_pSoundManager != nullptr)
                {
                    auto pSoundData = g_pSoundManager->GetSoundData(7);

                    if (pSoundData)
                        pSoundData->Play(0, 0);
                }
            }
        }
        m_dwLastTime = dwServerTime;
    }
    return 1;
}
