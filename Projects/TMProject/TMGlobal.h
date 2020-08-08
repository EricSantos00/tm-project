#pragma once

#include "NewApp.h"
#include "CPSock.h"
#include "ObjectManager.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "TimerManager.h"
#include "TMScene.h"
#include "RenderDevice.h"
#include "EventTranslator.h"
#include "dsutil.h"
#include "SControl.h"
#include "TMPaths.h"
#include "ResourceControl.h"

constexpr unsigned int WYDCOLOR_ALPHA(unsigned int color) { return color & 0xFF000000; }
constexpr unsigned int WYDCOLOR_RED(unsigned int color) { return (((unsigned int)0xFF0000 & color) >> 16); }
constexpr unsigned int WYDCOLOR_GREEN(unsigned int color) { return (((unsigned short)0xFF00 & color) >> 8); }
constexpr unsigned int WYDCOLOR_BLUE(unsigned int color) { return ((unsigned char)0xFF & color); }
constexpr unsigned int WYD_RGBA(unsigned int r, unsigned int  g, unsigned int  b, unsigned int  a) { 
    return ((DWORD)((a | 0xFF000000) | (b & 0xFF) | ((g << 8) & 0xFF00) | ((r << 16) & 0xFF0000))); 
}

constexpr DWORD operator""_min(unsigned long long min)
{
    return static_cast<DWORD>(min) * 60000;
}

constexpr DWORD operator""_sec(unsigned long long sec)
{
    return static_cast<DWORD>(sec) * 1000;
}

extern NewApp* g_pApp;
extern CPSock* g_pSocketManager;
extern CPSock* g_LoginSocket;
extern ObjectManager* g_pObjectManager;
extern EventTranslator* g_pEventTranslator;
extern MeshManager* g_pMeshManager;
extern TextureManager* g_pTextureManager;
extern TimerManager* g_pTimerManager;
extern TMScene* g_pCurrentScene;
extern RenderDevice* g_pDevice;
extern SCursor* g_pCursor;
extern CSoundManager* g_pSoundManager;

extern int g_nUseBlur;
extern int g_nAntialias;
extern int g_bDebugMsg;
extern int g_nReflection;
extern char g_szFontName[128];
extern int g_nFontBold;
extern float g_ClipNear;
extern float g_ClipFar;

extern int g_nServerCountList[11];
extern char g_szServerNameList[11][9];
extern char g_szServerName[10][10][9];

extern char g_UIString[500][64];

extern int g_bActiveWB;
extern int g_bHideEffect;
extern int g_bHideSkillBuffEffect;
extern int g_bHideSkillBuffEffect2;
extern int g_nPlayDemo;
extern int g_UIVer;
extern int g_nKeyType;

extern int g_HeightWidth;
extern int g_HeightHeight;
extern int g_HeightPosX;
extern int g_HeightPosY;

extern HINSTANCE g_hInstance;
extern STRUCT_MIXHELP g_pItemMixHelp[11500];
extern STRUCT_ITEMHELP g_pItemHelp[6500];

extern unsigned int g_dwStartPlayTime;
extern unsigned int g_dwPausedTime;
extern unsigned int g_dwStartPacketTime;
extern int g_nCurrentPos;
extern int g_nDumpPacketSize;
extern FILE* g_hPacketDump;
extern char* g_pDumpPacket;
extern unsigned short g_usLastPacketType;
extern int g_bLastStop;
extern int g_bCastleWar;
extern int g_bCastleWar2;

extern int g_GameAuto_mountValue;
extern int g_GameAuto_hpValue;

extern SPanel* g_pGBPanel;

extern int g_GameAuto;

extern int g_bEndGame;

extern unsigned int g_dwStartQuitGameTime;

extern unsigned int g_dwServerTime;
extern unsigned int g_dwClientTime;
extern unsigned int g_pLastFixTime;

extern unsigned int CurrentTime;
extern unsigned int LastSendTime;

extern int g_nUnDelMobCount;

extern float g_fWide;

extern char g_szOS[3];

extern int g_hLogFile;

extern int g_objectnumber;
extern int g_effectnumber;
extern int g_totaleffect;
extern int g_nUpdateGuildName;
extern char g_szEncryptedAcc[256];
extern int g_bMoveServer;

