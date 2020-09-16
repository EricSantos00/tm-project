#include "pch.h"
#include "TMEffectSkinMesh.h"
#include "DXUtil.h"
#include "TMHuman.h"
#include "TMGlobal.h"
#include "TMEffectBillBoard.h"
#include "TMSkillFire.h"
#include "TMSkillPoison.h"

TMEffectSkinMesh::TMEffectSkinMesh(int nSkinMeshType, TMVector3 vecStart, TMVector3 vecTarget, int nLevel, TMObject* pOwner)
	: TMObject()
{
	m_dwObjType = 331;
	m_pSkinMesh = 0;
	m_pSkinMesh2 = 0;
	m_nSkinMeshType = nSkinMeshType;
	m_nSkinMeshType2 = -1;
	m_fScale2 = 1.0f;
	m_dwStartTime = 0;
	m_dwLifeTime = 0;
	m_nMotionType = 0;
	m_fAngle = 0.0;
	m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
	m_StartColor.r = 1.0f;
	m_StartColor.g = 1.0f;
	m_StartColor.b = 1.0f;
	m_EndColor.r = 1.0f;
	m_EndColor.g = 1.0f;
	m_EndColor.b = 1.0f;
	m_color.r = 1.0f;
	m_color.g = 1.0f;
	m_color.b = 1.0f;
	m_nFade = 0;
	m_nLevel = nLevel;
	m_pOwner = pOwner;

	m_vecStartPos = vecStart;
	m_vecTargetPos = vecTarget;

	m_dwLastSpeedUp = 0;
	auto vecD = vecTarget - vecStart;
	auto fLength = vecD.Length();

	m_dwLifeTime = 200 * (unsigned int)fLength;

	if (!m_dwLifeTime)
		m_dwLifeTime = 1;

	if (m_dwLifeTime > 5000)
		m_dwLifeTime = 5000;

	m_stLookInfo = {};
	m_stSancInfo = {};
	m_stLookInfo2 = {};
	m_bMirror = 0;
}

TMEffectSkinMesh::~TMEffectSkinMesh()
{
	SAFE_DELETE(m_pSkinMesh2);

	if (!m_nLevel && m_nMotionType == 2)
	{
		TMSkillFire* pFire = new TMSkillFire(m_vecTargetPos, 0, nullptr, 0xFFFFFFFF, 0x22331100);

		if (pFire)
			g_pCurrentScene->m_pEffectContainer->AddChild(pFire);
	}
	else
	{
		TMEffectSkinMesh* pEffect = nullptr;
		if (m_nLevel == 1)
			pEffect = new TMEffectSkinMesh(20, m_vecTargetPos, {}, 0, m_pOwner);

		if (pEffect)
		{
			pEffect->m_stLookInfo = m_stLookInfo;
			pEffect->InitObject(0);
			pEffect->m_dwLifeTime = 3000;
			pEffect->m_pSkinMesh->m_vScale.x = 0.2f;
			pEffect->m_pSkinMesh->m_vScale.y = 0.2f;
			pEffect->m_pSkinMesh->m_vScale.z = 0.2f;
			pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
			pEffect->m_StartColor.r = 1.0f;
			pEffect->m_StartColor.g = 1.0f;
			pEffect->m_StartColor.b = 1.0f;
			pEffect->m_nFade = 0;
			pEffect->m_fStartAngle = m_fAngle;
			pEffect->m_nMotionType = 3;

			g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
		}
	}
}

