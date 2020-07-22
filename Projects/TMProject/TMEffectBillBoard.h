#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMShade;
class TMEffectBillBoard : public TMEffect
{
public:
	TMEffectBillBoard(int nTextureIndex = 0, unsigned int dwLifeTime = 2000, float fScaleX = 0.5f, float fScaleY = 0.5f, float fScaleZ = 0.5f,
		float fVelocity = 0.0005f, int nCycleCount = 1, int nCycleTime = 80);
	~TMEffectBillBoard();

    int Render() override;
    virtual void SetColor(unsigned int dwColor);
    int FrameMove(unsigned int dwServerTime) override;
    virtual void SetLifeTime(unsigned int dwLifeTime);
    virtual void SetLightMap(unsigned int dwColor, int nSize);

public:
    RDLVERTEX m_vertex[4];
    TMVector3 m_vecScale;
    float m_fScaleVelX;
    float m_fScaleVelY;
    float m_fScaleVelZ;
    unsigned int m_dwLifeTime;
    unsigned int m_dwCreateTime;
    int m_bStickGround;
    int m_nFade;
    int m_bLookCam;
    int m_bFrameMove;
    int m_nTextureIndex;
    float m_fAxisAngle;
    float m_fProgress;
    float m_fBaseAlpha;
    int m_nCycleIndex;
    int m_nCycleCount;
    int m_nCycleTime;
    unsigned int m_dwA;
    unsigned int m_dwR;
    unsigned int m_dwG;
    unsigned int m_dwB;
    float m_fParticleH;
    float m_fParticleV;
    float m_fCircleSpeed;
    int m_nParticleType;
    TMVector3 m_vecStartPos;
    TMShade* m_pLightMap;
    int m_nAnimationType;
    TMVector3 m_vecDir;
    float m_fVel;
    TMVector3 m_vecRotAxis;
    float m_fRotAxisAngle;
    int m_bIsinit;
};