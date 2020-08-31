#include "pch.h"
#include "TMBike.h"

TMBike::TMBike()
	: TMObject()
{
}

TMBike::~TMBike()
{
}

void TMBike::InitPosition(float fX, float fY, float fZ)
{
}

int TMBike::FrameMove(unsigned int dwServerTime)
{
	return 1;
}
