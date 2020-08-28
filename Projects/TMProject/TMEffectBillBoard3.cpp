#include "pch.h"
#include "TMEffectBillBoard3.h"
#include "TMGlobal.h"

TMEffectBillBoard3::TMEffectBillBoard3(TMVector3 vecStart, TMVector3 vecEnd, int nTextureIndex, unsigned int dwColor, unsigned int dwLifeTime, float fScaleH, float fScaleV) :
	m_vecStartPos{},
	m_vecEndPos{}
{
	m_fScaleH = fScaleH;
	m_fScaleV = fScaleV;
	m_nTextureIndex = nTextureIndex;
	m_dwLifeTime = dwLifeTime;
	m_nFade = 0;

	m_vertex1[0].position = TMVector3{ vecStart.x, vecStart.y - m_fScaleV, vecStart.z };
	m_vertex1[1].position = TMVector3{ vecEnd.x, vecEnd.y - m_fScaleV, vecEnd.z };
	m_vertex1[2].position = TMVector3{ vecEnd.x, vecEnd.y + m_fScaleV, vecEnd.z };
	m_vertex1[3].position = TMVector3{ vecStart.x, vecStart.y + m_fScaleV, vecStart.z };

	m_vertex1[0].tu = 0.02f;
	m_vertex1[0].tv = 0.98000002f;
	m_vertex1[1].tu = 0.98000002f;
	m_vertex1[1].tv = 0.98000002f;
	m_vertex1[2].tu = 0.98000002f;
	m_vertex1[2].tv = 0.02f;
	m_vertex1[3].tu = 0.02f;
	m_vertex1[3].tv = 0.02f;

	m_vertex2[0].position = TMVector3{ vecStart.x - m_fScaleV, vecStart.y, vecStart.z };
	m_vertex2[1].position = TMVector3{ vecEnd.x - m_fScaleV, vecEnd.y, vecEnd.z };
	m_vertex2[2].position = TMVector3{ vecEnd.x + m_fScaleV, vecEnd.y, vecEnd.z };
	m_vertex2[3].position = TMVector3{ vecStart.x + m_fScaleV, vecStart.y, vecStart.z };

	m_vertex2[0].tu = 0.02f;
	m_vertex2[0].tv = 0.98000002f;
	m_vertex2[1].tu = 0.98000002f;
	m_vertex2[1].tv = 0.98000002f;
	m_vertex2[2].tu = 0.98000002f;
	m_vertex2[2].tv = 0.02f;
	m_vertex2[3].tu = 0.02f;
	m_vertex2[3].tv = 0.02f;
	SetColor(dwColor);
	m_dwShortTime = 0;
	m_dwCreateTime = g_pTimerManager->GetServerTime();
}

TMEffectBillBoard3::~TMEffectBillBoard3()
{
}

int TMEffectBillBoard3::Render()
{
	if (g_bHideEffect == 1)
		return 1;

	if (!m_bVisible)
		return 0;

	if (!strlen(g_pTextureManager->m_stEffectTextureList[m_nTextureIndex].szFileName))
		return 0;

	D3DXMatrixIdentity(&m_matEffect);
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

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
	g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
	g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
	g_pDevice->m_pd3dDevice->SetFVF(322u);
	
	g_pDevice->SetTexture(0, g_pTextureManager->GetEffectTexture(m_nTextureIndex, 5000));
	g_pDevice->m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2u, m_vertex1, 24u);
	g_pDevice->m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2u, m_vertex2, 24u);
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

	return 1;
}

void TMEffectBillBoard3::SetColor(unsigned int dwColor)
{
	for (int i = 0; i < 4; ++i)
	{
		m_vertex1[i].diffuse = dwColor;
		m_vertex2[i].diffuse = dwColor;
	}
	m_dwA = (dwColor & 0xFF000000) >> 24;
	m_dwR = (dwColor & 0xFF0000) >> 16;
	m_dwG = (dwColor & 0xFF00) >> 8;
	m_dwB = static_cast<unsigned char>(dwColor);
}

int TMEffectBillBoard3::FrameMove(unsigned int dwServerTime)
{
	dwServerTime = g_pTimerManager->GetServerTime();

	m_vecPosition = m_vertex1[0].position;

	IsVisible();

	float fProgress = 0.0f;

	if (m_dwLifeTime)
		fProgress = (float)(dwServerTime - m_dwCreateTime) / (float)m_dwLifeTime;
	else
		fProgress = (float)(dwServerTime % 1000) / 1000.0f;
	
	if (m_dwLifeTime && (dwServerTime - m_dwCreateTime) > m_dwLifeTime)
	{
		m_bVisible = 0;
		g_pObjectManager->DeleteObject(this);
	}

	if (m_nFade == 1 && fProgress < 1.0f)
	{
		float fAlpha = sinf(fProgress * 3.1415927f);
		unsigned int dwA = (unsigned int)((float)m_dwA * fAlpha);
		unsigned int dwR = (unsigned int)((float)m_dwR * fAlpha);
		unsigned int dwG = (unsigned int)((float)m_dwG * fAlpha);
		unsigned int dwB = (unsigned int)((float)m_dwB * fAlpha);

		for (int i = 0; i < 4; ++i)
		{
			m_vertex1[i].diffuse = dwB | (dwG << 8) | (dwR << 16) | (dwA << 24);
			m_vertex2[i].diffuse = dwB | (dwG << 8) | (dwR << 16) | (dwA << 24);
		}
	}

	if (m_dwShortTime)
	{
		float fShort = (float)(dwServerTime - m_dwShortTime) / (float)(m_dwLifeTime + m_dwCreateTime - m_dwShortTime);
		
		TMVector3 vecStartPos{ m_vecPosition.x, m_vecPosition.y + m_fScaleV, m_vecPosition.z };
		TMVector3 vecEndPos
		{	m_vertex1[1].position.x,
			m_vertex1[1].position.y + m_fScaleV,
			m_vertex1[1].position.z 
		};

		SetPosition(vecStartPos, (vecEndPos * (1.0f - fShort)) + (vecStartPos * fShort));
	}
	return 1;
}

void TMEffectBillBoard3::SetPosition(TMVector3 vecStart, TMVector3 vecEnd)
{
	m_vertex1[0].position = TMVector3{ vecStart.x, vecStart.y - m_fScaleV, vecStart.z };
	m_vertex1[1].position = TMVector3{ vecEnd.x, vecEnd.y - m_fScaleV, vecEnd.z };
	m_vertex1[2].position = TMVector3{ vecEnd.x, vecEnd.y + m_fScaleV, vecEnd.z };
	m_vertex1[3].position = TMVector3{ vecStart.x, vecStart.y + m_fScaleV, vecStart.z };
	m_vertex2[0].position = TMVector3{ vecStart.x - m_fScaleV, vecStart.y, vecStart.z };
	m_vertex2[1].position = TMVector3{ vecEnd.x - m_fScaleV, vecEnd.y, vecEnd.z };
	m_vertex2[2].position = TMVector3{ vecEnd.x + m_fScaleV, vecEnd.y, vecEnd.z };
	m_vertex2[3].position = TMVector3{ vecStart.x + m_fScaleV, vecStart.y, vecStart.z };
}

void TMEffectBillBoard3::SetShort(unsigned int dwTime)
{
	m_dwShortTime = dwTime;
}
