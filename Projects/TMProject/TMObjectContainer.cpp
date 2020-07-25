#include "pch.h"
#include "TMObjectContainer.h"
#include "TMGround.h"

TMObjectContainer::TMObjectContainer(TMGround* pGround)
	: TreeNode(0)
{
}

TMObjectContainer::~TMObjectContainer()
{
}

int TMObjectContainer::Load(const char* szFileName)
{
	return 0;
}

int TMObjectContainer::Save(const char* szFileName)
{
	return 0;
}

int TMObjectContainer::FrameMove(unsigned int dwServerTime)
{
	return 0;
}
