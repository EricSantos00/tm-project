#include "pch.h"
#include "TMEffectBillBoard3.h"
#include "TMEffectMesh.h"
#include "TMArrow.h"
#include "TMGlobal.h"
#include "TMUtil.h"
#include "TMEffectBillBoard3.h"
#include "TMCamera.h"
#include "TMMesh.h"
TMArrow::TMArrow(TMVector3 vecStart, TMVector3 vecTarget, int nLevel, int nType, char cAvatar, int nColor, int nDestID) 
	: TreeNode(0),
	m_vecStartPos{},
	m_vecTargetPos{},
	m_vecCurrentPos{},
	m_vecRotatePos1{},
	m_vecRotatePos2{},
	m_vecRotatePos3{}
{
	m_fAngle = 0.0f;
	m_fRotAngle = 0.0f;
	m_vecCurrentPos = m_vecStartPos = vecStart;
	m_vecTargetPos = vecTarget;
	m_nLevel = nLevel;
	m_nType = nType;
	m_dwStartTime = g_pTimerManager->GetServerTime();
	m_pEffectMesh = 0;
	m_vecRotatePos1.x = 0.0f;
	m_vecRotatePos1.y = 0.0f;
	m_vecRotatePos2.x = 0.0f;
	m_vecRotatePos2.y = 0.0f;
	m_vecRotatePos3.x = 0.0f;
	m_vecRotatePos3.y = 0.0f;

	auto vecD = vecTarget - vecStart;
	float fLength = vecD.Length();

    switch (m_nType)
    {
    case 151:
    {
        m_nMeshIndex = 800;
        m_fRotAngle = 0.0;
        if (nLevel > 0)
        {
            const static unsigned int dwColor[3]{ 0x00885522, 0x0AA00, 0x00AA00FF };
            m_pEffectMesh = new TMEffectMesh(28, dwColor[(nLevel % 3) - 1], m_fRotAngle, 1);;
            if (m_pEffectMesh)
            {
                m_pEffectMesh->m_fScaleH = 1.3f;
                m_pEffectMesh->m_fScaleV = 1.3f;
            }
        }

        GetSoundAndPlay(133, 0, 0);
        m_dwLifeTime = 50 * (unsigned int)fLength;
    }
    break;
    case 152:
    {
        m_dwLifeTime = 50 * (unsigned int)fLength;
        if (!nLevel)
            m_nMeshIndex = 871;
        if (nLevel == 1)
            m_nMeshIndex = 872;
        if (nLevel == 2)
        {
            m_nMeshIndex = 863;
            m_pEffectMesh = new TMEffectMesh(28, 0xFF001020, m_fRotAngle, 1);
            if (m_pEffectMesh)
            {
                m_pEffectMesh->m_fScaleH = 2.0f;
                m_pEffectMesh->m_fScaleV = 2.0f;
            }
            m_dwLifeTime = 70 * (unsigned int)fLength;
        }
        GetSoundAndPlay(134, 0, 0);
    }
    break;
    case 153:
    {
        if (!nLevel)
            m_nMeshIndex = 873;
        if (nLevel == 1)
            m_nMeshIndex = 874;
        if (nLevel == 2)
            m_nMeshIndex = 875;
        if (nLevel == 3)
            m_nMeshIndex = 876;
        if (nLevel == 4)
            m_nMeshIndex = 877;
        if (nLevel == 5)
            m_nMeshIndex = 892;
        if (nLevel == 6)
            m_nMeshIndex = 907;
        if (nLevel == 7)
            m_nMeshIndex = 908;
        if (nLevel == 8)
            m_nMeshIndex = 909;
        if (nLevel == 9)
            m_nMeshIndex = 37;
        if (nLevel == 10)
            m_nMeshIndex = 767;
        if (nLevel == 11)
            m_nMeshIndex = 2814;
        if (nLevel == 99)
            m_nMeshIndex = 2921;
        m_fRotAngle = 0.0;
        m_dwLifeTime = 100 * (unsigned int)fLength;
    }
    break;
    case 104:
        m_nMeshIndex = 879;
        m_dwLifeTime = 150 * (unsigned int)fLength;
        break;
    case 105:
        if (!nLevel)
            m_nMeshIndex = 885;
        if (nLevel == 1)
            m_nMeshIndex = 919;
        m_dwLifeTime = 100 * (unsigned int)fLength;
        break;
    case 10000:
        m_dwLifeTime = 50 * (unsigned int)fLength;
        break;
    case 10001:
        m_dwLifeTime = 100 * (unsigned int)fLength;
        m_nMeshIndex = 2840;
        nColor = 5;
        break;
    case 10002:
        m_dwLifeTime = 1000;
        m_nMeshIndex = 2840;
        nColor = 5;
        break;
    case 10003:
        m_dwLifeTime = 800;
        m_nMeshIndex = 800;
        nColor = 5;
        break;
    }

    if (!m_dwLifeTime)
        m_dwLifeTime = 1;
    if (m_dwLifeTime > 5000)
        m_dwLifeTime = 5000;
    if (nColor == 8 || nColor == 7 || nColor == 6 || nColor == 5)
        m_nColor = nColor;
    else
        m_nColor = 0;

    m_pBeam = nullptr;
    if (m_nType == 151 || m_nType == 152 || m_nType == 153 || m_nType == 10000 || m_nType == 10001)
    {
        float BeamSize = 0.079999998f;
        unsigned int BeamColor = 0x00777777;
        if (m_nType == 152)
            BeamSize = 0.1f;
        if (m_nType == 153)
            BeamSize = 0.4f;
        switch (nColor)
        {
        case 8:
            BeamColor = 0x00883333;
            break;
        case 7:
            BeamColor = 0x00884388;
            break;
        case 6:
            BeamColor = 0x338843;
            break;
        case 5:
            BeamColor = 0x222288;
            break;
        }
        if (m_nType == 10000)
        {
            BeamSize = 0.05f;
            BeamColor = 0xFFAAAAFF;
        }
        else if (m_nType == 10001)
        {
            BeamSize = 0.5f;
            BeamColor = 0xFF7777FF;
        }
        float fScaleV = BeamSize;
        float fAngle = BeamSize;
        m_pBeam = new TMEffectBillBoard3(vecStart, { vecStart.x, vecStart.y - 0.1f, vecStart.z }, 410, BeamColor, 1000, fAngle, fScaleV);
    }

    if (m_pBeam)
    {
        m_pBeam->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
        m_pBeam->m_nFade = 1;
        m_pBeam->m_dwLifeTime = m_dwLifeTime + 2000;
        g_pCurrentScene->m_pEffectContainer->AddChild(m_pBeam);
    }

    m_nDestID = nDestID;
    m_cAvatar = cAvatar;
}

