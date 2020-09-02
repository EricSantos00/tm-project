#include "pch.h"
#include "TMEffectBillBoard2.h"
#include "TMFloat.h"
#include "TMGlobal.h"
#include "TMSkinMesh.h"

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
	return 1;
}

int TMFloat::FrameMove(unsigned int dwServerTime)
{
	return 1;
}

void TMFloat::RestoreDeviceObjects()
{
}

void TMFloat::InvalidateDeviceObjects()
{
}

void TMFloat::InitPosition(float fX, float fY, float fZ)
{
}
