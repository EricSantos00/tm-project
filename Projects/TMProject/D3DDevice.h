#pragma once

#include "D3DEnumeration.h"
#include "D3DSettings.h"

enum APPMSGTYPE { MSG_NONE, MSGERR_APPMUSTEXIT, MSGWARN_SWITCHEDTOREF };

#define D3DAPPERR_NODIRECT3D          0x82000001
#define D3DAPPERR_NOWINDOW            0x82000002
#define D3DAPPERR_NOCOMPATIBLEDEVICES 0x82000003
#define D3DAPPERR_NOWINDOWABLEDEVICES 0x82000004
#define D3DAPPERR_NOHARDWAREDEVICE    0x82000005
#define D3DAPPERR_HALNOTCOMPATIBLE    0x82000006
#define D3DAPPERR_NOWINDOWEDHAL       0x82000007
#define D3DAPPERR_NODESKTOPHAL        0x82000008
#define D3DAPPERR_NOHALTHISMODE       0x82000009
#define D3DAPPERR_NONZEROREFCOUNT     0x8200000a
#define D3DAPPERR_MEDIANOTFOUND       0x8200000b
#define D3DAPPERR_RESETFAILED         0x8200000c
#define D3DAPPERR_NULLREFDEVICE       0x8200000d

class D3DDevice
{
public:	
	D3DDevice();

	virtual int Initialize(HWND hWnd);			
	virtual void Pause(bool bPause);
	virtual ~D3DDevice();
	
	HRESULT DisplayErrorMsg(HRESULT hr, unsigned int dwType);
	// static?
	static bool ConfirmDeviceHelper(D3DCAPS9* pCaps,
		VertexProcessingType vertexProcessingType, D3DFORMAT backBufferFormat);
	void BuildPresentParamsFromSettings();
	char FindBestWindowedMode(bool bRequireHAL, bool bRequireREF);
	char FindBestFullscreenMode(bool bRequireHAL, bool bRequireREF);
	HRESULT ChooseInitialD3DSettings();
	HRESULT Initialize3DEnvironment();
	HRESULT HandlePossibleSizeChange();
	HRESULT Reset3DEnvironment();
	HRESULT ToggleFullscreen();
	HRESULT ForceWindowed();
	HRESULT UserSelectNewDevice();
	void Cleanup3DEnvironment();

	virtual HRESULT AdjustWindowForChange();
	static HRESULT ConfirmDevice(D3DCAPS9* pCaps, DWORD dwBehavior, D3DFORMAT backBufferFormat);
	virtual HRESULT OneTimeSceneInit();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT FrameMove();
	virtual HRESULT Render();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT FinalCleanup();
	void CaptureScreen();

public:
	CD3DEnumeration m_d3dEnumeration;
	CD3DSettings m_d3dSettings;
	int m_bG400;
	bool m_bWindowed;
	bool m_bDeviceLost;
	bool m_bMinized;
	bool m_bMaximized;
	bool m_bIgnoreSizeChange;
	bool m_bDeviceObjectsInited;
	bool m_bDeviceObjectsRestored;
	unsigned int m_dwScreenWidth;
	unsigned int m_dwScreenHeight;
	unsigned int m_dwBitCount;
	unsigned int m_dwMaxStageNum;
	D3DFORMAT m_eFormat;
	unsigned int m_dwOS;
	int m_iVGAID;
	D3DPRESENT_PARAMETERS m_d3dpp;
	HWND m_hWnd;
	HWND m_hWndFocus;
	HMENU m_hMenu;
	IDirect3D9* m_pD3D;
	IDirect3DDevice9* m_pd3dDevice;
	D3DCAPS9 m_d3dCaps;
	D3DSURFACE_DESC m_d3dsdBackBuffer;
	unsigned int m_dwCreateFlags;
	unsigned int m_dwWindowStyle;
	RECT m_rcWindowBounds;
	RECT m_rcWindowClient;
	float m_fTime;
	float m_fElapsedTime;
	float m_fFPS;
	char m_strDeviceStats[90];
	char m_strFrameStats[90];
	bool m_bShowCursorWhenFullscreen;
	bool m_bClipCursorWhenFullscreen;
	bool m_bStartFullscreen;
	int m_nAntiAliasLevel;
	int m_bSavage;
	int m_bVoodoo;
	int m_bNVIDIA;
	int m_bIntel;
	int m_bDXT1;
	int m_bDXT3;
	int m_bTNT;

public:
	static int m_bDxt;
	static int m_nMipMap;
};