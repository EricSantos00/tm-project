#include "pch.h"
#include "TMSelectCharScene.h"
#include "TMCamera.h"
#include "TMGlobal.h"
#include "ObjectManager.h"
#include "TMHuman.h"
#include "SControlContainer.h"

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
	if (m_pFocused)
		SAFE_DELETE(m_pFocused);
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
	auto pEditChar = m_pControlContainer->FindControl(4626u);

	if (iCharCode == VK_RETURN)
	{
		if (pEditChar->IsFocused() == 1)
			OnControlEvent(1545u, 0);

		return TMScene::OnCharEvent(iCharCode, lParam);
	}

	if (iCharCode != VK_ESCAPE)
		return TMScene::OnCharEvent(iCharCode, lParam);

	auto pSelChar = m_pControlContainer->FindControl(1282u);
	if (pSelChar->IsVisible() != 1)
	{
		if (m_pCreateWin->IsVisible() == 1)
			OnControlEvent(1552u, 0);
		else
			OnControlEvent(5673u, 0);
	}
	else
		OnControlEvent(4616u, 0);

	return 1;
}

int TMSelectCharScene::OnKeyDownEvent(unsigned int iKeyCode)
{
	if (TMScene::OnKeyDownEvent(iKeyCode) == 1)
		return 1;

	if (iKeyCode == VK_INSERT)
	{
		MSG_MessageWhisper stWhisper{};
		stWhisper.Header.ID = g_pObjectManager->m_dwCharID;
		stWhisper.Header.Type = MSG_MessageWhisper_Opcode;

		sprintf_s(stWhisper.MobName, "time");

		g_pSocketManager->SendOneMessage((char*)&stWhisper, sizeof stWhisper);
	}

	return 1;
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
	TMScene::FrameMove(dwServerTime);

	auto dwServerTimea = g_pTimerManager->GetServerTime();
	if (dwServerTimea - m_dwLastClickLoginBtnTime > 3000 && m_pBtnLogin && !m_pBtnLogin->m_bEnable)
	{
		m_pBtnLogin->SetEnable(1);
		m_pBtnCancel->SetEnable(1);
		m_pBtnDelete->SetEnable(1);
	}

	if (dwServerTimea - m_dwLastClickCreateBtnTime > 2000 && m_pBtnCreate && !m_pBtnCreate->m_bEnable)
		m_pBtnCreate->SetEnable(1);

	if (m_bMovingNow == 1)
	{
		m_pBtnCreate->SetEnable(0);
		m_pBtnLogin->SetEnable(0);
		m_pBtnCancel->SetEnable(0);
		m_pBtnDelete->SetEnable(0);
	}

	if (dwServerTimea - LastSendTime > 300000)
	{
		MSG_STANDARD stStandard{};
		stStandard.ID = 0;
		stStandard.Type = MSG_Ping_Opcode;

		g_pSocketManager->SendOneMessage((char*)&stStandard, sizeof MSG_STANDARD);
	}

	if (m_bCriticalError == 1)
	{
		m_pMessagePanel->SetMessage("Critical Data Error In Client", 0);
		m_pMessagePanel->SetVisible(1, 0);
	}

	return 1;
}

