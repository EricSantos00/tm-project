#include "pch.h"
#include "EventTranslator.h"
#include "RenderDevice.h"
#include "dsutil.h"
#include "DirShow.h"
#include "TMVideoWnd.h"
#include "JBlur.h"
#include "TimerManager.h"
#include "ObjectManager.h"
#include "CPSock.h"
#include "NewApp.h"
#include "TMGlobal.h"
#include <shellapi.h>
#include "TMLog.h"
#include "Basedef.h"
#include "TMCamera.h"
#include <WinInet.h>
#include "TMSkinMesh.h"
#include "resource.h"
#include "TMHuman.h"
#include "TMFieldScene.h"
#include "SControlContainer.h"

const char ClassName[4] = "WYD";

NewApp::NewApp()
{
	m_hWnd = 0;
	m_bActive = 0;
	m_dwScreenWidth = 800;
	m_dwScreenHeight = 600;
	m_pRenderDevice = 0;
	m_pSoundManager = 0;
	m_pAviPlayer = 0;
	m_pBGMManager = 0;
	m_pEventTranslator = 0;
	m_pTimerManager = 0;
	m_pObjectManager = 0;
	m_pSocketManager = 0;
	g_pApp = this;
	ShellExecute(0, "open", ChangeUpdate_Path, 0, 0, 1);
	BASE_InitModuleDir();
	BASE_InitializeHitRate();
	BASE_ReadMessageBin();
	LOG_INITIALIZELOG(LogFile_Path);
	sprintf(m_strWindowTitle, GameWindow_Title);
	m_Winstate = 1;
	china_bWrite = 0;
	china_Playtime = -1;
	m_binactive = 1;

	CreateConsole();
}

NewApp::~NewApp()
{
	if (m_bwFullScreen)
		m_pRenderDevice->RestoreWindowMode();

	LOG_FINALIZELOG();
}

