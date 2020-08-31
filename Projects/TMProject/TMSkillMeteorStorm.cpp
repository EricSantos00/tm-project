#include "pch.h"
#include "TMSkillMeteorStorm.h"
#include "TMObject.h"
#include "TMShade.h"
#include "TMEffectBillBoard.h"
#include "TMEffectBillBoard2.h"
#include "TMEffectParticle.h"
#include "TMSkillExplosion2.h"
#include "TMMesh.h"
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
		auto pChild = new TMEffectBillBoard2(8, 1000u, 0.0099999998f, 0.0099999998f, 0.0099999998f, 0.0060000001f, 0);

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
			pBill4->m_vecPosition = { m_vecTargetPos.x, m_vecTargetPos.y + 1.0f, m_vecPosition.z };
			pBill4->m_vecStartPos = pBill4->m_vecPosition;
			pBill4->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
			
			if (g_pDevice->m_bSavage == 1 || g_pDevice->m_bIntel == 1)
				pBill4->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

			pBill4->SetColor(0xFFFFFFFF);
			g_pCurrentScene->m_pEffectContainer->AddChild(pBill4);
		}

		auto pParticle = new TMEffectParticle({ m_vecTargetPos.x - 3.0f, m_vecTargetPos.y, m_vecTargetPos.z - 3.0f }, 4, 12, 0.1f, 0xFFFFAA00, 0, 56, 1.0f, 1, {}, 1000u);

		if (pParticle)
			g_pCurrentScene->m_pEffectContainer->AddChild(pParticle);

		unsigned int fScale = dwColor;
		auto pExplosion = new TMSkillExplosion2({ m_vecTargetPos.x - 3.0f, m_vecTargetPos.y, m_vecTargetPos.z - 3.0f }, 0, 3.0f, 2120u, fScale);
		if (pExplosion)
			g_pCurrentScene->m_pEffectContainer->AddChild(pExplosion);

		auto pBill = new TMEffectBillBoard(59, 2500u, 1.2f, 1.2f, 1.2f, 0.003f, 1, 80);
		if (pBill)
		{
			pBill->m_vecPosition = { m_vecTargetPos.x - 3.0f, m_vecTargetPos.y + 1.0f, m_vecPosition.z - 3.0f };
			pBill->m_vecStartPos = pBill->m_vecPosition;
			pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
			if (g_pDevice->m_bSavage == 1 || g_pDevice->m_bIntel == 1)
				pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

			pBill->SetColor(0xFFFFFFFF);
			g_pCurrentScene->m_pEffectContainer->AddChild(pBill);
		}

		auto pParticle1 = new TMEffectParticle({ m_vecTargetPos.x - 3.0f, m_vecTargetPos.y, m_vecTargetPos.z + 3.0f }, 4, 12, 0.1f, 0xFFFFAA00, 0, 56, 1.0f, 1, {}, 1000u);
		if (pParticle1)
			g_pCurrentScene->m_pEffectContainer->AddChild(pParticle1);

		auto pExplosion1 = new TMSkillExplosion2({ m_vecTargetPos.x + 3.0f, m_vecTargetPos.y, m_vecTargetPos.z + 3.0f }, 0, 3.0f, 210, dwColor);
		if(pExplosion1)
			g_pCurrentScene->m_pEffectContainer->AddChild(pExplosion1);

		auto pBill1 = new TMEffectBillBoard(59, 2500u, 1.2f, 1.2f, 1.2f, 0.003f, 1, 80);
		if (pBill1)
		{
			pBill1->m_vecPosition = { m_vecTargetPos.x - 3.0f, m_vecTargetPos.y + 1.0f, m_vecPosition.z + 3.0f};
			pBill1->m_vecStartPos = pBill1->m_vecPosition;
			pBill1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;

			if (g_pDevice->m_bSavage == 1 || g_pDevice->m_bIntel == 1)
				pBill1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

			pBill1->SetColor(0xFFFFFFFF);
			g_pCurrentScene->m_pEffectContainer->AddChild(pBill1);
		}

		auto pParticle2 = new TMEffectParticle({ m_vecTargetPos.x + 3.0f, m_vecTargetPos.y, m_vecTargetPos.z - 3.0f }, 4, 12, 0.1f, 0xFFFFAA00, 0, 56, 1.0f, 1, {}, 1000u);
		if(pParticle2)
			g_pCurrentScene->m_pEffectContainer->AddChild(pParticle2);

		auto pExplosion2 = new TMSkillExplosion2({ m_vecTargetPos.x + 3.0f, m_vecTargetPos.y, m_vecTargetPos.z + 3.0f }, 0, 3.0f, 210, dwColor);
		if (pExplosion2)
			g_pCurrentScene->m_pEffectContainer->AddChild(pExplosion2);

		auto pBill2 = new TMEffectBillBoard(59, 2500u, 1.2f, 1.2f, 1.2f, 0.003f, 1, 80);
		if (pBill2)
		{
			pBill2->m_vecPosition = { m_vecTargetPos.x + 3.0f, m_vecTargetPos.y + 1.0f, m_vecPosition.z - 3.0f};
			pBill2->m_vecStartPos = pBill2->m_vecPosition;
			pBill2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;

			if (g_pDevice->m_bSavage == 1 || g_pDevice->m_bIntel == 1)
				pBill2->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

			pBill2->SetColor(0xFFFFFFFF);
			g_pCurrentScene->m_pEffectContainer->AddChild(pBill2);
		}

		auto pParticle3 = new TMEffectParticle({ m_vecTargetPos.x + 3.0f, m_vecTargetPos.y, m_vecTargetPos.z + 3.0f }, 4, 12, 0.1f, 0xFFFFAA00, 0, 56, 1.0f, 1, {}, 1000u);
		if (pParticle3)
			g_pCurrentScene->m_pEffectContainer->AddChild(pParticle3);

		auto pExplosion3 = new TMSkillExplosion2({ m_vecTargetPos.x + 3.0f, m_vecTargetPos.y, m_vecTargetPos.z + 3.0f }, 0, 3.0f, 210, dwColor);
		if (pExplosion3)
			g_pCurrentScene->m_pEffectContainer->AddChild(pExplosion3);

		auto pBill3 = new TMEffectBillBoard(59, 2500u, 1.2f, 1.2f, 1.2f, 0.003f, 1, 80);
		if (pBill2)
		{
			pBill3->m_vecPosition = { m_vecTargetPos.x + 3.0f, m_vecTargetPos.y + 1.0f, m_vecPosition.z + 3.0f };
			pBill3->m_vecStartPos = pBill3->m_vecPosition;
			pBill3->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;

			if (g_pDevice->m_bSavage == 1 || g_pDevice->m_bIntel == 1)
				pBill3->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

			pBill3->SetColor(0xFFFFFFFF);
			g_pCurrentScene->m_pEffectContainer->AddChild(pBill3);
		}

		nSoundIndex = 309;
	}

	if (g_pSoundManager && g_pSoundManager->GetSoundData(nSoundIndex))
		g_pSoundManager->GetSoundData(nSoundIndex)->Play(0, 0);
}

