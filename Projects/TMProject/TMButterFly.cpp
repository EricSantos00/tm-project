#include "pch.h"
#include "TMButterFly.h"
#include "TMSkinMesh.h"
#include "TMGlobal.h"
#include "TMCamera.h"

TMButterFly::TMButterFly(int nType, int nBD, TMObject* pOwner)
{
	int nRand = rand() % 100;

	m_dwObjType = nType;
	m_nMotionType = nRand % 3;
	m_dwStartTime = 0;
	m_nBD = nBD;
	m_pSkinMesh = nullptr;
	m_nSkinMeshType = 69;

	if (nType == 7)
	{
		m_nSkinMeshType = 24;
		m_nMotionType = 3;
	}

	m_pOwner = pOwner;

	memset(&m_stLookInfo, 0, sizeof LOOK_INFO);
	memset(&m_stSancInfo.Sanc0, 0, sizeof SANC_INFO);

	if (m_nBD)
	{
		switch (m_nBD)
		{
		case 1:
			m_stLookInfo.Skin0 = rand() % 2 + 3;
			break;
		case 2:
			m_stLookInfo.Skin0 = 2;
			break;
		case 3:
			m_stLookInfo.Skin0 = 5;
			break;
		default:
			m_stLookInfo.Skin0 = 6;
			break;
		}
	}
	else
		m_stLookInfo.Skin0 = rand() % 3;

	m_fCircleSpeed = static_cast<float>(nRand) * 0.1f + 1.0f;
	m_fParticleH = static_cast<float>(nRand) * 0.5f + 3.0f;
	m_fParticleH = static_cast<float>(nRand) * 0.05f + 0.2f;
}

TMButterFly::~TMButterFly()
{
}

int TMButterFly::InitObject()
{
	if (!m_pSkinMesh)
	{
		m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, 0, 0, 0, 0);

		if (m_pSkinMesh)
		{
			m_pSkinMesh->RestoreDeviceObjects();

			if (m_nBD == 1)
			{
				if (m_stLookInfo.Skin0 == 3)
				{
					m_pSkinMesh->m_vScale.x = 1.0f;
					m_pSkinMesh->m_vScale.y = 1.0f;
					m_pSkinMesh->m_vScale.z = 1.0f;
				}
				else
				{
					m_pSkinMesh->m_vScale.x = 0.69f;
					m_pSkinMesh->m_vScale.y = 0.69f;
					m_pSkinMesh->m_vScale.z = 0.69f;
				}
				m_pSkinMesh->m_dwFPS = 10;
			}
			else if (m_nBD == 2)
			{
				m_pSkinMesh->m_dwFPS = 4;
				m_pSkinMesh->m_vScale.x = 0.2f;
				m_pSkinMesh->m_vScale.y = 0.2f;
				m_pSkinMesh->m_vScale.z = 0.2f;
			}
			else
			{
				if (m_nBD == 3)
					m_pSkinMesh->m_dwFPS = 8;
				else
					m_pSkinMesh->m_dwFPS = 15;
				m_pSkinMesh->m_vScale.x = 0.5f;
				m_pSkinMesh->m_vScale.y = 0.5f;
				m_pSkinMesh->m_vScale.z = 0.5f;
			}
		}
	}

	return 1;
}

int TMButterFly::Render()
{
	if (m_dwKey != -1
		&& m_dwKey != TreeNode::m_VisualKey1
		&& m_dwKey != TreeNode::m_VisualKey2
		&& m_dwKey != TreeNode::m_VisualKey3
		&& m_dwKey != TreeNode::m_VisualKey4)
	{
		return 0;
	}
	if (m_pSkinMesh && m_bVisible == 1)
	{
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
		if (m_nBD > 0)
		{
			g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
			g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
			g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
			g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
			g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
		}
		if (m_nBD == 2)
			g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
		if (g_pDevice->m_dwBitCount == 32)
			g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xAAu);
		else
			g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xFFu);

		m_pSkinMesh->Render(0.0f, 1.0f, 0.0f);
		if (m_nBD == 1)
		{
			g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
			g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
			g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
			g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
		}
		if (m_nBD == 2)
			g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
	}

	return 1;
}

