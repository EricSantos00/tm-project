#pragma once

#include "TMEffect.h"

class TMSkillCure : public TMEffect
{
public:
    TMSkillCure(TMVector3 vecPosition, int nType);
    ~TMSkillCure();

    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    float m_fAngle;
    int m_nType;
};