void TMSelectCharScene::VisibleSelectCreate(int bSelect)
{
	m_bSelect = bSelect;

	if (bSelect != 1)
	{
		if (m_pBtnDelete->m_bVisible == 1)
			m_pBtnDelete->SetVisible(0);

		CamAction("UI\\CreCamAction");

		auto pSelTitle = m_pControlContainer->FindControl(1281u);
		auto pSelChar = m_pControlContainer->FindControl(1282u);

		if (pSelTitle)
			pSelTitle->SetVisible(1);

		m_pNewCharPanel->SetVisible(1);
		m_pDelCharPanel->SetVisible(1);

		m_pNewCharPanel->SetPos(27.0f * RenderDevice::m_fWidthRatio + m_pSelbackpanel->m_nPosX, 13.0f * RenderDevice::m_fHeightRatio + m_pSelbackpanel->m_nPosY);
		m_pNewCharPanel->SetPos(27.0f * RenderDevice::m_fWidthRatio + m_pSelbackpanel->m_nPosX, 39.0f * RenderDevice::m_fHeightRatio + m_pSelbackpanel->m_nPosY);
		m_pNewCharPanel->SetPos(27.0f * RenderDevice::m_fWidthRatio + m_pSelbackpanel->m_nPosX, 64.0f * RenderDevice::m_fHeightRatio + m_pSelbackpanel->m_nPosY);

		pSelChar->SetPos(RenderDevice::m_fWidthRatio * 514.0f, RenderDevice::m_fHeightRatio * 35.0f);

		if (pSelChar)
			pSelChar->SetVisible(0);

		auto pCreTitle = m_pControlContainer->FindControl(1537u);
		auto pCreBG1 = m_pControlContainer->FindControl(1538u);
		auto pCreBG2 = m_pControlContainer->FindControl(1539u);
		auto pCreBG3 = m_pControlContainer->FindControl(1540u);
		auto pCreBG4 = m_pControlContainer->FindControl(1541u);
		auto pCreWin = m_pControlContainer->FindControl(1542u);

		if (pCreTitle)
			pCreTitle->SetVisible(0);
		if (pCreBG1)
			pCreBG1->SetVisible(0);
		if (pCreBG2)
			pCreBG2->SetVisible(0);
		if (pCreBG3)
			pCreBG3->SetVisible(0);
		if (pCreBG4)
			pCreBG4->SetVisible(0);
		if (pCreWin)
			pCreWin->SetVisible(0);
	}
	else
	{
		if (m_pBtnDelete->m_bVisible == 1)
			m_pBtnDelete->SetVisible(0);

		CamAction("UI\\CreCamAction");

		auto pSelTitle = m_pControlContainer->FindControl(1281u);
		auto pSelChar = m_pControlContainer->FindControl(1282u);

		if (pSelTitle)
			pSelTitle->SetVisible(0);

		if (pSelChar)
			pSelChar->SetVisible(0);

		auto pCreTitle = m_pControlContainer->FindControl(1537u);
		auto pCreBG1 = m_pControlContainer->FindControl(1538u);
		auto pCreBG2 = m_pControlContainer->FindControl(1539u);
		auto pCreBG3 = m_pControlContainer->FindControl(1540u);
		auto pCreBG4 = m_pControlContainer->FindControl(1541u);
		auto pCreWin = m_pControlContainer->FindControl(1542u);

		m_pNewCharPanel->SetVisible(0);
		m_pDelCharPanel->SetVisible(0);

		pCreWin->SetPos(RenderDevice::m_fWidthRatio * 514.0f, RenderDevice::m_fHeightRatio * 35.0f);
		if (pCreTitle)
			pCreTitle->SetVisible(1);
		if (pCreBG1)
			pCreBG1->SetVisible(1);
		if (pCreBG2)
			pCreBG2->SetVisible(1);
		if (pCreBG3)
			pCreBG3->SetVisible(1);
		if (pCreBG4)
			pCreBG4->SetVisible(1);
		if (pCreWin)
			pCreWin->SetVisible(1);

		auto pEdit = m_pControlContainer->FindControl(4626u);
		if (pEdit)
			m_pControlContainer->SetFocusedControl(pEdit);
	}
}

void TMSelectCharScene::CamAction(const char* szAction)
{
	auto pCamera = g_pObjectManager->m_pCamera;
	pCamera->m_bStandAlone = 1;

	m_dwStartCamTime = g_pTimerManager->GetServerTime();
	ReadCameraPos(szAction);

	m_sPlayDemo = 1;
}

