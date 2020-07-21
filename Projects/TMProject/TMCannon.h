#pragma once

#include "TMItem.h"
#include "Structures.h"

class TMCannon : public TMItem
{
public:
    TMCannon();
    ~TMCannon();

    int FrameMove(unsigned int dwServerTime) override;
    void SetAngle(float fYaw, float fPitch, float fRoll) override;
    void SetPosition(float fX, float fY, float fZ) override;

public:
    TMVector2 m_vecBasePosition;
    unsigned int m_dwLastFireTime;
    float m_fSinF;
    float m_fCosF;
    float m_fCannonHeight;
    float m_fCannonLen;
    char m_cAutoFire;
    char m_cFire;
};