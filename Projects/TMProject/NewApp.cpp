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

NewApp::NewApp()
{
}

NewApp::~NewApp()
{
}

HRESULT NewApp::Initialize(HINSTANCE hInstance, int nFull)
{
	return E_NOTIMPL;
}

HRESULT NewApp::InitDevice()
{
	return E_NOTIMPL;
}

void NewApp::InitServerName()
{
}

void NewApp::InitMusicList()
{
}

HRESULT NewApp::Finalize()
{
	return E_NOTIMPL;
}

DWORD NewApp::Run()
{
	return 0;
}

void NewApp::OnCreate(HWND hWnd, DWORD wParam, int lParam)
{
}

HRESULT NewApp::RenderScene()
{
	return E_NOTIMPL;
}

void NewApp::SetObjectManager(ObjectManager* pManager)
{
}

EventTranslator* NewApp::GetEventTranslator()
{
	return nullptr;
}

HWND NewApp::GetSafeHwnd()
{
	return HWND();
}

void NewApp::SwitchWebBrowserState(int nEmptyCargo)
{
}

void NewApp::SwitchWebBoard()
{
}

DWORD NewApp::GetHttpRequest(char* httpname, char* Request, int MaxBuffer)
{
	return 0;
}

void NewApp::MixHelp()
{
}

int NewApp::BASE_Initialize_NewServerList()
{
	return 0;
}

void NewApp::InitServerNameMR()
{
}

HRESULT NewApp::MsgProc(HWND hWnd, DWORD uMsg, DWORD wParam, int lParam)
{
	return E_NOTIMPL;
}

HRESULT NewApp::CheckResolution(DWORD x, DWORD y, DWORD bpp)
{
	return E_NOTIMPL;
}

char NewApp::base_chinaTid(char* TID, char* Id)
{
	return 0;
}
