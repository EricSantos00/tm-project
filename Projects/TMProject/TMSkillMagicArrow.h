#pragma once

#include "TMEffect.h"

class TMObject;
class TMShade;
class TMEffectMesh;
class TMSkillMagicArrow : public TMEffect
{
public:
    TMSkillMagicArrow(TMVector3 vecStart, TMVector3 vecTarget, int nType, TMObject* pOwner);
    ~TMSkillMagicArrow();

    int Render() override;
    int IsVisible() override;
    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    TMVector3 m_vecStartPos;
    TMVector3 m_vecTargetPos;
    TMShade* m_pLightMap;
    TMEffectMesh* m_pEffectMesh;
    int m_nType;
    float m_fAngle;
    float m_fRotAngle;
    float m_fProgress;
    unsigned int m_dwLifeTime;
    unsigned int m_dwColor;
    unsigned int m_dwColor2;
};