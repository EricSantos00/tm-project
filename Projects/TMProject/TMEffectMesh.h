#pragma once

#include "TMEffect.h"

class TMMesh;
class TMEffectMesh : public TMEffect
{
public:
    TMEffectMesh(int nMeshIndex, unsigned int dwColor, float fAngle, int nType);
    ~TMEffectMesh();

    int Render() override;
    int FrameMove(unsigned int dwServerTime) override;
    void SetColor(unsigned int dwColor);
    int IsVisible() override;
    int IsInView();

public:
    TMMesh* m_pMesh;
    int m_nMeshIndex;
    unsigned int m_dwColor;
    float m_fAngle;
    float m_fAngle2;
    float m_fAngle3;
    float m_fScaleH;
    float m_fScaleV;
    int m_nType;
    int m_nTextureIndex;
    float m_fProgress;
    char m_cShine;
    char m_cUScroll;
    unsigned int m_dwLifeTime;
    unsigned int m_dwCreateTime;
    unsigned int m_dwCycleTime;
    unsigned int m_dwA;
    unsigned int m_dwR;
    unsigned int m_dwG;
    unsigned int m_dwB;
};