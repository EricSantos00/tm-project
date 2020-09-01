#include "pch.h"
#include "TMEffectBillBoard2.h"
#include "TMGate.h"

TMGate::TMGate()
	: TMItem()
{
}

TMGate::~TMGate()
{
}

void TMGate::InitGate(STRUCT_ITEM stItem)
{
}

int TMGate::Render()
{
	return 1;
}

int TMGate::FrameMove(unsigned int dwServerTime)
{
	return 1;
}

void TMGate::SetState(EGATE_STATE eState)
{
}

int TMGate::IsMouseOver()
{
	return 1;
}