int TMEffectSkinMesh::InitObject(int bExpand)
{
	if (m_nSkinMeshType2 >= 0)
	{
		if (!m_pSkinMesh)
		{
			m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, nullptr, 0, 0, 0);

			if (m_pSkinMesh)
			{
				m_pSkinMesh->RestoreDeviceObjects();

				// this is not a TMHuman object. We cannot use static_cast.
				// Maybe this is wrong or some class was decompiled with the wrong inheritance
				// This will crash...
				m_pSkinMesh->m_pOwner = (TMHuman*)this;
				m_pSkinMesh->m_dwFPS = 80;
				m_pSkinMesh->m_bBaseMat = 0;
			}
		}

		if (m_nMotionType == 10 && m_pSkinMesh)
		{
			m_pSkinMesh->m_dwStartTime = 0;
			m_pSkinMesh->m_dwStartOffset = g_pTimerManager->GetServerTime();
		}

		if (!m_pSkinMesh2)
		{
			m_pSkinMesh2 = new TMSkinMesh(&m_stLookInfo2, &m_stSancInfo, m_nSkinMeshType2, bExpand, nullptr, 0, 0, 0);

			if (m_pSkinMesh2)
			{
				m_pSkinMesh2->RestoreDeviceObjects();
				m_pSkinMesh2->m_dwFPS = 80;

				if (m_nSkinMeshType != 20 || m_stLookInfo2.Mesh0 != 7)
				{
					if (m_nSkinMeshType == 20)
						m_pSkinMesh2->SetVecMantua(3, m_nSkinMeshType);
					else
						m_pSkinMesh2->SetVecMantua(2, m_nSkinMeshType);
				}
				else
				{
					m_pSkinMesh2->SetVecMantua(4, m_nSkinMeshType);
				}
			}
		}

		return 1;
	}

	if (!m_pSkinMesh)
	{
		m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, bExpand, nullptr, 0, 0, 0);

		if (m_pSkinMesh)
		{
			m_pSkinMesh->RestoreDeviceObjects();
			m_pSkinMesh->m_vScale.x = m_fScale;
			m_pSkinMesh->m_vScale.y = m_fScale;
			m_pSkinMesh->m_vScale.z = m_fScale;
			m_pSkinMesh->m_dwFPS = 80;
		}
	}

	if (m_nMotionType == 10 && m_pSkinMesh)
	{
		m_pSkinMesh->m_dwStartTime = 0;
		m_pSkinMesh->m_dwStartOffset = g_pTimerManager->GetServerTime();
	}

	return 1;
}

int TMEffectSkinMesh::Render()
{
	if (g_bHideEffect == 1 && m_nLevel != 3 && m_nLevel != 4 && m_nLevel != 5 && m_nLevel != 6)
		return 1;

	if (m_pSkinMesh && IsVisible() == 1)
	{
		m_pSkinMesh->m_materials.Diffuse.r = m_color.r;
		m_pSkinMesh->m_materials.Diffuse.g = m_color.g;
		m_pSkinMesh->m_materials.Diffuse.b = m_color.b;
		m_pSkinMesh->m_materials.Diffuse.a = m_color.a;

		m_pSkinMesh->m_materials.Specular.r = 1.0f;
		m_pSkinMesh->m_materials.Specular.g = 1.0f;
		m_pSkinMesh->m_materials.Specular.b = 1.0f;

		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);

		if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_BRIGHT)
		{
			g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
			g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
			g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);

			m_pSkinMesh->m_materials.Emissive.r = 0.3f;
			m_pSkinMesh->m_materials.Emissive.g = 0.3f;
			m_pSkinMesh->m_materials.Emissive.b = 0.3f;
		}
		else if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_NONEBRIGHT)
		{
			g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
			g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
			g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);

			m_pSkinMesh->m_materials.Emissive.r = 0.69f * m_pSkinMesh->m_materials.Diffuse.r;
			m_pSkinMesh->m_materials.Emissive.g = 0.69f * m_pSkinMesh->m_materials.Diffuse.g;
			m_pSkinMesh->m_materials.Emissive.b = 0.69f * m_pSkinMesh->m_materials.Diffuse.b;
		}
		else
		{
			if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_DEFAULT)
			{
				g_pDevice->SetRenderState(D3DRS_FOGENABLE, 1u);
				g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
				g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
				g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
			}
			else
			{
				g_pDevice->SetRenderState(D3DRS_DESTBLEND, 9u);
				g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
			}

			m_pSkinMesh->m_materials.Emissive.r = 0.0f;
			m_pSkinMesh->m_materials.Emissive.g = 0.0f;
			m_pSkinMesh->m_materials.Emissive.b = 0.0f;
		}

		if (m_pSkinMesh2)
			m_pSkinMesh2->m_materials = m_pSkinMesh->m_materials;

		m_pSkinMesh->Render(0.0f, 1.0f, 0.0f);
		if (m_pSkinMesh2)
		{
			TMVector3 vecPosScale{ -0.37f * m_fScale2, 1.0f / m_fScale2, 0.2f * m_fScale2 };
			m_pSkinMesh2->m_BaseMatrix = m_pSkinMesh->m_OutMatrix;
			m_pSkinMesh2->Render(vecPosScale.x, vecPosScale.y, vecPosScale.z);
		}

		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
	}

	return 1;
}

