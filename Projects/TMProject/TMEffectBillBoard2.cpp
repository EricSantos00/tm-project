#include "pch.h"
#include "TMEffectBillBoard2.h"
#include "TMGlobal.h"
#include "TMObject.h"

TMEffectBillBoard2::TMEffectBillBoard2(int nTextureIndex, unsigned int dwLifeTime, float fScaleX, float fScaleY, float fScaleZ, float fVelocity, unsigned int dwVel) :
	TMEffect(),
	m_vecScale{}
{
	m_fAxisAngle = 0.0f;
	m_dwCreateTime = 0;
	m_fLocalHeight = 0.0f;
	m_fProgress = 0.0f;
	m_dwLifeTime = dwLifeTime;
	m_vecScale.x = fScaleX;
	m_vecScale.y = fScaleY;
	m_vecScale.z = fScaleZ;
	m_fScaleVel = fVelocity;
	m_dwRotVel = dwVel;
	m_nTextureIndex = nTextureIndex;
	m_nFade = 1;
	m_pOwner = 0;
	m_bSlope = 0;

	m_vecPosition = TMVector3{ 0.0f, 0.0f, 0.0f };

	m_vertex[0].position = TMVector3{ -0.5f, 0.0f, -0.5f };
	m_vertex[1].position = TMVector3{ 0.5f, 0.0f, -0.5f };
	m_vertex[2].position = TMVector3{ 0.5f, 0.0f, 0.5f };
	m_vertex[3].position = TMVector3{ -0.5f, 0.0f, 0.5f };

	m_vertex[0].tu = 0.02f;
	m_vertex[0].tv = 0.02f;
	m_vertex[1].tu = 0.98000002f;
	m_vertex[1].tv = 0.02f;
	m_vertex[2].tu = 0.98000002f;
	m_vertex[2].tv = 0.98000002f;
	m_vertex[3].tu = 0.02f;
	m_vertex[3].tv = 0.98000002f;

	SetColor(0xFFFFFFFF);
}

TMEffectBillBoard2::~TMEffectBillBoard2()
{
}

int TMEffectBillBoard2::Render()
{
	if (g_bHideEffect == 1 && m_nFade != 4)
		return 1;

	if (m_dwLifeTime && m_fProgress < 0.050000001)
		return 1;

	if (IsVisible() == 1)
	{
		if (!strlen(g_pTextureManager->m_stEffectTextureList[m_nTextureIndex].szFileName))
			return 0;

		g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLD, &m_matEffect);
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);

		if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_BRIGHT)
		{
			g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
		}
		else
		{
			g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
			g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
		}

		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
		g_pDevice->SetRenderState(D3DRS_CULLMODE, 2u);
		g_pDevice->m_pd3dDevice->SetFVF(322u);
		
		g_pDevice->SetTexture(0, g_pTextureManager->GetEffectTexture(m_nTextureIndex, 5000));

		g_pDevice->m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2u, m_vertex, 24u);

		g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
		g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);

		if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_BRIGHT)
			g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
	}
	return 1;
}

void TMEffectBillBoard2::SetColor(unsigned int dwColor)
{
	for (int i = 0; i < 4; ++i)
		m_vertex[i].diffuse = dwColor;

	m_dwA = (dwColor & 0xFF000000) >> 24;
	m_dwR = ((unsigned int)0xFF0000 & dwColor) >> 16;
	m_dwG = (dwColor & 0xFF00) >> 8;
	m_dwB = static_cast<unsigned char>(dwColor);
}

