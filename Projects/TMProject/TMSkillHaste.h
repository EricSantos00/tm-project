#pragma once

#include "TMEffect.h"

class TMSkillHaste : public TMEffect
{
public:
	TMSkillHaste(TMVector3 vecPosition, int nType);
	~TMSkillHaste();

	int FrameMove(unsigned int dwServerTime) override;

public:
	unsigned int m_dwStartTime;
	unsigned int m_dwLifeTime;
	float m_fAngle;
	int m_nType;
};