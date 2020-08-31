#include "pch.h"
#include "TMEffectBillBoard2.h"
#include "TMFloat.h"

TMFloat::TMFloat(int nType)
	: TMObject()
{
}

TMFloat::~TMFloat()
{
}

int TMFloat::InitObject()
{
	return 1;
}

int TMFloat::Render()
{
	return 1;
}

int TMFloat::FrameMove(unsigned int dwServerTime)
{
	return 1;
}

void TMFloat::RestoreDeviceObjects()
{
}

void TMFloat::InvalidateDeviceObjects()
{
}

void TMFloat::InitPosition(float fX, float fY, float fZ)
{
}