int TMEffectSkinMesh::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = g_pTimerManager->GetServerTime();

	if (!m_dwStartTime)
		m_dwStartTime = dwServerTime;

	if (dwServerTime < m_dwStartTime)
		return 1;

	if (m_dwLifeTime && m_dwLifeTime < dwServerTime - m_dwStartTime)
	{
		g_pObjectManager->DeleteObject(this);

		return 1;
	}
	if (m_dwLifeTime && dwServerTime - m_dwStartTime > 10000)
	{
		g_pObjectManager->DeleteObject(this);

		return 1;
	}

	const static unsigned int dwCol[3]{ 0xFFFFAA00, 0xFFFF0000, 0xFFFFAAFF };
	float fProgress = 0.0f;

	if (m_dwLifeTime)
		fProgress = static_cast<float>(dwServerTime - m_dwStartTime) / static_cast<float>(m_dwLifeTime);
	else
		fProgress = 1.0f;

	if (fProgress >= 0.0099999998f)
	{
		if (m_nFade == 1 && m_dwLifeTime)
		{
			m_color.r = cosf(fProgress * D3DXToRadian(180) / 2.0f) * m_StartColor.r;
			m_color.g = cosf(fProgress * D3DXToRadian(180) / 2.0f) * m_StartColor.g;
			m_color.b = cosf(fProgress * D3DXToRadian(180) / 2.0f) * m_StartColor.b;
		}
		else if (m_nFade == 2 && m_dwLifeTime)
		{
			m_color.r = cosf((float)(fProgress * D3DXToRadian(180)) / 2.0f) * m_StartColor.r + (float)(cosf((float)((float)(1.0f - fProgress) * D3DXToRadian(180)) / 2.0f) * m_EndColor.r);
			m_color.g = cosf((float)(fProgress * D3DXToRadian(180)) / 2.0f) * m_StartColor.g + (float)(cosf((float)((float)(1.0f - fProgress) * D3DXToRadian(180)) / 2.0f) * m_EndColor.g);
			m_color.b = cosf((float)(fProgress * D3DXToRadian(180)) / 2.0f) * m_StartColor.b + (float)(cosf((float)((float)(1.0f - fProgress) * D3DXToRadian(180)) / 2.0f) * m_EndColor.b);
		}

		if (fProgress < 1.0f && m_pOwner)
		{
			m_vecTargetPos.x = m_pOwner->m_vecPosition.x;
			// yes... according to original code, is z = y
			m_vecTargetPos.z = m_pOwner->m_vecPosition.y;
			m_vecTargetPos.y = m_pOwner->m_fHeight;
		}

		switch (m_nMotionType)
		{
		case 1:
			m_fHeight = (static_cast<float>(dwServerTime - m_dwStartTime) / 1000.0f) + m_vecStartPos.y;
			break;
		case 2:
		{
			TMVector3 vecDPos = m_vecTargetPos - m_vecStartPos;

			if (m_pOwner)
				vecDPos = TMVector3{ m_pOwner->m_vecPosition.x, m_pOwner->m_fHeight, m_pOwner->m_vecPosition.y } -m_vecStartPos;

			//Fix angle skill: Fera Flamejante
			m_fAngle = atan2f(vecDPos.x, vecDPos.z) + D3DXToRadian(90);

			auto value = static_cast<float>(dwServerTime - m_dwStartTime) / static_cast<float>(m_dwLifeTime);
			if (value < 1.0f)
			{
				TMVector3 vec = m_vecStartPos * (1.0f - value) + (m_vecTargetPos * value);
				m_vecPosition = { vec.x, vec.z };
				m_fHeight = vec.y;

				auto pPoison = new TMSkillPoison({ m_vecPosition.x, m_fHeight, m_vecPosition.y }, dwCol[m_nLevel], 2, 1, 0);
				if (pPoison)
					g_pCurrentScene->m_pEffectContainer->AddChild(pPoison);
			}

			if (m_nLevel)
			{
				m_pSkinMesh->m_dwFPS = 4;
				m_pSkinMesh->SetAnimation(g_MobAniTable[m_nSkinMeshType].dwAniTable[3]);
			}
			else
			{
				m_pSkinMesh->m_dwFPS = 5;
				m_pSkinMesh->SetAnimation(g_MobAniTable[m_nSkinMeshType].dwAniTable[2]);
			}
		}
		break;
		case 3:
		{
			auto fAngle = (((dwServerTime - m_dwStartTime) % 1000u) * 6.2831855f / 1000.0f) + m_fStartAngle;

			if (m_pOwner)
			{
				m_vecPosition.x = (cosf(fAngle) * 1.0f) + m_pOwner->m_vecPosition.x;
				m_vecPosition.y = (sinf(fAngle) * 1.0f) + m_pOwner->m_vecPosition.y;
				m_fHeight = m_pOwner->m_fHeight + 0.5f;
			}
			else
			{
				m_vecPosition.x = (cosf(fAngle) * 1.0f) + m_vecStartPos.x;
				m_vecPosition.y = (sinf(fAngle) * 1.0f) + m_vecStartPos.z;
				m_fHeight = (m_vecStartPos.y + m_vecTargetPos.y) / 2.0f;
			}

			auto pChild = new TMSkillPoison({ m_vecPosition.x, m_fHeight, m_vecPosition.y }, 0xFFFF0000, 2, 1, 0);

			if (pChild)
				g_pCurrentScene->m_pEffectContainer->AddChild(pChild);

			m_pSkinMesh->m_dwFPS = 5;
			m_pSkinMesh->SetAnimation(g_MobAniTable[m_nSkinMeshType].dwAniTable[3]);
		}
		break;
		case 4:
		{
			auto deltaPosition = m_vecTargetPos - m_vecStartPos; // v114
			if (m_pOwner)
				deltaPosition = TMVector3{ m_pOwner->m_vecPosition.x, m_pOwner->m_fHeight, m_pOwner->m_vecPosition.y } -m_vecStartPos;

			m_fAngle = atan2f(deltaPosition.x, deltaPosition.z) + D3DXToRadian(90);
			if (fProgress < 1.0f)
			{
				auto positionProgress = static_cast<float>((dwServerTime - m_dwStartTime + static_cast<unsigned int>(m_vecStartPos.x * 100.0f)) % 1000);
				auto positionAngle = ((positionProgress * D3DXToRadian(360)) / 1000.0f) + m_fStartAngle; //

				auto targetPositionProgress = m_vecTargetPos * fProgress; // v82 - v26
				auto startPositionProgress = m_vecStartPos * (1.0f - fProgress); // v81 - v27

				auto positionByProgress = startPositionProgress + targetPositionProgress;

				m_vecPosition = { cosf(positionAngle) * 0.2f + positionByProgress.x, (sinf(positionAngle) * 0.2f) + positionByProgress.z };
				m_fHeight = positionByProgress.y;

				auto pPoison = new TMSkillPoison({ m_vecPosition.x, m_fHeight, m_vecPosition.y }, dwCol[m_nLevel], 2, 1, 0);
				if (pPoison)
					g_pCurrentScene->m_pEffectContainer->AddChild(pPoison);
			}

			m_pSkinMesh->m_dwFPS = 5;
			m_pSkinMesh->SetAnimation(g_MobAniTable[m_nSkinMeshType].dwAniTable[2]);
		}
		break;
		case 5:
		case 7:
		{
			if (m_pOwner)
			{
				float fHumanHeight = 2.0f;
				float fOffset = 0.0f;

				auto positionProgress = static_cast<float>((dwServerTime - m_dwStartTime + static_cast<unsigned int>(m_vecStartPos.x * 100.0f)) % 1000); // v175
				positionProgress = (positionProgress * D3DXToRadian(360)) / 1000.0f;

				if (m_nMotionType == 7)
				{
					fHumanHeight = 1.9f;
					positionProgress += D3DXToRadian(30);
					fOffset = D3DXToRadian(45);
				}

				TMVector2 vec{ (cosf((m_pOwner->m_fAngle - D3DXToRadian(180)) - fOffset) * 0.3f) + m_pOwner->m_vecPosition.x,
					(sinf((m_pOwner->m_fAngle - D3DXToRadian(180)) - fOffset) * 0.3f) + m_pOwner->m_vecPosition.y };

				m_vecPosition = TMVector2{ (cosf(positionProgress) * 0.1f) + vec.x, (sinf(positionProgress) * 0.1f) + vec.y };
				//m_vecPosition = { cosf(m_pOwner->m_fAngle - D3DXToRadian(180) - fOffset) * 0.30f + m_pOwner->m_vecPosition.x, sinf(m_pOwner->m_fAngle - D3DXToRadian(180) - fOffset) * 0.30f + m_pOwner->m_vecPosition.y };
				m_fHeight = ((fHumanHeight * m_pOwner->m_fScale) + m_pOwner->m_fHeight) + (sinf(positionProgress + fOffset) * 0.05f);
				m_fAngle = m_pOwner->m_fAngle;

				int nRand = rand() % 5;
				if (m_nMotionType == 5)
				{
					float fSize = 1.0f;
					if (m_nLevel == 3)
						m_pSkinMesh->m_dwFPS = 5;

					if (m_nLevel == 4 || m_nLevel == 5 || m_nLevel == 6)
					{
						m_pSkinMesh->m_dwFPS = 10;
						fSize = 2.0f;
					}

					m_pSkinMesh->SetAnimation(g_MobAniTable[m_nSkinMeshType].dwAniTable[2]);

					if (!g_bHideEffect)
					{
						TMEffectBillBoard* mpBill = nullptr;
						if (m_nLevel == 5)
							mpBill = new TMEffectBillBoard(2, 2500u, 0.029999999f * fSize, 0.029999999f * fSize, 0.029999999f * fSize, 0.0f, 1, 80);
						else if (m_nLevel == 6)
							mpBill = new TMEffectBillBoard(200, 1500u, 0.02f * fSize, 0.02f * fSize, 0.02f * fSize, 0.0f, 1, 80);
						else
						{
							mpBill = new TMEffectBillBoard(0, 1500,
								(nRand * 0.00999998f) + (0.00999998f * fSize),
								(nRand * 0.1f) + (0.00999998f * fSize),
								(nRand * 0.00999998f) + (0.00999998f * fSize),
								0.000099999997f,
								1,
								80);
						}

						if (mpBill)
						{
							float _Y = m_fHeight;
							int v45 = rand();

							mpBill->m_vecPosition = { (static_cast<float>((rand() % 10 - 5)) * 0.02f) + m_vecPosition.x, m_fHeight, (static_cast<float>((rand() % 10 - 5)) * 0.02f) + m_vecPosition.y };
							mpBill->m_vecStartPos = mpBill->m_vecPosition;
							mpBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
							mpBill->m_bStickGround = 0;
							mpBill->m_nParticleType = 1;

							if (m_nLevel == 5)
								mpBill->m_fParticleV = -1.5f;
							else
								mpBill->m_fParticleV = -0.5f;

							if (m_nLevel == 3)
								mpBill->SetColor(0xFFFFAAFF);
							else if (m_nLevel == 4)
								mpBill->SetColor(0xFFAAFFEE);
							else if (m_nLevel == 5)
								mpBill->SetColor(0xFFEEEEFF);

							g_pCurrentScene->m_pEffectContainer->AddChild(mpBill);
						}
					}
				}
				else
				{
					m_pSkinMesh->m_dwFPS = 4;
					m_pSkinMesh->SetAnimation(g_MobAniTable[m_nSkinMeshType].dwAniTable[3]);

					if (!g_bHideEffect)
					{
						auto pEffect = new TMEffectBillBoard(0, 1500u, nRand * 0.00999998f + 0.02f, 0.00999998f * 0.1f + 0.2f, nRand * 0.00999998f + 0.02f, 0.000099999997f, 1, 80);
						if (pEffect)
						{
							pEffect->m_vecPosition = { (rand() % 10 - 5) * 0.02f + m_vecPosition.x, m_fHeight, static_cast<float>((rand() % 10 - 5)) * 0.02f + m_vecPosition.y };
							pEffect->m_vecStartPos = pEffect->m_vecPosition;

							pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
							pEffect->m_bStickGround = 0;
							pEffect->m_nParticleType = 1;
							pEffect->m_fParticleV = 0.5f;

							if (m_nLevel == 3)
								pEffect->SetColor(0xFFFF0000);

							g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
						}
					}
				}
			}
		}
		break;
		case 6:
		{
			auto deltaPosition = m_vecTargetPos - m_vecStartPos; // v111
			if (m_pOwner)
				deltaPosition = TMVector3{ m_pOwner->m_vecPosition.x, m_pOwner->m_fHeight, m_vecPosition.y } -m_vecStartPos;

			m_fAngle = atan2f(deltaPosition.x, deltaPosition.z) + D3DXToRadian(90);

			float v165 = static_cast<float>(dwServerTime - m_dwStartTime);
			if (static_cast<float>(dwServerTime - m_dwStartTime) / static_cast<float>(m_dwLifeTime) < 1.0f)
			{
				TMVector3 targetPositionProgress = m_vecTargetPos * static_cast<float>(dwServerTime - m_dwStartTime) / static_cast<float>(m_dwLifeTime);
				TMVector3 startPositionProgress = m_vecStartPos * (1.0f - static_cast<float>(dwServerTime - m_dwStartTime) / static_cast<float>(m_dwLifeTime));

				auto positionTo2D = targetPositionProgress + startPositionProgress;
				m_vecPosition = TMVector2{ positionTo2D.x, positionTo2D.z };
				m_fHeight = positionTo2D.y;
			}

			if (!g_bHideEffect)
			{
				int randScale = rand() % 5;
				auto pEffect = new TMEffectBillBoard(0, 1500u, randScale * 0.05f + 0.02f, randScale * 0.1f + 0.02f, randScale * 0.05f + 0.02f);

				if (pEffect)
				{
					pEffect->m_vecPosition = { static_cast<float>(rand() % 10 - 5) * 0.02f + m_vecPosition.x, m_fHeight, static_cast<float>(rand() % 10 - 5) * 0.02f + m_vecPosition.y };
					pEffect->m_vecStartPos = pEffect->m_vecPosition;

					pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
					pEffect->m_bStickGround = 0;
					pEffect->m_nParticleType = 1;
					pEffect->m_fParticleV = 1.0f;
					pEffect->SetColor(0xFFAA8877);

					g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
				}
			}
		}
		break;
		case 8:
			m_fHeight = m_vecStartPos.y - static_cast<float>(dwServerTime - m_dwStartTime) * 2.0f / 1000.0f;
			break;
		case 9:
		{
			float progressLifeTime = static_cast<float>(dwServerTime - m_dwStartTime) / static_cast<float>(m_dwLifeTime);
			if (progressLifeTime < 1.0f)
				m_fHeight = ((1.0f - progressLifeTime) * 3.0f) + m_vecStartPos.y;
		}
		break;
		case 10:
		{
			if (m_pOwner)
			{
				m_vecPosition.x = (m_pOwner->m_vecTempPos[1].x + m_pOwner->m_vecTempPos[2].x) / 2.0f;
				m_vecPosition.y = (m_pOwner->m_vecTempPos[1].z + m_pOwner->m_vecTempPos[2].z) / 2.0f;
				m_fHeight = (m_pOwner->m_vecTempPos[1].y + m_pOwner->m_vecTempPos[1].y) / 2.0f;
				m_fAngle = m_pOwner->m_fAngle;
			}

			if (m_pSkinMesh)
			{
				float progressLifeTime = static_cast<float>(dwServerTime - m_dwStartTime) / static_cast<float>(m_dwLifeTime); // v199
				auto fLemit = 0.56999f;

				constexpr auto a = D3DXToRadian(90);
				if (progressLifeTime > 0.56999f)
				{
					m_color.r *= cosf(((progressLifeTime - fLemit) * D3DXToRadian(180)) / ((1.0f - fLemit) * 2.0f));
					m_color.g *= cosf(((progressLifeTime - fLemit) * D3DXToRadian(180)) / ((1.0f - fLemit) * 2.0f));
					m_color.b *= cosf(((progressLifeTime - fLemit) * D3DXToRadian(180)) / ((1.0f - fLemit) * 2.0f));

					m_pSkinMesh->m_vScale.x = ((progressLifeTime - fLemit) * 1.0f) + 1.0f;
					m_pSkinMesh->m_vScale.y = ((progressLifeTime - fLemit) * 1.0f) + 1.0f;
					m_pSkinMesh->m_vScale.z = ((progressLifeTime - fLemit) * 1.0f) + 1.0f;
				}

				m_pSkinMesh->m_dwFPS = 15 * m_dwLifeTime / 1000u;
				m_pSkinMesh->SetAnimation(g_MobAniTable[m_nSkinMeshType].dwAniTable[2]);
			}
		}
		break;
		}
	}

	SetPosition(m_vecPosition.x, m_fHeight, m_vecPosition.y);
	SetAngle(0, m_fAngle, 0);

	if (m_pSkinMesh && IsVisible() == 1)
	{
		m_pSkinMesh->FrameMove(dwServerTime);

		if (m_pSkinMesh2)
			m_pSkinMesh2->FrameMove(dwServerTime);
	}

	return 1;
}

void TMEffectSkinMesh::RestoreDeviceObjects()
{
	if (!m_pSkinMesh)
	{
		m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, nullptr, 0, 0, 0);

		if (m_pSkinMesh)
			m_pSkinMesh->RestoreDeviceObjects();
	}

	if (m_nSkinMeshType2 > 0 && !m_pSkinMesh2)
		m_pSkinMesh2 = new TMSkinMesh(&m_stLookInfo2, &m_stSancInfo, m_nSkinMeshType2, 0, nullptr, 0, 0, 0);

	if (m_pSkinMesh2)
		m_pSkinMesh2->RestoreDeviceObjects();
}

void TMEffectSkinMesh::InvalidateDeviceObjects()
{
	if (m_pSkinMesh)
		m_pSkinMesh->InvalidateDeviceObjects();

	if (m_pSkinMesh2)
		m_pSkinMesh2->InvalidateDeviceObjects();
}

void TMEffectSkinMesh::InitPosition(float fX, float fY, float fZ)
{
	m_vecStartPos.x = fX;
	m_vecStartPos.z = fZ;
	m_vecStartPos.y = fY;

	TMObject::InitPosition(fX, fY, fZ);
}