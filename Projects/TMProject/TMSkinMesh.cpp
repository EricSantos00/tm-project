#include "pch.h"
#include "CFrame.h"
#include "TMObject.h"
#include "TMEffectSWSwing.h"
#include "TMSkinMesh.h"

int TMSkinMesh::m_nSmooth = 1;

TMSkinMesh::TMSkinMesh(LOOK_INFO* pLook, SANC_INFO* pSanc, int nBoneAniIndex, int bExpand, SANC_INFO* pColor, short nMeshType, short nCos, int mount)
{
}

TMSkinMesh::~TMSkinMesh()
{
}

HRESULT TMSkinMesh::InitDeviceObjects()
{
	return E_NOTIMPL;
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