TMArrow::~TMArrow()
{
}

int TMArrow::Render()
{
    if (m_bVisible == 1 && m_nType != 10000)
    {
        bool bEffect = false;
        if (m_nType == 10001)
            bEffect = true;

        auto pMesh = g_pMeshManager->GetCommonMesh(m_nMeshIndex, bEffect, 180000);
        D3DMATERIAL9 Materials{};
        if (m_nType == 10001 || m_nType == 10002 || m_nType == 10003)
        {
            Materials.Diffuse.r = 0.3f;
            Materials.Diffuse.g = 0.3f;
            Materials.Diffuse.b = 1.0f;
            Materials.Emissive.r = 0.3f;
            Materials.Emissive.g = 0.3f;
            Materials.Emissive.b = 1.0f;
            Materials.Emissive.a = Materials.Diffuse.a;
            Materials.Specular.r = 0.3f;
            Materials.Specular.g = 0.3f;
            Materials.Specular.b = 1.0f;
            Materials.Specular.a = Materials.Diffuse.a;
            Materials.Power = 0.0;
        }
        else if (m_nType == 10003)
        {
            Materials.Diffuse.r = 1.0f;
            Materials.Diffuse.g = 1.0f;
            Materials.Diffuse.b = 1.0f;
            Materials.Emissive.r = 1.0f;
            Materials.Emissive.g = 1.0f;
            Materials.Emissive.b = 1.0f;
            Materials.Emissive.a = Materials.Diffuse.a;
            Materials.Specular.r = 1.0f;
            Materials.Specular.g = 1.0f;
            Materials.Specular.b = 1.0f;
            Materials.Specular.a = Materials.Diffuse.a;
            Materials.Power = 1.0f;
        }
        else
        {
            Materials.Emissive.r = 0.3f;
            Materials.Emissive.g = 0.3f;
            Materials.Emissive.b = 0.3f;
            Materials.Diffuse.r = 0.3f;
            Materials.Diffuse.g = 0.3f;
            Materials.Diffuse.b = 0.3f;
            Materials.Diffuse.a = Materials.Emissive.a;
            Materials.Specular.r = 0.3f;
            Materials.Specular.g = 0.3f;
            Materials.Specular.b = 0.3f;
            Materials.Specular.a = Materials.Emissive.a;
            Materials.Power = 0.0;
        }
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
        if (!m_nColor)
        {
            g_pDevice->SetTexture(1u, nullptr);
            g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
        }
        else
        {
            int nBaseIndex = 153;
            if (m_nColor == 6)
                nBaseIndex = 166;
            if (m_nColor == 7)
                nBaseIndex = 246;
            if (m_nColor == 8)
                nBaseIndex = 260;

            g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(nBaseIndex + 10, 5000));
            if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
            {
                g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 7u);
            }
            else
            {
                g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 0xBu);
            }
        }
        if (pMesh)
        {
            switch (m_nType)
            {
            case 151:
            {
                pMesh->Render(m_vecCurrentPos.x, m_vecCurrentPos.y, m_vecCurrentPos.z, m_fAngle, m_fRotAngle - D3DXToRadian(90), 0, 0, 0);
            }
            break;
            case 104:
            case 152:
            {
                pMesh->Render(m_vecCurrentPos.x, m_vecCurrentPos.y, m_vecCurrentPos.z, m_fAngle - D3DXToRadian(90), D3DXToRadian(90), 0, 0, 0);
            }
            break;
            case 10001:
            {
                pMesh->Render(m_vecCurrentPos.x, m_vecCurrentPos.y, m_vecCurrentPos.z, m_fAngle - D3DXToRadian(90), -0.69813174f, 0.78539819f, 0, 0);
            }
            break;
            case 10002:
            {
                pMesh->m_fScaleH = 0.55f;
                pMesh->m_fScaleV = 0.55f;
                TMVector3 vPos1;
                TMVector3 vPos2;
                TMVector3 vPos3;
                vPos1 = vPos2 = vPos3 = m_vecCurrentPos;
                float m_nHeight = (float)(m_vecRotatePos1.x / 3.0f) + 0.3f;
                vPos1.x = vPos1.x + m_vecRotatePos1.x;
                vPos1.z = vPos1.z + m_vecRotatePos1.y;
                pMesh->Render(vPos1.x, vPos1.y + m_nHeight, vPos1.z, m_vecRotatePos1.x * 4.0f, 0, 0, 0, 0);
                vPos2.x = vPos2.x + m_vecRotatePos2.x;
                vPos2.z = vPos2.z + m_vecRotatePos2.y;
                pMesh->Render(vPos2.x, vPos2.y + m_nHeight, vPos2.z, m_vecRotatePos2.x * 4.0f, 0, 0, 0, 0);
                vPos3.x = vPos3.x + m_vecRotatePos3.x;
                vPos3.z = vPos3.z + m_vecRotatePos3.y;
                pMesh->Render(vPos3.x, vPos3.y + m_nHeight, vPos3.z, m_vecRotatePos3.x * 4.0f, 0, 0, 0, 0);
            }
            break;
            case 10003:
            {
                g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(6, 0x1388u));
                g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 0xBu);
                g_pDevice->SetTextureStageState(1, D3DTSS_COLOROP, 9u);
                pMesh->m_fScaleH = 1.5f;
                pMesh->m_fScaleV = 1.5f;
                TMVector3 vPos1;
                TMVector3 vPos2;
                TMVector3 vPos3;
                vPos1 = vPos2 = vPos3 = m_vecCurrentPos;
                float m_nHeight = (float)(m_vecRotatePos1.x / 3.0f) + 0.1f;
                vPos1.x += m_vecRotatePos1.x;
                vPos1.z += m_vecRotatePos1.y;
                pMesh->Render(vPos1.x, vPos1.y + m_nHeight, vPos1.z, (m_vecRotatePos1.x * 2.0f) - 1.6f, m_vecRotatePos1.x * 2.0f, m_vecRotatePos1.x / 2.0f, 0, 0);

                vPos2.x += m_vecRotatePos2.x;
                vPos2.z += m_vecRotatePos2.y;
                pMesh->Render(vPos2.x, vPos2.y + m_nHeight, vPos2.z, m_vecRotatePos2.x * 2.0f, m_vecRotatePos2.x * 2.0f, m_vecRotatePos2.x / 2.0f, 0, 0);

                vPos3.x += m_vecRotatePos3.x;
                vPos3.z += m_vecRotatePos3.y;
                pMesh->Render(vPos3.x, vPos3.y + m_nHeight, vPos3.z, (m_vecRotatePos2.x * 2.0f) + 4.1999998f, m_vecRotatePos3.x * 2.0f, m_vecRotatePos3.x / 2.0f, 0, 0);
            }
            break;
            default:
            {
                pMesh->Render(m_vecCurrentPos.x, m_vecCurrentPos.y, m_vecCurrentPos.z, m_fAngle, D3DXToRadian(90), 0, 0, 0);
            }
            break;
            }
        }
        if (m_nColor)
        {
            g_pDevice->SetTexture(1u, nullptr);
            g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
            g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
        }
        g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
        g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
        g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
        if (m_pEffectMesh)
            m_pEffectMesh->Render();
    }

    return 1;
}

