#pragma once

class TMMesh;
class TMSkinMesh;
class CMesh
{
public:
	CMesh(TMSkinMesh* pParentSkin);
	~CMesh();

	virtual int Render(int bBright);

	int LoadMesh(char* file);
	int InitEffect();
	void SetMaterial(char cAlpha);

private:
	int RenderMesh(char cAlpha);

public:
	TMMesh* m_pMesh;
	DWORD m_dwID;
	DWORD m_numPalette;
	D3DXMATRIX* m_pBoneMatrix; // 0x10
	D3DXMATRIX* m_pBoneOffset[40]; // 0x14
	DWORD* m_dwNames;
	DWORD m_numFaceInflunce;
	int m_bMeshGenerated;
	TMSkinMesh* m_pParentSkin;
	short m_sMultiType;
	short m_sLegendType;
	int m_nTextureIndex;
	DWORD m_numFaces;
	int m_nSkinMeshIndex;
	bool m_bHead;
	bool m_bMount;
	bool m_god2cos;
	int m_god2Alpha;
	int m_god2Red;
	int m_god2Green;
	int m_god2Brue;
	int m_bSheild;
};