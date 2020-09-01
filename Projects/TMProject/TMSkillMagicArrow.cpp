#include "pch.h"
#include "TMSkillMagicArrow.h"
#include "TMObject.h"
#include "TMEffectBillBoard.h"
#include "TMSkillExplosion2.h"
#include "TMSkillFire.h"
#include "TMGlobal.h"
#include "TMShade.h"
#include "TMEffectMesh.h"

TMSkillMagicArrow::TMSkillMagicArrow(TMVector3 vecStart, TMVector3 vecTarget, int nType, TMObject* pOwner)
	: TMEffect()
{
	m_vecStartPos = TMVector3{};
	m_vecTargetPos = TMVector3{};

	m_vecStartPos = vecStart;
	m_vecPosition = vecStart;
	m_vecTargetPos = vecTarget;

	m_nType = nType;
	m_dwStartTime = g_pTimerManager->GetServerTime();

	m_dwColor = 0xFFAA88FF;
	m_dwColor2 = 0xFF4422AA;

	float fScale = 0.69f;
	int nMeshIndex = 701;
	int nSoundIndex = 161;

	auto vecD = vecTarget - vecStart;
	float fLength = vecD.Length();
	m_dwLifeTime = static_cast<unsigned int>(50.0f * fLength);

	switch (m_nType)
	{
	case 1:      
		fScale = 1.0f;
		nMeshIndex = 8;
		nSoundIndex = 155;
		m_dwColor = 1145324612;
		m_dwColor2 = -5601280;
		m_dwLifeTime = (unsigned int)(float)(fLength * 120.0f);
		break;
	case 2:
		fScale = 1.0f;
		nMeshIndex = 8;
		nSoundIndex = 155;
		m_dwColor = 0xFF004488;
		m_dwColor2 = 0xFF001122;
		m_dwLifeTime = (unsigned int)(float)(fLength * 200.0);
		break;
	case 5:
		fScale = 0.60f;
		nMeshIndex = 8;
		nSoundIndex = 155;
		m_dwColor = 0xFF226644;
		m_dwColor2 = 0xFF112211;
		m_dwLifeTime = (unsigned int)(float)(fLength * 200.0);
		break;
	case 3:
		nMeshIndex = 505;
		m_dwLifeTime = 4000;
		m_dwColor = 0xFFFFFFFF;
		break;
	case 4:
		nMeshIndex = 504;
		m_dwLifeTime = 4000;
		m_dwColor = 0xFFFFFFFF;
		break;
	}

	if (m_nType != 3 && m_nType != 4 && m_nType != 5)
	{	
		m_pLightMap = new TMShade(4, 7, 1.0f);

		if (m_pLightMap)
		{
			m_pLightMap->SetColor(m_dwColor2);
			m_pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
		}

		if (g_pSoundManager && g_pSoundManager->GetSoundData(nSoundIndex))
			g_pSoundManager->GetSoundData(nSoundIndex)->Play(0, 0);
	}

	if (!m_dwLifeTime)
		m_dwLifeTime = 1;
	if (m_dwLifeTime > 5000)
		m_dwLifeTime = 5000;

	m_pEffectMesh = new TMEffectMesh(nMeshIndex, m_dwColor, m_fAngle, 1);
	if (m_pEffectMesh)
	{
		m_pEffectMesh->m_fScaleH = fScale;
		m_pEffectMesh->m_fScaleV = fScale;

		if (m_nType == 3 || m_nType == 4)
		{
			m_pEffectMesh->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
			m_pEffectMesh->m_cUScroll = 0;
			m_pEffectMesh->m_fScaleH = 1.0f;
			m_pEffectMesh->m_fScaleV = 1.0f;
		}
	}

	m_pOwner = pOwner;
}

TMSkillMagicArrow::~TMSkillMagicArrow()
{
	SAFE_DELETE(m_pLightMap);
	SAFE_DELETE(m_pEffectMesh);

	if (g_bHideEffect != 1)
	{
		if (!m_nType)
		{
			auto pEffect = new TMEffectBillBoard(71, 888u, 1.5f, 1.5f, 1.5f, 0.0f, 8, 111);

			if (pEffect)
			{
				pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				pEffect->m_nFade = 0;
				pEffect->m_vecPosition = m_vecTargetPos;
				pEffect->m_vecPosition.y = pEffect->m_vecPosition.y - 0.5f;

				g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
			}

			auto pLightMap = new TMShade(4, 7, 1.0f);
			if (pLightMap)
			{
				pLightMap->SetColor(m_dwColor2);
				pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				pLightMap->SetPosition({ m_vecTargetPos.x, m_vecTargetPos.z });
				pLightMap->m_dwLifeTime = 1500;

				g_pCurrentScene->m_pEffectContainer->AddChild(pLightMap);
			}
		}
		else if (m_nType == 1)
		{
			auto dwColor = 0x44444444;
			auto pExplosion = new TMSkillExplosion2(m_vecTargetPos, 0, 1.0f, 180, dwColor);

			if (pExplosion)
				g_pCurrentScene->m_pEffectContainer->AddChild(pExplosion);
		}
		else if (m_nType == 2)
		{
			auto pChild = new TMSkillExplosion2(m_vecTargetPos, 2, 1.0f, 180, 0x4488);

			if(pChild)
				g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
		}

		if (m_nType != 3 && m_nType != 4 && g_pSoundManager && g_pSoundManager->GetSoundData(154))
			g_pSoundManager->GetSoundData(154)->Play(0, 0);
	}
}

