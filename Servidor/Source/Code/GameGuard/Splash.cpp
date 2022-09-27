
#include "splash.h"
#include "windowsx.h"

typedef BOOL (WINAPI *lpfnSetLayeredWindowAttributes)
        (HWND hWnd, COLORREF cr, BYTE bAlpha, DWORD dwFlags);

lpfnSetLayeredWindowAttributes g_pSetLayeredWindowAttributes;

#define WS_EX_LAYERED 0x00080000 

static LRESULT CALLBACK ExtWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static CSplash * spl = NULL;
    if(uMsg == WM_CREATE)
    {
        spl = (CSplash*)((LPCREATESTRUCT)lParam)->lpCreateParams;
    }
    if(spl)
        return spl->WindowProc(hwnd, uMsg, wParam, lParam);
    else
        return DefWindowProc (hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK CSplash::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
    }

    return DefWindowProc (hwnd, uMsg, wParam, lParam) ;
}

void CSplash:: OnPaint(HWND hwnd)
{
    if (!m_hBitmap)
        return;

    PAINTSTRUCT ps ;
    HDC hDC = BeginPaint (hwnd, &ps) ;

    RECT   rect;
    ::GetClientRect(m_hwnd, &rect);
    
    HDC hMemDC      = ::CreateCompatibleDC(hDC);
    HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC, m_hBitmap);
    
    BitBlt(hDC, 0, 0, m_dwWidth, m_dwHeight, hMemDC, 0, 0, SRCCOPY);

    ::SelectObject(hMemDC, hOldBmp);

    ::DeleteDC(hMemDC);
    
    EndPaint (hwnd, &ps) ;
}

void CSplash::Init()
{
    m_hwnd = NULL;
    m_lpszClassName = TEXT("SPLASH");
    m_colTrans = 0;
    HMODULE hUser32 = GetModuleHandle(TEXT("USER32.DLL"));

    g_pSetLayeredWindowAttributes = (lpfnSetLayeredWindowAttributes)
                        GetProcAddress(hUser32, "SetLayeredWindowAttributes");
}

CSplash::CSplash()
{
    Init();
}

CSplash::CSplash(LPCTSTR lpszFileName, COLORREF colTrans)
{
    Init();

    SetBitmap(lpszFileName);
    SetTransparentColor(colTrans);
}

CSplash::~CSplash()
{
    FreeResources();
}

HWND CSplash::RegAndCreateWindow()
{
   
    WNDCLASSEX wndclass;
    wndclass.cbSize         = sizeof (wndclass);
    wndclass.style          = CS_BYTEALIGNCLIENT | CS_BYTEALIGNWINDOW;
    wndclass.lpfnWndProc    = ExtWndProc;
    wndclass.cbClsExtra     = 0;
    wndclass.cbWndExtra     = DLGWINDOWEXTRA;
    wndclass.hInstance      = ::GetModuleHandle(NULL);
    wndclass.hIcon          = NULL;
    wndclass.hCursor        = ::LoadCursor( NULL, IDC_WAIT );
    wndclass.hbrBackground  = (HBRUSH)::GetStockObject(LTGRAY_BRUSH);
    wndclass.lpszMenuName   = NULL;
    wndclass.lpszClassName  = m_lpszClassName;
    wndclass.hIconSm        = NULL;

    if(!RegisterClassEx (&wndclass))
        return NULL;

    DWORD nScrWidth  = ::GetSystemMetrics(SM_CXFULLSCREEN);
    DWORD nScrHeight = ::GetSystemMetrics(SM_CYFULLSCREEN);

    int x = (nScrWidth  - m_dwWidth) / 2;
    int y = (nScrHeight - m_dwHeight) / 2;
    m_hwnd = ::CreateWindowEx(WS_EX_TOPMOST|WS_EX_TOOLWINDOW, m_lpszClassName, 
                              TEXT("Banner"), WS_POPUP, x, y, 
                              m_dwWidth, m_dwHeight, NULL, NULL, NULL, this);

    if(m_hwnd)
    {
        MakeTransparent();
        ShowWindow   (m_hwnd, SW_SHOW) ;
        UpdateWindow (m_hwnd);
    }
    return m_hwnd;
}

int CSplash::DoLoop()
{
  
    if(!m_hwnd)
        ShowSplash();

    MSG msg ;
    while (GetMessage (&msg, NULL, 0, 0))
    {
        TranslateMessage (&msg) ;
        DispatchMessage  (&msg) ;
    }

    return msg.wParam ;

}

void CSplash::ShowSplash()
{
    CloseSplash();
    RegAndCreateWindow();
}


DWORD CSplash::SetBitmap(LPCTSTR lpszFileName)
{
    
    HBITMAP    hBitmap       = NULL;
    hBitmap = (HBITMAP)::LoadImage(0, lpszFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    return SetBitmap(hBitmap);
}

DWORD CSplash::SetBitmap(HBITMAP hBitmap)
{
    int nRetValue;
    BITMAP  csBitmapSize;
    
   FreeResources();
    
    if (hBitmap)
    {
        m_hBitmap = hBitmap;
        nRetValue = ::GetObject(hBitmap, sizeof(csBitmapSize), &csBitmapSize);
        if (nRetValue == 0)
        {
            FreeResources();
            return 0;
        }
        m_dwWidth = (DWORD)csBitmapSize.bmWidth;
        m_dwHeight = (DWORD)csBitmapSize.bmHeight;
    }
       
    return 1;
}

void CSplash::FreeResources()
{
    if (m_hBitmap)
        ::DeleteObject (m_hBitmap);
    m_hBitmap = NULL;
}

int CSplash::CloseSplash()
{
    
    if(m_hwnd)
    {
        DestroyWindow(m_hwnd);
        m_hwnd = 0;
        UnregisterClass(m_lpszClassName, ::GetModuleHandle(NULL));
        return 1;
    }
    return 0;
}

bool CSplash::SetTransparentColor(COLORREF col)
{
    m_colTrans = col;

    return MakeTransparent();
}

bool CSplash::MakeTransparent()
{
   if(m_hwnd && g_pSetLayeredWindowAttributes && m_colTrans )
    {     
        SetWindowLong(m_hwnd, GWL_EXSTYLE, GetWindowLong(m_hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        g_pSetLayeredWindowAttributes(m_hwnd, m_colTrans, 0, LWA_COLORKEY);
    }    
    return TRUE;
}