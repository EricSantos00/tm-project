#include "pch.h"
#include "TMEffectBillBoard2.h"
#include "TMFloat.h"
#include "TMGlobal.h"
#include "TMSkinMesh.h"
#include "TMFieldScene.h"

TMFloat::TMFloat(int nType)
	: TMObject()
{
	m_dwObjType = nType;
	m_pSkinMesh = nullptr;
	m_nSkinMeshType = 62;
	m_pBillBoard = nullptr;
	m_dwWaterTime = 0;
	m_pWaterEffect[0] = nullptr;
	m_stLookInfo = {};
	m_stSancInfo = {};
}

TMFloat::~TMFloat()
{
	SAFE_DELETE(m_pBillBoard);
	SAFE_DELETE(m_pWaterEffect[0]);
}

int TMFloat::InitObject()
{
    if (!m_pSkinMesh && m_dwObjType == 3)
    {
        m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, 0, 0, 0, 0);
        if (!m_pSkinMesh)
            return 1;

        m_pSkinMesh->RestoreDeviceObjects();
        m_pSkinMesh->m_vScale.x = 1.5f;
        m_pSkinMesh->m_vScale.y = 1.5f;
        m_pSkinMesh->m_vScale.z = 1.5f;
        m_pSkinMesh->m_dwFPS = 80;
        m_pSkinMesh->m_dwStartOffset = g_pTimerManager->GetServerTime() - 300 * (rand() % 10);
    }
    else if (m_dwObjType == 5)
    {
        m_pBillBoard = new TMEffectBillBoard2(90, 0, 1.0f, 1.0f, 1.0f, 0.0005f, 0);;
        if (!m_pBillBoard)
            return 1;
        m_pBillBoard->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pBillBoard);
    }
    for (int i = 0; i < 1; ++i)
    {
        m_pWaterEffect[i] = new TMEffectBillBoard2(10, 0, 0.5f, 0.5f, 0.5f, 0.001f, 0);;
        m_pWaterEffect[i]->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        if (!m_pWaterEffect[i])
            return 1;
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pWaterEffect[i]);
    }

    return 1;
}

int TMFloat::Render()
{
    if (g_bHideBackground == 1)
        return 0;
    if (m_dwKey != -1 && m_dwKey != TreeNode::m_VisualKey1 && m_dwKey != TreeNode::m_VisualKey2 && m_dwKey != TreeNode::m_VisualKey3 && m_dwKey != TreeNode::m_VisualKey4)
        return 0;

    if (m_pSkinMesh && m_bVisible == 1)
    {
        if (g_pDevice->m_iVGAID == 1)
        {
            if (g_pDevice->m_dwBitCount == 32)
                g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xFF000000);
            else
                g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xF000u);
        }
        else if (g_pDevice->m_dwBitCount == 32)
            g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xDDu);
        else
            g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xDu);

        g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
        g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
        g_pDevice->SetRenderState(D3DRS_FOGVERTEXMODE, 3u);
        g_pDevice->SetRenderState(D3DRS_FOGENABLE, g_pDevice->m_bFog);
        m_pSkinMesh->Render(0.0f, 1.0f, 0.0f);
        g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
        g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
    }
    return 1;
}

int TMFloat::FrameMove(unsigned int dwServerTime)
{
    if (m_dwKey != -1 && m_dwKey != TreeNode::m_VisualKey1 && m_dwKey != TreeNode::m_VisualKey2 && m_dwKey != TreeNode::m_VisualKey3 && m_dwKey != TreeNode::m_VisualKey4)
        return 0;

    dwServerTime = g_pTimerManager->GetServerTime();
    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    if (m_pSkinMesh && m_dwObjType == 3)
    {
        if (IsVisible() == 1)
        {
            TMVector2 vecWater{ m_vecPosition.x, m_vecPosition.y };
            float fHeight = 0.0f;

            if (pScene->GroundGetWaterHeight(vecWater, &fHeight) > -100.0f)
            {
                m_fHeight = fHeight + 0.3f;
                SetPosition(m_vecPosition.x, m_fHeight, m_vecPosition.y);
            }

            auto color = pScene->GroundGetColor(m_vecPosition);
            color.r = (color.r * 0.3f) + 0.5f;
            color.g = (color.g * 0.3f) + 0.5f;
            color.b = (color.b * 0.3f) + 0.5f;
            m_pSkinMesh->m_materials.Diffuse = color;
            m_pSkinMesh->m_materials.Specular = m_pSkinMesh->m_materials.Diffuse;
            m_pSkinMesh->FrameMove(dwServerTime);
        }
    }
    else if (m_dwObjType == 5)
    {
        if (m_pBillBoard)
        {
            float pfWaterHeight = 0.0f;
            if (pScene->GroundGetWaterHeight({ m_vecPosition.x, m_vecPosition.y }, &pfWaterHeight) > -100.0f)
            {
                m_fHeight = pfWaterHeight + 0.36f;
                m_pBillBoard->m_vecPosition.y = m_fHeight;
            }
        }
    }
    if (dwServerTime - m_dwWaterTime > 500)
    {
        for (int i = 0; i < 1; ++i)
        {
            m_pWaterEffect[i]->m_vecPosition.x = m_vecPosition.x;
            m_pWaterEffect[i]->m_vecPosition.z = m_vecPosition.y;
            m_pWaterEffect[i]->m_vecPosition.y = m_fHeight - 0.1f;
        }
    }
    return 1;
}

void TMFloat::RestoreDeviceObjects()
{
    if (m_dwObjType == 3)
    {
        if (!m_pSkinMesh)
            m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, 0, 0, 0, 0);

        m_pSkinMesh->RestoreDeviceObjects();
    }
}

void TMFloat::InvalidateDeviceObjects()
{
    if (m_pSkinMesh && m_dwObjType == 3)
        m_pSkinMesh->InvalidateDeviceObjects();
}

void TMFloat::InitPosition(float fX, float fY, float fZ)
{
    TMObject::InitPosition(fX, fY, fZ);
    if (m_pBillBoard)
    {
        m_pBillBoard->m_vecPosition.x = fX;
        m_pBillBoard->m_vecPosition.y = fY;
        m_pBillBoard->m_vecPosition.z = fZ;
    }
}
