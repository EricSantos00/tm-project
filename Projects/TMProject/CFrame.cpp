#include "pch.h"
#include "CMesh.h"
#include "TMSkinMesh.h"
#include "CFrame.h"
#include "TMGlobal.h"
#include "TMHuman.h"
#include "TMEffectSWSwing.h"

CFrame::CFrame(DWORD id)
{
	m_dwID = id;
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matCombined);

	m_pSibling = nullptr;
	m_pFirstChild = nullptr;
	m_pMesh = nullptr;
	m_pParentSkin = nullptr;
}

CFrame::~CFrame()
{
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
}

CFrame* CFrame::FindFrame(DWORD dwID)
{
	if (m_dwID == dwID)
		return this;

	if (m_pFirstChild != nullptr)
	{
		CFrame* pframe = m_pFirstChild->FindFrame(dwID);
		if (pframe)
			return pframe;
	}

	if (m_pSibling != nullptr)
	{
		CFrame* pframe = m_pSibling->FindFrame(dwID);
		if (pframe)
			return pframe;
	}

	return nullptr;
}

HRESULT CFrame::InvalidateDeviceObjects()
{
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}

	if (m_pFirstChild != nullptr)
		m_pFirstChild->InvalidateDeviceObjects();
	if (m_pSibling != nullptr)
		m_pSibling->InvalidateDeviceObjects();

	return S_OK;
}

