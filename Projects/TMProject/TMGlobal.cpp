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