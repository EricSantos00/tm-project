#include "pch.h"
#include "TMObject.h"
#include "TMGlobal.h"
#include "TMSkinMesh.h"
#include "Basedef.h"
#include "TMLog.h"
#include "TMCamera.h"
#include "TMMesh.h"

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
	else
	{
		if (!g_pCurrentScene->m_bCriticalError)
			g_pCurrentScene->LogMsgCriticalError(6, m_dwID, m_dwObjType, (int)m_vecPosition.x, (int)m_vecPosition.y);
		
		g_pCurrentScene->m_bCriticalError = 1;
	}

	return 0;
}

int TMObject::IsInPKZone()
{
	int nX4 = (int)m_vecPosition.x / 4;
	int nY4 = (int)m_vecPosition.y / 4;

	if (nY4 < 1024 && nX4 < 1024 && nY4 >= 0 && nX4 >= 0)
		return (g_pAttribute[nY4][nX4] & 0x40) != 0;

	LOG_WRITELOG("\nWrong Position [X:%d Y:%d]\n", nX4, nY4);

	if (!g_pCurrentScene->m_bCriticalError)
		g_pCurrentScene->LogMsgCriticalError(7, m_dwID, m_dwObjType, (int)m_vecPosition.x, (int)m_vecPosition.y);
	
	g_pCurrentScene->m_bCriticalError = 1;
	return 0;
}

int TMObject::IsInCastleZone()
{
	return 0;
}

int TMObject::IsInCastleZone2()
{
	int nX = (int)m_vecPosition.x;
	int nY = (int)m_vecPosition.y;

	if (nX >> 7 == 8 && nY >> 7 == 13 || 
		nX >> 7 == 8 && nY >> 7 == 15 || 
		nX >> 7 == 8 && nY >> 7 == 16 || 
		nX >> 7 == 9 && nY >> 7 == 15 || 
		nX >> 7 == 9 && nY >> 7 == 16)
		return 1;

	return 0;
}

int TMObject::IsChannelWarZone(int nPositionX, int nPositionY)
{
	return 0;
}

int TMObject::IsInHouse()
{
	int nX4 = (int)m_vecPosition.x / 4;
	int nY4 = (int)m_vecPosition.y / 4;
	if (nY4 < 1024 && nX4 < 1024 && nY4 >= 0 && nX4 >= 0)
		return (g_pAttribute[nY4][nX4] & 8) != 0;

	LOG_WRITELOG("\nWrong Position [X:%d Y:%d]\n", nX4, nY4);

	if (!g_pCurrentScene->m_bCriticalError)
			g_pCurrentScene->LogMsgCriticalError(9, m_dwID, m_dwObjType, (int)m_vecPosition.x, (int)m_vecPosition.y);

	g_pCurrentScene->m_bCriticalError = 1;
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
	fwrite(&m_dwObjType, 4u, 1u, fp);
	fwrite(&m_vecPosition, 8u, 1u, fp);
	fwrite(&m_fHeight, 4u, 1u, fp);
	fwrite(&m_fAngle, 4u, 1u, fp);
	fwrite(&m_nTextureSetIndex, 4u, 1u, fp);
	fwrite(&m_nMaskIndex, 4u, 1u, fp);
}

int TMObject::IsMouseOver()
{
	return 0;
}

int TMObject::isVisualKey()
{
	return m_bCheckKey != 1 || 
		m_dwKey == -1 ||
		m_dwKey == TreeNode::m_VisualKey1 || 
		m_dwKey == TreeNode::m_VisualKey2 || 
		m_dwKey == TreeNode::m_VisualKey3 || 
		m_dwKey == TreeNode::m_VisualKey4 || 
		m_dwKey == TreeNode::m_VisualKey5 || 
		m_dwKey == TreeNode::m_VisualKey6 || 
		m_dwKey == TreeNode::m_VisualKey7 || 
		m_dwKey == TreeNode::m_VisualKey8 || 
		m_dwKey == TreeNode::m_VisualKey9;
}

