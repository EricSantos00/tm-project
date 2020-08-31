#include "pch.h"
#include "TMDust.h"

TMDust::TMDust(float fScale, int nType) 
	: TMObject()
{
}

TMDust::~TMDust()
{
}

int TMDust::Render()
{
	return 1;
}

int TMDust::FrameMove(unsigned int dwServerTime)
{
	return 1;
}
