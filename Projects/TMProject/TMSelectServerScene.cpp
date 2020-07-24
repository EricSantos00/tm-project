#include "pch.h"
#include "TMSelectServerScene.h"
#include "TMGlobal.h"
#include "DirShow.h"
#include "ObjectManager.h"
#include "TMHuman.h"

TMSelectServerScene::TMSelectServerScene()
{
	m_eSceneType = ESCENE_TYPE::ESCENE_SELECT_SERVER;
	m_nTextIndex = -1;
	m_nMaxGroup = 0;
	m_dwStartCamTime = 0;
	m_dwLoginTime = 0;
	m_dwLastClickLoginBtnTime = 0;
	m_cStartRun = 0;
	m_nDemoType = 0;
	m_bAdmit = 0;
	m_bRemove = 0;

	if (Game_grade)
		GameGradeScene();

	m_bAdmit = 0;
	if (g_pApp->m_pBGMManager != nullptr)
		g_pApp->m_pBGMManager->StopBGM();

	memset(m_HeightMapData, 0, sizeof(m_HeightMapData));

	if (g_pApp->m_pBGMManager != nullptr)
		g_pApp->m_pBGMManager->PlayMusic(0);

	DS_SOUND_MANAGER::m_nMusicIndex = 0;
	
	g_AccountLock = 0;
	g_nBattleMaster = 0;
	LastSendMsgTime = 0;
}

TMSelectServerScene::~TMSelectServerScene()
{
	for (int nPerson = 0; nPerson < 50; ++nPerson)
	{
		if (m_pCheckHumanList[nPerson] != nullptr)
		{
			g_pObjectManager->DeleteObject(m_pCheckHumanList[nPerson]);
			m_pCheckHumanList[nPerson] = nullptr;
		}
	}
	if (g_pSoundManager != nullptr)
	{
		if (g_pSoundManager->GetSoundData(102) != nullptr &&
			g_pSoundManager->GetSoundData(102)->IsSoundPlaying())
		{
			g_pSoundManager->GetSoundData(102)->Stop();
		}
	}
	Game_grade = 0;
}

int TMSelectServerScene::InitializeScene()
{
	if (!LoadRC("UI\\SelServerScene2.txt"))
	{

	}
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
