#include "pch.h"
#include "EventTranslator.h"
#include "TMGlobal.h"
#include "TMCamera.h"
#include "TMFieldScene.h"
#include "TMHuman.h"

EventTranslator::EventTranslator()
{
    m_lpCandList = 0;
    for (int i = 0; i < 256; ++i)
        m_bKey[i] = 0;

    m_bLock = 0;
    m_pDI = 0;
    m_pMouseDevice = 0;
    m_wParam = 0;
    m_bRBtn = 0;
    memset(m_strComp, 0, sizeof(m_strComp));
    memset(m_szResultStr, 0, sizeof(m_szResultStr));
    memset(m_bCompAttr, 0, sizeof(m_bCompAttr));
    m_dwCompAttrLen = 0;

    g_pEventTranslator = this;

    m_bAlt = 0;
    m_bShift = 0;
}

EventTranslator::~EventTranslator()
{
    Finalize();
    FinalizeIME();
    g_pEventTranslator = nullptr;
}

BOOL EventTranslator::Initialize(HWND hWnd)
{
    m_hWnd = hWnd;

    return InitializeInputDevice(hWnd) != 0;
}

int EventTranslator::InitializeIME()
{
    if (m_lpCandList == nullptr)
        m_lpCandList = (LPCANDIDATELIST)GlobalAlloc(64, 28);

    HIMC hIMC = ImmCreateContext();
    m_hOldIMC = ImmAssociateContext(m_hWnd, hIMC);

    SetWindowLong(m_hWnd, 0, (LONG)m_hOldIMC);

    ImmReleaseContext(m_hWnd, hIMC);
    SendMessage(g_pApp->m_hWnd, 641, 0, 0x8000000E);

    HWND hWndIME = ImmGetDefaultIMEWnd(m_hWnd);

    char szName[128];
    GetWindowText(hWndIME, szName, 128);
    return 1;
}

int EventTranslator::InitializeInputDevice(HWND hWnd)
{
    if (FAILED(DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8A, (LPVOID*)&m_pDI, 0)))
        return 0;
    if (FAILED(m_pDI->CreateDevice(GUID_SysMouse, &m_pMouseDevice, 0)))
        return 0;
    if (FAILED(m_pMouseDevice->SetDataFormat(&c_dfDIMouse2)))
        return 0;
    if (FAILED(m_pMouseDevice->SetCooperativeLevel(hWnd, 6)))
        return 0;

    m_pMouseDevice->Acquire();
    m_bLock = 1;

    return 1;
}

void EventTranslator::Finalize()
{
    if (m_pMouseDevice != nullptr)
    {
        m_pMouseDevice->Unacquire();
        m_bLock = 0;
    }

    SAFE_RELEASE(m_pMouseDevice);
    SAFE_RELEASE(m_pDI);
}

void EventTranslator::FinalizeIME()
{
    GlobalFree(m_lpCandList);
    m_lpCandList = nullptr;
    m_hOldIMC = (HIMC)GetWindowLong(m_hWnd, 0);

    HIMC hIMC = ImmAssociateContext(m_hWnd, m_hOldIMC);
    ImmDestroyContext(hIMC);
}

BOOL EventTranslator::IsNative()
{
    DWORD dwSent = 0;
    DWORD dwConv = 0;

    HIMC hIMC = ImmGetContext(m_hWnd);
    if (hIMC != nullptr)
    {
        ImmGetConversionStatus(hIMC, &dwConv, &dwSent);
        ImmReleaseContext(m_hWnd, hIMC);
    }

    return (dwConv & 1) != 0;
}

void EventTranslator::SetIMENative()
{
    HIMC hIMC = ImmGetContext(m_hWnd);
    if (hIMC != nullptr)
    {
        DWORD dwConv;
        DWORD dwSent;
        ImmGetConversionStatus(hIMC, &dwConv, &dwSent);
        dwConv = 1;
        ImmSetConversionStatus(hIMC, 1u, dwSent);
        ImmReleaseContext(m_hWnd, hIMC);
    }
}

