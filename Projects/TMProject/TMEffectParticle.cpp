#include "pch.h"
#include "TMEffectParticle.h"
#include "TMEffectBillBoard.h"
#include "TMGlobal.h"

TMEffectParticle::TMEffectParticle(TMVector3 vecPosition, int nType, int nCount, float fSize, unsigned int dwColor, int bRand, int nTextureIndex, float fRadius, int bBright, TMVector3 vecDir, unsigned int dwLifeTime)
{
	m_dwLifeTime = dwLifeTime;
	m_fAngle = 0.0f;
	m_vecPosition = vecPosition;
	m_nType = nType;
	m_dwStartTime = g_pTimerManager->GetServerTime();

	for (int i = 0; i < nCount; ++i)
	{
		unsigned int dwTime = 300 * i + 2000;

		if (m_nType == 4)
			dwTime = 300 * i + 1000;

		auto pParticle = new TMEffectBillBoard(
			nTextureIndex,
			dwTime,
			((float)(i % 2) * fSize) + 0.1f,
			((float)(i % 2) * fSize) + 0.1f,
			((float)(i % 2) * fSize) + 0.1f,
			0.0f,
			1,
			80);

		if (pParticle)
		{
			pParticle->m_fParticleH = ((float)(i % 3) * 0.050000001f) + 0.1f;
			pParticle->m_efAlphaType = static_cast<EEFFECT_ALPHATYPE>(bBright == 1);

			switch (m_nType)
			{
			case 0:
			case 1:
				pParticle->m_nParticleType = nType + i % 2 + 1;
				break;
			case 2:
				pParticle->m_nParticleType = 1;
				pParticle->m_fParticleV = -3.0f;
				break;
			case 3:
				pParticle->m_nParticleType = 1;
				pParticle->m_fParticleV = 3.0f;
				break;
			case 4:
				pParticle->m_nParticleType = 2;
				pParticle->m_fParticleV = 5.0f;
				break;
			case 5:
				pParticle->m_nFade = 4;
				pParticle->m_nParticleType = 13;
				D3DXVECTOR3 vecDir1{};
				D3DXMATRIX matRot{};
				D3DXMatrixRotationY(&matRot, (float)(rand() % 300 + 700) * 0.001f);
				D3DXVec3TransformCoord(&vecDir1, (D3DXVECTOR3*)&vecDir, &matRot);
				D3DXMatrixRotationAxis(&matRot, (D3DXVECTOR3*)&vecDir, (((float)(rand() % 365) / 365.0f) * 3.1415927f) * 2.0f);
				D3DXVec3TransformCoord((D3DXVECTOR3*)&pParticle->m_vecDir, &vecDir1, &matRot);
				D3DXVec3Normalize((D3DXVECTOR3*)&pParticle->m_vecDir, (D3DXVECTOR3*)&pParticle->m_vecDir);
				pParticle->m_fVel = (float)(rand() % 1000) * 0.001f;
				pParticle->m_dwLifeTime = dwLifeTime;
				break;
			}

			pParticle->m_vecStartPos = TMVector3{
				(((float)(rand() % 5 - 3) * 0.30000001f) * fRadius) + vecPosition.x,
				((float)(rand() % 5 - 3) * 0.1f) + vecPosition.y,
				(((float)(rand() % 5 - 3) * 0.30000001f) * fRadius) + vecPosition.z
			};

			pParticle->m_vecPosition = pParticle->m_vecStartPos;

			if (m_nType == 5)
			{
				pParticle->m_vecStartPos = TMVector3{ vecPosition.x, vecPosition.y, vecPosition.z };
				pParticle->m_vecPosition = pParticle->m_vecStartPos;
			}

			if (bRand)
			{
				unsigned int dwColors[7]{};

				dwColors[0] = 0xFFFFFFFF;
				dwColors[1] = 0xFFFFAAAA;
				dwColors[2] = 0xFFFFFFAA;
				dwColors[3] = 0xFFAAFFAA;
				dwColors[4] = 0xFFAAAAFF;
				dwColors[5] = 0xFFAAFFFF;
				dwColors[6] = 0xFFFFAAFF;
				
				pParticle->SetColor(dwColors[rand() % 7]);
			}
			else
			{
				pParticle->SetColor(dwColor);
			}

			g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);
		}
	}
}

TMEffectParticle::~TMEffectParticle()
{
}

int TMEffectParticle::Render()
{
	return 1;
}

int TMEffectParticle::IsVisible()
{
	m_fRadius = 5.0f;
	return TMEffect::IsVisible();
}

int TMEffectParticle::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = g_pTimerManager->GetServerTime();
	IsVisible();
	if (m_dwLifeTime)
	{
		if ((static_cast<float>(dwServerTime - m_dwStartTime) / static_cast<float>(m_dwLifeTime)) > 1.0f)
			g_pObjectManager->DeleteObject(this);
	}
	return 1;
}
