#pragma once

#include <dinput.h>

class IEventListener
{
public:
	virtual int OnControlEvent(DWORD idwControlID, DWORD idwEvent) = 0;
};

class EventTranslator
{
public:
	EventTranslator();
	virtual ~EventTranslator();

	BOOL Initialize(HWND hWnd);
	int InitializeIME();
	int InitializeInputDevice(HWND hWnd);

	void Finalize();
	void FinalizeIME();

	BOOL IsNative();

	void SetIMENative();
	void SetIMEAlphaNumeric();
	void SetIMEOpenStatus(int bOpen);

	int IsIMEOpenStatus();
	void SetVisibleCandidateList(int lParam, int bVisible);

	void Lock();
	void Unlock();

	int ReadInputEventData();
	int CameraEventData();

	void OnKeyDown(unsigned int iKeyCode);
	void OnKeyUp(unsigned int iKeyCode);
	void OnChar(char iCharCode, int lParam);
	void OnIME(char iCharCode, int lParam);
	void OnIME2();

	void UpdateCompositionPos();

	void OnLMousePressed();
	void OnLMouseReleased();
	void OnRMousePressed();
	void OnRMouseReleased();
	void OnMouseEvent(unsigned int nFlags, unsigned int wParam, int ix, int iy);

private:	
	IDirectInput8* m_pDI;
	IDirectInputDevice8* m_pMouseDevice;

public:
	int dx;
	int dy;
	int wheel;
	int viewchange;
	int button[3];
	int lastButtonState[3];
	int m_bKey[256];
	int m_bAlt;
	int m_bCtrl;
	int m_bRBtn;
	int m_bShift;
	HWND m_hWnd;
	int m_bLock;
	unsigned int m_wParam;
	HIMC m_hOldIMC;
	char m_strComp[512];
	char m_szResultStr[512];
	char m_bCompAttr[512];
	unsigned int m_dwCompAttrLen;
	LPCANDIDATELIST m_lpCandList;
};