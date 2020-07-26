#include "pch.h"
#include "D3DDevice.h"
#include "TMGlobal.h"
#include "TMLog.h"

int D3DDevice::m_bDxt = 1;
int D3DDevice::m_nMipMap = 20;

D3DDevice::D3DDevice()
{
	m_pD3D = nullptr;
	m_pd3dDevice = nullptr;
	m_hWnd = nullptr;
	m_hWndFocus = nullptr;
	m_hMenu = nullptr;
	m_bWindowed = true;
	m_iVGAID = -1;
	m_bDeviceLost = 0;
	m_bMaximized = 0;
	m_bMinized = 0;
	m_bIgnoreSizeChange = 0;
	m_bDeviceObjectsInited = 0;
	m_bDeviceObjectsRestored = 0;
	m_dwCreateFlags = 0;
	m_dwMaxStageNum = 0;
	m_eFormat = D3DFORMAT::D3DFMT_UNKNOWN;
	m_bSavage = 0;
	m_bVoodoo = 0;
	m_bNVIDIA = 0;
	m_bIntel = 0;
	m_bG400 = 0;
	memset(&m_d3dpp, 0, sizeof(m_d3dpp));
	m_fTime = 0;
	m_fElapsedTime = 0;
	m_fFPS = 0;
	m_strDeviceStats[0] = 0;
	m_strFrameStats[0] = 0;
	m_bShowCursorWhenFullscreen = false;
	m_bStartFullscreen = false;
	Pause(true);
	m_bClipCursorWhenFullscreen = true;
}

D3DDevice::~D3DDevice()
{
}

int D3DDevice::Initialize(HWND hWnd)
{
	HRESULT hr;

	// Create the Direct3D object
	m_pD3D = Direct3DCreate9(D3D9b_SDK_VERSION);
	if (m_pD3D == NULL)
		return DisplayErrorMsg(D3DAPPERR_NODIRECT3D, MSGERR_APPMUSTEXIT);

	// Build a list of Direct3D adapters, modes and devices. The
	// ConfirmDevice() callback is used to confirm that only devices that
	// meet the app's requirements are considered.
	m_d3dEnumeration.SetD3D(m_pD3D);
	m_d3dEnumeration.ConfirmDeviceCallback = D3DDevice::ConfirmDeviceHelper;
	if (FAILED(hr = m_d3dEnumeration.Enumerate()))
	{
		SAFE_RELEASE(m_pD3D);
		return DisplayErrorMsg(hr, MSGERR_APPMUSTEXIT);
	}

	if (!m_hWnd)
		m_hWnd = hWnd;
	if (!m_hWndFocus)
		m_hWndFocus = m_hWnd;

	m_dwWindowStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	GetWindowRect(m_hWnd, &m_rcWindowBounds);

	m_rcWindowClient.left = 0;
	m_rcWindowClient.top = 0;
	m_rcWindowClient.right = m_dwScreenWidth;
	m_rcWindowClient.bottom = m_dwScreenHeight;
	if (FAILED(hr = ChooseInitialD3DSettings()))
	{
		SAFE_RELEASE(m_pD3D);
		return DisplayErrorMsg(hr, MSGERR_APPMUSTEXIT);
	}

	// Initialize the app's custom scene stuff
	if (FAILED(hr = OneTimeSceneInit()))
	{
		SAFE_RELEASE(m_pD3D);
		return DisplayErrorMsg(hr, MSGERR_APPMUSTEXIT);
	}

	// Initialize the 3D environment for the app
	if (FAILED(hr = Initialize3DEnvironment()))
	{
		SAFE_RELEASE(m_pD3D);
		return DisplayErrorMsg(hr, MSGERR_APPMUSTEXIT);
	}

	return S_OK;
}

void D3DDevice::Pause(bool bPause)
{
	static DWORD dwAppPausedCount = 0;

	dwAppPausedCount += (bPause ? +1 : -1);
	g_pApp->m_bActive = dwAppPausedCount == 0;
}

