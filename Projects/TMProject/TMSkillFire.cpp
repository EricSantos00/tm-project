#include "pch.h"
#include "TMSkillFire.h"
#include "TMEffectBillBoard.h"
#include "TMObject.h"
#include "TMShade.h"
#include "TMGlobal.h"

TMSkillFire::TMSkillFire(TMVector3 vecPosition, int nType, TMObject* pOwner, unsigned int dwColor, unsigned int dwColor2)
	: TMEffect()
{
	m_nType = nType;
	m_vecPosition = vecPosition;
	m_dwStartTime = g_pTimerManager->GetServerTime();
	m_dwLifeTime = 2400;
	m_dwLastTime = 0;
	m_pOwner = pOwner;
	m_dwColor = dwColor;
	m_dwColor2 = dwColor2;
	
	m_fAngle = 0.0f;

	if (m_nType == 2 || m_nType == 3 || m_nType == 5 || m_nType == 6)
	{
		m_dwLifeTime = 800;
		m_pLightMap = new TMShade(2, 7, 1.0f);

		if (m_pLightMap)
		{
			m_pLightMap->SetColor(m_dwColor2);
			m_pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			m_pLightMap->SetPosition({ m_vecPosition.x, m_vecPosition.z });
			m_pLightMap->m_dwLifeTime = m_dwLifeTime + 1000;
			g_pCurrentScene->m_pEffectContainer->AddChild(m_pLightMap);
		}
	}
	else if (m_nType == 7)
		m_dwLifeTime = 1000;
	else if (m_nType == 8)
		m_dwLifeTime = 100;
	else
	{
		m_pLightMap = new TMShade(4, 7, 1.0f);
		if (m_pLightMap)
		{
			m_pLightMap->SetColor(m_dwColor2);
			m_pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			m_pLightMap->SetPosition({ m_vecPosition.x, m_vecPosition.z });
			m_pLightMap->m_dwLifeTime = m_dwLifeTime + 1000;

			g_pCurrentScene->m_pEffectContainer->AddChild(m_pLightMap);
		}
	}

	if (g_pSoundManager && g_pSoundManager->GetSoundData(155))
		g_pSoundManager->GetSoundData(155)->Play(0, 0);
}

TMSkillFire::~TMSkillFire()
{
}

int TMSkillFire::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = g_pTimerManager->GetServerTime();

	if (!IsVisible())
		return 0;

	float fProgress = static_cast<float>(dwServerTime - m_dwStartTime) / static_cast<float>(m_dwLifeTime);
	if (fProgress < 0.0099999998f)
		return 1;

	if (fProgress > 0.5f && m_pOwner)
		m_pOwner = nullptr;

	if (fProgress <= 1.0f)
	{
		unsigned int dwTime = 100;
		if (m_nType == 1)
			dwTime = 300;
		if (m_nType == 2 || m_nType == 5)
			dwTime = 180;
		if (m_nType == 3 || m_nType == 6)
			dwTime = 10000;
		if (m_nType == 7)
			dwTime = 1000;
		if (m_nType == 8)
			dwTime = 100;

		if (g_pDevice->m_fFPS < 10.0)
			dwTime *= 6;
		else if (g_pDevice->m_fFPS < 20.0)
			dwTime *= 5;
		else if (g_pDevice->m_fFPS < 30.0)
			dwTime *= 3;

		if (dwServerTime - m_dwLastTime > dwTime)
		{
			if (m_pOwner)
			{
				m_vecPosition.x = m_pOwner->m_vecPosition.x;
				m_vecPosition.z = m_pOwner->m_vecPosition.y;
				m_vecPosition.y = m_pOwner->m_fHeight;

				if (m_pLightMap)
					m_pLightMap->SetPosition({ m_vecPosition.x, m_vecPosition.z });
			}

			if (!g_bHideEffect)
			{
				int nRand = rand();
				float fRand = static_cast<float>(nRand);
				TMEffectBillBoard* pEffect = nullptr;

				if (m_nType)
				{
					switch (m_nType)
					{
					case 1:
						pEffect = new TMEffectBillBoard(33, 1000u, 1.2f, 1.0f, 1.2f, 0.002f, 9, 111);
						break;
					case 2:
						pEffect = new TMEffectBillBoard(33, 1000u, 0.40000001f, 0.40000001f, 0.40000001f, 0.001f, 9, 111);
						break;
					case 3:
						pEffect = new TMEffectBillBoard(33, 1000u, 0.60000002f, 0.60000002f, 0.60000002f, 0.001f, 9, 111);
						break;
					case 4:
						pEffect = new TMEffectBillBoard(71, 1000u, 0.60000002f, 0.60000002f, 0.60000002f, 0.001f, 8, 111);
						break;
					case 5:
						pEffect = new TMEffectBillBoard(71, 1000u, 0.40000001f, 0.40000001f, 0.40000001f, 0.001f, 8, 111);
						break;
					case 6:
						pEffect = new TMEffectBillBoard(71, 1000u, 0.40000001f, 0.40000001f, 0.40000001f, 0.001f, 8, 111);
						break;
					case 7:
						pEffect = new TMEffectBillBoard(2, 1000u, 0.80000001f, 0.80000001f, 0.80000001f, 0.001f, 1, 1);
						break;
					case 8:
						pEffect = new TMEffectBillBoard(33, 1000u, 1.2f, 1.0f, 1.2f, 0.0020000001f, 9, 111);
						break;
					}
				}
				else
					pEffect = new TMEffectBillBoard(33, 500u, 0.69999999f, 0.69999999f, 0.69999999f, 0.001f, 9, 11);

				if (!pEffect)
					return 0;

				pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				pEffect->m_vecStartPos = { static_cast<float>(nRand % 5) * 0.0099999998f + m_vecPosition.x, m_vecPosition.y, static_cast<float>(nRand % 5) * 0.0099999998f + m_vecPosition.z };
				pEffect->m_vecPosition = pEffect->m_vecStartPos;
				pEffect->m_nParticleType = 1;

				if (m_nType)
				{
					switch (m_nType)
					{
					case 1:
						pEffect->m_fParticleV = 4.0f;
						break;
					case 2:
						pEffect->m_fParticleV = 4.0f;
						break;
					case 3:
						pEffect->m_fParticleV = 1.7f;
						break;
					case 4:
						pEffect->m_fParticleV = 1.7f;
						pEffect->SetColor(0x3366u);
						break;
					case 5:
						pEffect->m_fParticleV = 4.0f;
						pEffect->SetColor(0x6688u);
						break;
					case 6:
						pEffect->m_fParticleV = 1.7f;
						pEffect->SetColor(0x3366u);
						break;
					case 7:
						pEffect->m_fParticleV = 1.7f;
						pEffect->SetColor(0xFFFFFFFF);
						break;
					}
				}
				else
					pEffect->m_fParticleV = 3.0f;

				pEffect->SetColor(m_dwColor);
				g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
			}

			m_dwLastTime = dwServerTime;
		}
	}
	else
		g_pObjectManager->DeleteObject(this);

	return 1;
}
