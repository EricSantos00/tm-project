#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMEffectLevelUp : public TMEffect
{
public:
    TMEffectLevelUp(TMVector3 vecPosition, int nType);
    ~TMEffectLevelUp();
    
    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    float m_fAngle;
    int m_nType;
};