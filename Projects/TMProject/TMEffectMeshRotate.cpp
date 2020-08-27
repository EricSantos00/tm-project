#include "pch.h"
#include "TMObject.h"
#include "TMEffectBillBoard.h"
#include "TMEffectMeshRotate.h"
#include "TMMesh.h"
#include "TMGlobal.h"

TMEffectMeshRotate::TMEffectMeshRotate(TMVector3 vecPosition, int nType, TMObject* pOwner, int bFire, int bCenter) :
	m_vecStartPos{ vecPosition }
{
	m_nType = nType;
	m_fRadius = 1.0f;
	m_fScale = 1.0f;

	if (m_nType == 1)
		m_dwRotateTime = 2000;
	else
		m_dwRotateTime = 1000;

	m_bScale = 0;
	m_vecPosition = m_vecStartPos;

	m_dwStartTime = 100 * ((unsigned int)this % 10) + g_pTimerManager->GetServerTime();
	if (m_nType == 2)
		m_dwStartTime = g_pTimerManager->GetServerTime();
	m_pOwner = pOwner;
	m_bCenter = bCenter;
	m_nMeshIndex = -1;
	m_pBillBoard = 0;
	m_dwLifeTime = 0;

	if (bFire == 1)
	{
		if (m_nType == 0)
		{
			m_pBillBoard = new TMEffectBillBoard(11, 0, 0.80000001f, 1.0f, 0.80000001f, 0.0f, 8, 80);

			if (m_pBillBoard)
			{
				m_pBillBoard->SetColor(0xFF440000);
				m_pBillBoard->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				m_pBillBoard->m_nFade = 0;
				m_pBillBoard->m_vecPosition = m_vecStartPos;
				g_pCurrentScene->m_pEffectContainer->AddChild(m_pBillBoard);
			}
		}
		else if (m_nType == 1)
		{
			m_pBillBoard = new TMEffectBillBoard(56, 0, 1.5f, 1.5f, 1.5f, 0.0f, 1, 80);

			if (m_pBillBoard)
			{
				m_pBillBoard->SetColor(0xFF55AAFF);
				m_pBillBoard->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				m_pBillBoard->m_nFade = 2;
				m_pBillBoard->m_vecPosition = m_vecStartPos;
				g_pCurrentScene->m_pEffectContainer->AddChild(m_pBillBoard);
			}
		}
	}

	m_fAngle2 = 0.0f;
	SetColor(0xFFFFFFFF);
}

TMEffectMeshRotate::~TMEffectMeshRotate()
{
	if (m_pBillBoard != nullptr)
		g_pObjectManager->DeleteObject(m_pBillBoard);
}

int TMEffectMeshRotate::Render()
{
	if (g_bHideEffect == 1)
		return 1;
	if (!m_bVisible)
		return 0;

	TMMesh* pMesh{};

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);

	if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_BRIGHT)
	{
		pMesh = g_pMeshManager->GetCommonMesh(m_nMeshIndex, 1, 180000);

		if (pMesh == nullptr)
			return 0;

		g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);

		RDLVERTEX* pVertex;
		D3DVERTEXBUFFER_DESC vDesc;

		pMesh->m_pVB->GetDesc(&vDesc);
		pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);

		int nCount = vDesc.Size / 24;

		float fAlpha = 1.0f;

		if (m_nType == 1)
			fAlpha = 1.0f;
		else
			fAlpha = sinf(m_fScale * 3.1415927f);

		unsigned int dwA = (unsigned int)((float)m_dwA * fAlpha);
		unsigned int dwR = (unsigned int)((float)m_dwR * fAlpha);
		unsigned int dwG = (unsigned int)((float)m_dwG * fAlpha);
		unsigned int dwB = (unsigned int)((float)m_dwB * fAlpha);
		unsigned int dwColor = dwB | (dwG << 8) | (dwR << 16) | (dwA << 24);

		for (int i = 0; i < nCount; ++i)
			pVertex[i].diffuse = dwColor;

		pMesh->m_pVB->Unlock();
	}
	else
	{
		pMesh = g_pMeshManager->GetCommonMesh(m_nMeshIndex, 0, 180000);

		if (pMesh == nullptr)
			return 0;

		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
		g_pDevice->SetRenderState(D3DRS_FOGENABLE, g_pDevice->m_bFog);

		D3DCOLORVALUE color = g_pCurrentScene->GroundGetColor(TMVector2{ m_vecPosition.x, m_vecPosition.z });
		color.r = (0.2f * color.r) + (g_pDevice->m_colorLight.r * 0.30000001f);
		color.g = (0.2f * color.r) + (g_pDevice->m_colorLight.g * 0.30000001f);
		color.b = (0.2f * color.r) + (g_pDevice->m_colorLight.b * 0.30000001f);
		color.a = 1.0f;

		_D3DMATERIAL9 materials{};
		materials.Ambient.r = color.r;
		materials.Ambient.g = color.g;
		materials.Ambient.b = color.b;
		materials.Ambient.a = color.a;
		materials.Diffuse.r = color.r;
		materials.Diffuse.g = color.g;
		materials.Diffuse.b = color.b;
		materials.Diffuse.a = color.a;
		materials.Emissive.r = color.r;
		materials.Emissive.g = color.g;
		materials.Emissive.b = color.b;
		materials.Emissive.a = color.a;
		materials.Specular.r = 1.0f;
		materials.Specular.g = 1.0f;
		materials.Specular.b = 1.0f;
		g_pDevice->m_pd3dDevice->SetMaterial(&materials);
	}

	if (pMesh == nullptr)
		return 0;

	pMesh->m_fScaleV = m_fScale;
	pMesh->m_fScaleH = m_fScale;

	if (m_nType == 1)
		pMesh->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, m_fAngle, m_fAngle2, 1.5707964f, 0, 0);
	else
		pMesh->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, m_fAngle, 0, 1.5707964f, 0, 0);

	return 1;
}