HRESULT D3DDevice::DisplayErrorMsg(HRESULT hr, unsigned int dwType)
{
	static bool s_bFatalErrorReported = false;
	TCHAR strMsg[512];

	// If a fatal error message has already been reported, the app
	// is already shutting down, so don't show more error messages.
	if (s_bFatalErrorReported)
		return hr;

	switch (hr)
	{
	case D3DAPPERR_NODIRECT3D:
		_tcscpy(strMsg, _T("Could not initialize Direct3D. You may\n")
			_T("want to check that the latest version of\n")
			_T("DirectX is correctly installed on your\n")
			_T("system.  Also make sure that this program\n")
			_T("was compiled with header files that match\n")
			_T("the installed DirectX DLLs."));
		break;

	case D3DAPPERR_NOCOMPATIBLEDEVICES:
		_tcscpy(strMsg, _T("Could not find any compatible Direct3D\n")
			_T("devices."));
		break;

	case D3DAPPERR_NOWINDOWABLEDEVICES:
		_tcscpy(strMsg, _T("This sample cannot run in a desktop\n")
			_T("window with the current display settings.\n")
			_T("Please change your desktop settings to a\n")
			_T("16- or 32-bit display mode and re-run this\n")
			_T("sample."));
		break;

	case D3DAPPERR_NOHARDWAREDEVICE:
		_tcscpy(strMsg, _T("No hardware-accelerated Direct3D devices\n")
			_T("were found."));
		break;

	case D3DAPPERR_HALNOTCOMPATIBLE:
		_tcscpy(strMsg, _T("This sample requires functionality that is\n")
			_T("not available on your Direct3D hardware\n")
			_T("accelerator."));
		break;

	case D3DAPPERR_NOWINDOWEDHAL:
		_tcscpy(strMsg, _T("Your Direct3D hardware accelerator cannot\n")
			_T("render into a window.\n")
			_T("Press F2 while the app is running to see a\n")
			_T("list of available devices and modes."));
		break;

	case D3DAPPERR_NODESKTOPHAL:
		_tcscpy(strMsg, _T("Your Direct3D hardware accelerator cannot\n")
			_T("render into a window with the current\n")
			_T("desktop display settings.\n")
			_T("Press F2 while the app is running to see a\n")
			_T("list of available devices and modes."));
		break;

	case D3DAPPERR_NOHALTHISMODE:
		_tcscpy(strMsg, _T("This sample requires functionality that is\n")
			_T("not available on your Direct3D hardware\n")
			_T("accelerator with the current desktop display\n")
			_T("settings.\n")
			_T("Press F2 while the app is running to see a\n")
			_T("list of available devices and modes."));
		break;

	case D3DAPPERR_MEDIANOTFOUND:
	case HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND):
		_tcscpy(strMsg, _T("Could not load required media."));
		break;

	case D3DAPPERR_RESETFAILED:
		_tcscpy(strMsg, _T("Could not reset the Direct3D device."));
		break;

	case D3DAPPERR_NONZEROREFCOUNT:
		_tcscpy(strMsg, _T("A D3D object has a non-zero reference\n")
			_T("count (meaning things were not properly\n")
			_T("cleaned up)."));
		break;

	case D3DAPPERR_NULLREFDEVICE:
		_tcscpy(strMsg, _T("Warning: Nothing will be rendered.\n")
			_T("The reference rendering device was selected, but your\n")
			_T("computer only has a reduced-functionality reference device\n")
			_T("installed.  Install the DirectX SDK to get the full\n")
			_T("reference device.\n"));
		break;

	case E_OUTOFMEMORY:
		_tcscpy(strMsg, _T("Not enough memory."));
		break;

	case D3DERR_OUTOFVIDEOMEMORY:
		_tcscpy(strMsg, _T("Not enough video memory."));
		break;

	default:
		_tcscpy(strMsg, _T("Generic application error. Enable\n")
			_T("debug output for detailed information."));
	}

	if (MSGERR_APPMUSTEXIT == dwType)
	{
		s_bFatalErrorReported = true;
		_tcscat(strMsg, _T("\n\nThis sample will now exit."));
		MessageBox(NULL, strMsg, "Error", MB_ICONERROR | MB_OK);

		// Close the window, which shuts down the app
		if (m_hWnd)
			SendMessage(m_hWnd, WM_CLOSE, 0, 0);
	}
	else
	{
		if (MSGWARN_SWITCHEDTOREF == dwType)
			_tcscat(strMsg, _T("\n\nSwitching to the reference rasterizer,\n")
				_T("a software device that implements the entire\n")
				_T("Direct3D feature set, but runs very slowly."));
		MessageBox(NULL, strMsg, "Error", MB_ICONWARNING | MB_OK);
	}

	return hr;
}

bool D3DDevice::ConfirmDeviceHelper(D3DCAPS9* pCaps, VertexProcessingType vertexProcessingType, D3DFORMAT backBufferFormat)
{
	DWORD dwBehavior;

	if (vertexProcessingType == SOFTWARE_VP)
		dwBehavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else if (vertexProcessingType == MIXED_VP)
		dwBehavior = D3DCREATE_MIXED_VERTEXPROCESSING;
	else if (vertexProcessingType == HARDWARE_VP)
		dwBehavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else if (vertexProcessingType == PURE_HARDWARE_VP)
		dwBehavior = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
	else
		dwBehavior = 0; // TODO: throw exception

	return D3DDevice::ConfirmDevice(pCaps, dwBehavior, backBufferFormat) >= 0;
}

