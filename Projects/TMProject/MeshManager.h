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

constexpr auto MAX_COMMON_MESH = 3048;
constexpr auto MAX_SKIN_MESH_LIST = 1024;
constexpr auto MAX_BONE_ANIMATION_LIST = 100;

constexpr auto MAX_ANI_CLASS = 6;
constexpr auto MAX_ANI_TYPE = 60;
constexpr auto MAX_ANI_MOTION = 56;

constexpr auto MAX_OBJECT_MASK = 2048;
constexpr auto MAX_MASK_X = 16;
constexpr auto MAX_MASK_Y = 16;

constexpr auto MAX_VALID_ANI_LIST = 100;

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
	stCommonMeshList m_stCommonMesh[MAX_COMMON_MESH];
	stCommonMeshList m_stSkinMeshList[MAX_SKIN_MESH_LIST];

	static stBoneAni m_BoneAnimationList[MAX_BONE_ANIMATION_LIST];
	static short m_sAnimationArray[MAX_ANI_CLASS][MAX_ANI_TYPE][MAX_ANI_MOTION];
	static char m_aObjectMask[MAX_OBJECT_MASK][MAX_MASK_X][MAX_MASK_Y];
	static int m_nFullCount;

	stValidAniList m_stValidAniList[MAX_VALID_ANI_LIST][186];
};