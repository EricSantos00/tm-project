#pragma once

#include "TMEffect.h"

class TMVector3;
class TMObject;

class TMEffectStart : public TMEffect
{
public:
	TMEffectStart(TMVector3 vecPosition, int nType, TMObject* pOwner);
	~TMEffectStart();
	
	int Render();
	int IsVisible();
	int FrameMove(unsigned int dwServerTime);

public:
	unsigned int m_dwStartTime;
	unsigned int m_dwLifeTime;
	float m_fAngle;
	float m_fProgress;
	int m_nType;
};