void D3DDevice::BuildPresentParamsFromSettings()
{
	m_d3dpp.Windowed = m_d3dSettings.IsWindowed;
	m_d3dpp.BackBufferCount = 1;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dpp.EnableAutoDepthStencil = m_d3dEnumeration.AppUsesDepthBuffer;
	m_d3dpp.hDeviceWindow = m_hWnd;

	if (m_iVGAID == 2 && g_nUseBlur > 0)
		g_nAntialias = 0;

	if (m_d3dEnumeration.AppUsesDepthBuffer)
	{
		if (!g_nAntialias)
			m_d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
		m_d3dpp.AutoDepthStencilFormat = m_d3dSettings.DepthStencilBufferFormat();
	}
	else
	{
		m_d3dpp.Flags = 0;
	}

	if (m_bWindowed)
	{
		m_d3dpp.BackBufferWidth = m_rcWindowClient.right - m_rcWindowClient.left;
		m_d3dpp.BackBufferHeight = m_rcWindowClient.bottom - m_rcWindowClient.top;
		m_d3dpp.BackBufferFormat = m_d3dSettings.PDeviceCombo()->BackBufferFormat;
		m_d3dpp.FullScreen_RefreshRateInHz = 0;
		m_d3dpp.PresentationInterval = 0;
		if (!g_nAntialias)
			m_d3dpp.Flags |= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	}
	else
	{
		m_d3dpp.BackBufferWidth = m_d3dSettings.DisplayMode().Width;
		m_d3dpp.BackBufferHeight = m_d3dSettings.DisplayMode().Height;
		m_d3dpp.BackBufferFormat = m_d3dSettings.PDeviceCombo()->BackBufferFormat;
		m_d3dpp.FullScreen_RefreshRateInHz = m_d3dSettings.Fullscreen_DisplayMode.RefreshRate;
		m_d3dpp.PresentationInterval = m_d3dSettings.PresentInterval();
		if (!g_nAntialias)
			m_d3dpp.Flags |= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	}

	m_nAntiAliasLevel = 0;

	if (g_nAntialias)
	{
		for (int i = 1; i <= g_nAntialias; ++i)
		{
			int nTempLevel = i + 1;
			DWORD qualityLevel = 0;
			if (m_pD3D->CheckDeviceMultiSampleType(0, D3DDEVTYPE::D3DDEVTYPE_HAL, m_d3dpp.BackBufferFormat,
				m_bWindowed, (D3DMULTISAMPLE_TYPE)(i + 1), &qualityLevel) >= 0 &&
				m_pD3D->CheckDeviceMultiSampleType(0, D3DDEVTYPE::D3DDEVTYPE_HAL, m_d3dpp.AutoDepthStencilFormat,
					m_bWindowed, (D3DMULTISAMPLE_TYPE)(nTempLevel), &qualityLevel) >= 0)
			{
				m_nAntiAliasLevel = nTempLevel;
				m_d3dSettings.SetMultisampleType((D3DMULTISAMPLE_TYPE)nTempLevel);
				m_d3dSettings.SetMultisampleQuality(qualityLevel - 1);
			}
		}
	}

	m_d3dpp.MultiSampleType = m_d3dSettings.MultisampleType();
	m_d3dpp.MultiSampleQuality = m_d3dSettings.MultisampleQuality();
}

char D3DDevice::FindBestWindowedMode(bool bRequireHAL, bool bRequireREF)
{
	// Get display mode of primary adapter (which is assumed to be where the window 
// will appear)
	D3DDISPLAYMODE primaryDesktopDisplayMode;
	m_pD3D->GetAdapterDisplayMode(0, &primaryDesktopDisplayMode);

	D3DAdapterInfo* pBestAdapterInfo = NULL;
	D3DDeviceInfo* pBestDeviceInfo = NULL;
	D3DDeviceCombo* pBestDeviceCombo = NULL;

	for (UINT iai = 0; iai < m_d3dEnumeration.m_pAdapterInfoList->Count(); iai++)
	{
		D3DAdapterInfo* pAdapterInfo = (D3DAdapterInfo*)m_d3dEnumeration.m_pAdapterInfoList->GetPtr(iai);
		for (UINT idi = 0; idi < pAdapterInfo->pDeviceInfoList->Count(); idi++)
		{
			D3DDeviceInfo* pDeviceInfo = (D3DDeviceInfo*)pAdapterInfo->pDeviceInfoList->GetPtr(idi);
			if (bRequireHAL && pDeviceInfo->DevType != D3DDEVTYPE_HAL)
				continue;
			if (bRequireREF && pDeviceInfo->DevType != D3DDEVTYPE_REF)
				continue;
			for (UINT idc = 0; idc < pDeviceInfo->pDeviceComboList->Count(); idc++)
			{
				D3DDeviceCombo* pDeviceCombo = (D3DDeviceCombo*)pDeviceInfo->pDeviceComboList->GetPtr(idc);
				bool bAdapterMatchesBB = (pDeviceCombo->BackBufferFormat == pDeviceCombo->AdapterFormat);
				if (!pDeviceCombo->IsWindowed)
					continue;
				if (pDeviceCombo->AdapterFormat != primaryDesktopDisplayMode.Format)
					continue;
				// If we haven't found a compatible DeviceCombo yet, or if this set
				// is better (because it's a HAL, and/or because formats match better),
				// save it
				if (pBestDeviceCombo == NULL ||
					pBestDeviceCombo->DevType != D3DDEVTYPE_HAL && pDeviceCombo->DevType == D3DDEVTYPE_HAL ||
					pDeviceCombo->DevType == D3DDEVTYPE_HAL && bAdapterMatchesBB)
				{
					pBestAdapterInfo = pAdapterInfo;
					pBestDeviceInfo = pDeviceInfo;
					pBestDeviceCombo = pDeviceCombo;
					if (pDeviceCombo->DevType == D3DDEVTYPE_HAL && bAdapterMatchesBB)
					{
						// This windowed device combo looks great -- take it
						goto EndWindowedDeviceComboSearch;
					}
					// Otherwise keep looking for a better windowed device combo
				}
			}
		}
	}
EndWindowedDeviceComboSearch:
	if (pBestDeviceCombo == NULL)
		return false;

	m_d3dSettings.pWindowed_AdapterInfo = pBestAdapterInfo;
	m_d3dSettings.pWindowed_DeviceInfo = pBestDeviceInfo;
	m_d3dSettings.pWindowed_DeviceCombo = pBestDeviceCombo;
	m_d3dSettings.IsWindowed = true;
	m_d3dSettings.Windowed_DisplayMode = primaryDesktopDisplayMode;
	m_d3dSettings.Windowed_Width = m_rcWindowClient.right - m_rcWindowClient.left;
	m_d3dSettings.Windowed_Height = m_rcWindowClient.bottom - m_rcWindowClient.top;
	if (m_d3dEnumeration.AppUsesDepthBuffer)
		m_d3dSettings.Windowed_DepthStencilBufferFormat = *(D3DFORMAT*)pBestDeviceCombo->pDepthStencilFormatList->GetPtr(0);
	m_d3dSettings.Windowed_MultisampleType = *(D3DMULTISAMPLE_TYPE*)pBestDeviceCombo->pMultiSampleTypeList->GetPtr(0);
	m_d3dSettings.Windowed_MultisampleQuality = 0;
	m_d3dSettings.Windowed_VertexProcessingType = *(VertexProcessingType*)pBestDeviceCombo->pVertexProcessingTypeList->GetPtr(0);
	m_d3dSettings.Windowed_PresentInterval = *(UINT*)pBestDeviceCombo->pPresentIntervalList->GetPtr(0);
	m_eFormat = pBestDeviceCombo->AdapterFormat;
	m_dwMaxStageNum = m_d3dSettings.PDeviceInfo()->Caps.MaxTextureBlendStages;

	return true;
}

