#include "pch.h"
#include "TMEffectParticle.h"

TMEffectParticle::TMEffectParticle(TMVector3 vecPosition, int nType, int nCount, float fSize, unsigned int dwColor, int bRand, int nTextureIndex, float fRadius, int bBright, TMVector3 vecDir, unsigned int dwLifeTime)
{
}

TMEffectParticle::~TMEffectParticle()
{
}

int TMEffectParticle::Render()
{
	return 0;
}

int TMEffectParticle::IsVisible()
{
	return 0;
}

int TMEffectParticle::FrameMove(unsigned int dwServerTime)
{
	return 0;
}