int TMEffectBillBoard2::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = g_pTimerManager->GetServerTime();

	if (!m_dwCreateTime)
		m_dwCreateTime = dwServerTime;

	int nTimeSpent{};

	if (dwServerTime < m_dwCreateTime)
		nTimeSpent = m_dwLifeTime;
	else
		nTimeSpent = dwServerTime - m_dwCreateTime;

	if (m_dwLifeTime && static_cast<int>(m_dwLifeTime) < nTimeSpent)
		g_pObjectManager->DeleteObject(static_cast<TreeNode*>(this));

	if (m_pOwner)
	{
		m_vecPosition.x = m_pOwner->m_vecPosition.x;
		m_vecPosition.z = m_pOwner->m_vecPosition.y;
		m_vecPosition.y = m_pOwner->m_fHeight + m_fLocalHeight;
	}

	if (m_dwLifeTime)
	{
		m_fProgress = (float)nTimeSpent / (float)m_dwLifeTime;
	}

	if (!m_dwLifeTime)
	{
		if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_BRIGHT)
		{
			m_fProgress = (float)((dwServerTime + (int)m_vecPosition.z + (int)m_vecPosition.x + 300 * ((unsigned int)this % 10)) % 1000) / 1000.0f;
		}
		else
		{
			m_fProgress = 0.30000001f;
		}
	}

	switch (m_nFade)
	{
	case 1:
	{
		DWORD dwA = (unsigned int)((float)m_dwA * fabsf(sinf(m_fProgress * D3DXToRadian(180))));
		DWORD dwR = (unsigned int)((float)m_dwR * fabsf(sinf(m_fProgress * D3DXToRadian(180))));
		DWORD dwG = (unsigned int)((float)m_dwG * fabsf(sinf(m_fProgress * D3DXToRadian(180))));
		DWORD dwB = (unsigned int)((float)m_dwB * fabsf(sinf(m_fProgress * D3DXToRadian(180))));

		for (int i = 0; i < 4; ++i)
		{
			m_vertex[i].diffuse = (unsigned int)(dwB | (dwG << 8) | (dwR << 16) | (dwA << 24));
		}
	}
	break;
	case 2:
	{
		float fVel = (float)((dwServerTime + 200 * ((unsigned int)this % 100)) % 5000) / 5000.0f;

		DWORD dwA = (unsigned int)(((0.2f * fabsf(sinf((fVel * D3DXToRadian(180)) * 2.0f))) + 0.80000001f) * (float)m_dwA);
		DWORD dwR = (unsigned int)(((0.2f * fabsf(sinf((fVel * D3DXToRadian(180)) * 2.0f))) + 0.80000001f) * (float)m_dwR);
		DWORD dwG = (unsigned int)(((0.2f * fabsf(sinf((fVel * D3DXToRadian(180)) * 2.0f))) + 0.80000001f) * (float)m_dwG);
		DWORD dwB = (unsigned int)(((0.2f * fabsf(sinf((fVel * D3DXToRadian(180)) * 2.0f))) + 0.80000001f) * (float)m_dwB);

		for (int j = 0; j < 4; ++j)
		{
			m_vertex[j].diffuse = (unsigned int)(dwB | (dwG << 8) | (dwR << 16) | (dwA << 24));
		}
	}
	break;
	case 3:
	case 4:
	{
		float fVel = (float)((dwServerTime + 200 * ((unsigned int)this % 100)) % 5000) / 5000.0f;

		DWORD dwA = (unsigned int)(((0.80000001f * fabsf(sinf((fVel * D3DXToRadian(180)) * 2.0f))) + 0.2f) * (float)m_dwA);
		DWORD dwR = (unsigned int)(((0.80000001f * fabsf(sinf((fVel * D3DXToRadian(180)) * 2.0f))) + 0.2f) * (float)m_dwR);
		DWORD dwG = (unsigned int)(((0.80000001f * fabsf(sinf((fVel * D3DXToRadian(180)) * 2.0f))) + 0.2f) * (float)m_dwG);
		DWORD dwB = (unsigned int)(((0.80000001f * fabsf(sinf((fVel * D3DXToRadian(180)) * 2.0f))) + 0.2f) * (float)m_dwB);

		for (int k = 0; k < 4; ++k)
		{
			m_vertex[k].diffuse = (unsigned int)(dwB | (dwG << 8) | (dwR << 16) | (dwA << 24));
		}
	}
	break;
	}

	if (m_dwRotVel)
	{
		m_fAxisAngle = ((float)(dwServerTime % m_dwRotVel) / (float)m_dwRotVel) * D3DXToRadian(360);
	}

	if (IsVisible() == 1)
	{
		D3DXMATRIX matTrans{};
		D3DXMATRIX matScale{};

		TMVector3 vecScale{ m_vecScale };

		if (m_dwLifeTime)
		{
			vecScale.x = ((float)(dwServerTime - m_dwCreateTime) * m_fScaleVel) + m_vecScale.x;
			vecScale.y = ((float)(dwServerTime - m_dwCreateTime) * m_fScaleVel) + m_vecScale.y;
			vecScale.z = ((float)(dwServerTime - m_dwCreateTime) * m_fScaleVel) + m_vecScale.z;
		}
		else if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_BRIGHT)
		{
			vecScale.x = ((m_fProgress * 500.0f) * m_fScaleVel) + m_vecScale.x;
			vecScale.y = ((m_fProgress * 500.0f) * m_fScaleVel) + m_vecScale.y;
			vecScale.z = ((m_fProgress * 500.0f) * m_fScaleVel) + m_vecScale.z;
		}

		D3DXMatrixIdentity(&m_matEffect);
		D3DXMatrixScaling(&matScale, vecScale.x, vecScale.y, vecScale.z);
		D3DXMatrixTranslation(&matTrans, m_vecPosition.x, m_vecPosition.y, m_vecPosition.z);
		D3DXMatrixRotationYawPitchRoll(&m_matEffect, m_fAxisAngle + 0.78539819f, 0, 0);
		D3DXMatrixMultiply(&m_matEffect, &m_matEffect, &matScale);
		D3DXMatrixMultiply(&m_matEffect, &m_matEffect, &matTrans);
	}
	return 1;
}

void TMEffectBillBoard2::SetLifeTime(unsigned int dwLifeTime)
{
	m_dwLifeTime = dwLifeTime;
}
