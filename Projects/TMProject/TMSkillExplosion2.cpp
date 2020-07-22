#include "pch.h"
#include "TMSkillExplosion2.h"

float TMSkillExplosion2::m_fDirX[8] = { 1.0,  1.0,  0.0, -1.0, -1.0, -1.0,  0.0,  1.0 };
float TMSkillExplosion2::m_fDirY[11] = { 0.0,  1.0,  1.0,  1.0,  0.0, -1.0, -1.0, -1.0,  0.0,  0.0,  0.0 };

TMSkillExplosion2::TMSkillExplosion2(TMVector3 vecPosition, int nType, float fRange, unsigned int dwTerm, unsigned int dwColor)
{
}

TMSkillExplosion2::~TMSkillExplosion2()
{
}

int TMSkillExplosion2::FrameMove(unsigned int dwServerTime)
{
	return 0;
}
