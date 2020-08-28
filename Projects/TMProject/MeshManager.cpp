#include "pch.h"
#include "TMMesh.h"
#include "MeshManager.h"
#include "TMGlobal.h"
#include "TMLog.h"
#include "TMPaths.h"

int g_nMaxSizeOffset[MAX_BONE_ANIMATION_LIST];

stAniSoundTable2 g_MobAniTableEx[4][2];
stAniSoundTable g_MobAniTable[60];

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
	if (!InitBoneAnimation())
	{
		LOG_WRITELOG("Initialize Bone Animation Failed\r\n");
		return 0;
	}

	FILE* fp = nullptr;
	fopen_s(&fp, MeshList_Path, "rt");

	if (fp == nullptr)
		return 0;

	int nIndex = 0;
	char szMeshName[255]{};

	while (fscanf(fp, "%d %s\r\n", &nIndex, szMeshName) != -1)
	{
		sprintf(m_stCommonMesh[nIndex].szFileName, "%s", szMeshName);
	}

	fclose(fp);

	return ReadObjectMask();
}

int MeshManager::InitBoneAnimation()
{
	memset(MeshManager::m_BoneAnimationList, 0, sizeof(MeshManager::m_BoneAnimationList));

	char szFileName[128]{};
	sprintf(szFileName, BoneAni4_Path);

	FILE* fpList = nullptr;
	fopen_s(&fpList, szFileName, "rt");

	// TODO: add a message box here
	if (fpList == nullptr)
		return 0;

	FILE* fpValidAni = nullptr;
	fopen_s(&fpValidAni, ValidIndex_Path, "rb");

	// TODO: add a message box here if fails
	if (fpValidAni != nullptr)
	{
		fread(m_stValidAniList, sizeof(m_stValidAniList), 1, fpValidAni);
		fclose(fpValidAni);
	}

	int nCount = 0;
	int nAniTypeCount = 0;
	int nParts = 0;

	char temp[256]{};
	for (int Count = 0; Count < MAX_BONE_ANIMATION_LIST; ++Count)
	{
		int nFullTickCount = 0;
		if (fscanf(fpList, "%d %d %d %s\r\n", &nCount, &nAniTypeCount, &nParts, temp) == -1)
			break;

		MeshManager::m_BoneAnimationList[nCount].numAniTypeCount = nAniTypeCount;
		MeshManager::m_BoneAnimationList[nCount].numParts = nParts;

		sprintf(MeshManager::m_BoneAnimationList[nCount].szAniName, "%s", temp);

		char szTemp[128];
		sprintf(szTemp, "%s.bon", MeshManager::m_BoneAnimationList[nCount].szAniName);

		int handle = _open(szTemp, _O_BINARY);
		int sz = _filelength(handle);

		MeshManager::m_BoneAnimationList[nCount].pBone = (unsigned int*)malloc(sz);

		_read(handle, MeshManager::m_BoneAnimationList[nCount].pBone, sz);
		_close(handle);

		MeshManager::m_BoneAnimationList[nCount].numBone = sz / 8;
		unsigned int dwFileIndex = 0;
		for (size_t nFI = 0; nFI < MeshManager::m_BoneAnimationList[nCount].numAniTypeCount; ++nFI)
		{
			sprintf(szTemp,	"%s%04d.ani", MeshManager::m_BoneAnimationList[nCount].szAniName, m_stValidAniList[nCount][nFI].nI + 1);
			handle = _open(szTemp, _O_BINARY, 0);

			if (handle >= 0)
			{
				int numAniTick = 0;
				_read(handle, &numAniTick, 4);
				_read(handle, &MeshManager::m_BoneAnimationList[nCount].numAniFrame, 4);
				_close(handle);
				nFullTickCount += numAniTick;
				++dwFileIndex;
			}
		}

		MeshManager::m_nFullCount = nFullTickCount;
		MeshManager::m_BoneAnimationList[nCount].matAnimation = (LPD3DXMATRIX)malloc(
			MeshManager::m_BoneAnimationList[nCount].numAniFrame
			* (nFullTickCount * sizeof(D3DXMATRIX)));

		// This is used on characters animation/bone read. (ch01/02)
		if (nCount == 0 || nCount == 1)
		{
			MeshManager::m_BoneAnimationList[nCount].matQuaternion = (LPD3DXQUATERNION)malloc(
				MeshManager::m_BoneAnimationList[nCount].numAniFrame
				* (sizeof(D3DXQUATERNION)
				* nFullTickCount));
		}		
		
		dwFileIndex = 0;
		int nOffset = 0;

		// This loop is related with weapon animations
		for (size_t nFI = 0; nFI < MeshManager::m_BoneAnimationList[nCount].numAniTypeCount; ++nFI)
		{
			sprintf(szTemp,	"%s%04d.ani", MeshManager::m_BoneAnimationList[nCount].szAniName, m_stValidAniList[nCount][nFI].nI + 1);
			handle = _open(szTemp, _O_BINARY, 0);

			if (handle < 0)
				continue;

			unsigned int buffer;
			_read(handle, &buffer, 4);
			_read(handle, &MeshManager::m_BoneAnimationList[nCount].numAniFrame, 4);
			MeshManager::m_BoneAnimationList[nCount].numAniCut[dwFileIndex] = buffer;
			_read(handle, &MeshManager::m_BoneAnimationList[nCount].matAnimation[nOffset],
				MeshManager::m_BoneAnimationList[nCount].numAniFrame * (buffer * sizeof(D3DXMATRIX)));

			if (nCount == 0 || nCount == 1)
			{
				for (size_t j = 0; j < MeshManager::m_BoneAnimationList[nCount].numAniFrame * buffer; ++j)
				{
					D3DXQuaternionRotationMatrix(
						&MeshManager::m_BoneAnimationList[nCount].matQuaternion[j + nOffset],
						&MeshManager::m_BoneAnimationList[nCount].matAnimation[j + nOffset]);
				}				
			}

			nOffset += MeshManager::m_BoneAnimationList[nCount].numAniFrame * buffer;
			_close(handle);

			if (nCount == 0 || nCount == 1)
			{
				int nArrayIndex = m_stValidAniList[nCount][nFI].nI + 1;
				int nWeapon = nArrayIndex / 100 - 1;
				int nAnimation = nArrayIndex % 100 - 1;
				MeshManager::m_sAnimationArray[nCount][nWeapon][nAnimation] = dwFileIndex;

				// TK-BM
				if (nCount == 0)
				{
					if (nAnimation >= 4 && nAnimation < 9)
					{
						for (int nRemainIndex = nAnimation + 1; nRemainIndex < 10; ++nRemainIndex)
							MeshManager::m_sAnimationArray[nCount][nWeapon][nRemainIndex] = MeshManager::m_sAnimationArray[nCount][nWeapon][nAnimation];
					}
					if (nAnimation >= 25 && nAnimation < 29)
					{
						for (int nRemainIndex = nAnimation + 1; nRemainIndex < 30; ++nRemainIndex)
							MeshManager::m_sAnimationArray[nCount][nWeapon][nRemainIndex] = MeshManager::m_sAnimationArray[nCount][nWeapon][nAnimation];
					}
					if (nWeapon >= 12)
					{
						MeshManager::m_sAnimationArray[0][nWeapon][11] = MeshManager::m_sAnimationArray[nCount][11][11];
						MeshManager::m_sAnimationArray[0][nWeapon][12] = MeshManager::m_sAnimationArray[nCount][11][12];
						MeshManager::m_sAnimationArray[0][nWeapon][14] = MeshManager::m_sAnimationArray[nCount][11][14];
					}
					if (nArrayIndex == 138)
					{
						for (int nAniTypeNum = 1; nAniTypeNum < 60; ++nAniTypeNum)
						{
							for (int nAniMotionNum = 0; nAniMotionNum < 56; ++nAniMotionNum)
								MeshManager::m_sAnimationArray[nCount][nAniTypeNum][nAniMotionNum] = MeshManager::m_sAnimationArray[nCount][0][nAniMotionNum];
						}
					}
				}
				else if (nCount == 1)
				{
					if (nAnimation >= 4 && nAnimation < 9)
					{
						for (int nRemainIndex = nAnimation + 1; nRemainIndex < 10; ++nRemainIndex)
							MeshManager::m_sAnimationArray[nCount][nWeapon][nRemainIndex] = MeshManager::m_sAnimationArray[nCount][nWeapon][nAnimation];
					}
					if (nAnimation >= 25 && nAnimation < 29)
					{
						for (int nRemainIndex = nAnimation + 1; nRemainIndex < 30; ++nRemainIndex)
							MeshManager::m_sAnimationArray[nCount][nWeapon][nRemainIndex] = MeshManager::m_sAnimationArray[nCount][nWeapon][nAnimation];
					}
					if (nWeapon == 2 && nAnimation == 4)
					{
						for (int nRemainIndex = 0; nRemainIndex < 4; ++nRemainIndex)
							MeshManager::m_sAnimationArray[nCount][nWeapon][nRemainIndex] = MeshManager::m_sAnimationArray[nCount][1][nRemainIndex];
					}
					if (nArrayIndex == 137)
					{
						for (int nAniTypeNum = 1; nAniTypeNum < MAX_ANI_TYPE; ++nAniTypeNum)
						{
							for (int nAniMotionNum = 0; nAniMotionNum < MAX_ANI_MOTION; ++nAniMotionNum)
								MeshManager::m_sAnimationArray[nCount][nAniTypeNum][nAniMotionNum] = MeshManager::m_sAnimationArray[nCount][0][nAniMotionNum];
						}
					}
				}
			}
			else if(nCount == 2)
			{
				int nArrayIndex = m_stValidAniList[2][nFI].nI + 1;
				int nWeapon = nArrayIndex / 100 - 1;
				int nAnimation = nArrayIndex % 100 - 1;
				MeshManager::m_sAnimationArray[2][nWeapon][nAnimation] = dwFileIndex;

				if (nAnimation == 3)
				{
					for (int i = 4; i < 5; ++i)
						MeshManager::m_sAnimationArray[nCount][nWeapon][i] = MeshManager::m_sAnimationArray[nCount][nWeapon][nAnimation];
				}
				if (nArrayIndex == 307)
				{
					for (int nAniMotionNum = 0; nAniMotionNum < MAX_ANI_MOTION; ++nAniMotionNum)
						MeshManager::m_sAnimationArray[nCount][3][nAniMotionNum] = MeshManager::m_sAnimationArray[nCount][2][nAniMotionNum];
				}
				if (nArrayIndex == 107)
				{
					for (int nAniTypeNum = 1; nAniTypeNum < MAX_ANI_TYPE; ++nAniTypeNum)
					{
						for (int nAniMotionNum = 0; nAniMotionNum < MAX_ANI_MOTION; ++nAniMotionNum)
							MeshManager::m_sAnimationArray[nCount][nAniTypeNum][nAniMotionNum] = MeshManager::m_sAnimationArray[nCount][0][nAniMotionNum];
					}
				}
			}
			else if (nCount == 5)
			{
				int nArrayIndex = m_stValidAniList[5][nFI].nI + 1;
				MeshManager::m_sAnimationArray[4][nArrayIndex / 100 + 59][nArrayIndex % 100 - 1] = dwFileIndex;
				if (nArrayIndex == 111)
				{
					for (int nAniTypeNum = 1; nAniTypeNum < MAX_ANI_TYPE; ++nAniTypeNum)
					{
						for (int nAniMotionNum = 0; nAniMotionNum < MAX_ANI_MOTION; ++nAniMotionNum)
							MeshManager::m_sAnimationArray[nCount][nAniTypeNum][nAniMotionNum] = MeshManager::m_sAnimationArray[nCount][0][nAniMotionNum];
					}
				}
			}
			else if (nCount == 3)
			{
				int nArrayIndex = m_stValidAniList[3][nFI].nI + 1;
				MeshManager::m_sAnimationArray[2][nArrayIndex / 100 + 59][nArrayIndex % 100 - 1] = dwFileIndex;
				if (nArrayIndex == 108)
				{
					for (int nAniTypeNum = 1; nAniTypeNum < MAX_ANI_TYPE; ++nAniTypeNum)
					{
						for (int nAniMotionNum = 0; nAniMotionNum < MAX_ANI_MOTION; ++nAniMotionNum)
							MeshManager::m_sAnimationArray[nCount][nAniTypeNum][nAniMotionNum] = MeshManager::m_sAnimationArray[nCount][0][nAniMotionNum];
					}
				}
			}
			else if (nCount == 4)
			{
				int nArrayIndex = m_stValidAniList[4][nFI].nI + 1;
				int nWeapon = nArrayIndex / 100 - 1;
				int nAnimation = nArrayIndex % 100 - 1;
				MeshManager::m_sAnimationArray[4][nWeapon][nAnimation] = dwFileIndex;

				if (nAnimation == 3)
				{
					for (int ll = 4; ll < 5; ++ll)
						MeshManager::m_sAnimationArray[nCount][nWeapon][ll] = MeshManager::m_sAnimationArray[nCount][nWeapon][nAnimation];
				}
				if (nArrayIndex == 108)
				{
					for (int nAniTypeNum = 1; nAniTypeNum < MAX_ANI_TYPE; ++nAniTypeNum)
					{
						for (int nAniMotionNum = 0; nAniMotionNum < MAX_ANI_MOTION; ++nAniMotionNum)
							MeshManager::m_sAnimationArray[nCount][nAniTypeNum][nAniMotionNum] = MeshManager::m_sAnimationArray[nCount][0][nAniMotionNum];
					}
				}
			}
			else if(nCount == 28 || nCount == 7)
			{
				if (m_stValidAniList[nCount][nFI].nI == 107)
				{
					for (int nAniTypeNum = 1; nAniTypeNum < MAX_ANI_TYPE; ++nAniTypeNum)
					{
						for (int nAniMotionNum = 0; nAniMotionNum < MAX_ANI_MOTION; ++nAniMotionNum)
							MeshManager::m_sAnimationArray[nCount][nAniTypeNum][nAniMotionNum] = MeshManager::m_sAnimationArray[nCount][0][nAniMotionNum];
					}
				}
			}

			if (++dwFileIndex >= MeshManager::m_BoneAnimationList[nCount].numAniTypeCount)
			{
				g_nMaxSizeOffset[nCount] = nOffset * sizeof(D3DXMATRIX);
				break;
			}
		}
	}

	fclose(fpList);
	return 1;
}

