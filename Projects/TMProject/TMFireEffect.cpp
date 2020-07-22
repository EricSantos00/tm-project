#include "pch.h"
#include "TMObject.h"
#include "TMFireEffect.h"

TMFireEffect::TMFireEffect(TMVector3 vecStart, TMObject* pTarget, int nTextureIndex) : TreeNode(0)
{
}

TMFireEffect::~TMFireEffect()
{
}

int TMFireEffect::FrameMove(unsigned int dwServerTime)
{
	return 0;
}
