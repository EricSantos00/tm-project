#include "pch.h"
#include "TMSkillHeal.h"
#include "TMObject.h"
#include "TMGlobal.h"
#include "TMEffectParticle.h"
#include "TMShade.h"

TMSkillHeal::TMSkillHeal(TMVector3 vecPosition, int nType, TMObject* pOwner) :
	TMEffect()
{
	m_nType = nType;
	m_vecPosition = vecPosition;
	m_dwStartTime = g_pTimerManager->GetServerTime();
	m_dwLifeTime = 2000;
	m_dwLastTime = 0;
	m_pOwner = pOwner;

	int nCount = 12;
	if (g_pDevice->m_fFPS < 10.0f)
		nCount = 2;
	else if (g_pDevice->m_fFPS < 20.0f)
		nCount = 5;
	else if (g_pDevice->m_fFPS < 30.0f)
		nCount = 8;

	if (!g_bHideEffect)
	{
		auto pParticle = new TMEffectParticle(vecPosition, 0, nCount, 0.1f, 0xFF77AAFF, 0, 56, 1.0f, 1, TMVector3{}, 1000u);

		if (pParticle)
			g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);
	}

	auto pLightMap = new TMShade(4, 7, 1.0f);

	if (pLightMap)
	{
		pLightMap->SetColor(0x115588);
		pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

		pLightMap->SetPosition(TMVector2{ m_vecPosition.x, m_vecPosition.z });
		pLightMap->m_dwLifeTime = 3000;

		g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);
	}

	if (g_pSoundManager)
	{
		if (g_pSoundManager->GetSoundData(158))
		{
			g_pSoundManager->GetSoundData(158)->Play();
		}
	}
}

TMSkillHeal::~TMSkillHeal()
{
}

int TMSkillHeal::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = g_pTimerManager->GetServerTime();
	if (!IsVisible())
		return 0;

	if (static_cast<float>(dwServerTime - m_dwStartTime) / static_cast<float>(m_dwLifeTime) > 1.0f)
		g_pObjectManager->DeleteObject(this);

	return 1;
}
