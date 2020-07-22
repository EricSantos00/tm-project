#include "pch.h"
#include "TMMesh.h"
#include "TMSea.h"

TMSea::TMSea()
{
}

TMSea::~TMSea()
{
}

int TMSea::Render()
{
	return 0;
}

int TMSea::InitObject()
{
	return 0;
}

void TMSea::InitPosition(float fX, float fY, float fZ)
{
}

D3DXVECTOR3* TMSea::GetPickPos(D3DXVECTOR3* result)
{
	return nullptr;
}

double TMSea::GetHeight(float fX, float fY)
{
	return 0.0;
}

int TMSea::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

int TMSea::IsVisible()
{
	return 0;
}
