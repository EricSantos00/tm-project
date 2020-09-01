#include "pch.h"
#include "TMSkillThunderBolt.h"
#include "TMGlobal.h"
#include "TMEffectBillBoard.h"
#include "TMSkillPoison.h"
#include "TMShade.h"
#include "TMUtil.h"

TMSkillThunderBolt::TMSkillThunderBolt(TMVector3 vecPosition, int nType) 
	: TMEffect()
{
	m_nType = nType;
	m_vecPosition = vecPosition;
	m_dwStartTime = g_pTimerManager->GetServerTime();
	m_dwLifeTime = 2000;

	const static unsigned int dwCol[3][3] = 
	{
		{0xFF77AAAA, 0xFF7777AA, 0xFF7777FF},
		{0xFFFFAA00, 0xFFFFAA00, 0xFFFFAA00},
		{0xFF00FF77, 0xFF00FFAA, 0xFF00FFAA}
	};

	auto pThunder = new TMEffectBillBoard(45, m_dwLifeTime, 0.55f, 10.0f, 1.55f, 0.0f, 6, 80);
	pThunder->m_vecStartPos = pThunder->m_vecPosition = TMVector3(m_vecPosition.x, m_vecPosition.y - 1.0f, m_vecPosition.z);
	pThunder->m_nFade = 0;
	pThunder->m_bStickGround = 1;
	pThunder->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
	pThunder->SetColor(dwCol[m_nType][0]);

	auto pThunder2 = new TMEffectBillBoard(45, m_dwLifeTime, 0.55f, 10.0f, 0.55f, 0.0f, 6, 80);
	pThunder2->m_vecStartPos = pThunder->m_vecPosition = TMVector3(m_vecPosition.x, m_vecPosition.y - 1.0f, m_vecPosition.z);
	pThunder2->m_nFade = 0;
	pThunder2->m_bStickGround = 1;
	pThunder2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
	pThunder2->SetColor(dwCol[m_nType][1]);
	g_pCurrentScene->m_pEffectContainer->AddChild(pThunder);
	g_pCurrentScene->m_pEffectContainer->AddChild(pThunder2);

	auto pPoison = new TMSkillPoison(m_vecPosition, dwCol[m_nType][0], 10, 1, 0);
	g_pCurrentScene->m_pEffectContainer->AddChild(pPoison);

	auto pLightMap = new TMShade(4, 7, 1.0f);
	pLightMap->SetColor(dwCol[m_nType][2]);
	pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
	pLightMap->SetPosition(TMVector2(m_vecPosition.x, m_vecPosition.z));
	pLightMap->m_dwLifeTime = m_dwLifeTime;
	g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);

	GetSoundAndPlay(152, 0, 0);
}

TMSkillThunderBolt::~TMSkillThunderBolt()
{
}

int TMSkillThunderBolt::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = g_pTimerManager->GetServerTime();
	if (!IsVisible())
		return 0;

	if (((float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime) > 1.0f)
		g_pObjectManager->DeleteObject(this);

	return 1;
}
