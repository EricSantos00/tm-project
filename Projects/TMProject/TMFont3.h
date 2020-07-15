#pragma once

#include "TreeNode.h"
#include "TMFont2.h"
#include "Structures.h"

struct stNum
{
    int nX;
    int nY;
    int nTexIndex;
};

class TMFont3 : public TreeNode
{
public:
    TMFont3(char* szText, int nStartX, int nStartY, unsigned int dwColor, float fSize, unsigned int dwDelay,
		short sDir, unsigned int dwLifeTime, int bViewHalf, int nType);
    ~TMFont3();
    
    int Render() override;
    int FrameMove(unsigned int dwServerTime) override;

public:
    int m_nStrLen;
    stNum m_stNum[11];
    int m_nType;
    int m_nTextureSetIndex;
    short m_sDir;
    IVector2 m_vecPosition;
    IVector2 m_vecStartPosition;
    unsigned int m_dwCreateTime;
    unsigned int m_dwLifeTime;
    float m_fVisualProgress;
    float m_fScale;
    TMFont2 m_Font2;
    unsigned int m_dwDelay;
    int m_bVisible;
    int m_bViewHalf;
    int m_nSpeed;
    float m_fCurrScale;
    float m_fCurrSpeed;
};