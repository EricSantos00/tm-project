#include "pch.h"
#include "TMSkillHolyTouch.h"
#include "TMGlobal.h"
#include "TMShade.h"
#include "TMEffectBillBoard.h"
#include "TMEffectBillBoard2.h"
#include "TMEffectParticle.h"

TMSkillHolyTouch::TMSkillHolyTouch(TMVector3 vecPosition, int nType)
	:TMEffect()
{
	m_nType = nType;
	m_vecPosition = vecPosition;
	m_dwStartTime = g_pTimerManager->GetServerTime();
	m_fAngle = 0.0f;

	int nX[4] = { -2, 0, -1, -1 };
	int nY[4] = { 0, -1, 0, -1 };
	TMEffectBillBoard* mpBill[4];

	if (!nType)
	{
		for (int i = 0; i < 4; ++i)
		{
			mpBill[i] = new TMEffectBillBoard(54, 400 * i + 1500, 0.80000001f, 0.80000001f, 0.80000001f, 0.0f, 1, 80);

			if (mpBill[i])
			{
				mpBill[i]->m_vecPosition = { static_cast<float>(nX[i]) * 0.5f + m_vecPosition.x, m_vecPosition.y - 1.0f, static_cast<float>(nX[i]) * 0.5f + m_vecPosition.z };
				mpBill[i]->m_fScaleVelY = static_cast<float>(i) * 0.001f + 0.002f;
				mpBill[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				mpBill[i]->m_bStickGround = 1;

				g_pCurrentScene->m_pEffectContainer->AddChild(mpBill[i]);
			}
		}

		auto pEffect2 = new TMEffectBillBoard(55, 2000u, 0.0099999998f, 0.0099999998f, 0.0099999998f, 0.003f, 0);
		if (pEffect2)
		{
			pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			pEffect2->m_vecPosition = m_vecPosition;
			pEffect2->m_vecPosition.y += 0.1f;
			g_pCurrentScene->m_pEffectContainer->AddChild(pEffect2);
		}
	}

	auto pEffect20 = new TMEffectBillBoard2(2, 2000u, 2.0f, 2.0f, 2.0f, 0.0020000001f, 0);
	if (pEffect20)
	{
		pEffect20->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
		pEffect20->m_vecPosition = m_vecPosition;
		pEffect20->m_bSlope = 1;
		pEffect20->m_vecPosition.y += 0.30f;

		g_pCurrentScene->m_pEffectContainer->AddChild(pEffect20);
	}

	auto pLightMap = new TMShade(4, 7, 1.0f);
	if (pLightMap)
	{
		pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
		pLightMap->SetPosition({ m_vecPosition.x, m_vecPosition.z });
		pLightMap->m_dwLifeTime = 3000;

		g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);
	}

	int nSoundIndex = 159;
	if (!nType)
	{
		pEffect20->SetColor(0xFFAAAAAA);
		pLightMap->SetColor(0x55555555u);
	}
	else if (nType == 1)
	{
		pEffect20->SetColor(0xFFAA77FF);
		pLightMap->SetColor(0x55553388u);
		nSoundIndex = 158;
	}
	else if (nType == 2)
	{
		pEffect20->SetColor(0xFFAA0000);
		pLightMap->SetColor(0x55883333u);
	}

	if (!nType || nType == 2)
	{
		auto pParticle = new TMEffectParticle(vecPosition, 0, 10, 0.05f, 0xFFFFFFFF, 0, 56, 1.0f, 1, {}, 1000u);

		if (pParticle)
			g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);
	}

	m_dwLifeTime = 1000;

	if (g_pSoundManager && g_pSoundManager->GetSoundData(nSoundIndex))
		g_pSoundManager->GetSoundData(nSoundIndex)->Play(0, 0);
}

TMSkillHolyTouch::~TMSkillHolyTouch()
{
}

int TMSkillHolyTouch::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = g_pTimerManager->GetServerTime();

	if (!IsVisible())
		return 0;

	if (static_cast<float>(static_cast<int>(dwServerTime - m_dwStartTime)) / static_cast<float>(m_dwLifeTime) > 1.0f)
		g_pObjectManager->DeleteObject(this);

	return 1;
}
