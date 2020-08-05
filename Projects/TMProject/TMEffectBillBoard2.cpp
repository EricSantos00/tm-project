#include "pch.h"
#include "TMEffectBillBoard2.h"
#include "TMGlobal.h"

TMEffectBillBoard2::TMEffectBillBoard2(int nTextureIndex, unsigned int dwLifeTime, float fScaleX, float fScaleY, float fScaleZ, float fVelocity, unsigned int dwVel) :
	m_vecScale{}
{
	m_fAxisAngle = 0.0f;
	m_dwCreateTime = 0;
	m_fLocalHeight = 0.0f;
	m_fProgress = 0.0f;
	m_dwLifeTime = dwLifeTime;
	m_vecScale.x = fScaleX;
	m_vecScale.y = fScaleY;
	m_vecScale.z = fScaleZ;
	m_fScaleVel = fVelocity;
	m_dwRotVel = dwVel;
	m_nTextureIndex = nTextureIndex;
	m_nFade = 1;
	m_pOwner = 0;
	m_bSlope = 0;

	m_vecPosition = TMVector3{ 0.0, 0.0, 0.0 };

	m_vertex[0].position = TMVector3{ -0.5f, 0.0f, -0.5f };
	m_vertex[1].position = TMVector3{ 0.5f, 0.0f, -0.5f };
	m_vertex[2].position = TMVector3{ 0.5f, 0.0f, 0.5f };
	m_vertex[3].position = TMVector3{ -0.5f, 0.0f, 0.5f };

	m_vertex[0].tu = 0.02f;
	m_vertex[0].tv = 0.02f;
	m_vertex[1].tu = 0.98000002f;
	m_vertex[1].tv = 0.02f;
	m_vertex[2].tu = 0.98000002f;
	m_vertex[2].tv = 0.98000002f;
	m_vertex[3].tu = 0.02f;
	m_vertex[3].tv = 0.98000002f;

	SetColor(0xFFFFFFFF);
}

TMEffectBillBoard2::~TMEffectBillBoard2()
{
}

int TMEffectBillBoard2::Render()
{
	return 0;
}

void TMEffectBillBoard2::SetColor(unsigned int dwColor)
{
}

int TMEffectBillBoard2::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMEffectBillBoard2::SetLifeTime(unsigned int dwLifeTime)
{
}
