#pragma once

#include "TreeNode.h"

class TMGround;
class TMLight;

constexpr auto MAX_OBJECT_LIST = 4096;
constexpr auto MAX_LIGHT_CONTAINER = 6;

class TMObjectContainer : public TreeNode
{
public:
    TMGround* m_pGround;
    int m_nLightIndex;
    TMLight* m_pLightContainer[MAX_LIGHT_CONTAINER];
    TreeNode* m_pGroundEffectContainer;
    int m_nObjectIndex;
    TMObject* m_pObjectList[MAX_OBJECT_LIST];

public:
    TMObjectContainer(TMGround* pGround);
    ~TMObjectContainer();

    int Load(const char* szFileName);
    int Save(const char* szFileName);
    int FrameMove(unsigned int dwServerTime);
};