void InitServerName2()
{
	memset(g_szServerName, 0, sizeof(g_szServerName));
	FILE* fpBin = nullptr;
	fopen_s(&fpBin, ServerName2_Path, "rb");
	if (fpBin)
	{
		fread(g_szServerName, sizeof(g_szServerName), 1u, fpBin);
		fclose(fpBin);
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return g_pApp->MsgProc(hWnd, message, wParam, lParam);
}

HRESULT NewApp::Initialize(HINSTANCE hInstance, int nFull)
{
	struct stRes
	{
		unsigned int dwWidth;
		unsigned int dwHeight;
		unsigned int dwBit;
	} stResList[11];

	m_dwColorBit = 16;
	m_bwFullScreen = 0;
	g_hInstance = hInstance;
	m_dwScreenWidth = 800;
	m_dwScreenHeight = 600;
	m_nSound = 0;
	m_dwColorBit = 16;
	m_bwFullScreen = nFull;
	BASE_InitEffectString();
	stResList[0].dwWidth = 640;
	stResList[0].dwHeight = 480;
	stResList[0].dwBit = 32;
	stResList[1].dwWidth = 800;
	stResList[1].dwHeight = 600;
	stResList[1].dwBit = 32;
	stResList[2].dwWidth = 1024;
	stResList[2].dwHeight = 768;
	stResList[2].dwBit = 32;
	stResList[3].dwWidth = 1280;
	stResList[3].dwHeight = 1024;
	stResList[3].dwBit = 32;
	stResList[4].dwWidth = 1600;
	stResList[4].dwHeight = 1200;
	stResList[4].dwBit = 32;
	stResList[5].dwWidth = 640;
	stResList[5].dwHeight = 480;
	stResList[5].dwBit = 32;
	stResList[6].dwWidth = 800;
	stResList[6].dwHeight = 600;
	stResList[6].dwBit = 32;
	stResList[7].dwWidth = 1024;
	stResList[7].dwHeight = 768;
	stResList[7].dwBit = 32;
	stResList[8].dwWidth = 1280;
	stResList[8].dwHeight = 1024;
	stResList[8].dwBit = 32;
	stResList[9].dwWidth = 1600;
	stResList[9].dwHeight = 1200;
	stResList[9].dwBit = 32;
	stResList[10].dwWidth = 3200;
	stResList[10].dwHeight = 2400;
	stResList[10].dwBit = 32;

	int nResIndex = 2;
	int nBright = 50;
	int nCursor = 0;
	int nClassic = 0;
	int nMipMap = 30;
	int nCameraRotate = 0;
	int nDXT = 0;
	int nCameraView = 1;

	SaveUpdatAndConfig Config;

	FILE* fp = nullptr;
	fopen_s(&fp, ConfigFile_Path, "rb");
	if (fp)
	{
		fread(&Config, sizeof(Config), 1, fp);
		fclose(fp);
		fp = nullptr;
	}
	else
	{
		Config.Version = 7000;
		Config.Config[0] = 7;
		Config.Config[1] = 2;
		Config.Config[2] = 0;
		Config.Config[3] = 0;
		Config.Config[4] = -1;
		Config.Config[5] = 57;
		Config.Config[6] = 2;
		Config.Config[7] = 1;
		Config.Config[8] = 1;
		Config.Config[9] = 1;
		Config.Config[10] = 0;
		Config.Config[11] = 0;
		Config.Config[12] = 0;
		Config.Config[13] = 1;
	}

	int nWindow = -1;
	nResIndex = Config.Config[0];

	TMSkinMesh::m_nSmooth = Config.Config[1];

	if (Config.Config[1] >= 3)
		TMSkinMesh::m_nSmooth = 2;

	g_bHideEffect = 0;
	g_bHideSkillBuffEffect = 0;
	g_bHideSkillBuffEffect2 = 0;

	m_nSound = Config.Config[2];
	m_nMusic = Config.Config[3];
	nBright = Config.Config[5];
	nCursor = Config.Config[6];

	g_nPlayDemo = Config.Config[7];
	nWindow = Config.Config[8];
	if (Config.Config[8] >= 0)
	{		 
		m_bwFullScreen = nWindow == 0;
	}

	g_UIVer = Config.Config[9];
	if (nClassic == 1 || nResIndex == 1 || nResIndex == 6)
		g_UIVer = 1;

	nCameraRotate = Config.Config[10] > 0;
	nDXT = Config.Config[11] > 0;
	g_nKeyType = Config.Config[12];
	nCameraView = Config.Config[13];
	m_nCameraView = Config.Config[13];
	m_nCameraView = 1;
	g_UIVer = 2;
	D3DDevice::m_bDxt = nDXT == 0;
	RenderDevice::m_bCameraRot = nCameraRotate;
	D3DDevice::m_nMipMap = nMipMap;

	if (nBright < 0)
		nBright = 0;
	if (nBright > 100)
		nBright = 100;
	RenderDevice::m_nBright = nBright;
	TMSkinMesh::m_nSmooth = 1;

	if (nCursor == 1)
		nCursor = 0;
	else
		nCursor = 2;

	SCursor::m_nCursorType = nCursor;
	if (nCursor == 2)
	{
		SCursor::m_hCursor1 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
		SCursor::m_hCursor2 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
		if (SCursor::m_hCursor1)
			SetCursor(SCursor::m_hCursor1);
	}

	m_dwScreenWidth = stResList[nResIndex - 1].dwWidth;
	m_dwScreenHeight = stResList[nResIndex - 1].dwHeight;
	m_dwColorBit = stResList[nResIndex - 1].dwBit;
	if (!CheckResolution(m_dwScreenWidth, m_dwScreenHeight, m_dwColorBit))
	{
		m_dwScreenWidth = stResList[1].dwWidth;
		m_dwScreenHeight = stResList[1].dwHeight;
		m_dwColorBit = stResList[1].dwBit;
	}

	int _nFontSize = 14;
	switch (m_dwScreenWidth)
	{
	case 640:
		_nFontSize = 10;
		break;
	case 800:
		_nFontSize = 12;
		break;
	case 1024:
		_nFontSize = 14;
		break;
	case 1280:
		_nFontSize = 20;
		break;
	default:
		_nFontSize = 24;
		break;
	}

	RenderDevice::m_nFontSize = _nFontSize;
	RenderDevice::m_nFontTextureSize = 512;
	InitServerName2();
	InitServerName();

	if (m_hWnd == nullptr)
	{
		WNDCLASS wndClass;
		wndClass.style = 8;
		wndClass.lpfnWndProc = WndProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = hInstance;
		wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TMPROJECT));
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)GetStockObject(4);
		wndClass.lpszMenuName = 0;
		wndClass.lpszClassName = ClassName;

		RegisterClass(&wndClass);

		DWORD dwCreationFlags = 0;

		if (m_bwFullScreen)
			dwCreationFlags = 0x80000000;
		else
			dwCreationFlags = 0x0CA0000; // check what flag is this

		m_dwWindowStyle = dwCreationFlags | 0x10000000;

		RECT rc;
		SetRect(&rc, 0, 0, m_dwScreenWidth, m_dwScreenHeight);
		AdjustWindowRect(&rc, m_dwWindowStyle, 0);

		m_hWnd = CreateWindowEx(
			0,
			ClassName,
			m_strWindowTitle,
			m_dwWindowStyle,
			0,
			0,
			rc.right - rc.left,
			rc.bottom - rc.top,
			0,
			0,
			hInstance,
			0);
	}

	hWndMain = m_hWnd;

	if (!BASE_InitializeBaseDef())
	{
		MessageBoxA(m_hWnd, "Initialize Data Failed", "Error", 0);
		LOG_WRITELOGSTRING("Initialize Data Failed\r\n");
		return 0;
	}

	ReadItemicon();
	ReadItemName();
	ReadUIString();
	BASE_ReadItemPrice();

	m_pAviPlayer = new TMVideoWnd(m_bwFullScreen);

	if (m_pAviPlayer != nullptr)
	{
		if (!m_pAviPlayer->OpenClip(VideoClipFile_Path))
		{
			SAFE_DELETE(m_pAviPlayer);
		}
	}

	memset(g_pItemHelp, 0, sizeof(g_pItemHelp));
	char szItemHelpFile[128];
	sprintf(szItemHelpFile, ItemHelp_Path);

	remove(ChangeUpdate_Path);

	MixHelp();

	fopen_s(&fp, szItemHelpFile, "rt");

	if (fp == nullptr)
	{
		MessageBoxA(m_hWnd, "Can't open itemhelp.dat", "Error", 0);
		return 0;
	}

	char szCol[8]{};
	char szTemp[256]{};

	int NumHelp = 0;
	int ItemIndex = 0;
	int Color = 0;

	while (NumHelp < 6500)
	{
		for (int j = 0; j < 10 && fgets(szTemp, 256, fp); ++j)
		{
			if (j == 0)
			{
				sscanf(szTemp, "%d", &ItemIndex);
			}
			else
			{
				memset(szCol, 0, 8);
				strncpy(szCol, szTemp, 6);
				sscanf(szCol, "%x", &Color);
				char* szRet = strstr(szTemp, "\n");
				if (szRet)
					*szRet = 0;
				if (szTemp[8] == '\t' || szTemp[8] == ' ')
					sprintf(g_pItemHelp[ItemIndex].Help[j - 1], "%s", &szTemp[9]);

				g_pItemHelp[ItemIndex].Color[j - 1] = static_cast<short>(Color);
			}
		}
		++NumHelp;
	}

	fclose(fp);

	if (m_pAviPlayer)
		return 1;
	else
		return InitDevice();

	return 0;
 }

