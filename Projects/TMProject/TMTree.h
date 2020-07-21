#pragma once

#include "TMObject.h"
#include "Structures.h"

class TMTree : public TMObject
{
public:
    TMTree(int nType);
    ~TMTree();

    int InitObject() override;
    int Render() override;
    int FrameMove(unsigned int dwServerTime) override;
    void RestoreDeviceObjects() override;
    void InvalidateDeviceObjects() override;
    void InitPosition(float fX, float fY, float fZ) override;
    virtual void SetAnimation(int nAniIndex);
    void InitLook(int nType);

public:
    LOOK_INFO m_stLookInfo;
    SANC_INFO m_stSancInfo;
    unsigned int m_dwLastTime;
};