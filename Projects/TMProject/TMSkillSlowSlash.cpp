#include "pch.h"
#include "TMSkillSlowSlash.h"
#include "TMObject.h"
#include "TMGlobal.h"
#include "TMEffectBillBoard.h"

TMSkillSlowSlash::TMSkillSlowSlash(TMVector3 vecStart, TMVector3 vecTarget, int nType, TMObject* pOwner)
	: TMEffect()
{
	m_vecStartPos = TMVector3{};
	m_vecTargetPos = TMVector3{};

	m_nType = nType;
	m_vecStartPos = vecStart;
	m_vecPosition = vecStart;
	m_vecTargetPos = vecTarget;

	m_dwStartTime = g_pTimerManager->GetServerTime();
	m_dwLifeTime = 2000;
	m_dwLastTime = 0;
	m_pOwner = pOwner;
	m_nTextureIndex = 2;

	if (!nType && g_pSoundManager)
	{
		if (g_pSoundManager->GetSoundData(167))
			g_pSoundManager->GetSoundData(167)->Play(0, 0);
	}
}

TMSkillSlowSlash::~TMSkillSlowSlash()
{
}

int TMSkillSlowSlash::FrameMove(unsigned int dwServerTime)
{
	if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELECT_SERVER)
		m_pOwner = nullptr;

	dwServerTime = g_pTimerManager->GetServerTime();

	if (!IsVisible())
		return 0;

	float fProgress = static_cast<float>(dwServerTime - m_dwStartTime) / static_cast<float>(m_dwLifeTime);

	if (fProgress > 0.5f && m_pOwner)
		m_pOwner = 0;

	if (fProgress <= 1.0f)
	{
		if (dwServerTime - m_dwLastTime > 500)
		{
			if (m_pOwner)
				m_vecPosition = { m_pOwner->m_vecPosition.x, m_pOwner->m_fHeight, m_pOwner->m_vecPosition.y };
			else if (fProgress >= 0.5f)
				m_vecPosition = m_vecTargetPos;
			else
				m_vecPosition = (m_vecStartPos * (1.0f - (fProgress * 2.0f))) + (m_vecTargetPos * fProgress * 2.0f);

			if (!g_bHideEffect)
			{
				auto nRand = rand();
				int color = 0;
				int pos = 0;
				float fSize = 0.0f;
				float fParticleH = 0.0f;

				if (m_nType)
				{
					if (m_nType == 1)
					{
						color = 0xAA5599AA;
						pos = 5;
						fParticleH = 0.60000002f;
						fSize = 0.050000001f;
					}
					else if (m_nType == 2)
					{
						color = 0xFFFFEEFF;
						pos = 5;
						fParticleH = 1.2f;
						fSize = 0.02f;
					}
				}
				else
				{
					color = 0xAAAAAA00;
					pos = 5;
					fParticleH = 0.2f;
					fSize = 0.050000001f;
				}

				auto pEffect = new TMEffectBillBoard(m_nTextureIndex, 2000u, fSize, fSize, fSize, 0.000099999997f, 1, 80);
				if (!pEffect)
					return 1;

				pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

				pEffect->m_vecStartPos = { static_cast<float>(nRand % pos + 1) * 0.1f + m_vecPosition.x, m_vecPosition.y, static_cast<float>(nRand % pos) * 0.1f + m_vecPosition.z };
				pEffect->m_vecPosition = pEffect->m_vecStartPos;
				pEffect->SetColor(color);
				pEffect->m_nParticleType = nRand % 3 + 1;
				pEffect->m_fParticleV = 1.5f;
				pEffect->m_fParticleH = fParticleH;
				pEffect->m_fCircleSpeed = 3.0f;

				g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
			}

			m_dwLastTime = dwServerTime;
		}
	}
	else
		g_pObjectManager->DeleteObject(this);

	return 1;
}