char D3DDevice::FindBestFullscreenMode(bool bRequireHAL, bool bRequireREF)
{
	// For fullscreen, default to first HAL DeviceCombo that supports the current desktop 
	// display mode, or any display mode if HAL is not compatible with the desktop mode, or 
	// non-HAL if no HAL is available
	D3DDISPLAYMODE adapterDesktopDisplayMode;
	D3DDISPLAYMODE bestAdapterDesktopDisplayMode;
	D3DDISPLAYMODE bestDisplayMode;
	bestAdapterDesktopDisplayMode.Width = 0;
	bestAdapterDesktopDisplayMode.Height = 0;
	bestAdapterDesktopDisplayMode.Format = D3DFMT_UNKNOWN;
	bestAdapterDesktopDisplayMode.RefreshRate = 0;

	D3DAdapterInfo* pBestAdapterInfo = NULL;
	D3DDeviceInfo* pBestDeviceInfo = NULL;
	D3DDeviceCombo* pBestDeviceCombo = NULL;

	for (UINT iai = 0; iai < m_d3dEnumeration.m_pAdapterInfoList->Count(); iai++)
	{
		D3DAdapterInfo* pAdapterInfo = (D3DAdapterInfo*)m_d3dEnumeration.m_pAdapterInfoList->GetPtr(iai);
		m_pD3D->GetAdapterDisplayMode(pAdapterInfo->AdapterOrdinal, &adapterDesktopDisplayMode);
		for (UINT idi = 0; idi < pAdapterInfo->pDeviceInfoList->Count(); idi++)
		{
			D3DDeviceInfo* pDeviceInfo = (D3DDeviceInfo*)pAdapterInfo->pDeviceInfoList->GetPtr(idi);
			if (bRequireHAL && pDeviceInfo->DevType != D3DDEVTYPE_HAL)
				continue;
			if (bRequireREF && pDeviceInfo->DevType != D3DDEVTYPE_REF)
				continue;
			for (UINT idc = 0; idc < pDeviceInfo->pDeviceComboList->Count(); idc++)
			{
				D3DDeviceCombo* pDeviceCombo = (D3DDeviceCombo*)pDeviceInfo->pDeviceComboList->GetPtr(idc);
				bool bAdapterMatchesBB = (pDeviceCombo->BackBufferFormat == pDeviceCombo->AdapterFormat);
				bool bAdapterMatchesDesktop = (pDeviceCombo->AdapterFormat == adapterDesktopDisplayMode.Format);
				if (pDeviceCombo->IsWindowed)
					continue;
				// If we haven't found a compatible set yet, or if this set
				// is better (because it's a HAL, and/or because formats match better),
				// save it
				if (pBestDeviceCombo == NULL ||
					pBestDeviceCombo->DevType != D3DDEVTYPE_HAL && pDeviceInfo->DevType == D3DDEVTYPE_HAL ||
					pDeviceCombo->DevType == D3DDEVTYPE_HAL && pBestDeviceCombo->AdapterFormat != adapterDesktopDisplayMode.Format && bAdapterMatchesDesktop ||
					pDeviceCombo->DevType == D3DDEVTYPE_HAL && bAdapterMatchesDesktop && bAdapterMatchesBB)
				{
					bestAdapterDesktopDisplayMode = adapterDesktopDisplayMode;
					pBestAdapterInfo = pAdapterInfo;
					pBestDeviceInfo = pDeviceInfo;
					pBestDeviceCombo = pDeviceCombo;
					if (pDeviceInfo->DevType == D3DDEVTYPE_HAL && bAdapterMatchesDesktop && bAdapterMatchesBB)
					{
						// This fullscreen device combo looks great -- take it
						goto EndFullscreenDeviceComboSearch;
					}
					// Otherwise keep looking for a better fullscreen device combo
				}
			}
		}
	}
EndFullscreenDeviceComboSearch:
	if (pBestDeviceCombo == NULL)
		return false;

	bestDisplayMode.Width = m_dwScreenWidth;
	bestDisplayMode.Height = m_dwScreenHeight;

	if (m_dwBitCount == 32)
		bestDisplayMode.Format = D3DFORMAT::D3DFMT_X8R8G8B8;
	else
		bestDisplayMode.Format = D3DFORMAT::D3DFMT_R5G6B5;

	bestDisplayMode.RefreshRate = 0;
	for (UINT idm = 0; idm < pBestAdapterInfo->pDisplayModeList->Count(); idm++)
	{
		D3DDISPLAYMODE* pdm = (D3DDISPLAYMODE*)pBestAdapterInfo->pDisplayModeList->GetPtr(idm);
		if (pdm->Format != pBestDeviceCombo->AdapterFormat)
			continue;
		if (pdm->Width == bestAdapterDesktopDisplayMode.Width &&
			pdm->Height == bestAdapterDesktopDisplayMode.Height &&
			pdm->RefreshRate == bestAdapterDesktopDisplayMode.RefreshRate)
		{
			// found a perfect match, so stop
			bestDisplayMode = *pdm;
			break;
		}
		else if (pdm->Width == bestAdapterDesktopDisplayMode.Width &&
			pdm->Height == bestAdapterDesktopDisplayMode.Height &&
			pdm->RefreshRate > bestDisplayMode.RefreshRate)
		{
			// refresh rate doesn't match, but width/height match, so keep this
			// and keep looking
			bestDisplayMode = *pdm;
		}
		else if (pdm->Width == bestAdapterDesktopDisplayMode.Width)
		{
			// width matches, so keep this and keep looking
			bestDisplayMode = *pdm;
		}
		else if (bestDisplayMode.Width == 0)
		{
			// we don't have anything better yet, so keep this and keep looking
			bestDisplayMode = *pdm;
		}
	}

	m_d3dSettings.pFullscreen_AdapterInfo = pBestAdapterInfo;
	m_d3dSettings.pFullscreen_DeviceInfo = pBestDeviceInfo;
	m_d3dSettings.pFullscreen_DeviceCombo = pBestDeviceCombo;
	m_d3dSettings.IsWindowed = false;
	m_d3dSettings.Fullscreen_DisplayMode = bestDisplayMode;
	if (m_d3dEnumeration.AppUsesDepthBuffer)
		m_d3dSettings.Fullscreen_DepthStencilBufferFormat = *(D3DFORMAT*)pBestDeviceCombo->pDepthStencilFormatList->GetPtr(0);
	m_d3dSettings.Fullscreen_MultisampleType = *(D3DMULTISAMPLE_TYPE*)pBestDeviceCombo->pMultiSampleTypeList->GetPtr(0);
	m_d3dSettings.Fullscreen_MultisampleQuality = 0;
	m_d3dSettings.Fullscreen_VertexProcessingType = *(VertexProcessingType*)pBestDeviceCombo->pVertexProcessingTypeList->GetPtr(0);
	m_d3dSettings.Fullscreen_PresentInterval = D3DPRESENT_INTERVAL_DEFAULT;

	m_eFormat = pBestDeviceCombo->AdapterFormat;
	m_dwMaxStageNum = m_d3dSettings.PDeviceInfo()->Caps.MaxTextureBlendStages;
	return true;
}

