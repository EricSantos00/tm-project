#include "pch.h"
#include "TMSelectCharScene.h"
#include "TMGlobal.h"

TMSelectCharScene::TMSelectCharScene() :
	m_vecSelPos{},
	m_vecCrePos{}
{
	g_ClipFar = 70.0f;
	m_dwStartRise = 0;
	m_dwStartSet = 0;
	m_dwCStartRise = 0;
	m_dwCStartSet = 0;
	m_dwLastMoveTime = 0;
	m_bMovingNow = 0;
	m_pBtnLogin = nullptr;
	m_pBtnCancel = nullptr;
	m_pBtnDelete = nullptr;
	m_pBtnCreate = nullptr;
	m_pRename = nullptr;
	m_pEditRename = nullptr;
	m_pPWEdit = nullptr;
	m_pInputPWPanel = nullptr;
	m_bShowNameLabel = 0;
	m_dwLastClickLoginBtnTime = 0;
	m_dwLastClickCreateBtnTime = 0;
	m_fFocusHeight = 1.0f;
	m_bAni = 0;
	m_vecSelPos = TMVector2{ 2052.0f, 2052.0f };
	m_vecCrePos = TMVector2{ 2080.0f, 2080.0f };
	g_pObjectManager->m_cCharacterSlot = -1;
	g_pObjectManager->m_usWarGuild = -1;
	g_pObjectManager->m_usAllyGuild = -1;
	m_pFocused = nullptr;

	for (int i = 0; i < 4; ++i)
		m_pHuman[i] = nullptr;

	m_eSceneType = ESCENE_TYPE::ESCENE_SELCHAR;
	m_bSelect = 1;
	m_pAccountLockTime = 0;
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
