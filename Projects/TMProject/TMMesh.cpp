#include "pch.h"
#include "TreeNode.h"
#include "TMMesh.h"
#include "TMGlobal.h"

TMMesh::TMMesh()
{
	m_pVB = 0;
	m_pIB = 0;
	m_bDummy = 0;
	m_bFirst = 1;
	m_sizeVertex = 0;
	m_dwFVF = 0;
	m_dwAttCount = 0;
	m_nMeshType = 0;
	m_dwLastUsedTime = 0;

	m_fScaleV = 1.0f;
	m_fScaleH = 1.0f;
	m_fRadius = 1.0f;

	m_fMaxX = 1.175494f;
	m_fMinX = 3.402823f;
	m_fMaxY = 1.175494f;
	m_fMinY = 3.402823f;
	m_fMaxZ = 1.175494f;
	m_fMinZ = 3.402823f;

	m_bEffect = 0;

	memset(m_AttRange, 0, sizeof(m_AttRange));
	memset(m_nTextureIndex, 0, sizeof(m_nTextureIndex));
}

TMMesh::~TMMesh()
{
	if (m_pVB != nullptr)
	{
		m_pVB->Release();
		m_pVB = nullptr;
	}

	if (m_pIB != nullptr)
	{
		m_pIB->Release();
		m_pIB = nullptr;
	}
}

int TMMesh::Render(char cMulti, int nTexOffset)
{
	if (!m_pVB || !m_pIB)
		return 1;

	if (g_pDevice->m_pd3dDevice->SetStreamSource(0, m_pVB, 0, m_sizeVertex) < 0)
		return 1;

	if (g_pDevice->m_pd3dDevice->SetIndices(m_pIB) < 0)
		return 1;

	if (g_pDevice->m_pd3dDevice->SetFVF(m_dwFVF) < 0)
		return 1;

	g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_FOGVERTEXMODE, 3);

	if (!cMulti || m_dwFVF != 530)
		return RenderDraw(nTexOffset);

	DWORD dwTime = g_pTimerManager->GetServerTime();
	float fProgress;
	if (cMulti == 1)
		fProgress = (double)(dwTime % 10000);
	else if (cMulti == 100)
		fProgress = (double)(dwTime % 8000) / 8000.0f;
	else
		fProgress = (double)(dwTime % 4000) / 4000.0f;

	RDVERTEX2* pVertex = nullptr;

	if (FAILED(m_pVB->Lock(0, 0, (void**)&pVertex, 0)))
		return 1;

	for (int k = 0; k < m_dwAttCount; ++k)
	{
		int nStartIndex = m_AttRange[k].VertexStart;
		int nCount = m_AttRange[k].VertexCount;

		switch (cMulti)
		{
		case 1:
			for (int j = m_AttRange[k].VertexStart; j < nCount + nStartIndex; ++j)
			{
				pVertex[j].tu2 = pVertex[j].tu1 + fProgress;
				pVertex[j].tv2 = pVertex[j].tv1 + fProgress;
			}
			break;
		case 2:
			for (int l = m_AttRange[k].VertexStart; l < nCount + nStartIndex; ++l)
				pVertex[l].tu2 = pVertex[l].tu1 + fProgress;
			break;
		case 3:
			for (int m = m_AttRange[k].VertexStart; m < nCount + nStartIndex; ++m)
				pVertex[m].tv2 = pVertex[m].tv1 + fProgress;
			break;
		case 4:
			for (int n = m_AttRange[k].VertexStart; n < nCount + nStartIndex; ++n)
				pVertex[n].tu2 = pVertex[n].tu1 - fProgress;
			break;
		case 5:
			for (int ii = m_AttRange[k].VertexStart; ii < nCount + nStartIndex; ++ii)
				pVertex[ii].tv2 = pVertex[ii].tv1 - fProgress;
			break;
		case 6:
			if (m_bFirst == 1)
			{
				for (int jj = m_AttRange[k].VertexStart; jj < nCount + nStartIndex; ++jj)
					pVertex[jj].tv2 = pVertex[jj].tv1;
				m_bFirst = 0;
			}
			else
			{
				for (int kk = m_AttRange[k].VertexStart; kk < nCount + nStartIndex; ++kk)
					pVertex[kk].tv1 = pVertex[kk].tv2 - fProgress;
			}
			break;
		case 7:
			for (int ll = m_AttRange[k].VertexStart; ll < nCount + nStartIndex; ++ll)
				pVertex[ll].tu1 = pVertex[ll].tu2 - (float)(fProgress * 3.0);
			break;
		case 100:
			for (int mm = m_AttRange[k].VertexStart; mm < nCount + nStartIndex; ++mm)
				pVertex[mm].tu1 = pVertex[mm].tu2 - (float)(fProgress * 2.0);
			break;
		case 101:
			if (m_bFirst == 1)
			{
				for (int nn = m_AttRange[k].VertexStart; nn < nCount + nStartIndex; ++nn)
					pVertex[nn].tv2 = pVertex[nn].tv1;
				m_bFirst = 0;
			}
			else
			{
				for (int i1 = m_AttRange[k].VertexStart; i1 < nCount + nStartIndex; ++i1)
				{
					pVertex[i1].tv1 = pVertex[i1].tv2 - fProgress;
					pVertex[i1].tu1 = pVertex[i1].tu2 + fProgress;
				}
			}
			break;
		}
	}

	if (FAILED(m_pVB->Unlock()))
		return 1;

	return RenderDraw(nTexOffset);
}

