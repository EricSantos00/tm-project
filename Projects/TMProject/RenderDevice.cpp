#include "pch.h"
#include "GeomObject.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "TMFont2.h"
#include "RenderDevice.h"
#include "TMGlobal.h"
#include "TMLog.h"

int RenderDevice::m_nBright = 50;
DWORD RenderDevice::m_dwCurrScreenX = 1024;
DWORD RenderDevice::m_dwCurrScreenY = 768;
DWORD RenderDevice::m_dwCurrBpp = 32;
DWORD RenderDevice::m_dwCurrRefreshRate = 60;
int RenderDevice::m_nFontSize = 12;
int RenderDevice::m_nLargeFontSize = 40;
int RenderDevice::m_nFontTextureSize = 512;
int RenderDevice::m_nFontTextureSizeY = 64;
float RenderDevice::m_fWidthRatio = 1.0f;
float RenderDevice::m_fHeightRatio = 1.0f;
float RenderDevice::m_fFOVY = 0.25f;
int RenderDevice::m_bCameraRot = 1;

RenderDevice::RenderDevice(DWORD dwScreenWidth, DWORD dwScreenHeight, DWORD dwBitCount, int bFullScreen)
{
	m_pOldRenderTarget = nullptr;
	m_pOldDepthStencil = nullptr;
	m_pSprite = nullptr;
	m_pFont = nullptr;
	m_pDXFont = nullptr;
	m_pDXFontLarge = nullptr;
	m_pTextureManager = nullptr;
	m_pMeshManager = nullptr;

	m_dwBufferUsage = 24;
	m_d3dEnumeration.AppUsesDepthBuffer = 1;
	m_d3dEnumeration.AppUsesMixedVP = 1;
	m_dwClearColor = 0;
	m_dwScreenWidth = dwScreenWidth;
	m_dwScreenHeight = dwScreenHeight;
	m_dwBitCount = dwBitCount;
	m_bFull = bFullScreen;
	m_nWidthShift = 0;
	m_nHeightShift = 0;
	m_bLoadMeshManager = 0;
	m_fFPS = 0.0f;
	m_fFogStart = 60.0f;
	m_fFogEnd = 156.0f;
	m_dwStartTime = 0;
	m_bFog = 1;
	m_bShowEffects = 1;
	m_bSupportPS11 = 0;
	m_bSupportVS20 = 0;

	RenderDevice::m_fWidthRatio = (float)m_dwScreenWidth / 800.0f;
	RenderDevice::m_fHeightRatio = (float)m_dwScreenHeight / 600.0f;

	m_bSavage = 0;

	RenderDevice::m_nLargeFontSize = (int)((float)RenderDevice::m_nLargeFontSize * RenderDevice::m_fWidthRatio);

	memset(m_dwRenderStateList, -1, sizeof(m_dwRenderStateList));
	memset(m_hbmBitmap, 0, sizeof(m_hbmBitmap));
	memset(m_hDC, 0, sizeof(m_hDC));
	memset(m_hFont, 0, sizeof(m_hFont));
	memset(&m_bmi, 0, sizeof(m_bmi));
	memset(m_pBitmapBits, 0, sizeof(m_pBitmapBits));

	for (int nStage = 0; nStage < 8; ++nStage)
	{
		memset(m_dwTextureStageStateList[nStage], 0, sizeof(m_dwTextureStageStateList[nStage]));
		m_pTexture[nStage] = nullptr;
	}

	for (int nStagea = 0; nStagea < 8; ++nStagea)
	{
		memset(m_dwSamplerStateList[nStagea], -1, sizeof(m_dwSamplerStateList[nStagea]));
	}

	for (int i = 0; i < 2; ++i)
	{
		memset(&m_light[i], 0, sizeof(m_light[i]));
		m_light[i].Type = D3DLIGHTTYPE::D3DLIGHT_DIRECTIONAL;
		m_light[i].Ambient.r = 0.0f;
		m_light[i].Ambient.g = 0.0f;
		m_light[i].Ambient.b = 0.0f;

		if (i == 0)
		{
			m_light[0].Direction = D3DXVECTOR3(-10.0f, 10.0f, -6.0f);
			
			D3DXVECTOR3 vecDir(m_light[0].Direction.x, m_light[0].Direction.y, m_light[0].Direction.z);
			D3DXVec3Normalize((D3DXVECTOR3*)&m_light[0].Direction, &vecDir);
		}
		else if (i == 1)
		{
			m_light[1].Direction = D3DXVECTOR3(10.0f, -14.0f, 6.0f);

			D3DXVECTOR3 vecDir(m_light[1].Direction.x, m_light[1].Direction.y, m_light[1].Direction.z);
			D3DXVec3Normalize((D3DXVECTOR3*)&m_light[1].Direction, &vecDir);
		}
	}

	for (int ia = 0; ia < 8; ++ia)
	{
		m_pVertexShader[ia] = nullptr;
		m_pVertexDeclaration[ia] = nullptr;
	}

	for (int ib = 0; ib < 4; ++ib)
	{
		m_pVSEffect[ib] = nullptr;
		m_pVDEffect[ib] = nullptr;
	}

	for (int ic = 0; ic < 6; ++ic)
	{
		m_pPSEffect[ic] = nullptr;
	}

	m_colorLight.r = 1.0f;
	m_colorLight.g = 1.0f;
	m_colorLight.b = 1.0f;
	m_colorBackLight.r = 0.69f;
	m_colorBackLight.g = 0.69f;
	m_colorBackLight.b = 0.69f;

	m_vPickRayDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vPickRayOrig = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// TODO: add a throw here if the g_pDevice is not null
	g_pDevice = this;
}

