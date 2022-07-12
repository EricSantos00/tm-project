#include "pch.h"
#include "SControlContainer.h"
#include "SControl.h"
#include "SGrid.h"
#include "UIBinary.h"
#include "TMGround.h"
#include "TMSky.h"
#include "TMSun.h"
#include "TMLight.h"
#include "TMHuman.h"
#include "TMObject.h"
#include "TMCamera.h"
#include "TMObjectContainer.h"
#include "TMItem.h"
#include "TMGlobal.h"
#include "TMLog.h"
#include "TMScene.h"
#include "TMFieldScene.h"
#include "TMEffectFirework.h"
#include "TMSnow.h"
#include "TMRain.h"

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
			char tmp[] = "Ch";
			m_pAlphaNative->SetText(tmp, 0);
			
			char szDesc[256]{};

			ImmGetDescriptionA(GetKeyboardLayout(0), szDesc, sizeof(szDesc));

			m_pTextIMEDesc->SetText(szDesc, 0);
			m_pTextIMEDesc->SetSize((float)(8 * strlen(szDesc)) + 16.0f, 16.0f);
		}
		else
		{
			char tmp[] = "En";
			m_pAlphaNative->SetText(tmp, 0);
		}
	}

	memset(m_HeightMapData, 0, sizeof(m_HeightMapData));
	memset(m_GateMapData, 0, sizeof(m_GateMapData));

	BASE_ApplyAttribute((char*)m_HeightMapData, 256);

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

int TMScene::LoadRC(const char* szFileName)
{
	if (!m_pControlContainer)
		m_pControlContainer = new SControlContainer(this);

	char szBinFileName[128]{};

	sprintf_s(szBinFileName, "%s", szFileName);
	
	int nLength = strlen(szBinFileName);

	if (strchr(szBinFileName, '_'))
		sprintf_s(&szBinFileName[nLength - 7], sizeof(szBinFileName) - nLength - 7, ".bin");
	else
		sprintf_s(&szBinFileName[nLength - 3], sizeof(szBinFileName) - nLength - 3, "bin");

	return ReadRCBin(szBinFileName);
}

int TMScene::ParseRC(FILE* fp, FILE* fpBinary, char* szControlType)
{
	return 0;
}

int TMScene::ReadRCBin(char* szBinFileName)
{
	FILE* fpBinary = nullptr;
	
	fopen_s(&fpBinary, szBinFileName, "rb");

	if (!fpBinary)
		return 0;

	CONTROL_TYPE nControlType{};

	while (fread(&nControlType, 4, 1, fpBinary))
	{
		switch (nControlType)
		{
		case CONTROL_TYPE::CTRL_TYPE_PANEL:
		{
			BinPanel binPanelData;

			if (!fread(&binPanelData, sizeof(binPanelData), 1, fpBinary))
			{
				LOG_WRITELOG("Can't Read Resource Data[%d] in [%s]\r\n", nControlType, szBinFileName);
				fclose(fpBinary);
				return 0;
			}

			auto pPanel = new SPanel(
				binPanelData.nTextureSetIndex,
				(float)binPanelData.nStartX,
				(float)binPanelData.nStartY,
				(float)binPanelData.nWidth,
				(float)binPanelData.nHeight,
				binPanelData.nColor,
				static_cast<RENDERCTRLTYPE>(binPanelData.nFillType));

			if (!pPanel)
			{
				LOG_WRITELOG("Can't Create [%d] in Scene [%d]\r\n", binPanelData.nID, GetSceneType());
				return 0;
			}

			pPanel->SetControlID(binPanelData.nID);
			pPanel->SetCenterPos(binPanelData.nID,
				(float)binPanelData.nStartX,
				(float)binPanelData.nStartY,
				(float)binPanelData.nWidth,
				(float)binPanelData.nHeight);

			if (binPanelData.nParentID)
			{
				auto pParent = m_pControlContainer->FindControl(binPanelData.nParentID);

				if (pParent)
					pParent->AddChild(static_cast<TreeNode*>(pPanel));
			}
			else
			{
				m_pControlContainer->AddItem(static_cast<SControl*>(pPanel));
			}

			pPanel->m_bPickable = binPanelData.nPickable;
		}
		break;
		case CONTROL_TYPE::CTRL_TYPE_GRID:
		{
			BinGrid binGridData;

			if (!fread(&binGridData, sizeof(binGridData), 1, fpBinary))
			{
				LOG_WRITELOG("Can't Read Resource Data[%d] in [%s]\r\n", nControlType, szBinFileName);
				fclose(fpBinary);
				return 0;
			}

			auto pGrid = new SGridControl(
				binGridData.nTextureSetIndex,
				binGridData.nRowCount,
				binGridData.nColumnCount,
				(float)binGridData.nStartX,
				(float)binGridData.nStartY,
				(float)binGridData.nWidth,
				(float)binGridData.nHeight,
				static_cast<TMEITEMTYPE>(binGridData.nType));

			if (!pGrid)
			{
				LOG_WRITELOG("Can't Create [%d] in Scene [%d]\r\n", binGridData.nID, GetSceneType());
				return 0;
			}

			pGrid->SetControlID(binGridData.nID);

			pGrid->SetCenterPos(binGridData.nID,
				(float)binGridData.nStartX,
				(float)binGridData.nStartY,
				(float)binGridData.nWidth,
				(float)binGridData.nHeight);

			if (m_pControlContainer)
				pGrid->SetEventListener(static_cast<IEventListener*>(m_pControlContainer));
			else
				pGrid->SetEventListener(nullptr);

			if (binGridData.nParentID)
			{
				auto pParent = m_pControlContainer->FindControl(binGridData.nParentID);

				if (pParent)
					pParent->AddChild(static_cast<TreeNode*>(pGrid));
			}
			else
			{
				m_pControlContainer->AddItem(static_cast<SControl*>(pGrid));
			}
		}
		break;
		case CONTROL_TYPE::CTRL_TYPE_3DOBJ:
		{
			Bin3DObj bin3DObjData;

			if (!fread(&bin3DObjData, sizeof(bin3DObjData), 1, fpBinary))
			{
				LOG_WRITELOG("Can't Read Resource Data[%d] in [%s]\r\n", nControlType, szBinFileName);
				fclose(fpBinary);
				return 0;
			}

			auto p3DObj = new S3DObj(bin3DObjData.n3DObjIndex,
				(float)bin3DObjData.nStartX,
				(float)bin3DObjData.nStartY,
				(float)bin3DObjData.nWidth,
				(float)bin3DObjData.nHeight);

			if (!p3DObj)
			{
				LOG_WRITELOG("Can't Create [%d] in Scene [%d]\r\n", bin3DObjData.nID, GetSceneType());
				return 0;
			}

			p3DObj->SetControlID(bin3DObjData.nID);
			p3DObj->SetCenterPos(bin3DObjData.nID,
				(float)bin3DObjData.nStartX,
				(float)bin3DObjData.nStartY,
				(float)bin3DObjData.nWidth,
				(float)bin3DObjData.nHeight);

			if (bin3DObjData.nParentID)
			{
				auto pParent = m_pControlContainer->FindControl(bin3DObjData.nParentID);

				if (pParent)
					pParent->AddChild(static_cast<TreeNode*>(p3DObj));
			}
			else
			{
				m_pControlContainer->AddItem(static_cast<SControl*>(p3DObj));
			}
		}
		break;
		case CONTROL_TYPE::CTRL_TYPE_BUTTON:
		{
			BinButton binButtonData;

			if (!fread(&binButtonData, sizeof(binButtonData), 1, fpBinary))
			{
				LOG_WRITELOG("Can't Read Resource Data[%d] in [%s]\r\n", nControlType, szBinFileName);
				fclose(fpBinary);
				return 0;
			}

			char strbuf[128]{};

			sprintf_s(strbuf, "%s", g_UIString[binButtonData.nStringIndex]);

			auto pButton = new SButton(
				binButtonData.nTextureSetIndex,
				(float)binButtonData.nStartX,
				(float)binButtonData.nStartY,
				(float)binButtonData.nWidth,
				(float)binButtonData.nHeight,
				binButtonData.nColor,
				binButtonData.nSound,
				strbuf);

			if (!pButton)
			{
				LOG_WRITELOG("Can't Create [%d] in Scene [%d]\r\n", binButtonData.nID, GetSceneType());
				return 0;
			}

			pButton->SetControlID(binButtonData.nID);

			pButton->SetCenterPos(binButtonData.nID,
				(float)binButtonData.nStartX,
				(float)binButtonData.nStartY,
				(float)binButtonData.nWidth,
				(float)binButtonData.nHeight);

			if (binButtonData.nParentID)
			{
				auto pParent = m_pControlContainer->FindControl(binButtonData.nParentID);

				if (pParent)
					pParent->AddChild(static_cast<TreeNode*>(pButton));
			}
			else
			{
				m_pControlContainer->AddItem(static_cast<SControl*>(pButton));
			}

			if (m_pControlContainer)
				pButton->SetEventListener(static_cast<IEventListener*>(m_pControlContainer));
			else
				pButton->SetEventListener(nullptr);
		}
		break;
		case CONTROL_TYPE::CTRL_TYPE_TEXT:
		{
			BinText binTextData;

			if (!fread(&binTextData, sizeof(binTextData), 1, fpBinary))
			{
				LOG_WRITELOG("Can't Read Resource Data[%d] in [%s]\r\n", nControlType, szBinFileName);
				fclose(fpBinary);
				return 0;
			}

			char strbuf[128]{};

			sprintf_s(strbuf, "%s", g_UIString[binTextData.nStringIndex]);

			auto pText = new SText(
				binTextData.nTextureSetIndex,
				strbuf,
				binTextData.nFontColor,
				(float)binTextData.nStartX,
				(float)binTextData.nStartY,
				(float)binTextData.nWidth,
				(float)binTextData.nHeight,
				binTextData.nBorder,
				binTextData.nBorderColor,
				binTextData.nTextType,
				binTextData.nAlignType);

			if (!pText)
			{
				LOG_WRITELOG("Can't Create [%d] in Scene [%d]\r\n", binTextData.nID, GetSceneType());
				return 0;
			}

			pText->SetControlID(binTextData.nID);

			pText->SetCenterPos(binTextData.nID,
				(float)binTextData.nStartX,
				(float)binTextData.nStartY,
				(float)binTextData.nWidth,
				(float)binTextData.nHeight);

			if (binTextData.nParentID)
			{
				auto pParent = m_pControlContainer->FindControl(binTextData.nParentID);

				if (pParent)
					pParent->AddChild(static_cast<TreeNode*>(pText));
			}
			else
			{
				m_pControlContainer->AddItem(static_cast<SControl*>(pText));
			}
		}
		break;
		case CONTROL_TYPE::CTRL_TYPE_EDITABLETEXT:
		{
			BinEdit binEditData;

			if (!fread(&binEditData, sizeof(binEditData), 1, fpBinary))
			{
				LOG_WRITELOG("Can't Read Resource Data[%d] in [%s]\r\n", nControlType, szBinFileName);
				fclose(fpBinary);
				return 0;
			}

			auto pEdit = new SEditableText(
				binEditData.nTextureSetIndex,
				binEditData.szString,
				binEditData.nMaxStringLength,
				binEditData.nPassword,
				binEditData.nFontColor,
				(float)binEditData.nStartX,
				(float)binEditData.nStartY,
				(float)binEditData.nWidth,
				(float)binEditData.nHeight,
				binEditData.nBorder,
				binEditData.nBorderColor,
				binEditData.nTextType,
				binEditData.nAlignType);

			if (!pEdit)
			{
				LOG_WRITELOG("Can't Create [%d] in Scene [%d]\r\n", binEditData.nID, GetSceneType());
				return 0;
			}

			pEdit->SetControlID(binEditData.nID);

			pEdit->SetCenterPos(binEditData.nID,
				(float)binEditData.nStartX,
				(float)binEditData.nStartY,
				(float)binEditData.nWidth,
				(float)binEditData.nHeight);

			if (binEditData.nParentID)
			{
				auto pParent = m_pControlContainer->FindControl(binEditData.nParentID);

				if (pParent)
					pParent->AddChild(static_cast<TreeNode*>(pEdit));
			}
			else
			{
				m_pControlContainer->AddItem(static_cast<SControl*>(pEdit));
			}

			if (m_pControlContainer)
				pEdit->SetEventListener(static_cast<IEventListener*>(m_pControlContainer));
			else
				pEdit->SetEventListener(nullptr);
		}
		break;
		case CONTROL_TYPE::CTRL_TYPE_PROGRESSBAR:
		{
			BinProgress binProgressData;

			if (!fread(&binProgressData, sizeof(binProgressData), 1, fpBinary))
			{
				LOG_WRITELOG("Can't Read Resource Data[%d] in [%s]\r\n", nControlType, szBinFileName);
				fclose(fpBinary);
				return 0;
			}

			auto pProgress = new SProgressBar(
				binProgressData.nTextureSetIndex,
				binProgressData.nCurrent,
				binProgressData.nMaxValue,
				(float)binProgressData.nStartX,
				(float)binProgressData.nStartY,
				(float)binProgressData.nWidth,
				(float)binProgressData.nHeight,
				binProgressData.nProgressColor,
				binProgressData.nColor,
				binProgressData.nStyle);

			if (!pProgress)
			{
				LOG_WRITELOG("Can't Create [%d] in Scene [%d]\r\n", binProgressData.nID, GetSceneType());
				return 0;
			}

			pProgress->SetControlID(binProgressData.nID);

			pProgress->SetCenterPos(binProgressData.nID,
				(float)binProgressData.nStartX,
				(float)binProgressData.nStartY,
				(float)binProgressData.nWidth,
				(float)binProgressData.nHeight);

			if (binProgressData.nParentID)
			{
				auto pParent = m_pControlContainer->FindControl(binProgressData.nParentID);

				if (pParent)
					pParent->AddChild(static_cast<TreeNode*>(pProgress));
			}
			else
			{
				m_pControlContainer->AddItem(static_cast<SControl*>(pProgress));
			}

			if (m_pControlContainer)
				pProgress->SetEventListener(static_cast<IEventListener*>(m_pControlContainer));
			else
				pProgress->SetEventListener(nullptr);
		}
		break;
		case CONTROL_TYPE::CTRL_TYPE_CHECKBOX:
		{
			BinCheckBox binCheckBoxData;

			if (!fread(&binCheckBoxData, sizeof(binCheckBoxData), 1, fpBinary))
			{
				LOG_WRITELOG("Can't Read Resource Data[%d] in [%s]\r\n", nControlType, szBinFileName);
				fclose(fpBinary);
				return 0;
			}

			auto pCheckBox = new SCheckBox(
				binCheckBoxData.nTextureSetIndex,
				(float)binCheckBoxData.nStartX,
				(float)binCheckBoxData.nStartY,
				(float)binCheckBoxData.nWidth,
				(float)binCheckBoxData.nHeight,
				binCheckBoxData.nColor);

			if (!pCheckBox)
			{
				LOG_WRITELOG("Can't Create [%d] in Scene [%d]\r\n", binCheckBoxData.nID, GetSceneType());
				return 0;
			}

			pCheckBox->SetControlID(binCheckBoxData.nID);

			pCheckBox->SetCenterPos(binCheckBoxData.nID,
				(float)binCheckBoxData.nStartX,
				(float)binCheckBoxData.nStartY,
				(float)binCheckBoxData.nWidth,
				(float)binCheckBoxData.nHeight);

			if (binCheckBoxData.nParentID)
			{
				auto pParent = m_pControlContainer->FindControl(binCheckBoxData.nParentID);

				if (pParent)
					pParent->AddChild(static_cast<TreeNode*>(pCheckBox));
			}
			else
			{
				m_pControlContainer->AddItem(static_cast<SControl*>(pCheckBox));
			}

			if (m_pControlContainer)
				pCheckBox->SetEventListener(static_cast<IEventListener*>(m_pControlContainer));
			else
				pCheckBox->SetEventListener(nullptr);
		}
		break;
		case CONTROL_TYPE::CTRL_TYPE_LISTBOX:
		{
			BinListBox binListBoxData;

			if (!fread(&binListBoxData, sizeof(binListBoxData), 1, fpBinary))
			{
				LOG_WRITELOG("Can't Read Resource Data[%d] in [%s]\r\n", nControlType, szBinFileName);
				fclose(fpBinary);
				return 0;
			}

			auto pListBox = new SListBox(
				binListBoxData.nTextureSetIndex,
				binListBoxData.nMaxCount,
				binListBoxData.nVisibleCount,
				(float)binListBoxData.nStartX,
				(float)binListBoxData.nStartY,
				(float)binListBoxData.nWidth,
				(float)binListBoxData.nHeight,
				binListBoxData.nColor,
				static_cast<RENDERCTRLTYPE>(binListBoxData.nFillType),
				binListBoxData.nSelect,
				binListBoxData.nScroll,
				0);

			if (!pListBox)
			{
				LOG_WRITELOG("Can't Create [%d] in Scene [%d]\r\n", binListBoxData.nID, GetSceneType());
				return 0;
			}

			pListBox->SetControlID(binListBoxData.nID);

			pListBox->SetCenterPos(binListBoxData.nID,
				(float)binListBoxData.nStartX,
				(float)binListBoxData.nStartY,
				(float)binListBoxData.nWidth,
				(float)binListBoxData.nHeight);

			if (binListBoxData.nParentID)
			{
				auto pParent = m_pControlContainer->FindControl(binListBoxData.nParentID);

				if (pParent)
					pParent->AddChild(static_cast<TreeNode*>(pListBox));
			}
			else
			{
				m_pControlContainer->AddItem(static_cast<SControl*>(pListBox));
			}

			if (m_pControlContainer)
				pListBox->SetEventListener(static_cast<IEventListener*>(m_pControlContainer));
			else
				pListBox->SetEventListener(nullptr);
		}
		break;
		default:
			LOG_WRITELOG("Not Support Control Type [%d]\r\n", nControlType);
			return 0;
		}
	}

	fclose(fpBinary);
	return 1;
}

