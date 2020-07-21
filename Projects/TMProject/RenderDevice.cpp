#include "pch.h"
#include "GeomObject.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "TMFont2.h"
#include "RenderDevice.h"
#include "TMGlobal.h"
#include "TMLog.h"
#include "TMSky.h"
#include "TMFieldScene.h"
#include "TMCamera.h"
#include <io.h>
#include <fcntl.h>

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
	RenderDevice::m_nBright = 50;

	D3DGAMMARAMP gamma{};
	m_pd3dDevice->GetGammaRamp(0, &gamma);

	for (int i = 0; i < 256; i++)
	{
		WORD nVal = (float)((float)(((float)RenderDevice::m_nBright * 0.02f) * (float)i) * 256.0f);
		if (nVal > -1)
			nVal = -1;

		gamma.red[i] = nVal;
		gamma.green[i] = nVal;
		gamma.blue[i] = nVal;
	}

	m_pd3dDevice->SetGammaRamp(0, 0, &gamma);

	if (m_d3dpp.Windowed)
	{
		HDC hdc = GetDC(g_pApp->m_hWnd);
		SetDeviceGammaRamp(hdc, &gamma);
		ReleaseDC(g_pApp->m_hWnd, hdc);
	}

	SAFE_DELETE(m_pTextureManager);
	SAFE_DELETE(m_pMeshManager);
	SAFE_RELEASE(m_pSprite);

	for (int ia = 0; ia < 8; ++ia)
	{
		SAFE_RELEASE(m_pVertexShader[ia]);
		SAFE_RELEASE(m_pVertexDeclaration[ia]);
	}

	for (int ib = 0; ib < 4; ++ib)
	{
		SAFE_RELEASE(m_pVSEffect[ib]);
		SAFE_RELEASE(m_pVDEffect[ib]);
	}

	for (int ic = 0; ic < 6; ++ic)
	{
		SAFE_RELEASE(m_pPSEffect[ic]);
	}

	SAFE_DELETE(m_pFont);
	SAFE_DELETE_ARRAY(TMFont2::m_pBuffer);

	Cleanup3DEnvironment();
}

void RenderDevice::SetViewPort(int nStartX, int nStartY, int nWidth, int nHeight)
{
	m_viewport.X = nStartX;
	m_viewport.Y = nStartY;
	m_viewport.Width = nWidth;
	m_viewport.Height = nHeight;
	m_viewport.MinZ = 0.0f;
	m_viewport.MaxZ = 1.0f;

	if (FAILED(m_pd3dDevice->SetViewport(&m_viewport)))
	{
		LOG_WRITEERROR(0x10000006);
	}

	SetProjectionMatrix();
}

int RenderDevice::Lock(int bClear)
{
	if (m_bDeviceLost)
	{
		HRESULT hr = m_pd3dDevice->TestCooperativeLevel();
		if (FAILED(hr))
		{
			constexpr bool a = D3DERR_INVALIDCALL == -2005530516;
			if (hr == D3DERR_DEVICELOST)
				return 0;
			if (hr != D3DERR_DEVICENOTRESET)
				return hr;
			
			if (m_bWindowed)
			{
				D3DAdapterInfo* pAdapterInfo = m_d3dSettings.PAdapterInfo();
				m_pD3D->GetAdapterDisplayMode(pAdapterInfo->AdapterOrdinal, &m_d3dSettings.Windowed_DisplayMode);
				m_d3dpp.BackBufferFormat = m_d3dSettings.Windowed_DisplayMode.Format;
			}

			return Reset3DEnvironment();
		}

		m_bDeviceLost = 0;
	}

	if (bClear)
	{
		if (g_pCurrentScene != nullptr && g_pCurrentScene->m_pSky != nullptr)
		{
			if (RenderDevice::m_bDungeon != 0 && RenderDevice::m_bDungeon != 3 && RenderDevice::m_bDungeon != 4)
				m_dwActualClearColor = 0;
			else if (g_pCurrentScene->m_pSky->m_nState == 0)
				m_dwActualClearColor = 0xFF335599;
			else if (g_pCurrentScene->m_pSky->m_nState == 1)
				m_dwActualClearColor = 0xFF333333;
			else if (g_pCurrentScene->m_pSky->m_nState == 2)
				m_dwActualClearColor = 0xFF441100;
			else if (g_pCurrentScene->m_pSky->m_nState == 3)
				m_dwActualClearColor = 0xFF222222;
		}

		if (FAILED(m_pd3dDevice->Clear(0, nullptr, D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, m_dwActualClearColor, 1.0f, 0)))
			return 0;
	}

	HRESULT result = m_pd3dDevice->BeginScene();

	return result == D3DERR_INVALIDCALL ? 0 : result >= 0;
}

int RenderDevice::Unlock(int bEnd)
{
	if (bEnd == 1 && m_pFont != nullptr)
	{
		float fTime = timeGetTime() * 0.001f;

		static DWORD dwFrames = 0;
		++dwFrames;

		static float fLastTime = 0.0f;
		if ((fTime - fLastTime) > 2.0f)
		{
			m_fFPS = dwFrames / (fTime - fLastTime);
			fLastTime = fTime;
			dwFrames = 0;
			
			static char szString[256];
			sprintf_s(szString, "Ver:%1.3f  FPS : %4.3f", 1.758f, m_fFPS);
		}

		int rect_4 = 0;
		m_bShowEffects = 1;
		if (g_bDebugMsg == 1)
			rect_4 = m_dwScreenHeight - 12;
	}

	if (FAILED(m_pd3dDevice->EndScene()))
		return 0;

	if (bEnd == 1)
	{
		if (m_pd3dDevice->Present(nullptr, nullptr, nullptr, nullptr) == D3DERR_DEVICEREMOVED)
			m_bDeviceLost = 1;
	}

	return 1;
}

void RenderDevice::SetLight()
{
	for (int i = 0; i < 2; i++)
	{
		if(FAILED(m_pd3dDevice->SetLight(i, &m_light[i])))
			return;

		if (FAILED(m_pd3dDevice->LightEnable(i, 1)))
			return;
	}
}

void RenderDevice::SetWindowedFullScreen()
{
	HDC hDC = CreateDCA("DISPLAY", 0, 0, nullptr);
	m_dwCurrScreenX = GetDeviceCaps(hDC, HORZRES);
	m_dwCurrScreenY = GetDeviceCaps(hDC, VERTRES);
	m_dwCurrBpp = GetDeviceCaps(hDC, BITSPIXEL);
	m_dwCurrRefreshRate = GetDeviceCaps(hDC, VREFRESH);

	DeleteDC(hDC);

	if (!ChangeDisplay(m_dwScreenWidth, m_dwScreenHeight, m_dwBitCount, RenderDevice::m_dwCurrRefreshRate))
		ChangeDisplay(m_dwScreenWidth, m_dwScreenHeight, m_dwBitCount, 0);
}

void RenderDevice::RestoreWindowMode()
{
	ChangeDisplay(RenderDevice::m_dwCurrScreenX,
		RenderDevice::m_dwCurrScreenY,
		RenderDevice::m_dwCurrBpp,
		RenderDevice::m_dwCurrRefreshRate);
}

int RenderDevice::ChangeDisplay(DWORD x, DWORD y, DWORD bpp, DWORD ref)
{
	DEVMODE mode;
	GetCurrentDisplayMode(&mode);

	mode.dmPelsWidth = x;
	mode.dmPelsHeight = y;
	mode.dmBitsPerPel = bpp;
	if (ref)
		mode.dmDisplayFrequency = ref;

	int lResult = ChangeDisplaySettings(&mode, 0);
	return lResult == 0 || lResult == 1;
}

HRESULT RenderDevice::GetCurrentDisplayMode(PDEVMODE devMode)
{
	HDC hDC = CreateDCA("DISPLAY", 0, 0, 0);
	int iOrgX = GetDeviceCaps(hDC, HORZRES);
	int iOrgY = GetDeviceCaps(hDC, VERTRES);
	int iOrgBpp = GetDeviceCaps(hDC, BITSPIXEL);
	GetDeviceCaps(hDC, VREFRESH);
	DeleteDC(hDC);

	int iModeNum = 0;
	for (int bResult = EnumDisplaySettings(0, 0, devMode); bResult; bResult = EnumDisplaySettings(0, iModeNum, devMode))
	{
		if (devMode->dmPelsWidth == iOrgX && devMode->dmPelsHeight == iOrgY && devMode->dmBitsPerPel == iOrgBpp)
			return 1;

		++iModeNum;
	}

	return 0;
}

