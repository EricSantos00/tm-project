#include "pch.h"
#include "TMShip.h"
#include "TMSkinMesh.h"
#include "TMGlobal.h"

TMShip::TMShip(int nType) :
    TMObject(),
	m_vecMoveToPos{}
{
	m_dwObjType = nType;
	m_pSkinMesh = 0;
	m_fMaxSpeed = 1.0f;
	m_fMaxAngleSpeed = 1.0f;
	m_nSkinMeshType = 60;
	memset(&m_stLookInfo, 0, sizeof(m_stLookInfo));
	memset(&m_stSancInfo, 0, sizeof(m_stSancInfo));
	m_stLookInfo.Mesh0 = nType - 487;
}

TMShip::~TMShip()
{
}

int TMShip::InitObject()
{
    if (!m_pSkinMesh)
    {
        m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, 0, 0, 0, 0);

        if (m_pSkinMesh)
            m_pSkinMesh->RestoreDeviceObjects();
    }
    return 1;
}

int TMShip::Render()
{
    if (g_bHideBackground == 1)
        return 0;

    if (m_dwKey != -1 &&
        m_dwKey != TreeNode::m_VisualKey1 &&
        m_dwKey != TreeNode::m_VisualKey2 &&
        m_dwKey != TreeNode::m_VisualKey3 &&
        m_dwKey != TreeNode::m_VisualKey4)
    {
        return 0;
    }

    TMObject::Render();

    if (m_pSkinMesh)
    {
        if (m_bVisible == 1)
        {
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
            m_pSkinMesh->Render(0.0f, 1.0f, 0.0f);
            g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
        }
    }
    return 1;
}

int TMShip::FrameMove(unsigned int dwServerTime)
{
    if (m_dwKey != -1 &&
        m_dwKey != TreeNode::m_VisualKey1 &&
        m_dwKey != TreeNode::m_VisualKey2 && 
        m_dwKey != TreeNode::m_VisualKey3 &&
        m_dwKey != TreeNode::m_VisualKey4)
    {
        return 0;
    }

    dwServerTime = g_pTimerManager->GetServerTime();

    if (IsVisible() == 1)
    {
        memset(&m_pSkinMesh->m_materials, 0, sizeof(m_pSkinMesh->m_materials));

        m_pSkinMesh->m_materials.Emissive.r = 0.30000001f;
        m_pSkinMesh->m_materials.Emissive.g = 0.30000001f;
        m_pSkinMesh->m_materials.Emissive.b = 0.30000001f;
        m_pSkinMesh->m_materials.Diffuse.r = 0.69999999f;
        m_pSkinMesh->m_materials.Diffuse.g = 0.69999999f;
        m_pSkinMesh->m_materials.Diffuse.b = 0.69999999f;
        m_pSkinMesh->m_materials.Diffuse.a = 0.0f;
        m_pSkinMesh->m_materials.Specular.r = m_pSkinMesh->m_materials.Diffuse.r;
        m_pSkinMesh->m_materials.Specular.g = m_pSkinMesh->m_materials.Diffuse.g;
        m_pSkinMesh->m_materials.Specular.b = m_pSkinMesh->m_materials.Diffuse.b;
        m_pSkinMesh->m_materials.Specular.a = m_pSkinMesh->m_materials.Diffuse.a;
        m_pSkinMesh->m_materials.Power = 0.0f;
        m_pSkinMesh->FrameMove(dwServerTime);
    }
    return 1;
}

void TMShip::MoveTo(TMVector2 vecPos)
{
    m_vecMoveToPos = vecPos;

    TMVector2 dPosition = m_vecMoveToPos - m_vecPosition;

    m_fMoveToAngle = atan2f(dPosition.x, dPosition.y);

    float fAngleDiff = m_fMoveToAngle - m_fAngle;

    if (fAngleDiff > 3.1400001f)
         m_fAngle += 6.2800002f;
    else if (fAngleDiff < -3.1400001f)
        m_fMoveToAngle += 6.2800002f;
}

void TMShip::InitPosition(float fX, float fY, float fZ)
{
    TMObject::SetPosition(fX, fY, fZ);

    m_vecMoveToPos = m_vecPosition;
}

void TMShip::InitAngle(float fYaw, float fPitch, float fRoll)
{
    m_fAngle = fPitch;

    if (m_pSkinMesh)
        m_pSkinMesh->SetAngle(fYaw, fPitch + 1.5707964f, fRoll);

    m_fMoveToAngle = m_fAngle;
}

void TMShip::RestoreDeviceObjects()
{
    if (m_pSkinMesh == nullptr)
        m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, 0, 0, 0, 0);

    if (m_pSkinMesh)
        m_pSkinMesh->RestoreDeviceObjects();
}

void TMShip::InvalidateDeviceObjects()
{
    if (m_pSkinMesh)
        m_pSkinMesh->InvalidateDeviceObjects();
}