int TMScene::FindID(char* szID)
{
	int nID = 0;
	int bFindID = 0;

	if (!strcmp(szID, "NONE"))
		return 0;

	for (int i = 0; i < 2560; ++i)
	{
		if (!strcmp(szID, g_pObjectManager->m_ResourceList[i].szString))
		{
			nID = g_pObjectManager->m_ResourceList[i].nNumber;
			bFindID = 1;
			break;
		}
	}

	if (!bFindID)
		LOG_WRITELOG("Cannot Match Resource ID [%s] in [%s].\r\n", szID, "UI\\TMResource.h");

	return nID;
}

int TMScene::InitializeScene()
{
	SetFocus(g_pApp->m_hWnd);
	return 1;
}

int TMScene::OnPacketEvent(unsigned int dwCode, char* pSBuffer)
{
	if (g_pCurrentScene != this)
		return 0;

	auto pStd = reinterpret_cast<MSG_STANDARD*>(pSBuffer);
	auto dwServerTime = g_pTimerManager->GetServerTime();

	if (!pSBuffer && (!m_dwDelayDisconnectTime || m_dwDelayDisconnectTime + 15000 < dwServerTime))
	{
		if (!m_pMessagePanel->IsVisible())
		{
			m_pMessagePanel->SetMessage(g_pMessageStringTable[13], 4000u);
			m_pMessagePanel->SetVisible(1, 1);
		}

		if (m_eSceneType != ESCENE_TYPE::ESCENE_LOGIN)
			g_pObjectManager->SetCurrentState(ObjectManager::TM_GAME_STATE::TM_SELECTSERVER_STATE);

		m_dwDelayDisconnectTime = 0;
		return 1;
	}

	if (!pStd)
	{
		if(!m_pMessagePanel->IsVisible())
		{
			m_pMessagePanel->SetMessage(g_pMessageStringTable[13], 4000u);
			m_pMessagePanel->SetVisible(1, 1);
		}

		if (m_eSceneType != ESCENE_TYPE::ESCENE_LOGIN)
			g_pObjectManager->SetCurrentState(ObjectManager::TM_GAME_STATE::TM_SELECTSERVER_STATE);

		m_dwDelayDisconnectTime = 0;
		return 1;
	}

	if (pStd->Type == 0x194)
	{
		g_pObjectManager->m_bBilling = 1;
		m_pMessageBox->SetMessage(g_pMessageStringTable[132], B_CREATE_ID, nullptr);
		m_pMessageBox->SetVisible(1);
		return 1;
	}

	if (pStd->Type == MSG_Encode_Opcode)
	{
		MSG_Encode* pEncode = reinterpret_cast<MSG_Encode*>(pStd);

		int EncodeByte1 = *(DWORD*)&pEncode->Parm[40];
		int EncodeByte2 = *(DWORD*)&pEncode->Parm[41];

		int type = (3 * (EncodeByte1 / 7) + 7 * (EncodeByte2 / 3) + 220) % 3;
		if (type)
		{
			if (type == 1)
				pStd->Type = 0x13BD;
			else if (type == 2)
				pStd->Type = 0x7BE;
		}
		else
			pStd->Type = 0xFBC;
		return 1;
	}

	if (pStd->Type == 0xFBC)
	{
		// need to decompile here... and other encode packets
		return 1;
	}

	if (pStd->Type == 0x13BD)
	{
		// need to decompile here... and other encode packets
		return 1;
	}

	if (pStd->Type == 0x7BE)
	{
		// need to decompile here... and other encode packets
		return 1;
	}
	if (!pStd->ID && (pStd->Type == MSG_MessagePanel_Opcode || pStd->Type == 0x102 || pStd->Type == 0x104 || pStd->Type == 0x105 || pStd->Type == 0x106))
	{
		char szStr[128] = { 0 };
		if (pStd->Type != MSG_MessagePanel_Opcode)
		{
			if (pStd->Type == 0x105)
			{
				auto pMessageChat = reinterpret_cast<MSG_MessageChat*>(pStd);
				if (!pMessageChat->String[0])
				{
					char str[128]{};
					char num[5]{};

					int index = *reinterpret_cast<short*>(&pMessageChat->String[2]) + 1000;
					g_pMessageStringTable[index][127] = 0;
					g_pMessageStringTable[index][126] = 0;

					strcpy(str, g_pMessageStringTable[index]);
					if (strlen(str) < 1)
						strcpy(str, _itoa(*reinterpret_cast<short*>(&pMessageChat->String[2]), num, 10));

					if (index == 465 || index == 466 || index == 485 || index == 484)
						m_pMessagePanel->SetMessage(str, 600000);
					else
						m_pMessagePanel->SetMessage(str, 4000);

					m_pMessagePanel->SetVisible(1, 1);
				}
			}
			else if (pStd->Type == 0x106)
			{
				auto pMessageChat = reinterpret_cast<MSG_MessageChat*>(pStd);
				if (!pMessageChat->String[0])
				{
					char szStr[128]{};
					char szParse[6][128]{};
					int Param = 0;
					strcpy(szStr, &pMessageChat->String[4]);

					for (int k = 0; k < 128; ++k)
					{
						if (szStr[k] == ',')
						{
							szStr[k] = ' ';
							++Param;
						}
						if (!szStr[k])
							break;
					}

					sscanf(szStr, "%s %s %s %s %s %s", szParse[0], szParse[1], szParse[2], szParse[3], szParse[4], szParse[5]);


					int index = *reinterpret_cast<short*>(&pMessageChat->String[2]) + 1000;

					memset(szStr, 0, sizeof(szStr));
					sprintf(szStr, g_pMessageStringTable[index], szParse[0], szParse[1], szParse[2], szParse[3], szParse[4], szParse[5]);

					char buffer[4]{};

					if (strlen(szStr) < 1)
						strcpy(szStr, _itoa(*reinterpret_cast<short*>(&pMessageChat->String[2]), buffer, 10));

					if (index == 465 || index == 466 || index == 485 || index == 484)
						m_pMessagePanel->SetMessage(szStr, 600000);
					else
						m_pMessagePanel->SetMessage(szStr, 4000);

					m_pMessagePanel->SetVisible(1, 1);
				}
			}

			return 1;
		}

		auto pMsgPanel = reinterpret_cast<MSG_MessagePanel*>(pStd);
		pMsgPanel->String[127] = 0;
		pMsgPanel->String[126] = 0;

		if (m_eSceneType == ESCENE_TYPE::ESCENE_SELCHAR && pMsgPanel->String[0] == '^')
		{
			char szMsg[128]{ 0 };
			sprintf_s(szMsg, "%s", &pMsgPanel->String[1]);

			m_pMessageBox2->SetMessage(szMsg, 0, nullptr);
			m_pMessageBox2->SetVisible(1);
		}
		else if (pMsgPanel->String[0] == '^')
		{
			char szMsg[128]{ 0 };
			sprintf_s(szMsg, "%s", &pMsgPanel->String[1]);

			m_pMessagePanel->SetMessage(szMsg, 7000);
			m_pMessagePanel->SetVisible(1, 1);
		}
		else if (pMsgPanel->String[0] == '!' && pMsgPanel->String[1] == '#')
		{
			for (int i = 2; i < 6; i++)
			{
				if (pMsgPanel->String[i] < '0' || pMsgPanel->String[i] > '9')
					pMsgPanel->String[i] = '0';
			}

			TMFieldScene* pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
			pFScene->m_nYear = static_cast<unsigned short>(pMsgPanel->String[3] - 48)
				+ 10 * static_cast<unsigned short>(pMsgPanel->String[2] - 48);
			pFScene->m_nDays = static_cast<unsigned short>(pMsgPanel->String[6] - 48)
				+ 10 * static_cast<unsigned short>(pMsgPanel->String[5] - 48)
				+ 100 * static_cast<unsigned short>(pMsgPanel->String[4] - 48);

			return 1;
		}
		else if (pMsgPanel->String[1] == '!' && pMsgPanel->String[2] == '!' && pMsgPanel->String[3] == '!')
		{
			auto pFocusedObject = static_cast<TMObject*>(m_pMyHuman);

			if ((int)pFocusedObject->m_vecPosition.x >> 7 == 31 && (int)pFocusedObject->m_vecPosition.y >> 7 == 31)
			{
				for (int nType = 0; nType < 5; ++nType)
				{
					for (int j = 0; j < 5; ++j)
					{
						auto pFireWork = new TMEffectFireWork({ (pFocusedObject->m_vecPosition.x) - 10.0f + (5.0f * nType), 7.0f, ((pFocusedObject->m_vecPosition.y - 10.0f) + 5.0f * j) + 8.0f }, nType);

						g_pCurrentScene->AddChild(pFireWork);
					}
				}
			}

			if (pFocusedObject->IsInTown() == 1 || (int)pFocusedObject->m_vecPosition.x >> 7 != 31 || (int)pFocusedObject->m_vecPosition.y >> 7 != 31)
			{
				m_pMessagePanel->SetMessage(pMsgPanel->String, 4000);
				m_pMessagePanel->SetVisible(1, 1);
			}
		}
		else if (pMsgPanel->String[1] == '!' && pMsgPanel->String[2] == '!' && pMsgPanel->String[3] == '#')
		{
			if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD && pMsgPanel->String[4] == 'E')
			{
				auto pKilled = static_cast<TMHuman*>(g_pObjectManager->GetHumanByID(static_cast<TMFieldScene*>(g_pCurrentScene)->m_dwKhepraID));

				if (pKilled)
				{
					pKilled->m_stScore.Hp = 0;
					pKilled->Die();
				}

				static_cast<TMFieldScene*>(g_pCurrentScene)->m_dwKhepraID = 0;

				for (int iSt = 0; iSt < 5; ++iSt)
					pMsgPanel->String[iSt] = '_';
			}
		}
		else if (pMsgPanel->String[0] == '!' || pMsgPanel->String[1] == '!')
		{
			if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
			{
				for (int n = 2; n < 8; ++n)
				{
					if (pMsgPanel->String[n] < '0' || pMsgPanel->String[n] > '9')
						pMsgPanel->String[n] = '0';
				}

				TMFieldScene* pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
				pFScene->m_NightmareTime.wHour = pMsgPanel->String[3] - 48 + 10 * (pMsgPanel->String[2] - 48);
				pFScene->m_NightmareTime.wMonth = pMsgPanel->String[5] - 48 + 10 * (pMsgPanel->String[4] - 48);
				pFScene->m_NightmareTime.wSecond = pMsgPanel->String[7] - 48 + 10 * (pMsgPanel->String[6] - 48);
				pFScene->m_dwLastNightmareTime = g_pTimerManager->GetServerTime();
				return 1;
			}
		}
		else if (pMsgPanel->String[0] == '!')
		{
			SYSTEMTIME sysTime;
			GetLocalTime(&sysTime);

			if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
			{
				auto pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);

				auto pItem3 = new SListBoxItem(" ", 0xFFFFFFFF, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777u, 1u, 0);
				pFScene->m_pHelpList[3]->AddItem(pItem3);

				char szTime[128]{ 0 };
				char _Buffer[128]{ 0 };

				sprintf_s(szTime, "SMS [%02d:%02d:%02d]", sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
				auto pItem = new SListBoxItem(szTime, 0xFFBBFFFF, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777u, 1u, 0);
				pFScene->m_pHelpList[3]->AddItem(pItem);

				sprintf_s(_Buffer, "%s", &pMsgPanel->String[1]);

				auto pItem2 = new SListBoxItem(_Buffer, 0xFFBBFFCC, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777u, 1u, 0);
				pFScene->m_pHelpList[3]->AddItem(pItem2);

				if (pFScene->m_pHelpMemo)
					pFScene->m_pHelpMemo->SetVisible(1);
			}
			else
			{
				for (int l = 0; l < 98; ++l)
				{
					if (!g_pObjectManager->m_stMemo[l].szString[0] && !g_pObjectManager->m_stMemo[l + 1].szString[0])
					{
						g_pObjectManager->m_stMemo[l].dwColor = -1;
						sprintf_s(g_pObjectManager->m_stMemo[l].szString, "");
						g_pObjectManager->m_stMemo[l + 1].dwColor = 0xFFBBFFFF;
						sprintf_s(g_pObjectManager->m_stMemo[l + 1].szString, "SMS [%02d:%02d:%02d]", sysTime.wHour, sysTime.wMinute, sysTime.wSecond);

						g_pObjectManager->m_stMemo[l + 2].dwColor = 0xFFBBFFCC;
						sprintf_s(g_pObjectManager->m_stMemo[l + 2].szString, "%s", &pMsgPanel->String[1]);
					}
				}
			}

			m_pMessagePanel->SetMessage(&pMsgPanel->String[1], 4000u);
			m_pMessagePanel->SetVisible(1, 1);
		}
		else if (pMsgPanel->String[0] == '2' && pMsgPanel->String[1] == '0' && pMsgPanel->String[2] == '0')
		{
			char Msg[128]{ 0 };
			if (m_pMyHuman)
				sprintf_s(Msg, "%s %d %d %d", pMsgPanel->String, g_pObjectManager->m_nServerIndex, static_cast<int>(m_pMyHuman->m_vecPosition.x), 
					static_cast<int>(m_pMyHuman->m_vecPosition.y));
			else
				sprintf_s(Msg, "%s %d", pMsgPanel->String, g_pObjectManager->m_nServerIndex);

			m_pMessagePanel->SetMessage(Msg, 4000u);
			m_pMessagePanel->SetVisible(1, 1);
		}
		else
		{
			m_pMessagePanel->SetMessage(pMsgPanel->String, 4000u);
			m_pMessagePanel->SetVisible(1, 1);
		}

		SListBox* pChatList = static_cast<SListBox*>(m_pControlContainer->FindControl(65667));

		int len = strlen(pMsgPanel->String);
		int size = 50;
		if (len > size)
		{
			char szMsg2[128]{};
			char szMsg3[128]{};

			if (IsClearString(pMsgPanel->String, size - 1))
			{
				strncpy(szMsg3, pMsgPanel->String, size);
				sprintf(szMsg2, "%s", &pMsgPanel->String[size]);
			}
			else
			{
				strncpy(szMsg3, pMsgPanel->String, size - 1);
				sprintf(szMsg2, "%s", &pMsgPanel->String[size - 1]);
			}

			SListBoxItem* ipNewItem = new SListBoxItem(szMsg3, 0xFFCCAAFF, 0.0f, 0.0f, 280.0f, 16.0f, 0, 0x77777777, 1u, 0);
			if (ipNewItem && pChatList)
				pChatList->AddItem(ipNewItem);

			SListBoxItem* ipNewItem2 = new SListBoxItem(szMsg2, 0xFFCCAAFF, 0.0f, 0.0f, 280.0f, 16.0, 0, 0x77777777, 1u, 0);
			if (ipNewItem2 && pChatList)
				pChatList->AddItem(ipNewItem2);
		}
		else
		{
			if (g_pCurrentScene->m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
			{
				TMFieldScene* pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
				if (!strcmp(pMsgPanel->String, "Whisper : Off"))
				{
					sprintf(pMsgPanel->String, "%s%s", g_pMessageStringTable[448], g_pMessageStringTable[447]);
					pFScene->SetWhisper(0);
				}
				if (!strcmp(pMsgPanel->String, "Whisper : On"))
				{
					sprintf(pMsgPanel->String, "%s%s", g_pMessageStringTable[448], g_pMessageStringTable[446]);
					pFScene->SetWhisper(1);
				}
				if (!strcmp(pMsgPanel->String, "Citizen Chatting : Off"))
				{
					sprintf(pMsgPanel->String, "%s%s", g_pMessageStringTable[449], g_pMessageStringTable[447]);
					pFScene->SetPartyChat(0);
				}
				if (!strcmp(pMsgPanel->String, "Citizen Chatting : On"))
				{
					sprintf(pMsgPanel->String, "%s%s", g_pMessageStringTable[449], g_pMessageStringTable[446]);
					pFScene->SetPartyChat(1);
				}
				if (!strcmp(pMsgPanel->String, "Guild Chatting : Off"))
				{
					sprintf(pMsgPanel->String, "%s%s", g_pMessageStringTable[450], g_pMessageStringTable[447]);
					pFScene->SetGuildChat(0);
				}
				if (!strcmp(pMsgPanel->String, "Guild Chatting : On"))
				{
					sprintf(pMsgPanel->String, "%s%s", g_pMessageStringTable[450], g_pMessageStringTable[446]);
					pFScene->SetGuildChat(1);
				}
				if (!strcmp(pMsgPanel->String, "Kingdom Chatting : On"))
				{
					sprintf(pMsgPanel->String, "%s%s", g_pMessageStringTable[451], g_pMessageStringTable[446]);
					pFScene->SetKingDomChat(1);
				}
				if (!strcmp(pMsgPanel->String, "Kingdom Chatting : Off"))
				{
					sprintf(pMsgPanel->String, "%s%s", g_pMessageStringTable[451], g_pMessageStringTable[447]);
					pFScene->SetKingDomChat(0);
				}
			}

			SListBoxItem* ipNewItem = new SListBoxItem(pMsgPanel->String, 0xFFCCAAFF, 0.0f, 0.0f, 280.0f, 16.0f, 0, 0x77777777, 1u, 0);
			if (ipNewItem && pChatList)
				pChatList->AddItem(ipNewItem);
		}

		SControl* pLoginOK = m_pControlContainer->FindControl(65873);
		if (pLoginOK)
			pLoginOK->SetEnable(1);
		return 1;
	}
	if (pStd->Type == MSG_MessageShout_Opcode)
	{
		MSG_MessageWhisper* pShoutMessage = reinterpret_cast<MSG_MessageWhisper*>(pStd);
		pShoutMessage->String[111] = 0;
		pShoutMessage->String[110] = 0;

		TMFieldScene* pFScene = static_cast<TMFieldScene*>(g_pCurrentScene);
		if (!pFScene->m_pChatGeneral || pFScene->GetSceneType() != ESCENE_TYPE::ESCENE_FIELD || pFScene->m_pCHP->m_bSelectEnable)
		{
			int nIndex = 0;
			unsigned int dwColor = 0xFF00CD00;

			SListBox* pChatList = pFScene->m_pChatList;

			int nLen = strlen(pShoutMessage->MobName);

			SListBoxItem* ipNewItem = new SListBoxItem(pShoutMessage->MobName,
				dwColor,
				0.0f,
				0.0f,
				(float)nLen * 6.6999998f,
				16.0f,
				0,
				0xFFFFFF00,
				1u,
				0);

			ipNewItem->m_bBGColor = 0;
			if (ipNewItem && pChatList)
				pChatList->AddItem(ipNewItem);

			pFScene->m_dwChatTime = g_pTimerManager->GetServerTime();
			return 1;
		}
		else
			return 1;
	}
	if (pStd->Type == 0x7DB)
	{
		MSG_STANDARDPARM* m = reinterpret_cast<MSG_STANDARDPARM*>(pStd);

		g_pApp->china_bWrite = 1;
		g_pApp->china_Playtime = m->Parm / 60;
		LOG_WRITELOG("get start Time : %d \r\n", g_pApp->china_Playtime);
		return 1;
	}

	if (m_pControlContainer && m_pControlContainer->OnPacketEvent(dwCode, pSBuffer) == 1)
		return 1;

	TreeNode::OnPacketEvent(dwCode, pSBuffer);
	return 0;
}

