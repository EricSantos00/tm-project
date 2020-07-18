#pragma once

#include "Structures.h"

struct RDVERTEX2
{
	TMVector3 position;
	TMVector3 normal;
	float tu1;
	float tv1;
	float tu2;
	float tv2;
};

class TMMesh
{
public:
	TMMesh();
	virtual ~TMMesh();

	virtual int Render(char cMulti, int nTexOffset);
	virtual int Render(float fX, float fY, float fZ, float fAngle, float fAngle2, float fAngle3, char cMulti, int nTexOffset);
	virtual int Render(float fX, float fY, float fZ, D3DXQUATERNION quat, char cMulti, int nTexOffset);
	
	virtual int RenderPick(float fX, float fY, float fZ, float fAngle, float fAngle2, float fAngle3, float cMulti, int nTexOffset);
	virtual int RenderForUI(int nX, int nY, float fAngle, float fScale, DWORD dwColor, int nMultiTex, int nTexOffset, short sLegend);

	int LoadMsa(const char* szFileName);
private:

	// These two functions doesn't exist in the original version
	HRESULT RenderDraw(int nTexOffset);
	void SetTexture(int index);

public:
	int m_bEffect;
	int m_bDummy;
	unsigned int m_sizeVertex;
	unsigned int m_dwFVF;
	unsigned int m_dwAttCount;
	D3DXATTRIBUTERANGE m_AttRange[32];
	int m_nTextureIndex[32];
	IDirect3DVertexBuffer9* m_pVB;
	IDirect3DIndexBuffer9* m_pIB;
	unsigned int m_dwLastUsedTime;
	unsigned int m_dwShowTime;
	int m_nMeshType;
	float m_fScaleH;
	float m_fScaleV;
	TMVector3 m_vecCenter;
	float m_fRadius;
	float m_fMaxX;
	float m_fMinX;
	float m_fMaxY;
	float m_fMinY;
	float m_fMaxZ;
	float m_fMinZ;
	int m_bFirst;
};