#include "pch.h"
#include "TMObject.h"
#include "TMEffectBillBoard.h"
#include "TMEffectMeshRotate.h"

TMEffectMeshRotate::TMEffectMeshRotate(TMVector3 vecPosition, int nType, TMObject* pOwner, int bFire, int bCenter)
{
}

TMEffectMeshRotate::~TMEffectMeshRotate()
{
}

int TMEffectMeshRotate::Render()
{
	return 0;
}

int TMEffectMeshRotate::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMEffectMeshRotate::SetColor(unsigned int dwColor)
{
}
