#include "pch.h"
#include "TMSkillLusterFurnish.h"
#include "TMGlobal.h"

TMSKillLusterFurnish::TMSKillLusterFurnish(TMVector3 vecStart, TMVector3 vecEnd)
	: TMEffect()
{
	m_vecStartPos = vecStart;
	m_vecEndPos = vecEnd;

	m_dwStartTime = g_pTimerManager->GetServerTime();
	m_dwLifeTime = 2000;
}

TMSKillLusterFurnish::~TMSKillLusterFurnish()
{
}

int TMSKillLusterFurnish::FrameMove(unsigned int dwServerTime)
{
	if (!IsVisible())
		return 0;

	float fProgress = (static_cast<float>(g_pTimerManager->GetServerTime()) - static_cast<float>(m_dwStartTime)) / static_cast<float>(m_dwLifeTime);

	if (fProgress <= 1.0f)
		m_vecPosition = (m_vecStartPos * (1.0f - fProgress)) + (m_vecEndPos * fProgress);
	else
		g_pObjectManager->DeleteObject(this);

	return 1;
}

int TMSKillLusterFurnish::Render()
{
	return 1;
}