HRESULT D3DDevice::ChooseInitialD3DSettings()
{
	bool bFoundFullscreen = FindBestFullscreenMode(false, false);
	bool bFoundWindowed = FindBestWindowedMode(false, false);

	if (m_bStartFullscreen && bFoundFullscreen)
		m_d3dSettings.IsWindowed = false;
	if (!bFoundWindowed && bFoundFullscreen)
		m_d3dSettings.IsWindowed = false;

	if (!bFoundFullscreen && !bFoundWindowed)
		return D3DAPPERR_NOCOMPATIBLEDEVICES;

	return S_OK;
}

HRESULT D3DDevice::Initialize3DEnvironment()
{
	HRESULT hr;

	OSVERSIONINFOEX osvi = { 0 };
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	osvi.dwMajorVersion = 6;
	osvi.dwMinorVersion = 3;
	DWORDLONG dwlConditionMask = 0;
	VER_SET_CONDITION(dwlConditionMask, VER_MAJORVERSION, VER_GREATER_EQUAL);
	VER_SET_CONDITION(dwlConditionMask, VER_MINORVERSION, VER_GREATER_EQUAL);
	VerifyVersionInfo(&osvi, VER_MAJORVERSION | VER_MINORVERSION, dwlConditionMask);

	m_dwOS = osvi.dwMajorVersion;

	D3DAdapterInfo* pAdapterInfo = m_d3dSettings.PAdapterInfo();
	D3DDeviceInfo* pDeviceInfo = m_d3dSettings.PDeviceInfo();

	char* vgaUP = _strupr(pAdapterInfo->AdapterIdentifier.Description);

	char strVGA[256];
	sprintf(strVGA, "%s", vgaUP);

	if (strstr(strVGA, "NVIDIA"))
	{
		if (strstr(strVGA, "MX"))
			m_iVGAID = 0;
		else
			m_iVGAID = 1;
	}
	if (strstr(strVGA, "RADEON"))
		m_iVGAID = 2;
	if (strstr(strVGA, "NVIDIA"))
	{
		m_bNVIDIA = 1;
		if (strstr(strVGA, "RIVA") || strstr(strVGA, "TNT") || strstr(strVGA, "TNT2"))
			m_bTNT = 1;
	}
	if (strstr(strVGA, "SAVAGA"))
		m_bSavage = 1;
	if (strstr(strVGA, "MATROX") && strstr(strVGA, "G4"))
		m_bG400 = 1;
	if (strstr(strVGA, "INTEL") || strstr(strVGA, "810"))
		m_bIntel = 1;

	m_bWindowed = m_d3dSettings.IsWindowed;
	AdjustWindowForChange();
	BuildPresentParamsFromSettings();
	if (pDeviceInfo->Caps.PrimitiveMiscCaps & D3DPMISCCAPS_NULLREFERENCE)
	{
		// Warn user about null ref device that can't render anything
		DisplayErrorMsg(D3DAPPERR_NULLREFDEVICE, 0);
	}

	DWORD behaviorFlags;
	if (m_d3dSettings.GetVertexProcessingType() == SOFTWARE_VP)
		behaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else if (m_d3dSettings.GetVertexProcessingType() == MIXED_VP)
		behaviorFlags = D3DCREATE_MIXED_VERTEXPROCESSING;
	else if (m_d3dSettings.GetVertexProcessingType() == HARDWARE_VP)
		behaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else if (m_d3dSettings.GetVertexProcessingType() == PURE_HARDWARE_VP)
		behaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE;
	else
		behaviorFlags = 0; // TODO: throw exception

	hr = m_pD3D->CreateDevice(m_d3dSettings.AdapterOrdinal(), pDeviceInfo->DevType,
		m_hWndFocus, behaviorFlags, &m_d3dpp,
		&m_pd3dDevice);

	if (SUCCEEDED(hr))
	{
		// When moving from fullscreen to windowed mode, it is important to
		// adjust the window size after recreating the device rather than
		// beforehand to ensure that you get the window size you want.  For
		// example, when switching from 640x480 fullscreen to windowed with
		// a 1000x600 window on a 1024x768 desktop, it is impossible to set
		// the window size to 1000x600 until after the display mode has
		// changed to 1024x768, because windows cannot be larger than the
		// desktop.
		if (m_bWindowed)
		{
			SetWindowPos(m_hWnd, HWND_NOTOPMOST,
				m_rcWindowBounds.left, m_rcWindowBounds.top,
				(m_rcWindowBounds.right - m_rcWindowBounds.left),
				(m_rcWindowBounds.bottom - m_rcWindowBounds.top),
				SWP_SHOWWINDOW);
		}

		// Store device Caps
		m_pd3dDevice->GetDeviceCaps(&m_d3dCaps);
		m_dwCreateFlags = behaviorFlags;

		// Store device description
		if (pDeviceInfo->DevType == D3DDEVTYPE_REF)
			lstrcpy(m_strDeviceStats, TEXT("REF"));
		else if (pDeviceInfo->DevType == D3DDEVTYPE_HAL)
			lstrcpy(m_strDeviceStats, TEXT("HAL"));
		else if (pDeviceInfo->DevType == D3DDEVTYPE_SW)
			lstrcpy(m_strDeviceStats, TEXT("SW"));

		if (behaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING &&
			behaviorFlags & D3DCREATE_PUREDEVICE)
		{
			if (pDeviceInfo->DevType == D3DDEVTYPE_HAL)
				lstrcat(m_strDeviceStats, TEXT(" (pure hw vp)"));
			else
				lstrcat(m_strDeviceStats, TEXT(" (simulated pure hw vp)"));
		}
		else if (behaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
		{
			if (pDeviceInfo->DevType == D3DDEVTYPE_HAL)
				lstrcat(m_strDeviceStats, TEXT(" (hw vp)"));
			else
				lstrcat(m_strDeviceStats, TEXT(" (simulated hw vp)"));
		}
		else if (behaviorFlags & D3DCREATE_MIXED_VERTEXPROCESSING)
		{
			if (pDeviceInfo->DevType == D3DDEVTYPE_HAL)
				lstrcat(m_strDeviceStats, TEXT(" (mixed vp)"));
			else
				lstrcat(m_strDeviceStats, TEXT(" (simulated mixed vp)"));
		}
		else if (behaviorFlags & D3DCREATE_SOFTWARE_VERTEXPROCESSING)
		{
			lstrcat(m_strDeviceStats, TEXT(" (sw vp)"));
		}

		if (pDeviceInfo->DevType == D3DDEVTYPE_HAL)
		{
			// Be sure not to overflow m_strDeviceStats when appending the adapter 
			// description, since it can be long.  Note that the adapter description
			// is initially CHAR and must be converted to TCHAR.
			lstrcat(m_strDeviceStats, TEXT(": "));
			const int cchDesc = sizeof(pAdapterInfo->AdapterIdentifier.Description);
			TCHAR szDescription[cchDesc];
			DXUtil_ConvertAnsiStringToGenericCch(szDescription,
				pAdapterInfo->AdapterIdentifier.Description, cchDesc);
			int maxAppend = sizeof(m_strDeviceStats) / sizeof(TCHAR) -
				lstrlen(m_strDeviceStats) - 1;
			_tcsncat(m_strDeviceStats, szDescription, maxAppend);
		}

		// Store render target surface desc
		LPDIRECT3DSURFACE9 pBackBuffer = NULL;
		m_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
		pBackBuffer->GetDesc(&m_d3dsdBackBuffer);
		pBackBuffer->Release();

		// Initialize the app's device-dependent objects
		hr = InitDeviceObjects();
		if (FAILED(hr))
		{
			DeleteDeviceObjects();
		}
		else
		{
			m_bDeviceObjectsInited = true;
			hr = RestoreDeviceObjects();
			if (FAILED(hr))
			{
				InvalidateDeviceObjects();
			}
			else
			{
				m_bDeviceObjectsRestored = true;
				return S_OK;
			}
		}

		// Cleanup before we try again
		Cleanup3DEnvironment();
	}

	// If that failed, fall back to the reference rasterizer
	if (hr != D3DAPPERR_MEDIANOTFOUND &&
		hr != HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) &&
		pDeviceInfo->DevType == D3DDEVTYPE_HAL)
	{
		if (FindBestWindowedMode(false, true))
		{
			m_bWindowed = true;
			AdjustWindowForChange();
			// Make sure main window isn't topmost, so error message is visible
			SetWindowPos(m_hWnd, HWND_NOTOPMOST,
				m_rcWindowBounds.left, m_rcWindowBounds.top,
				(m_rcWindowBounds.right - m_rcWindowBounds.left),
				(m_rcWindowBounds.bottom - m_rcWindowBounds.top),
				SWP_SHOWWINDOW);

			// Let the user know we are switching from HAL to the reference rasterizer
			DisplayErrorMsg(hr, MSGWARN_SWITCHEDTOREF);

			hr = Initialize3DEnvironment();
		}
	}
	return hr;
}

