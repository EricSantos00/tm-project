#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMEffectBillBoard2 : public TMEffect
{
public:
    TMEffectBillBoard2(int nTextureIndex, unsigned int dwLifeTime, float fScaleX, float fScaleY, float fScaleZ, float fVelocity, unsigned int dwVel);
    ~TMEffectBillBoard2();

    int Render() override;
    virtual void SetColor(unsigned int dwColor);
    int FrameMove(unsigned int dwServerTime) override;
    virtual void SetLifeTime(unsigned int dwLifeTime);

public:
    RDLVERTEX m_vertex[4];
    TMVector3 m_vecScale;
    float m_fScaleVel;
    unsigned int m_dwLifeTime;
    unsigned int m_dwCreateTime;
    unsigned int m_dwRotVel;
    int m_nTextureIndex;
    float m_fAxisAngle;
    int m_nFade;
    int m_bSlope;
    float m_fLocalHeight;
    float m_fProgress;
    unsigned int m_dwA;
    unsigned int m_dwR;
    unsigned int m_dwG;
    unsigned int m_dwB;
};