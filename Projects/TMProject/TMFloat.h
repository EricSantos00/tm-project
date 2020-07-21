#pragma once

#include "TMObject.h"
#include "Structures.h"

class TMEffectBillBoard2;
class TMFloat : public TMObject
{
public:
    TMFloat(int nType);
    ~TMFloat();

    int InitObject() override;
    int Render() override;
    int FrameMove(unsigned int dwServerTime) override;
    void RestoreDeviceObjects() override;
    void InvalidateDeviceObjects() override;
    void InitPosition(float fX, float fY, float fZ) override;

public:
    LOOK_INFO m_stLookInfo;
    SANC_INFO m_stSancInfo;
    TMEffectBillBoard2* m_pBillBoard;
    TMEffectBillBoard2* m_pWaterEffect[1];
    unsigned int m_dwWaterTime;
};