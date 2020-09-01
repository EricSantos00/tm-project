#include "pch.h"
#include "TMTree.h"
#include "TMSkinMesh.h"
#include "TMGlobal.h"
#include "TMFieldScene.h"
#include "TMCamera.h"
#include "TMEffectBillBoard.h"
#include "TMShade.h"

TMTree::TMTree(int nType) 
	: TMObject()
{
	InitLook(nType);
}

TMTree::~TMTree()
{
}

int TMTree::InitObject()
{
    if (m_pSkinMesh)
        return 1;

    m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, 0, 0, 0, 0);
    m_pSkinMesh->m_dwFPS = 80;
    m_pSkinMesh->RestoreDeviceObjects();
    return 1;
}

int TMTree::Render()
{
    if (g_bHideBackground == 1)
        return 0;
    if (m_dwKey != -1 && m_dwKey != TreeNode::m_VisualKey1 && m_dwKey != TreeNode::m_VisualKey2 && m_dwKey != TreeNode::m_VisualKey3 && m_dwKey != TreeNode::m_VisualKey4)
        return 0;

    if (!m_pSkinMesh || !m_bVisible)
        return 1;

    if (g_pDevice->m_dwBitCount == 32)
        g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xAAu);
    else
        g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xFFu);

    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    auto pFocused = g_pObjectManager->m_pCamera->GetFocusedObject();
    g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
    if (pScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD && (m_dwObjType == 354 || m_dwObjType == 377 || m_dwObjType == 378))
    {
        if (pScene->m_cWarClan == 7 && m_dwObjType != 378)
        {
            SAFE_DELETE(m_pSkinMesh);
            InitLook(378);
            InitObject();
            InitAngle(0, m_fAngle, 0);
            InitPosition(m_vecPosition.x, m_fHeight, m_vecPosition.y);
        }
        else if (pScene->m_cWarClan == 8 && m_dwObjType != 377)
        {
            SAFE_DELETE(m_pSkinMesh);
            InitLook(377);
            InitObject();
            InitAngle(0, m_fAngle, 0);
            InitPosition(m_vecPosition.x, m_fHeight, m_vecPosition.y);
        }
        else if (pScene->m_cWarClan != 7 && pScene->m_cWarClan != 8 && m_dwObjType != 354)
        {
            SAFE_DELETE(m_pSkinMesh);
            InitLook(354);
            InitObject();
            InitAngle(0, m_fAngle, 0);
            InitPosition(m_vecPosition.x, m_fHeight, m_vecPosition.y);
        }
    }

    m_pSkinMesh->Render(0.0f, 1.0f, 0.0f);
    return 1;
}

