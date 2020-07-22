#pragma once

#include "TMEffect.h"

class TMObject;
class TMSkillSlowSlash : public TMEffect
{
public:
    TMSkillSlowSlash(TMVector3 vecStart, TMVector3 vecTarget, int nType, TMObject* pOwner);
    ~TMSkillSlowSlash();

    int FrameMove(unsigned int dwServerTime) override;

public:
    TMVector3 m_vecStartPos;
    TMVector3 m_vecTargetPos;
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    unsigned int m_dwLastTime;
    int m_nType;
    int m_nTextureIndex;
};