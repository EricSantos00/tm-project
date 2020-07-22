#pragma once

#include "TMEffect.h"

class TMEffectBillBoard2;
class TMSkillJudgement : public TMEffect
{
public:
	TMSkillJudgement(TMVector3 vecPosition, int nType, float fSetScale);
	~TMSkillJudgement();

	int FrameMove(unsigned int dwServerTime) override;

public:
	int m_nType;
	TMEffectBillBoard2* m_pEffect1;
	TMEffectBillBoard2* m_pEffect2;
	unsigned int m_dwStartTime;
	unsigned int m_dwLifeTime;
};