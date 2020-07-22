#include "pch.h"
#include "TMObject.h"

TMObject::TMObject()
	: TreeNode(0)
{
}

TMObject::~TMObject()
{
}

int TMObject::InitObject()
{
	return 0;
}

void TMObject::InitPosition(float fX, float fY, float fZ)
{
}

void TMObject::InitAngle(float fYaw, float fPitch, float fRoll)
{
}

void TMObject::SetPosition(float fX, float fY, float fZ)
{
}

void TMObject::SetAngle(float fYaw, float fPitch, float fRoll)
{
}

int TMObject::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

int TMObject::Render()
{
	return 0;
}

int TMObject::IsVisible()
{
	return 0;
}

int TMObject::IsInTown()
{
	return 0;
}

int TMObject::IsInPKZone()
{
	return 0;
}

int TMObject::IsInCastleZone()
{
	return 0;
}

int TMObject::IsInCastleZone2()
{
	return 0;
}

int TMObject::IsChannelWarZone(int nPositionX, int nPositionY)
{
	return 0;
}

int TMObject::IsInHouse()
{
	return 0;
}

int TMObject::IsInView()
{
	return 0;
}

int TMObject::RegisterMask(TMGround* pGround, float fX, float fY)
{
	return 0;
}

void TMObject::Save(FILE* fp)
{
}

int TMObject::IsMouseOver()
{
	return 0;
}

int TMObject::isVisualKey()
{
	return 0;
}

int TMObject::isCamPos()
{
	return 0;
}

void TMObject::ResetObject()
{
}
