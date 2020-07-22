#include "pch.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Finalize()
{
}

void ObjectManager::OnPacketEvent(unsigned int dwCode, char* buf)
{
}

void ObjectManager::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
}

void ObjectManager::OnKeyDownEvent(unsigned int nKeyCode)
{
}

void ObjectManager::OnKeyUpEvent(unsigned int nKeyCode)
{
}

void ObjectManager::OnCharEvent(char nCharCode, int lParam)
{
}

void ObjectManager::OnChangeIME()
{
}

void ObjectManager::OnIMEEvent(char* ipComposeString)
{
}

void ObjectManager::OnDataEvent(unsigned int wParam, int lParam)
{
}

void ObjectManager::FrameMove(unsigned int dwServerTime)
{
}

void ObjectManager::EffectFrameMove(TreeNode* pNode, unsigned int dwServerTime)
{
}

TMFieldScene* ObjectManager::GetNodeByID(unsigned int dwID)
{
	return nullptr;
}

TreeNode* ObjectManager::GetHumanByID(unsigned int dwID)
{
	return nullptr;
}

TreeNode* ObjectManager::GetItemByID(unsigned int dwID)
{
	return nullptr;
}

void ObjectManager::RestoreDeviceObjects()
{
}

void ObjectManager::InvalidateDeviceObjects()
{
}

void ObjectManager::RenderControl()
{
}

void ObjectManager::RenderObject()
{
}

void ObjectManager::RenderTargetObject(float fHeight)
{
}

void ObjectManager::SetCurrentState(TM_GAME_STATE ieNewState)
{
}

void ObjectManager::SetCurrentScene(TMScene* pScene)
{
}

TMFieldScene* ObjectManager::GetCurrentScene()
{
	return nullptr;
}

void ObjectManager::DeleteObject(TreeNode* pNode)
{
}

void ObjectManager::DeleteObject(unsigned int dwID)
{
}

void ObjectManager::DisconnectEffectFromMob(TMObject* pMob)
{
}

int ObjectManager::InitResourceList()
{
	return 0;
}

void ObjectManager::InitAniSoundTable()
{
}

void ObjectManager::InitCurseList()
{
}

TMCamera* ObjectManager::GetCamera()
{
	return nullptr;
}

void ObjectManager::CleanUp()
{
}
