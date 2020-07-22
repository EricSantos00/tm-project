#include "pch.h"
#include "ObjectManager.h"
#include "TMGlobal.h"
#include "TMCamera.h"

ObjectManager::ObjectManager()
{
	m_pRoot = nullptr;
	m_pCamera = nullptr;
	m_pPreviousScene = nullptr;

	g_pApp->SetObjectManager(this);

	InitResourceList();
	InitAniSoundTable();
	InitCurseList();

	m_pTargetObject = nullptr;

	m_pRoot = new TreeNode(0);
	m_pCamera = new TMCamera();

	m_pRoot->AddChild(m_pCamera);
	g_pCurrentScene = nullptr;

	m_eCurrentState = TM_GAME_STATE::TM_NONE_STATE;
	m_nServerGroupIndex = -1;
	m_nServerIndex = -1;
	m_bBilling = 0;
	m_nTax = 0;
	m_nAuto = 0;
	m_nFakeExp = 0;
	m_cCharacterSlot = -1;
	m_cSelectShortSkill = 0;

	memset(&m_stSelCharData, 0, sizeof(m_stSelCharData));
	memset(m_stItemCargo, 0, sizeof(m_stItemCargo));
	memset(&m_stMobData, 0, sizeof(m_stMobData));
	memset(m_stCapsuleInfo, 0, sizeof(m_stCapsuleInfo));
	memset(m_strGuildName, 0, sizeof(m_strGuildName));

	for (int i = 0; i < 20; ++i)
		m_cShortSkill[i] = -1;

	m_bCleanUp = 0;
	m_bVisualControl = 1;
	m_bTvControl = 0;
	for (int ia = 0; ia < 4; ++ia)
		m_cAvatar[ia] = 0;

	for (int ib = 0; ib < 64; ++ib)
	{
		memset(m_stPlayTime[ib].strAccount, 0, sizeof(m_stPlayTime[ib].strAccount));
		m_stPlayTime[ib].nServer = 0;
		m_stPlayTime[ib].nYear = 0;
		m_stPlayTime[ib].nMonth = 0;
		m_stPlayTime[ib].nDay = 0;
		m_stPlayTime[ib].nHour = 0;
		m_stPlayTime[ib].nMinute = 0;
		m_stPlayTime[ib].nPlayTime = 0;
	}

	m_bPlayTime = 0;
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
