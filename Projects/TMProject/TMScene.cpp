#include "pch.h"
#include "SControlContainer.h"
#include "SControl.h"
#include "TMGround.h"
#include "TMSky.h"
#include "TMSun.h"
#include "TMLight.h"
#include "TMHuman.h"
#include "TMObject.h"
#include "TMItem.h"
#include "TMGlobal.h"
#include "TMScene.h"

TMScene::TMScene() : TreeNode(0)
{
	m_eSceneType = ESCENE_TYPE::ESCENE_NONE;
	m_pControlContainer = nullptr;
	m_pExtraContainer = nullptr;
	m_pGround = nullptr;
	m_pMouseOverHuman = nullptr;
	m_pMouseOverItem = nullptr;
	m_sPlayDemo = -1;
	m_nCurrentGroundIndex = 0;
	m_dwStartCamTime = 0;
	g_ClipFar = 70.0f;
	SControl::m_dwStaticID = 0;
	m_nAdjustTime = 0;
	m_dwInitTime = 0;
	n_bPrtScreen = 0;
	m_pMyHuman = nullptr;
	m_pSky = nullptr;
	m_pSun = nullptr;
	m_pHumanContainer = nullptr;
	m_pItemContainer = nullptr;
	m_pAlphaNative = nullptr;
	m_pDescPanel = nullptr;
	m_pTextBillMsg = nullptr;
	m_bShowNameLabel = 0;
	m_bCriticalError = 0;
	m_bAutoRun = 0;
	m_bReverse = 0;
	TMLight::m_dwBaseLightIndex = 2;
	m_pTextIMEDesc = 0;

	for (int nImeCount = 0; nImeCount < 10; ++nImeCount)
		m_pTextCandidate[nImeCount] = 0;

	m_pTextCompose = nullptr;
	m_pTextComposeB = nullptr;
	m_pTextReadCompose = nullptr;
	m_pTextReadComposeB = nullptr;
	m_dwDelayDisconnectTime = 0;
	m_bMsgRemoveServer = 0;

	for (int i = 0; i < 2; ++i)
	{
		m_pGroundList[i] = 0;
		m_pObjectContainerList[i] = 0;
	}

	m_pControlContainer = new SControlContainer(this);

	m_pExtraContainer = new TreeNode(0);

	AddChild(m_pExtraContainer);

	m_pEffectContainer = new TreeNode(0);

	AddChild(m_pEffectContainer);

	m_pShadeContainer = new TreeNode(0);

	AddChild(m_pShadeContainer);

	m_pGroundObjectContainer = new TreeNode(0);

	AddChild(m_pGroundObjectContainer);

	m_pHumanContainer = new TreeNode(0);

	AddChild(m_pHumanContainer);

	m_pTextBillMsg = new SText(-2, "ºô", 0xFFFFFFFF, 120.0f, 70.0f, 540.0f, 20.0f, 1, 0xAAFF0000, 1, 1);
	m_pTextBillMsg->m_bSelectEnable = 0;
	m_pTextBillMsg->SetVisible(0);

	m_pMessagePanel = new SMessagePanel("Message Panel", 160.0f, 80.0f, 480.0f, 24.0f, 2000);

	m_pMessageBox = new SMessageBox(
		"Message Box",
		0,
		(((float)g_pDevice->m_dwScreenWidth / RenderDevice::m_fWidthRatio) - 256.0f) / 2.0f,
		(((float)g_pDevice->m_dwScreenHeight / RenderDevice::m_fHeightRatio) - 152.0f) / 2.0f);

	m_pMessageBox2 = new SMessageBox(
		"Message Box",
		4,
		(((float)g_pDevice->m_dwScreenWidth / RenderDevice::m_fWidthRatio) - 256.0f) / 2.0f,
		(((float)g_pDevice->m_dwScreenHeight / RenderDevice::m_fHeightRatio) - 152.0f) / 2.0f);

	for (int nImeCounta = 0; nImeCounta < 10; ++nImeCounta)
	{
		m_pTextCandidate[nImeCounta] = new SText(
			-2,
			"",
			0xFFFFFFFF,
			((float)g_pDevice->m_dwScreenWidth / RenderDevice::m_fWidthRatio) - 180.0f,
			(((float)g_pDevice->m_dwScreenHeight / RenderDevice::m_fHeightRatio) - 161.0f) + (float)(16 * nImeCounta),
			179.0f,
			16.0f,
			1,
			0x9955AA55,
			1,
			0);
	}

	m_pTextCompose = new SText(
		-2,
		"",
		0xFFFFFFFF,
		0.0f,
		((float)g_pDevice->m_dwScreenHeight / RenderDevice::m_fHeightRatio) - 36.0f,
		200.0f,
		16.0f,
		1,
		0xAA55AA55,
		1,
		0);

	m_pTextReadCompose = new SText(
		-2,
		"",
		0xFFFFFFFF,
		0.0f,
		((float)g_pDevice->m_dwScreenHeight / RenderDevice::m_fHeightRatio) - 36.0f,
		200.0f,
		16.0f,
		1,
		0xAA55AA55,
		1,
		0);

	m_pTextComposeB = new SText(
		-2,
		"",
		0xFFFFFF00,
		0.0f,
		((float)g_pDevice->m_dwScreenHeight / RenderDevice::m_fHeightRatio) - 36.0f,
		200.0f,
		16.0f,
		0,
		0xAA55AA55,
		1,
		0);

	m_pTextReadComposeB = new SText(
		-2,
		"",
		0xFFFFFF00,
		0.0f,
		((float)g_pDevice->m_dwScreenHeight / RenderDevice::m_fHeightRatio) - 36.0f,
		200.0f,
		16.0f,
		0,
		0xAA55AA55,
		1,
		0);

	m_pTextCompose->SetVisible(0);
	m_pTextReadCompose->SetVisible(0);
	m_pTextComposeB->SetVisible(0);
	m_pTextReadComposeB->SetVisible(0);
	m_pMessagePanel->SetVisible(0, 1);
	m_pMessageBox->SetVisible(0);
	m_pMessageBox2->SetVisible(0);

	if (m_pControlContainer)
		m_pMessageBox->SetEventListener(static_cast<IEventListener*>(m_pControlContainer));
	else
		m_pMessageBox->SetEventListener(nullptr);

	if (m_pControlContainer)
		m_pMessageBox2->SetEventListener(static_cast<IEventListener*>(m_pControlContainer));
	else
		m_pMessageBox2->SetEventListener(nullptr);

	m_pMessageBox->m_bModal = 1;
	m_pMessageBox2->m_bModal = 1;
	m_pMessagePanel->m_bSelectEnable = 0;

	m_pControlContainer->m_pModalControl[0] = dynamic_cast<SControl*>(m_pMessageBox);
	m_pControlContainer->m_pModalControl[4] = dynamic_cast<SControl*>(m_pMessageBox2);

	m_pControlContainer->AddItem(static_cast<SControl*>(m_pMessagePanel));
	m_pControlContainer->AddItem(static_cast<SControl*>(m_pMessageBox));
	m_pControlContainer->AddItem(static_cast<SControl*>(m_pMessageBox2));
	m_pControlContainer->AddItem(static_cast<SControl*>(m_pTextBillMsg));

	for (int nImeCountb = 0; nImeCountb < 10; ++nImeCountb)
	{
		m_pTextCandidate[nImeCountb]->SetVisible(0);

		m_pControlContainer->AddItem(static_cast<SControl*>(m_pTextCandidate[nImeCountb]));
	}

	m_pControlContainer->AddItem(static_cast<SControl*>(m_pTextComposeB));
	m_pControlContainer->AddItem(static_cast<SControl*>(m_pTextReadComposeB));
	m_pControlContainer->AddItem(static_cast<SControl*>(m_pTextCompose));
	m_pControlContainer->AddItem(static_cast<SControl*>(m_pTextReadCompose));

	float fHeight = (float)g_pDevice->m_dwScreenHeight - 20.0f;

	m_pAlphaNative = new SText(-2, "Ch", 0xFFFFFFDD, 0.0f, fHeight, 28.0f, 16.0f, 1, 0xAA000077, 1, 0);
	m_pAlphaNative->SetVisible(0);

	m_pControlContainer->AddItem(static_cast<SControl*>(m_pAlphaNative));

	m_pTextIMEDesc = new SText(-2, "IME Desc", 0xFFFFFFDD, 30.0f, fHeight, 180.0f, 16.0f, 1, 0xAA000077, 1, 0);
	m_pTextIMEDesc->SetVisible(0);

	m_pControlContainer->AddItem(static_cast<SControl*>(m_pTextIMEDesc));

	if (g_pEventTranslator)
	{
		if (g_pEventTranslator->IsNative())
		{
			m_pAlphaNative->SetText("Ch", 0);
			
			char szDesc[256]{};

			ImmGetDescriptionA(GetKeyboardLayout(0), szDesc, sizeof(szDesc));

			m_pTextIMEDesc->SetText(szDesc, 0);
			m_pTextIMEDesc->SetSize((float)(8 * strlen(szDesc)) + 16.0f, 16.0f);
		}
		else
		{
			m_pAlphaNative->SetText("En", 0);
		}
	}

	memset(m_HeightMapData, 0, sizeof(m_HeightMapData));
	memset(m_GateMapData, 0, sizeof(m_GateMapData));

	BASE_ApplyAttribute(m_HeightMapData, 256);

	for (int i = 0; i < 32; ++i)
		m_TargetAffect[i] = 0;
}

TMScene::~TMScene()
{
	g_pTimerManager->m_dwDelayTime = 20000;

	unsigned int dwServerTime = g_pTimerManager->GetServerTime();

	g_pObjectManager->EffectFrameMove(m_pEffectContainer, dwServerTime);

	SAFE_DELETE(m_pHumanContainer);

	SAFE_DELETE(m_pItemContainer);

	SAFE_DELETE(m_pControlContainer);

	g_pObjectManager->m_pPreviousScene = nullptr;
	g_pObjectManager->CleanUp();

	m_pGround = nullptr;

	g_nUnDelMobCount = 0;

	g_pTimerManager->m_dwDelayTime = 0;
}

SControlContainer* TMScene::GetCtrlContainer()
{
	return m_pControlContainer;
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
	return 1;
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