HRESULT RenderDevice::ConfirmDevice(D3DCAPS9* pCaps, DWORD dwBehavior, D3DFORMAT Format)
{
	return (dwBehavior & 0x40) ? E_FAIL : 0;
}

HRESULT RenderDevice::RestoreDeviceObjects()
{
	D3DCAPS9 d3dCaps{};
	m_pd3dDevice->GetDeviceCaps(&d3dCaps);
	if (d3dCaps.PixelShaderVersion >= 0xFFFF0101)
	{
		m_bSupportPS11 = 1;
		m_nShadowTextureSize = 128;
	}
	else
	{
		m_bSupportPS11 = 0;
		m_nShadowTextureSize = 64;

		if (g_nReflection > 0)
			g_nReflection = 0;
		if (g_nUseBlur > 0)
			g_nUseBlur = 0;
	}

	m_bSupportPS12 = d3dCaps.PixelShaderVersion >= 0xFFFF0102;
	m_bSupportVS20 = d3dCaps.VertexShaderVersion >= 0xFFFE0200;

	SetViewPort(0, 0, m_dwScreenWidth, m_dwScreenHeight);

	for (int i = 0; i < 10; ++i)
		m_pd3dDevice->SetTexture(i, nullptr);

	if (m_pSprite == nullptr)
	{
		if (FAILED(D3DXCreateSprite(m_pd3dDevice, &m_pSprite)))
			return 0;
	}

	if (g_pApp->m_pObjectManager != nullptr)
		g_pApp->m_pObjectManager->RestoreDeviceObjects();

	if (m_hbmBitmap == nullptr)
	{
		memset(&m_bmi, 0, sizeof(m_bmi));
		m_bmi.bmiHeader.biSize = 40;
		m_bmi.bmiHeader.biWidth = RenderDevice::m_nFontTextureSize;
		m_bmi.bmiHeader.biHeight = -RenderDevice::m_nFontTextureSize;
		m_bmi.bmiHeader.biPlanes = 1;
		m_bmi.bmiHeader.biCompression = 0;
		m_bmi.bmiHeader.biBitCount = 32;
		m_hDC = CreateCompatibleDC(0);
		m_hbmBitmap = CreateDIBSection(m_hDC, &m_bmi, 0, (void**)&m_pBitmapBits, 0,	0);

		sprintf(g_szFontName, "Tahoma");
		FILE* fpFont = nullptr;
		fopen_s(&fpFont, "font.txt", "rt");

		if (fpFont != nullptr)
		{
			char szTemp[256]{};
			fgets(szTemp, 256, fpFont);
			sscanf(szTemp, "%s", g_szFontName);
			fgets(szTemp, 256, fpFont);
			sscanf(szTemp, "%d", &g_nFontBold);

			if (g_nFontBold <= 0)
				g_nFontBold = 500;

			fclose(fpFont);
		}

		m_hFont = CreateFont(RenderDevice::m_nFontSize, 0, 0, 0, g_nFontBold, 0, 0, 0, 1, 4, 0, 4, 2, g_szFontName);
		SelectObject(m_hDC, m_hbmBitmap);
		SelectObject(m_hDC, m_hFont);
		SetTextColor(m_hDC, (COLORREF)0xFFFFFF);
		SetBkColor(m_hDC, 0);
	}

	HRESULT hr = m_pd3dDevice->GetRenderTarget(0, &m_pOldRenderTarget);
	if (FAILED(hr))
		return hr;

	hr = m_pd3dDevice->GetDepthStencilSurface(&m_pOldDepthStencil);
	if (FAILED(hr))
		return hr;

	if (m_pDXFont != nullptr)
		m_pDXFont->OnResetDevice();
	if (m_pDXFontLarge != nullptr)
		m_pDXFontLarge->OnResetDevice();

	InitializeRenderingState();
	InitVertexShader();
	InitPixelShader();

	if (d3dCaps.MaxTextureWidth > 256)
	{
		TextureManager::DYNAMIC_TEXTURE_WIDTH = 512;
		TextureManager::DYNAMIC_TEXTURE_HEIGHT = 512;
	}

	return 0;
}

HRESULT RenderDevice::InvalidateDeviceObjects()
{
	if (m_pTextureManager != nullptr)
		m_pTextureManager->ReleaseTexture();
	if (m_pMeshManager != nullptr)
		m_pMeshManager->ReleaseMesh();
	if (g_pObjectManager != nullptr)
		g_pObjectManager->InvalidateDeviceObjects();

	for (int iInfl = 0; iInfl < 8; ++iInfl)
	{
		SAFE_RELEASE(m_pVertexShader[iInfl]);
		SAFE_RELEASE(m_pVertexDeclaration[iInfl]);
	}
	for (int i = 0; i < 4; ++i)
	{
		SAFE_RELEASE(m_pVSEffect[i]);
	}
	for (int ia = 0; ia < 6; ++ia)
	{
		SAFE_RELEASE(m_pPSEffect[ia]);
	}

	if (m_hbmBitmap != nullptr)
	{
		DeleteObject(m_hbmBitmap);
		DeleteDC(m_hDC);
		DeleteObject(m_hFont);
		m_hbmBitmap = nullptr;
		m_hDC = nullptr;
		m_hFont = nullptr;
	}
	
	SAFE_RELEASE(m_pOldRenderTarget);
	SAFE_RELEASE(m_pOldDepthStencil);

	if (m_pDXFont != nullptr)
		m_pDXFont->OnLostDevice();
	if (m_pDXFontLarge != nullptr)
		m_pDXFontLarge->OnLostDevice();
	
	SAFE_RELEASE(m_pSprite);

	return 0;
}

void RenderDevice::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	if (State >= 0 && State < 256 && m_dwRenderStateList[State] != Value)
	{
		m_dwRenderStateList[State] = Value;
		m_pd3dDevice->SetRenderState(State, Value);
	}
}

void RenderDevice::SetTextureStageState(DWORD dwStage, D3DTEXTURESTAGESTATETYPE type, DWORD Value)
{
	if (dwStage >= 8)
		return;

	if (type >= 0 && type < 29 && m_dwTextureStageStateList[dwStage][type] != Value)
	{
		m_dwTextureStageStateList[dwStage][type] = Value;
		m_pd3dDevice->SetTextureStageState(dwStage, type, Value);
	}
}

void RenderDevice::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
	if (Stage >= 8)
		return;

	if (m_pTexture[Stage] != pTexture)
	{
		m_pTexture[Stage] = pTexture;
		m_pd3dDevice->SetTexture(Stage, pTexture);
	}
}

void RenderDevice::SetSamplerState(DWORD dwStage, D3DSAMPLERSTATETYPE State, DWORD Value)
{
	if (dwStage >= 8)
		return;

	if (State >= 0 && State < 14 && m_dwSamplerStateList[dwStage][State] != Value)
	{
		m_dwSamplerStateList[dwStage][State] = Value;
		m_pd3dDevice->SetSamplerState(dwStage, State, Value);
	}
}

void RenderDevice::SetGamma()
{
	if (RenderDevice::m_nBright != 50)
	{
		static D3DGAMMARAMP gamma;
		memset(&gamma, 0, sizeof(gamma));

		m_pd3dDevice->GetGammaRamp(1, &gamma);

		for (int i = 0; i < 256; i++)
		{
			WORD nVal = (float)((float)(((float)RenderDevice::m_nBright * 0.02f) * (float)i) * 256.0f);
			if (nVal > -1)
				nVal = -1;

			gamma.red[i] = nVal;
			gamma.green[i] = nVal;
			gamma.blue[i] = nVal;
		}

		m_pd3dDevice->SetGammaRamp(0, 0, &gamma);

		if (m_d3dpp.Windowed)
		{
			HDC hdc = GetDC(g_pApp->m_hWnd);
			SetDeviceGammaRamp(hdc, &gamma);
			ReleaseDC(g_pApp->m_hWnd, hdc);
		}
	}
}

int RenderDevice::InitMeshManager()
{
	if (m_pMeshManager != nullptr)
		return 1;

	m_pMeshManager = new MeshManager();
	if (!m_pMeshManager->InitMeshManager())
	{
		LOG_WRITELOG("Initialize Mesh Manager Failed\r\n");
		return 0;
	}

	m_pMeshManager->RestoreDeviceObjects();
	m_bLoadMeshManager = 1;

	return 1;
}

