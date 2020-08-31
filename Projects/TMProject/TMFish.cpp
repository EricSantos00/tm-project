#include "pch.h"
#include "TMFish.h"

TMFish::TMFish(unsigned int dwObjType, int nType)
	: TMObject()
{
}

TMFish::~TMFish()
{
}

int TMFish::InitObject()
{
	return 1;
}

int TMFish::Render()
{
	return 1;
}

int TMFish::FrameMove(unsigned int dwServerTime)
{
	return 1;
}

void TMFish::RestoreDeviceObjects()
{
}

void TMFish::InvalidateDeviceObjects()
{
}

void TMFish::InitPosition(float fX, float fY, float fZ)
{
}

void TMFish::SetAnimation(int nAniIndex)
{
}
