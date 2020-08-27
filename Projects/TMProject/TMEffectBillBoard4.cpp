#include "pch.h"
#include "TMEffectBillBoard4.h"
#include "TMGlobal.h"

TMEffectBillBoard4::TMEffectBillBoard4(int nTextureIndex, unsigned int dwLifeTime, float fScaleX, float fScaleY, float fVelocity, int nCycleCount, int nCycleTime) :
    TMEffect(),
	m_vecPosition{}
{
	m_dwCreateTime = 0;
	m_fProgress = 0.0f;
	m_nTextureIndex = nTextureIndex;
	m_nCycleIndex = 0;
	m_nCycleCount = nCycleCount;
	m_nCycleTime = nCycleTime;
	m_dwLifeTime = dwLifeTime;
	m_fScaleVelX = fVelocity;
	m_fScaleVelY = fVelocity;
	m_fParticleH = 0.0f;
	m_fParticleV = 0.0f;
	m_vecScale.x = fScaleX * RenderDevice::m_fWidthRatio;
	m_vecScale.y = fScaleY * RenderDevice::m_fHeightRatio;
	m_nFade = 1;

	m_vertex[0].position = TMVector3{ 0.0f, 0.0f, 0.0099999998f };
	m_vertex[1].position = TMVector3{ 0.0f, 0.0f, 0.0099999998f };
	m_vertex[2].position = TMVector3{ 0.0f, 0.0f, 0.0099999998f };
	m_vertex[3].position = TMVector3{ 0.0f, 0.0f, 0.0099999998f };

	m_vertex[0].rhw = 1.0f;
	m_vertex[1].rhw = 1.0f;
	m_vertex[2].rhw = 1.0f;
	m_vertex[3].rhw = 1.0f;
	m_vertex[0].tu = 0.0099999998f;
	m_vertex[0].tv = 0.0099999998f;
	m_vertex[1].tu = 0.99000001f;
	m_vertex[1].tv = 0.0099999998f;
	m_vertex[2].tu = 0.99000001f;
	m_vertex[2].tv = 0.99000001f;
	m_vertex[3].tu = 0.0099999998f;
	m_vertex[3].tv = 0.99000001f;

	SetColor(0xFFFFFFFF);
}

TMEffectBillBoard4::~TMEffectBillBoard4()
{
}

int TMEffectBillBoard4::Render()
{
    if (g_bHideEffect == 1)
        return 1;

    if (m_dwLifeTime && m_fProgress < 0.050000001f)
        return 1;
    
    if (!strlen(g_pTextureManager->m_stEffectTextureList[m_nTextureIndex].szFileName))
        return 0;

    if (m_bVisible == 1)
    {
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

        g_pDevice->m_pd3dDevice->SetFVF(324u);

        g_pDevice->SetTexture(0, g_pTextureManager->GetEffectTexture(m_nCycleIndex + m_nTextureIndex, 5000));

        g_pDevice->m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2u, m_vertex, 28u);

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

void TMEffectBillBoard4::SetColor(unsigned int dwColor)
{
    for (int i = 0; i < 4; ++i)
        m_vertex[i].diffuse = dwColor;

    m_dwA = (dwColor & 0xFF000000) >> 24;
    m_dwR = (dwColor & 0xFF0000) >> 16;
    m_dwG = (dwColor & 0xFF00) >> 8;
    m_dwB = static_cast<unsigned char>(dwColor);
}

int TMEffectBillBoard4::FrameMove(unsigned int dwServerTime)
{
    dwServerTime = g_pTimerManager->GetServerTime();

    if (!m_dwCreateTime)
        m_dwCreateTime = dwServerTime;

    int timespent{};

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

    DWORD dwMod = m_nCycleTime * m_nCycleCount;

    if (!dwMod)
        dwMod = 1;

    if (m_nCycleTime)
        m_nCycleIndex = timespent % dwMod / m_nCycleTime;
    else
        m_nCycleIndex = 0;

    if (m_dwLifeTime)
        m_fProgress = (float)timespent / (float)m_dwLifeTime;

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
        float fVel = (float)((dwServerTime + 200 * ((unsigned int)this % 100)) % 3000) / 3000.0f;

        DWORD dwA = (unsigned int)(((0.2f * fabsf(sinf((fVel * 3.1415927f) * 2.0f))) + 0.80000001f) * (float)m_dwA);
        DWORD dwR = (unsigned int)(((0.2f * fabsf(sinf((fVel * 3.1415927f) * 2.0f))) + 0.80000001f) * (float)m_dwR);
        DWORD dwG = (unsigned int)(((0.2f * fabsf(sinf((fVel * 3.1415927f) * 2.0f))) + 0.80000001f) * (float)m_dwG);
        DWORD dwB = (unsigned int)(((0.2f * fabsf(sinf((fVel * 3.1415927f) * 2.0f))) + 0.80000001f) * (float)m_dwB);

        for (int j = 0; j < 4; ++j)
            m_vertex[j].diffuse = dwB | (dwG << 8) | (dwR << 16) | (dwA << 24);
    }
    break;
    case 3:
    {
        float fAlpha = sinf(m_fProgress * 3.1415927f);

        DWORD dwA = (unsigned int)((float)m_dwA * fAlpha);

        for (int k = 0; k < 4; ++k)
            m_vertex[k].diffuse = m_dwB | (m_dwG << 8) | (m_dwR << 16) | (dwA << 24);
    }
    break;
    }

    m_vertex[0].position.x = ((float)m_vecPosition.x - ((m_vecScale.x * m_fProgress) * m_fScaleVelX)) + (m_fParticleH * m_fProgress);
    m_vertex[3].position.x = ((float)m_vecPosition.x - ((m_vecScale.x * m_fProgress) * m_fScaleVelX)) + (m_fParticleH * m_fProgress);

    m_vertex[1].position.x = ((float)m_vecPosition.x + ((m_vecScale.x * m_fProgress) * m_fScaleVelX)) + (m_fParticleH * m_fProgress);
    m_vertex[2].position.x = ((float)m_vecPosition.x + ((m_vecScale.x * m_fProgress) * m_fScaleVelX)) + (m_fParticleH * m_fProgress);

    m_vertex[0].position.y = ((float)m_vecPosition.y - ((m_vecScale.y * m_fProgress) * m_fScaleVelY)) + (m_fParticleV * m_fProgress);
    m_vertex[1].position.y = ((float)m_vecPosition.y - ((m_vecScale.y * m_fProgress) * m_fScaleVelY)) + (m_fParticleV * m_fProgress);

    m_vertex[2].position.y = ((float)m_vecPosition.y + ((m_vecScale.y * m_fProgress) * m_fScaleVelY)) + (m_fParticleV * m_fProgress);
    m_vertex[3].position.y = ((float)m_vecPosition.y + ((m_vecScale.y * m_fProgress) * m_fScaleVelY)) + (m_fParticleV * m_fProgress);
    
	return 1;
}

void TMEffectBillBoard4::SetPosition(int nX, int nY)
{
    m_vecPosition.x = static_cast<int>((float)nX * RenderDevice::m_fWidthRatio);
    m_vecPosition.y = static_cast<int>((float)nY * RenderDevice::m_fHeightRatio);
}

void TMEffectBillBoard4::SetParticle(float fH, float fV)
{
    m_fParticleH = fH * RenderDevice::m_fWidthRatio;
    m_fParticleV = fV * RenderDevice::m_fHeightRatio;
}
