#pragma once

#include "TMEffect.h"

class TMSkillThunderBolt : public TMEffect
{
public:
    TMSkillThunderBolt(TMVector3 vecPosition, int nType);
    ~TMSkillThunderBolt();

    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    float m_fAngle;
    int m_nType;
};