HRESULT NewApp::InitDevice()
{
	m_pRenderDevice = new RenderDevice(m_dwScreenWidth, m_dwScreenHeight, m_dwColorBit, m_bwFullScreen);

	if (m_bwFullScreen)
		m_pRenderDevice->SetWindowedFullScreen();

	if (!m_pRenderDevice->Initialize(m_hWnd))
	{
		MessageBoxA(m_hWnd, "Initialize Render Failed.", "Error", 0);
		LOG_WRITELOGSTRING("Initialize Render Failed\r\n");
		// todo: release the m_prenderdevice?
		return 0;
	}

	if (m_nSound > 0)
	{
		InitMusicList();

		m_pSoundManager = new CSoundManager();

		if (FAILED(m_pSoundManager->Initialize(m_hWnd, 2, 2, 0x5622, 0x10)))
		{
			LOG_WRITELOG("Initialize Sound Failed\r\n");
			SAFE_DELETE(m_pSoundManager);
		}

		int nVolume = 25 * m_nSound - 2500;
		if (nVolume > 0)
			nVolume = 0;
		if (nVolume < -2500)
			nVolume = -2500;

		m_pSoundManager->SetSoundVolume(nVolume);
		m_pSoundManager->LoadSoundData();
	}

	if (m_nMusic > 0)
	{
		m_pBGMManager = new DS_SOUND_MANAGER(1, 30 * m_nMusic - 3000);
		g_pApp->m_pBGMManager->SetVolume(0, g_pApp->m_pBGMManager->m_lBGMVolume);
	}

	m_pEventTranslator = new EventTranslator();
	if (!m_pEventTranslator->Initialize(m_hWnd))
	{
		LOG_WRITELOG("Initialize Interface Failed");
		return 0;
	}

	if (!m_pEventTranslator->InitializeIME())
	{
		LOG_WRITELOG("Initialize IME Failed");
		return 0;
	}

	m_pTimerManager = new TimerManager();

	m_pObjectManager = new ObjectManager();
	if (m_pObjectManager != nullptr)
	{
		m_pObjectManager->InvalidateDeviceObjects();
		m_pObjectManager->RestoreDeviceObjects();
	}

	if (m_pTimerManager != nullptr)
		m_pTimerManager->StartTimer();

	m_pSocketManager = new CPSock();

	if (!m_pSocketManager->WSAInitialize())
	{
		LOG_WRITELOG("Initialize Socket Failed");
		return 0;
	}
	g_pSocketManager = m_pSocketManager;
	g_LoginSocket = new CPSock();
	g_pTimerManager->SetServerTime(0);

	m_bActive = 1;

	int nMipMap;
	if (m_pRenderDevice->m_pd3dDevice->GetAvailableTextureMem() > 64)
	{
		nMipMap = D3DDevice::m_nMipMap;
	}
	else if (m_pRenderDevice->m_pd3dDevice->GetAvailableTextureMem() > 56 && D3DDevice::m_nMipMap > 20)
	{
		nMipMap = 20;
	}
	else if (m_pRenderDevice->m_pd3dDevice->GetAvailableTextureMem() > 48 && D3DDevice::m_nMipMap > 10)
	{
		nMipMap = 10;
	}
	else
	{
		nMipMap = 0;
	}

	D3DDevice::m_nMipMap = nMipMap;

	m_pBlur = new JBlur();

	return m_pBlur->InitObject() != 0;
}

void NewApp::InitServerName()
{
	int nTempList[11];
	memset(g_szServerNameList, 0, sizeof(g_szServerNameList));
	memset(g_nServerCountList, 0, sizeof(g_nServerCountList));
	memset(nTempList, 0, sizeof(nTempList));

	FILE* fpBin = nullptr;
	fopen_s(&fpBin, ServerName_Path, "rb");
	if (fpBin)
	{
		fread(g_szServerNameList, 1, sizeof(g_szServerNameList), fpBin);
		fread(g_nServerCountList, 1, sizeof(g_nServerCountList), fpBin);
		fclose(fpBin);
	}
}

void NewApp::InitMusicList()
{
	FILE* fp = nullptr;
	fopen_s(&fp, MusicConfig_Path, "rt");

	if (fp == nullptr)
		return;

	char szTemp1[256];
	for (int i = 0; i < 15 && fgets(szTemp1, 256, fp); ++i)
	{
		char szTemp2[256];

		strcpy(szTemp2, &szTemp1[17]);
		int nLen = strlen(szTemp2);

		if (szTemp1[nLen + 255] == '\n' || szTemp1[nLen + 255] == '\r')
		{
			szTemp2[nLen - 1] = 0;
		}
		if (szTemp1[nLen + 254] == '\n' || szTemp1[nLen + 254] == '\r')
		{		
			szTemp2[nLen - 2] = 0;
		}

		sprintf(DS_SOUND_MANAGER::m_szMusicPath[i], szTemp2);
	}

	fclose(fp);

	sprintf(DS_SOUND_MANAGER::m_szMusicPathOrigin[14], DSSound_1_Path);
	sprintf(DS_SOUND_MANAGER::m_szMusicPathOrigin[13], DSSound_2_Path);
}