int TMObject::isCamPos()
{
	TMMesh *pMesh = g_pMeshManager->GetCommonMesh(m_dwObjType, 0, 180000);
	if (!pMesh)
		return 0;

	if (g_pCurrentScene->GroundGetMask(m_vecPosition) < 126)
		return 0;

	TMCamera* pCamera = g_pObjectManager->m_pCamera;

	D3DXVECTOR3 VecCam = D3DXVECTOR3(pCamera->m_cameraPos.x, pCamera->m_cameraPos.z, pCamera->m_cameraPos.y);
	D3DXVECTOR3 VecCenter = D3DXVECTOR3(pCamera->m_pFocusedObject->m_vecPosition.x, pCamera->m_pFocusedObject->m_vecPosition.y, pCamera->m_pFocusedObject->m_fHeight);
	D3DXVECTOR3 Vec = D3DXVECTOR3(m_vecPosition.x, m_vecPosition.y, m_fHeight) - VecCenter;

	if (D3DXVec3Dot(&Vec, &D3DXVECTOR3(pCamera->m_vecCamDir.x, pCamera->m_vecCamDir.z, pCamera->m_vecCamDir.y)) > 0.0f)
		return 0;

	D3DXVECTOR3 CamPos(pCamera->m_cameraPos.x, pCamera->m_cameraPos.y, pCamera->m_cameraPos.z);
	D3DXVECTOR3 CamDir(pCamera->m_vecCamDir.x, pCamera->m_vecCamDir.y, pCamera->m_vecCamDir.z);

	D3DXVECTOR3 vecPos[9];
	for (int i = 0; i < 9; ++i)
	{
		vecPos[i].x = m_vecPosition.x;
		vecPos[i].y = m_vecPosition.y;
		vecPos[i].z = m_fHeight;
	}

	vecPos[1].x = vecPos[3].x = vecPos[5].x = vecPos[7].x = vecPos[7].x + pMesh->m_fMinX;
	vecPos[1].z = vecPos[2].z = vecPos[5].z = vecPos[6].z = vecPos[6].z + pMesh->m_fMinY;
	vecPos[1].y = vecPos[2].y = vecPos[3].y = vecPos[4].y = vecPos[4].y + pMesh->m_fMinZ;

	vecPos[2].x = vecPos[4].x = vecPos[6].x = vecPos[8].x = vecPos[8].x + pMesh->m_fMaxX;
	vecPos[3].z = vecPos[4].z = vecPos[7].z = vecPos[8].z = vecPos[8].z + pMesh->m_fMaxY;
	vecPos[5].y = vecPos[6].y = vecPos[7].y = vecPos[8].y = vecPos[8].y + pMesh->m_fMaxZ;

	D3DXMATRIX matScale;
	D3DXMATRIX matPosition;
	D3DXMATRIX mat;
	D3DXMATRIX mat2;
	D3DXMatrixScaling(&matScale,pMesh->m_fScaleH, pMesh->m_fScaleV, pMesh->m_fScaleH);
	D3DXMatrixRotationYawPitchRoll(&mat, m_fAngle, D3DXToRadian(90), 0);
	D3DXMatrixMultiply(&mat, &g_pDevice->m_matWorld, &mat);
	D3DXMatrixMultiply(&mat, &mat, &matScale);

	for (int i = 0; i < 9; ++i)
	{
		D3DXMatrixTranslation(&matPosition, vecPos[i].x, vecPos[i].y, vecPos[i].z);
		D3DXMatrixMultiply(&mat2, &mat, &matPosition);
		vecPos[i].x = mat2._41;
		vecPos[i].y = mat2._42;
		vecPos[i].z = mat2._43;
	}

	int nAlpha = 0;
	if (D3DXIntersectTri(&vecPos[1], &vecPos[2], &vecPos[5], &CamPos, &CamDir, 0, 0, 0) == 1)
		nAlpha = 1;
	else if (D3DXIntersectTri(&vecPos[5], &vecPos[6], &vecPos[1], &CamPos, &CamDir, 0, 0, 0) == 1)
		nAlpha = 1;
	else if (D3DXIntersectTri(&vecPos[1], &vecPos[4], &vecPos[6], &CamPos, &CamDir, 0, 0, 0) == 1)
		nAlpha = 1;
	else if (D3DXIntersectTri(&vecPos[6], &vecPos[8], &vecPos[4], &CamPos, &CamDir, 0, 0, 0) == 1)
		nAlpha = 1;
	else if (D3DXIntersectTri(&vecPos[3], &vecPos[4], &vecPos[7], &CamPos, &CamDir, 0, 0, 0) == 1)
		nAlpha = 1;
	else if (D3DXIntersectTri(&vecPos[7], &vecPos[8], &vecPos[4], &CamPos, &CamDir, 0, 0, 0) == 1)
		nAlpha = 1;
	else if (D3DXIntersectTri(&vecPos[1], &vecPos[3], &vecPos[5], &CamPos, &CamDir, 0, 0, 0) == 1)
		nAlpha = 1;
	else if(D3DXIntersectTri(&vecPos[5], &vecPos[7], &vecPos[3], &CamPos, &CamDir, 0, 0, 0) == 1)
		nAlpha = 1;

	float fRadius = 1.0f;
	fRadius = pMesh->m_fRadius;
	if (nAlpha == 1)
	{
		TMVector2 Position(CamPos.x, CamPos.z);
		if (g_pCurrentScene->GroundGetMask(Position) > 125)
			nAlpha = 2;
	}

	return nAlpha;
}

void TMObject::ResetObject()
{
	m_dwID = -1;
	m_bCheckKey = 1;
	m_dwObjType = -1;
	m_pSkinMesh = 0;
	m_bVisible = 0;
	m_bNullObj = 0;
	m_fAngle = 0.0;
	m_fScale = 1.0f;
	m_vecSkinPos = TMVector3(0.0f, 0.0, 0.0f);
	m_nTextureSetIndex = -1;
	m_nMaskIndex = -1;

	for (int i = 0; i < 10; ++i)
	{
		m_vecTempPos[i] = TMVector3(0.0f, 0.0, 0.0f);
	}

	m_nAlpha = 0;
	m_AlphaColor = 0.0;
	m_bAlphaObj = 0;
	m_cDeleted = 0;
	m_dwKey = -1;

	m_vecPosition = TMVector2(0.0f, 0.0f);

	m_fHeight = 0.0;
	m_nSkinMeshType = 0;
}
