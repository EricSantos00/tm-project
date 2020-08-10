#pragma once

#include "TreeNode.h"
#include "Structures.h"
#include "GeomObject.h"
#include "TMFont2.h"
#include "EventTranslator.h"

enum class CONTROL_TYPE : int
{
    CTRL_TYPE_NONE = -1,
    CTRL_TYPE_CURSOR = 0,
    CTRL_TYPE_PANEL = 1,
    CTRL_TYPE_BUTTON = 2,
    CTRL_TYPE_CHECKBOX = 3,
    CTRL_TYPE_RADIOBUTTON = 4,
    CTRL_TYPE_RADIOBUTTONSET = 5,
    CTRL_TYPE_LISTBOX = 6,
    CTRL_TYPE_LISTBOXITEM = 7,
    CTRL_TYPE_MESSAGEBOX = 8,
    CTRL_TYPE_MESSAGEPANEL = 9,
    CTRL_TYPE_PROGRESSBAR = 10,
    CTRL_TYPE_SCROLLBAR = 11,
    CTRL_TYPE_TEXT = 12,
    CTRL_TYPE_EDITABLETEXT = 13,
    CTRL_TYPE_DIALOG = 14,
    CTRL_TYPE_3DOBJ = 15,
    CTRL_TYPE_GRID = 16,
};

class IEventListener;
class SControl : public TreeNode
{
public:
    enum { TMC_NONE_ID };

    SControl(float inPosX, float inPosY, float inWidth, float inHeight);
    ~SControl();

    int OnPacketEvent(unsigned int dwCode, char* buf) override;
    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
    int OnKeyDownEvent(unsigned int iKeyCode) override;
    int OnKeyUpEvent(unsigned int iKeyCode) override;
    int OnCharEvent(char iCharCode, int lParam) override;

    virtual int OnChangeIME();
    virtual int OnIMEEvent(char* ipComposeString);
    virtual int IsIMENative();

    virtual void SetControlID(unsigned int idwControlID);
    virtual unsigned int GetControlID();
    virtual unsigned int GetUniqueID();
    virtual void SetEventListener(IEventListener* ipEventListener);
    virtual void Update();
    virtual void FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag);

    virtual void SetAlwaysOnTop(int bAlwaysOnTop);
    virtual void SetVisible(int bVisible);
    virtual void SetEnable(int bEnable);
    virtual void SetFocused(int bFocused);
   
    int IsVisible();
    int IsFocused();
    int IsOver();
    TMVector2 GetPos();
   
    virtual int ChildCount();
    virtual void SetPos(float nPosX, float nPosY);
    virtual void SetSize(float nWidth, float nHeight);

    void SetRealPos(float nPosX, float nPosY);
    void SetRealSize(float nWidth, float nHeight);
    void SetAutoSize();
    void SetCenterSize();
    void SetStickLeft();
    void SetStickRight();
    void SetStickTop();
    void SetStickBottom();
    int PtInControl(int inPosX, int inPosY);

    virtual CONTROL_TYPE GetControlType();
    virtual void SetCenterPos(unsigned int dwControlID, float inPosX, float inPosY, float inWidth, float inHeight);

public:
    static unsigned int m_dwStaticID;
    static int m_nGridCellSize;

public:
    int m_bAlwaysOnTop;
    int m_bVisible;
    int m_bEnable;
    int m_bFocused;
    int m_bOver;
    int m_bDeleteThisObject;
    int m_bSelectEnable;
    CONTROL_TYPE m_eCtrlType;
    unsigned int m_dwControlID;
    unsigned int m_dwUniqueID;
    float m_nPosX;
    float m_nPosY;
    float m_nWidth;
    float m_nHeight;
    IEventListener* m_pEventListener;
    int m_bModal;
};

class SPanel : public SControl
{
public:
    SPanel(int inTextureSetIndex, float inX, float inY, float inWidth, float inHeight, unsigned int idwColor, RENDERCTRLTYPE eRenderType); 
    ~SPanel();

    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
    virtual void SetTextureSetIndex(int inTextureSetIndex);
    virtual GeomControl* GetGeomControl();

    void SetVisible(int bVisible) override;
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag) override;

public:
    GeomControl m_GCPanel;
    SPanel* m_pDescPanel;
    int m_nPickPosX;
    int m_nPickPosY;
    int m_bPickable;
    int m_bPicked;
};