void TMSelectCharScene::LookSampleHuman(int nIndex, int bLook, int bSelect)
{
	TMVector3 vecStartPos{};
	TMVector3 vecLastPos{};
	TMVector3 vecCamDir{};

	int nStart = 0;
	int nEnd = 0;
	if (bLook)
	{
		nStart = 0;
		nEnd = 1;
	}
	else
	{
		nStart = 1;
		nEnd = 0;
	}

	float fEndHeight = 0.0f;
	if (bSelect)
	{
		vecStartPos = { 2044.0F, 2.0f, 2044.0f };
		fEndHeight = 1.3f;

		vecLastPos = { m_pHuman[nIndex]->m_vecPosition.x, m_pHuman[nIndex]->m_fHeight, m_pHuman[nIndex]->m_vecPosition.y };
	}
	else
	{
		vecStartPos = { 2072.0f, 5.5f, 2072.0f };
		fEndHeight = 5.19f;
		vecLastPos = { m_pSampleHuman[nIndex]->m_vecPosition.x, m_pSampleHuman[nIndex]->m_fHeight, m_pSampleHuman[nIndex]->m_vecPosition.y };
	}

	auto pCamera = g_pObjectManager->m_pCamera;
	pCamera->m_bStandAlone = 1;

	m_dwStartCamTime = g_pTimerManager->GetServerTime();

	memset(m_stCameraTick, 0, sizeof m_stCameraTick);
	m_nCameraLoop = 2;
	m_stCameraTick[0].dwTick = 0;
	m_stCameraTick[nEnd].sLocal = 0;
	m_stCameraTick[nStart].sLocal = 0;
	m_stCameraTick[nStart].fX = vecStartPos.x;
	m_stCameraTick[nStart].fY = vecStartPos.y;
	m_stCameraTick[nStart].fZ = vecStartPos.z;
	m_stCameraTick[nEnd].fHorizonAngle = 44.76f;
	m_stCameraTick[nStart].fHorizonAngle = 44.76f;
	m_stCameraTick[nEnd].fVerticalAngle = 0.0;
	m_stCameraTick[nStart].fVerticalAngle = 0.0;
	m_stCameraTick[1].dwTick = 400;

	vecStartPos = { m_stCameraTick[nStart].fX, m_stCameraTick[nStart].fY, m_stCameraTick[nStart].fZ };

	vecCamDir = pCamera->GetCameraLookatDir();

	m_stCameraTick[nEnd].fX = vecLastPos.x - (vecCamDir.x * 4.0f) + (g_pDevice->m_matView._11 * 0.5f);
	m_stCameraTick[nEnd].fY = fEndHeight;
	m_stCameraTick[nEnd].fX = vecLastPos.z - (vecCamDir.z * 4.0f) + (g_pDevice->m_matView._11 * 0.5f);

	m_sPlayDemo = 1;
}

void TMSelectCharScene::SetvirtualKey()
{
	char Keylist[10];
	Keylist[0] = 1;
	Keylist[1] = 2;
	Keylist[2] = 3;
	Keylist[3] = 4;
	Keylist[4] = 5;
	Keylist[5] = 6;
	Keylist[6] = 7;
	Keylist[7] = 8;
	Keylist[8] = 9;
	Keylist[9] = 0;

	srand(g_pTimerManager->GetServerTime());

	for (int i = 0; i < 10; ++i)
	{
		auto key = rand() % 10 - i;
		keybuf[i] = Keylist[key];

		for (int j = key; j < 9; ++j)
			Keylist[j] = Keylist[j + 1];
	}

	for (int i = 0; i < 10; ++i)
	{
		char chTmp[128] = { 0 };
		sprintf_s(chTmp, "%d", keybuf[i]);

		if (m_pBtnNumDlg[i])
			m_pBtnNumDlg[i]->SetText(chTmp);
	}

	memset(keypass, 0, sizeof keypass);
}

void TMSelectCharScene::AddvirtualKeyNum(int num)
{
	int paslen = strlen(keypass);
	char chdata[10];
	char Passdata[11] = { 0 };
	strcpy(Passdata, "**********");

	memset(chdata, 0, sizeof chdata);

	if (paslen < 6)
	{
		sprintf_s(keypass, "%s%d", keypass, keybuf[num]);
		strncpy(chdata, Passdata, strlen(keypass));
		m_pAccountLockDlgTitle->SetText(chdata, 0);
	}
}
