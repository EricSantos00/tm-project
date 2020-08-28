#include "pch.h"
#include "TMEffectBillBoard3.h"
#include "TMGlobal.h"

TMEffectBillBoard3::TMEffectBillBoard3(TMVector3 vecStart, TMVector3 vecEnd, int nTextureIndex, unsigned int dwColor, unsigned int dwLifeTime, float fScaleH, float fScaleV) :
	m_vecStartPos{},
	m_vecEndPos{}
{
	m_fScaleH = fScaleH;
	m_fScaleV = fScaleV;
	m_nTextureIndex = nTextureIndex;
	m_dwLifeTime = dwLifeTime;
	m_nFade = 0;

	m_vertex1[0].position = TMVector3{ vecStart.x, vecStart.y - m_fScaleV, vecStart.z };
	m_vertex1[1].position = TMVector3{ vecEnd.x, vecEnd.y - m_fScaleV, vecEnd.z };
	m_vertex1[2].position = TMVector3{ vecEnd.x, vecEnd.y + m_fScaleV, vecEnd.z };
	m_vertex1[3].position = TMVector3{ vecStart.x, vecStart.y + m_fScaleV, vecStart.z };

	m_vertex1[0].tu = 0.02f;
	m_vertex1[0].tv = 0.98000002f;
	m_vertex1[1].tu = 0.98000002f;
	m_vertex1[1].tv = 0.98000002f;
	m_vertex1[2].tu = 0.98000002f;
	m_vertex1[2].tv = 0.02f;
	m_vertex1[3].tu = 0.02f;
	m_vertex1[3].tv = 0.02f;

	m_vertex2[0].position = TMVector3{ vecStart.x - m_fScaleV, vecStart.y, vecStart.z };
	m_vertex2[1].position = TMVector3{ vecEnd.x - m_fScaleV, vecEnd.y, vecEnd.z };
	m_vertex2[2].position = TMVector3{ vecEnd.x + m_fScaleV, vecEnd.y, vecEnd.z };
	m_vertex2[3].position = TMVector3{ vecStart.x + m_fScaleV, vecStart.y, vecStart.z };

	m_vertex2[0].tu = 0.02f;
	m_vertex2[0].tv = 0.98000002f;
	m_vertex2[1].tu = 0.98000002f;
	m_vertex2[1].tv = 0.98000002f;
	m_vertex2[2].tu = 0.98000002f;
	m_vertex2[2].tv = 0.02f;
	m_vertex2[3].tu = 0.02f;
	m_vertex2[3].tv = 0.02f;
	SetColor(dwColor);
	m_dwShortTime = 0;
	m_dwCreateTime = g_pTimerManager->GetServerTime();
}

TMEffectBillBoard3::~TMEffectBillBoard3()
{
}

int TMEffectBillBoard3::Render()
{
	return 0;
}

void TMEffectBillBoard3::SetColor(unsigned int dwColor)
{
}

int TMEffectBillBoard3::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMEffectBillBoard3::SetPosition(TMVector3 vecStart, TMVector3 vecEnd)
{
}

void TMEffectBillBoard3::SetShort(unsigned int dwTime)
{
}
