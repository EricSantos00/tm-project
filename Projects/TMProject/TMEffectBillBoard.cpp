#include "pch.h"
#include "TMShade.h"
#include "TMEffectBillBoard.h"
#include "TMGlobal.h"
#include "TMObject.h"
#include "TMHuman.h"
#include "TMCamera.h"

TMEffectBillBoard::TMEffectBillBoard(int nTextureIndex, unsigned int dwLifeTime, float fScaleX, float fScaleY, float fScaleZ, float fVelocity, int nCycleCount, int nCycleTime) :
	TMEffect(),
	m_vecScale{},
	m_vecStartPos{},
	m_vecDir{},
	m_vecRotAxis{}
{
	m_fAxisAngle = 0.0f;
	m_nParticleType = 0;
	m_dwCreateTime = 0;
	m_fProgress = 0.0f;
	m_bFrameMove = 1;
	m_dwLifeTime = dwLifeTime;
	m_vecScale.x = fScaleX;
	m_vecScale.y = fScaleY;
	m_vecScale.z = fScaleZ;
	m_fScaleVelX = fVelocity;
	m_fScaleVelY = fVelocity;
	m_fScaleVelZ = fVelocity;
	m_nTextureIndex = nTextureIndex;
	m_nCycleIndex = 0;
	m_nCycleCount = nCycleCount;
	m_nCycleTime = nCycleTime;
	m_nFade = 1;
	m_bLookCam = 1;
	m_bStickGround = 0;
	m_pOwner = 0;
	m_pLightMap = 0;
	m_fParticleH = 1.0f;
	m_fParticleV = 2.0f;
	m_fCircleSpeed = 6.0f;
	m_fBaseAlpha = 0.69999999f;

	m_vecPosition = TMVector3{ 0.0f, 0.0f, 0.0f };

	m_vertex[0].position = TMVector3{ -0.5f, -0.5f, 0.0f };
	m_vertex[1].position = TMVector3{ 0.5f, -0.5f, 0.0f };
	m_vertex[2].position = TMVector3{ 0.5f, 0.5f, 0.0f };
	m_vertex[3].position = TMVector3{ -0.5f, 0.5f, 0.0f };

	m_vertex[0].tu = 0.02f;
	m_vertex[0].tv = 0.98000002f;
	m_vertex[1].tu = 0.98000002f;
	m_vertex[1].tv = 0.98000002f;
	m_vertex[2].tu = 0.98000002f;
	m_vertex[2].tv = 0.02f;
	m_vertex[3].tu = 0.02f;
	m_vertex[3].tv = 0.02f;

	SetColor(0xFFFFFFFF);

	if (nTextureIndex == 33)
	{
		m_vertex[0].tu = 0.0f;
		m_vertex[0].tv = 1.0f;
		m_vertex[1].tu = 1.0f;
		m_vertex[1].tv = 1.0f;
		m_vertex[2].tu = 1.0f;
		m_vertex[2].tv = 0.0f;
		m_vertex[3].tu = 0.0f;
		m_vertex[3].tv = 0.0f;
	}

	m_nAnimationType = 0;
	m_bIsinit = 0;
}

TMEffectBillBoard::~TMEffectBillBoard()
{
	if (m_pLightMap)
	{
		delete m_pLightMap;

		m_pLightMap = nullptr;
	}
}

