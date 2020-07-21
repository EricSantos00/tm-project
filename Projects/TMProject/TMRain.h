#pragma once

#include "TMEffect.h"

class TMRain : public TMEffect
{
public:
	TMRain();
	~TMRain();

	int Render() override;
	int FrameMove(unsigned int dwServerTime) override;

public:
	unsigned int m_dwOldServerTime;
	float m_fSpeed[50];
	TMVector3 m_vecRainPosition[50];
	RDLVERTEX m_vertex[4];
};