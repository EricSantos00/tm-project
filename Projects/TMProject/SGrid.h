#pragma once

#include "SControl.h"
#include "GeomObject.h"
#include "Structures.h"
#include "Basedef.h"
#include "TMFont2.h"

enum TMEGRIDTYPE
{
    GRID_DEFAULT = 0x0,
    GRID_SHOP = 0x1,
    GRID_CARGO = 0x2,
    GRID_SELL = 0x3,
    GRID_SKILLM = 0x4,
    GRID_SKILLB = 0x5,
    GRID_TRADEMY = 0x6,
    GRID_TRADEINV = 0x7,
    GRID_TRADENONE = 0x8,
    GRID_TRADEOP = 0x9,
    GRID_TRADEINV2 = 0xA,
    GRID_TRADEMY2 = 0xB,
    GRID_ITEMMIX = 0xC,
    GRID_TRADEINV3 = 0xD,
    GRID_ITEMMIX4 = 0xE,
    GRID_TRADEINV6 = 0xF,
    GRID_TRADEINV8 = 0x10,
    GRID_CUBEBOX = 0x11,
    GRID_QUICKSLOAT1 = 0x12,
    GRID_QUICKSLOAT2 = 0x13,
    GRID_QUICKSLOAT3 = 0x14,
    GRID_QUICKSLOAT4 = 0x15,
    GRID_QUICKSLOAT5 = 0x16,
    GRID_DELETE = 0x17,
    GRID_ITEMMIXRESULT = 0x18,
    GRID_ITEMMIXNEED = 0x19,
    GRID_MISSION_RESULT = 0x1A,
    GRID_MISSION_NEED = 0x1B,
    GRID_MISSION_NEEDLIST = 0x1C,
};
class SGridControlItem;
class SGridControl : public SPanel
{
public:
    SGridControl(unsigned int inTextureSetIndex, int inRowGridCount, int inColumnGridCount, float inX, float inY, float inWidth, float inHeight, TMEITEMTYPE type); 
    ~SGridControl();
    int OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY) override;
    void FrameMove2(stGeomList* pDrawList, TMVector2 ivParentPos, int inParentLayer, int nFlag) override;
    int CanItAdd(int* bFilledBuffer, int inCellIndexX, int inCellIndexY, int inCellWidth, int inCellHeight);
    int AddItem(SGridControlItem* ipNewItem, int inCellIndexX, int inCellIndexY);
    int AddSkillItem(SGridControlItem* ipNewItem, int inCellIndexX, int inCellIndexY);
    int SetItem(SGridControlItem* ipNewItem, int inCellIndexX, int inCellIndexY);
    IVector2* AddItemInEmpty(IVector2* result, SGridControlItem* ipNewItem);
    IVector2* CanAddItemInEmpty(IVector2* result, int nWidth, int nHeight);
    int CanChangeItem(SGridControlItem* ipNewItem, int inCellIndexX, int inCellIndexY, int bOnlyCheck);
    SGridControlItem* PickupItem(int inCellIndexX, int inCellIndexY);
    SGridControlItem* PickupAtItem(int inCellIndexX, int inCellIndexY);
    SGridControlItem* PickupItem_0(SGridControlItem* ipItem);
    SGridControlItem* SelectItem(int inCellIndexX, int inCellIndexY);
    SGridControlItem* GetItem(int inCellIndexX, int inCellIndexY);
    SGridControlItem* GetAtItem(int inCellIndexX, int inCellIndexY);
    SGridControlItem* GetItem_0(int nCount);
    int OnKeyDownEvent(unsigned int iKeyCode);
    void Empty();
    short CheckType(TMEITEMTYPE eType, TMEGRIDTYPE eGridType);
    short CheckPos(TMEITEMTYPE eType);
    void BuyItem(int nCellX, int nCellY);
    int TradeItem(int nCellX, int nCellY);
    int SellItem(int nCellX, int nCellY, unsigned int dwFlags, unsigned int wParam);
    int SellItem2();
    void SwapItem(int nCellX, int nCellY, int nCellVWidth, int nCellVHeight, STRUCT_ITEM* pItem);
    int MouseOver(int nCellX, int nCellY, int bPtInRect);
    void RButton(int nCellX, int nCellY, int bPtInRect);
    void UpdateCapsuleInfo(int nIndex);
    char AutoSellShowPrice(char* Price);
    char automove(int nCellX, int nCellY);
    int Check_ItemRightClick(int nType, int nItemSIndex);

public:
    TMEITEMTYPE m_eItemType;
    int m_nRowGridCount;
    int m_nColumnGridCount;
    int* m_pbFilled;
    GeomControl* m_GCGrid;
    int m_bDrawGrid;
    int m_nNumItem;
    SGridControlItem* m_pItemList[128];
    TMEGRIDTYPE m_eGridType;
    unsigned int m_dwMerchantID;
    unsigned int m_dwLastBuyTime;
    GeomControl m_GCEnable;
    unsigned int m_dwEnableColor;
    IVector2 m_vecPickupedPos;
    IVector2 m_vecPickupedSize;
    int m_nTradeMoney;
    unsigned int m_dwLastSortTime;
    int _nCellX;
    int _nCellY;
    unsigned int _dwFlags;
    unsigned int _wParam;
};

class SGridControlItem : public S3DObj
{
public:
    SGridControlItem(SGridControl* pParent, STRUCT_ITEM* pItem, float inX, float inY);
    ~SGridControlItem();

    virtual void SelectThis(int bSelect);
    virtual int IsSelect();
    virtual SGridControl* GetGridControl();
    virtual void SetGridControl(SGridControl* pGridControl);
    virtual STRUCT_ITEM* GetItem();

    void FrameMove2(stGeomList* pDrawList, TMVector2 ivItemPos, int inParentLayer, int nFlag) override;
    int PtInItem(int inPosX, int inPosY);
    int PtAtItem(int inPosX, int inPosY);

public:
    int m_nCellIndexX;
    int m_nCellIndexY;
    int m_nCellWidth;
    int m_nCellHeight;
    int m_bSelect;
    SGridControl* m_pGridControl;
    GeomControl m_GCEnable;
    GeomControl m_GCText;
    TMFont2 m_Font;
    STRUCT_ITEM* m_pItem;
    float m_fTimer;
};
