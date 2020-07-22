#include "pch.h"
#include "TMDemoScene.h"

TMDemoScene::TMDemoScene()
{
}

TMDemoScene::~TMDemoScene()
{
}

int TMDemoScene::InitializeScene()
{
	return 0;
}

int TMDemoScene::OnControlEvent(unsigned int idwControlID, unsigned int idwEvent)
{
	return 0;
}

int TMDemoScene::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

int TMDemoScene::OnPacketEvent(unsigned int dwCode, char* buf)
{
	return 0;
}

int TMDemoScene::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

int TMDemoScene::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMDemoScene::ResetDemoPlayer()
{
}

void TMDemoScene::ReadTimeTable()
{
}

void TMDemoScene::CamAction()
{
}

void TMDemoScene::ReadStrings()
{
}