HRESULT NewApp::Finalize()
{
	for (int nCount = 0; nCount < 100; ++nCount)
	{
		free(MeshManager::m_BoneAnimationList[nCount].pBone);
		free(MeshManager::m_BoneAnimationList[nCount].matAnimation);
		free(MeshManager::m_BoneAnimationList[nCount].matQuaternion);
	}
	
	SAFE_DELETE(g_pObjectManager);
	SAFE_DELETE(m_pTimerManager);
	SAFE_DELETE(m_pRenderDevice);
	SAFE_DELETE(m_pSoundManager);
	SAFE_DELETE(m_pSocketManager);
	SAFE_DELETE(m_pBGMManager);
	SAFE_DELETE(m_pAviPlayer);
	SAFE_DELETE(m_pEventTranslator);

	g_pSocketManager = nullptr;
	DeleteObject(m_hBMBtnBG);

	return 1;
}

DWORD NewApp::Run()
{
	HACCEL hAccel = LoadAccelerators(0, MAKEINTRESOURCE(IDC_TMPROJECT));

	MSG msg;
	PeekMessage(&msg, 0, 0, 0, 0);
	while (msg.message != WM_QUIT)
	{
		int bGotMsg = 0;
		if (!m_bActive)
			bGotMsg = GetMessage(&msg, 0, 0, 0);
		else
			bGotMsg = PeekMessage(&msg, 0, 0, 0, PM_REMOVE);

		if (bGotMsg == 1)
		{
			if (!hAccel || !m_hWnd || TranslateAccelerator(m_hWnd, hAccel, &msg) == 0)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (m_bActive == 1)
			{
				unsigned int dwServerTime = m_pTimerManager->GetServerTime();

				m_pEventTranslator->ReadInputEventData();
				m_pEventTranslator->CameraEventData();

				m_pObjectManager->FrameMove(dwServerTime);

				if (g_dwStartPlayTime != 0 && g_dwPausedTime == 0)
				{
					if (g_nDumpPacketSize > g_nCurrentPos)
					{
						unsigned int dwTermTime = 0;
						memcpy((char*)&dwTermTime, &g_pDumpPacket[g_nCurrentPos], 4);
						if (dwServerTime > g_dwStartPlayTime + dwTermTime)
						{
							g_nCurrentPos += 4;
							MSG_STANDARD* pStd = (MSG_STANDARD*)&g_pDumpPacket[g_nCurrentPos];
							m_pObjectManager->OnPacketEvent(
								*(unsigned short*)&g_pDumpPacket[g_nCurrentPos + 4],
								&g_pDumpPacket[g_nCurrentPos]);
							g_nCurrentPos += pStd->Size;
						}
					}
					else
					{
						g_dwStartPlayTime = 0;
						g_pCurrentScene->m_pMessagePanel->SetMessage("End Replay", 4000);
						g_pCurrentScene->m_pMessagePanel->SetVisible(1, 1);
						g_pCurrentScene->m_pMyHuman->m_cHide = 0;
					}
				}
				if (m_pAviPlayer == nullptr || m_pAviPlayer != nullptr && m_pAviPlayer->m_psCurrent != PLAYSTATE::Running)
				{
					RenderScene();
				}
				if ((m_pAviPlayer == nullptr || m_pAviPlayer != nullptr && m_pAviPlayer->m_psCurrent != PLAYSTATE::Running) &&
					m_pRenderDevice->m_pMeshManager == nullptr)
				{
					if (!m_pRenderDevice->InitMeshManager())
					{
						MessageBoxA(m_hWnd, "Game data crashed. Install game again.", "Error", MB_SYSTEMMODAL);
						PostMessageA(m_hWnd, WM_CLOSE, 0, 0);
					}

					SAFE_DELETE(m_pAviPlayer);

					m_pObjectManager->SetCurrentState(ObjectManager::TM_GAME_STATE::TM_SELECTSERVER_STATE);
				}
				if (m_pObjectManager->m_bCleanUp)
					m_pObjectManager->CleanUp();
			}
		}		
	}

	if (hAccel)
		DestroyAcceleratorTable(hAccel);

	return msg.wParam;
}

void NewApp::OnCreate(HWND hWnd, DWORD wParam, int lParam)
{
	m_hBMBtnBG = LoadBitmap(g_hInstance, (LPCSTR)0xAB);
}

HRESULT NewApp::RenderScene()
{
	HRESULT hr = m_pRenderDevice->m_pd3dDevice->TestCooperativeLevel();
	if (FAILED(hr) && hr == D3DERR_DEVICELOST)
		return 1;

	m_pRenderDevice->SetViewPort(0, 0, m_dwScreenWidth, m_dwScreenHeight);

	m_pRenderDevice->Lock(1);

	TMCamera* pCamera = m_pObjectManager->m_pCamera;
	TMVector3 vecLookAt = pCamera->GetCameraLookatPos();

	m_pRenderDevice->SetViewVector(pCamera->m_cameraPos, vecLookAt);
	m_pRenderDevice->SetRenderStateBlock(1);
	m_pObjectManager->RenderObject();
	m_pRenderDevice->SetRenderStateBlock(3);
	m_pObjectManager->RenderControl();
	m_pRenderDevice->Unlock(1);

	if (g_pTextureManager)
		g_pTextureManager->ReleaseNotUsingTexture();
	if (g_pMeshManager)
		g_pMeshManager->ReleaseNotUsingMesh();

	return 1;
}

