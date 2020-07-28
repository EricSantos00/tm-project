#include "pch.h"
#include "TMSun.h"
#include "TMGlobal.h"
#include "TMCamera.h"

TMSun::TMSun() : 
	TreeNode(0),
	m_vFlareDirection{},
	m_vecTLVertex{},
	m_stFlareArray{}
{
	m_bHide = 1;
	m_fDefSize = 1.0f;

	m_vFlareDirection.x = -1.0f;
	m_vFlareDirection.y = 0.69999999f;
	m_vFlareDirection.z = 0.30000001f;
}

TMSun::~TMSun()
{
}

int TMSun::InitObject()
{
	float fRatio = RenderDevice::m_fWidthRatio * 50.0f;

	m_stFlareArray[0].nTexIndex = 206;
	m_stFlareArray[0].fLoc = -0.60000002f;
	m_stFlareArray[1].nTexIndex = 212;
	m_stFlareArray[1].fLoc = -0.40000001f;
	m_stFlareArray[2].nTexIndex = 212;
	m_stFlareArray[2].fLoc = -0.30000001f;
	m_stFlareArray[3].nTexIndex = 211;
	m_stFlareArray[3].fLoc = 0.0f;
	m_stFlareArray[4].nTexIndex = 210;
	m_stFlareArray[4].fLoc = 0.0f;
	m_stFlareArray[5].nTexIndex = 211;
	m_stFlareArray[5].fLoc = 0.0f;
	m_stFlareArray[6].nTexIndex = 212;
	m_stFlareArray[6].fLoc = 0.0f;
	m_stFlareArray[7].nTexIndex = 213;
	m_stFlareArray[7].fLoc = 0.0f;
	m_stFlareArray[8].nTexIndex = 210;
	m_stFlareArray[8].fLoc = 0.1f;
	m_stFlareArray[9].nTexIndex = 209;
	m_stFlareArray[9].fLoc = 0.2f;
	m_stFlareArray[10].nTexIndex = 206;
	m_stFlareArray[10].fLoc = 0.30000001f;
	m_stFlareArray[11].nTexIndex = 208;
	m_stFlareArray[11].fLoc = 0.60000002f;
	m_stFlareArray[0].fScale = 0.40000001f * fRatio;
	m_stFlareArray[0].diffuse = 0xAA8888u;
	m_stFlareArray[1].fScale = 0.23f * fRatio;
	m_stFlareArray[1].diffuse = 0xAAAA22u;
	m_stFlareArray[2].fScale = 0.090000004f * fRatio;
	m_stFlareArray[2].diffuse = 0xAA22AAu;
	m_stFlareArray[3].fScale = 1.6f * fRatio;
	m_stFlareArray[3].diffuse = 0xFFFFFFu;
	m_stFlareArray[4].fScale = 0.93000001f * fRatio;
	m_stFlareArray[4].diffuse = 0xAAAAAAu;
	m_stFlareArray[5].fScale = 2.8099999f * fRatio;
	m_stFlareArray[5].diffuse = 0xAAAAAAu;
	m_stFlareArray[6].fScale = 9.4300003f * fRatio;
	m_stFlareArray[6].diffuse = 0xAAAAAAu;
	m_stFlareArray[7].fScale = 10.6f * fRatio;
	m_stFlareArray[7].diffuse = 0xFFFFFFu;
	m_stFlareArray[8].fScale = 0.41999999f * fRatio;
	m_stFlareArray[8].diffuse = 0xAAAAAAu;
	m_stFlareArray[9].fScale = 0.63999999f * fRatio;
	m_stFlareArray[9].diffuse = 0xAAAAAAu;
	m_stFlareArray[10].fScale = 0.73000002f * fRatio;
	m_stFlareArray[10].diffuse = 0xAAAAAAu;
	m_stFlareArray[11].fScale = 1.5599999f * fRatio;
	m_stFlareArray[11].diffuse = 0xAAAAAAu;
	m_vecTLVertex[0].tu = -1.0f;
	m_vecTLVertex[0].tv = -1.0f;
	m_vecTLVertex[1].tu = 0.0f;
	m_vecTLVertex[1].tv = -1.0f;
	m_vecTLVertex[2].tu = 0.0f;
	m_vecTLVertex[2].tv = 0.0f;
	m_vecTLVertex[3].tu = -1.0f;
	m_vecTLVertex[3].tv = 0.0f;

	for (int j = 0; j < 4; ++j)
		m_vecTLVertex[j].rhw = 1.0f;

	return 1;
}

