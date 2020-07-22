#pragma once

#include "TMEffect.h"

class TMObject;
class TMSkillHeal : public TMEffect
{
public:
    TMSkillHeal(TMVector3 vecPosition, int nType, TMObject* pOwner);
    ~TMSkillHeal();

    int FrameMove(unsigned int dwServerTime) override;

public:
    unsigned int m_dwStartTime;
    unsigned int m_dwLifeTime;
    unsigned int m_dwLastTime;
    int m_nType;
};