void NewApp::SetObjectManager(ObjectManager* pManager)
{
	m_pObjectManager = pManager;
	g_pObjectManager = m_pObjectManager;
}

EventTranslator* NewApp::GetEventTranslator()
{
	return m_pEventTranslator;
}

HWND NewApp::GetSafeHwnd()
{
	return m_hWnd;
}

void NewApp::SwitchWebBrowserState(int nEmptyCargo)
{
}

void NewApp::SwitchWebBoard()
{
}

DWORD NewApp::GetHttpRequest(char* httpname, char* Request, int MaxBuffer)
{
	HINTERNET m_Session = InternetOpen("MS", 0, 0, 0, 0);
	HINTERNET hHttpFile = InternetOpenUrl(m_Session, httpname, 0, 0, 0x4000000, 0);

	if (hHttpFile)
	{
		DWORD dwBytesRead = 0;
		InternetReadFile(hHttpFile, Request, MaxBuffer, &dwBytesRead);
		InternetCloseHandle(hHttpFile);
		Request[dwBytesRead] = 0;
		InternetCloseHandle(m_Session);
		return 1;
	}
	else
	{
		GetLastError();
		InternetCloseHandle(m_Session);	
	}

	return 0;
}

void NewApp::MixHelp()
{
	memset(g_pItemMixHelp, 0, sizeof(g_pItemMixHelp));
	char szItemHelpFile[128];
	sprintf(szItemHelpFile, MixHelp_Path);

	FILE* fp = nullptr;
	fopen_s(&fp, szItemHelpFile, "rt");

	if (fp == nullptr)
		return;

	int NumHelp = 10000;
	int ItemIndex = 0;
	int Icon = 0;
	int Color = 0;
	char Name[256]{};

	while (NumHelp < 11500)
	{
		char szTemp[256];
		for (int j = 0; j < 10 && fgets(szTemp, 256, fp); ++j)
		{
			if (j == 0)
			{
				sscanf(szTemp, "%s %d %d", Name, &ItemIndex, &Icon);
				continue;
			}
			
			char szCol[7];
			memset(szCol, 0, 7);
			strncpy(szCol, szTemp, 6u);
			sscanf(szCol, "%d", &Color);
			char* szRet = strstr(szTemp, "\n");
			if (szRet)
				*szRet = 0;

			if (szTemp[8] == '\t' || szTemp[8] == ' ')
				sprintf(g_pItemMixHelp[ItemIndex].Help[j - 1], "%s", &szTemp[9]);

			g_pItemMixHelp[ItemIndex].Color[j - 1] = Color;
			g_pItemMixHelp[ItemIndex].Icon = Icon;
			strcpy(g_pItemMixHelp[ItemIndex].Name, Name);
		}

		++NumHelp;
	}

	fclose(fp);
}

int NewApp::BASE_Initialize_NewServerList()
{
	return 1;
}

void NewApp::InitServerNameMR()
{
}

