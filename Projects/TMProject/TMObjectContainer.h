#pragma once

#include "TreeNode.h"

class TMGround;
class TMLight;

class TMObjectContainer : public TreeNode
{
public:
    TMGround* m_pGround;
    int m_nLightIndex;
    TMLight* m_pLightContainer[6];
    TreeNode* m_pGroundEffectContainer;
    int m_nObjectIndex;
    TMObject* m_pObjectList[4096];

public:
    TMObjectContainer(TMGround* pGround);
    ~TMObjectContainer();

    int Load(const char* szFileName);
    int Save(const char* szFileName);
    int FrameMove(unsigned int dwServerTime);
};