extern stCurse_num g_pCurseList;
extern int g_bTestServer;

extern int Game_grade;
extern char g_AccountLock;
extern int g_nBattleMaster;
extern int g_pDebugMaxCount;

extern char g_pAttribute[1024][1024];

extern int g_bHideBackground;

extern int g_nMobCount;
extern int g_nWeather;

extern int g_nMyHumanSpeed;

extern int g_NonePKServer;;
extern int g_pPKServerNum[2];

extern int g_nTempArray[3];
extern int g_nTempArray2[4];

extern stMinimapPos g_MinimapPos[256];
extern char g_TempName[16];
extern char g_TempNick[26];

extern int g_bEffectFirst;
extern int g_bEvent;
extern int g_bRunning;

static stTeleportPos g_TeleportTable[37] =
{
  { 2116, 2100, 700, (char*)"" },
  { 2480, 1716, 700, (char*)"" },
  { 2456, 2016, 700, (char*)"" },
  { 3648, 3108, 0, (char*)"" },
  { 1044, 1724, 0, (char*)"" },
  { 1044, 1716, 0, (char*)"" },
  { 1044, 1708, 0, (char*)"" },
  { 1048, 1764, 0, (char*)"" },
  { 2140, 2068, 0, (char*)"" },
  { 2468, 1716, 0, (char*)"" },
  { 2364, 2284, 0, (char*)"" },
  { 144, 3788, 0, (char*)"" },
  { 2668, 2156, 0, (char*)"" },
  { 144, 3772, 0, (char*)"" },
  { 148, 3780, 0, (char*)"" },
  { 144, 3780, 0, (char*)"" },
  { 1004, 4028, 0, (char*)"" },
  { 408, 4072, 0, (char*)"" },
  { 1004, 4064, 0, (char*)"" },
  { 744, 3820, 0, (char*)"" },
  { 1004, 3992, 0, (char*)"" },
  { 680, 4076, 0, (char*)"" },
  { 916, 3820, 0, (char*)"" },
  { 876, 3872, 0, (char*)"" },
  { 932, 3820, 0, (char*)"" },
  { 188, 188, 0, (char*)"" },
  { 2548, 1740, 1000, (char*)"" },
  { 1824, 1772, 0, (char*)"" },
  { 1172, 4080, 0, (char*)"" },
  { 1516, 3996, 0, (char*)"" },
  { 1304, 3816, 0, (char*)"" },
  { 2452, 1716, 0, (char*)"" },
  { 2452, 1988, 0, (char*)"" },
  { 3648, 3140, 700, (char*)"" },
  { 2480, 1648, 700, (char*)"" },
  { 1052, 1708, 0, (char*)"" },
  { 1056, 1724, 0, (char*)"" }
};

static unsigned int g_dwFoodColor[7] =
{
  0xFF000000,
  0xFFFF00FF,
  0xFFFFAA00,
  0xFFFFFF00,
  0xFF00FFFF,
  0xFFAAAAFF,
  0xFFFFFFFF
};

static short g_sTimeTable[7] = { 120, 240, 360, 3360, 3656, 5936, 7375 };

static int g_AffectSkillType[122] =
{
  -1,
  1,
  41,
  16,
  165,
  119,
  105,
  19,
  161,
  44,
  51,
  43,
  84,
  11,
  3,
  45,
  71,
  5,
  46,
  76,
  40,
  77,
  37,
  54,
  13,
  53,
  89,
  75,
  95,
  102,
  163,
  85,
  47,
  96,
  164,
  125,
  92,
  81,
  87,
  162,
  96,
  26,
  121,
  129,
  99,
  114,
  130,
  147,
  140,
  165,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

static unsigned int g_dwHandIndex[101][2] =
{
    {19,25},{18,24},{15,21},{15,21},{12,18},{22,28},{23,29},
    {20,26},{24,30},{23,31},{32,17},{22,35},{34,44},{34,44},
    {34,44},{34,44},{34,44},{34,44},{34,44},{34,44},{0,0},
    {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
    {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
    {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
    {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
    {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
    {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
    {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
    {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
    {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}
};