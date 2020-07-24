#include "pch.h"
#include "TMSelectServerScene.h"

TMSelectServerScene::TMSelectServerScene()
{
}

TMSelectServerScene::~TMSelectServerScene()
{
}

int TMSelectServerScene::InitializeScene()
{
	return 1;
}

int TMSelectServerScene::OnControlEvent(unsigned int idwControlID, unsigned int idwEvent)
{
	return 0;
}

int TMSelectServerScene::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

int TMSelectServerScene::OnPacketEvent(unsigned int dwCode, char* buf)
{
	return 0;
}

int TMSelectServerScene::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

void TMSelectServerScene::ResetDemoPlayer()
{
}

void TMSelectServerScene::AniDemoPlayer()
{
}

void TMSelectServerScene::CamAction()
{
}

void TMSelectServerScene::MoveHuman(int nIndex)
{
}

void TMSelectServerScene::RemoveHuman()
{
}

void TMSelectServerScene::SetAlphaServer(unsigned int dwStartTime, unsigned int dwServerTime, unsigned int dwTerm, int bFade)
{
}

void TMSelectServerScene::SetAlphaLogin(unsigned int dwStartTime, unsigned int dwServerTime, unsigned int dwTerm, int bFade)
{
}

void TMSelectServerScene::SetAlphaVirtualkey(unsigned int dwStartTime, unsigned int dwServerTime, unsigned int dwTerm, int bFade)
{
}

void TMSelectServerScene::InitializeUI()
{
}

int TMSelectServerScene::FrameMoveGameGrade(unsigned int dwServerTime)
{
	return 0;
}

void TMSelectServerScene::GameGradeScene()
{
}
