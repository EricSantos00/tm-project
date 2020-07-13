#pragma once

class TMMesh;

struct stCommonMeshList
{
	char szFileName[64];
	TMMesh* pMesh;
	D3DXMATRIX* m_pBoneMatrix;
	DWORD* m_dwNames;
	DWORD m_dwID;
	DWORD m_numFaceInflunce;
	DWORD m_numPalette;
};

struct stValidAniList
{
	int nI;
};

struct stBoneAni
{
	char szAniName[128];
	unsigned int numBone; // 0x0ED9560
	unsigned int numParts; // 0x0ED9564
	unsigned int* pBone; // 0x0ED9568
	unsigned int numAniTypeCount; // 0x0ED956C
	unsigned int numAniCut[186]; // 0x0ED9570
	unsigned int numAniFrame; // 0x0ED9858
	D3DXMATRIXA16* matAnimation; // 0x0ED985C
	D3DXQUATERNION* matQuaternion; // 0x0ED9860
};

class MeshManager
{
public:
	MeshManager();
	virtual ~MeshManager();

	int InitMeshManager();
	virtual int InitBoneAnimation();
	virtual HRESULT RestoreDeviceObjects();
	void ReleaseMesh();
	void ReleaseNotUsingMesh();
	int ReadObjectMask();
	int LoadCommonMesh(int nIndex, int bEffect);
	TMMesh* GetCommonMesh(int nIndex, int bEffect, DWORD showTime);
	int GetSkinMeshIndex(char* szSkinMeshName);
	int GetAvailableSkinMeshIndex();

public:
	DWORD m_LastLoadTime;
	stCommonMeshList m_stCommonMesh[3048];
	stCommonMeshList m_stSkinMeshList[1024];

	static stBoneAni m_BoneAnimationList[100];
	static char m_sAnimationArray[6][60][56];
	static char m_aObjectMask[2048][16][16];
	static int m_nFullCount;

	stValidAniList m_stValidAniList[100][186];
};