int RenderDevice::InitVertexShader()
{
	D3DVERTEXELEMENT9 VertexDecl1[5];
	D3DVERTEXELEMENT9 VertexDecl2[5];
	D3DVERTEXELEMENT9 VertexDecl3[5];
	D3DVERTEXELEMENT9 VertexDecl4[5];

	VertexDecl1[0].Stream = 0;
	VertexDecl1[0].Offset = 0;
	VertexDecl1[0].Type = 2;
	VertexDecl1[0].Method = 0;
	VertexDecl1[0].Usage = 0;
	VertexDecl1[0].UsageIndex = 0;
	VertexDecl1[1].Stream = 0;
	VertexDecl1[1].Offset = 12;
	VertexDecl1[1].Type = 4;
	VertexDecl1[1].Method = 0;
	VertexDecl1[1].Usage = 2;
	VertexDecl1[1].UsageIndex = 0;
	VertexDecl1[2].Stream = 0;
	VertexDecl1[2].Offset = 16;
	VertexDecl1[2].Type = 2;
	VertexDecl1[2].Method = 0;
	VertexDecl1[2].Usage = 3;
	VertexDecl1[2].UsageIndex = 0;
	VertexDecl1[3].Stream = 0;
	VertexDecl1[3].Offset = 28;
	VertexDecl1[3].Type = 1;
	VertexDecl1[3].Method = 0;
	VertexDecl1[3].Usage = 5;
	VertexDecl1[3].UsageIndex = 0;
	VertexDecl1[4].Stream = 255;
	VertexDecl1[4].Offset = 0;
	VertexDecl1[4].Type = 17;
	VertexDecl1[4].Method = 0;
	VertexDecl1[4].Usage = 0;
	VertexDecl1[4].UsageIndex = 0;
	VertexDecl2[0].Stream = 0;
	VertexDecl2[0].Offset = 0;
	VertexDecl2[0].Type = 2;
	VertexDecl2[0].Method = 0;
	VertexDecl2[0].Usage = 0;
	VertexDecl2[0].UsageIndex = 0;
	VertexDecl2[1].Stream = 0;
	VertexDecl2[1].Offset = 12;
	VertexDecl2[1].Type = 0;
	VertexDecl2[1].Method = 0;
	VertexDecl2[1].Usage = 1;
	VertexDecl2[1].UsageIndex = 0;
	VertexDecl2[2].Stream = 0;
	VertexDecl2[2].Offset = 16;
	VertexDecl2[2].Type = 4;
	VertexDecl2[2].Method = 0;
	VertexDecl2[2].Usage = 2;
	VertexDecl2[2].UsageIndex = 0;
	VertexDecl2[3].Stream = 0;
	VertexDecl2[3].Offset = 20;
	VertexDecl2[3].Type = 2;
	VertexDecl2[3].Method = 0;
	VertexDecl2[3].Usage = 3;
	VertexDecl2[3].UsageIndex = 0;
	VertexDecl2[4].Stream = 0;
	VertexDecl2[4].Offset = 32;
	VertexDecl2[4].Type = 1;
	VertexDecl2[4].Method = 0;
	VertexDecl2[4].Usage = 5;
	VertexDecl2[4].UsageIndex = 0;
	VertexDecl2[5].Stream = 255;
	VertexDecl2[5].Offset = 0;
	VertexDecl2[5].Type = 17;
	VertexDecl2[5].Method = 0;
	VertexDecl2[5].Usage = 0;
	VertexDecl2[5].UsageIndex = 0;
	VertexDecl3[0].Stream = 0;
	VertexDecl3[0].Offset = 0;
	VertexDecl3[0].Type = 2;
	VertexDecl3[0].Method = 0;
	VertexDecl3[0].Usage = 0;
	VertexDecl3[0].UsageIndex = 0;
	VertexDecl3[1].Stream = 0;
	VertexDecl3[1].Offset = 12;
	VertexDecl3[1].Type = 1;
	VertexDecl3[1].Method = 0;
	VertexDecl3[1].Usage = 1;
	VertexDecl3[1].UsageIndex = 0;
	VertexDecl3[2].Stream = 0;
	VertexDecl3[2].Offset = 20;
	VertexDecl3[2].Type = 4;
	VertexDecl3[2].Method = 0;
	VertexDecl3[2].Usage = 2;
	VertexDecl3[2].UsageIndex = 0;
	VertexDecl3[3].Stream = 0;
	VertexDecl3[3].Offset = 24;
	VertexDecl3[3].Type = 2;
	VertexDecl3[3].Method = 0;
	VertexDecl3[3].Usage = 3;
	VertexDecl3[3].UsageIndex = 0;
	VertexDecl3[4].Stream = 0;
	VertexDecl3[4].Offset = 36;
	VertexDecl3[4].Type = 1;
	VertexDecl3[4].Method = 0;
	VertexDecl3[4].Usage = 5;
	VertexDecl3[4].UsageIndex = 0;
	VertexDecl3[5].Stream = 255;
	VertexDecl3[5].Offset = 0;
	VertexDecl3[5].Type = 17;
	VertexDecl3[5].Method = 0;
	VertexDecl3[5].Usage = 0;
	VertexDecl3[5].UsageIndex = 0;
	VertexDecl4[0].Stream = 0;
	VertexDecl4[0].Offset = 0;
	VertexDecl4[0].Type = 2;
	VertexDecl4[0].Method = 0;
	VertexDecl4[0].Usage = 0;
	VertexDecl4[0].UsageIndex = 0;
	VertexDecl4[1].Stream = 0;
	VertexDecl4[1].Offset = 12;
	VertexDecl4[1].Type = 2;
	VertexDecl4[1].Method = 0;
	VertexDecl4[1].Usage = 1;
	VertexDecl4[1].UsageIndex = 0;
	VertexDecl4[2].Stream = 0;
	VertexDecl4[2].Offset = 24;
	VertexDecl4[2].Type = 4;
	VertexDecl4[2].Method = 0;
	VertexDecl4[2].Usage = 2;
	VertexDecl4[2].UsageIndex = 0;
	VertexDecl4[3].Stream = 0;
	VertexDecl4[3].Offset = 28;
	VertexDecl4[3].Type = 2;
	VertexDecl4[3].Method = 0;
	VertexDecl4[3].Usage = 3;
	VertexDecl4[3].UsageIndex = 0;
	VertexDecl4[4].Stream = 0;
	VertexDecl4[4].Offset = 40;
	VertexDecl4[4].Type = 1;
	VertexDecl4[4].Method = 0;
	VertexDecl4[4].Usage = 5;
	VertexDecl4[4].UsageIndex = 0;
	VertexDecl4[5].Stream = 255;
	VertexDecl4[5].Offset = 0;
	VertexDecl4[5].Type = 17;
	VertexDecl4[5].Method = 0;
	VertexDecl4[5].Usage = 0;
	VertexDecl4[5].UsageIndex = 0;

	LPD3DVERTEXELEMENT9 VertexDecl[4];
	VertexDecl[0] = VertexDecl1;
	VertexDecl[1] = VertexDecl2;
	VertexDecl[2] = VertexDecl3;
	VertexDecl[3] = VertexDecl4;

	m_bUseSW = 16;
	D3DCAPS9 d3dCaps{};
	m_pd3dDevice->GetDeviceCaps(&d3dCaps);

	if (d3dCaps.VertexShaderVersion >= 0xFFFE0101)
	{
		m_bUseSW = 0;
		m_dwBufferUsage = 8;
		if (m_pVertexShader[0] == nullptr)
			LOG_WRITELOG("VertexShader HW Accel Enabled\r\n");
	}
	else if (m_pVertexShader[0] == nullptr)
	{
		LOG_WRITELOG("VertexShader SW Mode \r\n");
	}

	if (m_pVertexShader[0] == nullptr)
	{
		for (int i = 0; i < 8; ++i)
		{
			LPD3DXBUFFER pCode = nullptr;
			char szBinFile[128];
			sprintf(szBinFile, "Shader\\skinmesh%d.bin", i + 1);

			int handle = _open(szBinFile, _O_BINARY);
			if (handle == -1)
			{
				LOG_WRITELOG("Read VertexShader %d Error.. \r\n", i + 1);
				return 0;
			}

			int nLength = _filelength(handle);
			D3DXCreateBuffer(nLength, &pCode);
			_read(handle, pCode->GetBufferPointer(), pCode->GetBufferSize());

			if (FAILED(m_pd3dDevice->CreateVertexDeclaration(VertexDecl[i % 4], &m_pVertexDeclaration[i])))
				return 0;

			if (FAILED(m_pd3dDevice->CreateVertexShader((const DWORD*)pCode->GetBufferPointer(), &m_pVertexShader[i])))
				return 0;

			pCode->Release();
		}

		D3DXMATRIX mat;
		D3DXMatrixTranspose(&mat, &m_matProj);
		m_pd3dDevice->SetVertexShaderConstantF(2, (const float*)&mat, 4);
	}

	D3DVERTEXELEMENT9 DeclWater[4];
	DeclWater[0].Stream = 0;
	DeclWater[0].Offset = 0;
	DeclWater[0].Type = 2;
	DeclWater[0].Method = 0;
	DeclWater[0].Usage = 0;
	DeclWater[0].UsageIndex = 0;
	DeclWater[1].Stream = 0;
	DeclWater[1].Offset = 12;
	DeclWater[1].Type = 4;
	DeclWater[1].Method = 0;
	DeclWater[1].Usage = 10;
	DeclWater[1].UsageIndex = 0;
	DeclWater[2].Stream = 0;
	DeclWater[2].Offset = 16;
	DeclWater[2].Type = 1;
	DeclWater[2].Method = 0;
	DeclWater[2].Usage = 5;
	DeclWater[2].UsageIndex = 0;
	DeclWater[3].Stream = 255;
	DeclWater[3].Offset = 0;
	DeclWater[3].Type = 17;
	DeclWater[3].Method = 0;
	DeclWater[3].Usage = 0;
	DeclWater[3].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclEquip[4];
	DeclEquip[0].Stream = 0;
	DeclEquip[0].Offset = 0;
	DeclEquip[0].Type = 2;
	DeclEquip[0].Method = 0;
	DeclEquip[0].Usage = 0;
	DeclEquip[0].UsageIndex = 0;
	DeclEquip[1].Stream = 0;
	DeclEquip[1].Offset = 12;
	DeclEquip[1].Type = 2;
	DeclEquip[1].Method = 0;
	DeclEquip[1].Usage = 3;
	DeclEquip[1].UsageIndex = 0;
	DeclEquip[2].Stream = 0;
	DeclEquip[2].Offset = 24;
	DeclEquip[2].Type = 1;
	DeclEquip[2].Method = 0;
	DeclEquip[2].Usage = 5;
	DeclEquip[2].UsageIndex = 0;
	DeclEquip[3].Stream = 255;
	DeclEquip[3].Offset = 0;
	DeclEquip[3].Type = 17;
	DeclEquip[3].Method = 0;
	DeclEquip[3].Usage = 0;
	DeclEquip[3].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclEquipShadow[2];
	DeclEquipShadow[0].Stream = 0;
	DeclEquipShadow[0].Offset = 0;
	DeclEquipShadow[0].Type = 2;
	DeclEquipShadow[0].Method = 0;
	DeclEquipShadow[0].Usage = 0;
	DeclEquipShadow[0].UsageIndex = 0;
	DeclEquipShadow[1].Stream = 255;
	DeclEquipShadow[1].Offset = 0;
	DeclEquipShadow[1].Type = 17;
	DeclEquipShadow[1].Method = 0;
	DeclEquipShadow[1].Usage = 0;
	DeclEquipShadow[1].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclBlur[3];
	DeclBlur[0].Stream = 0;
	DeclBlur[0].Offset = 0;
	DeclBlur[0].Type = 2;
	DeclBlur[0].Method = 0;
	DeclBlur[0].Usage = 0;
	DeclBlur[0].UsageIndex = 0;
	DeclBlur[1].Stream = 0;
	DeclBlur[1].Offset = 12;
	DeclBlur[1].Type = 1;
	DeclBlur[1].Method = 0;
	DeclBlur[1].Usage = 5;
	DeclBlur[1].UsageIndex = 0;
	DeclBlur[2].Stream = 255;
	DeclBlur[2].Offset = 0;
	DeclBlur[2].Type = 17;
	DeclBlur[2].Method = 0;
	DeclBlur[2].Usage = 0;
	DeclBlur[2].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclMesh[4];
	DeclMesh[0].Stream = 0;
	DeclMesh[0].Offset = 0;
	DeclMesh[0].Type = 2;
	DeclMesh[0].Method = 0;
	DeclMesh[0].Usage = 0;
	DeclMesh[0].UsageIndex = 0;
	DeclMesh[1].Stream = 0;
	DeclMesh[1].Offset = 12;
	DeclMesh[1].Type = 4;
	DeclMesh[1].Method = 0;
	DeclMesh[1].Usage = 10;
	DeclMesh[1].UsageIndex = 0;
	DeclMesh[2].Stream = 0;
	DeclMesh[2].Offset = 16;
	DeclMesh[2].Type = 1;
	DeclMesh[2].Method = 0;
	DeclMesh[2].Usage = 5;
	DeclMesh[2].UsageIndex = 0;
	DeclMesh[3].Stream = 255;
	DeclMesh[3].Offset = 0;
	DeclMesh[3].Type = 17;
	DeclMesh[3].Method = 0;
	DeclMesh[3].Usage = 0;
	DeclMesh[3].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclSwing[6];
	DeclSwing[0].Stream = 0;
	DeclSwing[0].Offset = 0;
	DeclSwing[0].Type = 2;
	DeclSwing[0].Method = 0;
	DeclSwing[0].Usage = 0;
	DeclSwing[0].UsageIndex = 0;
	DeclSwing[1].Stream = 0;
	DeclSwing[1].Offset = 12;
	DeclSwing[1].Type = 4;
	DeclSwing[1].Method = 0;
	DeclSwing[1].Usage = 10;
	DeclSwing[1].UsageIndex = 0;
	DeclSwing[2].Stream = 0;
	DeclSwing[2].Offset = 16;
	DeclSwing[2].Type = 1;
	DeclSwing[2].Method = 0;
	DeclSwing[2].Usage = 5;
	DeclSwing[2].UsageIndex = 0;
	DeclSwing[3].Stream = 0;
	DeclSwing[3].Offset = 24;
	DeclSwing[3].Type = 1;
	DeclSwing[3].Method = 0;
	DeclSwing[3].Usage = 5;
	DeclSwing[3].UsageIndex = 1;
	DeclSwing[4].Stream = 0;
	DeclSwing[4].Offset = 32;
	DeclSwing[4].Type = 1;
	DeclSwing[4].Method = 0;
	DeclSwing[4].Usage = 5;
	DeclSwing[4].UsageIndex = 2;
	DeclSwing[5].Stream = 255;
	DeclSwing[5].Offset = 0;
	DeclSwing[5].Type = 17;
	DeclSwing[5].Method = 0;
	DeclSwing[5].Usage = 0;
	DeclSwing[5].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclEfMesh[3];
	DeclEfMesh[0].Stream = 0;
	DeclEfMesh[0].Offset = 0;
	DeclEfMesh[0].Type = 2;
	DeclEfMesh[0].Method = 0;
	DeclEfMesh[0].Usage = 0;
	DeclEfMesh[0].UsageIndex = 0;
	DeclEfMesh[1].Stream = 0;
	DeclEfMesh[1].Offset = 12;
	DeclEfMesh[1].Type = 1;
	DeclEfMesh[1].Method = 0;
	DeclEfMesh[1].Usage = 5;
	DeclEfMesh[1].UsageIndex = 0;
	DeclEfMesh[2].Stream = 255;
	DeclEfMesh[2].Offset = 0;
	DeclEfMesh[2].Type = 17;
	DeclEfMesh[2].Method = 0;
	DeclEfMesh[2].Usage = 0;
	DeclEfMesh[2].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclBumpEquip[5];
	DeclBumpEquip[0].Stream = 0;
	DeclBumpEquip[0].Offset = 0;
	DeclBumpEquip[0].Type = 2;
	DeclBumpEquip[0].Method = 0;
	DeclBumpEquip[0].Usage = 0;
	DeclBumpEquip[0].UsageIndex = 0;
	DeclBumpEquip[1].Stream = 0;
	DeclBumpEquip[1].Offset = 12;
	DeclBumpEquip[1].Type = 2;
	DeclBumpEquip[1].Method = 0;
	DeclBumpEquip[1].Usage = 3;
	DeclBumpEquip[1].UsageIndex = 0;
	DeclBumpEquip[2].Stream = 0;
	DeclBumpEquip[2].Offset = 24;
	DeclBumpEquip[2].Type = 1;
	DeclBumpEquip[2].Method = 0;
	DeclBumpEquip[2].Usage = 5;
	DeclBumpEquip[2].UsageIndex = 0;
	DeclBumpEquip[3].Stream = 0;
	DeclBumpEquip[3].Offset = 32;
	DeclBumpEquip[3].Type = 2;
	DeclBumpEquip[3].Method = 0;
	DeclBumpEquip[3].Usage = 6;
	DeclBumpEquip[3].UsageIndex = 0;
	DeclBumpEquip[4].Stream = 255;
	DeclBumpEquip[4].Offset = 0;
	DeclBumpEquip[4].Type = 17;
	DeclBumpEquip[4].Method = 0;
	DeclBumpEquip[4].Usage = 0;
	DeclBumpEquip[4].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclEnvMesh[4];
	DeclEnvMesh[0].Stream = 0;
	DeclEnvMesh[0].Offset = 0;
	DeclEnvMesh[0].Type = 2;
	DeclEnvMesh[0].Method = 0;
	DeclEnvMesh[0].Usage = 0;
	DeclEnvMesh[0].UsageIndex = 0;
	DeclEnvMesh[1].Stream = 0;
	DeclEnvMesh[1].Offset = 12;
	DeclEnvMesh[1].Type = 2;
	DeclEnvMesh[1].Method = 0;
	DeclEnvMesh[1].Usage = 3;
	DeclEnvMesh[1].UsageIndex = 0;
	DeclEnvMesh[2].Stream = 0;
	DeclEnvMesh[2].Offset = 24;
	DeclEnvMesh[2].Type = 1;
	DeclEnvMesh[2].Method = 0;
	DeclEnvMesh[2].Usage = 5;
	DeclEnvMesh[2].UsageIndex = 0;
	DeclEnvMesh[3].Stream = 255;
	DeclEnvMesh[3].Offset = 0;
	DeclEnvMesh[3].Type = 17;
	DeclEnvMesh[3].Method = 0;
	DeclEnvMesh[3].Usage = 0;
	DeclEnvMesh[3].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclBumpMesh[4];
	DeclBumpMesh[0].Stream = 0;
	DeclBumpMesh[0].Offset = 0;
	DeclBumpMesh[0].Type = 2;
	DeclBumpMesh[0].Method = 0;
	DeclBumpMesh[0].Usage = 0;
	DeclBumpMesh[0].UsageIndex = 0;
	DeclBumpMesh[1].Stream = 0;
	DeclBumpMesh[1].Offset = 12;
	DeclBumpMesh[1].Type = 2;
	DeclBumpMesh[1].Method = 0;
	DeclBumpMesh[1].Usage = 3;
	DeclBumpMesh[1].UsageIndex = 0;
	DeclBumpMesh[2].Stream = 0;
	DeclBumpMesh[2].Offset = 24;
	DeclBumpMesh[2].Type = 1;
	DeclBumpMesh[2].Method = 0;
	DeclBumpMesh[2].Usage = 5;
	DeclBumpMesh[2].UsageIndex = 0;
	DeclBumpMesh[3].Stream = 255;
	DeclBumpMesh[3].Offset = 0;
	DeclBumpMesh[3].Type = 17;
	DeclBumpMesh[3].Method = 0;
	DeclBumpMesh[3].Usage = 0;
	DeclBumpMesh[3].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclUV2Mesh[4];
	DeclUV2Mesh[0].Stream = 0;
	DeclUV2Mesh[0].Offset = 0;
	DeclUV2Mesh[0].Type = 2;
	DeclUV2Mesh[0].Method = 0;
	DeclUV2Mesh[0].Usage = 0;
	DeclUV2Mesh[0].UsageIndex = 0;
	DeclUV2Mesh[1].Stream = 0;
	DeclUV2Mesh[1].Offset = 12;
	DeclUV2Mesh[1].Type = 1;
	DeclUV2Mesh[1].Method = 0;
	DeclUV2Mesh[1].Usage = 5;
	DeclUV2Mesh[1].UsageIndex = 0;
	DeclUV2Mesh[2].Stream = 0;
	DeclUV2Mesh[2].Offset = 20;
	DeclUV2Mesh[2].Type = 1;
	DeclUV2Mesh[2].Method = 0;
	DeclUV2Mesh[2].Usage = 5;
	DeclUV2Mesh[2].UsageIndex = 1;
	DeclUV2Mesh[3].Stream = 255;
	DeclUV2Mesh[3].Offset = 0;
	DeclUV2Mesh[3].Type = 17;
	DeclUV2Mesh[3].Method = 0;
	DeclUV2Mesh[3].Usage = 0;
	DeclUV2Mesh[3].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclWaterFallMesh[5];
	DeclWaterFallMesh[0].Stream = 0;
	DeclWaterFallMesh[0].Offset = 0;
	DeclWaterFallMesh[0].Type = 2;
	DeclWaterFallMesh[0].Method = 0;
	DeclWaterFallMesh[0].Usage = 0;
	DeclWaterFallMesh[0].UsageIndex = 0;
	DeclWaterFallMesh[1].Stream = 0;
	DeclWaterFallMesh[1].Offset = 12;
	DeclWaterFallMesh[1].Type = 2;
	DeclWaterFallMesh[1].Method = 0;
	DeclWaterFallMesh[1].Usage = 3;
	DeclWaterFallMesh[1].UsageIndex = 0;
	DeclWaterFallMesh[2].Stream = 0;
	DeclWaterFallMesh[2].Offset = 24;
	DeclWaterFallMesh[2].Type = 4;
	DeclWaterFallMesh[2].Method = 0;
	DeclWaterFallMesh[2].Usage = 10;
	DeclWaterFallMesh[2].UsageIndex = 0;
	DeclWaterFallMesh[3].Stream = 0;
	DeclWaterFallMesh[3].Offset = 28;
	DeclWaterFallMesh[3].Type = 1;
	DeclWaterFallMesh[3].Method = 0;
	DeclWaterFallMesh[3].Usage = 5;
	DeclWaterFallMesh[3].UsageIndex = 0;
	DeclWaterFallMesh[4].Stream = 255;
	DeclWaterFallMesh[4].Offset = 0;
	DeclWaterFallMesh[4].Type = 17;
	DeclWaterFallMesh[4].Method = 0;
	DeclWaterFallMesh[4].Usage = 0;
	DeclWaterFallMesh[4].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclLODMesh[3];
	DeclLODMesh[0].Stream = 0;
	DeclLODMesh[0].Offset = 0;
	DeclLODMesh[0].Type = 2;
	DeclLODMesh[0].Method = 0;
	DeclLODMesh[0].Usage = 0;
	DeclLODMesh[0].UsageIndex = 0;
	DeclLODMesh[1].Stream = 0;
	DeclLODMesh[1].Offset = 12;
	DeclLODMesh[1].Type = 1;
	DeclLODMesh[1].Method = 0;
	DeclLODMesh[1].Usage = 5;
	DeclLODMesh[1].UsageIndex = 0;
	DeclLODMesh[2].Stream = 255;
	DeclLODMesh[2].Offset = 0;
	DeclLODMesh[2].Type = 17;
	DeclLODMesh[2].Method = 0;
	DeclLODMesh[2].Usage = 0;
	DeclLODMesh[2].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclNormalMesh[4];
	DeclNormalMesh[0].Stream = 0;
	DeclNormalMesh[0].Offset = 0;
	DeclNormalMesh[0].Type = 2;
	DeclNormalMesh[0].Method = 0;
	DeclNormalMesh[0].Usage = 0;
	DeclNormalMesh[0].UsageIndex = 0;
	DeclNormalMesh[1].Stream = 0;
	DeclNormalMesh[1].Offset = 12;
	DeclNormalMesh[1].Type = 2;
	DeclNormalMesh[1].Method = 0;
	DeclNormalMesh[1].Usage = 3;
	DeclNormalMesh[1].UsageIndex = 0;
	DeclNormalMesh[2].Stream = 0;
	DeclNormalMesh[2].Offset = 24;
	DeclNormalMesh[2].Type = 1;
	DeclNormalMesh[2].Method = 0;
	DeclNormalMesh[2].Usage = 5;
	DeclNormalMesh[2].UsageIndex = 0;
	DeclNormalMesh[3].Stream = 255;
	DeclNormalMesh[3].Offset = 0;
	DeclNormalMesh[3].Type = 17;
	DeclNormalMesh[3].Method = 0;
	DeclNormalMesh[3].Usage = 0;
	DeclNormalMesh[3].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclSpecNormalMesh[4];
	DeclSpecNormalMesh[0].Stream = 0;
	DeclSpecNormalMesh[0].Offset = 0;
	DeclSpecNormalMesh[0].Type = 2;
	DeclSpecNormalMesh[0].Method = 0;
	DeclSpecNormalMesh[0].Usage = 0;
	DeclSpecNormalMesh[0].UsageIndex = 0;
	DeclSpecNormalMesh[1].Stream = 0;
	DeclSpecNormalMesh[1].Offset = 12;
	DeclSpecNormalMesh[1].Type = 2;
	DeclSpecNormalMesh[1].Method = 0;
	DeclSpecNormalMesh[1].Usage = 3;
	DeclSpecNormalMesh[1].UsageIndex = 0;
	DeclSpecNormalMesh[2].Stream = 0;
	DeclSpecNormalMesh[2].Offset = 24;
	DeclSpecNormalMesh[2].Type = 1;
	DeclSpecNormalMesh[2].Method = 0;
	DeclSpecNormalMesh[2].Usage = 5;
	DeclSpecNormalMesh[2].UsageIndex = 0;
	DeclSpecNormalMesh[3].Stream = 255;
	DeclSpecNormalMesh[3].Offset = 0;
	DeclSpecNormalMesh[3].Type = 17;
	DeclSpecNormalMesh[3].Method = 0;
	DeclSpecNormalMesh[3].Usage = 0;
	DeclSpecNormalMesh[3].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclSpecWaterFall2Mesh[5];
	DeclSpecWaterFall2Mesh[0].Stream = 0;
	DeclSpecWaterFall2Mesh[0].Offset = 0;
	DeclSpecWaterFall2Mesh[0].Type = 2;
	DeclSpecWaterFall2Mesh[0].Method = 0;
	DeclSpecWaterFall2Mesh[0].Usage = 0;
	DeclSpecWaterFall2Mesh[0].UsageIndex = 0;
	DeclSpecWaterFall2Mesh[1].Stream = 0;
	DeclSpecWaterFall2Mesh[1].Offset = 12;
	DeclSpecWaterFall2Mesh[1].Type = 4;
	DeclSpecWaterFall2Mesh[1].Method = 0;
	DeclSpecWaterFall2Mesh[1].Usage = 10;
	DeclSpecWaterFall2Mesh[1].UsageIndex = 0;
	DeclSpecWaterFall2Mesh[2].Stream = 0;
	DeclSpecWaterFall2Mesh[2].Offset = 16;
	DeclSpecWaterFall2Mesh[2].Type = 1;
	DeclSpecWaterFall2Mesh[2].Method = 0;
	DeclSpecWaterFall2Mesh[2].Usage = 5;
	DeclSpecWaterFall2Mesh[2].UsageIndex = 0;
	DeclSpecWaterFall2Mesh[3].Stream = 0;
	DeclSpecWaterFall2Mesh[3].Offset = 24;
	DeclSpecWaterFall2Mesh[3].Type = 1;
	DeclSpecWaterFall2Mesh[3].Method = 0;
	DeclSpecWaterFall2Mesh[3].Usage = 5;
	DeclSpecWaterFall2Mesh[3].UsageIndex = 1;
	DeclSpecWaterFall2Mesh[4].Stream = 255;
	DeclSpecWaterFall2Mesh[4].Offset = 0;
	DeclSpecWaterFall2Mesh[4].Type = 17;
	DeclSpecWaterFall2Mesh[4].Method = 0;
	DeclSpecWaterFall2Mesh[4].Usage = 0;
	DeclSpecWaterFall2Mesh[4].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclSpecWater[5];
	DeclSpecWater[0].Stream = 0;
	DeclSpecWater[0].Offset = 0;
	DeclSpecWater[0].Type = 2;
	DeclSpecWater[0].Method = 0;
	DeclSpecWater[0].Usage = 0;
	DeclSpecWater[0].UsageIndex = 0;
	DeclSpecWater[1].Stream = 0;
	DeclSpecWater[1].Offset = 12;
	DeclSpecWater[1].Type = 2;
	DeclSpecWater[1].Method = 0;
	DeclSpecWater[1].Usage = 3;
	DeclSpecWater[1].UsageIndex = 0;
	DeclSpecWater[2].Stream = 0;
	DeclSpecWater[2].Offset = 24;
	DeclSpecWater[2].Type = 1;
	DeclSpecWater[2].Method = 0;
	DeclSpecWater[2].Usage = 5;
	DeclSpecWater[2].UsageIndex = 0;
	DeclSpecWater[3].Stream = 0;
	DeclSpecWater[3].Offset = 32;
	DeclSpecWater[3].Type = 1;
	DeclSpecWater[3].Method = 0;
	DeclSpecWater[3].Usage = 5;
	DeclSpecWater[3].UsageIndex = 1;
	DeclSpecWater[4].Stream = 255;
	DeclSpecWater[4].Offset = 0;
	DeclSpecWater[4].Type = 17;
	DeclSpecWater[4].Method = 0;
	DeclSpecWater[4].Usage = 0;
	DeclSpecWater[4].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclChannel2Alpha[4];
	DeclChannel2Alpha[0].Stream = 0;
	DeclChannel2Alpha[0].Offset = 0;
	DeclChannel2Alpha[0].Type = 2;
	DeclChannel2Alpha[0].Method = 0;
	DeclChannel2Alpha[0].Usage = 0;
	DeclChannel2Alpha[0].UsageIndex = 0;
	DeclChannel2Alpha[1].Stream = 0;
	DeclChannel2Alpha[1].Offset = 12;
	DeclChannel2Alpha[1].Type = 1;
	DeclChannel2Alpha[1].Method = 0;
	DeclChannel2Alpha[1].Usage = 5;
	DeclChannel2Alpha[1].UsageIndex = 0;
	DeclChannel2Alpha[2].Stream = 0;
	DeclChannel2Alpha[2].Offset = 20;
	DeclChannel2Alpha[2].Type = 1;
	DeclChannel2Alpha[2].Method = 0;
	DeclChannel2Alpha[2].Usage = 5;
	DeclChannel2Alpha[2].UsageIndex = 1;
	DeclChannel2Alpha[3].Stream = 255;
	DeclChannel2Alpha[3].Offset = 0;
	DeclChannel2Alpha[3].Type = 17;
	DeclChannel2Alpha[3].Method = 0;
	DeclChannel2Alpha[3].Usage = 0;
	DeclChannel2Alpha[3].UsageIndex = 0;

	D3DVERTEXELEMENT9 DeclRefectWater[5];
	DeclRefectWater[0].Stream = 0;
	DeclRefectWater[0].Offset = 0;
	DeclRefectWater[0].Type = 2;
	DeclRefectWater[0].Method = 0;
	DeclRefectWater[0].Usage = 0;
	DeclRefectWater[0].UsageIndex = 0;
	DeclRefectWater[1].Stream = 0;
	DeclRefectWater[1].Offset = 12;
	DeclRefectWater[1].Type = 4;
	DeclRefectWater[1].Method = 0;
	DeclRefectWater[1].Usage = 10;
	DeclRefectWater[1].UsageIndex = 0;
	DeclRefectWater[2].Stream = 0;
	DeclRefectWater[2].Offset = 16;
	DeclRefectWater[2].Type = 1;
	DeclRefectWater[2].Method = 0;
	DeclRefectWater[2].Usage = 5;
	DeclRefectWater[2].UsageIndex = 0;
	DeclRefectWater[3].Stream = 0;
	DeclRefectWater[3].Offset = 24;
	DeclRefectWater[3].Type = 1;
	DeclRefectWater[3].Method = 0;
	DeclRefectWater[3].Usage = 5;
	DeclRefectWater[3].UsageIndex = 1;
	DeclRefectWater[4].Stream = 255;
	DeclRefectWater[4].Offset = 0;
	DeclRefectWater[4].Type = 17;
	DeclRefectWater[4].Method = 0;
	DeclRefectWater[4].Usage = 0;
	DeclRefectWater[4].UsageIndex = 0;

	LPD3DVERTEXELEMENT9 VertexDeclEff[19];
	VertexDeclEff[0] = DeclWater;
	VertexDeclEff[1] = DeclEquip;
	VertexDeclEff[2] = DeclEquipShadow;
	VertexDeclEff[3] = DeclBlur;
	VertexDeclEff[4] = DeclMesh;
	VertexDeclEff[5] = DeclSwing;
	VertexDeclEff[6] = DeclEfMesh;
	VertexDeclEff[7] = DeclBumpEquip;
	VertexDeclEff[8] = DeclEnvMesh;
	VertexDeclEff[9] = DeclBumpMesh;
	VertexDeclEff[10] = DeclUV2Mesh;
	VertexDeclEff[11] = DeclWaterFallMesh;
	VertexDeclEff[12] = DeclLODMesh;
	VertexDeclEff[13] = DeclNormalMesh;
	VertexDeclEff[14] = DeclSpecNormalMesh;
	VertexDeclEff[15] = DeclSpecWaterFall2Mesh;
	VertexDeclEff[16] = DeclSpecWater;
	VertexDeclEff[17] = DeclChannel2Alpha;
	VertexDeclEff[18] = DeclRefectWater;

	if (m_pVSEffect[0] == nullptr)
	{
		for (int j = 0; j < 4; ++j)
		{
			LPD3DXBUFFER pCode = nullptr;
			char szFileName[128];
			sprintf_s(szFileName, "Shader\\vseffect%d.bin", j + 1);

			int fh = _open(szFileName, _O_BINARY);
			if (fh == -1)
			{
				LOG_WRITELOG("Read VertexShader %d Error.. \r\n", j + 1);
				return 0;
			}

			int nLength = _filelength(fh);
			D3DXCreateBuffer(nLength, &pCode);
			_read(fh, pCode->GetBufferPointer(), pCode->GetBufferSize());


			if (FAILED(m_pd3dDevice->CreateVertexDeclaration(VertexDeclEff[j], &m_pVDEffect[j])))
				return 0;

			if (FAILED(m_pd3dDevice->CreateVertexShader((const DWORD*)pCode->GetBufferPointer(), &m_pVSEffect[j])))
				return 0;

			pCode->Release();
		}
	}

	return 1;
}

