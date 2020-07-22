#include "pch.h"
#include "TMObject.h"
#include "TMEffectCharge.h"

TMEffectCharge::TMEffectCharge(TMObject* pParent, int nType, unsigned int dwColor)
{
}

TMEffectCharge::~TMEffectCharge()
{
}

int TMEffectCharge::Render()
{
	return 0;
}

int TMEffectCharge::IsVisible()
{
	return 0;
}

void TMEffectCharge::SetColor(unsigned int dwColor)
{
}

int TMEffectCharge::FrameMove(unsigned int dwServerTime)
{
	return 0;
}
