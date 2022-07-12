#include "pch.h"
#include "TMObject.h"
#include "TMGlobal.h"
#include "TMSkinMesh.h"
#include "Basedef.h"
#include "TMLog.h"
#include "TMCamera.h"
#include "TMMesh.h"
#include "TMGround.h"
#include "TMSky.h"

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

	dwServerTime = g_pTimerManager->GetServerTime();

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
	if (g_bHideBackground == 1)
		return 0;
	if (!isVisualKey())
	{
		if (m_dwObjType != 1562)
			return 0;
		if (g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_SELCHAR)
			return 0;
	}
	if (m_dwObjType == -1)
		return 1;
	if (m_bNullObj == 1)
		return 1;
	if (!IsVisible())
		return 1;

	TMScene* pScene = (TMScene*)g_pCurrentScene;
	D3DMATERIAL9 materials{};
	D3DCOLORVALUE color;
	if (!RenderDevice::m_bDungeon || RenderDevice::m_bDungeon == 3 || RenderDevice::m_bDungeon == 4)
	{
		color.r = 0.69999999f;
		color.g = 0.69999999f;
		color.b = 0.69999999f;
		color.a = 1.0f;
		materials.Emissive.r = 0.30000001f;
		materials.Emissive.g = 0.30000001f;
		materials.Emissive.b = 0.30000001f;
		materials.Emissive.a = 1.0f;
		materials.Diffuse.r = 0.69999999f;
		materials.Diffuse.g = 0.69999999f;
		materials.Diffuse.b = 0.69999999f;
		materials.Diffuse.a = 1.0f;
		materials.Specular.r = 0.69999999f;
		materials.Specular.g = 0.69999999f;
		materials.Specular.b = 0.69999999f;
		materials.Specular.a = 1.0f;
		materials.Power = 0.0;
	}
	else
	{
		D3DCOLORVALUE result = g_pCurrentScene->GroundGetColor(m_vecPosition);
		result.r = (float)(result.r * 0.5f) + (float)(g_pDevice->m_colorLight.r * 0.5f);
		result.g = (float)(result.g * 0.5f) + (float)(g_pDevice->m_colorLight.g * 0.5f);
		result.b = (float)(result.b * 0.5f) + (float)(g_pDevice->m_colorLight.b * 0.5f);
		result.a = 1.0f;
		materials.Specular.a = 1.0f;
		materials.Emissive.a = 1.0f;
		materials.Diffuse.r = result.r;
		materials.Diffuse.g = result.g;
		materials.Diffuse.b = result.b;
		materials.Diffuse.a = 1.0f;
		materials.Specular.r = 1.0f;
		materials.Specular.g = 1.0f;
		materials.Specular.b = 1.0f;
		materials.Emissive.r = (float)(g_pDevice->m_colorBackLight.r * 0.3f) + (float)(result.r * 0.4f);
		materials.Emissive.g = (float)(g_pDevice->m_colorBackLight.g * 0.3f) + (float)(result.r * 0.4f);
		materials.Emissive.b = (float)(g_pDevice->m_colorBackLight.b * 0.3f) + (float)(result.r * 0.4f);
	}

	g_pDevice->SetRenderState(D3DRS_FOGENABLE, g_pDevice->m_bFog);

	int nAlpha = 0;
	if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
	{
		if (m_bAlphaObj == 1)
		{
			if (((int)m_vecPosition.x >> 7 == 31 && (int)m_vecPosition.y >> 7 == 31) ||
				((int)m_vecPosition.x >> 7 > 16 && (int)m_vecPosition.x >> 7 < 20 && (int)m_vecPosition.y >> 7 > 29) ||
				((int)m_vecPosition.x >> 7 == 13 || (int)m_vecPosition.x >> 7 == 14 && (int)m_vecPosition.y >> 7 == 28))
			{
				nAlpha = isCamPos();
				if (nAlpha)
					m_nAlpha = nAlpha;
			}
		}
	}

	if (m_nAlpha != 0)
	{
		if (!nAlpha)
		{
			if (m_AlphaColor >= 0.94999999f)
			{
				m_AlphaColor = 1.0f;
				m_nAlpha = 0;
			}
			else
				m_AlphaColor += 0.05f;
		}
		else if (m_AlphaColor <= 0.75f)
			m_AlphaColor = 0.69999999f;
		else
			m_AlphaColor -= 0.02f;;

		color.b = 0.69f;
		color.g = 0.69f;
		color.r = 0.69f;
		color.a = m_AlphaColor;
		materials.Diffuse.r = 0.69f;
		materials.Diffuse.g = 0.69f;
		materials.Diffuse.b = 0.69f;
		materials.Diffuse.a = color.a;

		if (g_pDevice->m_iVGAID == 1)
		{
			if (g_pDevice->m_dwBitCount == 32)
				g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xFF000000);
			else
				g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xF000u);
		}
		else if (g_pDevice->m_dwBitCount == 32)
		{
			g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xDDu);
		}
		else
		{
			g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xDu);
		}

		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, 0);

		if (nAlpha == 2 && !m_bAlphaObj)
			g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
	}
	else
	{
		m_AlphaColor = 1.0f;
	}

	if (g_pDevice->m_bVoodoo == 1)
	{
		g_pDevice->m_pd3dDevice->SetMaterial(&materials);

		TMObject* pFocused = g_pObjectManager->m_pCamera->GetFocusedObject();

		if (pFocused != nullptr
			&& pFocused->m_vecPosition.x > m_vecPosition.x
			&& pFocused->m_vecPosition.y > m_vecPosition.y
			&& (m_dwObjType < 251 || m_dwObjType > 254))
		{
			g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
			g_pDevice->SetRenderState(D3DRS_DESTBLEND, 9u);
		}
		else 
			g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);

		g_pDevice->SetTexture(1u, 0);
		g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
		TMMesh* pMesh = g_pMeshManager->GetCommonMesh(m_dwObjType, 0, 3_min);

		if (pMesh == nullptr)
			return 0;

		pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, m_fAngle, 0, 0, 0, 0);
		g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
		g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
		return 1;
	}

	TMMesh *pMesh = g_pMeshManager->GetCommonMesh(m_dwObjType, 0, 3_min);
	if (pMesh == nullptr)
		return 0;

	g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
	if (!m_nAlpha)
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);

	if (g_pTextureManager->m_stModelTextureList[pMesh->m_nTextureIndex[0]].cAlpha != 'N' || m_dwObjType >= 156 && m_dwObjType <= 185)
	{
		if (g_pDevice->m_dwBitCount == 32)
			g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xAAu);
		else
			g_pDevice->SetRenderState(D3DRS_ALPHAREF, 0xFFu);

		g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
		g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
		g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
		g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
		g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
		g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
	}
	else
	{
		g_pDevice->SetTexture(1u, 0);
		g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
	}

	g_pDevice->m_pd3dDevice->SetMaterial(&materials);
	if (m_dwObjType == 1934 || m_dwObjType == 1976 || m_dwObjType == 1977)
	{
		g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 0xBu);
		g_pDevice->SetTexture(1u, g_pTextureManager->GetEffectTexture(g_pCurrentScene->m_pSky->m_nTextureIndex, 5000));
		g_pDevice->SetTextureStageState(1u, D3DTSS_TEXTURETRANSFORMFLAGS, 2u);
		g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 0x30000u);
	}

	pMesh->Render(m_vecPosition.x, m_fHeight, m_vecPosition.y, m_fAngle, 0, 0, 0, 0);

	if (m_dwObjType == 1934 || m_dwObjType == 1976 || m_dwObjType == 1977)
		g_pDevice->SetTextureStageState(1u, D3DTSS_TEXTURETRANSFORMFLAGS, 0);

	if (m_nAlpha)
	{
		g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
		g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
		g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
		g_pDevice->SetTextureStageState(1u, D3DTSS_ALPHAOP, 2u);
		if (nAlpha == 2)
			g_pDevice->SetRenderState(D3DRS_CULLMODE, 2u);
	}

	g_pDevice->SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
	g_pDevice->SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);

	return 1;
}