HRESULT MeshManager::RestoreDeviceObjects()
{
	return S_OK;
}

void MeshManager::ReleaseMesh()
{
	for (int nIndex = 0; nIndex < MAX_COMMON_MESH; ++nIndex)
	{
		SAFE_DELETE(m_stCommonMesh[nIndex].pMesh);
	}

	for (int nIndex = 0; nIndex < MAX_SKIN_MESH_LIST; ++nIndex)
	{
		memset(m_stSkinMeshList[nIndex].szFileName, 0, sizeof(m_stSkinMeshList[nIndex].szFileName));
		
		SAFE_DELETE(m_stSkinMeshList[nIndex].pMesh);

		if (m_stSkinMeshList[nIndex].m_pBoneMatrix != nullptr)
		{
			free(m_stSkinMeshList[nIndex].m_pBoneMatrix);
			m_stSkinMeshList[nIndex].m_pBoneMatrix = nullptr;
		}
		if (m_stSkinMeshList[nIndex].m_dwNames != nullptr)
		{
			free(m_stSkinMeshList[nIndex].m_dwNames);
			m_stSkinMeshList[nIndex].m_dwNames = nullptr;
		}
	}
}

void MeshManager::ReleaseNotUsingMesh()
{
	unsigned int dwCurrentTime = timeGetTime();
	if (m_LastLoadTime + 1200 <= dwCurrentTime)
	{
		m_LastLoadTime = dwCurrentTime;

		for (int nIndex = 0; nIndex < MAX_COMMON_MESH; ++nIndex)
		{
			if (m_stCommonMesh[nIndex].pMesh != nullptr)
			{
				if (dwCurrentTime - m_stCommonMesh[nIndex].pMesh->m_dwLastUsedTime > m_stCommonMesh[nIndex].pMesh->m_dwShowTime)
				{
					SAFE_DELETE(m_stCommonMesh[nIndex].pMesh);
				}
			}
		}
	}
}

