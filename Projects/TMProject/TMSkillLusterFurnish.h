#pragma once

#include "TMEffect.h"

class TMSKillLusterFurnish : public TMEffect
{
public:
    TMSKillLusterFurnish(TMVector3 vecStart, TMVector3 vecEnd);
    ~TMSKillLusterFurnish();

    int FrameMove(unsigned int dwServerTime) override;
    int Render() override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    TMVector3 m_vecStartPos;
    TMVector3 m_vecEndPos;
};