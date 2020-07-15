#pragma once

#include "TreeNode.h"

class TMVector3;
class TMObject;

class TMFireEffect : public TreeNode
{
public:
    TMFireEffect(TMVector3 vecStart, TMObject* pTarget, int nTextureIndex);
    ~TMFireEffect();
    
    int FrameMove(unsigned int dwServerTime);

public:
    TMVector3 m_vecStartPos;
    TMVector3 m_vecTargetPos;
    TMVector3 m_vecDistance;
    unsigned int m_dwCreateTime;
    unsigned int m_dwLifeTime;
    int m_nEntity;
    int m_nTextureIndex;
    float m_fLen;
};