#include "pch.h"
#include "TMSkillBash.h"
#include "TMSkillExplosion2.h"
#include "TMSkillSpeedUp.h"
#include "TMGlobal.h"

TMSkillBash::TMSkillBash(TMVector3 vecPosition, int nType)
{
	m_vecPosition = vecPosition;
	m_dwStartTime = g_pTimerManager->GetServerTime();
	m_dwLifeTime = 700;
	m_dwLastTime = 0;
	m_nType = nType;
}

TMSkillBash::~TMSkillBash()
{
	auto pSkillExplosion2 = new TMSkillExplosion2(m_vecPosition, 0, 0.5f, 250, 0xFFFFFFFF);

	if (pSkillExplosion2 != nullptr)
		g_pCurrentScene->m_pEffectContainer->AddChild(pSkillExplosion2);
}

int TMSkillBash::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();

    if (!IsVisible())
        return 0;

    float fProgress = (float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime;

    if (!g_pCurrentScene)
        return 0;

    if (fProgress > 1.0f)
    {
        g_pObjectManager->DeleteObject(this);
    }
    else if ((dwServerTime - m_dwLastTime) > 250)
    {
        TMVector3 vec
        {
            (((float)(rand() % 3) - (fProgress * 10.0f)) * 0.2f) + m_vecPosition.x,
            (((float)(rand() % 3) - (fProgress * 10.0f)) * 0.2f) + m_vecPosition.z,
            0.0f
        };

        auto pSkillSpeedUp = new TMSkillSpeedUp(vec, 1);

        if (pSkillSpeedUp != nullptr)
            g_pCurrentScene->m_pEffectContainer->AddChild(pSkillSpeedUp);

        m_dwLastTime = dwServerTime;
    }
    return 1;
}
