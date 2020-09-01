#include "pch.h"
#include "TMSkillMagicShield.h"
#include "TMObject.h"
#include "TMHuman.h"
#include "TMGlobal.h"
#include "TMMesh.h"

TMSkillMagicShield::TMSkillMagicShield(TMObject* pParent, int nType)
	:TMEffect()
{
	m_bView = 0;
	m_dwVisibleTime = 1000;
	m_fAngle = 0.0f;
	m_fProgress = 0.0f;
	m_fCancelScale = 1.0f;
	m_pOwner = pParent;

	if (m_pOwner)
		m_vecPosition = { m_pOwner->m_vecPosition.x, m_pOwner->m_fHeight, m_vecPosition.y };
	else
		m_vecPosition = TMVector3{};

	m_nType = nType;
	m_fVectorH = 0.0f;
	SetColor(0xFFFFFFFF);
	m_dwStartTime = g_pTimerManager->GetServerTime();
}

TMSkillMagicShield::~TMSkillMagicShield()
{
}

int TMSkillMagicShield::Render()
{
	if (g_bHideEffect == 1)
		return 1;

	if (m_fProgress < 0.050000001)
		return 1;

	if (!m_bView)
		return 1;

	if (!m_bVisible)
		return 1;

	if (m_nType == 4)
	{
		auto pMesh1 = g_pMeshManager->GetCommonMesh(501, 1, 180000u);
		auto pMesh2 = g_pMeshManager->GetCommonMesh(502, 1, 180000u);

		if (!pMesh1 || !pMesh2)
			return 0;

		pMesh2->m_nTextureIndex[0] = 202;
		pMesh1->m_nTextureIndex[0] = 202;

		g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);

		float fScale = m_fCancelScale;

		auto pOwner = static_cast<TMHuman*>(m_pOwner);
		if (m_pOwner && m_pOwner->m_dwObjType == 3 && pOwner->m_cMount == 1)
			fScale = 1.0f;

		pMesh1->m_fScaleH = 1.3f * fScale;
		pMesh2->m_fScaleH = 1.3f * fScale;

		pMesh1->Render(
			m_vecPosition.x - 0.5f,
			(m_fVectorH + 0.60000002f) * fScale + m_vecPosition.y,
			m_vecPosition.z,
			D3DXToRadian(-30),
			D3DXToRadian(-30),
			D3DXToRadian(180) - m_fAngle,
			0,
			0);

		pMesh2->Render(
			m_vecPosition.x,
			(m_fVectorH + 0.60000002f) * fScale + m_vecPosition.y,
			m_vecPosition.z,
			D3DXToRadian(-30),
			D3DXToRadian(-30),
			D3DXToRadian(180) - m_fAngle,
			0,
			0);

		g_pDevice->SetRenderState(D3DRS_FOGENABLE, g_pDevice->m_bFog);
		g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
	}
	else
	{
		auto pMesh1 = g_pMeshManager->GetCommonMesh(704, 1, 180000u);
		auto pMesh2 = g_pMeshManager->GetCommonMesh(705, 1, 180000u);

		if (!pMesh1 || !pMesh2)
			return 0;

		if (m_nType)
		{
			if (m_nType == 1)
			{
				pMesh2->m_nTextureIndex[0] = 45;
				pMesh1->m_nTextureIndex[0] = 45;
			}
			else if (m_nType == 2)
			{
				pMesh2->m_nTextureIndex[0] = 99;
				pMesh1->m_nTextureIndex[0] = 99;
			}
			else if (m_nType == 3)
			{
				pMesh2->m_nTextureIndex[0] = 99;
				pMesh1->m_nTextureIndex[0] = 99;
			}
		}
		else
		{
			pMesh2->m_nTextureIndex[0] = 57;
			pMesh1->m_nTextureIndex[0] = 57;
		}

		g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);

		float fScale = 1.0f;

		auto pOwner = static_cast<TMHuman*>(m_pOwner);
		if (m_pOwner && m_pOwner->m_dwObjType == 3 && pOwner->m_cMount == 1)
			fScale = 1.5f;

		pMesh1->m_fScaleH = 1.0f * fScale;
		pMesh2->m_fScaleH = 1.0f * fScale;

		pMesh1->Render(
			m_vecPosition.x,
			(float)(m_fVectorH * fScale) + m_vecPosition.y,
			m_vecPosition.z,
			-m_fAngle,
			0,
			D3DXToRadian(90),
			0,
			0);

		pMesh2->Render(
			m_vecPosition.x,
			m_fVectorH * fScale + m_vecPosition.y,
			m_vecPosition.z,
			-m_fAngle,
			0,
			D3DXToRadian(90),
			0,
			0);

		pMesh1->m_fScaleH = 1.5f * fScale;
		pMesh2->m_fScaleH = 1.5f * fScale;

		pMesh1->Render(
			m_vecPosition.x,
			(m_vecPosition.y - 0.1f) + (m_fVectorH * fScale),
			m_vecPosition.z,
			-m_fAngle + D3DXToRadian(45),
			0,
			D3DXToRadian(90),
			0,
			0);

		pMesh2->Render(
			m_vecPosition.x,
			(m_vecPosition.y - 0.1f) + (m_fVectorH * fScale),
			m_vecPosition.z,
			-m_fAngle + D3DXToRadian(45),
			0,
			D3DXToRadian(90),
			0,
			0);

		pMesh1->m_fScaleH = 2.0f * fScale;
		pMesh2->m_fScaleH = 2.0f* fScale;

		pMesh1->Render(
			m_vecPosition.x,
			(m_vecPosition.y - 0.2f) + (m_fVectorH * fScale),
			m_vecPosition.z,
			-m_fAngle + D3DXToRadian(90),
			0,
			D3DXToRadian(90),
			0,
			0);

		pMesh2->Render(
			m_vecPosition.x,
			(m_vecPosition.y - 0.2f) + (m_fVectorH * fScale),
			m_vecPosition.z,
			-m_fAngle + D3DXToRadian(90),
			0,
			D3DXToRadian(90),
			0,
			0);

		pMesh1->m_fScaleH = 2.0f * fScale;
		pMesh2->m_fScaleH = 2.0f * fScale;

		pMesh1->Render(
			m_vecPosition.x,
			(m_vecPosition.y - 0.1f) + (m_fVectorH * fScale),
			m_vecPosition.z,
			-m_fAngle - D3DXToRadian(45),
			0,
			D3DXToRadian(90),
			0,
			0);
		pMesh2->Render(
			m_vecPosition.x,
			(m_vecPosition.y - 0.1f) + (m_fVectorH * fScale),
			m_vecPosition.z,
			-m_fAngle - D3DXToRadian(45),
			0,
			D3DXToRadian(90),
			0,
			0);

		pMesh1->m_fScaleH = 1.5f * fScale;
		pMesh2->m_fScaleH = 1.5f * fScale;

		pMesh1->Render(
			m_vecPosition.x,
			(m_vecPosition.y - 0.2f) + (m_fVectorH * fScale),
			m_vecPosition.z,
			-m_fAngle - D3DXToRadian(90),
			0,
			D3DXToRadian(90),
			0,
			0);
		pMesh2->Render(
			m_vecPosition.x,
			(m_vecPosition.y - 0.2f) + (m_fVectorH * fScale),
			m_vecPosition.z,
			-m_fAngle - D3DXToRadian(90),
			0,
			D3DXToRadian(90),
			0,
			0);

		g_pDevice->SetRenderState(D3DRS_FOGENABLE, g_pDevice->m_bFog);
		g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
	}

	return 1;
}

