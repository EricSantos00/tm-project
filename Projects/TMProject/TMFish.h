#pragma once

#include "TMObject.h"
#include "Structures.h"

class TMFish : public TMObject
{
public:
    TMFish(unsigned int dwObjType, int nType);
    ~TMFish();

    int InitObject() override;
    int Render() override;
    int FrameMove(unsigned int dwServerTime) override;
    void RestoreDeviceObjects() override;
    void InvalidateDeviceObjects() override;
    void InitPosition(float fX, float fY, float fZ) override;
    virtual void SetAnimation(int nAniIndex);

public:
    int m_nType;
    LOOK_INFO m_stLookInfo;
    SANC_INFO m_stSancInfo;
    int m_nMotionType;
    float m_fCircleSpeed;
    float m_fParticleH;
    TMVector3 m_vecStartPos;
    unsigned int m_dwStartTime;
};