int MeshManager::ReadObjectMask()
{
	int nCheckSum = 0;

	FILE* fp = nullptr;
	fopen_s(&fp, ObjectMask_Path, "rb");

	if (fp == nullptr)
	{
		MessageBox(0, "Can't read object.bin", "ERROR", MB_OK);
		return 0;
	}

	for (int MaskNum = 0; MaskNum < MAX_OBJECT_MASK; ++MaskNum)
	{
		for (int MaskY = 0; MaskY < 16; ++MaskY)
		{
			fread(MeshManager::m_aObjectMask[MaskNum][MaskY], 16, 1, fp);

			for (int i = 0; i < 16; ++i)
			{
				nCheckSum += MeshManager::m_aObjectMask[MaskNum][MaskY][i] % 4 + 2 * MaskY + 5 * MaskNum;
			}
		}
	}

	char* pTemp = (char*)MeshManager::m_aObjectMask;

	int nLen = strlen((char*)ObjectMaskEncKeys);
	for (int j = 0; j < sizeof(MeshManager::m_aObjectMask); ++j)
		pTemp[j] = pTemp[j] - ObjectMaskEncKeys[j % nLen] - j;

	int nRCheckSum = 0;
	fread(&nRCheckSum, 4u, 1u, fp);
	fclose(fp);

	if (nCheckSum != nRCheckSum)
	{
		MessageBoxA(0, "Object.bin File Crashed", "CheckSum Error", MB_OK);
		return 0;
	}

	return 1;
}

