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

extern float g_fWide;

extern char g_szOS[3];

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