int TMSkillMeteorStorm::Render()
{
	if (m_fProgress < 0.05f)
		return 1;

	TMEffect::Render();

	TMMesh* pMesh = nullptr;
	switch (m_nLevel)
	{
	case 1:
		pMesh = g_pMeshManager->GetCommonMesh(708, 1, 180000u);
		if (!pMesh)
			return 0;

		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
		g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);

		pMesh->m_fScaleH = 1.7f;
		pMesh->m_fScaleV = 1.7f;

		pMesh->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, m_fAngle + D3DXToRadian(90), D3DXToRadian(45), 0.0f, 0, 0);

		pMesh->m_fScaleH = 2.0f;
		pMesh->m_fScaleV = 2.0f;

		g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
		break;
	case 2:
		pMesh = g_pMeshManager->GetCommonMesh(1608, 0, 180000u);
		if (!pMesh)
			return 0;

		g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
		g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);

		pMesh->m_fScaleH = 3.0f;
		pMesh->m_fScaleV = 3.0f;

		pMesh->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, 0.0f, 0.0f, 0.0f, 0, 0);
		break;
	case 3:
		for (int i = 0; i < 3; ++i)
		{
			pMesh = g_pMeshManager->GetCommonMesh(i + 2816, 0, 180000);
			if (!pMesh)
				return 0;

			g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
			g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
			g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
			g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
			g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
			g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
			g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
			g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);

			pMesh->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, m_fAngle, 0.0f, 0.0f, 0, 0);

			g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
			g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
			g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
			g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
			g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
			g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
			g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
		}
		break;
	case 5:
		pMesh = g_pMeshManager->GetCommonMesh(2840, 1, 180000u);
		if (!pMesh)
			return 0;

		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, 4u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 3u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
		g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);

		pMesh->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, m_fAngle + D3DXToRadian(180), 0.0f, 0.0f, 0, 0);

		g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
		break;
	}

	return 1;
}