int TMScene::OnKeyDownEvent(unsigned int iKeyCode)
{
	if (g_pCurrentScene != this)
		return 0;

	if (m_pControlContainer && m_pControlContainer->OnKeyDownEvent(iKeyCode) == 1)
		return 1;
	
	TreeNode::OnKeyDownEvent(iKeyCode);
	return 0;
}

int TMScene::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	if (g_pCurrentScene != this)
		return 0;

	if (m_pControlContainer && m_pControlContainer->OnMouseEvent(dwFlags, wParam, nX, nY) == 1)
		return 1;

	TreeNode::OnMouseEvent(dwFlags, wParam, nX, nY);
	return 0;
}

int TMScene::OnKeyUpEvent(unsigned int iKeyCode)
{
	if (g_pCurrentScene != this)
		return 0;

	if (m_pControlContainer && m_pControlContainer->OnKeyUpEvent(iKeyCode) == 1)
		return 1;

	TreeNode::OnKeyUpEvent(iKeyCode);
	return 0;
}

int TMScene::OnCharEvent(char iCharCode, int lParam)
{
	if (g_pCurrentScene != this)
		return 0;

	if (m_pControlContainer && m_pControlContainer->OnCharEvent(iCharCode, lParam) == 1)
		return 1;
	
	return TreeNode::OnCharEvent(iCharCode, lParam);
}

