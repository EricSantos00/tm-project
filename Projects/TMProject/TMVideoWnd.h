#pragma once

#include <control.h>
#include <strmif.h>

enum class PLAYSTATE
{
	Stopped = 0x0,
	Paused = 0x1,
	Running = 0x2,
	Init = 0x3,
};

class TMVideoWnd
{
public:
	TMVideoWnd(int bFull);
	virtual ~TMVideoWnd();

	HRESULT PlayMovieInWindow(char* szFile);
	HRESULT InitVideoWindow();
	void MoveVideoWindow();
	void CheckVisibility();
	int OpenClip(const char* szFilename);
	void CloseClip();
	void CloseInterfaces();
	HRESULT ToggleFullScreen();
	int HandleGraphEvent();

public:
	char m_szFileName[260];
	int m_bFullscreen;
	PLAYSTATE m_psCurrent;
	IGraphBuilder* m_pGB;
	IMediaControl* m_pMC;
	IMediaEventEx* m_pME;
	IVideoWindow* m_pVW;
	IBasicVideo* m_pBV;
};