int CFrame::Render()
{
	if (m_pMesh != nullptr)
	{
		D3DXMATRIX matrixComb = m_matCombined;
		if (m_pParentSkin->m_nBoneAniIndex < 19 && m_dwID == g_dwHandIndex[m_pParentSkin->m_nBoneAniIndex][0])
		{
			D3DXMATRIX matrix;
			D3DXMATRIX matTrans;
			if (m_pParentSkin->m_cRotate[0] == 1)
			{
				D3DXMatrixTranslation(&matTrans, m_pParentSkin->m_fLenDetail, 0.009f, 0.0f);
				D3DXMatrixRotationYawPitchRoll(&matrix, 0, 0, D3DXToRadian(180));
			}
			else
			{
				float fShield = 0.0f;
				if (m_pParentSkin->m_Look.Mesh7 > 1700
					&& m_pParentSkin->m_Look.Mesh7 <= 1800)
				{
					fShield = 0.05f;
				}

				D3DXMatrixTranslation(&matTrans, m_pParentSkin->m_fLenDetail, fShield + 0.009f, 0);
				D3DXMatrixRotationYawPitchRoll(&matrix, D3DXToRadian(180), 0, 0);
			}

			D3DXMatrixMultiply(&matrix, &matTrans, &matrix);
			D3DXMatrixMultiply(&matrixComb, &matrix, &m_matCombined);

			if (m_pParentSkin->m_pSwingEffect[0])
			{
				m_matCombined = matrixComb;
				m_pParentSkin->m_pSwingEffect[0]->m_matEffect = m_matCombined;
				m_pParentSkin->m_pSwingEffect[0]->m_matEffectMat = matTrans * matrix;
				m_pParentSkin->m_pSwingEffect[0]->m_matEffectCombine = m_pParentSkin->m_pRoot->m_matRot;
				m_pParentSkin->m_pSwingEffect[0]->m_dwSwingID = m_dwID;

				TMHuman* pHuman = (TMHuman*)m_pParentSkin->m_pOwner;
				if (pHuman)
					m_pParentSkin->m_pSwingEffect[0]->m_nWeaponType = pHuman->m_nWeaponTypeR;
			}
		}
		if (m_pParentSkin->m_nBoneAniIndex < 19
			&& m_dwID == g_dwHandIndex[m_pParentSkin->m_nBoneAniIndex][1])
		{
			D3DXMATRIX mat;
			D3DXMATRIX matTrans;

			if (m_pParentSkin->m_cRotate[1] == 1)
			{
				D3DXMatrixTranslation(&matTrans, m_pParentSkin->m_fLenDetail, 0.009f, 0.0f);
				D3DXMatrixRotationYawPitchRoll(&mat, D3DXToRadian(180), 0.0f, 0.0f);
			}			
			else
			{
				if (m_pParentSkin->m_nBoneAniIndex == 6)
				{
					D3DXMatrixTranslation(&matTrans, m_pParentSkin->m_fLenDetail * 0.5f, 0.009f, 0.0f);
				}
				else if (m_pParentSkin->m_nBoneAniIndex == 9)
				{
					D3DXMatrixTranslation(&matTrans, m_pParentSkin->m_fLenDetail * 1.6f, 0.029f, 0.0f);
				}
				else
				{
					D3DXMatrixTranslation(&matTrans, m_pParentSkin->m_fLenDetail, 0.009f, 0.0f);
				}
				if (m_pParentSkin->m_nBoneAniIndex == 1)
				{
					D3DXMatrixRotationYawPitchRoll(&mat, D3DXToRadian(15), D3DXToRadian(10), D3DXToRadian(180));
				}
				else if (m_pParentSkin->m_nBoneAniIndex == 6)
				{				
					D3DXMatrixRotationYawPitchRoll(&mat, D3DXToRadian(20), D3DXToRadian(0), D3DXToRadian(180));
				}
				else
				{
					D3DXMatrixRotationYawPitchRoll(&mat, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(180));
				}
			}
			D3DXMatrixMultiply(&mat, &matTrans, &mat);
			D3DXMatrixMultiply(&matrixComb, &mat, &m_matCombined);

			if (m_pParentSkin->m_pSwingEffect[1])
			{
				m_matCombined = matrixComb;
				m_pParentSkin->m_pSwingEffect[1]->m_matEffect = m_matCombined;
				m_pParentSkin->m_pSwingEffect[1]->m_matEffectMat = matTrans * mat;
				m_pParentSkin->m_pSwingEffect[1]->m_matEffectCombine = m_pParentSkin->m_pRoot->m_matRot;
				m_pParentSkin->m_pSwingEffect[1]->m_dwSwingID = m_dwID;

				TMHuman* pHuman = (TMHuman*)m_pParentSkin->m_pOwner;
				if (pHuman)
					m_pParentSkin->m_pSwingEffect[1]->m_nWeaponType = pHuman->m_nWeaponTypeR;
			}
		}
		if (m_pParentSkin->m_pOwner != nullptr)
		{
			if (m_pParentSkin->m_nBoneAniIndex == 0 || m_pParentSkin->m_nBoneAniIndex == 1 ||
				m_pParentSkin->m_nBoneAniIndex == 2 || m_pParentSkin->m_nBoneAniIndex == 4)
			{
				if (m_pParentSkin->m_pOwner->m_cWeapon == 1)
				{
					if (m_pMesh->m_dwID == g_dwHandIndex[m_pParentSkin->m_nBoneAniIndex][0]	||
						m_pMesh->m_dwID == g_dwHandIndex[m_pParentSkin->m_nBoneAniIndex][1])
					{
						if (m_pParentSkin->m_cDefaultAlpha == 1)
						{
							g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_SRCCOLOR);
							g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_DESTCOLOR);
						}

						D3DCOLORVALUE color;
						color.r = 0.5f;
						color.g = 0.5f;
						color.b = 0.5f;
						color.a = 0.5f;

						D3DMATERIAL9 materials{};
						materials.Specular.r = 0.5f;
						materials.Specular.g = 0.5f;
						materials.Specular.b = 0.5f;
						materials.Specular.a = 0.5f;
						materials.Diffuse.r = 0.5f;
						materials.Diffuse.g = 0.5f;
						materials.Diffuse.b = 0.5f;
						materials.Diffuse.a = 0.5f;
						materials.Emissive.r = 0.5f;
						materials.Emissive.g = 0.5f;
						materials.Emissive.b = 0.5f;
						materials.Emissive.a = 0.5f;
						materials.Ambient.r = 0.5f;
						materials.Ambient.g = 0.5f;
						materials.Ambient.b = 0.5f;
						materials.Ambient.a = 0.5f;

						g_pDevice->m_pd3dDevice->SetMaterial(&materials);
						g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLDMATRIX(0), &matrixComb);

						m_pMesh->Render(1);

						materials.Specular = color;
						materials.Diffuse = color;
						materials.Emissive = color;
						materials.Ambient = color;

						g_pDevice->m_pd3dDevice->SetMaterial(&materials);

						D3DXMATRIX matrixScale;
						D3DXMatrixScaling(&matrixScale,
							m_pParentSkin->m_pOwner->m_fScale + 0.05f,
							m_pParentSkin->m_pOwner->m_fScale + 0.05f,
							m_pParentSkin->m_pOwner->m_fScale + 0.05f);

						D3DXMatrixMultiply(&matrixScale, &matrixScale, &matrixComb);

						g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLDMATRIX(0), &matrixScale);
						m_pMesh->Render(1);

						if (m_pParentSkin->m_cDefaultAlpha == 1)
						{
							g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_SRCBLEND, D3DBLEND::D3DBLEND_ONE);
							g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_DESTBLEND, D3DBLEND::D3DBLEND_INVSRCALPHA);
						}
					}
				}
			}
		}
		else
		{
			g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLDMATRIX(0), &matrixComb);
			m_pMesh->Render(0);
		}
	}

	if (m_pSibling != nullptr)
		m_pSibling->Render();
	if (m_pFirstChild != nullptr)
		m_pFirstChild->Render();

	return 1;
}

void CFrame::AddFrame(CFrame* pframe)
{
	if (m_pFirstChild != nullptr)
	{
		pframe->m_pSibling = m_pFirstChild->m_pSibling;
		m_pFirstChild->m_pSibling = pframe;
	}
	else
		m_pFirstChild = pframe;
}

void CFrame::LinkBones(CFrame* root)
{
	if (m_pMesh != nullptr)
	{
		int num = m_pMesh->m_numPalette;
		for (int i = 0; i < num; ++i)
		{
			CFrame *pFrame = root->FindFrame(m_pMesh->m_dwNames[i]);
			if (pFrame)
				m_pMesh->m_pBoneOffset[i] = &pFrame->m_matCombined;
		}
	}

	if (m_pFirstChild != nullptr)
		m_pFirstChild->LinkBones(root);
	if (m_pSibling != nullptr)
		m_pSibling->LinkBones(root);
}

void CFrame::UpdateFrames(const D3DXMATRIX& matCur)
{
}
