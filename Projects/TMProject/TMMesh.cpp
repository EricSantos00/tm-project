#include "pch.h"
#include "TreeNode.h"
#include "TMMesh.h"
#include "TMGlobal.h"
#include "TMObject.h"
#include "TMLog.h"

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
	if (cMulti == 100)
		fProgress = (float)(dwTime % 8000) / 8000.0f;
	else
		fProgress = (float)(dwTime % 4000) / 4000.0f;

	RDVERTEX2* pVertex = nullptr;

	if (FAILED(m_pVB->Lock(0, 0, (void**)&pVertex, 0)))
		return 1;

	for (size_t k = 0; k < m_dwAttCount; ++k)
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
	D3DXMatrixRotationYawPitchRoll(&mat, fAngle, fAngle2 + -D3DXToRadian(90), fAngle3);
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
	if (m_bEffect == 1)
		texture = g_pTextureManager->GetEffectTexture(nIndex, m_dwShowTime <= 5000u ? 5000u : m_dwShowTime);
	else
		texture = g_pTextureManager->GetModelTexture(nIndex, m_dwShowTime <= 10000 ? 10000u : m_dwShowTime);

	g_pDevice->SetTexture(0, texture);
}

HRESULT TMMesh::RenderDraw(int nTexOffset)
{
	for (size_t i = 0; i < m_dwAttCount; ++i)
	{
		SetTexture(nTexOffset + m_nTextureIndex[i]);

		if (FAILED(g_pDevice->m_pd3dDevice->DrawIndexedPrimitive(
			D3DPT_TRIANGLELIST,
			0,
			m_AttRange[i].VertexStart,
			m_AttRange[i].VertexCount,
			3 * m_AttRange[i].FaceStart,
			m_AttRange[i].FaceCount)))
			return 0;
	}

	return 1;
}

int TMMesh::RenderPick(float fX, float fY, float fZ, float fAngle, float fAngle2, float fAngle3, float cMulti, int nTexOffset)
{
	SetTexture(nTexOffset + m_nTextureIndex[0]);

	D3DMATERIAL9 bmaterials{};
	g_pDevice->m_pd3dDevice->GetMaterial(&bmaterials);

	D3DCOLORVALUE color{};
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

	D3DXMATRIX matPosition{};
	D3DXMATRIX matScale{};
	D3DXMATRIX matQuat{};
	D3DXMATRIX mat{};

	D3DXMatrixScaling(&matScale, m_fScaleH, m_fScaleV, m_fScaleH);
	D3DXMatrixTranslation(&matPosition, fX, fY, fZ);
	D3DXMatrixRotationYawPitchRoll(&mat, fAngle, fAngle2 + -1.5707964f, fAngle3);
	D3DXMatrixMultiply(&mat, &g_pDevice->m_matWorld, &mat);
	D3DXMatrixMultiply(&mat, &mat, &matScale);
	D3DXMatrixMultiply(&mat, &mat, &matPosition);

	g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLDMATRIX(0), &mat);

	Render((char)cMulti, nTexOffset);

	g_pDevice->m_pd3dDevice->SetMaterial(&bmaterials);
	return 1;
}	


