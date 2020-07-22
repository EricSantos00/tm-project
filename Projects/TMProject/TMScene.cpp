#include "pch.h"
#include "SControlContainer.h"
#include "SControl.h"
#include "TMGround.h"
#include "TMSky.h"
#include "TMSun.h"
#include "TMHuman.h"
#include "TMObject.h"
#include "TMItem.h"
#include "TMScene.h"

TMScene::TMScene() : TreeNode(0)
{
}

TMScene::~TMScene()
{
}

SControlContainer* TMScene::GetCtrlContainer()
{
	return nullptr;
}

int TMScene::LoadRC(char* szFileName)
{
	return 0;
}

int TMScene::ParseRC(FILE* fp, FILE* fpBinary, char* szControlType)
{
	return 0;
}

int TMScene::ReadRCBin(char* szBinFileName)
{
	return 0;
}

int TMScene::FindID(char* szID)
{
	return 0;
}

int TMScene::InitializeScene()
{
	return 0;
}

int TMScene::OnPacketEvent(unsigned int dwCode, char* pSBuffer)
{
	return 0;
}

int TMScene::OnKeyDownEvent(unsigned int iKeyCode)
{
	return 0;
}

int TMScene::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	return 0;
}

int TMScene::OnKeyUpEvent(unsigned int iKeyCode)
{
	return 0;
}

int TMScene::OnCharEvent(char iCharCode, int lParam)
{
	return 0;
}

int TMScene::OnIMEEvent(char* ipComposeString)
{
	return 0;
}

int TMScene::OnChangeIME()
{
	return 0;
}

int TMScene::OnControlEvent(unsigned int idwControlID, unsigned int idwEvent)
{
	return 0;
}

int TMScene::OnAccel(int nMsg)
{
	return 0;
}

int TMScene::FrameMove(unsigned int dwServerTime)
{
	return 0;
}

int TMScene::ReloadScene()
{
	return 0;
}

ESCENE_TYPE TMScene::GetSceneType()
{
	return ESCENE_TYPE();
}

void TMScene::Cleanup()
{
}

int TMScene::GroundNewAttach(EDirection eDir)
{
	return 0;
}

D3DXVECTOR3* TMScene::GroundGetPickPos(D3DXVECTOR3* result)
{
	return nullptr;
}

int TMScene::GroundGetTileType(TMVector2 vecPosition)
{
	return 0;
}

int TMScene::GroundGetMask(TMVector2 vecPosition)
{
	return 0;
}

int TMScene::GroundGetMask(IVector2 vecPosition)
{
	return 0;
}

float TMScene::GroundGetHeight(TMVector2 vecPosition)
{
	return 0.0f;
}

D3DCOLORVALUE* TMScene::GroundGetColor(D3DCOLORVALUE* result, TMVector2 vecPosition)
{
	return nullptr;
}

void TMScene::GroundSetColor(TMVector2 vecPosition, unsigned int dwColor)
{
}

int TMScene::GroundIsInWater(TMVector2 vecPosition, float fHeight, float* pfWaterHeight)
{
	return 0;
}

int TMScene::GroundIsInWater2(TMVector2 vecPosition, float* pfWaterHeight)
{
	return 0;
}

float TMScene::GroundGetWaterHeight(TMVector2 vecPosition, float* pfWaterHeight)
{
	return 0.0f;
}

int TMScene::GetMask2(TMVector2 vecPosition)
{
	return 0;
}

void TMScene::Warp()
{
}

void TMScene::Warp2(int nZoneX, int nZoneY)
{
}

void TMScene::SaveHeightMap(char* szFileName)
{
}

void TMScene::CameraAction()
{
}

void TMScene::ReadCameraPos(char* szFileName)
{
}

int TMScene::LoadMsgText(SListBox* pListBox, char* szFileName)
{
	return 0;
}

int TMScene::LoadMsgText2(SListBox* pListBox, char* szFileName, int nStartLine, int nEndLine)
{
	return 0;
}

int TMScene::LoadMsgText3(SListBox* pListBox, char* szFileName, int nLv, int ntrans)
{
	return 0;
}

unsigned int TMScene::LoadMsgText4(char* pStr, char* szFileName, int nLv, int ntrans)
{
	return 0;
}

int TMScene::LoadMsgLevel(char* LevelQuest, char* szFileName, char cType)
{
	return 0;
}

void TMScene::CheckPKNonePK(int nServerIndex)
{
}

void TMScene::LogMsgCriticalError(int Type, int ID, int nMesh, int X, int Y)
{
}

void TMScene::DeleteOwnerAllContainer()
{
}