class S3DObj : public SControl
{
public:
    S3DObj(int nObjIndex, float inX, float inY, float inWidth, float inHeight);
    ~S3DObj();
    virtual void SetObjIndex(int nObjIndex);
    virtual GeomControl* GetGeomControl();

    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag) override;

public:
    GeomControl m_GCObj;
};

enum class ECursorStyle
{
    TMC_CURSOR_HAND = 0,
    TMC_CURSOR_CROSS_HAIR = 1,
    TMC_CURSOR_PICKUP = 2,
};

class SGridControlItem;
class SCursor : public SPanel
{
public:
    SCursor(int inTextureSetIndex, float inX, float inY, float inWidth, float inHeight);
    ~SCursor();

    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivParenPos, int inParentLayer, int nFlag) override;
    virtual void SetPosition(int iX, int iY);
    void SetVisible(int bVisible) override;
    virtual void SetStyle(ECursorStyle eStyle);
    virtual ECursorStyle GetStyle();
    GeomControl* GetGeomControl() override;
    virtual int AttachItem(SGridControlItem* pItem);
    virtual SGridControlItem* DetachItem();

public:
    ECursorStyle m_eStyle;
    SGridControlItem* m_pAttachedItem;
    GeomControl m_GeomItem;

    static int m_nCursorType;
    static HCURSOR m_hCursor1;
    static HCURSOR m_hCursor2;
};

class SText : public SControl
{
public:
    enum {
        TEXT_TYPE_NORMAL = 0x0,
        TEXT_TYPE_SHADOW = 0x1,
        TEXT_TYPE_TRANS = 0x2,
        TEXT_TYPE_FOCUS = 0x3
    };
    enum {
        TEXT_ALIGN_LEFT = 0x0,
        TEXT_ALIGN_CENTER = 0x1,
        TEXT_ALIGN_RIGHT = 0x2,
        TEXT_ALIGN_NOMARGINE = 0x3,
        TEXT_ALIGN_BATTLE = 0x4,
    };

public:
    SText(int inTextureSetIndex, const char* istrText, unsigned int idwFontColor, float inX, float inY, 
        float inWidth, float inHeight, int ibBorder, unsigned int idwBorderColor, unsigned int dwType, unsigned int dwAlignType);
    ~SText();
    virtual void SetText(char* istrText, int bCheckZero);
    virtual void SetTextColor(unsigned int dwFontColor);
    virtual char* GetText();
    virtual void SetType(unsigned int dwType);
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag) override;
    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;

public:
    TMFont2 m_Font;
    TMFont2 m_Font2;
    TMFont2 m_Font3;
    TMFont2 m_Font4;
    GeomControl m_GCText;
    GeomControl m_GCText2;
    GeomControl m_GCText3;
    GeomControl m_GCText4;
    unsigned int m_dwAlignType;
    unsigned int m_dwTextType;
    char m_cBorder;
    char m_cComma;
    GeomControl m_GCBorder;
};

class SEditableText : public SText
{
public:
    enum {
        TMEDIT_MSG_RETURN_PRESS = 0x0,
        TMEDIT_MSG_TAB_PRESS = 0x1,
        TMEDIT_MSG_PAGEUP_PRESS = 0x2,
        TMEDIT_MSG_UP_PRESS = 0x3,
        TMEDIT_MSG_PAGEDOWN_PRESS = 0x4,
        TMEDIT_MSG_DOWN_PRESS = 0x5,
        TMEDIT_MSG_DELETE_PRESS = 0x6,
        TMEDIT_MSG_NO_STRING = 0x7,
        TMEDIT_MSG_MAX_STRING = 0x8,
    };

public:
    SEditableText(int inTextureSetIndex, const char* istrText, size_t inMaxStringLen, int ibPasswd, 
        unsigned int idwFontColor, float inX, float inY, float inWidth, float inHeight, int ibBorder, 
        unsigned int idwBorderColor, unsigned int dwType, unsigned int dwAlignType);
    ~SEditableText();

    virtual void SetText(char* istrText);
    char* GetText() override;
    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
    int OnCharEvent(char iCharCode, int lParam) override;
    int OnChangeIME() override;
    int OnIMEEvent(char* ipComposeString) override;
    int OnKeyDownEvent(unsigned int iKeyCode) override;
    int OnKeyUpEvent(unsigned int iKeyCode) override;
    void Update() override;
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag) override;
    void SetFocused(int bFocused) override;
    int IsIMENative() override;

