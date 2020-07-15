#pragma once

class TMEffectBillBoard : public TMEffect
{
public:
	//Functions
	TMEffectBillBoard(int nTextureIndex, unsigned int dwLifeTime, float fScaleX, float fScaleY, float fScaleZ, float fVelocity, int nCycleCount, int nCycleTime);
	virtual ~TMEffectBillBoard();

    virtual int Render();
    virtual void SetColor(unsigned int dwColor);
    virtual int FrameMove(unsigned int dwServerTime);
    virtual void SetLifeTime(unsigned int dwLifeTime);
    virtual void SetLightMap(unsigned int dwColor, int nSize);

public:
	//Variables
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