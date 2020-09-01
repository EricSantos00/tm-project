#pragma once

#include "TreeNode.h"
#include "Structures.h"

class TMGround;
class TMSkinMesh;

class TMObject : public TreeNode
{
public:
	TMObject();
	~TMObject();

	virtual int InitObject();
	virtual void InitPosition(float fX, float fY, float fZ);
	virtual void InitAngle(float fYaw, float fPitch, float fRoll);
	virtual void SetPosition(float fX, float fY, float fZ);
	virtual void SetAngle(float fYaw, float fPitch, float fRoll);

	int FrameMove(unsigned int dwServerTime) override;
	int Render() override;

	virtual int IsVisible();
	virtual int IsInTown();
	virtual int IsInPKZone();
	virtual int IsInCastleZone();
	virtual int IsInCastleZone2();
	virtual int IsChannelWarZone(int nPositionX, int nPositionY);
	virtual int IsInHouse();
	virtual int IsInView();
	virtual int RegisterMask(TMGround* pGround, float fX, float fY);
	virtual void Save(FILE* fp);
	virtual int IsMouseOver();
	virtual int isVisualKey();
	virtual int isCamPos();

	void ResetObject();

public:
	unsigned int m_dwObjType;
	TMVector2 m_vecPosition;
	float m_fHeight;
	float m_fAngle;
	float m_fScale;
	int m_nTextureSetIndex;
	int m_nMaskIndex;
	int m_bCheckKey;
	int m_bVisible;
	int m_bNullObj;
	TMVector3 m_vecSkinPos;
	int m_nSkinMeshType;
	TMSkinMesh* m_pSkinMesh;
	TMVector3 m_vecTempPos[11];
	float m_AlphaColor;
	int m_nAlpha;
	int m_bAlphaObj;
};