int TMScene::OnIMEEvent(char* ipComposeString)
{
	if (g_pCurrentScene != this)
		return 0;

	if (m_pControlContainer && m_pControlContainer->OnIMEEvent(ipComposeString) == 1)
		return 1;
	
	return 0;
}

int TMScene::OnChangeIME()
{
	return m_pControlContainer && m_pControlContainer->OnChangeIME() == 1;
}

int TMScene::OnAccel(int nMsg)
{
	return 1;
}

int TMScene::FrameMove(unsigned int dwServerTime)
{
	if (g_pCurrentScene != this)
		return 1;

	if (m_pControlContainer)
		m_pControlContainer->FrameMove(dwServerTime);

	if (m_sPlayDemo >= 0)
		CameraAction();

	if (m_bCriticalError == 1)
		return 1;

	m_pMouseOverHuman = nullptr;
	m_pMouseOverItem = nullptr;

	auto pFocusedObject = static_cast<TMObject*>(m_pMyHuman);

	if (pFocusedObject && m_pGround)
	{
		float dX = pFocusedObject->m_vecPosition.x - m_pGround->m_vecOffset.x;
		float dY = pFocusedObject->m_vecPosition.y - m_pGround->m_vecOffset.y;

		int nShold = 14;

		if (((int)pFocusedObject->m_vecPosition.x >> 7) > 26 &&
			((int)pFocusedObject->m_vecPosition.x >> 7) < 31 &&
			((int)pFocusedObject->m_vecPosition.y >> 7) > 20 &&
			((int)pFocusedObject->m_vecPosition.y >> 7) < 25)
		{
			nShold = 20;
		}

		if (m_pGround->m_vecOffsetIndex.x == 17 && m_pGround->m_vecOffsetIndex.y == 10)
			nShold = 20;

		if (dX >= 0.0f && (float)nShold > dX)
		{
			if (!m_pGround->m_pLeftGround)
				GroundNewAttach(EDirection::EDIR_LEFT);
		}
		else if (dX < 0.0f && dX > (float)-nShold)
		{
			if (m_pGround->m_pLeftGround)
			{
				m_pGround = m_pGround->m_pLeftGround;

				m_nCurrentGroundIndex = (m_nCurrentGroundIndex + 1) % 2;
				
				m_pGround->SetMiniMapData();
			}
		}
		else if (dX > (float)(128 - nShold) && dX < 128.0f)
		{
			if (!m_pGround->m_pRightGround)
				GroundNewAttach(EDirection::EDIR_RIGHT);
		}
		else if (dX >= 128.0f && (float)(nShold + 128) > dX && m_pGround->m_pRightGround)
		{
			m_pGround = m_pGround->m_pRightGround;

			m_nCurrentGroundIndex = (m_nCurrentGroundIndex + 1) % 2;

			m_pGround->SetMiniMapData();
		}

		if (dY >= 0.0f && (float)nShold > dY)
		{
			if (!m_pGround->m_pUpGround)
				GroundNewAttach(EDirection::EDIR_UP);
		}
		else if (dY < 0.0f && dY > (float)-nShold)
		{
			if (m_pGround->m_pUpGround)
			{
				m_pGround = m_pGround->m_pUpGround;

				m_nCurrentGroundIndex = (m_nCurrentGroundIndex + 1) % 2;

				m_pGround->SetMiniMapData();
			}
		}
		else if (dY > (float)(128 - nShold) && (float)128 > dY)
		{
			if (!m_pGround->m_pDownGround)
				GroundNewAttach(EDirection::EDIR_DOWN);
		}
		else if (dY >= (float)128 && (float)(nShold + 128) > dY && m_pGround->m_pDownGround)
		{
			m_pGround = m_pGround->m_pDownGround;

			m_nCurrentGroundIndex = (m_nCurrentGroundIndex + 1) % 2;

			m_pGround->SetMiniMapData();
		}
	}

	return 1;
}

int TMScene::ReloadScene()
{
	if (m_pControlContainer != nullptr)
	{
		delete m_pControlContainer;

		m_pControlContainer = nullptr;
	}

	return InitializeScene();
}

ESCENE_TYPE TMScene::GetSceneType()
{
	return m_eSceneType;
}

void TMScene::Cleanup()
{
	;
}

