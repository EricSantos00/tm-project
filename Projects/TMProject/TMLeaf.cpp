#include "pch.h"
#include "TMLeaf.h"
#include "TMSkinMesh.h"
#include "TMCamera.h"
#include "TMObject.h"
#include "TMGlobal.h"

TMLeaf::TMLeaf(int nType) :
    TMObject(),
	m_stLookInfo{},
	m_stSancInfo{}
{
	m_dwObjType = nType;
	m_pSkinMesh = 0;
	m_nSkinMeshType = 61;
}

TMLeaf::~TMLeaf()
{
}

int TMLeaf::InitObject()
{
    if (!m_pSkinMesh)
    {
        m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, nullptr, 0, 0, 0);

        if (m_pSkinMesh)
        {
            m_pSkinMesh->RestoreDeviceObjects();
            m_pSkinMesh->m_dwFPS = 80;
        }
    }

    return 1;
}

int TMLeaf::Render()
{
    if (g_bHideBackground == 1)
        return 0;

    if (!g_pDevice->m_iVGAID)
        return 0;

    if (g_pDevice->m_bIntel == 1)
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

    TMVector2 vec
    {
        g_pObjectManager->m_pCamera->m_cameraPos.x,
        g_pObjectManager->m_pCamera->m_cameraPos.z 
    };

    float fLen = m_vecPosition.DistanceFrom2(vec);
    float FogLen = static_cast<float>(AlphaEnd);

    if (fLen > 900.0f)
        return 1;

    int AlphaStart = 20;

    if (m_pSkinMesh && m_bVisible == 1)
    {
        D3DCOLORVALUE color = g_pCurrentScene->GroundGetColor(m_vecPosition);

        color.r = 0.0f;
        color.g = 0.0f;
        color.b = 0.0f;

        m_pSkinMesh->m_materials.Diffuse.r = 0.0f;
        m_pSkinMesh->m_materials.Diffuse.g = color.g;
        m_pSkinMesh->m_materials.Diffuse.b = color.b;
        m_pSkinMesh->m_materials.Diffuse.a = color.a;
        m_pSkinMesh->m_materials.Specular.r = 1.0f;
        m_pSkinMesh->m_materials.Specular.g = 1.0f;
        m_pSkinMesh->m_materials.Specular.b = 1.0f;

        if ((int)m_vecPosition.x >> 7 > 26 &&
            (int)m_vecPosition.x >> 7 < 31 &&
            (int)m_vecPosition.y >> 7 > 20 && 
            (int)m_vecPosition.y >> 7 < 25)
        {
            D3DCOLORVALUE result = g_pCurrentScene->GroundGetColor(m_vecPosition);

            m_pSkinMesh->m_materials.Emissive.r = (result.r * 0.5f) + (g_pDevice->m_colorLight.r * 0.5f);
            m_pSkinMesh->m_materials.Emissive.g = (result.g * 0.5f) + (g_pDevice->m_colorLight.g * 0.5f);
            m_pSkinMesh->m_materials.Emissive.b = (result.b * 0.5f) + (g_pDevice->m_colorLight.b * 0.5f);
        }
        else
        {
            m_pSkinMesh->m_materials.Emissive.r = (color.r * 0.2f) + (g_pDevice->m_colorLight.r * 0.80000001f);
            m_pSkinMesh->m_materials.Emissive.g = (color.g * 0.2f) + (g_pDevice->m_colorLight.g * 0.80000001f);
            m_pSkinMesh->m_materials.Emissive.b = (color.b * 0.2f) + (g_pDevice->m_colorLight.b * 0.80000001f);
        }

        if (fLen <= static_cast<float>(AlphaStart * AlphaStart))
        {
            color.a = 1.0f;
        }
        else
        {
            color.a = 1.0f - (float)((fLen - (float)(AlphaStart * AlphaStart)) / (float)(AlphaEnd * AlphaEnd - AlphaStart * AlphaStart));

            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, 0);
        }

        m_pSkinMesh->m_materials.Diffuse = color;

        g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
        g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
        g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);

        m_pSkinMesh->Render(0.0f, 1.0f, 0.0f);

        g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
        g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);

        if (fLen > static_cast<float>(AlphaStart * AlphaStart))
        {
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
            g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, 1u);
        }
    }

	return 1;
}

int TMLeaf::FrameMove(unsigned int dwServerTime)
{
    if (!g_pDevice->m_iVGAID)
        return 0;

    if (g_pDevice->m_bIntel == 1)
        return 0;

    if ((m_dwObjType != 312 || (int)m_vecPosition.x != 3632 || (int)m_vecPosition.y != 3106) &&
        m_dwKey != -1 &&
        m_dwKey != TreeNode::m_VisualKey1 &&
        m_dwKey != TreeNode::m_VisualKey2 &&
        m_dwKey != TreeNode::m_VisualKey3 &&
        m_dwKey != TreeNode::m_VisualKey4)
    {
        return 0;
    }

    TMVector2 vec
    {
        g_pObjectManager->m_pCamera->m_cameraPos.x,
        g_pObjectManager->m_pCamera->m_cameraPos.z 
    };

    float fLen = m_vecPosition.DistanceFrom2(vec);
    float FogLen = g_pDevice->m_fFogStart * g_pDevice->m_fFogEnd;

    if (fLen > 900.0f)
        return 1;

    dwServerTime = g_pTimerManager->GetServerTime();

    if (m_pSkinMesh)
    {
        m_bVisible = 1;

        int nMask = g_pCurrentScene->GroundGetMask(m_vecPosition);

        if (nMask < 127)
            m_fHeight = (float)nMask * 0.1f;

        D3DCOLORVALUE color = g_pCurrentScene->GroundGetColor(m_vecPosition);

        color.r = (color.r * 0.30000001f) + 0.5f;
        color.g = (color.g * 0.30000001f) + 0.5f;
        color.b = (color.b * 0.30000001f) + 0.5f;

        m_pSkinMesh->m_materials.Diffuse = color;

        m_pSkinMesh->m_materials.Specular = m_pSkinMesh->m_materials.Diffuse;

        m_pSkinMesh->FrameMove(dwServerTime);
    }

    return 1;
}

void TMLeaf::RestoreDeviceObjects()
{
    if (!m_pSkinMesh)
    {
        m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, nullptr, 0, 0, 0);
    }

    if (m_pSkinMesh)
        m_pSkinMesh->RestoreDeviceObjects();
}

void TMLeaf::InvalidateDeviceObjects()
{
    if (m_pSkinMesh)
        m_pSkinMesh->InvalidateDeviceObjects();
}

void TMLeaf::InitPosition(float fX, float fY, float fZ)
{
    TMObject::InitPosition(fX, fY, fZ);
}
