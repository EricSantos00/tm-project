#include "pch.h"
#include "TMMesh.h"
#include "TMEffectMesh.h"
#include "TMGlobal.h"
#include "TMCamera.h"

TMEffectMesh::TMEffectMesh(int nMeshIndex, unsigned int dwColor, float fAngle, int nType)
	: TMEffect()
{
	m_pMesh = nullptr;
	m_nMeshIndex = nMeshIndex;
	m_fAngle = fAngle;
	m_fAngle2 = 0.0f;
	m_fAngle3 = 1.5707964f;
	m_nType = nType;
	m_fScaleH = 1.0f;
	m_fScaleV = 1.0f;
	m_fProgress = 0.0f;
	m_nTextureIndex = -1;
	m_cShine = 0;
	m_cUScroll = 0;
	m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
	m_dwLifeTime = 0;
	m_dwCycleTime = 1000;
	
	m_dwCreateTime = g_pTimerManager->GetServerTime();

	SetColor(dwColor);
}

TMEffectMesh::~TMEffectMesh()
{
}

int TMEffectMesh::Render()
{
	if (m_dwKey != -1 &&
		m_dwKey != TreeNode::m_VisualKey1 &&
		m_dwKey != TreeNode::m_VisualKey2 &&
		m_dwKey != TreeNode::m_VisualKey3 &&
		m_dwKey != TreeNode::m_VisualKey4 &&
		m_dwKey != TreeNode::m_VisualKey5 &&
		m_dwKey != TreeNode::m_VisualKey6 &&
		m_dwKey != TreeNode::m_VisualKey7 && 
		m_dwKey != TreeNode::m_VisualKey8 && 
		m_dwKey != TreeNode::m_VisualKey9)
	{
		if (m_nMeshIndex != 506)
			return 0;

		if (g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_SELCHAR)
			return 0;
	}

	if (m_bVisible == 1)
	{
		if (m_nMeshIndex >= 520 && m_nMeshIndex <= 530)
			return 0;

		auto pMesh = g_pMeshManager->GetCommonMesh(m_nMeshIndex, 1, 180000);

		if (pMesh)
		{
			if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_BRIGHT)
			{
				g_pDevice->SetRenderState(D3DRS_DESTBLEND, 2u);
				g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
			}
			else
			{
				g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
				g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
			}

			if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_ALPHA)
			{
				g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
				g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
				g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
				g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
				g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 2u);
				g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, 0);
			}
			else
			{
				g_pDevice->SetRenderState(D3DRS_CULLMODE, 1u);
				g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
				g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
				g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, 1u);
				g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
				g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, 0);
				g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
			}
			g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
			g_pDevice->SetRenderState(D3DRS_FOGENABLE, 0);
			g_pDevice->SetRenderState(D3DRS_SRCBLEND, 5u);
			g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 8u);
			g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);
			g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 0);
			g_pDevice->SetRenderState(D3DRS_LIGHTING, 0);

			if (m_efAlphaType == EEFFECT_ALPHATYPE::EF_ALPHA)
			{
				_D3DMATERIAL9 materials{};

				D3DXCOLOR specular{ m_dwColor };

				materials.Specular.r = specular.r;
				materials.Specular.g = specular.g;
				materials.Specular.b = specular.b;
				materials.Specular.a = specular.a;

				D3DXCOLOR diffuse{ m_dwColor };

				materials.Diffuse.r = diffuse.r;
				materials.Diffuse.g = diffuse.g;
				materials.Diffuse.b = diffuse.b;
				materials.Diffuse.a = diffuse.a;

				D3DXCOLOR emissive{ m_dwColor };

				materials.Emissive.r = emissive.r;
				materials.Emissive.g = emissive.g;
				materials.Emissive.b = emissive.b;
				materials.Emissive.a = emissive.a;

				D3DXCOLOR ambient{ m_dwColor };

				materials.Ambient.r = ambient.r;
				materials.Ambient.g = ambient.g;
				materials.Ambient.b = ambient.b;
				materials.Ambient.a = ambient.a;

				g_pDevice->m_pd3dDevice->SetMaterial(&materials);
			}
			else
			{
				if (!pMesh->m_pVB)
					return 0;

				RDLVERTEX* pVertex{};
				D3DVERTEXBUFFER_DESC vDesc{};

				pMesh->m_pVB->GetDesc(&vDesc);
				pMesh->m_pVB->Lock(0, 0, (void**)&pVertex, 0);

				int nCount = vDesc.Size / 0x18;

				DWORD dwColor = m_dwColor;

				if (m_cShine == 1)
				{
					float fAlpha = (float)((sinf((m_fProgress * 3.1415927f) * 2.0f)) * 0.2f) + 0.80000001f;
	
					DWORD dwA = (unsigned int)((float)m_dwA * fAlpha);
					DWORD dwR = (unsigned int)((float)m_dwR * fAlpha);
					DWORD dwG = (unsigned int)((float)m_dwG * fAlpha);
					DWORD dwB = (unsigned int)((float)m_dwB * fAlpha);

					dwColor = dwB | (dwG << 8) | (dwR << 16) | (dwA << 24);
				}

				if (m_nType == 4)
				{
					float fAlpha = sinf(m_fProgress * 3.1415927f);

					DWORD dwA = (unsigned int)((float)m_dwA * fAlpha);
					DWORD dwR = (unsigned int)((float)m_dwR * fAlpha);
					DWORD dwG = (unsigned int)((float)m_dwG * fAlpha);
					DWORD dwB = (unsigned int)((float)m_dwB * fAlpha);

					dwColor = dwB | (dwG << 8) | (dwR << 16) | (dwA << 24);
				}

				for (int i = 0; i < nCount; ++i)
				{
					pVertex[i].diffuse = dwColor;

					if (m_cUScroll == 1)
						pVertex[i].tu += (m_fProgress * 0.001f);

					if (m_cUScroll == 2)
					{
						DWORD dwServerTime = g_pTimerManager->GetServerTime();

						float fPro = (float)(dwServerTime % 100) / 100.0f;

						pVertex[i].tv += (fPro * 0.1f);
					}
				}

				pMesh->m_pVB->Unlock();
			}

			pMesh->m_fScaleH = m_fScaleH;
			pMesh->m_fScaleV = m_fScaleV;

			switch (m_nType)
			{
			case 1:
				pMesh->m_nTextureIndex[0] = m_nTextureIndex;
				break;
			case 2:
				pMesh->m_fScaleV = (m_fScaleH * m_fProgress) * 3.0f;
				m_fAngle = m_fProgress * 3.1415927f;
				break;
			case 3:
				m_fAngle = m_fProgress * 3.1415927f;
				break;
			case 4:
				pMesh->m_nTextureIndex[0] = m_nTextureIndex;

				if (m_fProgress >= 0.2)
				{
					float fSin = sinf(((m_fProgress - 0.2f) * 3.1415927f) * 0.5f);

					pMesh->m_fScaleH = (fSin + 1.5f) * m_fScaleH;
					pMesh->m_fScaleV = (fSin + 1.5f) * m_fScaleV;
				}
				else
				{
					pMesh->m_fScaleH = ((m_fProgress * 5.0f) + 0.5f) * m_fScaleH;
					pMesh->m_fScaleV = ((m_fProgress * 5.0f) + 0.5f) * m_fScaleV;
				}
				break;
			case 5:
				pMesh->m_nTextureIndex[0] = m_nTextureIndex;
				break;
			}

			pMesh->Render(m_vecPosition.x, m_vecPosition.y, m_vecPosition.z, m_fAngle, m_fAngle2, m_fAngle3, 0, 0);

			g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
			g_pDevice->SetRenderState(D3DRS_CULLMODE, 3u);
			g_pDevice->SetRenderState(D3DRS_LIGHTING, 1u);
			g_pDevice->SetRenderState(D3DRS_SRCBLEND, 2u);
			g_pDevice->SetRenderState(D3DRS_ALPHAFUNC, 7u);
			g_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
			g_pDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1u);
			g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, 4u);
			g_pDevice->SetRenderState(D3DRS_DESTBLEND, 6u);
		}
	}

	return 1;
}