char heightMapData[128][128]{};
int TMScene::GroundNewAttach(EDirection eDir)
{
	memset(heightMapData, 0, sizeof(heightMapData));
	if (!m_pGround)
		return 0;

	int x{};
	int y{};

	if (eDir == EDirection::EDIR_LEFT)
	{
		if (m_pGround->m_pLeftGround || m_pGround->m_cLeftEnable != 1)
			return 0;

		x = m_pGround->m_vecOffsetIndex.x - 1;
		y = m_pGround->m_vecOffsetIndex.y;
	}
	else if (eDir == EDirection::EDIR_RIGHT)
	{
		if (m_pGround->m_pRightGround || m_pGround->m_cRightEnable != 1)
			return 0;

		x = m_pGround->m_vecOffsetIndex.x + 1;
		y = m_pGround->m_vecOffsetIndex.y;
	}
	else if (eDir == EDirection::EDIR_UP)
	{
		if (m_pGround->m_pUpGround || m_pGround->m_cUpEnable != 1)
			return 0;

		x = m_pGround->m_vecOffsetIndex.x;
		y = m_pGround->m_vecOffsetIndex.y - 1;
	}
	else if (eDir == EDirection::EDIR_DOWN)
	{
		if (m_pGround->m_pDownGround || m_pGround->m_cDownEnable != 1)
			return 0;

		x = m_pGround->m_vecOffsetIndex.x;
		y = m_pGround->m_vecOffsetIndex.y + 1;
	}

	char fileNameTrn[128]{};
	char fileNameDat[128]{};

	sprintf_s(fileNameTrn, "Env\\Field%02d%02d.trn", x, y);
	sprintf_s(fileNameDat, "Env\\Field%02d%02d.dat", x, y);

	int gId = (m_nCurrentGroundIndex + 1) % 2;

	if (m_pGroundList[gId])
	{
		if (m_pGroundList[gId]->m_vecOffsetIndex.x == m_pGround->m_vecOffsetIndex.x + 1 &&
			m_pGroundList[gId]->m_vecOffsetIndex.y == m_pGround->m_vecOffsetIndex.y)
		{
			for (int i = 0; i < 128; ++i)
				memcpy(heightMapData[i], m_HeightMapData[i], 128);
		}
		else if (m_pGroundList[gId]->m_vecOffsetIndex.x == m_pGround->m_vecOffsetIndex.x &&
			m_pGroundList[gId]->m_vecOffsetIndex.y == m_pGround->m_vecOffsetIndex.y + 1)
		{
			for (int i = 0; i < 128; ++i)
				memcpy(heightMapData[i], m_HeightMapData[i], 128);
		}
		else if (m_pGroundList[gId]->m_vecOffsetIndex.x == m_pGround->m_vecOffsetIndex.x - 1 &&
			m_pGroundList[gId]->m_vecOffsetIndex.y == m_pGround->m_vecOffsetIndex.y)
		{
			for (int i = 0; i < 128; ++i)
				memcpy(heightMapData[i], &m_HeightMapData[i][128], 128);
		}
		else if (m_pGroundList[gId]->m_vecOffsetIndex.x == m_pGround->m_vecOffsetIndex.x &&
			m_pGroundList[gId]->m_vecOffsetIndex.y == m_pGround->m_vecOffsetIndex.y - 1)
		{
			for (int i = 0; i < 128; ++i)
				memcpy(heightMapData[i], m_HeightMapData[i + 128], 128);
		}
	}
	else
	{
		for (int i = 0; i < 128; ++i)
			memcpy(heightMapData[i], m_HeightMapData[i], 128);
	}
	
	auto pGround = new TMGround();

	if (!pGround->LoadTileMap(fileNameTrn))
	{
		delete pGround;
		return 0;
	}

	if (m_pGroundList[gId])
	{
		delete m_pGroundList[gId];

		m_pGroundList[gId] = nullptr;
	}

	if (m_pObjectContainerList[gId])
	{
		delete m_pObjectContainerList[gId];

		m_pObjectContainerList[gId] = nullptr;
	}

	m_pGroundList[gId] = pGround;

	m_pGroundObjectContainer->AddChild(m_pGroundList[gId]);

	if (m_pGroundList[m_nCurrentGroundIndex])
		m_pGroundList[m_nCurrentGroundIndex]->Attach(m_pGroundList[gId]);

	m_pObjectContainerList[gId] = new TMObjectContainer(m_pGroundList[gId]);

	if (!m_pObjectContainerList[gId]->Load(fileNameDat))
	{
		if (m_pObjectContainerList[gId])
		{
			delete m_pObjectContainerList[gId];
			
			m_pObjectContainerList[gId] = nullptr;
		}
		
		LOG_WRITELOG("DataFile Not Found : %s\r\n", fileNameDat);
		
		if (!m_bCriticalError)
			LogMsgCriticalError(12, 0, 0, 0, 0);

		m_bCriticalError = 1;
		return 0;
	}

	if (m_pObjectContainerList[m_nCurrentGroundIndex])
	{
		if (eDir == EDirection::EDIR_DOWN)
			m_pObjectContainerList[m_nCurrentGroundIndex]->SetPrevNode(m_pObjectContainerList[gId]);
		else
			m_pObjectContainerList[m_nCurrentGroundIndex]->SetNextNode(m_pObjectContainerList[gId]);
	}

	g_pTextureManager->ReleaseNotUsingTexture();
	
	memset(m_HeightMapData, 0, 4);

	switch (eDir)
	{
	case EDirection::EDIR_LEFT:
		for (int i = 0; i < 128; ++i)
		{
			memcpy(m_HeightMapData[i], m_pGround->m_pLeftGround->m_pMaskData[i], 128);
			memcpy(&m_HeightMapData[i][128], heightMapData[i], 128);
		}
		g_HeightPosX = (int)m_pGround->m_pLeftGround->m_vecOffset.x;
		g_HeightPosY = (int)m_pGround->m_pLeftGround->m_vecOffset.y;
		break;
	case EDirection::EDIR_RIGHT:
		for (int i = 0; i < 128; ++i)
		{
			memcpy(&m_HeightMapData[i][128], m_pGround->m_pRightGround->m_pMaskData[i], 128);
			memcpy(m_HeightMapData[i], heightMapData[i], 128);
		}
		g_HeightPosX = (int)m_pGround->m_vecOffset.x;
		g_HeightPosY = (int)m_pGround->m_vecOffset.y;
		break;
	case EDirection::EDIR_UP:
		for (int i = 0; i < 128; ++i)
		{
			memcpy(&m_HeightMapData[i], m_pGround->m_pUpGround->m_pMaskData[i], 128);
			memcpy(&m_HeightMapData[i + 128], heightMapData[i], 128);
		}
		g_HeightPosX = (int)m_pGround->m_pUpGround->m_vecOffset.x;
		g_HeightPosY = (int)m_pGround->m_pUpGround->m_vecOffset.y;
		break;
	case EDirection::EDIR_DOWN:
		for (int i = 0; i < 128; ++i)
		{
			memcpy(&m_HeightMapData[i + 128], m_pGround->m_pDownGround->m_pMaskData[i], 128);
			memcpy(&m_HeightMapData[i], heightMapData[i], 128);
		}
		g_HeightPosX = (int)m_pGround->m_vecOffset.x;
		g_HeightPosY = (int)m_pGround->m_vecOffset.y;
		break;
	}

	BASE_ApplyAttribute((char*)m_HeightMapData, 256);

	memcpy(m_GateMapData, m_HeightMapData, sizeof(m_HeightMapData));

	SaveHeightMap(fileNameTrn);

	m_pGround->SetMiniMapData();

	m_nAdjustTime = 0;
	m_dwInitTime = g_pTimerManager->GetServerTime();

	return 1;
}

D3DXVECTOR3 TMScene::GroundGetPickPos()
{
	D3DXVECTOR3 vPickPos{ 0.0f, -10000.0f, 0.0f };
	D3DXVECTOR3 vPickTempPos{ 0.0f, -10000.0f, 0.0f };
	D3DXVECTOR3 vFocusePos{ 0.0f, -9000.0f, 0.0f };

	auto pFocusedObject = static_cast<TMObject*>(m_pMyHuman);

	if (pFocusedObject)
	{
		vFocusePos.x = pFocusedObject->m_vecPosition.x;
		vFocusePos.y = pFocusedObject->m_fHeight;
		vFocusePos.z = pFocusedObject->m_vecPosition.x;
	}

	if (!m_pGround)
		return vPickPos;

	vPickTempPos = m_pGround->GetPickPos();

	if (fabsf(vFocusePos.y - vPickTempPos.y) < 4.0f)
		vPickPos = vPickTempPos;

	if (vPickPos.y >= -5000.0f && fabsf(vFocusePos.y - vPickPos.y) < 2.0f)
		return vPickPos;

	if (m_pGround->m_pLeftGround)
	{
		vPickTempPos = m_pGround->m_pLeftGround->GetPickPos();

		if (fabsf(vFocusePos.y - vPickPos.y) > fabsf(vFocusePos.y - vPickTempPos.y) || fabsf(vFocusePos.y - vPickTempPos.y) < 4.0f)
		{
			vPickPos = vPickTempPos;

			if (vPickTempPos.y > -5000.0f && fabsf(vFocusePos.y - vPickPos.y) < 2.0f)
				return vPickPos;
		}
	}

	if (m_pGround->m_pRightGround)
	{
		vPickTempPos = m_pGround->m_pRightGround->GetPickPos();

		if (fabsf(vFocusePos.y - vPickPos.y) > fabsf(vFocusePos.y - vPickTempPos.y))
		{
			vPickPos = vPickTempPos;

			if (vPickTempPos.y > -5000.0f && fabsf(vFocusePos.y - vPickPos.y) < 2.0f || fabsf(vFocusePos.y - vPickTempPos.y < 4.0f))
				return vPickPos;
		}
	}

	if (m_pGround->m_pUpGround)
	{
		vPickTempPos = m_pGround->m_pUpGround->GetPickPos();

		if (fabsf(vFocusePos.y - vPickPos.y) > fabsf(vFocusePos.y - vPickTempPos.y))
		{
			vPickPos = vPickTempPos;

			if (vPickTempPos.y > -5000.0f && fabsf(vFocusePos.y - vPickPos.y) < 2.0f || fabsf(vFocusePos.y - vPickTempPos.y) < 4.0f)
				return vPickPos;
		}
	}

	if (m_pGround->m_pDownGround)
	{
		vPickTempPos = m_pGround->m_pDownGround->GetPickPos();

		if (fabsf(vFocusePos.y - vPickPos.y) > fabsf(vFocusePos.y - vPickTempPos.y))
		{
			vPickPos = vPickTempPos;

			if (vPickTempPos.y > -5000.0 && fabsf(vFocusePos.y - vPickPos.y) < 2.0f || fabsf(vFocusePos.y - vPickTempPos.y) < 4.0f)
				return vPickPos;

		}
	}

	return vPickPos;
}

int TMScene::GroundGetTileType(TMVector2 vecPosition)
{
	int nTileType{};

	if (m_pGround)
	{
		if (vecPosition.x >= m_pGround->m_vecOffset.x &&
			vecPosition.x < (m_pGround->m_vecOffset.x + 128.0f) && 
			vecPosition.y >= m_pGround->m_vecOffset.y &&
			vecPosition.y < (m_pGround->m_vecOffset.y + 128.0f))
		{
			nTileType = m_pGround->GetTileType(vecPosition);
		}
		else if (m_pGround->m_pLeftGround
			&& vecPosition.x >= m_pGround->m_pLeftGround->m_vecOffset.x
			&& vecPosition.x < (m_pGround->m_pLeftGround->m_vecOffset.x + 128.0f)
			&& vecPosition.y >= m_pGround->m_pLeftGround->m_vecOffset.y
			&& vecPosition.y < (m_pGround->m_pLeftGround->m_vecOffset.y + 128.0f))
		{
			nTileType = m_pGround->m_pLeftGround->GetTileType(vecPosition);
		}
		else if (m_pGround->m_pRightGround
			&& vecPosition.x >= m_pGround->m_pRightGround->m_vecOffset.x
			&& vecPosition.x < (m_pGround->m_pRightGround->m_vecOffset.x + 128.0f)
			&& vecPosition.y >= m_pGround->m_pRightGround->m_vecOffset.y
			&& vecPosition.y < (m_pGround->m_pRightGround->m_vecOffset.y + 128.0f))
		{
			nTileType = m_pGround->m_pRightGround->GetTileType(vecPosition);
		}
		else if (m_pGround->m_pUpGround
			&& vecPosition.x >= m_pGround->m_pUpGround->m_vecOffset.x
			&& vecPosition.x < (m_pGround->m_pUpGround->m_vecOffset.x + 128.0f)
			&& vecPosition.y >= m_pGround->m_pUpGround->m_vecOffset.y
			&& vecPosition.y < (m_pGround->m_pUpGround->m_vecOffset.y + 128.0f))
		{
			nTileType = m_pGround->m_pUpGround->GetTileType(vecPosition);
		}
		else if (m_pGround->m_pDownGround
			&& vecPosition.x >= m_pGround->m_pDownGround->m_vecOffset.x
			&& vecPosition.x < (m_pGround->m_pDownGround->m_vecOffset.x + 128.0f)
			&& vecPosition.y >= m_pGround->m_pDownGround->m_vecOffset.y
			&& vecPosition.y < (m_pGround->m_pDownGround->m_vecOffset.y + 128.0f))
		{
			nTileType = m_pGround->m_pDownGround->GetTileType(vecPosition);
		}
	}

	return nTileType;
}

int TMScene::GroundGetMask(TMVector2 vecPosition)
{
	int nXIndex = (int)vecPosition.x - g_HeightPosX;
	int nYIndex = (int)vecPosition.y - g_HeightPosY;

	if (nXIndex < 0)
		nXIndex = 0;

	if (nYIndex < 0)
		nYIndex = 0;

	if (nXIndex > 256)
		nXIndex = 255;

	if (nYIndex > 256)
		nYIndex = 255;

	int value = m_HeightMapData[nYIndex][nXIndex];
	return m_HeightMapData[nYIndex][nXIndex];
}

int TMScene::GroundGetMask(IVector2 vecPosition)
{
	int nXIndex = vecPosition.x - g_HeightPosX;
	int nYIndex = vecPosition.y - g_HeightPosY;

	if (nXIndex < 0)
		nXIndex = 0;

	if (nYIndex < 0)
		nYIndex = 0;

	if (nXIndex > 256)
		nXIndex = 255;

	if (nYIndex > 256)
		nYIndex = 255;

	return m_HeightMapData[nYIndex][nXIndex];
}

