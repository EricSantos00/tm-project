#pragma once

#include "TMEffect.h"

class TMDrop : public TMEffect
{
public:
    TMDrop(TMVector2 vec);
    ~TMDrop();

    int Render();
    int FrameMove(unsigned int dwServerTime);

public:
    TMVector2 m_vecPos;
    unsigned int m_dwOldServerTime;
    float m_fSpeed[10];
    TMVector3 m_vecDropPosition[10];
    RDLVERTEX m_vertex[4];
};