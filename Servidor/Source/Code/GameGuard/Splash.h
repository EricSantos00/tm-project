
#ifndef _ABHI_SPLASH_H_
#define _ABHI_SPLASH_H_

#include "windows.h"

class CSplash
{
public:
   
    CSplash();
    CSplash(LPCTSTR lpszFileName, COLORREF colTrans);  
    virtual ~CSplash();
    void ShowSplash();
    int DoLoop();
    int CloseSplash();
    DWORD SetBitmap(LPCTSTR lpszFileName);
    DWORD SetBitmap(HBITMAP hBitmap);
	bool SetTransparentColor(COLORREF col);
	LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	HWND m_hwnd;

private:
    void Init();
    void  OnPaint(HWND hwnd);
    bool MakeTransparent();
    HWND RegAndCreateWindow();
    COLORREF m_colTrans;
    DWORD m_dwWidth;
    DWORD m_dwHeight;
    void FreeResources();
    HBITMAP m_hBitmap;
    LPCTSTR m_lpszClassName;
};

#endif 