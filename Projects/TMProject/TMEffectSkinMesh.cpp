#include "pch.h"
#include "TMEffectSkinMesh.h"
#include "DXUtil.h"
#include "TMGlobal.h"
#include "TMSkillFire.h"

TMEffectSkinMesh::TMEffectSkinMesh(int nSkinMeshType, TMVector3 vecStart, TMVector3 vecTarget, int nLevel, TMObject* pOwner)
{
	m_dwObjType = 331;
	m_pSkinMesh = 0;
	m_pSkinMesh2 = 0;
	m_nSkinMeshType = nSkinMeshType;
	m_nSkinMeshType2 = -1;
	m_fScale2 = 1.0f;
	m_dwStartTime = 0;
	m_dwLifeTime = 0;
	m_nMotionType = 0;
	m_fAngle = 0.0;
	m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
	m_StartColor.r = 1.0f;
	m_StartColor.g = 1.0f;
	m_StartColor.b = 1.0f;
	m_EndColor.r = 1.0f;
	m_EndColor.g = 1.0f;
	m_EndColor.b = 1.0f;
	m_color.r = 1.0f;
	m_color.g = 1.0f;
	m_color.b = 1.0f;
	m_nFade = 0;
	m_nLevel = nLevel;
	m_pOwner = pOwner;

	m_vecStartPos = vecStart;
	m_vecTargetPos = vecTarget;

	m_dwLastSpeedUp = 0;
	auto vecD = vecTarget - vecStart;
	auto fLength = vecD.Length();

	m_dwLifeTime = 200 * (unsigned int)fLength;

	if (!m_dwLifeTime)
		m_dwLifeTime = 1;

	if (m_dwLifeTime > 5000u)
		m_dwLifeTime = 5000u;

	m_stLookInfo = {};
	m_stSancInfo = {};
	m_stLookInfo2 = {};
	m_bMirror = 0;
}

TMEffectSkinMesh::~TMEffectSkinMesh()
{
	SAFE_DELETE(m_pSkinMesh2);

	if (m_nLevel || m_nMotionType != 2)
	{
		TMEffectSkinMesh* pEffect = nullptr;
		if (m_nLevel == 1)
			pEffect = new TMEffectSkinMesh(20, m_vecTargetPos, {}, 0, m_pOwner);

		if (pEffect)
		{
			pEffect->m_stLookInfo = m_stLookInfo;
			pEffect->InitObject(0);
			pEffect->m_dwLifeTime = 3000;
			pEffect->m_pSkinMesh->m_vScale.x = 0.2f;
			pEffect->m_pSkinMesh->m_vScale.y = 0.2f;
			pEffect->m_pSkinMesh->m_vScale.z = 0.2f;
			pEffect->m_efAlphaType = EEFFECT_ALPHATYPE::EF_DEFAULT;
			pEffect->m_StartColor.r = 1.0f;
			pEffect->m_StartColor.g = 1.0f;
			pEffect->m_StartColor.b = 1.0f;
			pEffect->m_nFade = 0;
			pEffect->m_fStartAngle = m_fAngle;
			pEffect->m_nMotionType = 3;

			g_pCurrentScene->m_pEffectContainer->AddChild(pEffect);
		}
	}
	else
	{
		TMSkillFire* pFire = new TMSkillFire(m_vecTargetPos, 0, nullptr, 0xFFFFFFFF, 0x22331100);

		if (pFire)
			g_pCurrentScene->m_pEffectContainer->AddChild(pFire);
	}
}

int TMEffectSkinMesh::InitObject(int bExpand)
{
	if (m_nSkinMeshType2 >= 0)
	{
		if (!m_pSkinMesh)
		{
			m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, 0, nullptr, 0, 0, 0);

			if (m_pSkinMesh)
			{
				m_pSkinMesh->RestoreDeviceObjects();

				// this is not a TMHuman object. We cannot use static_cast.
				// Maybe this is wrong or some class was decompiled with the wrong inheritance
				// This will crash...
				m_pSkinMesh->m_pOwner = (TMHuman*)this;
				m_pSkinMesh->m_dwFPS = 80;
				m_pSkinMesh->m_bBaseMat = 0;
			}
		}

		if (m_nMotionType == 10 && m_pSkinMesh)
		{
			m_pSkinMesh->m_dwStartTime = 0;
			m_pSkinMesh->m_dwStartOffset = g_pTimerManager->GetServerTime();
		}

		if (!m_pSkinMesh2)
		{
			m_pSkinMesh2 = new TMSkinMesh(&m_stLookInfo2, &m_stSancInfo, m_nSkinMeshType2, bExpand, nullptr, 0, 0, 0);

			if (m_pSkinMesh2)
			{
				m_pSkinMesh2->RestoreDeviceObjects();
				m_pSkinMesh2->m_dwFPS = 80;

				if (m_nSkinMeshType != 20 || m_stLookInfo2.Mesh0 != 7)
				{
					if (m_nSkinMeshType == 20)
						m_pSkinMesh2->SetVecMantua(3, m_nSkinMeshType);
					else
						m_pSkinMesh2->SetVecMantua(2, m_nSkinMeshType);
				}
				else
				{
					m_pSkinMesh2->SetVecMantua(4, m_nSkinMeshType);
				}
			}
		}

		return 1;
	}

	if (!m_pSkinMesh)
	{
		m_pSkinMesh = new TMSkinMesh(&m_stLookInfo, &m_stSancInfo, m_nSkinMeshType, bExpand, nullptr, 0, 0, 0);

		if (m_pSkinMesh)
		{
			m_pSkinMesh->RestoreDeviceObjects();
			m_pSkinMesh->m_vScale.x = m_fScale;
			m_pSkinMesh->m_vScale.y = m_fScale;
			m_pSkinMesh->m_vScale.z = m_fScale;
			m_pSkinMesh->m_dwFPS = 80;
		}
	}

	if (m_nMotionType == 10 && m_pSkinMesh)
	{
		m_pSkinMesh->m_dwStartTime = 0;
		m_pSkinMesh->m_dwStartOffset = g_pTimerManager->GetServerTime();
	}

	return 1;
}

int TMEffectSkinMesh::Render()
{
	return 0;
}

int TMEffectSkinMesh::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMEffectSkinMesh::RestoreDeviceObjects()
{
}

void TMEffectSkinMesh::InvalidateDeviceObjects()
{
}

void TMEffectSkinMesh::InitPosition(float fX, float fY, float fZ)
{
}
