#include "pch.h"
#include "TMEffectSkinMesh.h"

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
}

int TMEffectSkinMesh::InitObject(int bExpand)
{
	return 0;
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
