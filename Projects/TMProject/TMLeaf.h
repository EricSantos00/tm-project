#pragma once

#include "TMObject.h"
#include "Structures.h"

class TMLeaf : public TMObject
{
public:
    TMLeaf(int nType);
    ~TMLeaf();

    int InitObject() override;
    int Render() override;
    int FrameMove(unsigned int dwServerTime) override;
    void RestoreDeviceObjects() override;
    void InvalidateDeviceObjects() override;
    void InitPosition(float fX, float fY, float fZ) override;

public:
    LOOK_INFO m_stLookInfo;
    SANC_INFO m_stSancInfo;
};