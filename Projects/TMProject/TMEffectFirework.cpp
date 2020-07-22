#include "pch.h"
#include "TMEffectFirework.h"

TMEffectFireWork::TMEffectFireWork(TMVector3 vecPositiont, int nType) : TreeNode(0)
{
}

TMEffectFireWork::~TMEffectFireWork()
{
}

int TMEffectFireWork::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

int TMEffectFireWork::Render()
{
	return 0;
}

Particle* TMEffectFireWork::SetParticle(Particle* result, unsigned short wType, float fLifeTime, TMVector3 vBasePosition, TMVector3 vBaseVelocity)
{
	return nullptr;
}

void TMEffectFireWork::SetCustomFireWork(char* pBuffer)
{
}
