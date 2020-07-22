#include "pch.h"
#include "TMSelectCharScene.h"

TMSelectCharScene::TMSelectCharScene()
{
}

TMSelectCharScene::~TMSelectCharScene()
{
}

int TMSelectCharScene::InitializeScene()
{
	return 0;
}

int TMSelectCharScene::OnControlEvent(unsigned int idwControlID, unsigned int idwEvent)
{
	return 0;
}

int TMSelectCharScene::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

int TMSelectCharScene::OnKeyDownEvent(unsigned int iKeyCode)
{
	return 0;
}

int TMSelectCharScene::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

int TMSelectCharScene::OnPacketEvent(unsigned int dwCode, char* buf)
{
	return 0;
}

int TMSelectCharScene::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMSelectCharScene::VisibleSelectCreate(int bSelect)
{
}

void TMSelectCharScene::CamAction(char* szAction)
{
}

void TMSelectCharScene::LookSampleHuman(int nIndex, int bLook, int bSelect)
{
}

void TMSelectCharScene::SetvirtualKey()
{
}

void TMSelectCharScene::AddvirtualKeyNum(int num)
{
}
