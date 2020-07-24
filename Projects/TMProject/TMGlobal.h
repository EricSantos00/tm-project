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

constexpr unsigned int WYDCOLOR_ALPHA(unsigned int color) { return color & 0xFF000000; }
constexpr unsigned int WYDCOLOR_RED(unsigned int color) { return (((unsigned int)0xFF0000 & color) >> 16); }
constexpr unsigned int WYDCOLOR_GREEN(unsigned int color) { return (((unsigned short)0xFF00 & color) >> 8); }
constexpr unsigned int WYDCOLOR_BLUE(unsigned int color) { return ((unsigned char)0xFF & color); }
constexpr unsigned int WYD_RGBA(unsigned int r, unsigned int  g, unsigned int  b, unsigned int  a) { 
    return ((DWORD)((a | 0xFF000000) | (b & 0xFF) | ((g << 8) & 0xFF00) | ((r << 16) & 0xFF0000))); 
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

extern int g_nServerCountList[12];
extern char g_szServerNameList[11][9];
extern char g_szServerName[10][10][9];
extern int g_bActiveWB;

extern int g_bHideEffect;
extern int g_bHideSkillBuffEffect;
extern int g_bHideSkillBuffEffect2;
extern int g_nPlayDemo;
extern int g_UIVer;
extern int g_nKeyType;

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

extern stCurse_num g_pCurseList;

extern int g_pDebugMaxCount;

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

static int g_pMountTempBonus[20][5] =
{
    // AttackAdd, MagicAdd, Evasion, Resistence, Speed

    { 35, 7, 0, 0, 6 },//Shire 3D
    { 350, 55, 10, 28, 6 },//Thoroughbred 3D
    { 450, 55, 0, 0, 6 },//Klazedale 3D
    { 35, 7, 0, 0, 6 },//Shire 15D
    { 450, 72, 10, 28, 6 },//Thoroughbred 15D
    { 450, 72, 0, 0, 6 },//Klazedale 15D
    { 120, 45, 0, 0, 6 },//Shire 30D
    { 450, 72, 10, 28, 6 },//Thoroughbred 30D
    { 450, 72, 0, 0, 6 },//Klazedale 30D
    { 325, 35, 16, 28, 6 },//Gulfaxi 30D
    { 350, 45, 10, 4, 6 },//Tigre de Fogo
    { 250, 25, 0, 31, 6 },//Dragão Vermelho
    { 80, 15, 0, 31, 6 },//Dragão Menor
    { 950, 145, 60, 20, 6 },//Dragão Akelo
    { 950, 145, 60, 20, 6 },//Dragão Hekalo
};

static int g_pMountBonus[30][5] =
{
    // AttackAdd, MagicAdd, Evasion, Resistence, Speed

    {10, 1, 0, 0, 4},//Porco
    {10, 1, 0, 0, 4},//Javali
    {50, 1, 0, 0, 5},//Lobo
    {80, 15, 0, 0, 5},//Dragão menor
    {100, 20, 0, 0, 4},//Urso
    {150, 25, 0, 0, 5},//Dente de sabre
    {250, 50, 40, 0, 6},//Cavalo s/sela N
    {300, 60, 50, 0, 6},//Fantasma N
    {350, 65, 60, 0, 6},//Leve N
    {400, 70, 70, 0, 6},//Equip N
    {500, 85, 80, 0, 6},//Andaluz N
    {250, 50, 0, 16, 6},//Cavalo s/sela B
    {300, 60, 0, 20, 6},//Fantasma B
    {350, 65, 0, 24, 6},//Leve B
    {400, 70, 0, 28, 6},//Equip B
    {500, 85, 0, 32, 6},//Andaluz B
    {550, 90, 0, 0, 6},//Fenrir
    {600, 90, 0, 0, 6},//Dragao
    {550, 90, 0, 20, 6},//Fenrir das sombras
    {650, 100, 60, 28, 6},//Tigre de fogo
    {750, 110, 80, 32, 6},//Dragão vermelho
    {570, 90, 20, 16, 6},//Unicórnio
    {570, 90, 30, 8, 6},//Pegasus
    {570, 90, 40, 12, 6},//Unisus
    {590, 80, 30, 20, 6},//Grifo
    {615, 90, 40, 16, 6},//HipoGrifo
    {615, 90, 50, 16, 6},//Sangrento
    {620, 35, 30, 28, 6},//Svaldfire
    {250, 95, 0, 28, 6},//Sleipnir
    {150, 10, 20, 0, 6}//Pantera negra
};

static unsigned int dwEFParam[49] =
{
    18, 1, 22, 23, 24, 25, 2, 3, 4, 5,
    45, 46, 44, 42, 47, 48, 54, 40, 29,
    49, 50, 51, 52, 11, 12, 13, 14, 26,
    74, 7, 8, 9, 10, 60, 62, 64, 65, 66,
    53, 67, 68, 73, 78, 79, 80, 81, 82,
    84, 83
};

static int	g_pDistanceTable[7][7] =
{
    0, 1, 2, 3, 4, 5, 6,
    1, 1, 2, 3, 4, 5, 6,
    2, 2, 3, 4, 4, 5, 6,
    3, 3, 4, 4, 5, 5, 6,
    4, 4, 4, 5, 5, 5, 6,
    5, 5, 5, 5, 5, 6, 6,
    6, 6, 6, 6, 6, 6, 6,
};

static char g_pItemGrid[8][4] =
{
  { 0x1, 0x0, 0x0, 0x0 },
  { 0x1, 0x1, 0x0, 0x0 },
  { 0x1, 0x1, 0x1, 0x0 },
  { 0x1, 0x1, 0x1, 0x1 },
  { 0x1, 0x0, 0x0, 0x0 },
  { 0x1, 0x1, 0x0, 0x0 },
  { 0x1, 0x1, 0x1, 0x0 },
  { 0x1, 0x1, 0x1, 0x1 }
};

static int ResultQuest355[4][3] = { { 80, 0, 0 }, { 0, 30, 0 }, { 0, 0, 80 }, { 60, 20, 60 } };

static STRUCT_BEASTBONUS pTransBonus[5] =
{
    //MinDam, MaxDam, MinAc, MaxAc, MinHp, MaxHp, RunSpeed, UNK, AttackSpeed
    {110, 130,  95, 105,  95, 105, 1, 0, 20, 0, 100, 100, 100, 100, 100, 100,  15},
    { 80, 100, 100, 110, 110, 140, 0, 0,  0, 0, 100, 100, 100, 100, 100, 100,  60},
    {100, 120, 105, 115, 100, 120, 1, 0, 20, 0, 100, 100, 100, 100, 100, 100, 115},
    { 90, 110, 110, 125, 105, 110, 0, 0, 20, 0, 100, 100, 100, 100, 100, 100, 155 },
    { 105, 120, 110, 120, 105, 115, 3, 0, 20, 0, 100, 100, 100, 100, 100, 100, 155 }
};

static STRUCT_GUILDZONE g_pGuildZone[MAX_GUILDZONE] =
{
    {0, 0, 2088, 2148, 2086, 2093, 2052, 2052, 2171, 2163, 197, 213, 238, 230, 205, 220, 228, 220, 5, 0}, // Armia
    {0, 0, 2531, 1700, 2494, 1707, 2432, 1672, 2675, 1767, 197, 149, 238, 166, 205, 157, 228, 157, 5, 0}, // Azran
    {0, 0, 2460, 1976, 2453, 2000, 2448, 1966, 2476, 2024, 141, 213, 182, 230, 146, 220, 173, 220, 5, 0}, // Erion
    {0, 0, 3614, 3124, 3652, 3122, 3605, 3090, 3690, 3260, 141, 149, 182, 166, 146, 157, 173, 157, 5, 0}, // Nippleheim
    {0, 0, 1066, 1760, 1050, 1706, 1036, 1700, 1072, 1760, 4000, 4000, 4010, 4010, 4005, 4005, 4005, 4005, 5, 0} // Noatum
};

static int g_pSancRate[3][12] =
{
  { 100, 100, 100, 85, 70, 40, 10, 0, 0, 0, 0, 0 }, //PO
  { 100, 100, 100, 100, 100, 76, 57, 37, 18, 5, 0, 4 }, //PL
  { 100, 80, 70, 60, 45, 30, 20, 10, 5, 5, 3, 2 } //Essences?
};