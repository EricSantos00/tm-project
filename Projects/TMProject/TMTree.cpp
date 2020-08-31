#include "pch.h"
#include "TMTree.h"

TMTree::TMTree(int nType) 
	: TMObject()
{
}

TMTree::~TMTree()
{
}

int TMTree::InitObject()
{
	return 1;
}

int TMTree::Render()
{
	return 1;
}

int TMTree::FrameMove(unsigned int dwServerTime)
{
	return 1;
}

void TMTree::RestoreDeviceObjects()
{
}

void TMTree::InvalidateDeviceObjects()
{
}

void TMTree::InitPosition(float fX, float fY, float fZ)
{
}

void TMTree::SetAnimation(int nAniIndex)
{
}

void TMTree::InitLook(int nType)
{
}
