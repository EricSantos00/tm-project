#include "pch.h"
#include "TMFish.h"
#include "TMGlobal.h"
#include "TMSkinMesh.h"

TMFish::TMFish(unsigned int dwObjType, int nType)
	: TMObject(),
	m_vecStartPos{}
{
	m_dwObjType = dwObjType;
	m_nType = nType;
	m_nMotionType = rand() % 3;
	m_fScale = ((float)(rand() % 10) * 0.1f) + 1.0f;
	m_dwStartTime = 0;
	m_pSkinMesh = 0;
	m_nSkinMeshType = 70;
	m_stLookInfo = {};
	m_stSancInfo = {};
	if (!nType)
	{
		m_stLookInfo.Mesh0 = rand() % 3;
		m_stSancInfo.Sanc0 = rand() % 3 + 7;
	}
	else
	{
		m_stLookInfo.Mesh0 = nType % 3;
		m_stSancInfo.Sanc0 = nType + 1;
	}

	m_fCircleSpeed = ((float)(rand() % 10) * 0.1f) + 0.7f;
	m_fParticleH = ((float)(rand() % 7) * 0.5f) + 3.0f;
}

TMFish::~TMFish()
{
}

int TMFish::InitObject()
{
	if (m_pSkinMesh)
		return 1;

	m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, nullptr, 0, 0, 0);
	m_pSkinMesh->m_vScale.z = m_fScale;
	m_pSkinMesh->m_vScale.y = m_pSkinMesh->m_vScale.z;
	m_pSkinMesh->m_vScale.x = m_pSkinMesh->m_vScale.y;
	m_pSkinMesh->m_dwFPS = 30;
	m_pSkinMesh->RestoreDeviceObjects();
	return 1;
}

int TMFish::Render()
{
	if (g_bHideBackground == 1)
		return 0;

	if (m_pSkinMesh && IsVisible() == 1)
	{
		if (g_pDevice->m_dwBitCount == 32)
			g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xAAu);
		else
			g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xFFu);

		m_pSkinMesh->Render(0.0f, 1.0f, 0.0f);
	}
	return 1;
}

int TMFish::FrameMove(unsigned int dwServerTime)
{
    if (m_pSkinMesh)
    {
        dwServerTime = g_pTimerManager->GetServerTime();
        unsigned int dwOffset = (unsigned int)((((((m_fParticleH * 12.0f) + (m_fCircleSpeed * 12.0f)) + 
            (float)(20 * ((unsigned int)this % 100))) + (float)(10 * m_stLookInfo.Mesh0)) + (m_fScale * 10.0f)) + (float)(5 * m_nMotionType));

        float fProgress = sinf((((float)((dwOffset + dwServerTime - m_dwStartTime) % 40000) / 40000.0f) * D3DXToRadian(180)) * 2.0f);
        if (m_nMotionType == 0)
        {
            float fSin = sinf(((fProgress * D3DXToRadian(180)) * m_fCircleSpeed) + ((float)dwOffset * 0.05f));
            m_vecPosition.x = ((fProgress * m_fParticleH) * 0.4f) + m_vecStartPos.x;
            m_vecPosition.y = ((fSin * m_fParticleH) * 0.3f) + m_vecStartPos.z;
            m_fAngle = atan2f(m_vecPosition.x, m_vecPosition.y);
        }
        else if (m_nMotionType == 1)
        {
            float fCos = cosf(((fProgress * D3DXToRadian(180)) * m_fCircleSpeed) + ((float)dwOffset * 0.05f));
            m_vecPosition.x = ((fCos * m_fParticleH) * 0.4f) + m_vecStartPos.x;
            m_vecPosition.y = ((fProgress * m_fParticleH) * 0.3f) + m_vecStartPos.z;
            m_fAngle = atan2f(m_vecPosition.x, m_vecPosition.y);
        }
        else if (m_nMotionType == 2)
        {
            float fSinf = sinf(((fProgress * 2.0f) * D3DXToRadian(180)) + (float)((float)dwOffset * 0.05f));
            float fCosf = cosf(((fProgress * 2.0f) * D3DXToRadian(180)) + (float)((float)dwOffset * 0.05f));
            m_vecPosition.x = ((fCosf * m_fParticleH) * 0.1f) + m_vecStartPos.x;
            m_vecPosition.y = ((fSinf * m_fParticleH) * 0.1f) + m_vecStartPos.z;
            m_fAngle = atan2f(m_vecPosition.x, m_vecPosition.y);
        }

        SetAngle(0, m_fAngle, 0);
        SetPosition(m_vecPosition.x, m_fHeight, m_vecPosition.y);
        if (IsVisible() == 1)
        {
            auto color = g_pCurrentScene->GroundGetColor(m_vecPosition);
            color.r = (color.r * 0.2f) + (g_pDevice->m_colorLight.r * 0.5f);
            color.g = (color.g * 0.2f) + (g_pDevice->m_colorLight.g * 0.5f);
            color.b = (color.b * 0.2f) + (g_pDevice->m_colorLight.b * 0.5f);
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
            m_pSkinMesh->FrameMove(dwOffset + dwServerTime);
        }
    }
    return 1;
}

void TMFish::RestoreDeviceObjects()
{
    if(!m_pSkinMesh)
        m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, nullptr, 0, 0, 0);

    m_pSkinMesh->RestoreDeviceObjects();
}

void TMFish::InvalidateDeviceObjects()
{
    if (m_pSkinMesh)
        m_pSkinMesh->InvalidateDeviceObjects();
}

void TMFish::InitPosition(float fX, float fY, float fZ)
{
    TMObject::InitPosition(fX, fY, fZ);
    m_vecStartPos.x = fX;
    m_vecStartPos.y = fY;
    m_vecStartPos.z = fZ;
    m_dwStartTime = g_pTimerManager->GetServerTime();
}

void TMFish::SetAnimation(int nAniIndex)
{
    if (m_pSkinMesh)
        m_pSkinMesh->SetAnimation(nAniIndex);
}
