#pragma once

class TMSkinMesh;
class CMesh;
class CFrame
{
public:
	CFrame(DWORD id);
	~CFrame();

	CFrame* FindFrame(DWORD dwID);
	HRESULT InvalidateDeviceObjects();
	int Render();
	void AddFrame(CFrame* pframe);
	void LinkBones(CFrame* root);
	void UpdateFrames(D3DXMATRIX* matCur);

public:
	DWORD m_dwID;
	DWORD m_dwParentID;
	D3DXMATRIX m_matRot;
	D3DXMATRIX m_matCombined;
	CFrame* m_pSibling;
	CFrame* m_pFirstChild;
	CMesh* m_pMesh;
	TMSkinMesh* m_pParentSkin;
};