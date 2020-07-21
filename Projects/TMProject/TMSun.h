#pragma once

#include "TreeNode.h"

struct stFlare
{
    int nTexIndex;
    float fLoc;
    float fScale;
    unsigned int diffuse;
};

class TMSun : public TreeNode
{
public:
    TMSun();
    ~TMSun();

    virtual int InitObject();
    int Render() override;
    virtual int FrameMove();

public:
    stFlare m_stFlareArray[12];
    D3DXVECTOR3 m_vFlareDirection;
    RDTLVERTEX m_vecTLVertex[4];
    int bInViewPort;
    int m_bHide;
    float m_fDefSize;
};