#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMEffectBillBoard4 : public TMEffect
{
public:
    TMEffectBillBoard4(int nTextureIndex, unsigned int dwLifeTime, float fScaleX, float fScaleY, float fVelocity, int nCycleCount, int nCycleTime);
    ~TMEffectBillBoard4();

    int Render() override;
    virtual void SetColor(unsigned int dwColor);
    int FrameMove(unsigned int dwServerTime) override;
    
    void SetPosition(int nX, int nY);
    void SetParticle(float fH, float fV);

public:
    RDTLVERTEX m_vertex[4];
    TMVector2 m_vecScale;
    unsigned int m_dwLifeTime;
    unsigned int m_dwCreateTime;
    int m_nFade;
    float m_fScaleVelX;
    float m_fScaleVelY;
    int m_nTextureIndex;
    float m_fProgress;
    int m_nCycleIndex;
    int m_nCycleCount;
    int m_nCycleTime;
    float m_fParticleH;
    float m_fParticleV;
    unsigned int m_dwA;
    unsigned int m_dwR;
    unsigned int m_dwG;
    unsigned int m_dwB;
    IVector2 m_vecPosition;
};