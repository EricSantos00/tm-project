#pragma once

#include "TMEffect.h"

class TMShade;
class TMSkillFire : public TMEffect
{
public:
    TMSkillFire(TMVector3 vecPosition, int nType, TMObject* pOwner, unsigned int dwColor, unsigned int dwColor2);
    ~TMSkillFire();

    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    unsigned int m_dwLastTime;
    unsigned int m_dwColor;
    unsigned int m_dwColor2;
    float m_fAngle;
    int m_nType;
    TMShade* m_pLightMap;
};