#include "pch.h"
#include "TMLight.h"
#include "TMGlobal.h"

unsigned int TMLight::m_dwBaseLightIndex = 2;

TMLight::TMLight(D3DCOLORVALUE col, int bEnable) : 
	TreeNode(0)
{
	m_bVisible = 1;
	m_bEnable = bEnable;
	m_dwLightIndex = TMLight::m_dwBaseLightIndex;

	memset(&m_Light, 0, sizeof(m_Light));

	m_Light.Type = D3DLIGHTTYPE::D3DLIGHT_POINT;
	m_Light.Attenuation0 = 0.001f;
	m_Light.Attenuation1 = 0.001f;
	m_Light.Attenuation2 = 0.001f;
	m_Light.Ambient = col;
	m_Light.Specular = col;
	m_Light.Diffuse = col;

	if (g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_SELCHAR)
	{
		m_Light.Range = 5.0f;
	}
	else if (m_dwLightIndex == 6)
	{
		m_Light.Range = 7.0f;
	}
	else
	{
		m_Light.Range = 5.0f;
	}
}

TMLight::~TMLight()
{
	g_pDevice->m_pd3dDevice->LightEnable(m_dwLightIndex, 0);
}

void TMLight::InitPosition(float fX, float fY, float fZ)
{
	m_Light.Position.x = fX;
	m_Light.Position.y = fY;
	m_Light.Position.z = fZ;
	m_vecPosition.x = fX;
	m_vecPosition.y = fZ;

	unsigned int dwR = (unsigned int)(float)(m_Light.Ambient.r * 255.0f);
	unsigned int dwG = (unsigned int)(float)(m_Light.Ambient.g * 255.0f);
	unsigned int dwB = (unsigned int)(float)(m_Light.Ambient.b * 255.0f);
	unsigned int dwA = (unsigned int)(float)(m_Light.Ambient.a * 255.0f);

	unsigned int dwColor = dwB | (dwG << 8) | (dwR << 16) | (dwA << 24);
	for (int i = 0; i < 5; ++i)
	{
		TMVector2 vec((float)(fX - 1.0f) + (float)i, (float)(fZ - 3.0f) + (float)i);
		g_pCurrentScene->GroundSetColor(vec, dwColor);
	}
}

int TMLight::FrameMove(unsigned int dwServerTime)
{
	if (IsVisible() == 1)
	{
		if (m_bEnable == 1)
		{
			D3DLIGHT9 light;
			g_pDevice->m_pd3dDevice->GetLight(m_dwLightIndex, &light);

			if (memcmp(&light, &m_Light, sizeof(light)))
				g_pDevice->m_pd3dDevice->SetLight(m_dwLightIndex, &m_Light);

			g_pDevice->m_pd3dDevice->LightEnable(m_dwLightIndex, m_bEnable);
		}
		else
		{
			g_pDevice->m_pd3dDevice->LightEnable(m_dwLightIndex, 0);
		}
	}

	return 1;
}

int TMLight::IsVisible()
{
	if (g_pCurrentScene->GetSceneType() != ESCENE_TYPE::ESCENE_FIELD)
	{
		m_bVisible = 1;
		return 1;
	}
	
	// TODO

	return 0;
}
