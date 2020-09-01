#include "pch.h"
#include "TMEffectBillBoard3.h"
#include "TMEffectMesh.h"
#include "TMArrow.h"
#include "TMGlobal.h"
#include "TMUtil.h"
#include "TMEffectBillBoard3.h"
#include "TMCamera.h"

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
	return 0;
}

int TMArrow::IsVisible()
{
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
