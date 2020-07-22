#pragma once

#include "TMEffect.h"

class TMSkillHolyTouch : public TMEffect
{
public:
    TMSkillHolyTouch(TMVector3 vecPosition, int nType);
    ~TMSkillHolyTouch();

    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    float m_fAngle;
    int m_nType;
};