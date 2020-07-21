#pragma once

#include "TMEffect.h"

class TMSkillBash : public TMEffect
{
public:
	TMSkillBash(TMVector3 vecPosition, int nType);
	~TMSkillBash();

	int FrameMove(unsigned int dwServerTime) override;

public:
	unsigned int m_dwStartTime;
	unsigned int m_dwLifeTime;
	int m_nType;
	unsigned int m_dwLastTime;
};