int TMSkillMagicArrow::Render()
{
	if (!m_pEffectMesh)
		return 0;

	if (m_fProgress < 0.05f)
		return 1;

	if (m_bVisible == 1)
	{
		m_pEffectMesh->Render();

		if (m_pLightMap)
			m_pLightMap->RenderUnder();
	}

	return 1;
}

int TMSkillMagicArrow::IsVisible()
{
	m_fRadius = 1.0f;

	return TMEffect::IsVisible();
}

int TMSkillMagicArrow::FrameMove(unsigned int dwServerTime)
{
	if (!m_pEffectMesh)
		return 0;

	if (!IsVisible())
		return 0;

	dwServerTime = g_pTimerManager->GetServerTime();

	if (m_nType)
	{
		switch (m_nType)
		{
		case 1:
			m_pEffectMesh->m_nTextureIndex = dwServerTime % 300 / 50 + 61;
			break;
		case 2:
			m_pEffectMesh->m_nTextureIndex = dwServerTime % 300 / 50 + 101;
			break;
		case 3:
			m_pEffectMesh->m_nTextureIndex = 97;
			break;
		case 4:
			m_pEffectMesh->m_nTextureIndex = 200;
			break;
		case 5:
			m_pEffectMesh->m_nTextureIndex = dwServerTime % 300 / 50 + 101;
			break;
		}
	}
	else
		m_pEffectMesh->m_nTextureIndex = dwServerTime % 240 / 40 + 20;

	m_fProgress = static_cast<float>(static_cast<int>(dwServerTime - m_dwStartTime)) / static_cast<float>(m_dwLifeTime);

	if (m_fProgress > 0.30f && m_pOwner)
		m_pOwner = nullptr;

	if (m_pOwner)
	{
		m_vecTargetPos.x = m_pOwner->m_vecPosition.x;
		m_vecTargetPos.z = m_pOwner->m_vecPosition.y;
		m_vecTargetPos.y = m_pOwner->m_fHeight + 1.0f;
	}

	auto vecDPos = m_vecTargetPos - m_vecStartPos;
	m_fAngle = atan2f(vecDPos.x, vecDPos.z) - D3DXToRadian(90);

	if (m_fProgress < 1.0f)
	{
		m_vecPosition = (m_vecStartPos * (1.0f - m_fProgress)) + (m_vecTargetPos * m_fProgress);

		if (m_nType == 3)
		{
			float fSin = sinf(m_fProgress * 4.0f * D3DXToRadian(180));
			m_vecPosition.x = m_vecPosition.x + fSin;
		}

		if (m_pLightMap)
			m_pLightMap->SetPosition({ m_vecPosition.x, m_vecPosition.z });

		static auto dwOldTime_0 = 0;
		if (dwServerTime - dwOldTime_0 > 30)
		{
			if (!m_nType)
			{
				for (int i = 0; i < 3; ++i)
				{
					int nRand = rand() % 5;
					float fRand = static_cast<float>(nRand);

					auto pBill = new TMEffectBillBoard(0, 1000u, fRand * 0.2f + 0.30f, fRand * 0.2f + 0.30f, fRand * 0.2f + 0.30f, 0.001f, 1, 80);
					if (pBill)
					{
						pBill->m_vecPosition = { fRand * 0.1f + m_vecPosition.x, m_vecPosition.y - 1.0f, fRand * 0.1f + m_vecPosition.z };
						pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
						pBill->m_bStickGround = 1;
						pBill->SetColor(m_dwColor2);

						g_pCurrentScene->m_pEffectContainer->AddChild(pBill);
					}
				}
			}
			else if (m_nType != 3 && m_nType != 4)
			{
				TMScene* pScene = g_pCurrentScene;
				TMVector3 vec{ m_vecPosition.x, 0.0f, m_vecPosition.z };
				vec.y = (pScene->GroundGetMask(TMVector2 { vec.x, vec.z }) * 0.1f) + 0.4f;

				TMSkillFire* pFire = nullptr;

				if (m_nType == 2)
					pFire = new TMSkillFire(vec, 6, 0, 0x4488, 0x4488);
				else if (m_nType == 5)
					pFire = new TMSkillFire(vec, 6, 0, 0x112211u, 0x112211u);
				else
					pFire = new TMSkillFire(vec, 3, 0, 0x44444444u, 0x22331100u);

				if (pFire)
					g_pCurrentScene->m_pEffectContainer->AddChild(pFire);
			}

			if (m_pEffectMesh)
			{
				m_pEffectMesh->m_fAngle = m_fAngle;
				m_pEffectMesh->m_vecPosition = m_vecPosition;
				m_pEffectMesh->FrameMove(dwServerTime);
			}

			dwOldTime_0 = dwServerTime;
		}

		if ((m_nType == 3 || m_nType == 4) && m_pEffectMesh)
		{
			m_pEffectMesh->m_fAngle = m_fAngle + D3DXToRadian(180);
			m_pEffectMesh->m_vecPosition = m_vecPosition;
			m_pEffectMesh->FrameMove(dwServerTime);
		}
	}
	else
		g_pObjectManager->DeleteObject(this);

	return 1;
}