int TMArrow::IsVisible()
{
    if (g_pCurrentScene->GetSceneType() != ESCENE_TYPE::ESCENE_FIELD)
    {
        m_bVisible = 1;
        return 1;
    }

    auto pCamera = g_pObjectManager->m_pCamera;
    if (pCamera->m_nMethod)
    {
        if ((float)(fabsf(pCamera->m_fCX - m_vecCurrentPos.x) + fabsf(pCamera->m_fCY - m_vecCurrentPos.z)) < 18.0f)
        {
            m_bVisible = TMArrow::IsInView();
            return m_bVisible;
        }
    }
    else if (m_vecCurrentPos.x > pCamera->m_fX1 && pCamera->m_fX2 > m_vecCurrentPos.x && m_vecCurrentPos.z > pCamera->m_fY1 && pCamera->m_fY2 > m_vecCurrentPos.z)
    {
        m_bVisible = TMArrow::IsInView();
        return m_bVisible;
    }

    m_bVisible = 0;
    return 0;
}

int TMArrow::IsInView()
{
    if (g_pObjectManager->m_pCamera->m_fVerticalAngle >= -0.39269909f)
        return 1;

    bool bVisible = false;
    D3DXVECTOR3 vTemp{};
    D3DXVECTOR3 vPosTransformed{};
    D3DXVECTOR3 vecPos[9]{};
    for (int i = 0; i < 9; ++i)
    {
        vecPos[i].x = m_vecCurrentPos.x;
        vecPos[i].y = m_vecCurrentPos.y;
        vecPos[i].z = m_vecCurrentPos.z;
    }

    vecPos[1].x = vecPos[1].x - 1.0f;
    vecPos[2].x = vecPos[2].x + 1.0f;
    vecPos[3].z = vecPos[3].z - 1.0f;
    vecPos[4].z = vecPos[4].z + 1.0f;
    vecPos[5].x = vecPos[5].x - 1.0f;
    vecPos[5].z = vecPos[5].z - 1.0f;
    vecPos[6].x = vecPos[6].x - 1.0f;
    vecPos[6].z = vecPos[6].z + 1.0f;
    vecPos[7].x = vecPos[7].x + 1.0f;
    vecPos[7].z = vecPos[7].z - 1.0f;
    vecPos[8].x = vecPos[8].x + 1.0f;
    vecPos[8].z = vecPos[8].z + 1.0f;

    for (int i = 0; i < 9; ++i)
    {
        D3DXVec3TransformCoord(&vTemp, &vecPos[i], &g_pDevice->m_matView);
        D3DXVec3TransformCoord(&vPosTransformed, &vTemp, &g_pDevice->m_matProj);
        if (vPosTransformed.z >= -0.0099999998f && vPosTransformed.z < 1.0f)
        {
            int vPosInX = (int)(((vPosTransformed.x + 1.0f) * (float)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift)) / 2.0f);
            int vPosInY = (int)(((-vPosTransformed.y + 1.0f) * (float)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift)) / 2.0f);
            if (vPosInX > -30 && vPosInX < (int)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift + 30) && 
                vPosInY > -30 && vPosInY < (int)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift + 30))
            {
                return 1;
            }
        }
    }
    return bVisible;
}

int TMArrow::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMArrow::ReleaseEffect()
{
}