HRESULT D3DDevice::HandlePossibleSizeChange()
{
	HRESULT hr = S_OK;
	RECT rcClientOld;
	rcClientOld = m_rcWindowClient;

	if (m_bIgnoreSizeChange)
		return S_OK;

	// Update window properties
	GetWindowRect(m_hWnd, &m_rcWindowBounds);
	GetClientRect(m_hWnd, &m_rcWindowClient);

	if (rcClientOld.right - rcClientOld.left !=
		m_rcWindowClient.right - m_rcWindowClient.left ||
		rcClientOld.bottom - rcClientOld.top !=
		m_rcWindowClient.bottom - m_rcWindowClient.top)
	{
		// A new window size will require a new backbuffer
		// size, so the 3D structures must be changed accordingly.
		Pause(true);

		m_d3dpp.BackBufferWidth = m_rcWindowClient.right - m_rcWindowClient.left;
		m_d3dpp.BackBufferHeight = m_rcWindowClient.bottom - m_rcWindowClient.top;

		if (m_pd3dDevice != NULL)
		{
			// Reset the 3D environment
			if (FAILED(hr = Reset3DEnvironment()))
			{
				if (hr != D3DERR_OUTOFVIDEOMEMORY)
					hr = D3DAPPERR_RESETFAILED;
				DisplayErrorMsg(hr, MSGERR_APPMUSTEXIT);
			}
		}
		Pause(false);
	}
	return hr;
}

