#pragma once

#include "TreeNode.h"
#include "Structures.h"
#include "GeomObject.h"

enum class CONTROL_TYPE : int
{
    CTRL_TYPE_NONE = -1,
    CTRL_TYPE_CURSOR = 0x0,
    CTRL_TYPE_PANEL = 0x1,
    CTRL_TYPE_BUTTON = 0x2,
    CTRL_TYPE_CHECKBOX = 0x3,
    CTRL_TYPE_RADIOBUTTON = 0x4,
    CTRL_TYPE_RADIOBUTTONSET = 0x5,
    CTRL_TYPE_LISTBOX = 0x6,
    CTRL_TYPE_LISTBOXITEM = 0x7,
    CTRL_TYPE_MESSAGEBOX = 0x8,
    CTRL_TYPE_MESSAGEPANEL = 0x9,
    CTRL_TYPE_PROGRESSBAR = 0xA,
    CTRL_TYPE_SCROLLBAR = 0xB,
    CTRL_TYPE_TEXT = 0xC,
    CTRL_TYPE_EDITABLETEXT = 0xD,
    CTRL_TYPE_DIALOG = 0xE,
    CTRL_TYPE_3DOBJ = 0xF,
    CTRL_TYPE_GRID = 0x10,
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
    TMVector2* GetPos(TMVector2* result);
   
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

    virtual int GetControlType();
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

enum ECursorStyle
{
    TMC_CURSOR_HAND = 0x0,
    TMC_CURSOR_CROSS_HAIR = 0x1,
    TMC_CURSOR_PICKUP = 0x2,
};

class SGridControlItem;
class SCursor : public SPanel
{
public:
    SCursor(int inTextureSetIndex, float inX, float inY, float inWidth, float inHeight);
    ~SCursor();

    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int Y) override;
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
    SText(int inTextureSetIndex, char* istrText, unsigned int idwFontColor, float inX, float inY, 
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