int RenderDevice::InitPixelShader()
{
	D3DCAPS9 d3dCaps{};
	m_pd3dDevice->GetDeviceCaps(&d3dCaps);
	if (d3dCaps.PixelShaderVersion >= 0xFFFF0101)
	{
		if (m_pPSEffect[0] == nullptr)
		{
			for (int i = 0; i < 6; ++i)
			{
				LPD3DXBUFFER pCode = nullptr;
				char szBinFile[128];
				sprintf_s(szBinFile, "Shader\\pseffect%d.bin", i + 1);

				int handle = _open(szBinFile, _O_BINARY);
				if (handle == -1)
				{
					LOG_WRITELOG("Read PixelShader %d Error.. \r\n", i + 1);
					return 0;
				}

				int nLength = _filelength(handle);
				D3DXCreateBuffer(nLength, &pCode);
				_read(handle, pCode->GetBufferPointer(), pCode->GetBufferSize());

				if (FAILED(m_pd3dDevice->CreatePixelShader((const DWORD*)pCode->GetBufferPointer(), &m_pPSEffect[i])))
					return 0;

				pCode->Release();
			}
		}

		return 1;
	}
	else
	{
		m_bSupportPS11 = 0;
		m_nShadowTextureSize = 64;
		return 1;
	}

	return 1;
}