int MeshManager::LoadCommonMesh(int nIndex, int bEffect)
{
	Sleep(0);

	if (m_stCommonMesh[nIndex].pMesh != nullptr)
		return 0;

	m_stCommonMesh[nIndex].pMesh = new TMMesh();

	if (m_stCommonMesh[nIndex].pMesh == nullptr)
		return 0;

	if (bEffect == 1)
		m_stCommonMesh[nIndex].pMesh->m_bEffect = 1;

	if (!m_stCommonMesh[nIndex].pMesh->LoadMsa(m_stCommonMesh[nIndex].szFileName))
		m_stCommonMesh[nIndex].pMesh->m_bEffect = 0;

	return 1;
}

TMMesh* MeshManager::GetCommonMesh(int nIndex, int bEffect, DWORD showTime)
{
	if (nIndex < 0 || nIndex >= MAX_COMMON_MESH)
		return 0;

	if (m_stCommonMesh[nIndex].pMesh == nullptr)
		LoadCommonMesh(nIndex, bEffect);

	if (m_stCommonMesh[nIndex].pMesh == nullptr)
		return 0;

	if (m_stCommonMesh[nIndex].pMesh->m_bEffect != bEffect)
		m_stCommonMesh[nIndex].pMesh->m_bEffect = bEffect;

	m_stCommonMesh[nIndex].pMesh->m_dwLastUsedTime = timeGetTime();
	m_stCommonMesh[nIndex].pMesh->m_dwShowTime = showTime;
	return m_stCommonMesh[nIndex].pMesh;
}

int MeshManager::GetSkinMeshIndex(char* szSkinMeshName)
{
	for (int nIndex = 0; nIndex < MAX_SKIN_MESH_LIST; ++nIndex)
	{
		if (m_stSkinMeshList[nIndex].pMesh != nullptr)
		{
			if (!strcmp(m_stSkinMeshList[nIndex].szFileName, szSkinMeshName))
				return nIndex;
		}
	}

	return -1;
}

int MeshManager::GetAvailableSkinMeshIndex()
{
	for (int nIndex = 0; nIndex < MAX_SKIN_MESH_LIST; ++nIndex)
	{
		if (m_stSkinMeshList[nIndex].pMesh == nullptr)
			return nIndex;
	}

	return -1;
}
