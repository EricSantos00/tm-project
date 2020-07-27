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
int g_bDebugMsg;
int g_nReflection;
char g_szFontName[128] = { "Tahoma" };
int g_nFontBold = 500;
float g_ClipNear = 0.69f;
float g_ClipFar = 540.0f;

int g_nServerCountList[12];
char g_szServerNameList[11][9];
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

unsigned int g_dwStartQuitGameTime;

int g_bEndGame;

unsigned int g_dwServerTime;
unsigned int g_dwClientTime;
unsigned int g_pLastFixTime;

unsigned int CurrentTime;
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

stCurse_num g_pCurseList;
int Game_grade = 1;
char g_AccountLock;
int g_nBattleMaster;
int g_pDebugMaxCount; 