int TMEffectBillBoard::Render()
{
	if (g_bHideBackground == 1)
		return 0;

	if (!m_bIsinit)
		return 0;

	if (!strlen(g_pTextureManager->m_stEffectTextureList[m_nTextureIndex].szFileName))
		return 0;

	if (m_dwKey != -1 &&
		m_dwKey != TreeNode::m_VisualKey1 &&
		m_dwKey != TreeNode::m_VisualKey2 &&
		m_dwKey != TreeNode::m_VisualKey3 &&
		m_dwKey != TreeNode::m_VisualKey4)
	{
		return 0;
	}

	int AlphaEnd = 28;

	TMVector3 vec
	{
		g_pObjectManager->m_pCamera->m_cameraPos.x,
		0.0f,
		g_pObjectManager->m_pCamera->m_cameraPos.z
	};

	float fLen = m_vecPosition.DistanceFrom(vec);
	float FogLen = static_cast<float>(AlphaEnd);

	if (fLen > 45.0f)
		return 1;

	if (g_bHideEffect == 1 && m_nTextureIndex != 56 && m_nTextureIndex != 60 && m_nTextureIndex != 45)
		return 1;

	if (g_bHideEffect == 1 && m_nFade)
		return 1;

	if (m_dwLifeTime && m_fProgress < 0.050000001f)
		return 1;

	if (m_bVisible == 1)
	{
		g_pDevice->m_pd3dDevice->SetTransform((D3DTRANSFORMSTATETYPE)256, &m_matEffect);
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);

		if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_BRIGHT)
		{
			g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
			g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
		}
		else
		{
			g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
			g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
		}
		g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);

		g_pDevice->m_pd3dDevice->SetFVF(322u);

		g_pDevice->SetTexture(0, g_pTextureManager->GetEffectTexture(m_nCycleIndex + m_nTextureIndex, 5000u));

		if (g_pDevice->m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2u, m_vertex, 24u) < 0) 
			return 0;

		g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);

		if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_BRIGHT)
			g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
		else
			g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
	}
	return 1;
}

void TMEffectBillBoard::SetColor(unsigned int dwColor)
{
	for (int i = 0; i < 4; ++i)
		m_vertex[i].diffuse = dwColor;

	m_dwA = (dwColor & 0xFF000000) >> 24;
	m_dwR = (dwColor & 0xFF0000) >> 16;
	m_dwG = (dwColor & 0xFF00) >> 8;
	m_dwB = static_cast<unsigned char>(dwColor);
}