float TMScene::GroundGetHeight(TMVector2 vecPosition)
{
	float fHeight{ -10000.0f };

	if (m_pGround != nullptr)
	{
		if (vecPosition.x >= m_pGround->m_vecOffset.x &&
			vecPosition.x < (m_pGround->m_vecOffset.x + 128.0f) &&
			vecPosition.y >= m_pGround->m_vecOffset.y &&
			vecPosition.y < (m_pGround->m_vecOffset.y + 128.0f))
		{
			fHeight = m_pGround->GetHeight(vecPosition);
		}
		else if (m_pGround->m_pLeftGround
			&& vecPosition.x >= m_pGround->m_pLeftGround->m_vecOffset.x
			&& vecPosition.x < (m_pGround->m_pLeftGround->m_vecOffset.x + 128.0f)
			&& vecPosition.y >= m_pGround->m_pLeftGround->m_vecOffset.y
			&& vecPosition.y < (m_pGround->m_pLeftGround->m_vecOffset.y + 128.0f))
		{
			fHeight = m_pGround->m_pLeftGround->GetHeight(vecPosition);
		}
		else if (m_pGround->m_pRightGround
			&& vecPosition.x >= m_pGround->m_pRightGround->m_vecOffset.x
			&& vecPosition.x < (m_pGround->m_pRightGround->m_vecOffset.x + 128.0f)
			&& vecPosition.y >= m_pGround->m_pRightGround->m_vecOffset.y
			&& vecPosition.y < (m_pGround->m_pRightGround->m_vecOffset.y + 128.0f))
		{
			fHeight = m_pGround->m_pRightGround->GetHeight(vecPosition);
		}
		else if (m_pGround->m_pUpGround
			&& vecPosition.x >= m_pGround->m_pUpGround->m_vecOffset.x
			&& vecPosition.x < (m_pGround->m_pUpGround->m_vecOffset.x + 128.0f)
			&& vecPosition.y >= m_pGround->m_pUpGround->m_vecOffset.y
			&& vecPosition.y < (m_pGround->m_pUpGround->m_vecOffset.y + 128.0f))
		{
			fHeight = m_pGround->m_pUpGround->GetHeight(vecPosition);
		}
		else if (m_pGround->m_pDownGround
			&& vecPosition.x >= m_pGround->m_pDownGround->m_vecOffset.x
			&& vecPosition.x < (m_pGround->m_pDownGround->m_vecOffset.x + 128.0f)
			&& vecPosition.y >= m_pGround->m_pDownGround->m_vecOffset.y
			&& vecPosition.y < (m_pGround->m_pDownGround->m_vecOffset.y + 128.0f))
		{
			fHeight = m_pGround->m_pDownGround->GetHeight(vecPosition);
		}
	}

	return fHeight;
}

D3DCOLORVALUE TMScene::GroundGetColor(TMVector2 vecPosition)
{
	D3DCOLORVALUE color{ 1.0f, 1.0f, 1.0f, 1.0f };

	if (m_pGround != nullptr)
	{
		if (vecPosition.x >= m_pGround->m_vecOffset.x &&
			vecPosition.x < (m_pGround->m_vecOffset.x + 128.0f) &&
			vecPosition.y >= m_pGround->m_vecOffset.y &&
			vecPosition.y < (m_pGround->m_vecOffset.y + 128.0f))
		{
			color = m_pGround->GetColor(vecPosition);
		}

		else if (m_pGround->m_pLeftGround
			&& vecPosition.x >= m_pGround->m_pLeftGround->m_vecOffset.x
			&& vecPosition.x < (m_pGround->m_pLeftGround->m_vecOffset.x + 128.0f)
			&& vecPosition.y >= m_pGround->m_pLeftGround->m_vecOffset.y
			&& vecPosition.y < (m_pGround->m_pLeftGround->m_vecOffset.y + 128.0f))
		{
			color = m_pGround->m_pLeftGround->GetColor(vecPosition);
		}

		else if (m_pGround->m_pRightGround
			&& vecPosition.x >= m_pGround->m_pRightGround->m_vecOffset.x
			&& vecPosition.x < (m_pGround->m_pRightGround->m_vecOffset.x + 128.0f)
			&& vecPosition.y >= m_pGround->m_pRightGround->m_vecOffset.y
			&& vecPosition.y < (m_pGround->m_pRightGround->m_vecOffset.y + 128.0f))
		{
			color = m_pGround->m_pRightGround->GetColor(vecPosition);
		}

		else if (m_pGround->m_pUpGround
			&& vecPosition.x >= m_pGround->m_pUpGround->m_vecOffset.x
			&& vecPosition.x < (m_pGround->m_pUpGround->m_vecOffset.x + 128.0f)
			&& vecPosition.y >= m_pGround->m_pUpGround->m_vecOffset.y
			&& vecPosition.y < (m_pGround->m_pUpGround->m_vecOffset.y + 128.0f))
		{
			color = m_pGround->m_pUpGround->GetColor(vecPosition);
		}

		else if (m_pGround->m_pDownGround
			&& vecPosition.x >= m_pGround->m_pDownGround->m_vecOffset.x
			&& vecPosition.x < (m_pGround->m_pDownGround->m_vecOffset.x + 128.0f)
			&& vecPosition.y >= m_pGround->m_pDownGround->m_vecOffset.y
			&& vecPosition.y < (m_pGround->m_pDownGround->m_vecOffset.y + 128.0f))
		{
			color = m_pGround->m_pDownGround->GetColor(vecPosition);
		}
	}

	return color;
}

void TMScene::GroundSetColor(TMVector2 vecPosition, unsigned int dwColor)
{
	if (!m_pGround)
		return;

	if (vecPosition.x >= m_pGround->m_vecOffset.x && vecPosition.x < (m_pGround->m_vecOffset.x + 128.0f) &&
		vecPosition.y >= m_pGround->m_vecOffset.y && vecPosition.y < (m_pGround->m_vecOffset.y + 128.0f))
	{
		m_pGround->SetColor(vecPosition, dwColor);
	}
	else if (m_pGround->m_pLeftGround 
		&& vecPosition.x >= m_pGround->m_pLeftGround->m_vecOffset.x
		&& vecPosition.x < (m_pGround->m_pLeftGround->m_vecOffset.x + 128.0f)
		&& vecPosition.y >= m_pGround->m_pLeftGround->m_vecOffset.y
		&& vecPosition.y < (m_pGround->m_pLeftGround->m_vecOffset.y + 128.0f))
	{
		m_pGround->m_pLeftGround->SetColor(vecPosition, dwColor);
	}
	else if (m_pGround->m_pRightGround
		&& vecPosition.x >= m_pGround->m_pRightGround->m_vecOffset.x
		&& vecPosition.x < (m_pGround->m_pRightGround->m_vecOffset.x + 128.0f)
		&& vecPosition.y >= m_pGround->m_pRightGround->m_vecOffset.y
		&& vecPosition.y < (m_pGround->m_pRightGround->m_vecOffset.y + 128.0f))
	{
		m_pGround->m_pRightGround->SetColor(vecPosition, dwColor);
	}
	else if (m_pGround->m_pUpGround
		&& vecPosition.x >= m_pGround->m_pUpGround->m_vecOffset.x
		&& vecPosition.x < (m_pGround->m_pUpGround->m_vecOffset.x + 128.0f)
		&& vecPosition.y >= m_pGround->m_pUpGround->m_vecOffset.y
		&& vecPosition.y < (m_pGround->m_pUpGround->m_vecOffset.y + 128.0f))
	{
		m_pGround->m_pUpGround->SetColor(vecPosition, dwColor);
	}
	else if (m_pGround->m_pDownGround
		&& vecPosition.x >= m_pGround->m_pDownGround->m_vecOffset.x
		&& vecPosition.x < (m_pGround->m_pDownGround->m_vecOffset.x + 128.0f)
		&& vecPosition.y >= m_pGround->m_pDownGround->m_vecOffset.y
		&& vecPosition.y < (m_pGround->m_pDownGround->m_vecOffset.y + 128.0f))
	{
		m_pGround->m_pDownGround->SetColor(vecPosition, dwColor);
	}
}

