#pragma once

#include "TMEffect.h"

class TMSkillFlash : public TMEffect
{
public:
    TMSkillFlash(TMVector3 vecPosition, int nType);
    ~TMSkillFlash();

    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    float m_fAngle;
    int m_nType;
};