#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMShade;
class TMEffectBillBoard;
class TMSkillDoubleSwing : public TMEffect
{
public:
    TMSkillDoubleSwing(TMVector3 vecStart, TMVector3 vecTarget, int nLevel, TMObject* pOwner);
    ~TMSkillDoubleSwing();

    int Render() override;
    int IsVisible() override;
    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    TMVector3 m_vecStartPos;
    TMVector3 m_vecTargetPos;
    int m_nLevel;
    int m_nMeshIndex;
    float m_fAngle;
    float m_fAngle2;
    float m_fProgress;
    unsigned int m_dwLifeTime;
    unsigned int m_dwOldTime;
    TMShade* m_pLightMap;
    TMEffectBillBoard* m_pCenterLight;
    TMEffectBillBoard* m_pCenterLight2;
    TMEffectBillBoard* m_pCenterFlare;
};