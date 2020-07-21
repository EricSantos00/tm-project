#pragma once

#include "TMObject.h"
#include "Basedef.h"
#include "TMHuman.h"

class TMEffectBillBoard2;
class TMEffectBillBoard;
class SText;
class TMItem : public TMObject
{
public:
    TMItem();
    ~TMItem();

    virtual void InitItem(STRUCT_ITEM stItem);
    int InitObject() override;
    void InitPosition(float fX, float fY, float fZ) override;
    int Render() override;
    int IsMouseOver() override;
    int FrameMove(unsigned int dwServerTime) override;
    void LabelPosition();

public:
    STRUCT_ITEM m_stItem;
    D3DMATERIAL9 m_Materials;
    SText* m_pNameLabel;
    int m_bCannot;
    int m_bMouseOver;
    int m_nItemType;
    short m_sMultiTexture;
    short m_sLegendType;
    TMEffectBillBoard2* m_pEffectSpecial;
    int m_bHPotion;
    int m_bBonusEffect;
    TMEffectBillBoard* m_pEffectBill[28];
    stGuildMarkInfo m_stGuildMark;
    unsigned int m_dwNameColor;
};
