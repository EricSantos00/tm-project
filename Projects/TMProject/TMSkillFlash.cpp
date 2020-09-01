#include "pch.h"
#include "TMSkillFlash.h"
#include "TMGlobal.h"
#include "TMEffectBillBoard.h"
#include "TMEffectBillBoard2.h"
#include "TMShade.h"

TMSkillFlash::TMSkillFlash(TMVector3 vecPosition, int nType)
	: TMEffect()
{
	m_nType = nType;
	m_vecPosition = vecPosition;
	m_dwStartTime = g_pTimerManager->GetServerTime();

	int nX[4] = { -2, 0, -1, -1 };
	int nY[4] = { 0, -1, 0, -1 };

	TMEffectBillBoard* mpBill[4] { nullptr };
	for (int i = 0; i < 4; ++i)
	{
		mpBill[i] = new TMEffectBillBoard(58, 400 * i + 1500, 0.60f, 0.80f, 0.60f, 0.0f, 1, 80);

		if (mpBill[i])
		{
			mpBill[i]->m_vecPosition = TMVector3{ (float)nX[i] * 0.5f + m_vecPosition.x, m_vecPosition.y, (float)nY[i] * 0.5f + m_vecPosition.z };
			mpBill[i]->m_fScaleVelY = (float)i * 0.001f + 0.002f;
			mpBill[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			mpBill[i]->m_bStickGround = 1;
			mpBill[i]->SetColor(-100);

			g_pCurrentScene->m_pEffectContainer->AddChild(mpBill[i]);
		}
	}

	auto pEffect2 = new TMEffectBillBoard2(93, 2000u, 0.009f, 0.009f, 0.009f, 0.002f, 0);
	if (pEffect2)
	{
		pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
		pEffect2->m_vecPosition = m_vecPosition;
		pEffect2->m_vecPosition.y += 0.1f;

		g_pCurrentScene->m_pEffectContainer->AddChild(pEffect2);
	}

	auto pEffect20 = new TMEffectBillBoard2(2, 2000u, 2.0f, 2.0f, 2.0f, 0.002f, 0);
	if (pEffect20)
	{
		pEffect20->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
		pEffect20->m_vecPosition = m_vecPosition;
		pEffect20->m_bSlope = 1;
		pEffect20->m_vecPosition.y += 0.30f;
		pEffect20->SetColor(0xFFAAAAAA);

		g_pCurrentScene->m_pEffectContainer->AddChild(pEffect20);
	}

	auto pLightMap = new TMShade(4, 7, 1.0f);

	if (pLightMap)
	{
		pLightMap->SetColor(0x55555555);
		pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
		pLightMap->SetPosition(TMVector2{ m_vecPosition.x, m_vecPosition.z });
		pLightMap->m_dwLifeTime = 3000;

		g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);
	}

	m_dwLifeTime = 1000;

	if (g_pSoundManager && g_pSoundManager->GetSoundData(159))
		g_pSoundManager->GetSoundData(159)->Play();
}

TMSkillFlash::~TMSkillFlash()
{
}

int TMSkillFlash::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = g_pTimerManager->GetServerTime();

	if (!IsVisible())
		return 0;

	if (static_cast<float>(dwServerTime - m_dwStartTime) / static_cast<float>(m_dwLifeTime) > 1.0f)
		g_pObjectManager->DeleteObject(this);

	return 1;
}