int TMSkillMagicShield::IsVisible()
{
	auto pMesh = g_pMeshManager->GetCommonMesh(704, 1, 180000u);

	if (pMesh)
		m_fRadius = pMesh->m_fRadius;
	else
		m_fRadius = 1.0f;

	return TMEffect::IsVisible();
}

void TMSkillMagicShield::SetColor(unsigned int dwColor)
{
	m_dwA = (dwColor & 0xFF000000) >> 24;
	m_dwR = ((unsigned int)0xFF0000 & dwColor) >> 16;
	m_dwG = (dwColor & 0xFF00) >> 8;
	m_dwB = (unsigned char)dwColor;
}

int TMSkillMagicShield::FrameMove(unsigned int dwServerTime)
{
	if (!m_bView)
		return 1;

	if (!IsVisible())
		return 0;

	m_fProgress = static_cast<float>(static_cast<int>(g_pTimerManager->GetServerTime() - m_dwStartTime)) / static_cast<float>(m_dwVisibleTime);

	if (m_fProgress > 1.0f)
	{
		m_bView = 0;
		m_bVisible = 0;

		return 1;
	}

	if (m_pOwner)
	{
		if (m_pOwner->m_dwObjType == 3)
		{
			auto pOwner = static_cast<TMHuman*>(m_pOwner);
			if (pOwner->m_cMount == 1)
				m_vecPosition = pOwner->m_vecSkinPos;
			else
				m_vecPosition = { m_pOwner->m_vecPosition.x, m_pOwner->m_fHeight, m_pOwner->m_vecPosition.y };
		}
		else
			m_vecPosition = { m_pOwner->m_vecPosition.x, m_pOwner->m_fHeight, m_pOwner->m_vecPosition.y };
	}

	IsVisible();

	if (m_fProgress <= 1.0f)
	{
		float fDif = fabsf(sinf(m_fProgress * D3DXToRadian(180)));

		if (m_nType == 2)
			m_vecPosition.y = m_vecPosition.y - 0.30000001f;
		
		if (m_nType == 3)
			m_vecPosition.y = m_vecPosition.y + fDif;

		auto nIndex1 = 704;
		auto nIndex2 = 705;

		if (m_nType == 4)
		{
			nIndex1 = 501;
			nIndex2 = 502;

			fDif *= 0.5f;
		}

		for (int i = 0; i < 2; ++i) // this loop is not original ok
		{
			int nMeshIndex = nIndex1;
			if (i == 1)
				nMeshIndex = nIndex2;

			auto pMesh = g_pMeshManager->GetCommonMesh(nMeshIndex, 1, 180000u);
			if (!pMesh || !pMesh->m_pVB)
				return 0;

			D3DVERTEXBUFFER_DESC vDesc;
			RDLVERTEX* pVertex;

			pMesh->m_pVB->GetDesc(&vDesc);
			pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);

			auto nCount = vDesc.Size / sizeof RDLVERTEX;

			for (size_t i = 0; i < nCount; ++i)
			{
				if (m_nType == 4)
				{
					auto dwA = static_cast<unsigned int>(static_cast<float>(m_dwA) * fDif) << 24;
					auto dwR = static_cast<unsigned int>(static_cast<float>(m_dwR) * fDif) << 16;
					auto dwG = static_cast<unsigned int>(static_cast<float>(m_dwG) * fDif) << 8;
					auto dwB = static_cast<unsigned int>(static_cast<float>(m_dwB) * fDif);

					pVertex[i].diffuse = dwB | dwG | dwR | dwA;
				}
				else
				{
					auto dwR = static_cast<unsigned int>(static_cast<float>(m_dwR) * fDif) << 16;
					auto dwG = static_cast<unsigned int>(static_cast<float>(m_dwG) * fDif) << 8;
					auto dwB = static_cast<unsigned int>(static_cast<float>(m_dwB) * fDif);

					pVertex[i].diffuse = dwB | dwG | dwR;
				}
			}

			pMesh->m_pVB->Unlock();
		}

		m_fAngle = (float)(m_fProgress * D3DXToRadian(180)) * 2.0f;
	}

	return 1;
}

void TMSkillMagicShield::StartVisible(unsigned int dwServerTime)
{
	m_dwStartTime = g_pTimerManager->GetServerTime();
	m_bView = 1;
}