public:
    char m_strText[256];
    char m_strComposeText[256];
    char m_cTempChar;
    char m_cReserved;
    size_t m_nMaxStringLen;
    int m_nCursorVisible;
    int m_bPasswd;
    int m_bEncrypt;
    int m_bKorean;
};

class SButton : public SPanel
{
public:
    enum {
        TMC_IMAGE_COMMON = 0x0,
        TMC_IMAGE_OVER = 0x1,
        TMC_IMAGE_PRESS = 0x2,
        TMC_IMAGE_SELECTED = 0x3,
    };
    enum { TMC_BUTTON_CLICK = 0x0 };

public:
    SButton(int inTextureSetIndex, float inX, float inY, float inWidth, float inHeight, 
        unsigned int idwColor, int bSound, char* istrText);
    ~SButton();
    virtual void SetText(char* istrText);
    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
    virtual void SetSelected(int bSelected);
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag) override;
    void Update() override;

public:
    int m_bMouseOver;
    int m_bSelected;
    char m_cAlwaysAlt;
    char m_cBlink;
    SText* m_pAltText;
    int m_bPressed;
    int m_GrayType;

protected:
    unsigned int m_dwColor;
    int m_bSound;
    unsigned int m_dwOldTime;
};

class SButtonBox : public SControl
{
public:
    SButtonBox(float inPosX, float inPosY, float inWidth, float inHeight, int nStartCount, int nEndCount, int nCurrnetPage, int nPrevPage,
        int nNextPage, int nStartPage, int nEndPage);
    ~SButtonBox();

    void SetEventListener(IEventListener* ipEventListener) override;
    void SetButtonBox(int nStartCount, int nEndCount, int nCurrnetPage, int nPrevPage, int nNextPage, int nStartPage, int nEndPage);

public:
    SButton* m_pButtons[14];
    int m_nCurrentPage;
    int m_nStartCount;
    int m_nEndCount;
    int m_nStartPage;
    int m_nEndPage;
    int m_nPrevPage;
    int m_nNextPage;
};

class SCheckBox : public SPanel
{
public:
    enum {
        TMC_IMAGE_UNCHECKED = 0x0,
        TMC_IMAGE_CHECKED = 0x1,
    };
    enum {
        TMC_CHECKBOX_CHANGED = 0x0,
    };

public:
    SCheckBox(unsigned int inTextureSetIndex, float inX, float inY, float inWidth, float inHeight, unsigned int dwColor);
    ~SCheckBox();

    void SetValue(int ibValue);
    int GetValue();
    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
    void Update() override;

protected:
    int m_bValue;
    int m_bOver;
    unsigned int m_dwSelectedColor;
    unsigned int m_dwUnSelectedColor;
};

class SProgressBar : public SPanel
{
public:
    enum {
        PROGRESSBAR_DEFAULT_COLOR = 0x11111111,
    };
    enum {
        TMPROGRESS_STYLE_V = 0x0,
        TMPROGRESS_STYLE_H = 0x1,
        TMPROGRESS_STYLE_VH = 0x2,
    };
public:
    SProgressBar(int inTextureSetIndex, int inCurrent, int inMax, float inX, float inY, float inWidth, float inHeight,
        unsigned int idwProgressColor, unsigned int idwColor, unsigned int dwStyle);
    ~SProgressBar();

    virtual void SetCurrentProgress(int inCurrent);
    virtual void SetMaxProgress(int inMax);
    virtual int GetCurrentProgress();
    virtual int GetMaxProgress();
    void Update() override;
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag) override;
    virtual void ResetBar();

public:
    unsigned int m_dwStyle;
    int m_nCurrent;
    int m_nMax;
    float m_nProgressWidth;
    float m_nProgressHeight;
    GeomControl m_GCProgress;
    float m_InitHeight;
    float m_InitStartY;
    float m_InitWidth;
    float m_InitStartX;
};

class SScrollBar : public SControl, public IEventListener
{
public:
    enum {
        SCROLLBAR_DEFAULT_COLOR = 0x11111111,
    };
    enum {
        TMSCROLL_STYLE_V = 0x0,
        TMSCROLL_STYLE_H = 0x1,
    };
    enum {
        TMC_PANEL_UP = 0x0,
        TMC_PANEL_DOWN = 0x1,
        TMC_PANEL_BAR = 0x2,
        TMC_PANEL_BACK1 = 0x3,
        TMC_PANEL_BACK2 = 0x4,
    };
public:
    SScrollBar(int inCurrent, int inMax, float inX, float inY, float inWidth, float inHeight,
        unsigned int dwStyle, unsigned int idwBarColor, unsigned int idwColor, int bChat);
    ~SScrollBar();

