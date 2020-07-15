#pragma once

#include "TMEffect.h"

class TMVector3;

class TMEffectGold : public TMEffect
{
public:
    TMEffectGold(TMVector3 vecStart, float vecLiveTime);
    ~TMEffectGold();
    int FrameMove(unsigned int dwServerTime);
    int Render();

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    TMVector3 m_vecStartPos;
    TMVector3 m_vecEndPos;
    float m_LiveTime;
    float m_Hight;
    int m_Meshidx;
};