#include "pch.h"
#include "TMObject.h"
#include "TMGlobal.h"
#include "TMSkinMesh.h"
#include "Basedef.h"
#include "TMLog.h"
#include "TMCamera.h"

TMObject::TMObject()
	: TreeNode(0)
{
	ResetObject();
}

TMObject::~TMObject()
{
	if (g_pObjectManager->m_pTargetObject == this)
		g_pObjectManager->m_pTargetObject = nullptr;

	SAFE_DELETE(m_pSkinMesh);
}

int TMObject::InitObject()
{
	return 1;
}

void TMObject::InitPosition(float fX, float fY, float fZ)
{
	SetPosition(fX, fY, fZ);
}

void TMObject::InitAngle(float fYaw, float fPitch, float fRoll)
{
	SetAngle(fYaw, fPitch, fRoll);
}

void TMObject::SetPosition(float fX, float fY, float fZ)
{
	m_vecPosition.x = fX;
	m_vecPosition.y = fZ;
	m_fHeight = fY;

	if (m_pSkinMesh != nullptr)
		m_pSkinMesh->SetPosition(fX, fY, fZ);
}

void TMObject::SetAngle(float fYaw, float fPitch, float fRoll)
{
	m_fAngle = fPitch;
	if (m_pSkinMesh)
		m_pSkinMesh->SetAngle(fYaw, fPitch, fRoll);
}

int TMObject::FrameMove(unsigned int dwServerTime)
{
	if (!isVisualKey() && m_dwObjType != 3)
		return 0;

	unsigned int dwServerTime = g_pTimerManager->GetServerTime();

	if (m_dwObjType == 443 && (int)m_vecPosition.x == 2540 && (int)m_vecPosition.y == 2086)
	{
		m_fHeight = 0.0f;
	}
	if (m_dwObjType == 454 && (int)m_vecPosition.x == 2542 && (int)m_vecPosition.y == 2090)
	{
		m_fHeight = 0.0f;
	}
	if (m_dwObjType == 454 && (int)m_vecPosition.x == 2540 && (int)m_vecPosition.y == 2082)
	{
		m_fHeight = 0.0f;
	}
	if (m_dwObjType == 449 && (int)m_vecPosition.x == 2540 && (int)m_vecPosition.y == 2094)
	{
		m_fHeight = 0.0f;
	}

	return 1;
}

int TMObject::Render()
{
	return 0;
}

int TMObject::IsVisible()
{
	return 0;
}

int TMObject::IsInTown()
{
	int nX4 = (int)m_vecPosition.x / 4;
	int nY4 = (int)m_vecPosition.y / 4;
	int nX128 = (int)m_vecPosition.x / 128;
	int nY128 = (int)m_vecPosition.y / 128; 
	
	if (nY4 < 1024 && nX4 < 1024 && nY4 >= 0 && nX4 >= 0)
		return (g_pAttribute[nY4][nX4] & 1) != 0;

	LOG_WRITELOG("\nWrong Position [X:%d Y:%d]\n", nX4, nY4);

	TMVector2 vec = g_pObjectManager->m_pCamera->GetFocusedObject()->m_vecPosition;

	int nMyX128 = (int)vec.x / 128;
	int nMyY128 = (int)vec.y / 128;

	if (nMyX128 == 13 && nMyY128 == 31 || nMyX128 == 14 && nMyY128 == 30 || nMyX128 == 15 && nMyY128 == 31 || nMyX128 == 18 && nMyY128 == 30)
	{
		g_pCurrentScene->m_bCriticalError = 0;
	}
}

int TMObject::IsInPKZone()
{
	return 0;
}

int TMObject::IsInCastleZone()
{
	return 0;
}

int TMObject::IsInCastleZone2()
{
	return 0;
}

int TMObject::IsChannelWarZone(int nPositionX, int nPositionY)
{
	return 0;
}

int TMObject::IsInHouse()
{
	return 0;
}

int TMObject::IsInView()
{
	return 0;
}

int TMObject::RegisterMask(TMGround* pGround, float fX, float fY)
{
	return 0;
}

void TMObject::Save(FILE* fp)
{
}

int TMObject::IsMouseOver()
{
	return 0;
}

int TMObject::isVisualKey()
{
	return 0;
}

int TMObject::isCamPos()
{
	return 0;
}

void TMObject::ResetObject()
{
}