int RenderDevice::InitializeRenderingState()
{
	D3DXMatrixIdentity(&m_matWorld);
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

	memset(m_dwRenderStateList, 0, sizeof(m_dwRenderStateList));

	for (int nState = 0; nState < 256; ++nState)
	{
		m_dwRenderStateList[nState] = -1;
	}

	for (int nStage = 0; nStage < 8; ++nStage)
	{
		for (int i = 0; i < 14; ++i)
		{
			m_dwSamplerStateList[nStage][i] = -1;
		}
	}

	for (int nStage = 0; nStage < 8; ++nStage)
	{
		for (int j = 0; j < 29; ++j)
			m_dwTextureStageStateList[nStage][j] = -1;
	}

	return 1;
}

int RenderDevice::SetRenderStateBlock(int nIndex)
{
	if (nIndex == 0)
	{
		SetRenderState(D3DRS_ZENABLE, 1u);
		SetRenderState(D3DRS_FOGENABLE, 0);
		SetRenderState(D3DRS_LIGHTING, 0);
		SetRenderState(D3DRS_SPECULARENABLE, 1u);
		SetRenderState(D3DRS_CULLMODE, 3u);
		SetRenderState(D3DRS_SHADEMODE, 2u);
		SetRenderState(D3DRS_AMBIENT, 0x0AAAAAA);
		SetRenderState(D3DRS_SRCBLEND, 5u);
		SetRenderState(D3DRS_DESTBLEND, 7u);
		SetRenderState(D3DRS_COLORVERTEX, 1u);
		SetRenderState(D3DRS_DITHERENABLE, 1u);
		SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
		SetTextureStageState(0, D3DTSS_COLOROP, 2u);
		SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
		SetTextureStageState(0, D3DTSS_COLORARG2, 1u);
		SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
		SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
		SetTextureStageState(0, D3DTSS_ALPHAARG2, 1u);
		SetSamplerState(0, D3DSAMP_MINFILTER, 2u);
		SetSamplerState(0, D3DSAMP_MAGFILTER, 2u);
		SetSamplerState(0, D3DSAMP_MIPFILTER, 1u);
		SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		m_pd3dDevice->SetFVF(322);
	}
	else if (nIndex == 1)
	{
		m_light[0].Diffuse = m_colorLight;
		m_light[0].Specular = m_colorLight;
		m_light[1].Diffuse = m_colorBackLight;
		m_light[1].Specular = m_colorBackLight;

		if (g_pCurrentScene != nullptr && g_pCurrentScene->GetSceneType() == ESCENE_TYPE::ESCENE_FIELD)
		{
			if (static_cast<TMFieldScene*>(g_pCurrentScene)->m_bShowBoss == 1)
			{
				m_light[0].Diffuse.a = 0.0;
				m_light[0].Diffuse.b = 0.0;
				m_light[0].Diffuse.g = 0.0;
				m_light[0].Diffuse.r = 0.0;
				m_light[0].Specular.a = 0.0;
				m_light[0].Specular.b = 0.0;
				m_light[0].Specular.g = 0.0;
				m_light[0].Specular.r = 0.0;
			}
			static_cast<TMFieldScene*>(g_pCurrentScene)->m_bShowBoss = 0;
		}

		m_light[1].Diffuse = m_colorBackLight;
		m_light[1].Specular = m_colorBackLight;
		m_light[0].Direction = D3DXVECTOR3(1.0f, -1.0f, -1.0f);
		m_light[1].Direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

		for (int i = 0; i < 2; ++i)
		{
			if (FAILED(m_pd3dDevice->SetLight(i, &m_light[i])))
				return 0;

			if (FAILED(m_pd3dDevice->LightEnable(i, 1)))
				return 0;
		}

		D3DXVECTOR4 vLightDir;
		TMCamera* pCamera = g_pObjectManager->m_pCamera;

		if (RenderDevice::m_bDungeon != 0 && RenderDevice::m_bDungeon != 4)
		{
			vLightDir = D3DXVECTOR4(
				pCamera->m_vecCamDir.x - m_light[0].Direction.x, 
				0.5f, 
				(pCamera->m_vecCamDir.z + m_light[0].Direction.z) - 0.3f, 
				0.0f);
		}
		else
		{
			vLightDir = D3DXVECTOR4(
				m_light[0].Direction.x,
				0.5f,
				m_light[0].Direction.z,
				0.0f);
		}

		m_pd3dDevice->SetVertexShaderConstantF(1, (const float*)&vLightDir, 1);

		if (g_pDevice->m_iVGAID == 1)
		{
			if (g_pDevice->m_dwBitCount == 32)
				SetRenderState(D3DRS_ALPHAREF, 0xFF000000);
			else
				SetRenderState(D3DRS_ALPHAREF, 0xF000);
		}
		else if (g_pDevice->m_dwBitCount == 32)
		{
			SetRenderState(D3DRS_ALPHAREF, 0xDD);
		}
		else
		{
			SetRenderState(D3DRS_ALPHAREF, 0xD);
		}

		SetRenderState(D3DRS_ALPHABLENDENABLE, 1);
		SetRenderState(D3DRS_ALPHATESTENABLE, 1);
		SetRenderState(D3DRS_ALPHAFUNC, 7);
		SetRenderState(D3DRS_AMBIENT, 0x33FFFFFFu);
		SetRenderState(D3DRS_ZENABLE, 1);
		SetRenderState(D3DRS_ZFUNC, 4);
		SetRenderState(D3DRS_ZWRITEENABLE, 1);
		SetRenderState(D3DRS_LIGHTING, 1);
		SetRenderState(D3DRS_SPECULARENABLE, 0);
		SetRenderState(D3DRS_CULLMODE, 3);
		SetRenderState(D3DRS_SHADEMODE, 2);
		SetRenderState(D3DRS_COLORVERTEX, 1);
		SetRenderState(D3DRS_NORMALIZENORMALS, 1);
		SetRenderState(D3DRS_DITHERENABLE, 1);
		SetRenderState(D3DRS_SRCBLEND, 2);
		SetRenderState(D3DRS_DESTBLEND, 6);
		SetRenderState(D3DRS_FOGENABLE, m_bFog);
		SetRenderState(D3DRS_RANGEFOGENABLE, 0);

		m_dwActualClearColor = m_dwClearColor;
		float fstart = (float)(m_fFogStart + g_pApp->m_pObjectManager->m_pCamera->m_fSightLength) - 8.0f;
		float fend = (float)(m_fFogEnd + g_pApp->m_pObjectManager->m_pCamera->m_fSightLength) - 15.0f;

		SetRenderState(D3DRS_FOGCOLOR, m_dwClearColor);
		SetRenderState(D3DRS_FOGVERTEXMODE, 3);
		SetRenderState(D3DRS_FOGSTART, fstart);
		SetRenderState(D3DRS_FOGEND, fend);
		SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, 1);
		SetRenderState(D3DRS_SPECULARMATERIALSOURCE, 2);
		SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, 1);
		SetRenderState(D3DRS_SPECULARMATERIALSOURCE, 1);
		SetTextureStageState(0, D3DTSS_COLOROP, 4u);
		SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
		SetTextureStageState(0, D3DTSS_COLORARG2, 0);
		SetTextureStageState(0, D3DTSS_ALPHAOP, 2u);
		SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
		SetTextureStageState(0, D3DTSS_ALPHAARG2, 1u);
		SetSamplerState(0, D3DSAMP_MINFILTER, 2u);
		SetSamplerState(0, D3DSAMP_MAGFILTER, 2u);
		SetSamplerState(0, D3DSAMP_MIPFILTER, 2u);
		SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
		SetTextureStageState(1u, D3DTSS_COLORARG1, 2u);
		SetTextureStageState(1u, D3DTSS_COLORARG2, 1u);
		SetTextureStageState(1u, D3DTSS_ALPHAOP, 2u);
		SetTextureStageState(1u, D3DTSS_ALPHAARG1, 2u);
		SetTextureStageState(1u, D3DTSS_ALPHAARG2, 1u);
		SetSamplerState(1u, D3DSAMP_MINFILTER, 2u);
		SetSamplerState(1u, D3DSAMP_MAGFILTER, 2u);
		SetSamplerState(1u, D3DSAMP_MIPFILTER, 0);
		SetTextureStageState(1u, D3DTSS_TEXCOORDINDEX, 1u);
		SetTextureStageState(2u, D3DTSS_COLOROP, 1u);
	}
	else if (nIndex == 2)
	{
		SetRenderState(D3DRS_ZENABLE, 0);
		SetRenderState(D3DRS_ALPHABLENDENABLE, 1u);
		SetRenderState(D3DRS_SRCBLEND, 5u);
		SetRenderState(D3DRS_DESTBLEND, 6u);
		SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
		SetRenderState(D3DRS_ALPHAREF, 8u);
		SetRenderState(D3DRS_ALPHAFUNC, 7u);
		SetRenderState(D3DRS_FILLMODE, 3u);
		SetRenderState(D3DRS_CULLMODE, 3u);
		SetRenderState(D3DRS_STENCILENABLE, 0);
		SetRenderState(D3DRS_CLIPPING, 1u);
		SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, 0);
		SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, 0);
		SetRenderState(D3DRS_VERTEXBLEND, 0);
		SetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, 0);
		SetRenderState(D3DRS_FOGENABLE, 0);
		SetTextureStageState(0, D3DTSS_COLOROP, 4u);
		SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
		SetTextureStageState(0, D3DTSS_COLORARG2, 0);
		SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
		SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
		SetTextureStageState(0, D3DTSS_ALPHAARG2, 0);
		SetSamplerState(0, D3DSAMP_MINFILTER, 1u);
		SetSamplerState(0, D3DSAMP_MAGFILTER, 1u);
		SetSamplerState(0, D3DSAMP_MIPFILTER, 1u);
		SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
		SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
		SetTextureStageState(1u, D3DTSS_ALPHAOP, 1u);
	}
	else if (nIndex == 3)
	{
		SetRenderState(D3DRS_ZENABLE, 0);
		SetRenderState(D3DRS_ALPHABLENDENABLE, 0);
		SetRenderState(D3DRS_SRCBLEND, 5u);
		SetRenderState(D3DRS_DESTBLEND, 6u);
		SetRenderState(D3DRS_ALPHATESTENABLE, 1u);
		SetRenderState(D3DRS_ALPHAREF, 8u);
		SetRenderState(D3DRS_ALPHAFUNC, 7u);
		SetRenderState(D3DRS_FILLMODE, 3u);
		SetRenderState(D3DRS_CULLMODE, 3u);
		SetRenderState(D3DRS_STENCILENABLE, 0);
		SetRenderState(D3DRS_CLIPPING, 1u);
		SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, 0);
		SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, 0);
		SetRenderState(D3DRS_VERTEXBLEND, 0);
		SetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, 0);
		SetRenderState(D3DRS_FOGENABLE, 0);
		SetTextureStageState(0, D3DTSS_COLOROP, 4u);
		SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
		SetTextureStageState(0, D3DTSS_COLORARG2, 0);
		SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
		SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
		SetTextureStageState(0, D3DTSS_ALPHAARG2, 0);
		SetSamplerState(0, D3DSAMP_MINFILTER, 2u);
		SetSamplerState(0, D3DSAMP_MAGFILTER, 2u);
		SetSamplerState(0, D3DSAMP_MIPFILTER, 2u);
		SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
		SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, 0);
		SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
		SetTextureStageState(1u, D3DTSS_ALPHAOP, 1u);
	}

	return 1;
}