void EventTranslator::SetIMEAlphaNumeric()
{
    HIMC hIMC = nullptr;
    hIMC = ImmGetContext(m_hWnd);
    if (hIMC != nullptr && IsIMEOpenStatus())
    {
        DWORD dwConv;
        DWORD dwSent;

        ImmGetConversionStatus(hIMC, &dwConv, &dwSent);
        if (dwConv & 3)
        {
            dwConv = 0;
            ImmSetConversionStatus(hIMC, 0, dwSent);
        }
        ImmReleaseContext(m_hWnd, hIMC);
    }
}

void EventTranslator::SetIMEOpenStatus(int bOpen)
{
    HIMC hIMC = ImmGetContext(m_hWnd);
    ImmSetOpenStatus(hIMC, bOpen);
    ImmReleaseContext(m_hWnd, hIMC);
}

int EventTranslator::IsIMEOpenStatus()
{
    HIMC hIMC = ImmGetContext(this->m_hWnd);
    if (hIMC == nullptr)
        return 0;

    int bRet = ImmGetOpenStatus(hIMC);
    ImmReleaseContext(m_hWnd, hIMC);
    return bRet;
}

void EventTranslator::SetVisibleCandidateList(int lParam, int bVisible)
{
    // NOTE: this function is used only in chinese client
    // no need for descompile for now
}

void EventTranslator::Lock()
{
    if (!m_bLock)
    {
        m_pMouseDevice->Acquire();
        m_bLock = 1;
    }
}

void EventTranslator::Unlock()
{
    if (m_bLock)
    {
        m_pMouseDevice->Unacquire();
        m_bLock = 0;
    }
}

int EventTranslator::ReadInputEventData()
{
    if (m_pMouseDevice == nullptr)
        return 1;

    DIMOUSESTATE2 dims2;
    memset(&dims2, 0, sizeof(dims2));

    if (FAILED(m_pMouseDevice->GetDeviceState(20, &dims2)))
    {
        for (int hr = m_pMouseDevice->Acquire(); hr == 0x8007001E; hr = m_pMouseDevice->Acquire())
        {
            ;
        }

        return 1;
    }

    if (RenderDevice::m_bCameraRot)
    {
        dx = -dims2.lX;
        wheel = -dims2.lZ;
    }
    else
    {
        dx = dims2.lX;
        wheel = dims2.lZ;
    }

    viewchange = dims2.lZ;
    dy = dims2.lY;
    button[0] = dims2.rgbButtons[0] & 0x80;
    button[1] = dims2.rgbButtons[1] & 0x80;
    button[2] = dims2.rgbButtons[2] & 0x80;

    if (button[0])
        OnLMousePressed();
    if (!button[0] && lastButtonState[0])
        OnLMouseReleased();
    if (button[1])
        OnRMousePressed();
    if (!button[1] && lastButtonState[1])
        OnRMouseReleased();
    if (m_bAlt == 1 && !button[1])
    {
        wheel = 3 * dy;
        viewchange = 3 * dy;
    }
    if (g_bActiveWB)
    {
        wheel = 0;
        viewchange = 0;
    }

    memcpy(lastButtonState, button, sizeof(button));
    return 1;
}

