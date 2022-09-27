#pragma once

class SControlContainer;
class SGridControl;
class SGridControlItem;
class SMessagePanel;
class SPanel;

#include "Structures.h"
#include "Basedef.h"

class CMission
{
public:
    CMission();
    virtual ~CMission();

    void ResultItemListSet();
    void Set_NeedItemList(int Index);
    void ResultItemHelpSet();
    void TakeItResource(SControlContainer* ControlContainer, unsigned short CharID);
    void InvClear(SGridControl** GridInvList);
    void CheckInv(SGridControl** GridInvList);
    void ClickInvItem(SGridControlItem* pItem, SGridControl** GridInvList, short Sourpage);
    void ClearGridList();
    void ClearResultGridList();
    void ClearNeedGridList();
    void SetTextList();
    void DoCombine(SMessagePanel* MessagePanel, SGridControl** GridInvList, int Class, int Lev, int Coin);

public:
    SControlContainer* m_pControlContainer;
    SGridControl** m_pGridInvList;
    SPanel* m_pMissionPanel;
    SGridControl* m_pGridResultItem[24];
    SGridControl* m_pGridNeedItem[8];
    STRUCT_MIXHELP m_stMissionHelp[100];
    unsigned short m_dwID;
    MSG_Mission m_stCombineItem;
    short m_sMissionIndex;
    STRUCT_MISSIONITEM m_dVolume[8];
};