HRESULT D3DDevice::Reset3DEnvironment()
{
	HRESULT hr;

	// Release all vidmem objects
	if (m_bDeviceObjectsRestored)
	{
		m_bDeviceObjectsRestored = false;
		InvalidateDeviceObjects();
	}
	// Reset the device
	if (FAILED(hr = m_pd3dDevice->Reset(&m_d3dpp)))
		return hr;

	// Store render target surface desc
	LPDIRECT3DSURFACE9 pBackBuffer;
	m_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	pBackBuffer->GetDesc(&m_d3dsdBackBuffer);
	pBackBuffer->Release();

	// Initialize the app's device-dependent objects
	hr = RestoreDeviceObjects();
	if (FAILED(hr))
	{
		InvalidateDeviceObjects();
		return hr;
	}
	m_bDeviceObjectsRestored = true;

	return S_OK;
}

HRESULT D3DDevice::ToggleFullscreen()
{
	HRESULT hr;
	int AdapterOrdinalOld = m_d3dSettings.AdapterOrdinal();
	D3DDEVTYPE DevTypeOld = m_d3dSettings.DevType();

	Pause(true);
	m_bIgnoreSizeChange = true;

	// Toggle the windowed state
	m_bWindowed = !m_bWindowed;
	m_d3dSettings.IsWindowed = m_bWindowed;

	// Prepare window for windowed/fullscreen change
	AdjustWindowForChange();

	// If AdapterOrdinal and DevType are the same, we can just do a Reset().
	// If they've changed, we need to do a complete device teardown/rebuild.
	if (m_d3dSettings.AdapterOrdinal() == AdapterOrdinalOld &&
		m_d3dSettings.DevType() == DevTypeOld)
	{
		// Reset the 3D device
		BuildPresentParamsFromSettings();
		hr = Reset3DEnvironment();
	}
	else
	{
		Cleanup3DEnvironment();
		hr = Initialize3DEnvironment();
	}
	if (FAILED(hr))
	{
		if (hr != D3DERR_OUTOFVIDEOMEMORY)
			hr = D3DAPPERR_RESETFAILED;
		m_bIgnoreSizeChange = false;
		if (!m_bWindowed)
		{
			// Restore window type to windowed mode
			m_bWindowed = !m_bWindowed;
			m_d3dSettings.IsWindowed = m_bWindowed;
			AdjustWindowForChange();
			SetWindowPos(m_hWnd, HWND_NOTOPMOST,
				m_rcWindowBounds.left, m_rcWindowBounds.top,
				(m_rcWindowBounds.right - m_rcWindowBounds.left),
				(m_rcWindowBounds.bottom - m_rcWindowBounds.top),
				SWP_SHOWWINDOW);
		}
		return DisplayErrorMsg(hr, MSGERR_APPMUSTEXIT);
	}

	m_bIgnoreSizeChange = false;

	if (m_bWindowed)
	{
		SetWindowPos(m_hWnd, HWND_NOTOPMOST,
			m_rcWindowBounds.left, m_rcWindowBounds.top,
			(m_rcWindowBounds.right - m_rcWindowBounds.left),
			(m_rcWindowBounds.bottom - m_rcWindowBounds.top),
			SWP_SHOWWINDOW);
	}

	Pause(false);
	return S_OK;
}