int TMEffectMesh::FrameMove(unsigned int dwServerTime)
{
	if (m_dwKey != -1 &&
		m_dwKey != TreeNode::m_VisualKey1 &&
		m_dwKey != TreeNode::m_VisualKey2 && 
		m_dwKey != TreeNode::m_VisualKey3 && 
		m_dwKey != TreeNode::m_VisualKey4)
	{
		if (m_nMeshIndex != 506)
			return 0;

		if (g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_SELCHAR)
			return 0;
	}

	dwServerTime = g_pTimerManager->GetServerTime();

	auto pMesh = g_pMeshManager->GetCommonMesh(m_nMeshIndex, 1, 180000);

	if (pMesh)
		m_fRadius = pMesh->m_fRadius;

	IsVisible(); // ?

	m_fProgress = (float)((dwServerTime - m_dwCreateTime) % m_dwCycleTime) / (float)m_dwCycleTime;

	if (m_dwLifeTime)
	{
		if ((dwServerTime - m_dwCreateTime) > m_dwLifeTime)
		{
			m_bVisible = 0;
			g_pObjectManager->DeleteObject(static_cast<TreeNode*>(this));
		}
	}

	return 1;
}

void TMEffectMesh::SetColor(unsigned int dwColor)
{
	m_dwColor = dwColor;
	m_dwA = (dwColor & 0xFF000000) >> 24;
	m_dwR = ((unsigned int)0x0FF0000 & dwColor) >> 16;
	m_dwG = (dwColor & 0xFF00) >> 8;
	m_dwB = static_cast<unsigned char>(dwColor);
}

