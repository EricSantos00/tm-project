#pragma once

#include "TMEffect.h"

class TMShade;
class TMObject;
class TMSkillIceSpear : public TMEffect
{
public:
    TMSkillIceSpear(TMVector3 vecStart, TMVector3 vecTarget, int nLevel, TMObject* pOwner);
    ~TMSkillIceSpear();

    int Render() override;
    int IsVisible() override;
    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    TMVector3 m_vecStartPos;
    TMVector3 m_vecTargetPos;
    int m_nLevel;
    float m_fAngle;
    float m_fProgress;
    unsigned int m_dwLifeTime;
    TMShade* m_pLightMap;
};