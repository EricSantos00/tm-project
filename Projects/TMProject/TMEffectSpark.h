#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMShade;
class TMObject;
class TMEffectBillBoard3;
class TMEffectSpark : public TMEffect
{
public:
    TMEffectSpark(TMVector3 vecStart, TMObject* pTarget, TMVector3 vecEnd, unsigned int dwColor, unsigned int dwColor2, unsigned int dwLifeTime, float fWidth, int nSparkCount, float fProgress);
    ~TMEffectSpark();
    
    int FrameMove(unsigned int dwServerTime) override;
    int SetLifeTime(unsigned int dwLifeTime);

public:
    float m_fWidth;
    float m_fRange;
    TMEffectBillBoard3* m_pSpark[5];
    TMShade* m_pShade[5];
    unsigned int m_dwColor;
    unsigned int m_dwColor2;
    unsigned int m_dwCreateTime;
    unsigned int m_dwLifeTime;
    TMVector3 m_vecStartPos;
    TMVector3 m_vecEndPos;
    int m_nSparkCount;
};