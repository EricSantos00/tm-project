#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMSkillSnow : public TMEffect
{
public:
    TMSkillSnow(TMVector3 vecTarget);
    ~TMSkillSnow();

    int Render() override;
    int IsVisible() override;
    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwOldServerTime;
    float m_fSpeed[1000];
    TMVector3 m_vecSnowPos[1000];
    RDLVERTEX m_vertex[4];
    float m_fScale;
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    TMVector3 m_vecTarget;
};