RenderDevice::~RenderDevice()
{
	Finalize();
	g_pDevice = nullptr;
}

int RenderDevice::Initialize(HWND hWnd)
{
	if (!Initialize(hWnd))
		return 0;

	if (m_bFull)
		ToggleFullscreen();

	if (m_pTextureManager == nullptr)
	{
		m_pTextureManager = new TextureManager();

		if (!m_pTextureManager->InitTextureManager())
		{
			LOG_WRITELOG("Initialize Texture Manager Failed\r\n");
			return 0;
		}

		if (m_pMeshManager != nullptr)
			m_pMeshManager->RestoreDeviceObjects();
		if (m_pTextureManager != nullptr)
			m_pTextureManager->RestoreRenderTargetTexture();
	}

	if (m_pFont == nullptr)
	{
		m_pFont = new TMFont2();
	}

	if (m_pSprite == nullptr)
	{
		if (FAILED(D3DXCreateSprite(m_pd3dDevice, &m_pSprite)))
		{
			LOG_WRITELOG("Error Create Sprite\r\n");
			return 0;
		}
	}

	if (!InitVertexShader())
	{
		LOG_WRITELOG("Error VertexShader \r\n");
		return 0;
	}

	if (!InitPixelShader())
	{
		LOG_WRITELOG("Error Pixel Shader \r\n");
		return 0;
	}

	if (!InitializeRenderingState())
	{
		LOG_WRITELOG("Error Rendering State\r\n");
		return 0;
	}

	m_MiniMapVertex2[0].position = m_CtrlVertex[0].position = m_CtrlVertex2[0].position = m_CtrlVertexC2[0].position = TMVector3(0.0f, 0.0f, 0.009f);

	m_CtrlVertex[0].rhw = 1.0f;
	m_CtrlVertex2[0].rhw = 1.0f;
	m_CtrlVertexC2[0].rhw = 1.0f;
	m_MiniMapVertex2[0].rhw = 1.0f;
	m_CtrlVertex[0].diffuse = 0xAAAAAAAA;
	m_CtrlVertex2[0].diffuse = 0xAAAAAAAA;
	m_CtrlVertexC2[0].diffuse = 0xAAAAAAAA;
	m_MiniMapVertex2[0].diffuse = 0xAAAAAAAA;
	m_CtrlVertex[0].tu = 0.009f;
	m_CtrlVertex2[0].tu1 = 0.009f;
	m_CtrlVertexC2[0].tu1 = 0.009f;
	m_MiniMapVertex2[0].tu1 = 0.009f;
	m_CtrlVertex[0].tv = 0.009f;
	m_CtrlVertex2[0].tv1 = 0.009f;
	m_CtrlVertexC2[0].tv1 = 0.009f;
	m_MiniMapVertex2[0].tv1 = 0.009f;

	m_MiniMapVertex2[1].position = m_CtrlVertex[1].position = m_CtrlVertex2[1].position = m_CtrlVertexC2[1].position = TMVector3(0.0f, 0.0f, 0.009f);

	m_CtrlVertex[1].rhw = 1.0f;
	m_CtrlVertex2[1].rhw = 1.0f;
	m_CtrlVertexC2[1].rhw = 1.0f;
	m_MiniMapVertex2[1].rhw = 1.0f;
	m_CtrlVertex[1].diffuse = 0xAAAAAAAA;
	m_CtrlVertex2[1].diffuse = 0xAAAAAAAA;
	m_CtrlVertexC2[1].diffuse = 0xAAAAAAAA;
	m_MiniMapVertex2[1].diffuse = 0xAAAAAAAA;
	m_CtrlVertex[1].tu = 0.99f;
	m_CtrlVertex2[1].tu1 = 0.99f;
	m_CtrlVertexC2[1].tu1 = 0.99f;
	m_MiniMapVertex2[1].tu1 = 0.99f;
	m_CtrlVertex[1].tv = 0.009f;
	m_CtrlVertex2[1].tv1 = 0.009f;
	m_CtrlVertexC2[1].tv1 = 0.009f;
	m_MiniMapVertex2[1].tv1 = 0.009f;

	m_MiniMapVertex2[2].position = m_CtrlVertex[2].position = m_CtrlVertex2[2].position = m_CtrlVertexC2[2].position = TMVector3(0.0f, 0.0f, 0.009f);

	m_CtrlVertex[2].rhw = 1.0f;
	m_CtrlVertex2[2].rhw = 1.0f;
	m_CtrlVertexC2[2].rhw = 1.0f;
	m_MiniMapVertex2[2].rhw = 1.0f;
	m_CtrlVertex[2].diffuse = 0xAAAAAAAA;
	m_CtrlVertex2[2].diffuse = 0xAAAAAAAA;
	m_CtrlVertexC2[2].diffuse = 0xAAAAAAAA;
	m_MiniMapVertex2[2].diffuse = 0xAAAAAAAA;
	m_CtrlVertex[2].tu = 0.99f;
	m_CtrlVertex2[2].tu1 = 0.99f;
	m_CtrlVertexC2[2].tu1 = 0.99f;
	m_MiniMapVertex2[2].tu1 = 0.99f;
	m_CtrlVertex[2].tv = 0.99f;
	m_CtrlVertex2[2].tv1 = 0.99f;
	m_CtrlVertexC2[2].tv1 = 0.99f;
	m_MiniMapVertex2[2].tv1 = 0.99f;

	m_MiniMapVertex2[3].position = m_CtrlVertex[3].position = m_CtrlVertex2[3].position = m_CtrlVertexC2[3].position = TMVector3(0.0f, 0.0f, 0.009f);

	m_CtrlVertex[3].rhw = 1.0f;
	m_CtrlVertex2[3].rhw = 1.0f;
	m_CtrlVertexC2[3].rhw = 1.0f;
	m_MiniMapVertex2[3].rhw = 1.0f;
	m_CtrlVertex[3].diffuse = 0xAAAAAAAA;
	m_CtrlVertex2[3].diffuse = 0xAAAAAAAA;
	m_CtrlVertexC2[3].diffuse = 0xAAAAAAAA;
	m_MiniMapVertex2[3].diffuse = 0xAAAAAAAA;
	m_CtrlVertex[3].tu = 0.009f;
	m_CtrlVertex2[3].tu1 = 0.009f;
	m_CtrlVertexC2[3].tu1 = 0.009f;
	m_MiniMapVertex2[3].tu1 = 0.009f;
	m_CtrlVertex[3].tv = 0.99f;
	m_CtrlVertex2[3].tv1 = 0.99f;
	m_CtrlVertexC2[3].tv1 = 0.99f;
	m_MiniMapVertex2[3].tv1 = 0.99f;

	SetGamma();

	return 1;
}