int TMMesh::RenderForUI(int nX, int nY, float fAngle, float fScale, DWORD dwColor, int nMultiTex, int nTexOffset, short sLegend)
{
	float fWidthRatio = 6.3f;
	if (((float)g_pDevice->m_viewport.Width / (float)g_pDevice->m_viewport.Height) < 1.26f)
		fWidthRatio = 6.26f;

	float fX = (float)nX / (float)((float)g_pDevice->m_viewport.Width / fWidthRatio);
	float fY = (float)nY / (float)((float)g_pDevice->m_viewport.Height / 4.96f) - 2.48f;

	fX = fX - (float)(fWidthRatio / 2.0f);
	float fYaw = atan2f(fX, 50.0f);
	float fPitch = atan2f(fY, 50.0f);

	D3DXMATRIX matScale;
	D3DXMATRIX matPosition;
	D3DXMATRIX mat;

	D3DXMatrixScaling(&matScale, 0.51999998f * fScale, 0.51999998f * fScale, 0.51999998f * fScale);
	D3DXMatrixTranslation(&matPosition,
		-fX - ((m_vecCenter.x * 0.51999998f) * fScale),
		-fY - ((m_vecCenter.z * 0.51999998f) * fScale),
		(m_vecCenter.y * 0.51999998f) * fScale);

	D3DXMatrixRotationYawPitchRoll(&mat, fYaw + fAngle, fPitch + -1.5707964f, 0.0);
	D3DXMatrixMultiply(&mat, &g_pDevice->m_matWorld, &mat);
	D3DXMatrixMultiply(&mat, &mat, &matScale);
	D3DXMatrixMultiply(&mat, &mat, &matPosition);

	g_pDevice->m_pd3dDevice->SetTransform(D3DTS_WORLDMATRIX(0), &mat);

	char cAlpha = g_pTextureManager->m_stModelTextureList[m_nTextureIndex[0]].cAlpha;

	D3DCOLORVALUE color{};
	color.r = (float)((dwColor >> 16) & 0xFF) / 256.0f;
	color.g = (float)((unsigned short)dwColor >> 8) / 256.0f;
	color.b = (float)((unsigned char)dwColor) / 256.0f;

	D3DMATERIAL9 materials{};
	materials.Emissive.r = (color.r * 0.30000001f) + 0.1f;
	materials.Emissive.g = (color.r * 0.30000001f) + 0.1f;
	materials.Emissive.b = (color.r * 0.30000001f) + 0.1f;
	materials.Diffuse.r = color.r;
	materials.Diffuse.g = color.g;
	materials.Diffuse.b = (float)((unsigned char)dwColor) / 256.0f;
	materials.Diffuse.a = color.a;
	materials.Specular.r = color.r;
	materials.Specular.g = color.g;
	materials.Specular.b = (float)((unsigned char)dwColor) / 256.0f;
	materials.Specular.a = color.a;
	materials.Power = 0;

	g_pDevice->m_pd3dDevice->SetMaterial(&materials);

	if (nMultiTex <= 0 && (sLegend < 4 || sLegend > 8))
	{
		g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_ALPHATESTENABLE, 0);
		Render(1, nTexOffset);
		return 1;	
	}

	g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_TEXCOORDINDEX, 1);

	if (sLegend == 4)
	{
		g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(nMultiTex + 179, 5000));
		g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400) ? 4 : 5);
		g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 4);
	}
	else if (sLegend > 4 && sLegend <= 8)
	{
		int texSum = 153;
		if (sLegend == 6)
			texSum = 166;
		if (sLegend == 7)
			texSum = 246;
		if (sLegend == 8)
			texSum = 260;

		g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(nMultiTex + texSum, 5000));
		g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 4);
		g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400) ? 7 : 11);
	}
	else if (sLegend > 9 && sLegend <= 12)
	{
		int texSum = 153;
		if (sLegend == 10)
			texSum = 166;
		if (sLegend == 11)
			texSum = 246;
		if (sLegend == 12)
			texSum = 440;

		g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(nMultiTex + texSum, 5000));

		if (cAlpha != 67 || g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
		{
			g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, 2);
			g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, 1);
			g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAARG1, 2);
		}
		else
		{
			g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG1, 1);
			g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG2, 2);
			g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 18);
		}

		if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400)
		{
			g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 4);
			g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 7);
		}
		else
		{
			g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, nMultiTex < 7 ? 4 : 5);
			if (cAlpha != 67)
				g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 11);
		}
	}
	else if (sLegend > 116 && sLegend <= 125)
	{
		int texSum = 153;
		if (sLegend == 116)
			texSum = 275;
		if (sLegend == 117)
			texSum = 288;
		if (sLegend == 118)
			texSum = 301;
		if (sLegend == 119)
			texSum = 314;
		if (sLegend == 120)
			texSum = 327;
		if (sLegend == 121)
			texSum = 340;
		if (sLegend == 122)
			texSum = 353;
		if (sLegend == 123)
			texSum = 366;
		if (sLegend == 124)
			texSum = 425;
		if (sLegend == 125)
			texSum = 392;

		g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(nMultiTex + texSum - 1, 5000));

		if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400 || g_pDevice->m_bTNT)
		{
			g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 4);
			g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 7);
		}
		else
		{
			g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG2, 1);
			g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 24);
			g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 6);
		}
	}
	else
	{
		g_pDevice->SetTexture(1, g_pTextureManager->GetEffectTexture(nMultiTex + 233, 5000));

		if (g_pDevice->m_bVoodoo || g_pDevice->m_bIntel || g_pDevice->m_bG400 || g_pDevice->m_bTNT)
		{
			g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 4);
			g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 7);
		}
		else
		{
			if (cAlpha == 67)
			{
				g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG1, 1);
				g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLORARG2, 2);
				g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 18);
			}
			else
			{
				g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, 2);
				g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAOP, 1);
				g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_ALPHAARG1, 2);
			}

			g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, nMultiTex < 7 ? 4 : 5);
			if (cAlpha != 67)
				g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 11);

			g_pDevice->SetRenderState(D3DRENDERSTATETYPE::D3DRS_FOGVERTEXMODE, 0);
		}
	}

	Render(1, nTexOffset);

	g_pDevice->SetTexture(1, nullptr);
	g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_TEXCOORDINDEX, 1);
	g_pDevice->SetTextureStageState(0, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 4);
	g_pDevice->SetTextureStageState(1, D3DTEXTURESTAGESTATETYPE::D3DTSS_COLOROP, 1);
	return 1;
}

