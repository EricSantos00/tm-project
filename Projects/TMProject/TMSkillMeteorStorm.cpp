#include "pch.h"
#include "TMSkillMeteorStorm.h"
#include "TMObject.h"
#include "TMShade.h"
#include "TMEffectBillBoard.h"
#include "TMEffectBillBoard2.h"
#include "TMEffectParticle.h"
#include "TMSkillExplosion2.h"
#include "TMGlobal.h"
#include "TMShade.h"

TMSkillMeteorStorm::TMSkillMeteorStorm(TMVector3 vecStart, TMVector3 vecTarget, int nLevel, TMObject* pOwner)
	: TMEffect()
{
	m_vecStartPos = TMVector3{};
	m_vecTargetPos = TMVector3{};

	m_fAngle = 0.0f;
	m_fProgress = 0.0f;
	m_bPlaySound = 0;

	if (!vecStart.x && !vecStart.y && !vecStart.z)
	{
		vecStart.x = vecTarget.x + 3.0f;
		vecStart.z = vecTarget.z - 3.0f;
		vecStart.y = vecTarget.y + 5.0f;
	}

	if (nLevel == 9)
		vecStart = vecTarget;

	m_vecStartPos = vecStart;
	m_vecPosition = vecStart;
	m_vecTargetPos = vecTarget;

	m_nLevel = nLevel;
	m_dwStartTime = g_pTimerManager->GetServerTime();
	m_pOwner = pOwner;
	m_pCenterLight = 0;
	m_pCenterLight2 = 0;
	m_pCenterFlare = 0;
	m_pLightMap = 0;

	auto vecD = vecTarget - vecStart;
	m_fLength = vecD.Length();

	if (m_nLevel)
	{
		switch (m_nLevel)
		{
		case 1:
		{
			int nRand = 1; // this is 0x86C050... maybe a scoped static var but never changes... sooo...
			nRand %= 5; // yes... 

			m_dwLifeTime = 30 * nRand * static_cast<unsigned int>(m_fLength); // yes... we use the value that never changes
		}
		break;
		case 2:
			m_dwLifeTime = 100 * static_cast<unsigned int>(m_fLength);
			break;
		case 3:
			m_dwLifeTime = 50 * static_cast<unsigned int>(m_fLength);
			break;
		case 4:
			m_dwLifeTime = 100 * static_cast<unsigned int>(m_fLength);

			if (g_pSoundManager && g_pSoundManager->GetSoundData(160))
				g_pSoundManager->GetSoundData(160)->Play(0, 0);

			break;
		case 5:
			m_dwLifeTime = 100 * static_cast<unsigned int>(m_fLength);
			break;
		case 6:
			m_dwLifeTime = 100 * static_cast<unsigned int>(m_fLength);
			m_pLightMap = new TMShade(1, 7, 1.0f);

			if (m_pLightMap)
			{
				m_pLightMap->SetColor(0xFFFF7711);
				m_pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

				g_pCurrentScene->m_pEffectContainer->AddChild(m_pLightMap);
			}

			if (g_pSoundManager && g_pSoundManager->GetSoundData(160))
				g_pSoundManager->GetSoundData(160)->Play(0, 0);
			break;
		}
	}
	else
	{
		m_dwLifeTime = 100 * static_cast<unsigned int>(m_fLength);
		if (g_pSoundManager && g_pSoundManager->GetSoundData(160))
			g_pSoundManager->GetSoundData(160)->Play(0, 0);
	}

	if (!m_dwLifeTime)
		m_dwLifeTime = 1;

	if (m_dwLifeTime > 5000)
		m_dwLifeTime = 5000;

	if (m_nLevel && m_nLevel != 4 && m_nLevel == 6)
	{
		m_pCenterLight = new TMEffectBillBoard(56, 0, 2.5f, 2.5f, 2.5f, 0.0f, 1, 80);
		if (m_pCenterLight)
		{
			m_pCenterLight->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			m_pCenterLight->m_nFade = 0;
			m_pCenterLight->m_vecPosition = m_vecPosition;
			m_pCenterLight->m_vecPosition.y -= 0.5f;
			m_pCenterLight->SetColor(0xFFFF7711);

			g_pCurrentScene->m_pEffectContainer->AddChild(m_pCenterLight);
		}

		m_pCenterLight2 = new TMEffectBillBoard(2, 0, 1.5f, 1.5f, 1.5f, 0.0f, 1, 80);
		if (m_pCenterLight2)
		{
			m_pCenterLight2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			m_pCenterLight2->m_nFade = 0;
			m_pCenterLight2->m_vecPosition = m_vecPosition;
			m_pCenterLight2->m_vecPosition.y -= 0.5f;
			g_pCurrentScene->m_pEffectContainer->AddChild(m_pCenterLight2);
		}

		m_pCenterFlare = new TMEffectBillBoard(60, 0, 2.5f, 2.0f, 2.5f, 0.0f, 1, 80);
		if (m_pCenterFlare)
		{
			m_pCenterFlare->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			m_pCenterFlare->m_nFade = 0;
			m_pCenterFlare->m_vecPosition = m_vecPosition;
			m_pCenterFlare->m_vecPosition.y -= 0.5f;
			m_pCenterFlare->SetColor(0xFFFF7711);

			g_pCurrentScene->m_pEffectContainer->AddChild(m_pCenterFlare);
		}
	}
}