HRESULT D3DDevice::ForceWindowed()
{
	HRESULT hr;

	if (m_bWindowed)
		return S_OK;

	if (!FindBestWindowedMode(false, false))
	{
		return E_FAIL;
	}
	m_bWindowed = true;

	// Now destroy the current 3D device objects, then reinitialize

	Pause(true);

	// Release all scene objects that will be re-created for the new device
	Cleanup3DEnvironment();

	// Create the new device
	if (FAILED(hr = Initialize3DEnvironment()))
		return DisplayErrorMsg(hr, MSGERR_APPMUSTEXIT);

	Pause(false);
	return S_OK;
}

HRESULT D3DDevice::UserSelectNewDevice()
{
	HRESULT result;
	HRESULT hr;

	if (m_bWindowed || ToggleFullscreen() >= 0)
	{
		m_bWindowed = m_d3dSettings.IsWindowed;
		Cleanup3DEnvironment();
		hr = Initialize3DEnvironment();

		if (hr >= 0)
		{
			result = 0;
		}
		else
		{
			if (hr != D3DERR_OUTOFVIDEOMEMORY)
				hr = -2113929204;
			if (!m_bWindowed)
			{
				m_bWindowed = m_bWindowed == false;
				m_d3dSettings.IsWindowed = m_bWindowed;

				AdjustWindowForChange();
				SetWindowPos(m_hWnd,
					HWND_TOPMOST,
					m_rcWindowBounds.left,
					m_rcWindowBounds.top,
					m_rcWindowBounds.right - m_rcWindowBounds.left,
					m_rcWindowBounds.bottom - m_rcWindowBounds.top,
					SWP_SHOWWINDOW);
			}
			result = DisplayErrorMsg(hr, 1);
		}
	}
	else
	{
		DisplayErrorMsg(-2113929204, 1);
		result = E_FAIL;
	}

	return result;
}

void D3DDevice::Cleanup3DEnvironment()
{
	if (m_pd3dDevice)
	{
		if (m_bDeviceObjectsRestored)
		{
			m_bDeviceObjectsRestored = false;
			InvalidateDeviceObjects();
		}
		if (m_bDeviceObjectsInited)
		{
			m_bDeviceObjectsInited = false;
			DeleteDeviceObjects();
		}

		m_pd3dDevice->Release();
		m_pd3dDevice = nullptr;
	}
	if (m_pD3D)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

HRESULT D3DDevice::AdjustWindowForChange()
{
	if (m_bWindowed)
	{
		SetWindowLong(m_hWnd, GWL_STYLE, m_dwWindowStyle);

		if (m_hMenu)
		{
			SetMenu(m_hWnd, m_hMenu);
			m_hMenu = nullptr;
		}
	}
	else
	{
		// TODO: change this to define
		SetWindowLong(m_hWnd, GWL_STYLE, -1878523904);
		if (!m_hMenu)
		{
			m_hMenu = GetMenu(m_hWnd);
			SetMenu(m_hWnd, nullptr);
		}
	}

	return 0;
}

HRESULT D3DDevice::ConfirmDevice(D3DCAPS9* pCaps, DWORD dwBehavior, D3DFORMAT backBufferFormat)
{

	HRESULT result;
	if (dwBehavior & 0x10 || dwBehavior & 0x40)
	{
		result = E_FAIL;
	}
	else if (dwBehavior & 0x80 && pCaps->MaxVertexBlendMatrices < 2)
	{
		result = E_FAIL;
	}
	else
	{
		result = 0;
	}

	return result;
}

HRESULT D3DDevice::OneTimeSceneInit()
{
	return 0;
}

HRESULT D3DDevice::InitDeviceObjects()
{
	return 0;
}

HRESULT D3DDevice::RestoreDeviceObjects()
{
	return 0;
}

HRESULT D3DDevice::FrameMove()
{
	return 0;
}

HRESULT D3DDevice::Render()
{
	return 0;
}

HRESULT D3DDevice::InvalidateDeviceObjects()
{
	return 0;
}

HRESULT D3DDevice::DeleteDeviceObjects()
{
	return 0;
}

HRESULT D3DDevice::FinalCleanup()
{
	return 0;
}

void D3DDevice::CaptureScreen()
{
	IDirect3DSurface9* pBackBuffer;

	int handle = -1;
	int nCount = 0;
	TCHAR szFileName[128];

	sprintf((char*)szFileName, "ScreenShot\\Capture%04d.bmp", 0);

	do
	{
		handle = _open((char*)szFileName, _O_BINARY);
		if (handle < 0)
			break;

		_close(handle);
		sprintf((char*)szFileName, "ScreenShot\\Capture%04d.bmp", ++nCount);
	} while (nCount <= 9999);

	m_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE::D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);

	if (D3DXSaveSurfaceToFile(szFileName, D3DXIMAGE_FILEFORMAT::D3DXIFF_BMP, pBackBuffer, 0, 0) < 0)
		LOG_WRITELOG("Can't capture screen\r\n");

	pBackBuffer->Release();
}