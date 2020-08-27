#include "pch.h"
#include "TMShade.h"
#include "TMObject.h"
#include "TMEffectBillBoard3.h"
#include "TMEffectSpark.h"
#include "TMGlobal.h"

TMEffectSpark::TMEffectSpark(TMVector3 vecStart, TMObject* pTarget, TMVector3 vecEnd, unsigned int dwColor, unsigned int dwColor2, unsigned int dwLifeTime, float fWidth, int nSparkCount, float fProgress) :
	TMEffect(),
	m_vecStartPos{ vecStart },
	m_vecEndPos{ vecEnd }
{
	m_dwCreateTime = g_pTimerManager->GetServerTime();
	m_pOwner = pTarget;
	m_fRange = 1.0f;
	m_fWidth = fWidth;
	m_dwColor = dwColor;
	m_dwColor2 = dwColor2;
	if (m_nSparkCount <= 5)
		m_nSparkCount = nSparkCount;
	else
		m_nSparkCount = 5;

	m_vecPosition = vecStart;

	if (m_pOwner)
		m_vecEndPos = TMVector3{ m_pOwner->m_vecPosition.x, m_pOwner->m_fHeight + 1.0f, m_pOwner->m_vecPosition.y };

	m_dwLifeTime = dwLifeTime - 100;

	TMVector3 vecTemp1{ m_vecStartPos };

	TMVector3 vecTemp2
	{
		((1.0f - fProgress) * m_vecStartPos.x) + (m_vecEndPos.x * fProgress),
		((1.0f - fProgress) * m_vecStartPos.y) + (m_vecEndPos.y * fProgress),
		((1.0f - fProgress) * m_vecStartPos.z) + (m_vecEndPos.z * fProgress)
	};

	for (int i = 0; i < m_nSparkCount; ++i)
	{
		m_pSpark[i] = new TMEffectBillBoard3(vecTemp1, vecTemp2, 128, m_dwColor, dwLifeTime, 0.80000001f * m_fWidth, 0.80000001f * m_fWidth);

		if (m_pSpark[i])
		{
			m_pSpark[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			m_pSpark[i]->m_vertex2[0].tv = 1;

			vecTemp1 = vecTemp2;

			float fProgress = (float)(i + 1) / (float)m_nSparkCount;

			vecTemp2 = TMVector3{ 
				((1.0f - fProgress) * m_vecStartPos.x) + (m_vecEndPos.x * fProgress),
				((1.0f - fProgress) * m_vecStartPos.y) + (m_vecEndPos.y * fProgress),
				((1.0f - fProgress) * m_vecStartPos.z) + (m_vecEndPos.z * fProgress)};

			g_pCurrentScene->m_pEffectContainer->AddChild(m_pSpark[i]);

			if (pTarget)
			{
				m_pShade[i] = new TMShade(3, 7, 1.0f);

				if (m_pShade[i])
				{
					m_pShade[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
					m_pShade[i]->SetColor(m_dwColor2);
					
					m_pShade[i]->SetPosition(TMVector2{ vecTemp1.x, vecTemp1.z });
					m_pShade[i]->m_dwLifeTime = dwLifeTime;

					g_pCurrentScene->m_pEffectContainer->AddChild(m_pShade[i]);
				}
			}
		}
	}

	if (pTarget)
	{
		if (g_pSoundManager)
		{
			auto pSoundData = g_pSoundManager->GetSoundData(178);
			
			if (pSoundData && !pSoundData->IsSoundPlaying())
				pSoundData->Play(0, 0);
		}
	}
}

TMEffectSpark::~TMEffectSpark()
{
}

int TMEffectSpark::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = g_pTimerManager->GetServerTime();
	IsVisible();

	if (m_dwLifeTime && (dwServerTime - m_dwCreateTime) > m_dwLifeTime)
	{
		m_bVisible = 0;
		g_pObjectManager->DeleteObject(this);
	}
	else
	{
		TMVector3 vecTemp1 = m_vecStartPos;

		if (m_pOwner)
			m_vecEndPos = TMVector3{ m_pOwner->m_vecPosition.x, m_pOwner->m_fHeight + 1.0f, m_pOwner->m_vecPosition.y };

		for (int i = 0; i < m_nSparkCount; ++i)
		{
			float fProgress = (float)(i + 1) / (float)m_nSparkCount;

			TMVector3 vecTemp2 = TMVector3{
				((1.0f - fProgress) * m_vecStartPos.x) + (m_vecEndPos.x * fProgress),
				((1.0f - fProgress) * m_vecStartPos.y) + (m_vecEndPos.y * fProgress),
				((1.0f - fProgress) * m_vecStartPos.z) + (m_vecEndPos.z * fProgress)};

			if (i < m_nSparkCount - 1)
			{
				float fGrade = (float)(m_nSparkCount - i) * 0.15000001f;
				if (fGrade > 0.30000001f)
					fGrade = 0.5f;

				float fRand1 = ((float)(rand() % 9 - 5) * fGrade) * m_fRange;
				float fRand2 = ((float)(rand() % 9 - 5) * fGrade) * m_fRange;
				float fRand3 = ((float)(rand() % 9 - 5) * fGrade) * m_fRange;

				vecTemp2 = vecTemp2 + TMVector3{ fRand1, fRand2, fRand3 };
			}

			if (m_pSpark[i])
			{
				m_pSpark[i]->SetPosition(vecTemp1, vecTemp2);

				if (m_pOwner)
				{
					if (m_pShade[i])
						m_pShade[i]->SetPosition(TMVector2{ (vecTemp1.x + vecTemp2.x) / 2.0f, (vecTemp1.z + vecTemp2.z) / 2.0f });
				}
			}
			vecTemp1 = vecTemp2;
		}
	}
	return 1;
}

int TMEffectSpark::SetLifeTime(unsigned int dwLifeTime)
{
	m_dwLifeTime = dwLifeTime;

	for (int i = 0; i < m_nSparkCount; ++i)
	{
		if (m_pSpark[i])
			m_pSpark[i]->m_dwCreateTime = dwLifeTime;
	}
	return 1;
}