HRESULT NewApp::MsgProc(HWND hWnd, DWORD uMsg, DWORD wParam, int lParam)
{
	switch (uMsg)
	{
	case WM_SETCURSOR:
			return 0;
	case WM_MOUSEMOVE:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	{
		if (SCursor::m_nCursorType == 0)
		{
			SetCursor(0);
		}
		else if (SCursor::m_nCursorType == 2 && g_pCursor)
		{
			if (g_pCursor->m_GCPanel.nTextureIndex == 0)
				SetCursor(SCursor::m_hCursor1);
			else if(g_pCursor->m_GCPanel.nTextureIndex == 1)
				SetCursor(SCursor::m_hCursor2);
		}

		if (m_pEventTranslator != nullptr)
			m_pEventTranslator->OnMouseEvent(uMsg, wParam, LOWORD(lParam), HIWORD(lParam));		
	}
	break;
	case WM_DRAWITEM:
	{
		LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;
		HDC hdcMem = CreateCompatibleDC(lpdis->hDC);

		HBITMAP hOldBitMap = nullptr;
		hOldBitMap = (HBITMAP)SelectObject(hdcMem, m_hBMBtnBG);

		StretchBlt(
			lpdis->hDC,
			lpdis->rcItem.left,
			lpdis->rcItem.top,
			lpdis->rcItem.right - lpdis->rcItem.left,
			lpdis->rcItem.bottom - lpdis->rcItem.top,
			hdcMem,
			0,
			0,
			86,
			21,
			0x0CC0020);

		SelectObject(hdcMem, hOldBitMap);
		DeleteDC(hdcMem);
	}
	break;
	case WM_INPUTLANGCHANGE:
	{
		char szDesc[256]{};
		GetKeyboardLayoutName(szDesc);

		if (!strncmp(szDesc, "0000", 4))
		{
			if (g_pCurrentScene != nullptr)
			{
				static_cast<TMFieldScene*>(g_pCurrentScene)->m_pAlphaNative->SetText((char*)"EN", 0);
				static_cast<TMFieldScene*>(g_pCurrentScene)->m_pTextIMEDesc->SetVisible(0);
			}
		}
		else if (m_pEventTranslator != nullptr)
		{
			if (g_pCurrentScene->m_pControlContainer->m_pFocusControl != nullptr &&
				g_pCurrentScene->m_pControlContainer->m_pFocusControl->m_eCtrlType == CONTROL_TYPE::CTRL_TYPE_EDITABLETEXT)
			{
				m_pEventTranslator->SetIMENative();
				int bNative = m_pEventTranslator->IsNative();

				if (g_pCurrentScene != nullptr)
				{
					if (bNative != 0)
					{
						static_cast<TMFieldScene*>(g_pCurrentScene)->m_pAlphaNative->SetText((char*)"Ch", 0);
						HKL hkl = GetKeyboardLayout(0);

						char dst[256]{};
						ImmGetDescription(hkl, dst, 256);

						static_cast<TMFieldScene*>(g_pCurrentScene)->m_pTextIMEDesc->SetText(dst, 0);
						static_cast<TMFieldScene*>(g_pCurrentScene)->m_pTextIMEDesc->SetSize((float)(strlen(dst) * 8), 16.0f);
						static_cast<TMFieldScene*>(g_pCurrentScene)->m_pTextIMEDesc->SetVisible(1);
					}
					else
					{
						static_cast<TMFieldScene*>(g_pCurrentScene)->m_pAlphaNative->SetText((char*)"EN", 0);
						static_cast<TMFieldScene*>(g_pCurrentScene)->m_pTextIMEDesc->SetVisible(0);
					}
				}

				if (!strcmp(static_cast<TMFieldScene*>(g_pCurrentScene)->m_pTextIMEDesc->GetText(), "Î"))
					SendMessage(hWnd, 0x281, 0, -1073741809);
				else
					SendMessage(hWnd, 0x281u, 0, -1);
			}
		}
	}
	break;
	case WM_KEYDOWN:
	{
		if (m_pAviPlayer != nullptr && m_pAviPlayer->m_psCurrent == PLAYSTATE::Running)
		{
			m_pAviPlayer->CloseClip();
			SAFE_DELETE(m_pAviPlayer);
			InitDevice();
		}

		if (m_pEventTranslator == nullptr)
			break;

		WORD sVal = GetKeyState(VK_CONTROL);
		m_pEventTranslator->m_bCtrl = (int)sVal >> 8 > 0;
		WORD sVal2 = GetKeyState(VK_SHIFT);
		m_pEventTranslator->m_bShift = (int)sVal2 >> 8 > 0;

		if (wParam != VK_CONTROL && g_pCurrentScene != nullptr && m_pEventTranslator->m_bCtrl != 0)
		{
			if (wParam == VK_OEM_MINUS || wParam == VK_SUBTRACT)
			{
				g_pCurrentScene->OnAccel(40048);
				break;
			}
			else if (wParam == VK_OEM_PLUS || wParam == VK_ADD)
			{
				g_pCurrentScene->OnAccel(40047);
				break;
			}
			else if (wParam == VK_OEM_4)
			{
				g_pCurrentScene->OnAccel(40027);
				break;
			}
			else if (wParam == VK_OEM_6)
			{
				g_pCurrentScene->OnAccel(40028);
				break;
			}
			else if (wParam == VK_OEM_7)
			{
				g_pCurrentScene->OnAccel(40029);
				break;
			}
		}

		m_pEventTranslator->OnKeyDown(wParam);
	}
	break;
	case WM_KEYUP:
	{
		if (m_pEventTranslator == nullptr)
			break;

		if (wParam == VK_SNAPSHOT)
			m_pRenderDevice->CaptureScreen();

		WORD sVal = GetKeyState(VK_CONTROL);
		m_pEventTranslator->m_bCtrl = (int)sVal >> 8 > 0;
		WORD sVal2 = GetKeyState(VK_SHIFT);
		m_pEventTranslator->m_bShift = (int)sVal2 >> 8 > 0;

		m_pEventTranslator->OnKeyUp(wParam);
	}
	break;
	case WM_CHAR:
	{
		if (m_pEventTranslator != nullptr && !m_pEventTranslator->m_bCtrl)
			m_pEventTranslator->OnChar(static_cast<char>(wParam), static_cast<char>(lParam));
	}
	break;
	case WM_SYSKEYDOWN:
	{
		if (wParam == VK_MENU)
		{
			if (!g_nKeyType && m_pEventTranslator != nullptr)
				m_pEventTranslator->m_bAlt = 1;
		}
		else if (wParam == VK_F10 && m_pEventTranslator != nullptr)
		{
			m_pEventTranslator->OnKeyDown(VK_F10);
		}
	}
	break;
	case WM_SYSKEYUP:
	{
		if (wParam == VK_MENU && !g_nKeyType && m_pEventTranslator != nullptr)
		{
			m_pEventTranslator->m_bAlt = 0;
		}
		else if (wParam == VK_F10 && m_pEventTranslator != nullptr)
		{
			m_pEventTranslator->OnKeyUp(VK_F10);
		}
	}
	break;
	case WM_IME_ENDCOMPOSITION:
	{
		if (m_pEventTranslator == nullptr)
			break;

		m_pEventTranslator->SetVisibleCandidateList(lParam, 0);
		static_cast<TMFieldScene*>(g_pCurrentScene)->m_pTextCompose->SetVisible(0);
		static_cast<TMFieldScene*>(g_pCurrentScene)->m_pTextComposeB->SetVisible(0);
	}
	break;
	case WM_IME_COMPOSITION:
	{
		if (m_pEventTranslator == nullptr)
			break;

		m_pEventTranslator->OnIME(static_cast<char>(wParam), static_cast<char>(lParam));
	}
	break;
	case WM_COMMAND:
	{
		if (wParam == 999)
		{
			// SwitchWebBrowserState
			break;
		}

		int msg = wParam;
		HWND hWndFocus = GetFocus();

		if (hWndFocus != g_pApp->m_hWnd)
		{
			switch (msg)
			{
			case 40086:
				PostMessageA(hWndFocus, 0x301, 0, 0);
				return 1;
			case 40100:
				PostMessageA(hWndFocus, 0x302, 0, 0);
				return 1;
			case 40102:
				PostMessageA(hWndFocus, 0x300, 0, 0);
				return 1;
			}
		}

		if (g_pCurrentScene != nullptr)
			g_pCurrentScene->OnAccel(msg);
	}
	break;
	case WM_SYSCOMMAND:
	{
		switch (wParam)
		{
		case 0xF100u:
			SendMessageA(hWnd, 0x100, 0xA4, 0);
			return 0;
		case 0xF020u:
			g_pApp->m_Winstate = 0;
			break;
		case 0xF030u:
			g_pApp->m_Winstate = 1;
			break;
		}
	}
	break;
	case WM_IME_SETCONTEXT:
	{
		return DefWindowProc(hWnd, uMsg, lParam == -1, -2147483634);
	}
	break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
	{
		if (m_pAviPlayer != nullptr && m_pAviPlayer->m_psCurrent == PLAYSTATE::Running)
		{
			m_pAviPlayer->CloseClip();
			SAFE_DELETE(m_pAviPlayer);
			InitDevice();
		}
	}
	break;
	case WM_USER + 13:
	{
		if (m_pAviPlayer == nullptr)
			break;

		if (m_pAviPlayer->HandleGraphEvent() == 1)
		{
			SAFE_DELETE(m_pAviPlayer);
			InitDevice();
		}
		if (!m_bwFullScreen && m_pAviPlayer != nullptr)
			m_pAviPlayer->MoveVideoWindow();
	}
	break;
	case WM_IME_NOTIFY:
	{
		// stuffs for china
	}
	break;
	case WM_USER + 1:
	{
		if (g_LoginSocket == nullptr)
			break;

		if (lParam != 1)
		{
			g_LoginSocket->CloseSocket();
			m_pObjectManager->OnPacketEvent(0, nullptr);
			break;
		}

		if (!g_LoginSocket->Receive())
		{
			g_LoginSocket->CloseSocket();
			break;
		}

		int Error = 0;
		int nType = 0;
		while (1)
		{
			char* Msg = g_LoginSocket->ReadMessage(&Error, &nType);

			if (Msg == nullptr || Error != 0)
				break;

			MSG_STANDARD* pStd = (MSG_STANDARD*)Msg;

			unsigned int dwServerTime = m_pTimerManager->GetServerTime();
			g_dwServerTime = pStd->Tick;
			g_dwClientTime = dwServerTime / 1000;

			if (g_hPacketDump != nullptr)
			{
				unsigned int dwTermTime = dwServerTime - g_dwStartPacketTime;
				fwrite(&dwTermTime, 4, 1, g_hPacketDump);
				fwrite(pStd, pStd->Size, 1, g_hPacketDump);
			}

			if (dwServerTime > g_pLastFixTime + 10000)
			{
				if (g_pCurrentScene != nullptr && g_pCurrentScene->m_nAdjustTime != 0)
				{
					if (g_dwServerTime > dwServerTime + 500)
					{
						m_pTimerManager->SetServerTime(dwServerTime + 85);
					}
					else if (g_dwServerTime < dwServerTime - 500)
					{
						m_pTimerManager->SetServerTime(dwServerTime - 85);
					}
				}
				g_pLastFixTime = dwServerTime;
			}
			m_pObjectManager->OnPacketEvent(pStd->Type, Msg);
		}
	}
	break;
	case WM_USER + 100:
	{
		if (m_pSocketManager == nullptr)
			break;

		if (lParam != 1)
		{
			m_pSocketManager->CloseSocket();
			m_pObjectManager->OnPacketEvent(0, nullptr);
			break;
		}
		if (!m_pSocketManager->Receive())
		{
			m_pSocketManager->CloseSocket();
			break;
		}

		int ErrorCode = 0;
		int ErrorType = 0;
		while (1)
		{
			char* Msg = m_pSocketManager->ReadMessage(&ErrorCode, &ErrorType);

			if (Msg == nullptr || ErrorCode != 0)
				break;

			MSG_STANDARD* pStd = (MSG_STANDARD*)Msg;

			unsigned int dwServerTime = m_pTimerManager->GetServerTime();
			g_dwServerTime = pStd->Tick;
			g_dwClientTime = dwServerTime / 1000;

			if (g_hPacketDump != nullptr)
			{
				unsigned int dwTermTime = dwServerTime - g_dwStartPacketTime;
				fwrite(&dwTermTime, 4, 1, g_hPacketDump);
				fwrite(pStd, pStd->Size, 1, g_hPacketDump);
			}

			if (dwServerTime > g_pLastFixTime + 10000)
			{
				if (g_pCurrentScene != nullptr && g_pCurrentScene->m_nAdjustTime != 0)
				{
					if (g_dwServerTime > dwServerTime + 500)
					{
						m_pTimerManager->SetServerTime(dwServerTime + 85);
					}
					else if (g_dwServerTime < dwServerTime - 500)
					{
						m_pTimerManager->SetServerTime(dwServerTime - 85);
					}
				}
				g_pLastFixTime = dwServerTime;
			}
			m_pObjectManager->OnPacketEvent(pStd->Type, Msg);
		}
	}
	break;
	case WM_USER + 101:
	{
		m_pBGMManager->OnEvent();
	}
	break;
	case WM_CREATE:
	{
		OnCreate(hWnd, wParam, lParam);
	}
	break;
	case WM_DESTROY:
	case 4:
		break;
	case WM_MOVE:
	case WM_SIZE:
	{
		if (m_pAviPlayer != nullptr)
			m_pAviPlayer->MoveVideoWindow();
	}
	break;
	case WM_ACTIVATE:
	{
		if (g_pCurrentScene != nullptr)
		{
			if (strcmp(g_pCurrentScene->m_pTextIMEDesc->GetText(), "Î"))
				SendMessageA(hWnd, 0x281, 0, -1073741809);
			else
				SendMessageA(hWnd, 0x281, 0, -1);
		}
		if (wParam != 0)
		{
			if (m_pEventTranslator != nullptr)
				m_pEventTranslator->m_bAlt = 0;
			if (m_pBGMManager != nullptr)
				m_pBGMManager->SetVolume(0, m_pBGMManager->m_lBGMVolume);

			g_pApp->m_binactive = 1;
		}
		else if (!g_bEndGame && m_pRenderDevice != nullptr && m_bwFullScreen == 1)
		{
			ShowWindow(hWnd, 3);
		}
		else if (!g_bEndGame && m_pRenderDevice != nullptr && m_bwFullScreen == 1)
		{
			CloseWindow(hWnd);
		}
		else
		{
			if (m_pEventTranslator)
				m_pEventTranslator->m_bAlt = 0;
			if (m_pBGMManager)
				m_pBGMManager->SetVolume(0, -10000);
			g_pApp->m_binactive = 0;
		}
	}
	break;
	case WM_CLOSE:
	{
		if (g_pCurrentScene != nullptr && g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
		{
			if (g_dwStartQuitGameTime == 0)
			{
				g_dwStartQuitGameTime = m_pTimerManager->GetServerTime();
				MSG_STANDARDPARM stDelayStart{};
				stDelayStart.Header.ID = g_pCurrentScene->m_pMyHuman->m_dwID;
				stDelayStart.Header.Type = 942;
				stDelayStart.Parm = 0;

				g_pSocketManager->SendOneMessage((char*)&stDelayStart, sizeof(stDelayStart));
				return 0;
			}

			if (m_pTimerManager->GetServerTime() < g_dwStartQuitGameTime + 3000)
				return 0;
		}

		Finalize();
		if (g_hPacketDump != nullptr)
		{
			fclose(g_hPacketDump);
			g_hPacketDump = nullptr;
		}

		LOG_FINALIZELOG(); //Added this to finalize log file write?
		g_bEndGame = 1;
		EnableSysKey();
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		g_dwStartQuitGameTime = 0;
		return 0;
	}
	break;
	default:
		break;
	}

	if (m_pAviPlayer != nullptr)
	{
		if (m_pAviPlayer->m_pVW != nullptr)
			m_pAviPlayer->m_pVW->NotifyOwnerMessage((OAHWND)hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool NewApp::CheckResolution(DWORD x, DWORD y, DWORD bpp)
{
	int iModeNum = 0;
	DEVMODE devMode;
	for (int bResult = EnumDisplaySettings(0, 0, &devMode); bResult; bResult = EnumDisplaySettings(0, iModeNum, &devMode))
	{
		if (devMode.dmPelsWidth == x && devMode.dmPelsHeight == y && devMode.dmBitsPerPel == bpp)
			return true;

		++iModeNum;
	}

	return false;
}

char NewApp::base_chinaTid(char* TID, char* Id)
{
	return 0;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
#if !defined(_DEBUG)
	if (FindWindow(0, ClassName))
		return 0;
#endif

	char* szArgument = GetCommandLine();
	if (CheckOS())
		sprintf(g_szOS, "98");
	else
		sprintf(g_szOS, "NT");

	NewApp* newApp = new NewApp();

	int nFull = 1;
	char szDesc[256]{};
	GetKeyboardLayoutName(szDesc);
	
	if (!strcmp((const char*)lpCmdLine, "/w"))
		nFull = 0;

	// ?:????????????? KKKKKKKKKKKKKKKKKKKKKKKK
	//if (j___stricmp(lpCmdLine, "China No.1 It is TM Launcher"))
		//return 0;

	if (!ReadNameFiltraDataBase())
	{
		MessageBoxA(0, "Need System File", "WYD", 0);
		return 0;
	}
	else if (!ReadChatFiltraDataBase())
	{
		MessageBoxA(0, "Need System File", "WYD", 0);
		return 0;
	}
	else if (newApp->Initialize(hInstance, nFull))
	{
		DisableSysKey();

		int nResult = newApp->Run();
		if (newApp)
			delete newApp;

		return nResult;
	}

	return 0;
}

void CreateConsole()
{
	AllocConsole();

	// Output fix 
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
}
