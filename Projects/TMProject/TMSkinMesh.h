#pragma once

#include "Structures.h"

class CFrame;
class TMHuman;
class TMEffectSWSwing;

constexpr auto MAX_FRAME_TO_ANIMATE = 100;
constexpr auto MAX_VALID_FRAME_TO_ANIMATE = MAX_FRAME_TO_ANIMATE - 20;

class TMSkinMesh
{
public:
	TMSkinMesh(LOOK_INFO* pLook, SANC_INFO* pSanc, int nBoneAniIndex, int bExpand, SANC_INFO* pColor, short nMeshType, short nCos, int mount);
	~TMSkinMesh();

	HRESULT InitDeviceObjects();
	HRESULT RestoreDeviceObjects();

	void FrameMove(unsigned int dwServerTime);
	void InitMaterial(D3DMATERIAL9 material);
	int Render(float fLen, float fScale, float fLen2);

	HRESULT DeleteDeviceObjects();
	HRESULT InvalidateDeviceObjects();

	int SetAnimation(int nIndex);

	void SetPosition(D3DXVECTOR3 vPos);
	void SetPosition(float fX, float fY, float fZ);

	void SetAngle(D3DXVECTOR3 vAngle);
	void SetAngle(float fYaw, float fPitch, float fRoll);

	void SetSwingMatrix();
	void SetVecMantua(int nType, int nSkinIndex);
	
private:
	void RenderSkinMeshEffect();
	void RenderEffect_HorseFireLeg();
	void SetHardcoreMantle(char* szTexture, char* szName);
	void SetOldCostume(int costype, char* szTexture, char* szName);
	void SetRenewOldCostume(int costype, char* szTexture, char* szName);
	void SetCostume(int Costype, char* szTexture, char* szName);
	int MantleException(char* texture);
	BOOL God2Exception(int i);

public:
	int m_nBoneAniIndex;
	int m_bMeshGenerated;
	int m_bExpand;
	D3DXVECTOR3 m_vPosition;
	D3DXVECTOR3 m_vAngle;
	D3DXVECTOR3 m_vScale;
	int m_bBaseMat;
	D3DXMATRIX m_BaseMatrix;
	D3DXMATRIX m_OutMatrix;
	CFrame* m_pRoot;
	CFrame* m_pframeToAnimate[MAX_FRAME_TO_ANIMATE];
	LOOK_INFO m_Look;
	SANC_INFO m_Sanc;
	SANC_INFO m_Color;
	D3DMATERIAL9 m_materials;
	int m_nAniBaseIndex;
	int m_nAniIndex;
	int m_nAniIndexLast;
	int m_dwTickLast;
	unsigned int m_dwStartTime;
	unsigned int m_dwOffset;
	unsigned int m_dwFPS;
	unsigned int m_dwStartOffset;
	unsigned int m_dwLastUsedTime;
	unsigned int m_dwShowTime;
	TMHuman* m_pOwner;
	TMEffectSWSwing* m_pSwingEffect[2];
	float m_fLenDetail;

	static int m_nSmooth;

	char m_cRotate[2];
	char m_cEnableMultiTex;
	char m_cDefaultAlpha;
	D3DXMATRIX m_matMantua;
	unsigned int m_dwTexAni;
	char m_cTexAni;
	short m_nMeshType;
	short m_nCosType;
	int m_bMount;
	int m_bRenderEffect;

private:
	int m_Cos;
};