int TMMesh::Render(float fX, float fY, float fZ, float fAngle, float fAngle2, float fAngle3, char cMulti, int nTexOffset)
{
	D3DXMATRIX mat{};
	D3DXMATRIX matPosition{};
	D3DXMATRIX matScale{};

	SetTexture(nTexOffset + m_nTextureIndex[0]);

	D3DXMatrixScaling(&matScale, m_fScaleH, m_fScaleV, m_fScaleH);
	D3DXMatrixTranslation(&matPosition, fX, fY, fZ);
	D3DXMatrixRotationYawPitchRoll(&mat, fAngle, fAngle2 + -1.5707964f, fAngle3);
	D3DXMatrixMultiply(&mat, &g_pDevice->m_matWorld, &mat);
	D3DXMatrixMultiply(&mat, &mat, &matScale);
	D3DXMatrixMultiply(&mat, &mat, &matPosition);

	// In the original ER shows 256 value but this macro do the job according to arg
	g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLDMATRIX(0), &mat);

	Render(cMulti, nTexOffset);
	return 1;
}

int TMMesh::Render(float fX, float fY, float fZ, D3DXQUATERNION quat, char cMulti, int nTexOffset)
{
	D3DXMATRIX mat{};
	D3DXMATRIX matPosition{};
	D3DXMATRIX matScale{};
	D3DXMATRIX matQuat{};

	SetTexture(nTexOffset + m_nTextureIndex[0]);

	D3DXMatrixScaling(&matScale, m_fScaleH, m_fScaleV, m_fScaleH);
	D3DXMatrixTranslation(&matPosition, fX, fY, fZ);
	D3DXMatrixRotationQuaternion(&matQuat, &quat);
	D3DXMatrixMultiply(&mat, &matQuat, &g_pDevice->m_matWorld);
	D3DXMatrixMultiply(&mat, &mat, &matScale);
	D3DXMatrixMultiply(&mat, &mat, &matPosition);

	// In the original ER shows 256 value but this macro do the job according to arg
	g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLDMATRIX(0), &mat);

	Render(cMulti, nTexOffset);
	return 1;
}

void TMMesh::SetTexture(int nIndex)
{
	IDirect3DBaseTexture9* texture = nullptr;
	if (this->m_bEffect == 1)
		texture = g_pTextureManager->GetEffectTexture(nIndex, m_dwShowTime <= 5000u ? 5000u : m_dwShowTime);
	else
		texture = g_pTextureManager->GetModelTexture(nIndex, m_dwShowTime <= 10000 ? 10000u : m_dwShowTime);

	g_pDevice->SetTexture(0, texture);
}

HRESULT TMMesh::RenderDraw(int nTexOffset)
{
	for (int i = 0; i < m_dwAttCount; ++i)
	{
		SetTexture(nTexOffset + m_nTextureIndex[0]);

		if (FAILED(g_pDevice->m_pd3dDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			m_AttRange[i].VertexStart,
			m_AttRange[i].VertexCount,
			3 * m_AttRange[i].FaceStart,
			m_AttRange[i].FaceCount)))
			return 1;
	}

	return S_OK;
}

int TMMesh::RenderPick(float fX, float fY, float fZ, float fAngle, float fAngle2, float fAngle3, float cMulti, int nTexOffset)
{
	D3DXMATRIX mat{};
	D3DXMATRIX matPosition{};
	D3DXMATRIX matScale{};

	SetTexture(nTexOffset + m_nTextureIndex[0]);

	D3DMATERIAL9 bmaterials;
	g_pDevice->m_pd3dDevice->GetMaterial(&bmaterials);

	D3DCOLORVALUE color;
	color.r = 1.0f;
	color.g = 1.0f;
	color.b = 1.0f;

	D3DMATERIAL9 materials{};
	materials.Emissive.r = 1.0f;
	materials.Emissive.g = 1.0f;
	materials.Emissive.b = 1.0f;
	materials.Diffuse.r = 1.0f;
	materials.Diffuse.g = 1.0f;
	materials.Diffuse.b = 1.0f;
	materials.Diffuse.a = color.a;
	materials.Specular.r = 1.0f;
	materials.Specular.g = 1.0f;
	materials.Specular.b = 1.0f;
	materials.Specular.a = color.a;
	materials.Power = 0.0f;

	g_pDevice->m_pd3dDevice->SetMaterial(&materials);

	D3DXMATRIX matPosition;
	D3DXMATRIX matScale;
	D3DXMATRIX matQuat;
	D3DXMATRIX mat;

	D3DXMatrixScaling(&matScale, m_fScaleH, m_fScaleV, m_fScaleH);
	D3DXMatrixTranslation(&matPosition, fX, fY, fZ);
	D3DXMatrixRotationYawPitchRoll(&mat, fAngle, fAngle2 + -1.5707964f, fAngle3);
	D3DXMatrixMultiply(&mat, &g_pDevice->m_matWorld, &mat);
	D3DXMatrixMultiply(&mat, &mat, &matScale);
	D3DXMatrixMultiply(&mat, &mat, &matPosition);

	g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLDMATRIX(0), &mat);

	Render(cMulti, nTexOffset);

	g_pDevice->m_pd3dDevice->SetMaterial(&bmaterials);
}	