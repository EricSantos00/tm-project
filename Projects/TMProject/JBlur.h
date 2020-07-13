#pragma once

struct BLURVERTEX
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 tex;
};

struct BLURRENDERVERTEX
{
	D3DXVECTOR4 pos;
	unsigned int color;
	D3DXVECTOR2 tex;
};

struct MBVERTEX
{
	D3DXVECTOR4 pos;
	unsigned int color;
	D3DXVECTOR2 tex;
};

class JBlur
{
public:
	JBlur();
	virtual ~JBlur();

	int InitObject();
	int MakeVB();
	int Begin();
	void End();
	int BeginMotionBlur();
	void EndMotionBlur();
	void Render();
	void MakeBlur();
	void SwitchSetTexture();
	void SetLoginColor();
	void SetDefaultColor();
	void CopyTexture(int nScale, IDirect3DTexture9* pSrc, IDirect3DSurface9* pDestSurface, float fDepth);
	void SetVSConstant(float fScale, float fWidth, float fHeight, float fWidthPixelOffset, float fHeightPixelOffset, float fDepth);

public:
	IDirect3DSurface9* m_pOldSurface;
	int m_nCurrSetTexture;
	int m_nCurrDrawTexture;
	D3DXMATRIX m_matOrthoProj;
	int m_bForceColor;
	BLURVERTEX m_pBlurVertex[4];
	BLURRENDERVERTEX m_pRenderVertex[4];
	unsigned int m_dwAlpha;
	MBVERTEX m_vecMB[4];
	int m_bMotionBlur;
	int m_nCurrGlowSetTexture;
	int m_nCurrGlowDrawTexture;
	int m_bEnable;
	int m_bEnableGlow;
};