#include "pch.h"
#include "TMLight.h"

unsigned int TMLight::m_dwBaseLightIndex = 2;

TMLight::TMLight(D3DCOLORVALUE col, int bEnable) : 
	TreeNode(0)
{
}

TMLight::~TMLight()
{
}

void TMLight::InitPosition(float fX, float fY, float fZ)
{
}

int TMLight::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

int TMLight::IsVisible()
{
	return 0;
}
