#include "pch.h"
#include "TMSkillHeavenDust.h"
#include "TMEffectBillBoard.h"
#include "TMGlobal.h"

TMSkillHeavensDust::TMSkillHeavensDust(TMVector3 vecPosition, int nType)
{
    m_nType = nType;
    m_vecPosition = vecPosition;
    m_dwStartTime = g_pTimerManager->GetServerTime();
    m_dwLifeTime = 1000;

    int nCount = 10;
    if (g_pDevice->m_fFPS < 10.0f)
        nCount = 2;
    else if (g_pDevice->m_fFPS < 20.0f)
        nCount = 5;
    else if (g_pDevice->m_fFPS < 30.0f)
        nCount = 8;
    
    TMEffectBillBoard* mpBill[10]{};

    for (int i = 0; i < nCount; ++i)
    {
        int nRand = rand() % 5;

        mpBill[i] = new TMEffectBillBoard(
            0,
            400 * i + 1500,
            ((float)nRand * 0.5f) + 0.80000001f,
            ((float)nRand * 0.5f) + 0.80000001f,
            ((float)nRand * 0.5f) + 0.80000001f,
            0.001f,
            1,
            80);

        if (mpBill[i] != nullptr)
        {
            mpBill[i]->m_vecPosition = { ((float)(rand() % 10 - 5) * 0.2f) + m_vecPosition.x, m_vecPosition.y, ((float)(rand() % 10 - 5) * 0.2f) + m_vecPosition.z };
            mpBill[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            mpBill[i]->m_bStickGround = 1;
            mpBill[i]->SetColor(0xFFAAEEFF);
            g_pCurrentScene->m_pEffectContainer->AddChild(mpBill[i]);
        }
    }

    if (g_pSoundManager != nullptr)
    {
        auto pSoundData = g_pSoundManager->GetSoundData(153);

        if (pSoundData)
            pSoundData->Play(0, 0);
    }
}

TMSkillHeavensDust::~TMSkillHeavensDust()
{
}

int TMSkillHeavensDust::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();
    IsVisible();

    if (((float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime) > 1.0f)
        g_pObjectManager->DeleteObject(this);

    return 1;
}