int TMScene::GroundIsInWater(TMVector2 vecPosition, float fHeight, float* pfWaterHeight)
{
	if (!m_pGround)
		return 0;

	if (vecPosition.x >= m_pGround->m_vecOffset.x && (float)(m_pGround->m_vecOffset.x + 128.0f) > vecPosition.x && 
		vecPosition.y >= m_pGround->m_vecOffset.y && (float)(m_pGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
		return m_pGround->IsInWater(vecPosition, fHeight, pfWaterHeight);
	}
	if (m_pGround->m_pLeftGround && 
		vecPosition.x >= m_pGround->m_pLeftGround->m_vecOffset.x && (float)(m_pGround->m_pLeftGround->m_vecOffset.x + 128.0f) > vecPosition.x && 
		vecPosition.y >= m_pGround->m_pLeftGround->m_vecOffset.y && (float)(m_pGround->m_pLeftGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
		return m_pGround->m_pLeftGround->IsInWater(vecPosition, fHeight, pfWaterHeight);
	}
	if (m_pGround->m_pRightGround
		&& vecPosition.x >= m_pGround->m_pRightGround->m_vecOffset.x && (float)(m_pGround->m_pRightGround->m_vecOffset.x + 128.0f) > vecPosition.x
		&& vecPosition.y >= m_pGround->m_pRightGround->m_vecOffset.y && (float)(m_pGround->m_pRightGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
		return m_pGround->m_pRightGround->IsInWater(vecPosition, fHeight, pfWaterHeight);
	}
	if (m_pGround->m_pUpGround
		&& vecPosition.x >= m_pGround->m_pUpGround->m_vecOffset.x && (float)(m_pGround->m_pUpGround->m_vecOffset.x + 128.0f) > vecPosition.x
		&& vecPosition.y >= m_pGround->m_pUpGround->m_vecOffset.y && (float)(m_pGround->m_pUpGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
		return m_pGround->m_pUpGround->IsInWater(vecPosition, fHeight, pfWaterHeight);
	}
	if (m_pGround->m_pDownGround
		&& vecPosition.x >= m_pGround->m_pDownGround->m_vecOffset.x && (float)(m_pGround->m_pDownGround->m_vecOffset.x + 128.0f) > vecPosition.x
		&& vecPosition.y >= m_pGround->m_pDownGround->m_vecOffset.y && (float)(m_pGround->m_pDownGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
		return m_pGround->m_pDownGround->IsInWater(vecPosition, fHeight, pfWaterHeight);
	}

	return 0;
}

int TMScene::GroundIsInWater2(TMVector2 vecPosition, float* pfWaterHeight)
{
	if (!m_pGround)
		return 0;

	if (vecPosition.x >= m_pGround->m_vecOffset.x && (float)(m_pGround->m_vecOffset.x + 128.0f) > vecPosition.x && 
		vecPosition.y >= m_pGround->m_vecOffset.y && (float)(m_pGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
		return m_pGround->IsInWater(vecPosition, (float)GroundGetMask(vecPosition) * 0.1f, pfWaterHeight);
	}
	if (m_pGround->m_pLeftGround && 
		vecPosition.x >= m_pGround->m_pLeftGround->m_vecOffset.x && (float)(m_pGround->m_pLeftGround->m_vecOffset.x + 128.0f) > vecPosition.x && 
		vecPosition.y >= m_pGround->m_pLeftGround->m_vecOffset.y && (float)(m_pGround->m_pLeftGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
		return m_pGround->m_pLeftGround->IsInWater(vecPosition, (float)GroundGetMask(vecPosition) * 0.1f, pfWaterHeight);
	}
	if (m_pGround->m_pRightGround && 
		vecPosition.x >= m_pGround->m_pRightGround->m_vecOffset.x && (float)(m_pGround->m_pRightGround->m_vecOffset.x + 128.0f) > vecPosition.x && 
		vecPosition.y >= m_pGround->m_pRightGround->m_vecOffset.y && (float)(m_pGround->m_pRightGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
		return m_pGround->m_pRightGround->IsInWater(vecPosition, (float)GroundGetMask(vecPosition) * 0.1f, pfWaterHeight);
	}
	if (m_pGround->m_pUpGround && 
		vecPosition.x >= m_pGround->m_pUpGround->m_vecOffset.x && (float)(m_pGround->m_pUpGround->m_vecOffset.x + 128.0f) > vecPosition.x && 
		vecPosition.y >= m_pGround->m_pUpGround->m_vecOffset.y && (float)(m_pGround->m_pUpGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
		return m_pGround->m_pUpGround->IsInWater(vecPosition, (float)GroundGetMask(vecPosition) * 0.1f, pfWaterHeight);
	}
	if (!m_pGround->m_pDownGround || 
		vecPosition.x < m_pGround->m_pDownGround->m_vecOffset.x || (float)(m_pGround->m_pDownGround->m_vecOffset.x + 128.0f) <= vecPosition.x || 
		vecPosition.y < m_pGround->m_pDownGround->m_vecOffset.y || (float)(m_pGround->m_pDownGround->m_vecOffset.y + 128.0f) <= vecPosition.y)
	{
		return 0;
	}

	return m_pGround->m_pDownGround->IsInWater(vecPosition, (float)GroundGetMask(vecPosition) * 0.1f, pfWaterHeight);
}

float TMScene::GroundGetWaterHeight(TMVector2 vecPosition, float* pfWaterHeight)
{
	if (!m_pGround)
		return -100.0f;

	if (vecPosition.x >= m_pGround->m_vecOffset.x && (float)(m_pGround->m_vecOffset.x + 128.0f) > vecPosition.x && 
		vecPosition.y >= m_pGround->m_vecOffset.y && (float)(m_pGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
		return m_pGround->GetWaterHeight(vecPosition, pfWaterHeight);
	}
	if (m_pGround->m_pLeftGround && 
		vecPosition.x >= m_pGround->m_pLeftGround->m_vecOffset.x && (float)(m_pGround->m_pLeftGround->m_vecOffset.x + 128.0f) > vecPosition.x && 
		vecPosition.y >= m_pGround->m_pLeftGround->m_vecOffset.y && (float)(m_pGround->m_pLeftGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
		return m_pGround->m_pLeftGround->GetWaterHeight(vecPosition, pfWaterHeight);
	}
	if (m_pGround->m_pRightGround && 
		vecPosition.x >= m_pGround->m_pRightGround->m_vecOffset.x && (float)(m_pGround->m_pRightGround->m_vecOffset.x + 128.0f) > vecPosition.x && 
		vecPosition.y >= m_pGround->m_pRightGround->m_vecOffset.y && (float)(m_pGround->m_pRightGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
		return m_pGround->m_pRightGround->GetWaterHeight(vecPosition, pfWaterHeight);
	}
	if (m_pGround->m_pUpGround && 
		vecPosition.x >= m_pGround->m_pUpGround->m_vecOffset.x && (float)(m_pGround->m_pUpGround->m_vecOffset.x + 128.0f) > vecPosition.x && 
		vecPosition.y >= m_pGround->m_pUpGround->m_vecOffset.y && (float)(m_pGround->m_pUpGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
		return m_pGround->m_pUpGround->GetWaterHeight(vecPosition, pfWaterHeight);
	}
	if (m_pGround->m_pDownGround && 
		vecPosition.x >= m_pGround->m_pDownGround->m_vecOffset.x && (float)(m_pGround->m_pDownGround->m_vecOffset.x + 128.0f) > vecPosition.x && 
		vecPosition.y >= m_pGround->m_pDownGround->m_vecOffset.y && (float)(m_pGround->m_pDownGround->m_vecOffset.y + 128.0f) > vecPosition.y)
	{
	    return m_pGround->m_pDownGround->GetWaterHeight(vecPosition, pfWaterHeight);
	}

	return -100.0f;
}

int TMScene::GetMask2(TMVector2 vecPosition)
{
	int nMaskX = (int)(vecPosition.x - (float)g_HeightPosX);
	int nMaskY = (int)(vecPosition.y - (float)g_HeightPosY);

	if (nMaskX >= 0 && nMaskY >= 0 && nMaskX < 256 && nMaskY < 256)
		return m_GateMapData[nMaskY][nMaskX];

	return -10000;
}

void TMScene::Warp()
{
	if (m_bCriticalError == 1)
		return;

	auto pFocusedObject = static_cast<TMObject*>(m_pMyHuman);

	if (pFocusedObject)
	{
		if (m_pGround)
			Warp2((int)(pFocusedObject->m_vecPosition.x / 128.0f), (int)(pFocusedObject->m_vecPosition.y / 128.0f));
	}
}

void TMScene::Warp2(int nZoneX, int nZoneY)
{
	if (m_bCriticalError == 1 || !m_pGround)
		return;

	m_bAutoRun = 0;
	if (m_eSceneType == ESCENE_TYPE::ESCENE_FIELD && static_cast<TMFieldScene*>(this)->m_pAutoRunBtn)
		static_cast<TMFieldScene*>(this)->m_pAutoRunBtn->SetSelected(m_bAutoRun);

	TMGround* pNeighbor = nullptr;
	if (m_pGround->m_pLeftGround)
		pNeighbor = m_pGround->m_pLeftGround;
	if (m_pGround->m_pRightGround)
		pNeighbor = m_pGround->m_pRightGround;
	if (m_pGround->m_pUpGround)
		pNeighbor = m_pGround->m_pUpGround;
	if (m_pGround->m_pDownGround)
		pNeighbor = m_pGround->m_pDownGround;

	if (!pNeighbor && 
		(nZoneX != m_pGround->m_vecOffsetIndex.x || nZoneY != m_pGround->m_vecOffsetIndex.y) || 
		pNeighbor && 
		(nZoneX != m_pGround->m_vecOffsetIndex.x && nZoneX != pNeighbor->m_vecOffsetIndex.x || 
		 nZoneY != m_pGround->m_vecOffsetIndex.y && nZoneY != pNeighbor->m_vecOffsetIndex.y))
	{
		char szMapPath[128]{};
		char szDataPath[128]{};
		sprintf(szMapPath, "env\\Field%02d%02d.trn", nZoneX, nZoneY);
		sprintf(szDataPath, "env\\Field%02d%02d.dat", nZoneX, nZoneY);

		TMGround* pGround = new TMGround();

		if (!pGround->LoadTileMap(szMapPath))
		{
			if (!m_bCriticalError)
				LogMsgCriticalError(10, 0, 0, 0, 0);

			m_bCriticalError = 1;
			return;
		}

		TMGround* pOldGround = m_pGround;
		m_pGround = pGround;

		for (int i = 0; i < 2; ++i)
		{
			SAFE_DELETE(m_pObjectContainerList[i]);
			SAFE_DELETE(m_pGroundList[i]);
		}

		g_HeightPosX = nZoneX << 7;
		g_HeightPosY = nZoneY << 7;

		m_nCurrentGroundIndex = 0;
		m_pGroundList[0] = m_pGround;

		m_pObjectContainerList[0] = new TMObjectContainer(m_pGround);

		if (!m_pObjectContainerList[0]->Load(szDataPath))
		{
			LOG_WRITELOG("DataFile Not Found : %s\r\n", szDataPath);
			if (!m_bCriticalError)
				LogMsgCriticalError(11, 0, 0, 0, 0);

			m_bCriticalError = 1;
			return;
		}

		memset(m_HeightMapData, 0, 4u);

		for (int nY = 0; nY < 128; ++nY)
			memcpy(m_HeightMapData[nY], m_pGround->m_pMaskData[nY], 128);

		m_pGround->SetMiniMapData();
		m_pGroundObjectContainer->AddChild(m_pObjectContainerList[0]);
		m_pGroundObjectContainer->AddChild(m_pGroundList[0]);

		BASE_ApplyAttribute((char*)m_HeightMapData, 256);

		memcpy(m_GateMapData, m_HeightMapData, sizeof(m_GateMapData));

		SaveHeightMap(szMapPath);
		m_nAdjustTime = 0;
		m_dwInitTime = g_pTimerManager->GetServerTime();
	}
	else if (pNeighbor && nZoneX == pNeighbor->m_vecOffsetIndex.x && nZoneY == pNeighbor->m_vecOffsetIndex.y)
	{
		m_pGround = pNeighbor;
		m_nCurrentGroundIndex = (m_nCurrentGroundIndex + 1) % 2;
		m_pGround->SetMiniMapData();
	}
	if (m_eSceneType == ESCENE_TYPE::ESCENE_FIELD)
	{
		auto pSoundManager = g_pSoundManager;
		if (pSoundManager)
		{
			auto pSoundData = pSoundManager->GetSoundData(6);
			if (pSoundData && pSoundData->IsSoundPlaying())
			{
				pSoundData->Stop();
			}
		}
		if (RenderDevice::m_bDungeon && RenderDevice::m_bDungeon != 3 && RenderDevice::m_bDungeon != 4)
		{
			g_nWeather = 0;
			static_cast<TMFieldScene*>(this)->m_pRain->m_bVisible = 0;
			static_cast<TMFieldScene*>(this)->m_pSnow->m_bVisible = 0;
			static_cast<TMFieldScene*>(this)->m_pSnow2->m_bVisible = 0;
			static_cast<TMFieldScene*>(this)->m_bQuater = 1;
			static_cast<TMFieldScene*>(this)->UpdateScoreUI(0);
			static_cast<TMFieldScene*>(this)->m_pMiniMapPanel->m_GCPanel.dwColor = 0x80FFFFFF;
		}
		else
		{
			if (RenderDevice::m_bDungeon == 3 || RenderDevice::m_bDungeon == 4)
			{
				static_cast<TMFieldScene*>(this)->m_pSnow->m_bVisible = 0;
				static_cast<TMFieldScene*>(this)->m_pSnow2->m_bVisible = 0;
			}

			static_cast<TMFieldScene*>(this)->SetWeather(g_nWeather);
			g_pObjectManager->m_pCamera->m_fHorizonAngle = 0.78539819f;
			static_cast<TMFieldScene*>(this)->m_pMiniMapPanel->m_GCPanel.dwColor = 0x80FFFFFF;
		}
	}
}

void TMScene::SaveHeightMap(char* szFileName)
{
	;
}

void TMScene::CameraAction()
{
	if (m_dwStartCamTime == 0)
		return;

	DWORD dwTick = (g_pTimerManager->GetServerTime() - m_dwStartCamTime) + 100;

	TMCamera* pCamera = g_pObjectManager->m_pCamera;

	pCamera->m_fSightLength = 11.0f;

	for (int i = 0; i < (m_nCameraLoop - 1); ++i)
	{
		if (m_stCameraTick[i].dwTick >= dwTick || m_stCameraTick[i + 1].dwTick <= dwTick)
			continue;

		float fRatio =
			(float)(dwTick - m_stCameraTick[i].dwTick) /
			(float)(m_stCameraTick[i + 1].dwTick - m_stCameraTick[i].dwTick);

		auto fHorizonAngle = ((1.0f - fRatio) * m_stCameraTick[i].fHorizonAngle) + (m_stCameraTick[i + 1].fHorizonAngle * fRatio);

		pCamera->m_fHorizonAngle = fHorizonAngle;
		pCamera->m_fBackHorizonAngle = fHorizonAngle;

		auto fVerticalAngle = ((1.0f - fRatio) * m_stCameraTick[i].fVerticalAngle) + (m_stCameraTick[i + 1].fVerticalAngle * fRatio);

		pCamera->m_fVerticalAngle = fVerticalAngle;
		pCamera->m_fBackVerticalAngle = fVerticalAngle;

		TMVector3 vecLoc1{ 0.0f, 0.0f, 0.0f };
		TMVector3 vecLoc2{ 0.0f, 0.0f, 0.0f };

		if (m_stCameraTick[i].sLocal == 1 && m_pMyHuman != nullptr)
		{
			vecLoc1.x = m_pMyHuman->m_vecPosition.x;
			vecLoc1.y = m_pMyHuman->m_fHeight;
			vecLoc1.z = m_pMyHuman->m_vecPosition.y;
		}

		if (m_stCameraTick[i + 1].sLocal == 1 && m_pMyHuman != nullptr)
		{
			vecLoc2.x = m_pMyHuman->m_vecPosition.x;
			vecLoc2.y = m_pMyHuman->m_fHeight;
			vecLoc2.z = m_pMyHuman->m_vecPosition.y;
		}

		pCamera->m_cameraPos.x = ((vecLoc1.x + m_stCameraTick[i].fX) * (1.0f - fRatio))
			+ ((vecLoc2.x + m_stCameraTick[i + 1].fX) * fRatio);

		pCamera->m_cameraPos.y = ((vecLoc1.y + m_stCameraTick[i].fY) * (1.0f - fRatio))
			+ ((vecLoc2.y + m_stCameraTick[i + 1].fY) * fRatio);

		pCamera->m_cameraPos.z = ((vecLoc1.z + m_stCameraTick[i].fZ) * (1.0f - fRatio))
			+ ((vecLoc2.z + m_stCameraTick[i + 1].fZ) * fRatio);

		return;
	}

	if (m_stCameraTick[m_nCameraLoop - 1].dwTick < dwTick)
	{
		pCamera->m_fHorizonAngle = m_stCameraTick[m_nCameraLoop - 1].fHorizonAngle;
		pCamera->m_fVerticalAngle = m_stCameraTick[m_nCameraLoop - 1].fVerticalAngle;

		TMVector3 vecLoc3{ 0.0f, 0.0f, 0.0f };

		if (m_pMyHuman && m_stCameraTick[m_nCameraLoop - 1].sLocal == 1)
		{
			vecLoc3.x = m_pMyHuman->m_vecPosition.x;
			vecLoc3.y = m_pMyHuman->m_fHeight;
			vecLoc3.z = m_pMyHuman->m_vecPosition.y;
		}

		pCamera->m_cameraPos.x = m_stCameraTick[m_nCameraLoop - 1].fX + vecLoc3.x;
		pCamera->m_cameraPos.y = m_stCameraTick[m_nCameraLoop - 1].fY + vecLoc3.y;
		pCamera->m_cameraPos.z = m_stCameraTick[m_nCameraLoop - 1].fZ + vecLoc3.z;
	}
}

void TMScene::ReadCameraPos(const char* szFileName)
{
	m_nCameraLoop = 0;

	memset(m_stCameraTick, 0, sizeof(m_stCameraTick));

	char szBinFileName[128]{};

	sprintf_s(szBinFileName, "%s.bin", szFileName);

	FILE* fpBin = nullptr;

	fopen_s(&fpBin, szBinFileName, "rb");

	fread(&m_nCameraLoop, 1, 4, fpBin);

	if (m_nCameraLoop > 1000)
		m_nCameraLoop = 1000;

	else if (m_nCameraLoop < 0)
		m_nCameraLoop = 0;

	fread(m_stCameraTick, 1, 28 * m_nCameraLoop, fpBin);
	fclose(fpBin);
}

int TMScene::LoadMsgText(SListBox* pListBox, const char* szFileName)
{
	FILE* fp{};

	fopen_s(&fp, szFileName, "rt");

	if (!fp)
		return 0;

	if (!pListBox)
		return 0;

	char szText[256]{};
	char szTemp[256]{};

	for (int i = 0; i < 100 && fgets(szTemp, 256, fp); ++i)
	{
		char szCol[7]{};

		strncpy(szCol, szTemp, 6);

		DWORD dwCol{};

		sscanf(szCol, "%x", &dwCol);

		char* szRet = strstr(szTemp, "\n");

		if (szRet)
			*szRet = 0;

		if (szTemp[6] == 32)
		{
			sprintf_s(szText, "%s", &szTemp[6]);
			
			pListBox->AddItem(new SListBoxItem(
				szText,
				dwCol | 0xFF000000,
				0.0f,
				0.0f,
				pListBox->m_nWidth,
				16.0f,
				0,
				0x77777777u,
				1u,
				0));
		}
	}

	if (pListBox->m_pScrollBar)
		pListBox->m_pScrollBar->SetCurrentPos(0);

	fclose(fp);
	return 1;
}

int TMScene::LoadMsgText2(SListBox* pListBox, const char* szFileName, int nStartLine, int nEndLine)
{
	FILE* fp{};

	fopen_s(&fp, szFileName, "rt");

	if (!fp)
		return 0;

	if (!pListBox)
		return 0;

	char szText[256]{};
	char szTemp[256]{};

	int nCount = 0;

	pListBox->Empty();

	for (int i = 0; i < 560 && fgets(szTemp, 256, fp); ++i)
	{
		char szCol[7]{};
		
		strncpy(szCol, szTemp, 6);

		DWORD dwCol{};

		sscanf(szCol, "%x", &dwCol);

		char* szRet = strstr(szTemp, "\n");

		if (szRet)
			*szRet = 0;

		if (szTemp[6] == 32 && i >= nStartLine && i <= nEndLine)
		{
			sprintf_s(szText, "%s", &szTemp[6]);

			pListBox->AddItem(new SListBoxItem(
				szText,
				dwCol | 0xFF000000,
				0.0f,
				0.0f,
				pListBox->m_nWidth,
				16.0f,
				0,
				0x77777777u,
				1u,
				0));

			if (++nCount > 100)
				break;
		}
	}

	if (pListBox->m_pScrollBar)
		pListBox->m_pScrollBar->SetCurrentPos(0);

	fclose(fp);
	return 1;
}

int TMScene::LoadMsgText3(SListBox* pListBox, const char* szFileName, int nLv, int ntrans)
{
	FILE* fp{};

	fopen_s(&fp, szFileName, "rt");

	if (!fp)
		return 0;

	if (!pListBox)
		return 0;

	char szText[256]{};
	char szTemp[256]{};

	int nLvLimit = 300;

	pListBox->Empty();

	for (int i = 0; i < 100 && fgets(szTemp, 256, fp); ++i)
	{
		char szCol[11]{};
		
		strncpy(szCol, szTemp, 10);

		DWORD dwCol{};

		sscanf_s(szCol, "%d %x", &nLvLimit, &dwCol);

		if (nLvLimit > nLv)
			dwCol = 0xFF777777;

		if (nLvLimit > 350 && ntrans < 6)
			dwCol = 0xFF777777;

		if (g_pCurrentScene)
		{
			if (m_pMyHuman->Is2stClass() == 2)
				dwCol = 0xFF777777;

			else if (nLvLimit > nLv)
				dwCol = 0xFF777777;
		}

		char* szRet = strstr(szTemp, "\n");

		if (szRet)
			*szRet = 0;

		if (szTemp[10] == 32)
		{
			sprintf(szText, "%s", &szTemp[10]);
			
			pListBox->AddItem(new SListBoxItem(
				szText,
				dwCol | 0xFF000000,
				0.0f,
				0.0f,
				pListBox->m_nWidth,
				16.0f,
				0,
				0x77777777u,
				1u,
				0));
		}
	}

	if (pListBox->m_pScrollBar)
		pListBox->m_pScrollBar->SetCurrentPos(0);

	fclose(fp);
	return 1;
}

unsigned int TMScene::LoadMsgText4(char* pStr, int dwStrSize, const char* szFileName, int nLv, int ntrans)
{
	FILE* fp{};

	fopen_s(&fp, szFileName, "rt");

	if (!fp)
		return 0;

	int nLvLimit = 300;
	DWORD dwCol = 0;

	char szTemp[256]{};

	for (int i = 0; i < 100 && fgets(szTemp, 256, fp); ++i)
	{
		char szCol[11]{};

		strncpy(szCol, szTemp, 10);

		sscanf_s(szCol, "%d %x", &nLvLimit, &dwCol);

		if (nLvLimit == nLv)
		{
			if (dwCol == 0xFFAAAA && ntrans >= 6)
			{
				dwCol = 0;
			}
			else if (nLvLimit <= 350 || ntrans >= 6)
			{
				char* szRet = strstr(szTemp, "\n");

				if (szRet)
					*szRet = 0;

				if (szTemp[10] == 32)
					sprintf_s(pStr, dwStrSize, "%s", &szTemp[10]);
			}
			else
			{
				dwCol = 0;
			}
			
			break;
		}
	}

	fclose(fp);

	return dwCol | 0xFF000000;
}

int TMScene::LoadMsgLevel(char* LevelQuest, const char* szFileName, char cType)
{
	FILE* fp{};

	fopen_s(&fp, szFileName, "rt");

	if (!fp)
		return 0;

	char szTemp[256]{};

	for (int i = 0; i < 100 && fgets(szTemp, 256, fp); ++i)
	{
		char szCol[11]{};

		strncpy(szCol, szTemp, 10);

		int nLvLimit{};
		DWORD dwCol{};

		sscanf_s(szCol, "%d %x", &nLvLimit, &dwCol);

		LevelQuest[nLvLimit - 1] = cType;
	}
	fclose(fp);
	return 1;
}

void TMScene::CheckPKNonePK(int nServerIndex)
{
	g_NonePKServer = 1;
	for (int i = 0; i < 2; ++i)
	{
		if (nServerIndex == g_pPKServerNum[i])
			g_NonePKServer = 0;
	}
	g_NonePKServer = 0;
}

void TMScene::LogMsgCriticalError(int Type, int ID, int nMesh, int X, int Y)
{
	MSG_MessageLog stLog{};
	stLog.Header.ID = m_pMyHuman->m_dwID;
	stLog.Header.Type = MSG_MessageLog_Opcode;

	if(Type == 10)
		sprintf(stLog.String, "00000000 , Load Tile Map Fail");
	else
		sprintf(stLog.String, "%08d , Critical Data Err Cl,%d,%d,%d,%d,%d, %d", ID,	nMesh, (int)m_pMyHuman->m_vecPosition.x, (int)m_pMyHuman->m_vecPosition.y,
			X,
			Y,
			Type);

	g_pSocketManager->SendOneMessage((char*)&stLog, sizeof(stLog));
}

void TMScene::DeleteOwnerAllContainer()
{
	m_pEffectContainer->DeleteOwner(nullptr);
	m_pShadeContainer->DeleteOwner(nullptr);
	m_pHumanContainer->DeleteOwner(nullptr);
	m_pItemContainer->DeleteOwner(nullptr);
	m_pExtraContainer->DeleteOwner(nullptr);
}