    virtual void SetCurrentPos(int inCurrent);
    virtual int GetCurrentPos();
    virtual void SetMaxValue(int inMax);
    virtual int GetMaxValue();
    void SetSize(float nWidth, float nHeight) override;
    virtual void Up();
    virtual void Down();
    void Update() override;
    int OnControlEvent(DWORD idwControlID, DWORD idwEvent) override;
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag) override;
    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
    void upbarSetPos(float x, float y);
    void downbarSetPos(float x, float y);
    void upbarSetsize(float x, float y);
    void downbarSetsize(float x, float y);
    void upbarSetvisible(bool bSet);
    void downbarSetvisible(bool bSet);
    void scrollbarSetvisible(bool bSet);
    void scrollbarbackSetvisible(bool bSet);

protected:
    unsigned int m_dwStyle;
    int m_nCurrent;
    int m_nMax;
    int m_nScrollPos;
    int m_nScrollLength;
    float m_nBarSize;
    float m_nBtnSize;
    SPanel* m_pUpPanel;
    SPanel* m_pDownPanel;
    SPanel* m_pBar;

public:
    SPanel* m_pBackground1;
};

class SListBoxItem : public SText
{
public:
    SListBoxItem(const char* istrText, unsigned int idwFontColor, float inX, float inY, float inWidth, float inHeight,
        int ibBorder, unsigned int idwBorderColor, unsigned int dwType, unsigned int dwAlignType);
    ~SListBoxItem();
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag) override;
        
public:
    int m_bBGColor;
    unsigned int m_dwTime;
};

class SListBoxBoardItem : public SListBoxItem
{
public:
    SListBoxBoardItem(char* szIndex, char* szVIndex, char* szTitle, char* szWriter, char* szCount, char* szDate, unsigned int dwColor, int bTitile);
    ~SListBoxBoardItem();
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag) override;
    void SetPos(float nPosX, float nPosY) override;

public:
    SText* m_pTitleText;
    SText* m_pWriterText;
    SText* m_pCountText;
    SText* m_pDateText;
    char m_szIndex[256];
};

class SListBoxPartyItem : public SListBoxItem
{
public:
    SListBoxPartyItem(char* iStrText, unsigned int idwFontColor, float inX, float inY, float inWidth, float inHeight,
        unsigned int dwCharID, int nClass, int nLevel, int nHp, int nMaxHp);
    ~SListBoxPartyItem();

    void FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag) override;
        
public:
    unsigned int m_dwCharID;
    int m_nClass;
    int m_nLevel;
    int m_nState;
    SText* m_pLevelText;
    SPanel* m_pDirPanel;
    SProgressBar* m_pHpProgress;
};

class SListBoxServerItem : public SListBoxItem
{
public:
    SListBoxServerItem(int nTextureSet, char* iStrText, unsigned int idwFontColor, float inX, float inY, float inWidth, float inHeight,
        int nCount, char cCastle, char cGoldBug, int Num);
    ~SListBoxServerItem();
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag) override;
        
public:
    SProgressBar* m_pBusyProgress;
    SPanel* m_pCrownPanel;
    SPanel* m_pGoldBugPanel;
    SPanel* m_pAgePanel;
    int m_nCurrent;
    char m_cConnected;
    char m_cCastle;
    char m_cGoldBug;
};

class SListBox : public SPanel, public IEventListener
{
public:
    enum {
        TMC_SCROLL_BAR = 0x1,
        TMC_EDITBOX = 0x2,
    };

public:
    SListBox(int inTextureSetIndex, int inMaxCount, int inVisibleCount, float inX, float inY,
        float inWidth, float inHeight, unsigned int idwColor, RENDERCTRLTYPE eRenderType,
        int bSelectEnable, int bScrollBar, int bEditable);
    ~SListBox();

    int AddItem(SListBoxItem* ipNewItem);
    int DeleteItem(int inItemIndex);
    int DeleteItem(SListBoxItem* ipItem);
    SListBoxItem* GetItem(int inItemIndex);
    void Empty();
    void SetStartItemIndex(int nIndex);
    int GetSelectedIndex();
    void SetSelectedIndex(int nIndex);
    void SetSize(float nWidth, float nHeight) override;
    void SetPickSize(float nWidth, float nHeight);
    void SetEditable();
    int OnControlEvent(DWORD idwControlID, DWORD idwEvent) override;
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag) override;
    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
    void SetTextTimer(unsigned int dTime);