int EventTranslator::CameraEventData()
{
    TMCamera* pCamera = g_pObjectManager->m_pCamera;

    float fClose = pCamera->m_fMinClose;
    fClose = 1.2f;
    if (g_pCurrentScene != nullptr && g_pCurrentScene->m_pMyHuman != nullptr)
    {
        if (g_pCurrentScene->m_pMyHuman->m_cMount == 1)
            fClose = 2.5f;

        fClose = (float)((float)g_pCurrentScene->m_pMyHuman->m_stScore.Con * 0.00019f) + fClose;
    }

    if (g_pCurrentScene == nullptr)
        return 1;

    ESCENE_TYPE dwSceneType = g_pCurrentScene->m_eSceneType;
    if ((dwSceneType == ESCENE_TYPE::ESCENE_FIELD || dwSceneType == ESCENE_TYPE::ESCENE_SELECT_SERVER ||
        dwSceneType == ESCENE_TYPE::ESCENE_DEMO || dwSceneType == ESCENE_TYPE::ESCENE_SELCHAR) &&
        g_pCurrentScene->m_sPlayDemo < 0)
    {
        if (pCamera->m_dwSetTime == 0)
        {
            if (!pCamera->m_nQuaterView && (button[2] || m_bAlt == 1 && button[1]) && g_pCurrentScene->m_pGround != nullptr)
            {
                pCamera->m_fVerticalAngle = pCamera->m_fVerticalAngle - (float)((float)dy * 0.002f);
                if (pCamera->m_fVerticalAngle < -0.98539817f)
                    pCamera->m_fVerticalAngle = -0.98539817f;
                if (pCamera->m_fVerticalAngle > 0.75f)
                    pCamera->m_fVerticalAngle = 0.75f;

                pCamera->m_fHorizonAngle = (float)((float)dx * 0.0049f) + pCamera->m_fHorizonAngle;
                if (pCamera->m_fHorizonAngle > D3DXToRadian(360))
                    pCamera->m_fHorizonAngle = pCamera->m_fHorizonAngle - D3DXToRadian(360);
                if (pCamera->m_fHorizonAngle < 0.0)
                    pCamera->m_fHorizonAngle = pCamera->m_fHorizonAngle + D3DXToRadian(360);

                if (g_pCurrentScene != nullptr && g_pCurrentScene->m_pMyHuman != nullptr && 
                    g_pCurrentScene->m_pMyHuman->m_cMount != 0)
                {
                    float nMaxVerticalAngle = 0.449f;

                    TMHuman* pMyHuman = g_pCurrentScene->m_pMyHuman;
                    if (pMyHuman->m_nMountSkinMeshType == 39 || pMyHuman->m_nMountSkinMeshType == 40 || pMyHuman->m_nMountSkinMeshType == 20 
                        && pMyHuman->m_sMountIndex != 3)
                    {
                        nMaxVerticalAngle = 0.23f;
                    }
                    else if (pMyHuman->m_nMountSkinMeshType == 38)
                    {
                        nMaxVerticalAngle = 0.22f;
                    }

                    if (pCamera->m_fVerticalAngle > nMaxVerticalAngle)
                        pCamera->m_fVerticalAngle = nMaxVerticalAngle;
                }
            }
            if (pCamera->m_nQuaterView == 0 || pCamera->m_nQuaterView == 1)
            {
                if (pCamera->m_fSightLength > fClose && wheel < 0)
                {
                    pCamera->m_fSightLength = (float)((float)wheel / 240.0f) + pCamera->m_fSightLength;
                    pCamera->m_fWantLength = pCamera->m_fSightLength;
                }
                if (fClose > pCamera->m_fSightLength)
                {
                    pCamera->m_fSightLength = fClose;
                    pCamera->m_fWantLength = pCamera->m_fSightLength;
                }
                if (wheel > 0 && pCamera->m_fMaxCamLen > pCamera->m_fSightLength)
                {
                    pCamera->m_fSightLength = (float)((float)wheel / 240.0f) + pCamera->m_fSightLength;
                    pCamera->m_fWantLength = pCamera->m_fSightLength;
                }
                if (pCamera->m_fSightLength > pCamera->m_fMaxCamLen)
                {
                    pCamera->m_fSightLength = pCamera->m_fMaxCamLen;
                    pCamera->m_fWantLength = pCamera->m_fSightLength;
                }
            }

            pCamera->m_fBackHorizonAngle = pCamera->m_fHorizonAngle;
            pCamera->m_fBackVerticalAngle = pCamera->m_fVerticalAngle;
        }
        else if (pCamera->m_nEarthLevel == 10)
        {  
            float fProgress = sinf(((((float)(g_pTimerManager->GetServerTime() - pCamera->m_dwSetTime) / 3000.0f) * D3DXToRadian(180)) / 2.0f) + 4.712389f);
            fProgress += 1.0f;           
            if (fProgress >= 1.0f)
                fProgress = 1.0f;

            pCamera->m_fVerticalAngle = (float)((float)(1.0f - fProgress) * 0.1f) - (float)(D3DXToRadian(45) * fProgress);
            pCamera->m_fBackVerticalAngle = (float)((float)(1.0f - fProgress) * 0.1f) - (float)(D3DXToRadian(45) * fProgress);
            pCamera->m_fHorizonAngle = (float)((float)(1.0f - fProgress) * D3DXToRadian(180)) + (float)(D3DXToRadian(45) * fProgress);
            pCamera->m_fBackHorizonAngle = (float)((float)(1.0f - fProgress) * D3DXToRadian(180)) + (float)(D3DXToRadian(45) * fProgress);
            pCamera->m_fSightLength = (float)((float)(1.0f - fProgress) * 3.5f) + (float)(pCamera->m_fMaxCamLen * fProgress);
            pCamera->m_fWantLength = (float)((float)(1.0f - fProgress) * 3.5f) + (float)(pCamera->m_fMaxCamLen * fProgress);
        }
        else
        {
            float fProgress = (float)(g_pTimerManager->GetServerTime() - pCamera->m_dwSetTime);
            fProgress /= 1000.0f;
            if (fProgress > 1.0f)
                fProgress = 1.0f;

            pCamera->m_fVerticalAngle = ((((sinf(fProgress * D3DXToRadian(180)) * 12.0f) * 0.01f) * (float)pCamera->m_nEarthLevel)
                * (float)(1.0f - fProgress))
                + pCamera->m_fBackVerticalAngle;

            pCamera->m_fHorizonAngle = ((((sinf(fProgress * D3DXToRadian(180) * 12.0f)) * 0.01f) * (float)pCamera->m_nEarthLevel)
                * (float)(1.0f - fProgress))
                + pCamera->m_fBackHorizonAngle;
        }
    }

    return 1;
}

