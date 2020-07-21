#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMSnow : public TMEffect
{
public:
    TMSnow(float fScale);
    ~TMSnow();

    int Render() override;
    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwOldServerTime;
    float m_fSpeed[200];
    TMVector3 m_vecSnowPosition[200];
    RDLVERTEX m_vertex[4];
    float m_fScale;
};
