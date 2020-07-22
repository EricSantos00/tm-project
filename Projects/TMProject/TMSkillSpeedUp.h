#pragma once

#include "TMEffect.h"

class TMSkillSpeedUp : public TMEffect
{
public:
    TMSkillSpeedUp(TMVector3 vecPosition, int nType);
    ~TMSkillSpeedUp();

    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    float m_fAngle;
    int m_nType;
};