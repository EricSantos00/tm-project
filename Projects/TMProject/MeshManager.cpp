#include "pch.h"
#include "TMMesh.h"
#include "MeshManager.h"
#include "TMGlobal.h"

stBoneAni MeshManager::m_BoneAnimationList[MAX_BONE_ANIMATION_LIST]{};
short MeshManager::m_sAnimationArray[MAX_ANI_CLASS][MAX_ANI_TYPE][MAX_ANI_MOTION]{};
char MeshManager::m_aObjectMask[MAX_OBJECT_MASK][MAX_MASK_X][MAX_MASK_Y]{};
int MeshManager::m_nFullCount{0};

MeshManager::MeshManager()
{
	memset(m_stCommonMesh, 0, sizeof(m_stCommonMesh));
	memset(m_stSkinMeshList, 0, sizeof(m_stSkinMeshList));
	memset(m_stValidAniList, 0, sizeof(m_stValidAniList));

	for (int nClass = 0; nClass < MAX_ANI_CLASS; ++nClass)
	{
		for (int nAniTypeNum = 0; nAniTypeNum < MAX_ANI_TYPE; ++nAniTypeNum)
		{
			for (int nAniMotionNum = 0; nAniMotionNum < MAX_ANI_MOTION; ++nAniMotionNum)
			{
				MeshManager::m_sAnimationArray[nClass][nAniTypeNum][nAniMotionNum] = 0;
			}
		}
	}

	g_pMeshManager = this;
	m_LastLoadTime = 0;
}

MeshManager::~MeshManager()
{
	ReleaseMesh();
	g_pMeshManager = nullptr;
}

int MeshManager::InitMeshManager()
{
	return 1;
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
