#include "pch.h"
#include "TMSelectServerScene.h"
#include "TMGlobal.h"
#include "DirShow.h"
#include "ObjectManager.h"
#include "TMHuman.h"
#include "SControlContainer.h"
#include "TMCamera.h"
#include "TMObject.h"
#include "TMGround.h"
#include "TMSun.h"
#include "TMSky.h"
#include "TMSnow.h"
#include "TMLog.h"
#include "TMObjectContainer.h"
#include "NewApp.h"

void SwapLauncher()
{

}

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
	LoadRC("UI\\SelServerScene2.txt");

	_SYSTEMTIME time{};
	GetLocalTime(&time);
	g_pCursor->SetVisible(0);
	g_pDevice->m_dwClearColor = 0;
	
	memset(m_nDay, 0, sizeof m_nDay);
	memset(m_pGroupPanel, 0, sizeof m_pGroupPanel);

	InitializeUI();

	m_pLoginPanel = static_cast<SPanel*>(m_pControlContainer->FindControl(65870u));
	m_pLoginBtns[0] = static_cast<SButton*>(m_pControlContainer->FindControl(65873u));
	m_pLoginBtns[2] = static_cast<SButton*>(m_pControlContainer->FindControl(65874u));
	m_pLoginBtns[1] = static_cast<SButton*>(m_pControlContainer->FindControl(65875u));

	m_pLogoPanels[0] = static_cast<SPanel*>(m_pControlContainer->FindControl(311u));
	m_pLogoPanels[1] = static_cast<SPanel*>(m_pControlContainer->FindControl(312u));

	m_pLogoPanels[0]->SetVisible(Game_grade == 0);
	m_pLogoPanels[1]->SetVisible(Game_grade == 0);

	g_nChannelWidth = 133;

	m_pSelServerText = static_cast<SText*>(m_pControlContainer->FindControl(5635u));
	m_pSelChannelText = static_cast<SText*>(m_pControlContainer->FindControl(5636u));

	if (m_pSelServerText)
		m_pSelServerText->m_nPosY += 5.0f;

	if (m_pSelChannelText)
	{
		m_pSelChannelText->m_nPosX += 8.0f;
		m_pSelChannelText->m_nPosX += 5.0f;
	}

	m_pLoginPanelText = static_cast<SText*>(m_pControlContainer->FindControl(65876u));
	m_pLoginIDText = static_cast<SText*>(m_pControlContainer->FindControl(65877u));
	m_pLoginPasswordText = static_cast<SText*>(m_pControlContainer->FindControl(65878u));

	m_pLoginPanelText->m_nPosY += 5.0f;

	SText* pText = static_cast<SText*>(m_pControlContainer->FindControl(769u));

	pText->SetPos(pText->m_nPosX, static_cast<float>(g_pDevice->m_dwScreenHeight) - 15.0f);
	
	float nHeight = static_cast<float>(g_pDevice->m_dwScreenHeight) * 0.05f - static_cast<float>(m_pLoginPanel->m_nHeight) * 0.5;
	m_pLoginPanel->SetPos(static_cast<float>(g_pDevice->m_dwScreenWidth) * 0.5f - m_pLoginPanel->m_nWidth * 0.5f, nHeight);

	if(g_pDevice->m_dwScreenWidth == 1600)
	{
		float fWidthRatio = RenderDevice::m_fWidthRatio;
		float fHeightRatio = RenderDevice::m_fHeightRatio;

		m_pLogoPanels[0]->SetRealPos(400 * fWidthRatio, 10.0f * fHeightRatio);
		m_pLogoPanels[1]->SetRealPos(400 * fWidthRatio, 10.0f * fHeightRatio);
		m_pLogoPanels[0]->SetRealSize(256 * fWidthRatio, 256.0f * fHeightRatio);
		m_pLogoPanels[1]->SetRealSize(256 * fWidthRatio, 256.0f * fHeightRatio);
	}
	else
	{
		int nAddHeight = 0;
		if (g_pDevice->m_dwScreenWidth == 1024)
			nAddHeight = 20;
		else if (g_pDevice->m_dwScreenWidth == 12180)
			nAddHeight = 40;

		m_pLogoPanels[0]->SetPos(static_cast<float>(g_pDevice->m_dwScreenWidth) * 0.5f - m_pLogoPanels[0]->m_nWidth, 10.0f * RenderDevice::m_fHeightRatio + static_cast<float>(nAddHeight));
		m_pLogoPanels[1]->SetPos(static_cast<float>(g_pDevice->m_dwScreenWidth) * 0.5f, 10.0f * RenderDevice::m_fHeightRatio + static_cast<float>(nAddHeight));
	}

	m_pEditID = static_cast<SEditableText*>(m_pControlContainer->FindControl(65871u));
	m_pEditPW = static_cast<SEditableText*>(m_pControlContainer->FindControl(65872u));

	g_nServerGroupNum = m_nTextIndex + 1;
	g_pObjectManager->m_cCharacterSlot = -1;
	g_pObjectManager->m_cSelectShortSkill = 0;

	memset(&g_pObjectManager->m_stSelCharData, 0, sizeof STRUCT_SELCHAR);
	memset(g_pObjectManager->m_stItemCargo, 0, sizeof STRUCT_ITEM * MAX_CARGO);
	memset(&g_pObjectManager->m_stMobData, 0, sizeof STRUCT_MOB);

	for (int i = 0; i < 4; ++i)
		g_pObjectManager->m_stMobData.ShortSkill[i] = -1;

	if (g_pSocketManager)
		g_pSocketManager->CloseSocket();

	if (g_pObjectManager->m_bBilling == 1)
	{
		g_pObjectManager->m_bBilling = 0;

		m_pMessageBox->SetMessage(g_pMessageStringTable[132], 0, 0);
		m_pMessageBox->SetVisible(1);
	}

	int nAspGetweek = -1;
	int nAspGetday = -1;
	int nUserCount[11] { 0 };
	char szUserCount[1024]{ 0 };
	for (int i = 0; i < 11; +i)
		nUserCount[i] = -1;

	BASE_GetHttpRequest((char*)&g_pServerList, szUserCount, 1024);

	sscanf_s(szUserCount, "%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n",
		&nUserCount[0], &nUserCount[1], &nUserCount[2], &nUserCount[3], &nUserCount[4], &nUserCount[5],
		&nUserCount[6], &nUserCount[7], &nUserCount[8], &nUserCount[9], &nUserCount[10]);

	m_cLogin = 0;

	for (int i = 0; i < 3; ++i)
	{
		if (m_pLoginBtns[i])
		{
			m_pLoginBtns[i]->SetVisible(0);
			m_pLoginBtns[i]->m_GCPanel.dwColor = 0;
		}
	}

	m_pLoginPanel->SetVisible(0);
	m_pLoginPanel->m_GCPanel.dwColor = 0;

	g_pDevice->m_nHeightShift = 0;
	g_pObjectManager->m_pCamera->SetViewMode(0);

	memset(m_HeightMapData, 0, sizeof m_HeightMapData);

	char szMapPath[128]{ 0 };
	char szDataPath[128]{ 0 };
	memset(szMapPath, 0, sizeof szMapPath);
	memset(szDataPath, 0, sizeof szDataPath);

	sprintf_s(szMapPath, "env\\Field1616.trn");
	sprintf_s(szDataPath, "env\\Field1616.dat");

	if (m_nDemoType)
	{
		switch (m_nDemoType)
		{
		case 1:
			sprintf_s(szMapPath, "Character.trn");
			sprintf_s(szMapPath, "Character.dat");

			g_HeightPosX = 2048;
			g_HeightPosY = 2048;
			break;
		case 2:
		case 3:
			sprintf_s(szMapPath, "Field0813.trn");
			sprintf_s(szMapPath, "Field0813.dat");

			g_HeightPosX = 896;
			g_HeightPosY = 1536;
			break;
		case 4:
			sprintf_s(szMapPath, "Field2922.trn");
			sprintf_s(szMapPath, "Field2922.dat");

			g_HeightPosX = 3584;
			g_HeightPosY = 2684;
			break;
		}
	}
	else
	{
		sprintf_s(szMapPath, "Field2723.trn");
		sprintf_s(szMapPath, "Field2723.dat");

		g_HeightPosX = 3328;
		g_HeightPosY = 2816;
	}

	m_pGroundList[0] = new TMGround();

	if (!m_pGroundList[0]->LoadTileMap(szMapPath))
	{
		if (m_bCriticalError)
			LogMsgCriticalError(14, 0, 0, 0, 0);

		m_bCriticalError = 1;
	}

	m_pGround = m_pGroundList[0];

	for (int nY = 0; nY < 128; ++nY)
		memcpy(&m_HeightMapData[256 * nY], m_pGround->m_pMaskData[nY], 128);

	g_HeightPosX = m_pGround->m_vecOffset.x;
	g_HeightPosY = m_pGround->m_vecOffset.y;

	m_pObjectContainerList[0] = new TMObjectContainer(m_pGround);
	m_pGroundObjectContainer->AddChild(m_pObjectContainerList[0]);

	if (m_pObjectContainerList[0]->Load(szDataPath))
	{
		m_pGroundObjectContainer->AddChild(m_pGroundList[0]);

		if (m_nDemoType == 2)
			GroundNewAttach(EDirection::EDIR_RIGHT);

		m_pSun = new TMSun();
		m_pSun->InitObject();

		m_pEffectContainer->AddChild(m_pSun);

		m_pSky = new TMSky();
		AddChild(m_pSky);

		memset(&time, 0, sizeof time);
		GetLocalTime(&time);

		g_nSelServerWeather = time.wDay % 4;
		m_pSky->SetWeatherState(time.wDay % 4);

		++g_nSelServerWeather;
		g_nSelServerWeather %= 4;

		m_pSnow = new TMSnow(1.0f);
		m_pEffectContainer->AddChild(m_pSnow);
		m_pSnow->m_bVisible = g_nSelServerWeather == 2;

		memset(m_pCheckHumanList, 0, sizeof m_pCheckHumanList);

		g_pObjectManager->m_pCamera->m_vecCamPos = TMVector2(2112.55, 2088.0f);
		g_pObjectManager->m_pCamera->m_fHorizonAngle = 4.71f;
		g_pObjectManager->m_pCamera->m_fVerticalAngle = 0.26f;

		if (g_pSoundManager)
			if (g_pSoundManager->GetSoundData(102))
				if (!g_pSoundManager->GetSoundData(102)->IsSoundPlaying())
					g_pSoundManager->GetSoundData(102)->Play(0, 1u);

		if (!Game_grade)
		{
			ResetDemoPlayer();
			CamAction();
		}

		if (g_pSoundManager)
			if (g_pSoundManager->GetSoundData(101))
				if (!g_pSoundManager->GetSoundData(101)->IsSoundPlaying())
					g_pSoundManager->GetSoundData(101)->Play(0);

		SwapLauncher();
		return 1;
	}
	else
	{
		LOG_WRITELOG("DataFile Not Found");
		MessageBoxA(g_pApp->m_hWnd, "DataFile NotFound.", "File Lost", 0);
		PostMessageA(g_pApp->m_hWnd, 0x10u, 0, 0);
	}

	return 0;
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
	return TMScene::FrameMove(dwServerTime);
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
	m_pNServerSelect = (SPanel*)m_pControlContainer->FindControl(65537);
	m_pNServerSelect->SetVisible(1);

	m_pNServerGroupList = (SListBox*)m_pControlContainer->FindControl(65542);
	m_pNServerList = (SListBox*)m_pControlContainer->FindControl(65543u);

	if (m_pNServerList)
		m_pNServerList->SetVisible(0);

	m_pNServerSelect->SetPos(((float)g_pDevice->m_dwScreenWidth - m_pNServerSelect->m_nWidth) * 0.5f,
		((float)g_pDevice->m_dwScreenHeight - m_pNServerSelect->m_nHeight) * 0.5f);
	m_pNServerSelect->m_nPosY += 75.0f;

	// TODO: finish
}

int TMSelectServerScene::FrameMoveGameGrade(unsigned int dwServerTime)
{
	return 0;
}

void TMSelectServerScene::GameGradeScene()
{
}
