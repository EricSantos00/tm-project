#include "pch.h"
#include "TMObject.h"
#include "TMEffectStart.h"

TMEffectStart::TMEffectStart(TMVector3 vecPosition, int nType, TMObject* pOwner)
{
}

TMEffectStart::~TMEffectStart()
{
}

int TMEffectStart::Render()
{
	return 0;
}

int TMEffectStart::IsVisible()
{
	return 0;
}

int TMEffectStart::FrameMove(unsigned int dwServerTime)
{
	return 0;
}
