#include "pch.h"
#include "TMMesh.h"
#include "TMSea.h"
#include "TMGlobal.h"

TMSea::TMSea()
{
	m_dwObjType = 2;
	m_nPickX = -1;
	m_nPickY = -1;
	m_fAngle = 0.0f;
	m_pMesh = 0;
	m_dwServerTime = 0;
	m_bAlpha = 1;
}

TMSea::~TMSea()
{
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;

		m_pMesh = nullptr;
	}
}

int TMSea::Render()
{
    if (g_bHideBackground == 1)
        return 0;

    if (!IsVisible())
        return 0;

    if (m_pMesh)
    {
        if (m_bAlpha == 1)
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
        else
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
        
        if ((int)m_vecPosition.x >> 7 != 28 && (int)m_vecPosition.x >> 7 != 29 ||
            (int)m_vecPosition.y >> 7 != 23 && (int)m_vecPosition.y >> 7 != 22)
        {
            if (g_pDevice->m_bDungeon && g_pDevice->m_bDungeon != 3 && g_pDevice->m_bDungeon != 4)
            {
                m_materials.Ambient.r = 0.5f;
                m_materials.Ambient.g = 0.5f;
                m_materials.Ambient.b = 0.5f;
                m_materials.Diffuse.r = 0.5f;
                m_materials.Diffuse.g = 0.5f;
                m_materials.Diffuse.b = 0.5f;
                m_materials.Specular.r = m_materials.Diffuse.r;
                m_materials.Specular.g = m_materials.Diffuse.g;
                m_materials.Specular.b = m_materials.Diffuse.b;
                m_materials.Specular.a = m_materials.Diffuse.a;
                m_materials.Emissive.r = 0.0f;
                m_materials.Emissive.g = 0.0f;
                m_materials.Emissive.b = 0.0f;
                m_materials.Emissive.a = 0.0f;
                m_materials.Ambient.a = 0.0f;
                m_materials.Diffuse.a = 0.5f;
                g_pDevice->m_pd3dDevice->SetMaterial(&m_materials);
                m_pMesh->m_nTextureIndex[0] = 8;
                g_pDevice->SetTexture(1u, g_pTextureManager->GetModelTexture(9, 10000));
                g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
                g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
                g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
                g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
                g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
                g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
                g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
                g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
                g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
                g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
                g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
            }
            else
            {
                m_materials.Ambient.r = 0.5f;
                m_materials.Ambient.g = 0.5f;
                m_materials.Ambient.b = 0.5f;
                m_materials.Diffuse.r = 0.5f;
                m_materials.Diffuse.g = 0.5f;
                m_materials.Diffuse.b = 0.5f;
                m_materials.Specular.r = m_materials.Diffuse.r;
                m_materials.Specular.g = m_materials.Diffuse.g;
                m_materials.Specular.b = m_materials.Diffuse.b;
                m_materials.Specular.a = m_materials.Diffuse.a;
                m_materials.Emissive.r = 0.1f;
                m_materials.Emissive.g = 0.1f;
                m_materials.Emissive.b = 0.1f;
                m_materials.Emissive.a = 0.1f;
                m_materials.Ambient.a = 0.89999998f;
                m_materials.Diffuse.a = 0.89999998f;
                g_pDevice->m_pd3dDevice->SetMaterial(&m_materials);
                m_pMesh->m_nTextureIndex[0] = 2;
                g_pDevice->SetTexture(1u, g_pTextureManager->GetModelTexture(3, 10000));
                g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
                g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
                if (g_pDevice->m_bVoodoo == 1)
                {
                    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 3u);
                    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 7u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 7u);
                }
                else
                {
                    g_pDevice->SetRenderState(D3DRS_SRCBLEND, 3u);
                    g_pDevice->SetRenderState(D3DRS_DESTBLEND, 7u);
                    g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                    g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 5u);
                }
                g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
            }
        }
        else
        {
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
            m_materials.Ambient.r = 0.89999998f;
            m_materials.Ambient.g = 0.89999998f;
            m_materials.Ambient.b = 0.89999998f;
            m_materials.Diffuse.r = 0.89999998f;
            m_materials.Diffuse.g = 0.89999998f;
            m_materials.Diffuse.b = 0.89999998f;
            m_materials.Specular.r = m_materials.Diffuse.r;
            m_materials.Specular.g = m_materials.Diffuse.g;
            m_materials.Specular.b = m_materials.Diffuse.b;
            m_materials.Specular.a = m_materials.Diffuse.a;
            m_materials.Emissive.r = 0.89999998f;
            m_materials.Emissive.g = 0.89999998f;
            m_materials.Emissive.b = 0.89999998f;
            m_materials.Emissive.a = 0.89999998f;
            m_materials.Ambient.a = 0.89999998f;
            m_materials.Diffuse.a = 0.89999998f;
            g_pDevice->m_pd3dDevice->SetMaterial(&m_materials);
            m_pMesh->m_bEffect = 1;
            m_pMesh->m_nTextureIndex[0] = 406;
            g_pDevice->SetTexture(1u, g_pTextureManager->GetEffectTexture(406, 5000));
            g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
            g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
            if (g_pDevice->m_bVoodoo == 1)
            {
                g_pDevice->SetRenderState(D3DRS_SRCBLEND, 3u);
                g_pDevice->SetRenderState(D3DRS_DESTBLEND, 7u);
                g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 7u);
            }
            else
            {
                g_pDevice->SetRenderState(D3DRS_SRCBLEND, 4u);
                g_pDevice->SetRenderState(D3DRS_DESTBLEND, 3u);
                g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 4u);
            }
            g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
        }
        D3DXMATRIX matPosition;
        D3DXMATRIX matRotation;
        D3DXMatrixRotationYawPitchRoll(&matRotation, 0, 0, 0);
        D3DXMatrixTranslation(&matPosition, m_vecPosition.x, m_fHeight, m_vecPosition.y);
        D3DXMatrixMultiply(&matRotation, &g_pDevice->m_matWorld, &matRotation);
        D3DXMatrixMultiply(&matPosition, &matRotation, &matPosition);
        g_pDevice->m_pd3dDevice->SetTransform((D3DTRANSFORMSTATETYPE)256, &matPosition);
        m_pMesh->Render(0, 0);
        g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
        g_pDevice->SetTextureStageState(1u, D3DTSS_ALPHAOP, 2u);
        g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
        g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
        g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
        g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
    }
    return 1;
}

int TMSea::InitObject()
{
	return 0;
}

void TMSea::InitPosition(float fX, float fY, float fZ)
{
}

D3DXVECTOR3* TMSea::GetPickPos(D3DXVECTOR3* result)
{
	return nullptr;
}

float TMSea::GetHeight(float fX, float fY)
{
	return 0.0f;
}

int TMSea::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

int TMSea::IsVisible()
{
	return 0;
}
