#pragma once

#include "TMEffect.h"

class TMObject;
class TMEffectCharge : public TMEffect
{
public:
    TMEffectCharge(TMObject* pParent, int nType, unsigned int dwColor);
    ~TMEffectCharge();
    
    int Render() override;
    int IsVisible() override;
    virtual void SetColor(unsigned int dwColor);
    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    unsigned int m_dwA;
    unsigned int m_dwR;
    unsigned int m_dwG;
    unsigned int m_dwB;
    float m_fAngle;
    float m_fProgress;
    int m_nType;

private:
    unsigned int m_dwRand;
};