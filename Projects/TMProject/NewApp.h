#pragma once

class EventTranslator;
class RenderDevice;
class CSoundManager;
class TMVideoWnd;
class DS_SOUND_MANAGER;
class JBlur;
class TimerManager;
class ObjectManager;
class CPSock;

struct SaveUpdatAndConfig
{
    short Version;
    short Config[14];
};

class NewApp
{
public:
    NewApp();
    virtual ~NewApp();

    virtual HRESULT Initialize(HINSTANCE hInstance, int nFull);
    HRESULT InitDevice();
    void InitServerName();
    void InitMusicList();
    virtual HRESULT Finalize();
    virtual DWORD Run();
    virtual void OnCreate(HWND hWnd, DWORD wParam, int lParam);
    virtual HRESULT RenderScene();
    virtual void SetObjectManager(ObjectManager* pManager);
    virtual EventTranslator* GetEventTranslator();

    HWND GetSafeHwnd();
    void SwitchWebBrowserState(int nEmptyCargo);
    void SwitchWebBoard();
    DWORD GetHttpRequest(char* httpname, char* Request, int MaxBuffer);
    void MixHelp();
    int BASE_Initialize_NewServerList();
    void InitServerNameMR();
    HRESULT MsgProc(HWND hWnd, DWORD uMsg, DWORD wParam, int lParam);
    bool CheckResolution(DWORD x, DWORD y, DWORD bpp);

    char base_chinaTid(char* TID, char* Id);

public:
    HWND m_hWnd;
    int m_bActive;
    unsigned int m_dwWindowStyle;
    unsigned int m_dwScreenWidth;
    unsigned int m_dwScreenHeight;
    unsigned int m_dwColorBit;
    int m_bwFullScreen;
    char m_strWindowTitle[64];
    char m_szServerIP[128];
    char m_szLoginServerIP[128];
    RenderDevice* m_pRenderDevice;
    CSoundManager* m_pSoundManager;
    TMVideoWnd* m_pAviPlayer;
    DS_SOUND_MANAGER* m_pBGMManager;
    EventTranslator* m_pEventTranslator;
    TimerManager* m_pTimerManager;
    ObjectManager* m_pObjectManager;
    CPSock* m_pSocketManager;
    int m_bTex;
    int m_nSound;
    int m_nMusic;
    int m_nCameraView;
    int m_Winstate;
    bool m_binactive;
    HBITMAP m_hBMBtnBG;
    bool china_bWrite;
    int china_Playtime;
    JBlur* m_pBlur;
};

void InitServerName2();
void CreateConsole();