void RenderDevice::Finalize()
{
}

void RenderDevice::SetViewPort(int nStartX, int nStartY, int nWidth, int nHeight)
{
}

int RenderDevice::Lock(int bClear)
{
	return 0;
}

int RenderDevice::Unlock(int bEnd)
{
	return 0;
}

void RenderDevice::SetLight()
{
}

void RenderDevice::SetWindowedFullScreen()
{
}

void RenderDevice::RestoreWindowMode()
{
}

int RenderDevice::ChangeDisplay(DWORD x, DWORD y, DWORD bpp, DWORD ref)
{
	return 0;
}

HRESULT RenderDevice::GetCurrentDisplayMode(PDEVMODE devMode)
{
	return E_NOTIMPL;
}

HRESULT RenderDevice::ConfirmDevice(D3DCAPS9* pCaps, DWORD dwBehavior, D3DFORMAT Format)
{
	return E_NOTIMPL;
}

HRESULT RenderDevice::RestoreDeviceObjects()
{
	return E_NOTIMPL;
}

HRESULT RenderDevice::InvalidateDeviceObjects()
{
	return E_NOTIMPL;
}

void RenderDevice::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
}

void RenderDevice::SetTextureStageState(DWORD dwStage, D3DTEXTURESTAGESTATETYPE type, DWORD Value)
{
}