int TMObject::IsVisible()
{
	if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR)
	{
		if (m_dwObjType == 1562)
		{
			m_bVisible = 1;
			return 1;
		}
		if (m_dwObjType == 3)
		{
			m_bVisible = 1;
			return 1;
		}
		if (m_dwObjType == 506)
		{
			m_bVisible = 1;
			return 1;
		}
	}

	if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_DEMO && !g_pCursor->m_bVisible && m_dwObjType == 3)
	{
		m_bVisible = 1;
		return 1;
	}

	TMMesh * pMesh = g_pMeshManager->GetCommonMesh(m_dwObjType, 0, 3_min);
	if (pMesh == nullptr)
	{
		m_bVisible = 0;
		return 0;
	}

	TMCamera* pCamera = g_pObjectManager->m_pCamera;
	D3DXVECTOR3 VecCam = D3DXVECTOR3(pCamera->m_cameraPos.x, pCamera->m_cameraPos.z, pCamera->m_cameraPos.y);
	D3DXVECTOR3 Vec = D3DXVECTOR3(m_vecPosition.x, m_vecPosition.y, m_fHeight) - VecCam;

	if (pMesh->m_fRadius >= D3DXVec3Length(&Vec))
	{
		m_bVisible = 1;
		return 1;
	}

	auto pV2 = D3DXVECTOR3(pCamera->m_vecCamDir.x, pCamera->m_vecCamDir.z, pCamera->m_vecCamDir.y);
	if (D3DXVec3Dot(&Vec, &pV2) <= 0.0f)
	{
		m_bVisible = 0;
		return 0;
	}

	m_bVisible = IsInView();

	return m_bVisible;
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
	TMCamera* pCamera = g_pObjectManager->m_pCamera;
	TMMesh* pMesh = g_pMeshManager->GetCommonMesh(m_dwObjType, 0, 3_min);
	if (!pMesh)
		return 0;

	D3DXVECTOR3 vPosTransformed[9]{};
	D3DXVECTOR3 vecPos[9]{};

	D3DXVECTOR3 vecCenter = D3DXVECTOR3(m_vecPosition.x, 0.0f, m_vecPosition.y);

	D3DXVECTOR3 vTemp = vecCenter - D3DXVECTOR3(pCamera->m_cameraPos.x, 0.0f, pCamera->m_cameraPos.z);
	if (D3DXVec3Length(&vTemp) > g_pDevice->m_fFogEnd + pMesh->m_fRadius)
		return 0;

	for (int i = 0; i < 9; ++i)
	{
		vecPos[i].x = m_vecPosition.x;
		vecPos[i].z = m_vecPosition.y;
		vecPos[i].y = m_fHeight;
	}

	if (m_dwObjType == 3)
	{
		float fRadius = pMesh->m_fRadius;
		vecPos[7].x = vecPos[7].x - ((fRadius * pMesh->m_fScaleH) * m_fScale);
		vecPos[5].x = vecPos[7].x;
		vecPos[3].x = vecPos[7].x;
		vecPos[1].x = vecPos[7].x;
		vecPos[6].z = vecPos[6].z + ((fRadius * pMesh->m_fScaleH) * m_fScale);
		vecPos[5].z = vecPos[6].z;
		vecPos[2].z = vecPos[6].z;
		vecPos[1].z = vecPos[6].z;
		vecPos[4].y = vecPos[4].y - ((fRadius * pMesh->m_fScaleV) * m_fScale);
		vecPos[3].y = vecPos[4].y;
		vecPos[2].y = vecPos[4].y;
		vecPos[1].y = vecPos[4].y;
		vecPos[8].x = vecPos[8].x + ((fRadius * pMesh->m_fScaleH) * m_fScale);
		vecPos[6].x = vecPos[8].x;
		vecPos[4].x = vecPos[8].x;
		vecPos[2].x = vecPos[8].x;
		vecPos[8].z = vecPos[8].z - ((fRadius * pMesh->m_fScaleH) * m_fScale);
		vecPos[7].z = vecPos[8].z;
		vecPos[4].z = vecPos[8].z;
		vecPos[3].z = vecPos[8].z;
		vecPos[8].y = vecPos[8].y + ((fRadius * pMesh->m_fScaleV) * m_fScale);
		vecPos[7].y = vecPos[8].y;
		vecPos[6].y = vecPos[8].y;
		vecPos[5].y = vecPos[8].y;
	}
	else
	{
		vecPos[7].x = vecPos[7].x + pMesh->m_fMinX;
		vecPos[5].x = vecPos[7].x;
		vecPos[3].x = vecPos[7].x;
		vecPos[1].x = vecPos[7].x;
		vecPos[6].z = vecPos[6].z + -pMesh->m_fMinY;
		vecPos[5].z = vecPos[6].z;
		vecPos[2].z = vecPos[6].z;
		vecPos[1].z = vecPos[6].z;
		vecPos[4].y = vecPos[4].y + pMesh->m_fMinZ;
		vecPos[3].y = vecPos[4].y;
		vecPos[2].y = vecPos[4].y;
		vecPos[1].y = vecPos[4].y;
		vecPos[8].x = vecPos[8].x + pMesh->m_fMaxX;
		vecPos[6].x = vecPos[8].x;
		vecPos[4].x = vecPos[8].x;
		vecPos[2].x = vecPos[8].x;
		vecPos[8].z = vecPos[8].z + -pMesh->m_fMaxY;
		vecPos[7].z = vecPos[8].z;
		vecPos[4].z = vecPos[8].z;
		vecPos[3].z = vecPos[8].z;
		vecPos[8].y = vecPos[8].y + pMesh->m_fMaxZ;
		vecPos[7].y = vecPos[8].y;
		vecPos[6].y = vecPos[8].y;
		vecPos[5].y = vecPos[8].y;

		D3DXMATRIX matScale;
		D3DXMATRIX matPosition;
		D3DXMATRIX mat;
		D3DXMATRIX mat2;
		D3DXMatrixScaling(&matScale, pMesh->m_fScaleH * m_fScale, pMesh->m_fScaleV * m_fScale, pMesh->m_fScaleH * m_fScale);
		D3DXMatrixRotationYawPitchRoll(&mat, m_fAngle, -D3DXToRadian(90), 0);
		D3DXMatrixMultiply(&mat, &g_pDevice->m_matWorld, &mat);
		D3DXMatrixMultiply(&mat, &mat, &matScale);

		for (int i = 0; i < 9; ++i)
		{
			D3DXMatrixTranslation(&matPosition,	vecPos[i].x, vecPos[i].y, vecPos[i].z);
			D3DXMatrixMultiply(&mat2, &mat, &matPosition);
			vecPos[i].x = mat2._41;
			vecPos[i].y = mat2._42;
			vecPos[i].z = mat2._43;
		}
	}
	
	int bFront = 0;
	for (int i = 0; i < 9; ++i)
	{
		vTemp = vecPos[i] - D3DXVECTOR3(pCamera->m_cameraPos.x, pCamera->m_cameraPos.y, pCamera->m_cameraPos.z);
		if (g_pDevice->m_fFogEnd + 3.0f > D3DXVec3Length(&vTemp))
		{
			D3DXVec3Project(&vPosTransformed[i], &vecPos[i], &g_pDevice->m_viewport, &g_pDevice->m_matProj, &g_pDevice->m_matView,	&g_pDevice->m_matWorld);

			if (vPosTransformed[i].z >= -0.01f && vPosTransformed[i].z < 1.0f)
			{
				int vPosInX = (int)vPosTransformed[i].x;
				int vPosInY = (int)vPosTransformed[i].y;
				if (vPosInX > 0	&& vPosInX < (int)g_pDevice->m_viewport.Width && 
					vPosInY > 0 && vPosInY < (int)g_pDevice->m_viewport.Height)
				{
					return 1;
				}
			}

			if (i == 0 && vPosTransformed[i].z < 1.0f)
				bFront = 1;
		}
	}

	if (bFront != 1)
		return 0;

	RECT rcRect;
	SetRect(&rcRect, (int)vPosTransformed[0].x, (int)vPosTransformed[0].y, (int)vPosTransformed[0].x, (int)vPosTransformed[0].y);
	RECT WinRect;
	SetRect(&WinRect, 0, 0, g_pDevice->m_viewport.Width, g_pDevice->m_viewport.Height);

	for (int i = 1; i < 9; ++i)
	{
		if (rcRect.left > (int)vPosTransformed[i].x)
			rcRect.left = (int)vPosTransformed[i].x;

		if (rcRect.top > (int)vPosTransformed[i].y)
			rcRect.top = (int)vPosTransformed[i].y;

		if (rcRect.right < (int)vPosTransformed[i].x)
			rcRect.right = (int)vPosTransformed[i].x;

		if (rcRect.bottom < (int)vPosTransformed[i].y)
			rcRect.bottom = (int)vPosTransformed[i].y;
	}

	RECT returnRect;
	return IntersectRect(&returnRect, &rcRect, &WinRect) == 1;
}