int TMMesh::LoadMsa(const char* szFileName)
{
	if (!strlen(szFileName))
		return 0;

	FILE* fp = nullptr;
	fopen_s(&fp, szFileName, "rb");
	if (!fp)
	{
		LOG_WRITELOG("ReadingError : %s\n", szFileName);
		return 0;
	}

	fread(&m_dwFVF, 4, 1, fp);
	fread(&m_sizeVertex, 4, 1, fp);
	fread(&m_dwAttCount, 4, 1, fp);
	fread(m_AttRange, sizeof(D3DXATTRIBUTERANGE), m_dwAttCount, fp);

	int len = strlen(szFileName);

	char szPathName[24] = { 0, };
	int nIndex = 0;
	for (nIndex = 0; nIndex < len && szFileName[nIndex] != '\\'; ++nIndex)
		szPathName[nIndex] = szFileName[nIndex];

	char szTmpFileName[24];
	sprintf_s(szTmpFileName, "%s", &szFileName[nIndex + 2]);

	char szTextureName[24] = { 0, };
	char szTemp[24] = { 0, };
	char szTex[64] = { 0, };

	for (size_t i = 0; i < m_dwAttCount; ++i)
	{
		if (szTmpFileName[0] != 'a' || szTmpFileName[1] != 'a')
		{
			memset(szTextureName, 0, sizeof szTextureName);
			fread(szTemp, 11, 1, fp);
			len = strlen(szTemp);

			for (nIndex = len - 1; nIndex > 0; --nIndex)
			{
				if (szTemp[nIndex] == '\\')
				{
					sprintf_s(szTextureName, "%s", &szTemp[nIndex + 1]);
					break;
				}
			}
			if (!nIndex)
				sprintf_s(szTextureName, "%s", szTemp);

			sprintf_s(szTemp, "%s", szTextureName);
			memset(szTextureName, 0, 24);
			len = strlen(szTemp);

			for (nIndex = 0; nIndex < len && szTemp[nIndex] != '.'; ++nIndex)
				szTextureName[nIndex] = szTemp[nIndex];

			if (!_stricmp(szPathName, "effect"))
			{
				sprintf_s(szTex, EffectTexture_FileFormat_Path, szTextureName);
				m_nTextureIndex[i] = g_pTextureManager->GetEffectTextureIndex(szTex);
			}
			else
			{
				sprintf_s(szTex, MeshTexture_FileFormat_Path, szTextureName);
				m_nTextureIndex[i] = g_pTextureManager->GetModelTextureIndex(szTex);
			}
		}
		else
		{
			fread(szTextureName, 11, 1, fp);
			memset(szTextureName, 0, 24);
			for (nIndex = 0; nIndex < len && szTmpFileName[nIndex] != '.'; ++nIndex)
				szTextureName[nIndex] = szTmpFileName[nIndex];

			if (!_stricmp(szPathName, "effect"))
			{
				sprintf_s(szTex, EffectTexture_FileFormat_Path, szTextureName);
				m_nTextureIndex[i] = g_pTextureManager->GetEffectTextureIndex(szTex);
			}
			else
			{
				sprintf_s(szTex, MeshTexture_FileFormat_Path, szTextureName);
				m_nTextureIndex[i] = g_pTextureManager->GetModelTextureIndex(szTex);
			}
		}
		if (m_nTextureIndex[i] == -1)
		{
			len = strlen(szTmpFileName);
			memset(szTextureName, 0, 24);

			for (nIndex = 0; nIndex < len && szTmpFileName[nIndex] != '.'; ++nIndex)
				szTextureName[nIndex] = szTmpFileName[nIndex];

			if (!_stricmp(szPathName, "effect"))
			{
				sprintf_s(szTex, EffectTexture_FileFormat_Path, szTextureName);
				m_nTextureIndex[i] = g_pTextureManager->GetEffectTextureIndex(szTex);
			}
			else
			{
				sprintf_s(szTex, MeshTexture_FileFormat_Path, szTextureName);
				m_nTextureIndex[i] = g_pTextureManager->GetModelTextureIndex(szTex);
			}

			if (m_nTextureIndex[i] == -1)
			{
				LOG_WRITELOG("%s , %s \r\n", szFileName, szTex);
				if (fp)
				{
					fclose(fp);

					fp = nullptr;
					return 0;
				}
			}
		}
	}

	char* pIndex = nullptr;
	D3DINDEXBUFFER_DESC iDesc{};
	fread(&iDesc.Size, 4, 1, fp);

	if (iDesc.Size)
	{
		g_pDevice->m_pd3dDevice->CreateIndexBuffer(
			iDesc.Size,
			8,
			D3DFORMAT::D3DFMT_INDEX16,
			D3DPOOL::D3DPOOL_MANAGED,
			&m_pIB,
			nullptr);

		if (!m_pIB)
			return 0;

		m_pIB->Lock(0, 0, (void**)&pIndex, 0);
		fread(pIndex, iDesc.Size, 1, fp);
		m_pIB->Unlock();
	}

	float* pVertex = nullptr;
	char* pVertexB = nullptr;

	D3DVERTEXBUFFER_DESC vDesc;
	fread(&vDesc.Size, 4, 1, fp);

	int nFloatCount = m_sizeVertex >> 2;
	int nNumVertex = vDesc.Size / m_sizeVertex;

	if (m_dwFVF == 322)
	{
		g_pDevice->m_pd3dDevice->CreateVertexBuffer(
			vDesc.Size,
			8,
			m_dwFVF,
			D3DPOOL::D3DPOOL_MANAGED,
			&m_pVB,
			nullptr);
	}
	else
	{
		m_dwFVF += 256;
		g_pDevice->m_pd3dDevice->CreateVertexBuffer(
			vDesc.Size + 8 * nNumVertex,
			8,
			m_dwFVF,
			D3DPOOL::D3DPOOL_MANAGED,
			&m_pVB,
			nullptr);
	}

	if (!m_pVB)
		return 0;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	if (m_dwFVF == 322)
	{
		fread(pVertex, vDesc.Size, 1u, fp);
	}
	else
	{
		pVertexB = (char*)pVertex;
		for (int i = 0; i < nNumVertex; ++i)
			fread(&pVertexB[i * (m_sizeVertex + 8)], m_sizeVertex, 1u, fp);

		m_sizeVertex += 8;
	}

	int nAddedFloatNum = 0;
	if (m_dwFVF != 322)
		nAddedFloatNum = 2;

	m_fMinX = pVertex[nAddedFloatNum + nFloatCount];
	m_fMaxX = m_fMinX;
	m_fMinY = *(&pVertex[nAddedFloatNum + 1] + nFloatCount);
	m_fMaxY = m_fMinY;
	m_fMinZ = *(&pVertex[nAddedFloatNum + 2] + nFloatCount);
	m_fMaxZ = m_fMinZ;

	for (int i = 0; i < nNumVertex - 1; ++i)
	{
		if (m_dwFVF == 530)
		{
			pVertex[i * (nAddedFloatNum + nFloatCount) + 8] = pVertex[i * (nAddedFloatNum + nFloatCount) + 6];
			pVertex[i * (nAddedFloatNum + nFloatCount) + 9] = pVertex[i * (nAddedFloatNum + nFloatCount) + 7];
		}

		if (pVertex[i * (nAddedFloatNum + nFloatCount)] > m_fMaxX)
			m_fMaxX = pVertex[i * (nAddedFloatNum + nFloatCount)];
		if (m_fMinX > pVertex[i * (nAddedFloatNum + nFloatCount)])
			m_fMinX = pVertex[i * (nAddedFloatNum + nFloatCount)];
		if (pVertex[i * (nAddedFloatNum + nFloatCount) + 1] > m_fMaxY)
			m_fMaxY = pVertex[i * (nAddedFloatNum + nFloatCount) + 1];
		if (m_fMinY > pVertex[i * (nAddedFloatNum + nFloatCount) + 1])
			m_fMinY = pVertex[i * (nAddedFloatNum + nFloatCount) + 1];
		if (pVertex[i * (nAddedFloatNum + nFloatCount) + 2] > m_fMaxZ)
			m_fMaxZ = pVertex[i * (nAddedFloatNum + nFloatCount) + 2];
		if (m_fMinZ > pVertex[i * (nAddedFloatNum + nFloatCount) + 2])
			m_fMinZ = pVertex[i * (nAddedFloatNum + nFloatCount) + 2];
	}

	if (fabsf(m_fMaxX) > m_fRadius)
		m_fRadius = fabsf(m_fMaxX);
	if (fabsf(m_fMinX) > m_fRadius)
		m_fRadius = fabsf(m_fMinX);

	if (fabsf(m_fMaxY) > m_fRadius)
		m_fRadius = fabsf(m_fMaxY);
	if (fabsf(m_fMinY) > m_fRadius)
		m_fRadius = fabsf(m_fMinY);

	if (fabsf(m_fMaxZ) > m_fRadius)
		m_fRadius = fabsf(m_fMaxZ);
	if (fabsf(m_fMinZ) > m_fRadius)
		m_fRadius = fabsf(m_fMinZ);

	m_vecCenter = TMVector3((float)(m_fMaxX + m_fMinX) * 0.5f,
		(float)(m_fMaxY + m_fMinY) * 0.5f,
		(float)(m_fMaxZ + m_fMinZ) * 0.5f);

	m_pVB->Unlock();

	fclose(fp);
	return 1;
}