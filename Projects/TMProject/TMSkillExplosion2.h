#pragma once

#include "TMEffect.h"

class TMSkillExplosion2 : public TMEffect
{
public:
    TMSkillExplosion2(TMVector3 vecPosition, int nType, float fRange, unsigned int dwTerm, unsigned int dwColor);
    ~TMSkillExplosion2();

    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    unsigned int m_dwLastTime;
    unsigned int m_dwTerm;
    unsigned int m_dwColor;
    int m_nType;
    float m_fRange;

    static float m_fDirX[8];
    static float m_fDirY[11];
};