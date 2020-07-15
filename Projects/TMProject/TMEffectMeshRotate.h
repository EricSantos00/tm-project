#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMObject;
class TMEffectBillBoard;
class TMEffectMeshRotate : public TMEffect
{
public:
    TMEffectMeshRotate(TMVector3 vecPosition, int nType, TMObject* pOwner, int bFire, int bCenter);
    ~TMEffectMeshRotate();
    
    int Render() override;
    int FrameMove(unsigned int dwServerTime) override;
    void SetColor(unsigned int dwColor);

public:
    TMEffectBillBoard* m_pBillBoard;
    TMVector3 m_vecStartPos;
    unsigned int m_dwStartTime;
    unsigned int m_dwRotateTime;
    unsigned int m_dwLifeTime;
    int m_bCenter;
    int m_bScale;
    float m_fAngle;
    float m_fAngle2;
    float m_fRadius;
    int m_nType;
    int m_nMeshIndex;
    float m_fScale;
    unsigned int m_dwA;
    unsigned int m_dwR;
    unsigned int m_dwG;
    unsigned int m_dwB;
};