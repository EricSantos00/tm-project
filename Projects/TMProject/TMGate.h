#pragma once

#include "TMItem.h"

enum class EGATE_STATE
{
    EGATE_OPEN = 0x1,
    EGATE_CLOSED = 0x2,
    EGATE_LOCKED = 0x3,
    EGATE_OPENING = 0x4,
    EGATE_CLOSING = 0x5,
    EGATE_LOCKING = 0x6,
};

class TMEffectBillBoard2;
class TMGate : public TMItem
{
public:
    TMGate();
    ~TMGate();

    virtual void InitGate(STRUCT_ITEM stItem);
    int Render() override;
    int FrameMove(unsigned int dwServerTime) override;
    virtual void SetState(EGATE_STATE eState);
    int IsMouseOver() override;

public:
    TMEffectBillBoard2* m_pEffectSpecial;
    float m_fOpenAngle;
    EGATE_STATE m_eState;
    unsigned int m_dwLastSetTime;
    short m_sItemIndex;
    int m_nLeftIndex;
    int m_nRightIndex;
    float m_fWidth;
    short m_sAuth;
    short m_sType;
    float m_StdMinus;
    float m_StdPlus;
    float m_RotMinus;
    float m_RotPlus;
};