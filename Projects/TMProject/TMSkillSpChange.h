#pragma once

#include "TMEffect.h"

class TMObject;
class TMShade;
class TMEffectParticle;
class TMSkillSpChange : public TMEffect
{
public:
    TMSkillSpChange(TMVector3 vecPosition, int nType, TMObject* pOwner);
    ~TMSkillSpChange();

    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    float m_fAngle;
    int m_nType;
    float m_fScale;
    TMShade* m_pLightMap;
    TMEffectParticle* m_pParticle;
};