int TMTree::FrameMove(unsigned int dwServerTime)
{
    if (m_dwKey != -1 && m_dwKey != TreeNode::m_VisualKey1 && m_dwKey != TreeNode::m_VisualKey2 && m_dwKey != TreeNode::m_VisualKey3 && m_dwKey != TreeNode::m_VisualKey4)
        return 0;

    dwServerTime = g_pTimerManager->GetServerTime();
    if (!m_pSkinMesh || !IsVisible())
        return 1;

    auto pScene = static_cast<TMFieldScene*>(g_pCurrentScene);
    auto color = pScene->GroundGetColor(m_vecPosition);

    color.r = (color.r * 0.4f) + (g_pDevice->m_colorLight.r * 0.6f);
    color.g = (color.g * 0.4f) + (g_pDevice->m_colorLight.g * 0.6f);
    color.b = (color.b * 0.4f) + (g_pDevice->m_colorLight.b * 0.6f);

    m_pSkinMesh->m_materials.Ambient.r = 0.0f;
    m_pSkinMesh->m_materials.Ambient.g = 0.0f;
    m_pSkinMesh->m_materials.Ambient.b = 0.0f;

    m_pSkinMesh->m_materials.Diffuse = color;

    m_pSkinMesh->m_materials.Specular.r = 1.0f;
    m_pSkinMesh->m_materials.Specular.g = 1.0f;
    m_pSkinMesh->m_materials.Specular.b = 1.0f;

    m_pSkinMesh->m_materials.Emissive.r = (g_pDevice->m_colorBackLight.r * 0.4f) + (color.r * 0.4f);
    m_pSkinMesh->m_materials.Emissive.g = (g_pDevice->m_colorBackLight.g * 0.4f) + (color.r * 0.4f);
    m_pSkinMesh->m_materials.Emissive.b = (g_pDevice->m_colorBackLight.b * 0.4f) + (color.r * 0.4f);

    if (m_nSkinMeshType == 87)
    {
        m_pSkinMesh->m_materials.Emissive.r = 1.0f;
        m_pSkinMesh->m_materials.Emissive.g = 0.89999998f;
        m_pSkinMesh->m_materials.Emissive.b = 0.89999998f;
    }

    m_pSkinMesh->FrameMove(dwServerTime);
    if (m_dwObjType >= 363 && m_dwObjType <= 367 && m_pSkinMesh->m_dwOffset > 6 && m_pSkinMesh->m_dwOffset < 12)
    {
        int nIndex = (m_dwObjType - 363) >> 1;

        const static float fHeight[3]{ 1.6f, 1.4f, 1.4f };
        const static unsigned int dwColor[3]{ 0x00008822, 0x00884400, 0x00770000 };

        if (m_dwLastTime - dwServerTime > 1000)
        {
            auto mpBill = new TMEffectBillBoard(0, 1500, 0.0099999998f, 0.1f, 0.0099999998f, 0.001f, 1, 80);;

            float iZ = ((float)(rand() % 10 - 5) * 0.05f) + m_vecPosition.y;
            float iY = m_fHeight + fHeight[nIndex];
            mpBill->m_vecPosition = mpBill->m_vecStartPos = { ((float)(rand() % 10 - 5) * 0.05f) + m_vecPosition.x, iY, iZ };
            mpBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
            mpBill->m_nParticleType = 1;
            mpBill->m_fParticleV = 2.0f;
            mpBill->SetColor(dwColor[nIndex]);
            g_pCurrentScene->m_pEffectContainer->AddChild(mpBill);
            m_dwLastTime = dwServerTime;
        }
    }

    return 1;
}

void TMTree::RestoreDeviceObjects()
{
    if (m_pSkinMesh)
        return;

    m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, 0, 0, 0, 0);
    m_pSkinMesh->m_dwFPS = 80;
    m_pSkinMesh->RestoreDeviceObjects();
    return;
}

void TMTree::InvalidateDeviceObjects()
{
    if (m_pSkinMesh)
        m_pSkinMesh->InvalidateDeviceObjects();
}

void TMTree::InitPosition(float fX, float fY, float fZ)
{
    TMObject::InitPosition(fX, fY, fZ); 
    g_pCurrentScene->GroundSetColor({ fX + 2.0f, fZ - 2.0f }, 0);
}

void TMTree::SetAnimation(int nAniIndex)
{
    if (m_pSkinMesh)
        m_pSkinMesh->SetAnimation(nAniIndex);
}

void TMTree::InitLook(int nType)
{
    m_dwObjType = nType;
    m_pSkinMesh = 0;
    m_dwLastTime = 0;

    if (m_dwObjType >= 331 && m_dwObjType <= 342)
        m_nSkinMeshType = (nType - 331) / 2 + 63;
    else if (m_dwObjType >= 351 && m_dwObjType <= 400)
        m_nSkinMeshType = (nType - 351) / 2 + 71;

    m_stLookInfo = {};
    m_stSancInfo = {};
    if (g_nSpringTree == 1 && m_dwObjType != 359 && m_dwObjType != 81 && m_dwObjType != 371 && m_dwObjType != 369 && m_dwObjType != 354 && m_dwObjType != 377 && m_dwObjType != 378)
    {
        m_nSkinMeshType = 87;
        return;
    }

    switch (nType)
    {
    case 342:
        m_stLookInfo.Mesh0 = 1;
        break;
    case 354:
        m_stLookInfo.Skin0 = 1;
        break;
    case 361:
        m_stLookInfo.Mesh0 = 0;
        m_stLookInfo.Skin0 = 1;
        break;
    case 362:
        m_stLookInfo.Mesh0 = 1;
        m_stLookInfo.Skin0 = 0;
        break;
    case 377:
        m_stLookInfo.Mesh0 = 0;
        m_stLookInfo.Skin0 = 1;
        break;
    case 375:
        m_stLookInfo.Mesh0 = 0;
        m_stLookInfo.Skin0 = 1;
        break;
    case 373:
        m_stLookInfo.Mesh0 = 0;
        m_stLookInfo.Skin0 = 1;
        break;
    }
}
