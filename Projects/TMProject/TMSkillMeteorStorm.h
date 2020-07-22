#pragma once

#include "TMEffect.h"

class TMObject;
class TMShade;
class TMEffectBillBoard;
class TMSkillMeteorStorm : public TMEffect
{
public:
    TMSkillMeteorStorm(TMVector3 vecStart, TMVector3 vecTarget, int nLevel, TMObject* pOwner);
    ~TMSkillMeteorStorm();

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
    TMEffectBillBoard* m_pCenterLight;
    TMEffectBillBoard* m_pCenterLight2;
    TMEffectBillBoard* m_pCenterFlare;
    float m_fLength;
    float m_fDestLength;
    int m_bPlaySound;
};