int TMButterFly::FrameMove(unsigned int dwServerTime)
{
	if (m_dwKey != -1 && m_dwKey != TreeNode::m_VisualKey1 && m_dwKey != TreeNode::m_VisualKey2 && m_dwKey != TreeNode::m_VisualKey3 && m_dwKey != TreeNode::m_VisualKey4)
	{
		m_bVisible = 0;

		return 0;
	}

	dwServerTime = g_pTimerManager->GetServerTime();

	if (m_pSkinMesh)
	{
		float fProgress = fabsf(sinf((static_cast<float>((dwServerTime - m_dwStartTime) % 20000) / 20000.0f) * D3DXToRadian(180)));
		if (m_nMotionType)
		{
			switch (m_nMotionType)
			{
			case 1:
			{
				float fCos = cosf((fProgress * D3DXToRadian(180)) * m_fCircleSpeed);
				float fCos2 = cosf(((fProgress * 6.0f) * D3DXToRadian(180)) * m_fCircleSpeed);

				float vecPositionY = 0.0f; //v9
				if (m_pOwner)
				{
					m_fHeight = ((fCos2 * m_fParticleV) + m_pOwner->m_fHeight) + 1.5f;
					m_vecPosition.x = fCos * m_fParticleH * 0.5f + m_pOwner->m_vecPosition.x;
					vecPositionY = fProgress * m_fParticleH * 0.5f + m_pOwner->m_vecPosition.y;
				}
				else
				{
					m_fHeight = fCos2 * m_fParticleV + m_vecStartPos.y;
					m_vecPosition.x = ((fCos * m_fParticleH) * 0.5f) + m_vecStartPos.x;
					vecPositionY = fProgress * m_fParticleH * 0.5f + m_vecStartPos.z;
				}

				m_vecPosition.y = vecPositionY;
			}
			break;
			case 2:
			{
				float fSin = sinf((fProgress * 2.0f) * D3DXToRadian(180));
				float fCos2 = cosf((fProgress * 2.0f) * D3DXToRadian(180));
				float fCos3 = cosf(((fProgress * 6.0f) * D3DXToRadian(180)) * m_fCircleSpeed);

				float vecPositionY = 0.0f; // v10
				if (m_pOwner)
				{
					m_fHeight = fCos3 * m_fParticleV + m_pOwner->m_fHeight + 2.0f;
					m_vecPosition.x = fProgress * fCos2 * m_fParticleH * 0.5f + m_pOwner->m_vecPosition.x;
					vecPositionY = fProgress * fSin * m_fParticleH * 0.5f + m_pOwner->m_vecPosition.y;
				}
				else
				{
					m_fHeight = fCos3 * m_fParticleV + m_vecStartPos.y;
					m_vecPosition.x = fProgress * fCos2 * m_fParticleH * 0.5f + m_vecStartPos.x;
					vecPositionY = fProgress * fSin * m_fParticleH * 0.5f + m_vecStartPos.z;
				}

				m_vecPosition.y = vecPositionY;
			}
			break;
			case 3:
			{
				float fProgress = static_cast<float>((dwServerTime - m_dwStartTime) % 7000) / 7000.0f;
				float fDir = 1.0f;

				if (fProgress < 0.0099999998f && !(rand() % 2))
					fDir = -1.0f;

				float fSin = sinf(((fDir * fProgress) * 2.0f) * D3DXToRadian(180));
				float fCos = cosf(((fDir * fProgress) * 2.0f) * D3DXToRadian(180));

				float vecPositionY = 0.0f;
				if (m_pOwner)
				{
					m_fHeight = fCos * m_fParticleV + m_pOwner->m_fHeight + 2.0f;
					m_vecPosition.x = fProgress * fCos * m_fParticleH * 0.5f + m_pOwner->m_vecPosition.x;
					vecPositionY = fProgress * fSin * m_fParticleH * 0.5f + m_pOwner->m_vecPosition.y;
				}
				else
				{
					m_fHeight = fCos * m_fParticleV * 0.5f + m_vecStartPos.y;
					m_vecPosition.x = fCos * m_fParticleH * 0.5f + m_vecStartPos.x;
					vecPositionY = fSin * m_fParticleH * 0.5f + m_vecStartPos.z;
				}

				m_vecPosition.y = vecPositionY;
			}
			break;
			}
		}
		else
		{
			float fSin = sinf((fProgress * D3DXToRadian(180)) * m_fCircleSpeed);
			float fSin2 = sinf(((fProgress * 6.0f) * D3DXToRadian(180)) * m_fCircleSpeed);

			float vecPositionY = 0.0f;
			if (m_pOwner)
			{
				m_fHeight = fSin2 * m_fParticleV + m_pOwner->m_fHeight + 1.5f;
				m_vecPosition.x = fProgress * m_fParticleH * 0.5f + m_pOwner->m_vecPosition.x;
				vecPositionY = fSin * m_fParticleH * 0.5f + m_pOwner->m_vecPosition.y;
			}
			else
			{
				m_fHeight = fSin2 * m_fParticleV + m_vecStartPos.y;
				m_vecPosition.x = fProgress * m_fParticleH * 0.5f + m_vecStartPos.x;
				vecPositionY = fSin * m_fParticleH * 0.5f + m_vecStartPos.z;
			}

			m_vecPosition.y = vecPositionY;
		}

		SetPosition(m_vecPosition.x, m_fHeight, m_vecPosition.y);

		if (IsVisible())
		{
			float fDis = g_pObjectManager->m_pCamera->m_vecCamPos.DistanceFrom(m_vecPosition);

			if (fDis < 2.0f && m_nSkinMeshType == 24 && g_pSoundManager && g_pSoundManager->GetSoundData(5))
			{
				auto soundData = g_pSoundManager->GetSoundData(5);
				if (!soundData->IsSoundPlaying())
					soundData->Play(0, 0);
			}

			float color = (float)(g_pDevice->m_colorLight.r * 0.30000001f) + 0.69999999f;
			float color_4 = (float)(g_pDevice->m_colorLight.g * 0.30000001f) + 0.69999999f;
			float color_8 = (float)(g_pDevice->m_colorLight.b * 0.30000001f) + 0.69999999f;

			m_pSkinMesh->m_materials.Ambient.r = 0.0f;
			m_pSkinMesh->m_materials.Ambient.g = 0.0f;
			m_pSkinMesh->m_materials.Ambient.b = 0.0f;
			m_pSkinMesh->m_materials.Diffuse.r = color;
			m_pSkinMesh->m_materials.Diffuse.g = color_4;
			m_pSkinMesh->m_materials.Diffuse.b = color_8;
			m_pSkinMesh->m_materials.Diffuse.a = 0;

			m_pSkinMesh->m_materials.Specular.r = 1.0f;
			m_pSkinMesh->m_materials.Specular.g = 1.0f;
			m_pSkinMesh->m_materials.Specular.b = 1.0f;

			m_pSkinMesh->m_materials.Emissive.r = (float)(g_pDevice->m_colorBackLight.r * 0.40000001f) + (float)(color * 0.40000001f);
			m_pSkinMesh->m_materials.Emissive.g = (float)(g_pDevice->m_colorBackLight.g * 0.40000001f) + (float)(color * 0.40000001f);
			m_pSkinMesh->m_materials.Emissive.b = (float)(g_pDevice->m_colorBackLight.b * 0.40000001f) + (float)(color * 0.40000001f);

			m_pSkinMesh->FrameMove(dwServerTime + static_cast<unsigned int>(((m_fParticleH * 10.0f) + (m_fParticleV * 100.0f) + 5 * m_nMotionType)));
		}

		return 1;
	}
	else
		m_bVisible = 0;

	return 0;
}

void TMButterFly::RestoreDeviceObjects()
{
	if (!m_pSkinMesh)
		m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, nullptr, 0, 0, 0);

	if (m_pSkinMesh)
		m_pSkinMesh->RestoreDeviceObjects();
}

void TMButterFly::InvalidateDeviceObjects()
{
	if (m_pSkinMesh)
		m_pSkinMesh->InvalidateDeviceObjects();
}

void TMButterFly::InitPosition(float fX, float fY, float fZ)
{
	TMObject::InitPosition(fX, fY, fZ);

	m_vecStartPos.x = fX;
	m_vecStartPos.y = fY;
	m_vecStartPos.z = fZ;

	m_dwStartTime = g_pTimerManager->GetServerTime();
}

void TMButterFly::SetAnimation(int nAniIndex)
{
	if (m_pSkinMesh)
		m_pSkinMesh->SetAnimation(nAniIndex);
}
