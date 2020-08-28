#pragma once

#include "TMEffect.h"
#include "Structures.h"

class TMObject;
class TMEffectStart : public TMEffect
{
public:
	TMEffectStart(TMVector3 vecPosition, int nType, TMHuman* pOwner);
	~TMEffectStart();
	
	int Render() override;
	int IsVisible() override;
	int FrameMove(unsigned int dwServerTime) override;

public:
	unsigned int m_dwStartTime;
	unsigned int m_dwLifeTime;
	float m_fAngle;
	float m_fProgress;
	int m_nType;
};