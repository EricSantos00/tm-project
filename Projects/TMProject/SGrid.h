#pragma once

#include "SControl.h"
#include "GeomObject.h"
#include "Structures.h"
#include "Basedef.h"
#include "TMFont2.h"

enum class TMEGRIDTYPE
{
    GRID_DEFAULT = 0,
    GRID_SHOP = 1,
    GRID_CARGO = 2,
    GRID_SELL = 3,
    GRID_SKILLM = 4,
    GRID_SKILLB = 5,
    GRID_TRADEMY = 6,
    GRID_TRADEINV = 7,
    GRID_TRADENONE = 8,
    GRID_TRADEOP = 9,
    GRID_TRADEINV2 = 10,
    GRID_TRADEMY2 = 11,
    GRID_ITEMMIX = 12,
    GRID_TRADEINV3 = 13,
    GRID_ITEMMIX4 = 14,
    GRID_TRADEINV6 = 15,
    GRID_TRADEINV8 = 16,
    GRID_CUBEBOX = 17,
    GRID_QUICKSLOAT1 = 18,
    GRID_QUICKSLOAT2 = 19,
    GRID_QUICKSLOAT3 = 20,
    GRID_QUICKSLOAT4 = 21,
    GRID_QUICKSLOAT5 = 22,
    GRID_DELETE = 23,
    GRID_ITEMMIXRESULT = 24,
    GRID_ITEMMIXNEED = 25,
    GRID_MISSION_RESULT = 26,
    GRID_MISSION_NEED = 27,
    GRID_MISSION_NEEDLIST = 28,
};

static int g_pItemGridXY[8][2] =
{
  { 1, 1 },
  { 1, 2 },
  { 1, 3 },
  { 1, 4 },
  { 2, 1 },
  { 2, 2 },
  { 2, 3 },
  { 2, 4 }
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
    IVector2 AddItemInEmpty(SGridControlItem* ipNewItem);
    IVector2 CanAddItemInEmpty(int nWidth, int nHeight);
    int CanChangeItem(SGridControlItem* ipNewItem, int inCellIndexX, int inCellIndexY, int bOnlyCheck);
    SGridControlItem* PickupItem(int inCellIndexX, int inCellIndexY);
    SGridControlItem* PickupAtItem(int inCellIndexX, int inCellIndexY);
    SGridControlItem* PickupItem(SGridControlItem* ipItem);
    SGridControlItem* SelectItem(int inCellIndexX, int inCellIndexY);
    SGridControlItem* GetItem(int inCellIndexX, int inCellIndexY);
    SGridControlItem* GetAtItem(int inCellIndexX, int inCellIndexY);
    SGridControlItem* GetItem(int nCount);
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

public:
    static inline short m_sLastMouseOverIndex{-1};
    static SGridControlItem* m_pLastMouseOverItem;
    static SGridControlItem* m_pLastAttachedItem;
    static SGridControlItem* m_pSellItem;
    static int m_bNeedUpdate;
    static char* m_szParamString[49];
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
