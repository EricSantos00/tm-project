#pragma once

#include "D3DDevice.h"
#include "Structures.h"

class TMFont2;
class TextureManager;
class MeshManager;
class GeomControl;

class RenderDevice : public D3DDevice
{
public:
	RenderDevice(DWORD dwScreenWidth, DWORD dwScreenHeight, DWORD dwBitCount, int bFullScreen);
	~RenderDevice();

	int Initialize(HWND hWnd) override;

	virtual void Finalize();
	virtual void SetViewPort(int nStartX, int nStartY, int nWidth, int nHeight);
	virtual int Lock(int bClear);
	virtual int Unlock(int bEnd);

	void SetLight();
	void SetWindowedFullScreen();
	void RestoreWindowMode();
	int ChangeDisplay(DWORD x, DWORD y, DWORD bpp, DWORD ref);
	HRESULT GetCurrentDisplayMode(PDEVMODE devMode);

	// Check this ConfirmDevice function, maybe is virtual?
	virtual HRESULT ConfirmDevice(D3DCAPS9* pCaps, DWORD dwBehavior, D3DFORMAT Format);
	HRESULT RestoreDeviceObjects() override;
	HRESULT InvalidateDeviceObjects() override;

	void SetRenderState(D3DRENDERSTATETYPE State, DWORD Value);
	void SetTextureStageState(DWORD dwStage, D3DTEXTURESTAGESTATETYPE type, DWORD Value);
	void SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture);
	void SetSamplerState(DWORD dwStage, D3DSAMPLERSTATETYPE State, DWORD Value);
	void SetGamma();
	int InitMeshManager();
	int InitVertexShader();
	int InitPixelShader();
	int InitializeRenderingState();
	int SetRenderStateBlock(int nIndex);
	int SetViewVector(TMVector3 ivCamera, TMVector3 ivLookat);
	HRESULT SetProjectionMatrix();
	int SetMatrixForUI();

	void GetPickRayVector(D3DXVECTOR3* pRickRayOrig, D3DXVECTOR3* pPickRayDir);

	void RenderRect(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY, IDirect3DTexture9* pTexture,
		float fScaleX, float fScaleY);
	void RenderRectC(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY,
		IDirect3DTexture9* pTexture, DWORD dwColor, float fScaleX, float fScaleY);
	void RenderRectCoord(float iDestX, float iDestY, float iCX, float iCY, IDirect3DTexture9* pTexture, DWORD dwColor, float fU, float fV);
	void RenderRectNoTex(float iX, float iY, float iCX, float iCY, DWORD dwColor, int bTrans);
	void RenderRectTex(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY,
		float DestCX, float DestCY, IDirect3DTexture9* pTexture, DWORD dwColor, int bTrans, float fAngle, float fScale);
	void RenderRectTex2C(float iStartX, float iStartY, float iCX, float iCY, float iStartX2, float iStartY2,
		float iCX2, float iCY2, float iDestX, float iDestY, float DestCX, float DestCY, IDirect3DTexture9* pTexture,
		IDirect3DTexture9* pTexture2, DWORD dwColor, int bTrans, float fAngle, float fScale);
	void RenderRectTex2(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY,
		float DestCX, float DestCY, IDirect3DTexture9* pTexture,
		IDirect3DTexture9* pTexture2, DWORD dwColor, int bTrans, float fAngle, float fScale);
	void RenderRectTex2M(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY,
		float DestCX, float DestCY, IDirect3DTexture9* pTexture,
		IDirect3DTexture9* pTexture2, DWORD dwColor, int bTrans, float fAngle, float fScale);
	void RenderRectTexDamage(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY,
		float DestCX, float DestCY, IDirect3DTexture9* pTexture,
		DWORD dwColor, int bTrans, float fAngle, float fScale);
	void RenderRectProgress2(float iX, float iY, float iCX, float iCY, float fProgress, DWORD dwColor);
	void RenderRectRot(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY, float nCenX, float nCenY,
		float fAngle, IDirect3DTexture9* pTexture, float fScaleX, float fScaleY);
	void LogRenderState();
	void LogSamplerState();
	void LogTextureStageState();

	void RenderGeomRectImage(GeomControl* ipControl);
	void RenderGeomControl(GeomControl* ipControl);
	void RenderGeomControlBG(GeomControl* ipControl, DWORD dwColor, int nTextureIndex);

