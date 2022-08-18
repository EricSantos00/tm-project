#include "pch.h"
#include "TMGlobal.h"

NewApp* g_pApp;
CPSock* g_pSocketManager;
CPSock* g_LoginSocket;
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
int g_bDebugMsg = 1;
int g_nReflection;
char g_szFontName[128] = { "Tahoma" };
int g_nFontBold = 500;
int g_nLangIndex = 0;
float g_ClipNear = 0.69f;
float g_ClipFar = 540.0f;

int g_nServerCountList[11];
char g_szServerNameList[11][16];
char g_szServerName[10][10][9];

char g_UIString[500][64];

int g_bActiveWB;
int g_bHideEffect;
int g_bHideSkillBuffEffect;
int g_bHideSkillBuffEffect2;
int g_nPlayDemo = 1;
int g_UIVer = 2;
int g_nKeyType;

int g_HeightWidth = 256;
int g_HeightHeight = 256;
int g_HeightPosX = 2048;
int g_HeightPosY = 2048;

STRUCT_MIXHELP g_pItemMixHelp[11500];
STRUCT_ITEMHELP g_pItemHelp[6500];

unsigned int g_dwStartPlayTime;
unsigned int g_dwPausedTime;
unsigned int g_dwStartPacketTime;
int g_nCurrentPos;
int g_nDumpPacketSize;
FILE* g_hPacketDump;
char* g_pDumpPacket; 
unsigned short g_usLastPacketType;
int g_bLastStop;
int g_bCastleWar;
int g_bCastleWar2;

int g_GameAuto;

int g_GameAuto_mountValue = 30;
int g_GameAuto_hpValue = 30;

SPanel* g_pGBPanel;

unsigned int g_dwStartQuitGameTime;

int g_bEndGame;

unsigned int g_dwServerTime;
unsigned int g_dwClientTime;
unsigned int g_pLastFixTime;

unsigned int LastSendTime;

int g_nUnDelMobCount;

float g_fWide;

HINSTANCE g_hInstance;

char g_szOS[3] = "??";

int g_hLogFile; //Language File WYD.log

int g_objectnumber;
int g_effectnumber;
int g_totaleffect;

int g_nUpdateGuildName;

 

char g_pAttribute[1024][1024];

int Game_grade = 1;
char g_AccountLock;
int g_nBattleMaster;
int g_pDebugMaxCount; 

int g_bTestServer;
int g_bMoveServer;
char g_szEncryptedAcc[256];

int g_bHideBackground = FALSE;

int g_nMobCount;
int g_nWeather;

unsigned int CurrentTime;
int g_nMyHumanSpeed = 3;

int g_NonePKServer;
int g_pPKServerNum[2] = { 5, 10 };

int g_nTempArray[3] = { (int)(0xF1476E2F), 0, 0 };
int g_nTempArray2[4] = { (int)(0xF1577A31), 0, 0, 0 };

stMinimapPos g_MinimapPos[256];
char g_TempName[16];
char g_TempNick[26];

int g_bEffectFirst = 1;
int g_bEvent;

int g_bRunning = 1;

int g_nCombineMode = 0;

int g_nItemCount;
int g_nSpringTree;