int TMEffectMesh::IsVisible()
{
	if (g_pCurrentScene->GetSceneType() != ESCENE_TYPE::ESCENE_FIELD)
	{
		m_bVisible = 1;
		return 1;
	}

	if (!m_bShow)
	{
		m_bVisible = 0;
		return 0;
	}

	auto pMesh = g_pMeshManager->GetCommonMesh(m_nMeshIndex, 0, 180000);

	if (!pMesh)
	{
		m_bVisible = 0;
		return 0;
	}

	auto pCamera = g_pObjectManager->m_pCamera;

	D3DXVECTOR3 Vec{};
	D3DXVECTOR3 VecCam{ pCamera->m_cameraPos.x, pCamera->m_cameraPos.z, pCamera->m_cameraPos.y };

	Vec = D3DXVECTOR3{ m_vecPosition.x, m_vecPosition.z, m_vecPosition.y } - VecCam;

	if (pMesh->m_fRadius >= D3DXVec3Length(&Vec))
	{
		m_bVisible = 1;
		return 1;
	}

	auto pV = D3DXVECTOR3(pCamera->m_vecCamDir.x, pCamera->m_vecCamDir.z, pCamera->m_vecCamDir.y);
	if (D3DXVec3Dot(&Vec, &pV) <= 0.0f)
	{
		m_bVisible = 0;
		return 0;
	}

	m_bVisible = IsInView();

	return m_bVisible;
}

int TMEffectMesh::IsInView()
{
	auto pCamera = g_pObjectManager->m_pCamera;
	auto pMesh = g_pMeshManager->GetCommonMesh(m_nMeshIndex, 0, 180000);
	if (!pMesh)
		return 0;

	D3DXVECTOR3 vTemp{};
	D3DXVECTOR3 vPosTransformed[9]{};
	D3DXVECTOR3 vecPos[9]{};

	for (int i = 0; i < 9; ++i)
	{
		vecPos[i].x = m_vecPosition.x;
		vecPos[i].z = m_vecPosition.z;
		vecPos[i].y = m_vecPosition.y;
	}

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

	D3DXMatrixScaling(&matScale, pMesh->m_fScaleH, pMesh->m_fScaleV, pMesh->m_fScaleH);
	D3DXMatrixRotationYawPitchRoll(&mat, m_fAngle, -1.5707964f, 0);
	D3DXMatrixMultiply(&mat, &g_pDevice->m_matWorld, &mat);
	D3DXMatrixMultiply(&mat, &mat, &matScale);

	for (int i = 0; i < 9; i++)
	{
		D3DXMatrixTranslation(&matPosition, vecPos[i].x, vecPos[i].y, vecPos[i].z);
		D3DXMatrixMultiply(&mat2, &mat, &matPosition);
		vecPos[i].x = mat2._41;
		vecPos[i].y = mat2._42;
		vecPos[i].z = mat2._43;
	}

	bool bFront = false;
	for (int i = 0; i < 9; i++)
	{
		D3DXVECTOR3 result = vecPos[i] - D3DXVECTOR3(pCamera->m_cameraPos.x, pCamera->m_cameraPos.y, pCamera->m_cameraPos.z);
		if (g_pDevice->m_fFogEnd > D3DXVec3Length(&result))
		{
			D3DXVec3Project(&vPosTransformed[i], &vecPos[i], &g_pDevice->m_viewport, &g_pDevice->m_matProj,
				&g_pDevice->m_matView,
				&g_pDevice->m_matWorld);

			if (vPosTransformed[i].z >= -0.0099999998f && vPosTransformed[i].z < 1.0f)
			{
				int vPosInX = (int)vPosTransformed[i].x;
				int vPosInY = (int)vPosTransformed[i].y;
				if (vPosInX > 0 && vPosInX < (int)g_pDevice->m_viewport.Width && 
					vPosInY > 0 && vPosInY < (int)g_pDevice->m_viewport.Height)
				{
					return 1;
				}
			}

			if (i == 0 && vPosTransformed[i].z < 1.0f)
				bFront = true;
		}
	}

	if (bFront != true)
		return 0;

	if (fabsf(m_vecPosition.x - pCamera->m_cameraPos.x) >= 14.0f)
		return 0;

	if (fabsf(m_vecPosition.y - pCamera->m_cameraPos.z) >= 14.0f)
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
