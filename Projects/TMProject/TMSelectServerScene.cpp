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

int IsCastle(int nServerIndex)
{
	return 0;
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

	m_bAdmit = 1;
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
	int nUserCount[MAX_SERVERNUMBER] { 0 };
	char szUserCount[1024]{ 0 };
	for (int i = 0; i < MAX_SERVERNUMBER; ++i)
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
	int nMaxGroupN = 0;
	for (int j = 0; j < m_nMaxGroup; ++j)
	{
		if (g_nServerCountList[j])
			nMaxGroupN++;
	}

	SListBoxServerItem* pServerItem[11]{ nullptr };
	
	int nIndexN = g_nServerCountList[idwEvent];
	switch (idwControlID)
	{
	case 65542u:
	{
		char szStr[128] = { 0 };

		int nUserCount[MAX_SERVERNUMBER] = { 0 };
		int nUserCount2[MAX_SERVERNUMBER] = { 0 };
		char szUserCount[1024] = { 0 };
		for (int k = 0; k < MAX_SERVERNUMBER; ++k)
		{
			nUserCount[k] = 750;
			nUserCount2[k] = 750;
		}
		int nAspGetweek = -1;
		int nAspGetday = -1;

		m_pMessagePanel->SetMessage(g_pMessageStringTable[23], 0);
		m_pMessagePanel->SetVisible(1, 0);

		if (m_bAdmit == 1 && nIndexN == m_nAdmitGroup)
		{
			for (int i = m_nAdmitGroup; i < 10; ++i)
				g_pServerList[i][0][0] = 0;

			for (int i = 0; i < m_nAdmitGroup; ++i)
			{
				BASE_GetHttpRequest(g_pServerList[i][0], szUserCount, sizeof szUserCount);

				sscanf_s(szUserCount, "%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n",
					&nUserCount2[0], &nUserCount2[1], &nUserCount2[2], &nUserCount2[3], &nUserCount2[4], &nUserCount2[5],
					&nUserCount2[6], &nUserCount2[7], &nUserCount2[8], &nUserCount2[9], &nUserCount2[10]);

				if (m_nDay[i] >= 1)
					nUserCount2[m_nAdmitGroup - i + 10] = (int)pServerItem[m_nDay[i] + 10];

				sprintf_s(g_pServerList[nIndexN][i + 1], "%s", g_pServerList[m_nAdmitGroup - i - 1][m_bAdmit + m_nAdmitGroup - i]);
			}
		}
		else
		{
			BASE_GetHttpRequest(g_pServerList[nIndexN][0], szUserCount, sizeof szUserCount);
			sscanf_s(szUserCount, "%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n%d\\n",
				&nUserCount[0], &nUserCount[1], &nUserCount[2], &nUserCount[3], &nUserCount[4], &nUserCount[5],
				&nUserCount[6], &nUserCount[7], &nUserCount[8], &nUserCount[9], &nAspGetweek, &nAspGetday);
		}

		_SYSTEMTIME time{};
		GetLocalTime(&time);
		if (nAspGetday == -1)
			nAspGetday = time.wDay;

		for (int i = 0; i < MAX_SERVERGROUP; ++i)
		{
			m_nDay[i] = 0;
			for (int k = 1; k < MAX_SERVERNUMBER; ++k)
				if (g_pServerList[i][k][0] != 0)
					++m_nDay[i];

			if (m_nDay[i])
			{
				int nDay = time.wDay % m_nDay[i];
				if (!nDay)
					nDay = m_nDay[i];

				m_nDay[i] = nDay;
			}
		}

		m_pMessagePanel->SetVisible(0, 1);

		SListBox* pServerList = m_pNServerList;

		if (pServerList)
		{
			pServerList->Empty();

			for (int num = 1;; ++num)
			{
				if (num >= MAX_SERVERNUMBER)
				{
					pServerList->SetVisible(1);
					break;
				}

				if (g_pServerList[nIndexN][num][0])
				{
					int nCastle = 0;
					if (nAspGetweek == -1 || nAspGetweek != 1)
						nCastle = IsCastle(num - 1);
					else
						nCastle = num % 2 == ((nAspGetday - 1) / 7 + 1) % 2;

					int nServerAge = num;

					if (m_bAdmit == 1 && nIndexN == m_nAdmitGroup)
					{
						int nGIndex = m_nAdmitGroup - num;
						if (nGIndex < 0)
							continue;

						bool nCheckServer = false;
						for (int k = 0; k < m_nAdmitGroup; ++k)
						{
							if (g_nServerCountList[k] == nGIndex + 1)
								nCheckServer = true;
						}

						if (!nCheckServer)
							continue;

						nCastle = IsCastle(m_nDay[nGIndex] - 1);

						if (g_szServerName[nGIndex][m_nDay[nGIndex]][0])
							sprintf_s(szStr, "%s-%s", g_szServerNameList[nGIndex], g_szServerName[nGIndex][m_nDay[nGIndex] - 1][0]);
						else
						{
							sprintf_s(szStr, "%s-%d", g_szServerNameList[nGIndex], m_nDay[nGIndex]);

							nServerAge = m_nDay[nGIndex];

							if (nUserCount2[num] > 600)
							{
								int len = strlen(szStr);

								if (len < 14)
								{
									for (int n1 = len; n1 < len; ++n1)
										szStr[n1] = ' ';
								}

								szStr[14] = 0;
								strcat(szStr, "FULL");
							}
						}
					}
					else if (g_szServerNameList[nIndexN][0])
					{
						if (g_szServerName[nIndexN][num][0])
							sprintf_s(szStr, "%s-%s", g_szServerNameList[nIndexN], g_szServerName[nIndexN][num]);
						else
						{
							sprintf_s(szStr, "%s-%d", g_szServerNameList[nIndexN], num);

							if (nUserCount[num] > 600)
							{
								int len = strlen(szStr);

								if (len < 14)
								{
									for (int n1 = len; n1 < len; ++n1)
										szStr[n1] = ' ';
								}

								szStr[14] = 0;
								strcat(szStr, "FULL");
							}
						}
					}
					else
						sprintf_s(szStr, g_pMessageStringTable[68], nIndexN + 1, num);

					int nCount = nUserCount[num];
					if (nCount < 0)
						nCount = 0;

					int nTextureSet = -1;
					if (m_bAdmit == 1 && m_nDay[nIndexN] == num)
						nTextureSet = -2;

					if (m_bAdmit == 1 && nIndexN == m_nAdmitGroup)
						nTextureSet = -2;

					// -1??
					pServerItem[num] = new SListBoxServerItem(nTextureSet, szStr, 0xFFFFFFFF, 0.0f, 0.0f, g_nChannelWidth, 16.0f, nCount, nCastle, 0, nServerAge);
					
					if (nUserCount2[num] < 0)
						pServerItem[num - 1]->m_cConnected = 0;

					pServerList->AddItem(pServerItem[num]);
				}
				else if (m_bAdmit == -1 && num < m_nMaxGroup)
				{
					sprintf_s(szStr, g_pMessageStringTable[70]);

					pServerItem[num] = new SListBoxServerItem(6, szStr, 0xFFFFFFFF, 0.0f, 0.0f, g_nChannelWidth, 16.0f, nUserCount2[num], 0, 0, 0);

					if (nUserCount2[num] < 0)
						pServerItem[num]->m_cConnected = 0;

					// TODO : review code					
					pServerList->AddItem(pServerItem[num - 1]);
				}
			}
		}
	}

	SwapLauncher();

	break;
	}
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
	g_pCursor->SetVisible(1);
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
	SListBoxItem* pGroupItem[11];
	m_pNServerSelect = (SPanel*)m_pControlContainer->FindControl(65537);
	m_pNServerSelect->SetVisible(1);

	m_pNServerGroupList = (SListBox*)m_pControlContainer->FindControl(65542);
	m_pNServerList = (SListBox*)m_pControlContainer->FindControl(65543u);

	if (m_pNServerList)
		m_pNServerList->SetVisible(0);

	m_pNServerSelect->SetPos(((float)g_pDevice->m_dwScreenWidth - m_pNServerSelect->m_nWidth) * 0.5f,
		((float)g_pDevice->m_dwScreenHeight - m_pNServerSelect->m_nHeight) * 0.5f);
	m_pNServerSelect->m_nPosY += 75.0f;


	_SYSTEMTIME time{};
	GetLocalTime(&time);
	
	if (m_pNServerGroupList)
	{
		for (int i = 0; i < 11; ++i)
		{
			if (!g_pServerList[i][0][0])
			{
				m_nMaxGroup = i - 1;

				break;
			}
		}

		g_pTimerManager->GetServerTime();

		for (int i = 0; i < 10; i++)
		{
			for (int j = 1; j < 11; ++j)
			{
				if (g_pServerList[i][j][0])
					m_nDay[i] ++;
			}

			if (m_nDay[i])
			{
				int tmp = time.wDay % m_nDay[i];
				if (!tmp)
					tmp = m_nDay[i];

				m_nDay[i] = tmp;
			}
		}

		m_nAdmitGroup = 0;

		for (int nCount = 0; nCount <= 11; ++nCount)
		{
			if (m_nAdmitGroup <= g_nServerCountList[nCount])
				m_nAdmitGroup = g_nServerCountList[nCount];

			if (g_nServerCountList[nCount] > m_nMaxGroup)
				m_nMaxGroup = g_nServerCountList[nCount];
		}

		--m_nAdmitGroup;

		if (g_pServerList[9][0][0])
			m_nMaxGroup = 9;

		for (int i = m_nMaxGroup; i >= 0; --i)
		{
			int count = g_nServerCountList[i] - 1;

			if (count > -1 && g_pServerList[count][0][0])
			{
				char szStr[128]{ 0 };
				if (g_szServerNameList[g_nServerCountList[i] - 1][0])
					sprintf_s(szStr, g_szServerNameList[g_nServerCountList[i] - 1]);
				else
					sprintf_s(szStr, g_pMessageStringTable[66], count);

				pGroupItem[i] = new SListBoxItem(szStr, 0xD0FFFFFF, 0.0f, 0.0f, 63.0f, 16.0f, 0, 0x77777777u, 1u, 0);
				m_pNServerGroupList->AddItem(pGroupItem[i]);
			}
		}
	}
}

int TMSelectServerScene::FrameMoveGameGrade(unsigned int dwServerTime)
{
	return 0;
}

void TMSelectServerScene::GameGradeScene()
{
}