void RenderDevice::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
}

void RenderDevice::SetSamplerState(DWORD dwStage, D3DSAMPLERSTATETYPE State, DWORD Value)
{
}

void RenderDevice::SetGamma()
{
}

int RenderDevice::InitMeshManager()
{
	return 0;
}

int RenderDevice::InitVertexShader()
{
	return 0;
}

int RenderDevice::InitPixelShader()
{
	return 0;
}

int RenderDevice::InitializeRenderingState()
{
	return 0;
}

int RenderDevice::SetRenderStateBlock(int nIndex)
{
	return 0;
}

int RenderDevice::SetViewVector(TMVector3 ivCamera, TMVector3 ivLookat)
{
	return 0;
}

HRESULT RenderDevice::SetProjectionMatrix()
{
	return E_NOTIMPL;
}

int RenderDevice::SetMatrixForUI()
{
	return 0;
}

void RenderDevice::GetPickRayVector(D3DXVECTOR3* pRickRayOrig, D3DXVECTOR3* pPickRayDir)
{
}

void RenderDevice::RenderRect(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY, IDirect3DTexture9* pTexture, float fScaleX, float fScaleY)
{
}

void RenderDevice::RenderRectC(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY, IDirect3DTexture9* pTexture, DWORD dwColor, float fScaleX, float fScaleY)
{
}

void RenderDevice::RenderRectCoord(float iDestX, float iDestY, float iCX, float iCY, IDirect3DTexture9* pTexture, DWORD dwColor, float fU, float fV)
{
}

void RenderDevice::RenderRectNoTex(float iX, float iY, float iCX, float iCY, DWORD dwColor, int bTrans)
{
}

void RenderDevice::RenderRectTex(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY, float DestCX, float DestCY, IDirect3DTexture9* pTexture, DWORD dwColor, int bTrans, float fAngle, float fScale)
{
}

void RenderDevice::RenderRectTex2C(float iStartX, float iStartY, float iCX, float iCY, float iStartX2, float iStartY2, float iCX2, float iCY2, float iDestX, float iDestY, float DestCX, float DestCY, IDirect3DTexture9* pTexture, IDirect3DTexture9* pTexture2, DWORD dwColor, int bTrans, float fAngle, float fScale)
{
}

void RenderDevice::RenderRectTex2(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY, float DestCX, float DestCY, IDirect3DTexture9* pTexture, IDirect3DTexture9* pTexture2, DWORD dwColor, int bTrans, float fAngle, float fScale)
{
}

void RenderDevice::RenderRectTex2M(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY, float DestCX, float DestCY, IDirect3DTexture9* pTexture, IDirect3DTexture9* pTexture2, DWORD dwColor, int bTrans, float fAngle, float fScale)
{
}

void RenderDevice::RenderRectTexDamage(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY, float DestCX, float DestCY, IDirect3DTexture9* pTexture, DWORD dwColor, int bTrans, float fAngle, float fScale)
{
}

void RenderDevice::RenderRectProgress2(float iX, float iY, float iCX, float iCY, float fProgress, DWORD dwColor)
{
}

void RenderDevice::RenderRectRot(float iStartX, float iStartY, float iCX, float iCY, float iDestX, float iDestY, float nCenX, float nCenY, float fAngle, IDirect3DTexture9* pTexture, float fScaleX, float fScaleY)
{
}

void RenderDevice::LogRenderState()
{
}

void RenderDevice::LogSamplerState()
{
}

void RenderDevice::LogTextureStageState()
{
}

void RenderDevice::RenderGeomRectImage(GeomControl* ipControl)
{
}

void RenderDevice::RenderGeomControl(GeomControl* ipControl)
{
}

void RenderDevice::RenderGeomControlBG(GeomControl* ipControl, DWORD dwColor, int nTextureIndex)
{
}