public:
	unsigned int m_dwStartTime;
	D3DVIEWPORT9 m_viewport;
	int m_nWidthShift;
	int m_nHeightShift;
	D3DXMATRIX m_matProj;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matWaterView;
	D3DXMATRIX m_matWorld;
	D3DXVECTOR3 m_vCamera;
	D3DXVECTOR3 m_vLookatPos;
	LPDIRECT3DBASETEXTURE9  m_pTexture[8];
	LPDIRECT3DSURFACE9 m_pOldRenderTarget;
	LPDIRECT3DSURFACE9 m_pOldDepthStencil;
	D3DXVECTOR3 m_vPickRayDir;
	D3DXVECTOR3 m_vPickRayOrig;
	LPDIRECT3DVERTEXSHADER9 m_pVertexShader[8]; // 4E4 = [0]
	LPDIRECT3DVERTEXDECLARATION9 m_pVertexDeclaration[8]; // 504 = [0]
	LPDIRECT3DVERTEXDECLARATION9 m_pVDEffect[4];
	LPDIRECT3DVERTEXSHADER9 m_pVSEffect[4];
	LPDIRECT3DPIXELSHADER9 m_pPSEffect[6];
	D3DCOLORVALUE m_colorLight;
	D3DCOLORVALUE m_colorBackLight;
	D3DCOLORVALUE m_colNormalAmbient;
	LPD3DXSPRITE m_pSprite;
	TMFont2* m_pFont2;
	TMFont2* m_pFont;
	LPD3DXFONT m_pDXFont;
	LPD3DXFONT m_pDXFontLarge;
	TextureManager* m_pTextureManager;
	MeshManager* m_pMeshManager;
	RDTLVERTEX m_CtrlVertex[4];
	RDTLVERTEX m_CtrlProgressVertex[10];
	RDTLVERTEX2 m_CtrlVertex2[4];
	RDTLVERTEX2 m_CtrlVertexC2[4];
	RDTLVERTEX2 m_MiniMapVertex2[4];
	D3DLIGHT9 m_light[2];

	static int m_nBright;

	HFONT m_hFont;
	HDC m_hDC;
	HBITMAP m_hbmBitmap;
	BITMAPINFO m_bmi;
	unsigned int* m_pBitmapBits;
	unsigned int m_bUseSW;
	unsigned int m_dwBufferUsage;
	unsigned int m_dwRenderStateList[256];
	unsigned int m_dwTextureStageStateList[8][29];
	unsigned int m_dwSamplerStateList[8][14];
	unsigned int m_dwClearColor;
	unsigned int m_dwActualClearColor;
	int m_bFog;
	int m_bShowEffects;
	float m_fFogStart;
	float m_fFogEnd;
	int m_bFull;
	int m_bLoadMeshManager;
	int m_bSupportPS11;
	int m_bSupportPS12;
	int m_bSupportVS20;
	int m_nShadowTextureSize;

	static DWORD m_dwCurrScreenX;
	static DWORD m_dwCurrScreenY;
	static DWORD m_dwCurrBpp;
	static DWORD m_dwCurrRefreshRate;

	float m_fFPS;

	static int m_nFontSize;
	static int m_nLargeFontSize;
	static int m_nFontTextureSize;
	static int m_nFontTextureSizeY;
	static float m_fWidthRatio;
	static float m_fHeightRatio;
	static float m_fFOVY;
	static int m_bDungeon;

	int m_bDrawFPS;

	static int m_bCameraRot;
};