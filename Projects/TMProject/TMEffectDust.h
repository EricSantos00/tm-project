#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMMesh;
class TMEffectDust : public TMEffect
{
public:
    TMEffectDust(TMVector3 vecPosition, float fRadius, int nDustType);
    ~TMEffectDust();

    int FrameMove(unsigned int dwServerTime) override;
    int Render() override;

public:
    int m_nDustType;
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    TMMesh* m_pMeshDropStone[4];
    TMVector3 m_vecStonePos[4];
    char m_cDroped[4];
};