#include "pch.h"
#include "TMSkillTownPortal.h"
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
	return 0;
}

int TMSkillTownPortal::IsVisible()
{
	return 0;
}

int TMSkillTownPortal::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMSkillTownPortal::SetColor(unsigned int dwColor)
{
}
