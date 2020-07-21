#pragma once

#include "TMObject.h"

class TMBike : public TMObject
{
public:
	TMBike();
	~TMBike();

	void InitPosition(float fX, float fY, float fZ) override;
	int FrameMove(unsigned int dwServerTime) override;

public:
	TMVector2 m_vecStartPosition;
};