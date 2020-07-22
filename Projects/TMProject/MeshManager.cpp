#include "pch.h"
#include "TMMesh.h"
#include "MeshManager.h"

stBoneAni MeshManager::m_BoneAnimationList[100]{};
short MeshManager::m_sAnimationArray[6][60][56]{};
char MeshManager::m_aObjectMask[2048][16][16]{};
int MeshManager::m_nFullCount{0};

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
}

int MeshManager::InitMeshManager()
{
	return 0;
}

int MeshManager::InitBoneAnimation()
{
	return 0;
}

HRESULT MeshManager::RestoreDeviceObjects()
{
	return E_NOTIMPL;
}

void MeshManager::ReleaseMesh()
{
}

void MeshManager::ReleaseNotUsingMesh()
{
}

int MeshManager::ReadObjectMask()
{
	return 0;
}

int MeshManager::LoadCommonMesh(int nIndex, int bEffect)
{
	return 0;
}

TMMesh* MeshManager::GetCommonMesh(int nIndex, int bEffect, DWORD showTime)
{
	return nullptr;
}

int MeshManager::GetSkinMeshIndex(char* szSkinMeshName)
{
	return 0;
}

int MeshManager::GetAvailableSkinMeshIndex()
{
	return 0;
}
