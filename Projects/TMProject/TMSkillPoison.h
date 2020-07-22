#pragma once

#include "TMEffect.h"

class TMSkillPoison : public TMEffect
{
public:
    TMSkillPoison(TMVector3 vecPosition, unsigned int dwColor, int nCount, int bSound, int nType);
    ~TMSkillPoison();

    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    float m_fAngle;
    int m_nType;
};