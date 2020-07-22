#pragma once

#include "TMObject.h"

class TMMesh;
class TMSea : public TMObject
{
public:
    TMSea();
    ~TMSea();

    int Render() override;
    int InitObject() override;
    void InitPosition(float fX, float fY, float fZ) override;
    D3DXVECTOR3* GetPickPos(D3DXVECTOR3* result);
    float GetHeight(float fX, float fY);
    int FrameMove(unsigned int dwServerTime) override;
    int IsVisible() override;

public:
    int m_nGridNumX;
    int m_nGridNumY;
    RECT m_rectRange;
    unsigned int m_dwServerTime;
    TMMesh* m_pMesh;
    D3DMATERIAL9 m_materials;
    int m_nPickX;
    int m_nPickY;
    int m_bAlpha;
};
