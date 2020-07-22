#pragma once

#include "TMEffect.h"

class TMSkillFreezeBlade : public TMEffect
{
public:
    TMSkillFreezeBlade(TMVector3 vecPosition, int nType, int nType2, int nType3);
    ~TMSkillFreezeBlade();

    int Render() override;
    int IsVisible() override;
    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    unsigned int m_dwLastTime;
    TMVector2 m_vecNextD;
    float m_fProgress;
    float m_fAngle;
    int m_nType;
    int m_nType2;
    int m_nType3;
    int m_nMeshIndex;
    int m_bNext;
};