int TMEffectMeshRotate::FrameMove(unsigned int dwServerTime)
{
	if (g_bHideEffect == 1)
		return 1;
	if (!m_bVisible)
		return 0;

	dwServerTime = g_pTimerManager->GetServerTime();

	IsVisible();

	float fProgress = (float)((m_dwStartTime - dwServerTime) % m_dwRotateTime) / (float)m_dwRotateTime;
	float fAngle = (fProgress * 3.1415927f) * 2.0f;

	if (m_nType == 1 && m_pOwner)
	{
		m_fAngle = m_pOwner->m_fAngle;
		m_fAngle2 = 0.0f;
	}
	else
	{
		m_fAngle = fAngle * 2.0f;
	}
	if (m_nType == 2)
		fProgress = (float)(dwServerTime - m_dwStartTime) / (float)m_dwLifeTime;

	if (m_pOwner)
	{
		if (m_bCenter)
		{
			m_vecPosition.x = m_pOwner->m_vecPosition.x;
			m_vecPosition.z = m_pOwner->m_vecPosition.y;
			m_vecPosition.y = m_pOwner->m_fHeight;
		}
		else
		{
			m_vecPosition.x = (cosf(fAngle) * 1.0f) + m_pOwner->m_vecPosition.x;
			m_vecPosition.z =(sinf(fAngle) * 1.0f) + m_pOwner->m_vecPosition.y;
			m_vecPosition.y = m_pOwner->m_fHeight + 1.0f;
		}
	}
	else
	{
		if (m_bCenter)
		{
			m_vecPosition.x = m_vecStartPos.x;
			m_vecPosition.z = m_vecStartPos.z;
		}
		else
		{
			m_vecPosition.x = (cosf(fAngle) * 1.0f) + m_vecStartPos.x;
			m_vecPosition.z = (sinf(fAngle) * 1.0f) + m_vecStartPos.z;
		}
		m_vecPosition.y = m_vecStartPos.y;
	}

	if (m_pBillBoard)
	{
		m_pBillBoard->m_vecPosition = m_vecPosition;

		if (m_nType != 1)
			m_pBillBoard->m_vecPosition.y += 0.2f;
	}
	if (m_bScale == 1)
		m_fScale = (sinf(fAngle) * 0.1f) + 0.69999999f;
	
	switch (m_nType)
	{
	case 1:
	{
		int nRand = rand() % 5;

		auto pEffect = new TMEffectBillBoard(
			0,
			800,
			((float)nRand * 0.050000001f) + 0.02f,
			((float)nRand * 0.1f) + 0.02f,
			((float)nRand * 0.050000001f) + 0.02f,
			0.00050000002f,
			1,
			80);

		if (pEffect)
		{
			pEffect->m_vecStartPos = pEffect->m_vecPosition = m_vecPosition;
			pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			pEffect->m_bStickGround = 0;
			pEffect->m_nParticleType = 1;
			pEffect->m_fParticleV = 0.0f;
			pEffect->SetColor(0x0FF6688AA);
			g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
		}
	}
	break;
	case 2:
	{
		if (fProgress > 1.0)
		{
			g_pObjectManager->DeleteObject(this);
			return 1;
		}
		int nRand = rand() % 20 + 5;

		auto pEffect = new TMEffectBillBoard(
			0,
			900,
			(float)nRand * 0.2f,
			(float)nRand * 0.2f,
			(float)nRand * 0.2f,
			0.00050000002f,
			1,
			80);

		if (pEffect)
		{
			pEffect->m_vecStartPos = pEffect->m_vecPosition = m_vecPosition;
			pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			pEffect->m_bStickGround = 0;
			pEffect->m_nParticleType = 3;
			pEffect->m_fParticleV = 2.0f;
			pEffect->SetColor(0xFF6677CC);
			g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
		}
	}
	break;
	case 3:
	{
		if (fProgress > 1.0)
		{
			g_pObjectManager->DeleteObject(this);
			return 1;
		}
		int nRand = rand() % 20 + 3;

		auto pEffect = new TMEffectBillBoard(
			0,
			1500,
			(float)nRand * 0.2f,
			(float)nRand * 0.2f,
			(float)nRand * 0.2f,
			0.0000099999997f,
			1,
			80);

		if (pEffect)
		{
			m_vecPosition.y -= 0.80000001f;
			pEffect->m_vecStartPos = pEffect->m_vecPosition = m_vecPosition;
			pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
			pEffect->m_bStickGround = 0;
			pEffect->m_nParticleType = 3;
			pEffect->m_fParticleH = 1.0f;
			pEffect->m_fParticleV = 5.0f;
			pEffect->SetColor(0xFFFF0000);
			g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
		}
	}
	break;
	}

	return 1;
}

void TMEffectMeshRotate::SetColor(unsigned int dwColor)
{
	m_dwA = (dwColor & 0xFF000000) >> 24;
	m_dwR = (dwColor & 0xFF0000) >> 16;
	m_dwG = (dwColor & 0xFF00) >> 8;
	m_dwB = static_cast<unsigned char>(dwColor);
}
