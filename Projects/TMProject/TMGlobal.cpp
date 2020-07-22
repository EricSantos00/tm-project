#include "pch.h"
#include "TMGlobal.h"

NewApp* g_pApp;
ObjectManager* g_pObjectManager;
EventTranslator* g_pEventTranslator;
MeshManager* g_pMeshManager;
TextureManager* g_pTextureManager;
TimerManager* g_pTimerManager;
TMScene* g_pCurrentScene;
RenderDevice* g_pDevice;
SCursor* g_pCursor;
CSoundManager* g_pSoundManager;

int g_nUseBlur;
int g_nAntialias;
int g_bDebugMsg;
int g_nReflection;
char g_szFontName[128] = { "Tahoma" };
int g_nFontBold = 500;
float g_ClipNear = 0.69f;
float g_ClipFar = 540.0f;

int g_nServerCountList[12];
char g_szServerNameList[11][9];
char g_szServerName[10][10][9];

HWND hWndMain;

int g_bActiveWB;
int g_bHideEffect;
int g_bHideSkillBuffEffect;
int g_bHideSkillBuffEffect2;
int g_nPlayDemo = 1;
int g_UIVer = 2;
int g_nKeyType;

STRUCT_MIXHELP g_pItemMixHelp[11500];
STRUCT_ITEMHELP g_pItemHelp[6500];

unsigned int g_dwStartPlayTime;
unsigned int g_dwPausedTime;
unsigned int g_dwStartPacketTime;
int g_nCurrentPos;
int g_nDumpPacketSize;
int g_hPacketDump;
char* g_pDumpPacket;

HINSTANCE g_hInstance;