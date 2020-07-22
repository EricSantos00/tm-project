#include "pch.h"
#include "TMCamera.h"

TMCamera::TMCamera()
: TreeNode(0) {
}

TMCamera::~TMCamera()
{
}

void TMCamera::InitCamera()
{
}

TMVector3* TMCamera::GetCameraPos()
{
	return nullptr;
}

TMVector3* TMCamera::GetCameraLookatPos(TMVector3* result)
{
	return nullptr;
}

TMVector3* TMCamera::GetCameraLookatDir()
{
	return nullptr;
}

void TMCamera::TurnView(float horizonAngle, float verticalAngle)
{
}

void TMCamera::EarthQuake(int nLevel)
{
}

double TMCamera::GetHorizonAngle()
{
	return 0.0;
}

void TMCamera::SetFocusedObject(TMObject* pObject)
{
}

TMObject* TMCamera::GetFocusedObject()
{
	return nullptr;
}

void TMCamera::SetViewMode(int nMode)
{
}