void EventTranslator::OnKeyDown(unsigned int iKeyCode)
{
    if (m_bKey[iKeyCode] == 0)
    {
        if (g_pObjectManager != nullptr)
        {
            m_bKey[iKeyCode] = 1;
            g_pObjectManager->OnKeyDownEvent(iKeyCode);
        }
    }
}

void EventTranslator::OnKeyUp(unsigned int iKeyCode)
{
    if (m_bKey[iKeyCode] != 0)
    {
        if (g_pObjectManager != nullptr)
        {
            m_bKey[iKeyCode] = 0;
            g_pObjectManager->OnKeyUpEvent(iKeyCode);
        }
    }
}

void EventTranslator::OnChar(char iCharCode, int lParam)
{
    if (g_pObjectManager != nullptr)
        g_pObjectManager->OnCharEvent(iCharCode, lParam);
}

void EventTranslator::OnIME(char iCharCode, int lParam)
{
    // NOTE: china stuffs
}

void EventTranslator::OnIME2()
{
}

void EventTranslator::UpdateCompositionPos()
{
}

void EventTranslator::OnLMousePressed()
{
    if (g_pCursor != nullptr)
    {
        if (g_pCursor->m_nPosX > 0.0f && (float)g_pDevice->m_dwScreenWidth > g_pCursor->m_nPosX
            && g_pCursor->m_nPosY > 0.0f && (float)g_pDevice->m_dwScreenHeight > g_pCursor->m_nPosY)
        {
            g_pCurrentScene->OnMouseEvent(               
                513,
                m_wParam,
                static_cast<int>(g_pCursor->m_nPosX),
                static_cast<int>(g_pCursor->m_nPosY));
        }      
    }
}

void EventTranslator::OnLMouseReleased()
{
}

void EventTranslator::OnRMousePressed()
{
    if (g_pCursor != nullptr)
    {
        if (g_pCursor->m_nPosX > 0.0f && (float)(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift) > g_pCursor->m_nPosX
            && g_pCursor->m_nPosY > 0.0f && (float)(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift) > g_pCursor->m_nPosY)
        {
            g_pCurrentScene->OnMouseEvent(
                516,
                m_wParam,
                static_cast<int>(g_pCursor->m_nPosX),
                static_cast<int>(g_pCursor->m_nPosY));
        }        
    }
}

void EventTranslator::OnRMouseReleased()
{
    m_bRBtn = 0;
}

void EventTranslator::OnMouseEvent(unsigned int nFlags, unsigned int wParam, int ix, int iy)
{
    m_wParam = wParam;
    if (g_pCursor != nullptr)
        g_pCursor->SetPosition(ix, iy);

    if (g_pObjectManager != nullptr)
        g_pObjectManager->OnMouseEvent(nFlags, wParam, ix, iy);
}