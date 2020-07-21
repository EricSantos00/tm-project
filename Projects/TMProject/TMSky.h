#pragma once

#include "TMObject.h"
#include "TMEffectBillBoard.h"

class TMMesh;
class TMSky : public TMObject
{
public:
    TMSky();
    ~TMSky();

    int Render() override;
    int FrameMove(unsigned int dwServerTime) override;
    void RestoreDeviceObjects() override;
    void SetWeatherState(int nState);

public:
    int m_nTextureIndex;
    int m_nState;
    unsigned int m_dwStartTime;
    unsigned int m_dwChangeTime;
    TMMesh* n_pMeshMilkyway;
    TMEffectBillBoard m_ebStars[20];
    TMEffectBillBoard m_ebMoon[2];
    unsigned int m_dwR[4];
    unsigned int m_dwG[4];
    unsigned int m_dwB[4];

    static D3DCOLORVALUE m_LightVal[4];
    static float FogList[16][2];
};