int TMObject::RegisterMask(TMGround* pGround, float fX, float fY)
{
	if (!pGround)
		return 0;

	char cTempMask[16][16];
	memset(cTempMask, 0, sizeof(cTempMask));

	float revAngle = D3DXToRadian(180) - m_fAngle * -1.0f;
	for (int y = 0; y < 16; ++y)
	{
		for (int x = 0; x < 16; ++x)
		{
			float fx = (float)x + 0.5f - 7.5f;
			float fy = (float)y + 0.5f - 7.5f;
			float tx = (cos(revAngle) * fx) - (sin(revAngle) * fy);
			float ty = (sin(revAngle) * fx) + (cos(revAngle) * fy);

			int intx = (int)(tx + 7.5f);
			int inty = (int)(ty + 7.5f);

			if (intx >= 0 && inty >= 0 && intx < 16 && inty < 16)
				cTempMask[y][x] = MeshManager::m_aObjectMask[m_nMaskIndex][inty][intx];
		}
	}

	int nBaseX = (int)fX - 7;
	int nBaseY = (int)fY - 7;

	for (int y = 0; y < 16; ++y)
	{
		for (int i = 0; i < 16; ++i)
		{
			if (i + nBaseX >= 0 && i + nBaseX <= 128 && y + nBaseY >= 0 && y + nBaseY <= 128 && cTempMask[y][i])
			{
				int nTemp = (int)((m_fHeight / 0.1f) + (float)(3 * cTempMask[y][i]));
				if (m_fHeight > 0.0f)
					++nTemp;
				if (nTemp > 127)
					nTemp = 127;
				if ((char)nTemp > pGround->m_pMaskData[y][128 * nBaseY + i + nBaseX])
					pGround->m_pMaskData[y][128 * nBaseY + i + nBaseX] = nTemp;
			}
		}
	}

	return 1;
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
	TMMesh *pMesh = g_pMeshManager->GetCommonMesh(m_dwObjType, 0, 3_min);
	if (!pMesh)
		return 0;

	if (g_pCurrentScene->GroundGetMask(m_vecPosition) < 126)
		return 0;

	TMCamera* pCamera = g_pObjectManager->m_pCamera;

	D3DXVECTOR3 VecCam = D3DXVECTOR3(pCamera->m_cameraPos.x, pCamera->m_cameraPos.z, pCamera->m_cameraPos.y);
	D3DXVECTOR3 VecCenter = D3DXVECTOR3(pCamera->m_pFocusedObject->m_vecPosition.x, pCamera->m_pFocusedObject->m_vecPosition.y, pCamera->m_pFocusedObject->m_fHeight);
	D3DXVECTOR3 Vec = D3DXVECTOR3(m_vecPosition.x, m_vecPosition.y, m_fHeight) - VecCenter;

	auto pV2 = D3DXVECTOR3(pCamera->m_vecCamDir.x, pCamera->m_vecCamDir.z, pCamera->m_vecCamDir.y);
	if (D3DXVec3Dot(&Vec, &pV2) > 0.0f)
		return 0;

	D3DXVECTOR3 CamPos(pCamera->m_cameraPos.x, pCamera->m_cameraPos.y, pCamera->m_cameraPos.z);
	D3DXVECTOR3 CamDir(pCamera->m_vecCamDir.x, pCamera->m_vecCamDir.y, pCamera->m_vecCamDir.z);

	D3DXVECTOR3 vecPos[9]{};
	for (int i = 0; i < 9; ++i)
	{
		vecPos[i].x = m_vecPosition.x;
		vecPos[i].z = m_vecPosition.y;
		vecPos[i].y = m_fHeight;
	}

	vecPos[1].x = vecPos[3].x = vecPos[5].x = vecPos[7].x = vecPos[7].x + pMesh->m_fMinX;
	vecPos[1].z = vecPos[2].z = vecPos[5].z = vecPos[6].z = vecPos[6].z + -pMesh->m_fMinY;
	vecPos[1].y = vecPos[2].y = vecPos[3].y = vecPos[4].y = vecPos[4].y + pMesh->m_fMinZ;

	vecPos[2].x = vecPos[4].x = vecPos[6].x = vecPos[8].x = vecPos[8].x + pMesh->m_fMaxX;
	vecPos[3].z = vecPos[4].z = vecPos[7].z = vecPos[8].z = vecPos[8].z + -pMesh->m_fMaxY;
	vecPos[5].y = vecPos[6].y = vecPos[7].y = vecPos[8].y = vecPos[8].y + pMesh->m_fMaxZ;

	D3DXMATRIX matScale;
	D3DXMATRIX matPosition;
	D3DXMATRIX mat;
	D3DXMATRIX mat2;
	D3DXMatrixScaling(&matScale,pMesh->m_fScaleH, pMesh->m_fScaleV, pMesh->m_fScaleH);
	D3DXMatrixRotationYawPitchRoll(&mat, m_fAngle, -D3DXToRadian(90), 0);
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