public:
    char m_cScrollBar;
    char m_cEditable;
    short m_sEditLine;
    int m_bRButton;
    int m_nMaxCount;
    int m_nVisibleCount;
    int m_nStartItemIndex;
    int m_nSelectedItem;
    float m_fPickWidth;
    float m_fPickHeight;
    SEditableText* m_pEditLine;
    SScrollBar* m_pScrollBar;
    int m_nNumItem;
    SListBoxItem* m_pItemList[1000];
    unsigned int m_dwSetTime;
    unsigned int m_dwNowTime;
};

class SMessageBox : public SPanel, public IEventListener
{
public:
    enum {
        TMC_OKBUTTON_ID = 0x1,
        TMC_CANCELBUTTON_ID = 0x2,
    };
    enum {
        TMC_MESSAGEBOX_MESSAGE = 0,
        TMC_MESSAGEBOX_ASK = 1,
        TMC_MESSAGEBOX_SLIDE = 2,
        TMC_MESSAGEBOX_COMPLEX = 3,
        TMC_MESSAGEBOX_OK = 4,
    };
    enum {
        TMC_MESSAGE_OK = 0x0,
        TMC_MESSAGE_CANCEL = 0x1,
    };

public:
    SMessageBox(const char* istrMessage, char ibyMessageBoxType, float inX, float inY);
    ~SMessageBox();

    int OnControlEvent(DWORD idwControlID, DWORD idwEvent) override;
    virtual void SetMessage(char* istrMessage, unsigned int dwMessageValue, char* istrMessage2);
    virtual void SetMessage(unsigned int dwMessageValue);
    virtual unsigned int GetMessageA();
    int OnCharEvent(char iCharCode, int lParam) override;
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag) override;
    void SetVisible(int bVisible) override;
    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;

public:
    unsigned int m_dwArg;
    unsigned int m_dwMessage;
    char m_byMessageBoxType;

protected:
    SPanel* m_pPanel1;
    SPanel* m_pPanel2;
    SText* m_pMessage;
    SText* m_pMessage2;
    SText* m_pCaption;
    SButton* m_pOKButton;
    SButton* m_pCancelButton;
    SPanel* m_pPanelBtn1;
    SPanel* m_pPanelBtn2;
};

class SMessagePanel : public SPanel
{
public:
    SMessagePanel(const char* istrMessage, float inX, float inY, float inWidth, float inHeight, unsigned int dwTime);
    ~SMessagePanel();

    void SetMessage(const char* istrMessage, unsigned int dwTime);
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag) override;
    virtual void SetVisible(int bVisible, int bSound);

public:
    SText* m_pText;
    SText* m_pText2;
    SPanel* m_pPanelL;
    SPanel* m_pPanelR;
    unsigned int m_dwOldServerTime;
    unsigned int m_dwLifeTime;
};

class SReelPanel : public SPanel
{
public:
    SReelPanel(unsigned int inTextureSetIndex, float inX, float inY, float inSizeX, float inSizeY, float inPitch);
    ~SReelPanel();

    void SetRoll(bool bRoll, int StopPos1, int StopPos2, int StopPos3, unsigned int StopTime);
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag) override;
    void SetVisible(int bVisible) override;
    void SetResult(char cResult);
    void UpDateJackpot();

public:
    SPanel* m_pGamBleReel[3][22];
    SPanel* m_pGamBleBox[2][9];
    SPanel* m_pJACKPOTCOUNT[10];
    SPanel* m_pJACKPOTBG;
    bool m_bGamBleBox[9];
    bool m_bRoling;
    int m_RollPos[3];
    int m_StopPos[3];
    unsigned int m_dwOldServerTime;
    unsigned int m_dwStopTime;
    int m_bResult;
    unsigned int m_dwJackpot;
    unsigned int m_dwJackPotView;
    unsigned int m_dwAutoTime;
    unsigned int m_dwBoxAniTime;
    int m_nPresent;
    TMVector2 m_vSize;
    int m_nPitch;
    unsigned int m_dwBatCoin;
};

int PointInRect(int inPosX, int inPosY, float ifX, float ifY, float ifWidth, float ifHeight);
void RemoveRenderControlItem(stGeomList* pDrawList, GeomControl* pGeomControl, int nLayer);
int AddRenderControlItem(stGeomList* pDrawList, GeomControl* pGeomControl, int nLayer);