int TMSkillMeteorStorm::IsVisible()
{
	auto pMesh = g_pMeshManager->GetCommonMesh(708, 1, 1800000u);
	if (pMesh)
		m_fRadius = pMesh->m_fRadius;

	m_fRadius = 1.0f;
	return TMEffect::IsVisible();
}

int TMSkillMeteorStorm::FrameMove(unsigned int dwServerTime)
{
	if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELECT_SERVER)
		m_pOwner = nullptr;

	dwServerTime = g_pTimerManager->GetServerTime();

	if (!IsVisible())
		return 0;

	if (static_cast<float>(static_cast<int>(dwServerTime - m_dwStartTime)) < 0.0f)
		return 1;

	if (m_nLevel == 9 || m_nLevel == 10)
		g_pObjectManager->DeleteObject(this);

	if (m_pOwner)
	{
		m_vecTargetPos.x = m_pOwner->m_vecPosition.x;
		m_vecTargetPos.z = m_pOwner->m_vecPosition.y;
		m_vecTargetPos.y = m_pOwner->m_fHeight + 1.0f;
	}

	auto vecDPos = m_vecTargetPos - m_vecStartPos;
	m_fAngle = atan2f(vecDPos.x, vecDPos.z) - D3DXToRadian(90);

	if (m_nLevel == 1)
	{
		auto pMesh = g_pMeshManager->GetCommonMesh(708, 1, 180000u);
		if (!pMesh)
			return 0;
		D3DVERTEXBUFFER_DESC vDesc;
		RDLVERTEX* pVertex;
		pMesh->m_pVB->GetDesc(&vDesc);
		pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);

		int nCount = vDesc.Size / sizeof RDLVERTEX;

		for (int i = 0; i < nCount; ++i)
			pVertex[i].diffuse = -1;

		pMesh->m_pVB->Unlock();
		pMesh->m_nTextureIndex[0] = 19;

		auto result = m_vecTargetPos - m_vecStartPos;
		m_fAngle = atan2f(result.x, result.z) - D3DXToRadian(90);
	}
	if (m_nLevel != 2 || m_fLength <= 33.0f || m_fDestLength >= 33.0f)
		m_fProgress = (static_cast<float>(static_cast<int>(dwServerTime - m_dwStartTime))) / static_cast<float>(m_dwLifeTime);
	else
		m_fProgress = (static_cast<float>(static_cast<int>(dwServerTime - m_dwStartTime))) / static_cast<float>(m_dwLifeTime) + 0.80f;

	if (m_fProgress < 1.0f)
	{
		m_vecPosition = (m_vecStartPos * (1.0f - m_fProgress)) + (m_vecTargetPos * m_fProgress);

		if (!m_nLevel)
		{
			if (m_pCenterLight)
				m_pCenterLight->m_vecPosition = m_vecPosition;
			if (m_pCenterLight2)
				m_pCenterLight2->m_vecPosition = m_vecPosition;
			if (m_pCenterFlare)
				m_pCenterFlare->m_vecPosition = m_vecPosition;

			if (m_pLightMap)
				m_pLightMap->SetPosition({ m_vecPosition.x, m_vecPosition.z });
		}
		else if (m_nLevel != 1 || m_bPlaySound || m_fProgress <= 0.1f)
		{
			if (m_nLevel == 4)
			{
				if (m_pCenterLight)
					m_pCenterLight->m_vecPosition = m_vecPosition;
				if (m_pCenterLight2)
					m_pCenterLight2->m_vecPosition = m_vecPosition;
				if (m_pCenterFlare)
					m_pCenterFlare->m_vecPosition = m_vecPosition;

				if (m_pLightMap)
					m_pLightMap->SetPosition({ m_vecPosition.x, m_vecPosition.z });
			}
			else if (m_nLevel == 6)
			{
				if (m_pCenterLight)
					m_pCenterLight->m_vecPosition = m_vecPosition;
				if (m_pCenterLight2)
					m_pCenterLight2->m_vecPosition = m_vecPosition;
				if (m_pCenterFlare)
					m_pCenterFlare->m_vecPosition = m_vecPosition;

				if (m_pLightMap)
					m_pLightMap->SetPosition({ m_vecPosition.x, m_vecPosition.z });
			}
		}
		else
		{
			m_bPlaySound = 1;
			if (g_pSoundManager && g_pSoundManager->GetSoundData(161))
				g_pSoundManager->GetSoundData(161)->Play(0, 0);
		}

		switch (m_nLevel)
		{
		case 2:
			m_vecPosition.y = ((sinf(m_fProgress * D3DXToRadian(180)) * m_fLength) * 0.2f) + m_vecPosition.y;
			break;
		case 3:
			m_fAngle = ((static_cast<float>(dwServerTime % 250)) * D3DXToRadian(180)) / 125.0f;
			break;
		case 6:
			m_fAngle = ((static_cast<float>(dwServerTime % 250)) * D3DXToRadian(180)) / 85.0f;

			m_vecPosition.x += sinf(m_fProgress * D3DXToRadian(180) * 16.0f);
			m_vecPosition.z += sinf(m_fProgress * D3DXToRadian(180) * 16.0f);
			break;
		}

		int nTotalEffects = 4; // v67
		static unsigned int dwOldTime_1 = 0; // 2B42A04 kkkkkkkkkkkkkkkkkkkkk
		if (dwServerTime - dwOldTime_1 < 20)
			nTotalEffects = 1;
		else if (dwServerTime - dwOldTime_1 < 30)
			nTotalEffects = 2;

		for (int j = 0; j < nTotalEffects; ++j)
		{
			int nRand = rand() % 5;
			float fRand = static_cast<float>(nRand);
			auto pBill = new TMEffectBillBoard(0,
				1000u,
				fRand * 0.1f + 0.40f,
				fRand * 0.1f + 0.40f,
				fRand * 0.1f + 0.40f,
				0.001f, 1, 80);

			if (pBill)
			{
				pBill->m_vecPosition = { fRand * 0.0099999998f + m_vecPosition.x, m_vecPosition.y - 0.69999999f + fRand * 0.0099999998f, fRand * 0.0099999998f + m_vecPosition.z };
				pBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				pBill->m_bStickGround = 1;

				if (m_nLevel)
				{
					switch (m_nLevel)
					{
					case 1:
						pBill->SetColor(0xFF3333FF);
						break;
					case 2:
						pBill->SetColor(0xFFFFEE55);
						break;
					case 3:
						pBill->SetColor(0xFF555555);
						break;
					case 4:
						pBill->SetColor(0xFFFF7711);
						break;
					case 5:
						pBill->SetColor(0xFF6677FF);
						break;
					}
				}
				else
					pBill->SetColor(0xFFFF7711);

				g_pCurrentScene->m_pEffectContainer->AddChild(pBill);

				if (j == 3 && m_nLevel == 2)
				{
					auto pChild = new TMEffectBillBoard(59, 800, fRand * 0.1f + 0.40f, fRand * 0.1f + 0.40f, fRand * 0.1f + 0.40f, 0.001f, 1, 80);
					if (pChild)
					{
						pChild->m_vecPosition = { m_vecPosition.x - 0.0099999998f, m_vecPosition.y - 0.69999999f, m_vecPosition.z - 0.0099999998f };
						pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;

						if (g_pDevice->m_bSavage == 1 || g_pDevice->m_bIntel == 1)
							pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

						pChild->m_bStickGround = 1;
						pChild->SetColor(0xFFFFFFFF);

						g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
					}
				}

				if (!m_nLevel || m_nLevel == 4)
				{
					auto pChild = new TMEffectBillBoard(59, 800, fRand * 0.1f + 0.40f, fRand * 0.1f + 0.40f, fRand * 0.1f + 0.40f, 0.001f, 1, 80);
					if (pChild)
					{
						pChild->m_vecPosition = { m_vecPosition.x - 0.0099999998f, m_vecPosition.y - 0.5f, m_vecPosition.z - 0.0099999998f };
						pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;

						if (g_pDevice->m_bSavage == 1 || g_pDevice->m_bIntel == 1)
							pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

						pChild->m_bStickGround = 1;

						if (j == 3)
						{
							pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_NONEBRIGHT;
							pChild->SetColor(0xFFFFFF28);
						}
						else
						{
							pChild->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
							pChild->SetColor(0xFFFF7711);
						}

						g_pCurrentScene->m_pEffectContainer->AddChild(pChild);
					}
				}
			}
		}

		dwOldTime_1 = dwServerTime;
	}
	else
		g_pObjectManager->DeleteObject(this);

	return 1;
}
