#pragma once

#include "TreeNode.h"

//The TMEffect include is just to catch the RDLVERTEX struct...
#include "TMEffect.h"

class TMVector3;

struct Particle
{
    TMVector3 vPosition;
    TMVector3 vLaunchVelocity;
    TMVector3 vInitialPosition;
    TMVector3 vInitialVelocity;
    float fLifetime;
    float fMaturity;
    unsigned short wType;
    float fSize;
};

class TMEffectFireWork : public TreeNode
{
public:
    TMEffectFireWork(TMVector3 vecPositiont, int nType);
    ~TMEffectFireWork();
    
    int FrameMove(unsigned int dwServerTime);
    int Render();
    Particle* SetParticle(Particle* result, unsigned short wType, float fLifeTime, TMVector3 vBasePosition, TMVector3 vBaseVelocity);
    void SetCustomFireWork(char* pBuffer);

public:
    int m_nType;
    unsigned int m_dwColor;
    RDLVERTEX m_vertex[4];
    Particle m_Particle[100];
    unsigned int m_dwStartTime;
    int m_bBomb;
    TMVector3 m_vAddFireWork[100];
    int m_nColorType;
    char m_ArrCustomShape[100];
};