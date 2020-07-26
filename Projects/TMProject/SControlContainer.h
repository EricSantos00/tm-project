#pragma once

#include "TreeNode.h"
#include "EventTranslator.h"
#include "GeomObject.h"

constexpr auto MAX_DRAW_CONTROL = 30;

class SControl;
class TMScene;
class SCursor;
class SControlContainer : public TreeNode, public IEventListener
{
public:
    SControlContainer(TMScene* pScene);
    ~SControlContainer();
    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
    int OnKeyDownEvent(unsigned int iKeyCode) override;
    int OnKeyUpEvent(unsigned int iKeyCode) override;
    int OnCharEvent(char iCharCode, int lParam) override;
    virtual int OnChangeIME();
    virtual int OnIMEEvent(char* ipComposeString);
    virtual void SetFocusedControl(SControl* pControl);
    int OnControlEvent(DWORD idwControlID, DWORD idwEvent) override;
    virtual void AddItem(SControl* pControl);
    int FrameMove(unsigned int dwServerTime) override;
    virtual SControl* FindControl(unsigned int dwID);
    void GenerateText(const char* pFileName);

public:
    SControl* m_pControlRoot;
    TMScene* m_pScene;
    SCursor* m_pCursor;
    int m_bInvisibleUI;
    int m_bCleanUp;
    stGeomList m_pDrawControl[MAX_DRAW_CONTROL];
    SControl* m_pFocusControl;
    SControl* m_pPickedControl;
    SControl* m_pModalControl[8];
};