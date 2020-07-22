#include "pch.h"
#include "TMEffectBillBoard3.h"
#include "TMEffectMesh.h"
#include "TMArrow.h"

TMArrow::TMArrow(TMVector3 vecStart, TMVector3 vecTarget, int nLevel, int nType, char cAvatar, int nColor, int nDestID) 
	: TreeNode(0)
{
}

TMArrow::~TMArrow()
{
}

int TMArrow::Render()
{
	return 0;
}

int TMArrow::IsVisible()
{
	return 0;
}

int TMArrow::IsInView()
{
	return 0;
}

int TMArrow::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMArrow::ReleaseEffect()
{
}