TMSkillMeteorStorm::~TMSkillMeteorStorm()
{
	g_pObjectManager->DeleteObject(m_pCenterLight);
	g_pObjectManager->DeleteObject(m_pCenterLight2);
	g_pObjectManager->DeleteObject(m_pCenterFlare);
	g_pObjectManager->DeleteObject(m_pLightMap);

	TMEffectBillBoard* pEffect = nullptr;

	if (!m_nLevel || m_nLevel == 9)
		pEffect = new TMEffectBillBoard(33, 999, 3.5f, -1.5f, 3.5f, 0.004f, 9, 111);

	switch (m_nLevel)
	{
	case 10:
		pEffect = new TMEffectBillBoard(33, 999, 3.5f, -1.5f, 3.5f, 0.004f, 9, 111);
		break;
	case 1:
		pEffect = new TMEffectBillBoard(71, 888, 0.5f, 0.5f, 0.5f, 0.0f, 8, 111);
		break;
	case 4:
		pEffect = new TMEffectBillBoard(33, 999, 1.5f, 1.5f, 1.5f, 0.004f, 9, 111);
		break;
	case 6:
		pEffect = new TMEffectBillBoard(71, 888, 5.0f, 5.0f, 5.0f, 0.0f, 9, 90);
		break;
	}

	if (pEffect)
	{
		pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
		pEffect->m_nFade = 0;
		pEffect->m_vecPosition = m_vecTargetPos;
		pEffect->m_vecPosition.y = m_vecPosition.y - 1.5f;
		g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
	}

	int nSoundIndex = 152;
	TMShade* pLightMap = nullptr;
	TMEffectBillBoard2* pEffect2 = nullptr;

	if (!m_nLevel || m_nLevel == 9)
	{
		pEffect2 = new TMEffectBillBoard2(8, 500u, 0.0099999998f, 0.00999999978f, 0.0099999998f, 0.0099999998f, 0);

		if (pEffect2)
		{
			pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			pEffect2->m_vecPosition = m_vecTargetPos;
			pEffect2->m_vecPosition.y -= 0.60000002f;

			g_pCurrentScene->m_pEffectContainer->AddChild(pEffect2);
		}

		pLightMap = new TMShade(4, 7, 1.0f);

		if (pLightMap)
			pLightMap->SetColor(0xFFFF7711);
	}

	switch (m_nLevel)
	{
	case 10:
	{
		TMEffectBillBoard2* pChild = new TMEffectBillBoard2(8, 500, 1.0f, 1.0f, 1.0f, 0.0099999998f, 0);

		if (pChild)
		{
			pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			pChild->m_vecPosition = m_vecTargetPos;
			pChild->m_vecPosition.y -= 0.60000002f;

			g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
		}

		pLightMap = new TMShade(4, 7, 1.0f);
		if (pLightMap)
			pLightMap->SetColor(0xFFFF7711);
	}
	break;
	case 1:
		nSoundIndex = 154;

		pLightMap = new TMShade(2, 7, 1.0f);
		if (pLightMap)
			pLightMap->SetColor(0xFF3333FF);
		break;
	case 3:
		pLightMap = new TMShade(2, 7, 1.0f);
		if (pLightMap)
			pLightMap->SetColor(0xFFFF7722);
		break;
	case 4:
	{
		auto pChild = new TMEffectBillBoard2(8, 500u, 0.0099999998f, 0.0099999998f, 0.0099999998f, 0.0099999998f, 0); // v204

		if (pChild)
		{
			pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			pChild->m_vecPosition = m_vecTargetPos;
			pChild->m_vecPosition.y -= 0.60000002f;
			pChild->SetColor(0xFFFF7711);

			g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
		}

		pLightMap = new TMShade(2, 7, 1.0f);
		if (pLightMap)
			pLightMap->SetColor(0xFFFF7711);
	}
	break;
	case 6:
	{
		auto pChild = new TMEffectBillBoard2(8, 1000u, 0.0099999998f, 0.0099999998f, 0.0099999998f, 0.0060000001, 0);

		if (pChild)
		{
			pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			pChild->m_vecPosition = m_vecTargetPos;
			pChild->m_vecPosition.y -= 0.60000002f;
			pChild->SetColor(0xFFFF7711);

			g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
		}

		pLightMap = new TMShade(2, 7, 1.0f);
		if (pLightMap)
			pLightMap->SetColor(0xFFFF7711);
	}
	break;
	}

	if (pLightMap)
	{
		pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
		pLightMap->SetPosition({ m_vecTargetPos.x, m_vecTargetPos.z });
		pLightMap->m_dwLifeTime = 1500;

		g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);
	}

	if (m_nLevel == 2)
	{
		auto pParticle4 = new TMEffectParticle(m_vecTargetPos, 4, 12, 3.0f, 0xFFFFAA00, 0, 56, 1.0f, 1, {}, 1000u); 

		if (pParticle4)
			g_pCurrentScene->m_pEffectContainer->AddChild(pParticle4);

		unsigned int dwColor = 0x44444444;
		auto pExplosion4 = new TMSkillExplosion2(m_vecTargetPos, 0, 3.0f, 210u, dwColor);
		if (pExplosion4)
			g_pCurrentScene->m_pEffectContainer->AddChild(pExplosion4);

		auto pBill4 = new TMEffectBillBoard(59, 2500u, 1.2f, 1.2f, 1.2f, 0.003f, 1, 80);
		if (pBill4)
		{

		}
	}
}

int TMSkillMeteorStorm::Render()
{
	return 0;
}

int TMSkillMeteorStorm::IsVisible()
{
	return 0;
}

int TMSkillMeteorStorm::FrameMove(unsigned int dwServerTime)
{
	return 0;
}