int TMSun::Render()
{
	if (g_bHideBackground == 1)
		return 0;

	if (m_bHide == 1)
		return 1;

	D3DXVECTOR3 vecCam
	{ 
		g_pObjectManager->m_pCamera->m_cameraPos.x,
		g_pObjectManager->m_pCamera->m_cameraPos.y,
		g_pObjectManager->m_pCamera->m_cameraPos.z 
	};

	D3DXVECTOR3 lightVector{ vecCam + m_vFlareDirection };

	D3DXVECTOR3 vFlarePos{};

	D3DXVec3Project(
		&vFlarePos,
		&lightVector,
		&g_pDevice->m_viewport,
		&g_pDevice->m_matProj,
		&g_pDevice->m_matView,
		&g_pDevice->m_matWorld);

	if (vFlarePos.z > 1.0f)
		return 1;

	D3DXVECTOR3 vCenterPosFromFlare{};

	vCenterPosFromFlare.x = (float)(g_pDevice->m_viewport.Width >> 1) - vFlarePos.x;
	vCenterPosFromFlare.y = (float)(g_pDevice->m_viewport.Height >> 1) - vFlarePos.y;
	vCenterPosFromFlare.z = 0.0f;

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
	g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
	g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, 7u);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, 3u);
	g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
	g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);

	m_vFlareDirection.y = m_fDefSize * 0.69999999f;

	for (int i = 0; i < 12; ++i)
	{
		float flareXSize = (vCenterPosFromFlare.x * m_stFlareArray[i].fLoc) + vFlarePos.x;
		float flareYSize = (vCenterPosFromFlare.y * m_stFlareArray[i].fLoc) + vFlarePos.y;
		float defaultSize = m_stFlareArray[i].fScale;
		m_vecTLVertex[0].position.x = flareXSize - (defaultSize * m_fDefSize);
		m_vecTLVertex[0].position.y = flareYSize - (defaultSize * m_fDefSize);
		m_vecTLVertex[0].position.z = 0.80000001f - ((float)i * 0.039999999f);
		m_vecTLVertex[0].diffuse = m_stFlareArray[i].diffuse;
		m_vecTLVertex[1].position.x = flareXSize + (defaultSize * m_fDefSize);
		m_vecTLVertex[1].position.y = flareYSize - (defaultSize * m_fDefSize);
		m_vecTLVertex[1].position.z = 0.80000001f - ((float)i * 0.039999999f);
		m_vecTLVertex[1].diffuse = m_stFlareArray[i].diffuse;
		m_vecTLVertex[2].position.x = flareXSize + (defaultSize * m_fDefSize);
		m_vecTLVertex[2].position.y = flareYSize + (defaultSize * m_fDefSize);
		m_vecTLVertex[2].position.z = 0.80000001f - ((float)i * 0.039999999f);
		m_vecTLVertex[2].diffuse = m_stFlareArray[i].diffuse;
		m_vecTLVertex[3].position.x = flareXSize - (defaultSize * m_fDefSize);
		m_vecTLVertex[3].position.y = flareYSize + (defaultSize * m_fDefSize);
		m_vecTLVertex[3].position.z = 0.80000001f - ((float)i * 0.039999999f);
		m_vecTLVertex[3].diffuse = m_stFlareArray[i].diffuse;

		g_pDevice->SetTexture(0, g_pTextureManager->GetEffectTexture(m_stFlareArray[i].nTexIndex, 5000));

		g_pDevice->m_pd3dDevice->SetFVF(324u);
		g_pDevice->m_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2u, m_vecTLVertex, 28u);
	}
	return 1;
}

int TMSun::FrameMove()
{
	return 1;
}
