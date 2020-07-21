#pragma once

#include "TMObject.h"

class TMDust : public TMObject
{
public:
	TMDust(float fScale, int nType);
	~TMDust();

	int Render() override;
	int FrameMove(unsigned int dwServerTime) override;

public:
	int m_nType;
	unsigned int m_dwLastTime;
	float m_fScaleH;
	float m_fScaleV;
};