#include "pch.h"
#include "TMShade.h"
#include "TMObject.h"
#include "TMEffectBillBoard3.h"
#include "TMEffectSpark.h"

TMEffectSpark::TMEffectSpark(TMVector3 vecStart, TMObject* pTarget, TMVector3 vecEnd, unsigned int dwColor, unsigned int dwColor2, unsigned int dwLifeTime, float fWidth, int nSparkCount, float fProgress)
{
}

TMEffectSpark::~TMEffectSpark()
{
}

int TMEffectSpark::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

int TMEffectSpark::SetLifeTime(unsigned int dwLifeTime)
{
	return 0;
}