int RenderDevice::SetViewVector(TMVector3 ivCamera, TMVector3 ivLookat)
{
	D3DXVECTOR3 upVector(0.0f, 1.0f, 0.0f);
	m_vCamera = D3DXVECTOR3(ivCamera.x, ivCamera.y, ivCamera.z);
	m_vLookatPos = D3DXVECTOR3(ivLookat.x, ivLookat.y, ivLookat.z);

	D3DXMatrixLookAtLH(&m_matView, &m_vCamera, &m_vLookatPos, &upVector);

	return SUCCEEDED(m_pd3dDevice->SetTransform(D3DTS_VIEW, &m_matView));
}

HRESULT RenderDevice::SetProjectionMatrix()
{
	D3DXMatrixPerspectiveFovLH(&m_matProj, RenderDevice::m_fFOVY * D3DXToRadian(180),
		(float)((float)(m_dwScreenWidth - m_nWidthShift) / (float)(m_dwScreenHeight - m_nHeightShift)) * 1.0f,
		g_ClipNear * 1.4f,
		g_ClipFar);

	HRESULT hr = m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
	D3DXMATRIX mat;
	D3DXMatrixTranspose(&mat, &m_matProj);

	m_pd3dDevice->SetVertexShaderConstantF(2, (const float*)&mat, 4);

	return SUCCEEDED(hr) ? 0 : hr;
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
