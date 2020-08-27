#include "pch.h"
#include "TMObject.h"
#include "TMEffectBillBoard.h"
#include "TMEffectMeshRotate.h"
#include "TMGlobal.h"

TMEffectMeshRotate::TMEffectMeshRotate(TMVector3 vecPosition, int nType, TMObject* pOwner, int bFire, int bCenter) :
	m_vecStartPos{ vecPosition }
{
	m_nType = nType;
	m_fRadius = 1.0f;
	m_fScale = 1.0f;

	if (m_nType == 1)
		m_dwRotateTime = 2000;
	else
		m_dwRotateTime = 1000;

	m_bScale = 0;
	m_vecPosition = m_vecStartPos;

	m_dwStartTime = 100 * ((unsigned int)this % 10) + g_pTimerManager->GetServerTime();
	if (m_nType == 2)
		m_dwStartTime = g_pTimerManager->GetServerTime();
	m_pOwner = pOwner;
	m_bCenter = bCenter;
	m_nMeshIndex = -1;
	m_pBillBoard = 0;
	m_dwLifeTime = 0;

	if (bFire == 1)
	{
		if (m_nType == 0)
		{
			m_pBillBoard = new TMEffectBillBoard(11, 0, 0.80000001f, 1.0f, 0.80000001f, 0.0f, 8, 80);

			if (m_pBillBoard)
			{
				m_pBillBoard->SetColor(0xFF440000);
				m_pBillBoard->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				m_pBillBoard->m_nFade = 0;
				m_pBillBoard->m_vecPosition = m_vecStartPos;
				g_pCurrentScene->m_pEffectContainer->AddChild(m_pBillBoard);
			}
		}
		else if (m_nType == 1)
		{
			m_pBillBoard = new TMEffectBillBoard(56, 0, 1.5f, 1.5f, 1.5f, 0.0f, 1, 80);

			if (m_pBillBoard)
			{
				m_pBillBoard->SetColor(0xFF55AAFF);
				m_pBillBoard->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
				m_pBillBoard->m_nFade = 2;
				m_pBillBoard->m_vecPosition = m_vecStartPos;
				g_pCurrentScene->m_pEffectContainer->AddChild(m_pBillBoard);
			}
		}
	}

	m_fAngle2 = 0.0f;
	SetColor(0xFFFFFFFF);
}

TMEffectMeshRotate::~TMEffectMeshRotate()
{
}

int TMEffectMeshRotate::Render()
{
	return 0;
}

int TMEffectMeshRotate::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMEffectMeshRotate::SetColor(unsigned int dwColor)
{
}