int TMEffectBillBoard::FrameMove(unsigned int dwServerTime)
{
	if (!m_bFrameMove && dwServerTime)
		return 1;

	m_bIsinit = 1;

	dwServerTime = g_pTimerManager->GetServerTime();

	if (!m_dwCreateTime)
		m_dwCreateTime = dwServerTime;

	int timespent = 0;

	if (dwServerTime < m_dwCreateTime)
		timespent = m_dwLifeTime;
	else
		timespent = dwServerTime - m_dwCreateTime;

	if (m_dwLifeTime && static_cast<int>(m_dwLifeTime) <= timespent)
	{
		m_bVisible = 0;
		g_pObjectManager->DeleteObject(static_cast<TreeNode*>(this));
		
		return 1;
	}

	if (m_pOwner && m_nParticleType != 9)
	{
		if (m_pOwner->m_dwObjType != 3)
		{
			m_vecPosition.x = m_pOwner->m_vecPosition.x;
			m_vecPosition.z = m_pOwner->m_vecPosition.y;
			m_vecPosition.y = (m_vecScale.y / 2.0f) + m_pOwner->m_fHeight;
		}
		else
		{
			if (static_cast<TMHuman*>(m_pOwner)->m_cMount == 1)
			{
				m_vecPosition = m_pOwner->m_vecSkinPos;
				m_vecPosition.y += (m_vecScale.y / 2.0f);
			}
			else
			{
				m_vecPosition.x = m_pOwner->m_vecPosition.x;
				m_vecPosition.z = m_pOwner->m_vecPosition.y;
				m_vecPosition.y = (m_vecScale.y / 2.0f) + m_pOwner->m_fHeight;
			}
		}
	}

	DWORD dwMod = m_nCycleTime * m_nCycleCount;

	if (!dwMod)
		dwMod = 1;

	if (m_nCycleTime)
		m_nCycleIndex = timespent % dwMod / m_nCycleTime;
	else
		m_nCycleIndex = 0;

	if (m_dwLifeTime)
	{
		m_fProgress = (float)timespent / (float)m_dwLifeTime;
	}

	if (m_fProgress < 0.0f)
		m_fProgress = 0.0099999998f;

	if (m_fProgress > 1.0f)
		m_fProgress = 1.0f;

	switch (m_nFade)
	{
	case 1:
	{
		float fAlpha = sinf(m_fProgress * 3.1415927f);

		DWORD dwA = (unsigned int)((float)m_dwA * fAlpha);
		DWORD dwR = (unsigned int)((float)m_dwR * fAlpha);
		DWORD dwG = (unsigned int)((float)m_dwG * fAlpha);
		DWORD dwB = (unsigned int)((float)m_dwB * fAlpha);

		for (int i = 0; i < 4; ++i)
			m_vertex[i].diffuse = dwB | (dwG << 8) | (dwR << 16) | (dwA << 24);
	}
	break;
	case 2:
	{
		DWORD dwThis = (unsigned int)this % 100;
		float fOther = 1.0f - m_fBaseAlpha;
		float fVel = (float)((dwServerTime + 200 * dwThis) % 3000) / 3000.0f;

		DWORD dwA = (unsigned int)(((fOther * fabsf(sinf((fVel * 3.1415927f) * 2.0f))) + m_fBaseAlpha) * (float)m_dwA);
		DWORD dwR = (unsigned int)(((fOther * fabsf(sinf((fVel * 3.1415927f) * 2.0f))) + m_fBaseAlpha) * (float)m_dwR);
		DWORD dwG = (unsigned int)(((fOther * fabsf(sinf((fVel * 3.1415927f) * 2.0f))) + m_fBaseAlpha) * (float)m_dwG);
		DWORD dwB = (unsigned int)(((fOther * fabsf(sinf((fVel * 3.1415927f) * 2.0f))) + m_fBaseAlpha) * (float)m_dwB);

		for (int j = 0; j < 4; ++j)
			m_vertex[j].diffuse = dwB | (dwG << 8) | (dwR << 16) | (dwA << 24);
	}
	break;
	case 3:
	{
		DWORD dwA = (unsigned int)((float)m_dwA * sinf(m_fProgress * 3.1415927f));

		for (int k = 0; k < 4; ++k)
			m_vertex[k].diffuse = m_dwB | (m_dwG << 8) | (m_dwR << 16) | (dwA << 24);
	}
	break;
	case 4:
	{
		float fProgress{};

		if (m_fProgress >= 0.30000001f)
			fProgress = 1.0f - ((m_fProgress - 0.30000001f) * 1.428f);
		else
			fProgress = m_fProgress * 3.3299999f;

		DWORD dwA = (unsigned int)((float)m_dwA * fProgress);

		for (int l = 0; l < 4; ++l)
			m_vertex[l].diffuse = m_dwB | (m_dwG << 8) | (m_dwR << 16) | (dwA << 24);
	}
	break;
	}

	switch ((m_nParticleType - 1))
	{
	case 0:
		m_vecPosition.y = (m_fProgress * m_fParticleV) + m_vecStartPos.y;
		break;
	case 1:
	{
		float fSin = sinf((m_fProgress * 3.1415927f) * m_fCircleSpeed);
		m_vecPosition.y = (m_fProgress * m_fParticleV) + m_vecStartPos.y;
		m_vecPosition.x = (fSin * m_fParticleH) + m_vecStartPos.x;
	}
	break;
	case 2:
	{
		float fSin = sinf((m_fProgress * 3.1415927f) * m_fCircleSpeed);
		float fCos = cosf((m_fProgress * 3.1415927f) * m_fCircleSpeed);
		m_vecPosition.y = (m_fProgress * m_fParticleV) + m_vecStartPos.y;
		m_vecPosition.x = (fSin * m_fParticleH) + m_vecStartPos.x;
		m_vecPosition.z = (fCos * m_fParticleH) + m_vecStartPos.z;
	}
	break;
	case 3:
	{
		float fSin = sinf((m_fProgress * 3.1415927f) * m_fCircleSpeed);
		m_vecPosition.y = (m_fProgress * m_fParticleV) + m_vecStartPos.y;
		m_vecPosition.x = (fSin * m_fParticleH) + m_vecStartPos.x;
		m_vecPosition.z = (m_fProgress * m_fParticleH) + m_vecStartPos.z;
	}
	break;
	case 4:
	{
		float fSin = sinf((m_fProgress * 3.1415927f) * m_fCircleSpeed);
		m_vecPosition.y = (m_fProgress * m_fParticleV) + m_vecStartPos.y;
		m_vecPosition.x = (m_fProgress * m_fParticleH) + m_vecStartPos.x;
		m_vecPosition.z = (fSin * m_fParticleH) + m_vecStartPos.z;
	}
	break;
	case 5:
	{
		float fSin = sinf((m_fProgress * 3.1415927f) * m_fCircleSpeed);
		float fSin2 = sinf(((m_fProgress * 6.0f) * 3.1415927f) * m_fCircleSpeed);
		m_vecPosition.y = (fSin2 * m_fParticleV) + m_vecStartPos.y;
		m_vecPosition.x = (m_fProgress * m_fParticleH) + m_vecStartPos.x;
		m_vecPosition.z = (fSin * m_fParticleH) + m_vecStartPos.z;
	}
	break;
	case 6:
	{
		float fCos = cosf((m_fProgress * 3.1415927f) * m_fCircleSpeed);
		float fCos2 = cosf(((m_fProgress * 6.0f) * 3.1415927f) * m_fCircleSpeed);
		m_vecPosition.y = (fCos2 * m_fParticleV) + m_vecStartPos.y;
		m_vecPosition.x = (fCos * m_fParticleH) + m_vecStartPos.x;
		m_vecPosition.z = (m_fProgress * m_fParticleH) + m_vecStartPos.z;
	}
	break;
	case 7:
	{
		float fSin = sinf((m_fProgress * 3.1415927f) * m_fCircleSpeed);
		float fCos = cosf((m_fProgress * 3.1415927f) * m_fCircleSpeed);
		float fCos2 = cosf(((m_fProgress * 6.0f) * 3.1415927f) * m_fCircleSpeed);
		m_vecPosition.y = (fCos2 * m_fParticleV) + m_vecStartPos.y;
		m_vecPosition.x = ((m_fProgress * fCos) * m_fParticleH) + m_vecStartPos.x;
		m_vecPosition.z = ((m_fProgress * fSin) * m_fParticleH) + m_vecStartPos.z;
	}
	break;
	case 8:
	{
		if (m_pOwner)
		{
			if (m_pOwner->m_dwObjType == 3)
			{
				if (static_cast<TMHuman*>(m_pOwner)->m_cMount == 1)
				{
					m_vecPosition = m_pOwner->m_vecSkinPos;
					m_vecPosition.y = ((1.0f - m_fProgress) * m_vecStartPos.y) + ((m_pOwner->m_vecSkinPos.y + 1.0f) * m_fProgress);
					m_vecPosition.x = ((1.0f - m_fProgress) * m_vecStartPos.x) + (m_pOwner->m_vecSkinPos.x * m_fProgress);
					m_vecPosition.z = ((1.0f - m_fProgress) * m_vecStartPos.z) + (m_pOwner->m_vecSkinPos.y * m_fProgress);
				}
				else
				{
					m_vecPosition.y = ((1.0f - m_fProgress) * m_vecStartPos.y) + ((m_pOwner->m_fHeight + 1.0f) * m_fProgress);
					m_vecPosition.x = ((1.0f - m_fProgress) * m_vecStartPos.x) + (m_pOwner->m_vecPosition.x * m_fProgress);
					m_vecPosition.z = ((1.0f - m_fProgress) * m_vecStartPos.z) + (m_pOwner->m_vecPosition.y * m_fProgress);
				}
			}
			else
			{
				m_vecPosition.y = ((1.0f - m_fProgress) * m_vecStartPos.y) + ((m_pOwner->m_fHeight + 1.0f) * m_fProgress);
				m_vecPosition.x = ((1.0f - m_fProgress) * m_vecStartPos.x) + (m_pOwner->m_vecPosition.x * m_fProgress);
				m_vecPosition.z = ((1.0f - m_fProgress) * m_vecStartPos.z) + (m_pOwner->m_vecPosition.y * m_fProgress);
			}
		}

		if (m_pLightMap)
		{
			m_pLightMap->SetPosition(TMVector2{ m_vecPosition.x, m_vecPosition.z });
		}
	}
	break;
	case 9:
	{
		float fAng = (float)(dwServerTime % 2000) / 2000.0f;

		float fSin = sinf((float)(fAng * 3.1415927f) * 2.0f);
		float fCos = cosf((float)(fAng * 3.1415927f) * 2.0f);

		m_vecPosition.x = (fSin * m_fParticleH) + m_vecPosition.x;
		m_vecPosition.y = (fCos * m_fParticleV) + m_vecPosition.y;
		m_vecPosition.z = (fCos * m_fParticleH) + m_vecPosition.z;
	}
	break;
	case 10:
		m_vecPosition.x = (m_fProgress * m_fParticleH) + m_vecStartPos.x;
		m_vecPosition.y = (m_fProgress * m_fParticleV) + m_vecStartPos.y;
		break;
	case 11:
		m_vecPosition.x = (m_fProgress * m_fParticleH) + m_vecStartPos.x;
		m_vecPosition.z = (m_fProgress * m_fParticleH) + m_vecStartPos.z;
		m_vecPosition.y = (m_fProgress * m_fParticleV) + m_vecStartPos.y;
		break;
	case 12:
		if (m_fProgress >= 0.2f)
			m_vecPosition = (m_vecStartPos + ((m_vecDir * 0.2f) * 10.0f)) + ((m_vecDir * m_fProgress) * 0.30000001f);
		else
			m_vecPosition = m_vecStartPos + ((m_vecDir * m_fProgress) * 10.0f);
		break;
	case 13:
		m_fRotAxisAngle = (m_fProgress * 0.1f) * 3.1415927f;
		break;
	case 14:
		m_fRotAxisAngle = (-m_fProgress * 0.1f) * 3.1415927f;
		break;
	case 15:
	{
		auto fSin = sinf((((float)(timespent % 2000) / 2000.0f) * 3.1415927f) * 2.0f);
		auto fCos = cosf((((float)(timespent % 2000) / 2000.0f) * 3.1415927f) * 2.0f);

		m_vecPosition.x += (fSin * m_fParticleH);
		m_vecPosition.y += (fCos * m_fParticleV);
		m_vecPosition.z += (fCos * m_fParticleH);
	}
	break;
	case 16:
		m_vecPosition = m_vecStartPos + ((m_vecDir * m_fProgress) * 5.0f);
		break;
	}

	if (IsVisible() == 1)
	{
		D3DXMATRIX matTrans{};
		D3DXMATRIX matScale{};

		if (m_bLookCam == 1)
		{
			float fAngle = -g_pObjectManager->m_pCamera->m_fVerticalAngle;
			float fHAngle = g_pObjectManager->m_pCamera->m_fHorizonAngle;

			TMVector3 vecScale{ m_vecScale };

			if (m_dwLifeTime)
			{
				vecScale.x = ((float)(dwServerTime - m_dwCreateTime) * m_fScaleVelX) + m_vecScale.x;
				vecScale.y = ((float)(dwServerTime - m_dwCreateTime) * m_fScaleVelY) + m_vecScale.y;
				vecScale.z = ((float)(dwServerTime - m_dwCreateTime) * m_fScaleVelZ) + m_vecScale.z;
			}

			if (m_nAnimationType == 1)
			{
				float fSin = sinf(((float)(dwServerTime % 0x7D0) / 2000.0f) * 3.1415927f);
				float fSinScale = fSin * 0.2f;

				vecScale.x += fSinScale;
				vecScale.y += fSinScale;

				DWORD dwOneColor = 255 - (unsigned int)(155.0f * fSin);

				DWORD dwColor = dwOneColor | (dwOneColor << 24) | (dwOneColor << 16) | (dwOneColor << 8);

				for (int m = 0; m < 4; ++m)
					m_vertex[m].diffuse = dwColor;

				m_dwA = dwOneColor;
				m_dwR = dwOneColor;
				m_dwG = dwOneColor;
				m_dwB = dwOneColor;
			}
			else if (m_nAnimationType == 2 || m_nAnimationType == 3)
			{
				float fTime = (float)(dwServerTime % 4000) / 4000.0f;

				float fSin = sinf(fTime * 3.1415927f);
				float fSinScale = fSin * 3.0f;

				vecScale.x += fSinScale;
				vecScale.y += fSinScale;

				DWORD dwOneColor = 255 - (unsigned int)(255.0f * fSin);

				DWORD dwColor = dwOneColor | (dwOneColor << 24) | (dwOneColor << 16) | (dwOneColor << 8);

				for (int n = 0; n < 4; ++n)
					m_vertex[n].diffuse = dwColor;

				m_dwA = dwOneColor;
				m_dwR = dwOneColor;
				m_dwG = dwOneColor;
				m_dwB = dwOneColor;

				if (fTime >= 0.99000001f && m_nAnimationType == 2)
					m_nAnimationType = 1;
			}

			D3DXMatrixIdentity(&m_matEffect);
			D3DXMatrixScaling(&matScale, vecScale.x, vecScale.y,vecScale.z);

			if (m_bStickGround == 1)
				D3DXMatrixTranslation(&matTrans, m_vecPosition.x, m_vecPosition.y + (vecScale.y / 2.0f), m_vecPosition.z);
			else
				D3DXMatrixTranslation(&matTrans, m_vecPosition.x, m_vecPosition.y, m_vecPosition.z);

			if (!m_nAnimationType)
			{
				D3DXMatrixRotationX(&m_matEffect, fAngle);
				D3DXMatrixRotationYawPitchRoll(&m_matEffect, (1.5707964f - fHAngle), fAngle, m_fAxisAngle);
			}

			D3DXMatrixMultiply(&m_matEffect, &m_matEffect, &matScale);
			D3DXMatrixMultiply(&m_matEffect, &m_matEffect, &matTrans);
		}
		else
		{
			TMVector3 vecScale{ m_vecScale };

			if (m_dwLifeTime)
			{
				vecScale.x = (((float)dwServerTime - m_dwCreateTime) * m_fScaleVelX) + m_vecScale.x;
				vecScale.y = (((float)dwServerTime - m_dwCreateTime) * m_fScaleVelY) + m_vecScale.y;
				vecScale.z = (((float)dwServerTime - m_dwCreateTime) * m_fScaleVelZ) + m_vecScale.z;
			}

			D3DXMatrixIdentity(&m_matEffect);
			D3DXMatrixScaling(&matScale, vecScale.x, vecScale.y, vecScale.z);

			if (m_bStickGround == 1)
				D3DXMatrixTranslation(&matTrans, m_vecPosition.x, m_vecPosition.y + (vecScale.y / 2.0f), m_vecPosition.z);
			else
				D3DXMatrixTranslation(&matTrans, m_vecPosition.x, m_vecPosition.y, m_vecPosition.z);

			D3DXMatrixRotationY(&m_matEffect, m_fAxisAngle);

			if (m_nParticleType == 14 || m_nParticleType == 15)
			{
				D3DXMATRIX matAxisRot{};

				D3DXMatrixRotationAxis(&matAxisRot, (D3DXVECTOR3*)&m_vecRotAxis, m_fRotAxisAngle);
				D3DXMatrixMultiply(&m_matEffect, &m_matEffect, &matAxisRot);
			}

			D3DXMatrixMultiply(&m_matEffect, &m_matEffect, &matScale);
			D3DXMatrixMultiply(&m_matEffect, &m_matEffect, &matTrans);
		}
	}

	return 1;
}

void TMEffectBillBoard::SetLifeTime(unsigned int dwLifeTime)
{
	m_dwLifeTime = dwLifeTime;
}

void TMEffectBillBoard::SetLightMap(unsigned int dwColor, int nSize)
{
	if (m_pLightMap)
	{
		delete m_pLightMap;

		m_pLightMap = nullptr;
	}

	m_pLightMap = new TMShade(nSize, 7, 1.0f);

	if (m_pLightMap)
	{
		m_pLightMap->SetColor(dwColor);
		m_pLightMap->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;

		g_pCurrentScene->m_pEffectContainer->AddChild(static_cast<TreeNode*>(m_pLightMap));
	}
}
