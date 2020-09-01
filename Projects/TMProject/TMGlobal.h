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

extern int g_nCombineMode;

extern int g_nItemCount;
extern int g_nSpringTree;

const static TMVector3 g_vecItemBillPos[28] = 
{
    {0.398f, 5.7620001f, 0.70599997f},
    {0.70599997f, 4.9320002f, 0.15700001f},
    {1.117f, 4.072f, 1.22f},
    {-0.66399997f, 3.8039999f, 0.22f},
    {-0.056000002f, 32.778999f, 1.841f},
    {0.035f, 2.605f, -0.46900001f},
    {-1.081f, 2.2149999f, 0.134f},
    {1.182f, 3.1470001f, 1.7359999f},
    {1.52f, 2.3399999f, 1.7359999f},
    {1.924f, 2.2839999f, 0.109f},
    {1.4859999f, 1.878f, -0.5f},
    {-0.164f, 1.425f, 1.908f},
    {1.536f, 0.92199999f, 1.192f},
    {-1.081f, 1.114f, -0.185f},
    {-0.21699999f, 4.5630002f, 1.277f},
    {0.84399998f, 4.0580001f, -0.26499999f},
    {0.84399998f, 4.0580001f, -0.26499999f},
    {1.712f, 3.2249999f, 0.49900001f},
    {-0.77899998f, 3.326f, 0.917f},
    {-0.85900003f, 2.2839999f, 1.835f},
    {0.61199999f, 1.2869999f, 2.2950001f},
    {0.079000004f, 1.467f, -1.028f},
    {0.79000002f, 1.467f, -1.028f},
    {1.679f, 3.8169999f, 0.56300002f},
    {-0.115f, 3.283f, 1.824f},
    {-0.57800001f, 2.77f, -0.041000001f},
    {-0.84799999f, 1.306f, 2.23f},
    {0.76899999f, 0.509f, -1.143f},
};

const static stTeleportPos g_TeleportTable[37] =
{
  { 2116, 2100, 700, g_pMessageStringTable[209] },
  { 2480, 1716, 700, g_pMessageStringTable[209] },
  { 2456, 2016, 700, g_pMessageStringTable[209] },
  { 3648, 3108, 0, g_pMessageStringTable[209] },
  { 1044, 1724, 0, g_pMessageStringTable[125] },
  { 1044, 1716, 0, g_pMessageStringTable[126] },
  { 1044, 1708, 0, g_pMessageStringTable[173] },
  { 1048, 1764, 0, g_pMessageStringTable[210] },
  { 2140, 2068, 0, g_pMessageStringTable[213] },
  { 2468, 1716, 0, g_pMessageStringTable[211] },
  { 2364, 2284, 0, g_pMessageStringTable[212] },
  { 144, 3788, 0, g_pMessageStringTable[213] },
  { 2668, 2156, 0, g_pMessageStringTable[212] },
  { 144, 3772, 0, g_pMessageStringTable[213] },
  { 148, 3780, 0, g_pMessageStringTable[215] },
  { 144, 3780, 0, g_pMessageStringTable[215] },
  { 1004, 4028, 0, g_pMessageStringTable[214] },
  { 408, 4072, 0, g_pMessageStringTable[215] },
  { 1004, 4064, 0, g_pMessageStringTable[214] },
  { 744, 3820, 0, g_pMessageStringTable[215] },
  { 1004, 3992, 0, g_pMessageStringTable[214] },
  { 680, 4076, 0, g_pMessageStringTable[216] },
  { 916, 3820, 0, g_pMessageStringTable[215] },
  { 876, 3872, 0, g_pMessageStringTable[216] },
  { 932, 3820, 0, g_pMessageStringTable[215] },
  { 188, 188, 0, g_pMessageStringTable[126] },
  { 2548, 1740, 1000, g_pMessageStringTable[322] },
  { 1824, 1772, 0, g_pMessageStringTable[218] },
  { 1172, 4080, 0, g_pMessageStringTable[211] },
  { 1516, 3996, 0, g_pMessageStringTable[220] },
  { 1304, 3816, 0, g_pMessageStringTable[219] },
  { 2452, 1716, 0, g_pMessageStringTable[211] },
  { 2452, 1988, 0, g_pMessageStringTable[211] },
  { 3648, 3140, 700, g_pMessageStringTable[211] },
  { 2480, 1648, 700, g_pMessageStringTable[301] },
  { 1052, 1708, 0, g_pMessageStringTable[321] },
  { 1056, 1724, 0, g_pMessageStringTable[485] }
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