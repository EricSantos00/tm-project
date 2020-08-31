#pragma once

#include "TreeNode.h"
#include "Structures.h"
#include "Basedef.h"

enum class ESCENE_TYPE
{
    ESCENE_NONE = 0x0,
    ESCENE_FIELD = 0x7530,
    ESCENE_SELCHAR = 0x7531,
    ESCENE_LOGIN = 0x7532,
    ESCENE_CREATE_ACCOUNT = 0x7533,
    ESCENE_SELECT_SERVER = 0x7534,
    ESCENE_DEMO = 0x7535,
};

enum class EDirection
{
    EDIR_LEFT = 0x0,
    EDIR_RIGHT = 0x1,
    EDIR_UP = 0x2,
    EDIR_DOWN = 0x3,
};

struct stCameraTick
{
    unsigned int dwTick;
    short sLocal;
    float fX;
    float fY;
    float fZ;
    float fHorizonAngle;
    float fVerticalAngle;
};

class SControlContainer;
class SListBox;
class TMGround;
class TMSky;
class TMSun;
class TMHuman;
class SControl;
class SText;
class TMObjectContainer;
class TMItem;
class SMessagePanel;
class SMessageBox;

class TMScene : public TreeNode
{
public:
    TMScene();
    virtual ~TMScene();

    virtual SControlContainer* GetCtrlContainer();
    virtual int LoadRC(const char* szFileName);
    virtual int ParseRC(FILE* fp, FILE* fpBinary, char* szControlType);
    virtual int ReadRCBin(char* szBinFileName);
    virtual int FindID(char* szID);
    virtual int InitializeScene();
    int OnPacketEvent(unsigned int dwCode, char* pSBuffer) override;
    int OnKeyDownEvent(unsigned int iKeyCode) override;
    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
    int OnKeyUpEvent(unsigned int iKeyCode) override;
    int OnCharEvent(char iCharCode, int lParam) override;
    virtual int OnIMEEvent(char* ipComposeString);
    virtual int OnChangeIME();
    virtual int OnControlEvent(unsigned int idwControlID, unsigned int idwEvent) = 0;
    virtual int OnAccel(int nMsg);
    int FrameMove(unsigned int dwServerTime) override;
    virtual int ReloadScene();
    ESCENE_TYPE GetSceneType();
    virtual void Cleanup();
    int GroundNewAttach(EDirection eDir);
    D3DXVECTOR3 GroundGetPickPos();
    int GroundGetTileType(TMVector2 vecPosition);
    int GroundGetMask(TMVector2 vecPosition);
    int GroundGetMask(IVector2 vecPosition);
    float GroundGetHeight(TMVector2 vecPosition);
    D3DCOLORVALUE GroundGetColor(TMVector2 vecPosition);
    void GroundSetColor(TMVector2 vecPosition, unsigned int dwColor);
    int GroundIsInWater(TMVector2 vecPosition, float fHeight, float* pfWaterHeight);
    int GroundIsInWater2(TMVector2 vecPosition, float* pfWaterHeight);
    float GroundGetWaterHeight(TMVector2 vecPosition, float* pfWaterHeight);
    int GetMask2(TMVector2 vecPosition);
    void Warp();
    void Warp2(int nZoneX, int nZoneY);
    void SaveHeightMap(char* szFileName);
    void CameraAction();
    void ReadCameraPos(const char* szFileName);
    int LoadMsgText(SListBox* pListBox, const char* szFileName);
    int LoadMsgText2(SListBox* pListBox, const char* szFileName, int nStartLine, int nEndLine);
    int LoadMsgText3(SListBox* pListBox, const char* szFileName, int nLv, int ntrans);
    unsigned int LoadMsgText4(char* pStr, int dwStrSize, const char* szFileName, int nLv, int ntrans);
    int LoadMsgLevel(char* LevelQuest, const char* szFileName, char cType);
    void CheckPKNonePK(int nServerIndex);
    void LogMsgCriticalError(int Type, int ID, int nMesh, int X, int Y);
    void DeleteOwnerAllContainer();

public:
    ESCENE_TYPE m_eSceneType; // 36
    SControlContainer* m_pControlContainer; // 40
    TreeNode* m_pEffectContainer; // 44
    TreeNode* m_pShadeContainer;
    TreeNode* m_pHumanContainer;
    TreeNode* m_pItemContainer;
    TreeNode* m_pExtraContainer;
    TMGround* m_pGround;
    TMSky* m_pSky;
    TMSun* m_pSun;
    TMHuman* m_pMyHuman;
    int m_bShowNameLabel;
    int m_bCriticalError;
    SControl* m_pDescPanel;
    SText* m_pTextCandidate[10];
    SText* m_pTextCompose;
    SText* m_pTextComposeB;
    SText* m_pTextReadCompose;
    SText* m_pTextReadComposeB;
    SText* m_pTextIMEDesc;
    SText* m_pAlphaNative;
    unsigned short m_TargetAffect[32];
    TreeNode* m_pGroundObjectContainer;
    TMGround* m_pGroundList[2];
    TMObjectContainer* m_pObjectContainerList[2];
    int m_nCurrentGroundIndex;
    TMHuman* m_pMouseOverHuman;
    TMItem* m_pMouseOverItem;
    SMessagePanel* m_pMessagePanel;
    SText* m_pTextBillMsg;
    SMessageBox* m_pMessageBox;
    SMessageBox* m_pMessageBox2;
    char m_HeightMapData[256][256];
    char m_GateMapData[256][256];
    int n_bPrtScreen;
    short m_sPlayDemo;
    unsigned int m_dwStartCamTime;
    int m_bAutoRun;
    int m_bReverse;
    unsigned int m_dwInitTime;
    int m_nAdjustTime;
    int m_nCameraLoop;
    stCameraTick m_stCameraTick[1000];
    unsigned int m_dwDelayDisconnectTime;
    int m_bMsgRemoveServer;
};