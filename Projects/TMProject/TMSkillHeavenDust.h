#pragma once

#include "TMEffect.h"

class TMSkillHeavensDust : public TMEffect
{
public:
	TMSkillHeavensDust(TMVector3 vecPosition, int nType);
	~TMSkillHeavensDust();

	int FrameMove(unsigned int dwServerTime) override;

public:
	unsigned int m_dwStartTime;
	unsigned int m_dwLifeTime;
	float m_fAngle;
	int m_nType;
};