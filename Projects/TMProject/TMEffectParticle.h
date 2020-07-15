#pragma once

#include "TMEffect.h"

class TMVector3;

class TMEffectParticle : public TMEffect
{
public:
    TMEffectParticle(TMVector3 vecPosition, int nType, int nCount, float fSize, unsigned int dwColor, int bRand, int nTextureIndex, float fRadius, int bBright, TMVector3 vecDir, unsigned int dwLifeTime);
    ~TMEffectParticle();
    
    int Render();
    int IsVisible();
    int FrameMove(unsigned int dwServerTime);

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    float m_fAngle;
    int m_nType;
};