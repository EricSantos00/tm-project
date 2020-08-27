#include "pch.h"
#include "TMEffectLevelUp.h"
#include "TMGlobal.h"
#include "TMEffectBillBoard.h"
#include "TMEffectBillBoard2.h"
#include "TMShade.h"

TMEffectLevelUp::TMEffectLevelUp(TMVector3 vecPosition, int nType)
	: TMEffect()
{
	m_nType = nType;
	m_vecPosition = vecPosition;
	m_dwStartTime = g_pTimerManager->GetServerTime();
	
	const static int nX[4] = { -2, 0, -1, -1 };
	const static int nY[4] = { 0, -1, 0, -1 };
	nType %= 3;

	const static unsigned int dwColor[3][2] = 
	{
		{0xFF558833, 0xFF335511},
		{0xFF666600, 0xFF333300},
		{0xFF665566, 0xFF332833}
	};

	const static int nIndex[3] = { 54, 122, 122 };
	const static int nIndex2[3] = { 55, 56, 56 };

	if (!g_bHideEffect)
	{
		if (nType == 1 || nType == 2)
		{
			float fSize = 0.1f;
			for (int i = 0; i < 8; ++i)
			{
				auto pParticle = new TMEffectBillBoard(56,
					300 * i + 2000,
					((float)(i % 2) * fSize) + 0.1f,
					((float)(i % 2) * fSize) + 0.1f,
					((float)(i % 2) * fSize) + 0.1f,
					0.0f,
					1,
					80);

				pParticle->m_fParticleH = 0.5f;
				pParticle->m_fParticleV = 1.5f;
				pParticle->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				pParticle->m_nParticleType = 3;

				float iZ = ((float)(rand() % 5 - 3) * 0.2f) + vecPosition.z;
				float iY = vecPosition.y + 0.3f;
				pParticle->m_vecStartPos = TMVector3(((float)(rand() % 5 - 3) * 0.2f) + vecPosition.x, iY, iZ);
				pParticle->m_vecPosition = pParticle->m_vecStartPos;

				if (nType == 1)
					pParticle->SetColor(0xFFFFFF00);
				else
					pParticle->SetColor(0xFFFFEEFF);

				g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);
			}
		}
		TMEffectBillBoard* mpBill[4]{};
		for (int j = 0; j < 4; ++j)
		{
			mpBill[j] = new TMEffectBillBoard(nIndex[nType % 3],
				400 * j + 1500,
				0.8f,
				0.8f,
				0.8f,
				0.0f,
				1,
				80);

			mpBill[j]->m_vecPosition = TMVector3(((float)nX[j] * 0.5f) + m_vecPosition.x,
				m_vecPosition.y - 1.0f,
				((float)nY[j] * 0.5f) + m_vecPosition.z);

			mpBill[j]->m_fScaleVelY = ((float)j * 0.001f) + 0.002f;
			mpBill[j]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			mpBill[j]->m_bStickGround = 1;
			mpBill[j]->SetColor(dwColor[nType][0]);
			g_pCurrentScene->m_pEffectContainer->AddChild(mpBill[j]);
		}
	}

	auto pEffect2 = new TMEffectBillBoard2(nIndex2[nType % 3],
		2000,
		0.0099999998f,
		0.0099999998f,
		0.0099999998f,
		0.0020000001f,
		0);
	pEffect2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
	pEffect2->m_vecPosition = m_vecPosition;
	pEffect2->m_vecPosition.y = pEffect2->m_vecPosition.y + 0.1f;
	pEffect2->SetColor(dwColor[nType][0]);
	g_pCurrentScene->m_pEffectContainer->AddChild(pEffect2);

	auto pEffect20 = new TMEffectBillBoard2(2, 2000, 2.0f, 2.0f, 2.0f, 0.0f, 0);
	pEffect20->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
	pEffect20->m_vecPosition = m_vecPosition;
	pEffect20->m_bSlope = 1;
	pEffect20->m_vecPosition.y = pEffect20->m_vecPosition.y + 0.30000001f;
	pEffect20->SetColor(0xFF555555);
	g_pCurrentScene->m_pEffectContainer->AddChild(pEffect20);

	auto pLightMap = new TMShade(4, 7, 1.0f);
	pLightMap->SetColor(dwColor[nType][1]);
	pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
	pLightMap->SetPosition(TMVector2(m_vecPosition.x, m_vecPosition.z));
	pLightMap->m_dwLifeTime = 3000;
	g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);

	m_dwLifeTime = 1000;
}

TMEffectLevelUp::~TMEffectLevelUp()
{
}

int TMEffectLevelUp::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = g_pTimerManager->GetServerTime();

	IsVisible();
	if (((float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime) > 1.0f)
		g_pObjectManager->DeleteObject(this);

	return 1;
}
