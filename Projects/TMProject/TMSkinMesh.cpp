#include "pch.h"
#include "CFrame.h"
#include "TMObject.h"
#include "TMEffectSWSwing.h"
#include "TMSkinMesh.h"
#include "MeshManager.h"
#include "TMGlobal.h"

int TMSkinMesh::m_nSmooth = 1;

TMSkinMesh::TMSkinMesh(LOOK_INFO* pLook, SANC_INFO* pSanc, int nBoneAniIndex, int bExpand, SANC_INFO* pColor, short nMeshType, short nCos, int mount)
{
	m_nBoneAniIndex = nBoneAniIndex;
	m_bExpand = bExpand;
	m_bMeshGenerated = 0;
	m_bBaseMat = 0;
	m_cDefaultAlpha = 1;

	m_vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_pRoot = nullptr;
	m_nAniBaseIndex = 0;
	m_dwLastUsedTime = 0;
	m_dwShowTime = 0;
	m_nAniIndex = 0;
	m_dwFPS = 30;
	m_dwStartOffset = 0;
	m_pOwner = 0;

	memcpy(&m_Look, pLook, sizeof(m_Look));

	if (pSanc)
		memcpy(&m_Sanc, pSanc, sizeof(m_Sanc));
	else
		memset(&m_Sanc, 0, sizeof(m_Sanc));

	for (int i = 0; i < MAX_VALID_FRAME_TO_ANIMATE; ++i)
		m_pframeToAnimate[i] = 0;

	// This is setted to tree, grass, etc
	if (nBoneAniIndex >= MAX_ANI_TYPE)
		m_dwStartTime = 500 * (((m_nBoneAniIndex >> 1) % 5) + rand() % 5);

	memset(&m_materials, 0, sizeof(m_materials));

	m_materials.Diffuse.r = 1.0f;
	m_materials.Diffuse.g = 1.0f;
	m_materials.Diffuse.b = 1.0f;
	m_materials.Specular = m_materials.Diffuse;
	m_materials.Power = 0.0f;
	m_materials.Emissive.r = 0.3f;
	m_materials.Emissive.g = 0.3f;
	m_materials.Emissive.b = 0.3f;
	m_dwOffset = 0;
	m_nAniIndexLast = 0;
	m_pSwingEffect[0] = 0;
	m_pSwingEffect[1] = 0;
	m_cRotate[0] = 0;
	m_cRotate[1] = 0;

	m_cEnableMultiTex = 1;
	if (m_nBoneAniIndex == 1)
		m_fLenDetail = 0.07f;
	else
		m_fLenDetail = 0.1f;

	if (pColor)
		memcpy(&m_Color, pColor, sizeof(m_Color));
	else
		memset(&m_Color, 0, sizeof(m_Color));

	memset(m_matMantua, 0, sizeof(m_matMantua));

	m_dwTexAni = 0;
	m_cTexAni = 0;
	m_nMeshType = nMeshType;
	m_nCosType = nCos;
	m_bMount = mount;

	D3DXMatrixIdentity(&m_BaseMatrix);
	m_Cos = 1;
	m_bRenderEffect = 0;
}

TMSkinMesh::~TMSkinMesh()
{
	if (m_pRoot != m_pframeToAnimate[0] && m_pRoot != nullptr)
	{
		SAFE_DELETE(m_pRoot);
	}

	for (int i = 0; i < MAX_VALID_FRAME_TO_ANIMATE; ++i)
	{
		SAFE_DELETE(m_pframeToAnimate[i]);
	}

	for (int i = 0; i < 2; ++i)
	{
		if (m_pSwingEffect[i] != nullptr)
		{
			g_pObjectManager->DeleteObject(m_pSwingEffect[i]);
			m_pSwingEffect[i] = nullptr;
		}
	}
}

HRESULT TMSkinMesh::InitDeviceObjects()
{
	RestoreDeviceObjects();
	return 0;
}

HRESULT TMSkinMesh::RestoreDeviceObjects()
{
	return E_NOTIMPL;
}

void TMSkinMesh::FrameMove(unsigned int dwServerTime)
{
}

void TMSkinMesh::InitMaterial(D3DMATERIAL9 material)
{
}

int TMSkinMesh::Render(float fLen, float fScale, float fLen2)
{
	return 0;
}

HRESULT TMSkinMesh::DeleteDeviceObjects()
{
	return E_NOTIMPL;
}

HRESULT TMSkinMesh::InvalidateDeviceObjects()
{
	return E_NOTIMPL;
}

int TMSkinMesh::SetAnimation(int nIndex)
{
	return 0;
}

void TMSkinMesh::SetPosition(D3DXVECTOR3 vPos)
{
}

void TMSkinMesh::SetPosition(float fX, float fY, float fZ)
{
}

void TMSkinMesh::SetAngle(D3DXVECTOR3 vAngle)
{
}

void TMSkinMesh::SetAngle(float fYaw, float fPitch, float fRoll)
{
}

void TMSkinMesh::SetSwingMatrix()
{
}

void TMSkinMesh::SetVecMantua(int nType, int nSkinIndex)
{
}

void TMSkinMesh::RenderSkinMeshEffect()
{
}

void TMSkinMesh::RenderEffect_HorseFireLeg()
{
}

void TMSkinMesh::SetHardcoreMantle(char* szTexture, char* szName)
{
}

void TMSkinMesh::SetOldCostume(int costype, char* szTexture, char* szName)
{
}

void TMSkinMesh::SetRenewOldCostume(int costype, char* szTexture, char* szName)
{
}

void TMSkinMesh::SetCostume(int Costype, char* szTexture, char* szName)
{
}

int TMSkinMesh::MantleException(char* texture)
{
	return 0;
}

BOOL TMSkinMesh::God2Exception(int i)
{
	return 0;
}
