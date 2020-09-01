#include "pch.h"
#include "TMSkillPoison.h"
#include "TMGlobal.h"
#include "TMEffectBillBoard.h"
#include "TMUtil.h"

TMSkillPoison::TMSkillPoison(TMVector3 vecPosition, unsigned int dwColor, int nCount, int bSound, int nType)
	: TMEffect()
{
	m_nType = 0;
	m_vecPosition = vecPosition;
	m_dwStartTime = g_pTimerManager->GetServerTime();
	m_dwLifeTime = 3000;

	if (!g_bHideEffect)
	{
		for (int i = 0; i < nCount; ++i)
		{
			TMEffectBillBoard* mpBill = nullptr;

			if (nType == 0)
			{
				int nRand = rand() % 5;
				mpBill = new TMEffectBillBoard(0, 400 * i + 1500, ((float)nRand * 0.1f) + 0.2f, ((float)nRand * 0.1f) + 0.2f, ((float)nRand * 0.1f) + 0.2f,
					0.001f,	1, 80);
			}
			else
			{
				int nRand = rand() % 5 + 5;
				mpBill = new TMEffectBillBoard(0, 400 * i + 1500, ((float)nRand * 4.0f) + 1.0f, ((float)nRand * 4.0f) + 1.0f, ((float)nRand * 4.0f) + 1.0f, 
					0.001f,	1, 80);
			}

			float iZ = ((float)(rand() % 10 - 5) * 0.1f) + m_vecPosition.z;
			float iY = m_vecPosition.y;

			int nRand = rand();
			mpBill->m_vecPosition = TMVector3(((float)(nRand % 10 - 5) * 0.1f) + m_vecPosition.x, iY, iZ);
			mpBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			mpBill->m_bStickGround = 1;
			mpBill->SetColor(dwColor);
			g_pCurrentScene->m_pEffectContainer->AddChild(mpBill);
		}
	}

	if (bSound)
	{
		GetSoundAndPlay(156, 0, 0);
	}
}

TMSkillPoison::~TMSkillPoison()
{
}

int TMSkillPoison::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = g_pTimerManager->GetServerTime();
	if (!IsVisible())
		return 0;

	if (((float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime) > 1.0f)
		g_pObjectManager->DeleteObject(this);

	return 1;
}
