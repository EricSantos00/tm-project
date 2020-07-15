#pragma once

class TMVector3;

class TMEffectLevelUp
{
public:
    TMEffectLevelUp(TMVector3 vecPosition, int nType);
    ~TMEffectLevelUp();
    
    int FrameMove(unsigned int dwServerTime);

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    float m_fAngle;
    int m_nType;
};