#include "pch.h"
#include "TMFieldScene.h"
#include "TMGlobal.h"
#include "TMLog.h"
#include "dsutil.h"
#include "DirShow.h"
#include "SControlContainer.h"
#include "SGrid.h"
#include "Mission.h"
#include "MrItemMix.h"
#include "TMGround.h"
#include "TMHuman.h"
#include "TMObjectContainer.h"
#include "TMCamera.h"
#include "TMSun.h"
#include "TMSky.h"
#include "TMSnow.h"
#include "TMRain.h"
#include "TMSkinMesh.h"
#include "TMEffectMesh.h"
#include "TMEffectBillBoard2.h"
#include "TMEffectBillBoard.h"
#include "TMUtil.h"

RECT TMFieldScene::m_rectWarning[7] =
{
  { 2255, 1535, 2263, 1538 },
  { 150, 3788, 156, 3793 },
  { 150, 3711, 156, 3772 },
  { 154, 3773, 157, 3780 },
  { 1075, 1708, 1078, 1713 },
  { 1171, 4076, 1177, 4079 },
  { 2362, 4041, 2369, 4044 }
};

int TMFieldScene::m_bPK = 0;
unsigned short TMFieldScene::m_usProgress = 0;
unsigned int TMFieldScene::m_dwCargoID = 0;

TMFieldScene::TMFieldScene()
	: TMScene()
{
	g_nTempArray[1] = (int)g_pObjectManager->m_stMobData.MobName;
	g_nTempArray2[1] = (int)g_pObjectManager->m_stMobData.MobName;

	LOG_WRITELOG(">> New Field Scene\r\n");
	m_eSceneType = ESCENE_TYPE::ESCENE_FIELD;
	m_dwID = static_cast<unsigned int>(m_eSceneType);
	m_bInitGate = 1;

	g_bLastStop = 0;
	g_bCastleWar = 0;
	g_bCastleWar2 = 0;

	m_dwLastGuildNameCheckTime = 0;
	m_dwLastWolfSound = 0;
	m_nMySanc = 0;
	m_cResurrect = 0;
	m_dwDustTerm = 2000;
	m_cLastFlagLButtonUp = 1;
	m_dwInTownTime = 0;
	m_dwFieldTime = 0;
	m_dwLastMouseDownTime = 0;
	m_dwLastPappusTime = 0;
	m_dwLastDustTime = 0;
	m_dwLastRemain = 0;
	m_dwLastLogout = 0;
	m_dwLastSelServer = 0;
	m_dwLastTeleport = 0;
	m_dwLastTown = 0;
	m_dwLastResurrect = 0;
	m_dwLastRelo = 0;
	m_dwStartFlashTime = 0;
	m_dwOldAttackTime = 0;
	m_dwWeatherTime = 0;
	m_dwLastDeadTime = 0;
	m_nWTime = 0;
	m_dwKeyTime = 0;
	m_dwPGTTime = 0;
	m_dwGetItemTime = 0;
	m_dwUseItemTime = 0;
	m_dwNPCClickTime = 0;
	m_dwLastCheckTime = 0;
	m_dwLastSetTargetHuman = 0;
	m_dwRemainTime = 0;
	m_dwQuizStart = 0;
	m_nChatListSize = 0;
	m_nReqHP = 0;
	m_nReqMP = 0;
	m_nAutoSkillNum = 4;
	m_nLastAutoTradePos = -1;
	m_sDestType = -1;
	m_sDestPos = -1;
	m_dwLastMousePosTime = 0;
	m_nLastMousePosX = 0;
	m_nLastMousePosY = 0;
	m_bSandWind = 1;
	m_cLastTown = 0;
	m_cLastTeleport = 0;
	m_cLastRelo = 0;
	m_cLastWhisper = 0;
	m_cGuildOnOff = 1;
	m_bMoveing = 0;
	m_nDustCount = 0;
	m_pSysMsgList = 0;
	m_dwLastNightmareTime = 0;
	m_dwNightmareTime = 0;

	g_GameAuto = 0;

	m_dwAttackDelay = 0;
	m_dwLastWhisper = 0;

	memset(&m_stLastWhisper, 0, sizeof(m_stLastWhisper));
	memset(m_dwStartAffectTime, 0, sizeof(m_dwStartAffectTime));
	memset(&m_stAutoTrade, 0, sizeof(m_stAutoTrade));
	memset(&m_stUseItem, 0, sizeof(m_stUseItem));
	memset(&m_stCapsuleItem, 0, sizeof(m_stCapsuleItem));
	memset(&m_stPotalItem, 0, sizeof(m_stPotalItem));
	memset(m_szSummoner, 0, sizeof(m_szSummoner));
	memset(m_szSummoner2, 0, sizeof(m_szSummoner2));
	memset(m_pLottoNumber, 0, sizeof(m_pLottoNumber));

	m_bNumPad = 0;
	m_bMountDead = 0;
	m_pTarget1 = nullptr;
	m_pTarget2 = nullptr;
	m_pTargetBill = nullptr;
	m_pHelpMemo = nullptr;
	m_pHelpSummon = nullptr;
	m_pMyHuman = nullptr;
	m_pTargetItem = nullptr;
	m_pTargetHuman = nullptr;
	m_pAutoSkillPanel = nullptr;
	m_pPGTOver = nullptr;
	m_pTradePanel = nullptr;
	m_pLottoPanel = nullptr;
	m_pLottoCost = nullptr;
	m_pHellgateStore = nullptr;
	m_pHellStoreDesc = nullptr;
	m_pGridHellStore = nullptr;
	m_pGambleStore = nullptr;
	m_pQuestPanel = nullptr;
	m_pQuestQuitBtn = nullptr;
	m_pQuestMemo = nullptr;
	m_pCargoGrid = nullptr;
	m_pGridHelm = nullptr;
	m_pGridCoat = nullptr;
	m_pGridPants = nullptr;
	m_pGridGloves = nullptr;
	m_pGridBoots = nullptr;
	m_pGridRight = nullptr;
	m_pGridLeft = nullptr;
	m_pGridGuild = nullptr;
	m_pGridEvent = nullptr;
	m_pGridRing = nullptr;
	m_pGridNecklace = nullptr;
	m_pGridOrb = nullptr;
	m_pGridCabuncle = nullptr;
	m_pGridDRing = nullptr;
	m_pGridMantua = nullptr;
	m_pEventPanel = nullptr;
	m_dwLastAutoAttackTime = 0;
	m_nCoinMsgType = 0;
	m_dwOpID = 0;
	m_dwChatTime = 0;
	m_fFlashTerm = 2000.0f;
	m_dwLastCheckAutoMouse = 0;
	m_bLastMyAttr = 0;
	m_nLastPotal = -1;
	m_dwTID = 0;
	m_bWarning = 0;
	m_bQuater = 1;
	m_cWarClan = -1;
	m_cAutoAttack = 0;
	g_pDevice->m_bFog = 1;

	TMFieldScene::m_bPK = 0;

	m_bShowNameLabel = 1;
	m_cWhisper = 0;
	m_cPartyChat = 0;
	m_cGuildChat = 0;
	m_bTab = 0;

	TMFieldScene::m_dwCargoID = 0;

	m_dwHellStoreID = 0;
	m_nHellStoreValue = 0;
	m_nFireWorkCellX = -1;
	m_nFireWorkCellY = -1;
	m_nTotoNum = 0;

	memset(&m_stToto, 0, sizeof(m_stToto));

	m_sDay = 0;

	memset(m_dwLastChatTime, 0, sizeof(m_dwLastChatTime));
	memset(m_pGridAutoTrade, 0, sizeof(m_pGridAutoTrade));
	memset(m_pGridItemMix, 0, sizeof(m_pGridItemMix));
	memset(m_pGridMixResult, 0, sizeof(m_pGridMixResult));

	m_pChatList = nullptr;
	m_pChatPanel = nullptr;
	m_pPositionText = nullptr;
	m_pFadePanel = nullptr;
	m_pEditChat = nullptr;
	m_pInputBG2 = nullptr;
	m_pInvenPanel = nullptr;
	m_pAutoTrade = nullptr;
	m_pItemMixPanel = nullptr;
	m_pItemMixPanel4 = nullptr;
	m_pSystemPanel = nullptr;
	m_pPGTPanel = nullptr;
	m_pInputGoldPanel = nullptr;
	m_pCPanel = nullptr;
	m_pSkillPanel = nullptr;
	m_pKingDomFlag = nullptr;
	m_pFlagDesc = nullptr;
	m_pFlagDescText[0] = nullptr;
	m_pFlagDescText[1] = nullptr;
	m_pFlagDescText[2] = nullptr;
	m_pRankTimeText = nullptr;
	m_pRemainText = nullptr;
	m_nLastTime = 0;
	m_dwStartRankTime = 0;
	m_pMsgPanel = nullptr;
	m_pMsgList = nullptr;
	m_pMsgText = nullptr;
	m_nVillage = -1;
	m_pQuizPanel = nullptr;
	m_pQuizCaption = nullptr;

	memset(m_pQuizText, 0, sizeof(m_pQuizText));
	m_pQuizBG = 0;
	m_pQuizQuestion = 0;
	memset(m_pQuizButton, 0, sizeof(m_pQuizButton));

	m_pQuestBtn = 0;
	m_pAutoRunBtn = 0;
	m_pHelpBtn = 0;
	m_pMGameAutoBtn = 0;
	m_pSGameAutoBtn = 0;
	m_pAutoTarget = 0;
	m_pCCPotionBtn = 0;
	m_pCCFeedBtn = 0;
	m_AutoStartPointX = 0;
	m_AutoStartPointY = 0;
	m_AutoPostionUse = 2;
	m_AutoHpMp = 1;
	m_pSetType = 0;
	m_pHelpPanel = 0;
	m_pHelpText = 0;

	memset(m_pHelpButton, 0, sizeof(m_pHelpButton));
	memset(m_pHelpList, 0, sizeof(m_pHelpList));

	m_pFireWorkPanel = 0;
	memset(m_pFireWorkButton, 0, sizeof(m_pFireWorkButton));
	m_pFireWorkOKButton = 0;
	m_pFireWorkQuitButton = 0;

	m_pTotoPanel = 0;
	m_pTotoSelect_Btn = 0;
	m_pTotoBuy_Btn = 0;
	m_pTotoQuit_Btn = 0;
	m_pTotoNumber_Edit = 0;
	m_pTotoTime_Txt = 0;
	m_pTotoTeamA_Txt = 0;
	m_pTotoTeamB_Txt = 0;
	m_pTotoScoreA_Edit = 0;
	m_pTotoScoreB_Edit = 0;

	memset(m_szAutoCaption, 0, sizeof(m_szAutoCaption));
	memset(m_szAutoClass, 0, sizeof(m_szAutoClass));
	memset(m_szAutoFolder, 0, sizeof(m_szAutoFolder));
	memset(m_szAutoFolder2, 0, sizeof(m_szAutoFolder2));
	memset(m_szAutoProcess, 0, sizeof(m_szAutoProcess));

	m_szAutoFolder[0] = 107;
	m_szAutoFolder[1] = 48;
	m_szAutoFolder[2] = 101;
	m_szAutoFolder[3] = 48;
	m_szAutoFolder[4] = 98;
	m_szAutoFolder[5] = 48;
	m_szAutoFolder[6] = 105;
	m_szAutoFolder[7] = 48;
	m_szAutoFolder[8] = 97;
	m_szAutoFolder[9] = 48;
	m_szAutoFolder[10] = 117;
	m_szAutoFolder[11] = 116;
	m_szAutoFolder[12] = 111;
	m_szAutoFolder[13] = 92;
	m_szAutoFolder[14] = 107;
	m_szAutoFolder[15] = 101;
	m_szAutoFolder[16] = 98;
	m_szAutoFolder[17] = 105;
	m_szAutoFolder[18] = 97;
	m_szAutoFolder[19] = 117;
	m_szAutoFolder[20] = 116;
	m_szAutoFolder[21] = 111;
	m_szAutoFolder[22] = 46;
	m_szAutoFolder[23] = 101;
	m_szAutoFolder[24] = 120;
	m_szAutoFolder[25] = 101;
	m_szAutoFolder2[0] = 65;
	m_szAutoFolder2[1] = 99;
	m_szAutoFolder2[2] = 116;
	m_szAutoFolder2[3] = 105;
	m_szAutoFolder2[4] = 118;
	m_szAutoFolder2[5] = 101;
	m_szAutoFolder2[6] = 74;
	m_szAutoFolder2[7] = 111;
	m_szAutoFolder2[8] = 121;
	m_szAutoFolder2[9] = 46;
	m_szAutoFolder2[10] = 111;
	m_szAutoFolder2[11] = 99;
	m_szAutoFolder2[12] = 120;

	memset(m_pQuestButton, 0, sizeof(m_pQuestButton));
	memset(m_pQuestList, 0, sizeof(m_pQuestList));
	memset(m_pQuestContentList, 0, sizeof(m_pQuestContentList));

	m_pPartyPanel = 0;
	m_pBtnPGTParty = 0;
	m_pBtnPGTGuild = 0;
	m_pBtnPGTTrade = 0;
	m_pBtnPGTChallenge = 0;
	m_pBtnPGT1_V_1 = 0;
	m_pBtnPGT5_V_5 = 0;
	m_pBtnPGT10_V_10 = 0;
	m_pBtnPGTAll_V_All = 0;
	m_pBtnPGTGuildDrop = 0;
	m_pBtnPGTGuildWar = 0;
	m_pBtnPGTGuildAlly = 0;
	m_pBtnPGTGuildInvite = 0;
	m_pBtnPGTGICommon = 0;
	m_pBtnPGTGIChief1 = 0;
	m_pBtnPGTGIChief2 = 0;
	m_pBtnPGTGIChief3 = 0;
	m_pHPBar = 0;
	m_pMPBar = 0;
	m_pMHPBar = 0;
	m_pMHPBarT = 0;
	m_pCurrentHPText = 0;
	m_pMaxHPText = 0;
	m_pCurrentMPText = 0;
	m_pMaxMPText = 0;
	m_pCurrentMHPText = 0;
	m_pMaxMHPText = 0;
	m_pInfoText = 0;

	memset(m_szLastAttackerName, 0, sizeof(m_szLastAttackerName));

	for (int i = 0; i < 12; ++i)
	{
		float fAngle = (((float)i * 3.1415927f) * 2.0f) / 12.0f;
		m_vecKnifePos[i] = TMVector2(cosf(fAngle) * 10.0f, sinf(fAngle) * 10.0f);
	}
	for (int i = 0; i < 24; ++i)
		m_pSkillSecGrid[i] = 0;
	for (int i = 0; i < 12; ++i)
		m_pSkillSecGrid2[i] = 0;

	m_pGridSkillBelt = 0;
	m_pGridSkillBelt2 = 0;
	m_pGridSkillBelt3 = 0;
	m_pShortSkillTglBtn1 = 0;
	m_pShortSkillTglBtn2 = 0;
	g_pGBPanel = 0;
	m_nCameraLoop = 0;

	TMFieldScene::m_usProgress = 0;

	m_nYear = 0;
	m_nDays = 0;
	m_nBet = 1000;
	m_dwEventTime = 0;
	m_dwLastClbuttonTime = 0;
	m_bClbutton = 0;
	m_dwKhepraID = 0;

	memset(&m_stRemoveServer, 0, sizeof(m_stRemoveServer));

	m_nServerMove = 0;
	m_pPotalPanel = 0;
	m_pPotalList = 0;
	m_pPotalText = 0;
	g_nTempArray[2] = (int)m_bShowNameLabel + 28;
	g_nTempArray2[2] = (int)m_bShowNameLabel + 28;
	g_pObjectManager->m_cSelectShortSkill = 0;

	m_pKhepraPortal = 0;
	m_pKhepraPortalEff1 = 0;
	m_pKhepraPortalEff2 = 0;
	m_dwKhepraDieTime = 0;
	m_nKhepraDieFlag = 0;
	m_nQuest12MaxMobs = 0;
	m_pQuestRemainTime = 0;
	m_nCameraMode = 0;
	m_bCantAttk = 0;
	m_dwCantMoveTime = 0;
	m_bTeleportMsg = 0;
	m_dwLastSecProcessTime = 0;
	m_nGuildMarkCount = 0;
	m_hInternetSession = 0;
	m_dwLastGetGuildmarkTime = 0;
	m_bIsDungeon = 0;
	m_nMouseRDownX = 0;
	m_nMouseRDownY = 0;
	m_dwDeleteURLTime = 0;
	m_bAirMove = 0;
	m_nOldMountSkinMeshType = -1;
	m_nAirMove_State = 0;
	m_dwAirMove_TickTime = 0;
	m_bAirMove_Wing = 0;
	m_vecAirMove_Dest.x = 0.0;
	m_vecAirMove_Dest.y = 0.0;
	m_fAirMove_Speed = 0.6f;
	m_bAirmove_ShowUI = 0;
	m_nAirMove_Index = 0;
	m_nAirMove_RouteIndex = 0;
	m_eOldMotion = ECHAR_MOTION::ECMOTION_NONE;
	m_pPotalText1 = 0;
	m_pPotalText2 = 0;
	m_pPotalText3 = 0;

	for (int i = 0; i < 32; ++i)
	{
		m_pAffectIcon[i] = 0;
		m_pTargetAffectIcon[i] = 0;
		m_dwAffectBlinkTime[i] = 0;
	}

	for (int i = 0; i < 13; ++i)
	{
		for (int j = 0; j < 32; ++j)
			m_pPartyAffectIcon[i][j] = 0;
	}

	m_pPartyAffectText = 0;
	m_pPartyAutoButton = 0;
	m_pPartyAutoText = 0;
	m_bAutoParty = 0;
	m_pDailyQuestButton = 0;
	m_pAffectDesc = 0;
	m_pChatGeneral_C = 0;
	m_pChatParty_C = 0;
	m_pChatWhisper_C = 0;
	m_pChatGuild_C = 0;
	m_pMiniBtn = 0;
	m_pMiniPanel = 0;
	m_pMainInfo2 = 0;
	m_pShortSkillPanel = 0;
	m_pMainInfo1 = 0;
	m_pMainInfo1_BG = 0;
	m_nIsMP = 0;
	m_bShowExp = 0;
	m_bTempCastlewar = 0;

	for (int i = 0; i < 4; ++i)
		m_bJPNBag[i] = 0;

	strcpy(m_cChatType, "");
	strcpy(m_cChatSelect, "");
	strcpy(m_cWhisperName, "");

	m_bShowBoss = 0;
	m_Coin = 0;
	m_bIsUndoShoplist = 0;
	m_sShopTarget = 0;
	m_bEventCouponClick = 0;
	m_bEventCouponOpen = 0;
}

TMFieldScene::~TMFieldScene()
{
	g_nTempArray[1] = 0;
	g_nTempArray[2] = 0;

	if (g_bActiveWB == 1)
	{
		g_pApp->RenderScene();
		g_pApp->SwitchWebBrowserState(0);
	}

	if (m_pHelpList[3])
	{
		memset(g_pObjectManager->m_stMemo, 0, sizeof(g_pObjectManager->m_stMemo));
		for (int i = 0; i < m_pHelpList[3]->m_nNumItem; ++i)
		{
			g_pObjectManager->m_stMemo[i].dwColor = m_pHelpList[3]->m_pItemList[i]->m_GCText.dwColor;
			sprintf(g_pObjectManager->m_stMemo[i].szString, "%s", m_pHelpList[3]->m_pItemList[i]->m_GCText.strString);
		}
	}

	g_pDevice->m_nWidthShift = 0;

	auto pSoundManager = g_pSoundManager;
	if (pSoundManager)
	{
		auto pSoundData = pSoundManager->GetSoundData(107);
		if (pSoundData && pSoundData->IsSoundPlaying())
			pSoundData->Stop();

		pSoundData = pSoundManager->GetSoundData(6);
		if (pSoundData && pSoundData->IsSoundPlaying())
			pSoundData->Stop();
	}

	if (g_pCurrentScene
		&& g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_SELECT_SERVER
		&& g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_FIELD
		&& g_pCurrentScene->m_eSceneType != ESCENE_TYPE::ESCENE_DEMO
		&& g_pApp->m_pBGMManager)
	{
		g_pApp->m_pBGMManager->StopBGM();
	}

	if (m_pMyHuman)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (!strcmp(m_pMyHuman->m_szName, g_pObjectManager->m_stSelCharData.MobName[j]))
			{
				g_pObjectManager->m_stSelCharData.Exp[j] = g_pObjectManager->m_stMobData.Exp;
				break;
			}
		}
	}
}

void SetMinimapPos()
{
	// TODO
}

int TMFieldScene::InitializeScene()
{
	LOG_WRITELOG(">> Init Field Scene::Start\r\n");
	LoadRC("UI\\FieldScene2.txt");
	g_pDevice->m_nHeightShift = 0;

	m_pQuizBG = new SPanel(-9, BASE_ScreenResize(275.0f) / 2.0f, 100.0f, 525.0f, 54.0f, 0x44FFFFFF, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);
	if (m_pQuizBG)
	{
		m_pQuizBG->SetControlID(896);
		m_pQuizBG->m_bSelectEnable = 0;
		m_pControlContainer->AddItem(m_pQuizBG);

		float fScale = (float)g_pDevice->m_dwScreenHeight * 0.016f;
		m_pQuizBG->SetPos((float)g_pDevice->m_dwScreenWidth * 0.5f - m_pQuizBG->m_nWidth * 0.5f, fScale);
	}

	m_pQuizQuestion = new SText(-2, "Question", 0xFFFFFFFF, 5.0f, 104.0f, 510.0f, 16.0f, 0, 0x77777777, 1, 0);
	if (m_pQuizQuestion)
		m_pQuizBG->AddChild(m_pQuizQuestion);

	m_pQuizButton[0] = new SButton(-2, 5.0f, 128.0f, 125.0f, 20.0f, 0x77777777, 1, (char*)"Answer1");

	if (m_pQuizButton[0])
	{
		m_pQuizButton[0]->SetControlID(897);
		if (m_pControlContainer)
			m_pQuizButton[0]->SetEventListener(m_pControlContainer);
		else
			m_pQuizButton[0]->SetEventListener(nullptr);

		m_pQuizBG->AddChild(m_pQuizButton[0]);
	}

	m_pQuizButton[1] = new SButton(-2, 135.0f, 128.0f, 125.0f, 20.0f, 0x77777777, 1, (char*)"Answer2");
	if (m_pQuizButton[1])
	{
		m_pQuizButton[1]->SetControlID(898);
		if (m_pControlContainer)
			m_pQuizButton[1]->SetEventListener(m_pControlContainer);
		else
			m_pQuizButton[1]->SetEventListener(nullptr);

		m_pQuizBG->AddChild(m_pQuizButton[1]);
	}

	m_pQuizButton[2] = new SButton(-2, 265.0f, 128.0f, 125.0f, 20.0f, 0x77777777, 1, (char*)"Answer3");
	if (m_pQuizButton[2])
	{
		m_pQuizButton[2]->SetControlID(899);
		if (m_pControlContainer)
			m_pQuizButton[2]->SetEventListener(m_pControlContainer);
		else
			m_pQuizButton[2]->SetEventListener(nullptr);

		m_pQuizBG->AddChild(m_pQuizButton[2]);
	}

	m_pQuizButton[3] = new SButton(-2, 395.0f, 128.0f, 125.f, 20.0f, 0x77777777, 1, (char*)"Answer4");
	if (m_pQuizButton[3])
	{
		m_pQuizButton[3]->SetControlID(900);
		if (m_pControlContainer)
			m_pQuizButton[3]->SetEventListener(m_pControlContainer);
		else
			m_pQuizButton[3]->SetEventListener(nullptr);

		m_pQuizBG->AddChild(m_pQuizButton[3]);
	}

	if (m_pQuizBG)
		m_pQuizBG->SetVisible(0);

	m_pChatList = (SListBox*)m_pControlContainer->FindControl(65667);
	m_pChatListnotice = (SListBox*)m_pControlContainer->FindControl(65944);
	m_pChatBack = (SPanel*)m_pControlContainer->FindControl(65943);
	m_pChatGeneral = (SButton*)m_pControlContainer->FindControl(65677);
	m_pChatParty = (SButton*)m_pControlContainer->FindControl(65678);
	m_pChatWhisper = (SButton*)m_pControlContainer->FindControl(65679);
	m_pChatGuild = (SButton*)m_pControlContainer->FindControl(65680);
	m_pChatGeneral_C = (SButton*)m_pControlContainer->FindControl(65673);
	m_pChatParty_C = (SButton*)m_pControlContainer->FindControl(65674);
	m_pChatWhisper_C = (SButton*)m_pControlContainer->FindControl(65675);
	m_pChatGuild_C = (SButton*)m_pControlContainer->FindControl(65676);
	m_pKingdomText = (SText*)m_pControlContainer->FindControl(131072);
	m_pKingDomGuild = (SButton*)m_pControlContainer->FindControl(131074);
	m_pKingDomGuild_C = (SButton*)m_pControlContainer->FindControl(131073);
	m_pQuestBtn = (SButton*)m_pControlContainer->FindControl(65793);
	m_pHelpBtn = (SButton*)m_pControlContainer->FindControl(65795);
	m_pccmode = (SPanel*)m_pControlContainer->FindControl(66817);

	m_pccmode->SetVisible(0);
	m_pccmode->SetVisible(1);

	m_pGridCharFace = (SPanel*)m_pControlContainer->FindControl(69636);
	m_pKingDomGuild_C->m_bSelected = 1;
	m_pKingDomGuild_C->SetVisible(0);
	m_pChatGeneral_C->m_bSelected = 0;
	m_pChatParty_C->m_bSelected = 0;
	m_pChatWhisper_C->m_bSelected = 0;
	m_pChatGuild_C->m_bSelected = 0;
	m_pChatGeneral->m_bSelected = 1;
	m_pChatParty->m_bSelected = 1;
	m_pChatWhisper->m_bSelected = 1;
	m_pChatGuild->m_bSelected = 1;
	m_pKingDomGuild->m_bSelected = 0;
	m_pChatList->m_pScrollBar->SetVisible(1);
	m_pChatListnotice->m_nPosX = 490.0f * RenderDevice::m_fWidthRatio;
	m_pChatListnotice->m_nPosX = 440.0f * RenderDevice::m_fHeightRatio;
	m_pChatListnotice->m_pScrollBar->SetVisible(0);

	m_pAutoRunBtn = (SButton*)m_pControlContainer->FindControl(316);
	m_pSysMsgList = (SListBox*)m_pControlContainer->FindControl(5695);
	m_PkButton = (SButton*)m_pControlContainer->FindControl(65786);

	m_PkButton->SetSelected(TMFieldScene::m_bPK == 0);
	m_pPGTText = (SText*)m_pControlContainer->FindControl(645);

	char szStr[128]{};
	sprintf(szStr, " %s", g_pMessageStringTable[157]);

	m_pAutoSkillPanel = (SPanel*)m_pControlContainer->FindControl(65648);
	m_pAutoSkillPanelChild[0] = (SPanel*)m_pControlContainer->FindControl(65775);
	m_pAutoSkillPanelChild[1] = (SPanel*)m_pControlContainer->FindControl(65776);
	m_pAutoSkillPanelChild[2] = (SPanel*)m_pControlContainer->FindControl(65777);
	m_pAutoSkillPanelChild[3] = (SPanel*)m_pControlContainer->FindControl(65778);
	m_pAutoSkillPanelChild[4] = (SPanel*)m_pControlContainer->FindControl(65779);
	m_pAutoSkillPanelChild[5] = (SPanel*)m_pControlContainer->FindControl(65780);
	m_pAutoSkillPanelChild[6] = (SPanel*)m_pControlContainer->FindControl(65781);
	m_pAutoSkillPanelChild[7] = (SPanel*)m_pControlContainer->FindControl(65782);
	m_pAutoSkillPanelChild[8] = (SPanel*)m_pControlContainer->FindControl(65783);
	m_pAutoSkillPanelChild[9] = (SPanel*)m_pControlContainer->FindControl(65784);

	if (m_pAutoSkillPanel)
		m_pAutoSkillPanel->SetVisible(0);

	SetAutoSkillNum(m_nAutoSkillNum);

	memset(&g_pObjectManager->m_stTrade, 0, sizeof(g_pObjectManager->m_stTrade));
	memset(&g_pObjectManager->m_stCombineItem, 0, sizeof(g_pObjectManager->m_stCombineItem));
	memset(&g_pObjectManager->m_stCombineItem4, 0, sizeof(g_pObjectManager->m_stCombineItem4));
	g_pObjectManager->m_stCombineItem.Header.ID = g_pObjectManager->m_dwCharID;
	g_pObjectManager->m_stCombineItem.Header.Type = 0x3A6;
	g_pObjectManager->m_stCombineItem4.Header.ID = g_pObjectManager->m_dwCharID;
	g_pObjectManager->m_stCombineItem4.Header.Type = 0x3C0;

	for (int i = 0; i < 15; ++i)
		g_pObjectManager->m_stTrade.CarryPos[i] = -1;
	for (int i = 0; i < 8; ++i)
	{
		g_pObjectManager->m_stCombineItem.CarryPos[i] = -1;
		g_pObjectManager->m_stCombineItem4.CarryPos[i] = -1;
	}

	m_pPositionText = (SText*)m_pControlContainer->FindControl(771);
	if (m_pPositionText)
		m_pPositionText->SetVisible(0);

	m_pFadePanel = (SPanel*)m_pControlContainer->FindControl(65566);
	if (m_pFadePanel)
		m_pFadePanel->m_bSelectEnable = 0;

	SPanel* pUnderBGPanel = (SPanel*)m_pControlContainer->FindControl(625);
	if (pUnderBGPanel)
		pUnderBGPanel->m_bSelectEnable = 0;

	m_pEditChat = (SEditableText*)m_pControlContainer->FindControl(65671);
	m_pInputBG2 = (SPanel*)m_pControlContainer->FindControl(574);

	if (m_pInputBG2)
		m_pInputBG2->SetVisible(0);
	if (m_pEditChat)
		m_pEditChat->SetVisible(1);

	m_pEditChat = (SEditableText*)m_pControlContainer->FindControl(65671);
	m_pInputBG2 = (SPanel*)m_pControlContainer->FindControl(574);

	if (m_pInputBG2)
		m_pInputBG2->SetVisible(0);
	if (m_pEditChat)
		m_pEditChat->SetVisible(1);

	memset(m_dwSkillLastTime, 0, sizeof(m_dwSkillLastTime));

	m_sWhisperIndex = 0;
	m_sChatIndex = 0;

	memset(m_szLastChatList, 0, sizeof(m_szLastChatList));
	memset(m_szWhisperList, 0, sizeof(m_szWhisperList));

	m_pFadePanel->SetSize((float)g_pDevice->m_dwScreenWidth, (float)g_pDevice->m_dwScreenHeight);

	m_pKingDomFlag = (SPanel*)m_pControlContainer->FindControl(65768);
	if (m_pKingDomFlag)
		m_pKingDomFlag->SetVisible(0);

	m_pFlagDesc = (SPanel*)m_pControlContainer->FindControl(65771);
	if (m_pFlagDesc)
		m_pFlagDesc->SetVisible(0);

	m_pFlagDescText[0] = (SText*)m_pControlContainer->FindControl(65772);
	m_pFlagDescText[1] = (SText*)m_pControlContainer->FindControl(65773);
	m_pFlagDescText[2] = (SText*)m_pControlContainer->FindControl(65774);

	m_pKingDomFlag->m_pDescPanel = m_pFlagDesc;

	m_pRankTimeText = new SText(-2,
		"00 : 00",
		0xFF00FF00,
		(((float)g_pDevice->m_dwScreenWidth / RenderDevice::m_fWidthRatio) / 2.0f) - 42.0f,
		30.0f,
		200.0f,
		16.0f,
		0,
		0x77777777,
		1,
		0);

	if (m_pRankTimeText)
	{
		m_pRankTimeText->m_Font.m_fSize = 2.0f;
		m_pRankTimeText->SetVisible(0);
		m_bRankTimeOn = 0;
	}

	char szTempLeft[128]{};
	sprintf(szTempLeft, "%s 100", g_pMessageStringTable[230]);

	m_pRemainText = new SText(-2,
		szTempLeft,
		0xFFFFAA00,
		((float)g_pDevice->m_dwScreenWidth / RenderDevice::m_fWidthRatio) - 210.0f,
		30.0f,
		100.0f,
		16.0f,
		0,
		0x77777777,
		1,
		0);

	if (m_pRemainText)
	{
		m_pRemainText->m_Font.m_fSize = 2.0f;
		m_pRemainText->SetVisible(0);
	}

	m_pQuestRemainTime = new SText(-2,
		"",
		0xDDFFFF33,
		(float)((float)g_pDevice->m_dwScreenWidth / RenderDevice::m_fWidthRatio) - 140.0f,
		5.0f * RenderDevice::m_fHeightRatio,
		100.0f,
		16.0f,
		0,
		0x77777777,
		1,
		0);

	if (m_pQuestRemainTime)
	{
		m_pQuestRemainTime->m_Font.m_fSize = 1.0f;
		m_pQuestRemainTime->SetVisible(1);
	}

	if (m_pRankTimeText)
		m_pControlContainer->AddItem(m_pRankTimeText);
	if (m_pRemainText)
		m_pControlContainer->AddItem(m_pRemainText);
	if (m_pQuestRemainTime)
		m_pControlContainer->AddItem(m_pQuestRemainTime);

	m_pRankTimeText->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - 50.0f, 
		(3.0f * RenderDevice::m_fHeightRatio) + 55.0f);

	m_pRemainText->SetPos((float)g_pDevice->m_dwScreenWidth - 200.0f,
		30.0f * RenderDevice::m_fHeightRatio);

	if (g_pDevice->m_dwScreenWidth < 800)
	{
		m_pQuestRemainTime->SetPos((float)g_pDevice->m_dwScreenWidth + 35.0f,
			5.0f * RenderDevice::m_fHeightRatio);
	}
	else
	{
		m_pQuestRemainTime->SetPos(276.0f * RenderDevice::m_fWidthRatio,
			525.0f * RenderDevice::m_fHeightRatio);
	}

	m_pMoney1 = (SText*)m_pControlContainer->FindControl(65564u);
	m_pMoney4 = (SText*)m_pControlContainer->FindControl(94221u);
	m_pSkBonus = (SText*)m_pControlContainer->FindControl(65600u);
	m_pCHP = (SText*)m_pControlContainer->FindControl(65614u);
	m_pCMP = (SText*)m_pControlContainer->FindControl(65616u);
	m_pExpLamp[0] = (SPanel*)m_pControlContainer->FindControl(65637u);
	m_pExpLamp[1] = (SPanel*)m_pControlContainer->FindControl(65638u);
	m_pExpLamp[2] = (SPanel*)m_pControlContainer->FindControl(65639u);
	m_pExpProgress[0] = (SProgressBar*)m_pControlContainer->FindControl(65655u);
	m_pExpProgress[1] = (SProgressBar*)m_pControlContainer->FindControl(65656u);
	m_pExpProgress[2] = (SProgressBar*)m_pControlContainer->FindControl(65657u);
	m_pExpProgress[3] = (SProgressBar*)m_pControlContainer->FindControl(65658u);
	m_pExpProgress[4] = (SProgressBar*)m_pControlContainer->FindControl(65659u);
	m_pExpProgress[5] = (SProgressBar*)m_pControlContainer->FindControl(65660u);
	m_pExpProgress[6] = (SProgressBar*)m_pControlContainer->FindControl(65661u);
	m_pExpProgress[7] = (SProgressBar*)m_pControlContainer->FindControl(65662u);
	m_pExpProgress[8] = (SProgressBar*)m_pControlContainer->FindControl(65663u);
	m_pExpProgress[9] = (SProgressBar*)m_pControlContainer->FindControl(65664u);
	m_pCCModeHpSte = (SText*)m_pControlContainer->FindControl(66823u);
	m_pCCModeMountSte = (SText*)m_pControlContainer->FindControl(66824u);

	char chtmp[128]{};
	sprintf(chtmp, "%d", g_GameAuto_hpValue);
	m_pCCModeHpSte->SetText(chtmp, 0);
	sprintf(chtmp, "%d", g_GameAuto_mountValue);
	m_pCCModeMountSte->SetText(chtmp, 0);

	m_pCIName = (SText*)m_pControlContainer->FindControl(65703u);
	m_pCIClass = (SText*)m_pControlContainer->FindControl(65707u);
	m_pCIClass2 = (SText*)m_pControlContainer->FindControl(65708u);
	m_pCIHP = (SText*)m_pControlContainer->FindControl(65729u);
	m_pCIMP = (SText*)m_pControlContainer->FindControl(65731u);
	m_pCIEXP = (SText*)m_pControlContainer->FindControl(65710u);
	m_pCIEXPE = (SText*)m_pControlContainer->FindControl(65711u);
	m_pCLevel = (SText*)m_pControlContainer->FindControl(65713u);
	m_pScBonus = (SText*)m_pControlContainer->FindControl(65727u);
	m_pCIStr = (SText*)m_pControlContainer->FindControl(65715u);
	m_pCIInt = (SText*)m_pControlContainer->FindControl(65718u);
	m_pCIDex = (SText*)m_pControlContainer->FindControl(65721u);
	m_pCICon = (SText*)m_pControlContainer->FindControl(65724u);
	m_pCIFakeExp = (SText*)m_pControlContainer->FindControl(65767u);
	m_pCISpecial1 = (SText*)m_pControlContainer->FindControl(65753u);
	m_pCISpecial2 = (SText*)m_pControlContainer->FindControl(65756u);
	m_pCISpecial3 = (SText*)m_pControlContainer->FindControl(65759u);
	m_pCISpecial4 = (SText*)m_pControlContainer->FindControl(65762u);
	m_pSpBonus = (SText*)m_pControlContainer->FindControl(65765u);
	m_pMoney2 = (SText*)m_pControlContainer->FindControl(1041u);
	m_pMoney3 = (SText*)m_pControlContainer->FindControl(6408u);

	for (int i = 0; i < 24; ++i)
		m_pSkillSecGrid[i] = (SGridControl*)m_pControlContainer->FindControl(i + 65574);

	for (int i = 0; i < 12; ++i)
		m_pSkillSecGrid2[i] = (SGridControl*)m_pControlContainer->FindControl(i + 94208);

	m_pDamage = (SText*)m_pControlContainer->FindControl(65733u);
	m_pSkillDam = (SText*)m_pControlContainer->FindControl(65735u);
	m_pSpeed = (SText*)m_pControlContainer->FindControl(65737u);
	m_pDefence = (SText*)m_pControlContainer->FindControl(65739u);
	m_pAttackSpeed = (SText*)m_pControlContainer->FindControl(65741u);
	m_pCritical = (SText*)m_pControlContainer->FindControl(65743u);
	m_pRegist1 = (SText*)m_pControlContainer->FindControl(65745u);
	m_pRegist2 = (SText*)m_pControlContainer->FindControl(65747u);
	m_pRegist3 = (SText*)m_pControlContainer->FindControl(65749u);
	m_pRegist4 = (SText*)m_pControlContainer->FindControl(65751u);
	m_pSLPanel1 = (SPanel*)m_pControlContainer->FindControl(1923u);
	m_pSLPanel2 = (SPanel*)m_pControlContainer->FindControl(1924u);
	m_pSLPanel3 = (SPanel*)m_pControlContainer->FindControl(1925u);
	m_pSkillCover = (SPanel*)m_pControlContainer->FindControl(1157u);
	m_pMainInfo1 = (SPanel*)m_pControlContainer->FindControl(65628u);
	m_pMainInfo1_BG = (SPanel*)m_pControlContainer->FindControl(65641u);

	m_pMainInfo1_BG->SetPos(((float)g_pDevice->m_dwScreenWidth - m_pMainInfo1_BG->m_nWidth) / 2.0f,
		m_pMainInfo1_BG->m_nPosX);

	m_pMainInfo1->SetStickLeft();
	m_pMainInfo1->SetStickBottom();

	SPanel* pChatPanel = (SPanel*)m_pControlContainer->FindControl(65672);
	m_pChatPanel = (SPanel*)m_pControlContainer->FindControl(65672);
	m_pChatList->m_nPosX = BASE_ScreenResize(10.0f);
	m_pChatList->m_nPosY = (pChatPanel->m_nPosY - m_pChatList->m_nHeight) - BASE_ScreenResize(10.0f);

	m_pChatBack->m_nPosX = BASE_ScreenResize(10.0f);
	m_pChatBack->m_nPosY = m_pChatList->m_nPosY - BASE_ScreenResize(10.0f);

	m_pChatBack->SetSize(BASE_ScreenResize(10.0f) + m_pChatList->m_nWidth,
		BASE_ScreenResize(20.0f) + m_pChatList->m_nHeight);
	m_pChatList->SetSize(m_pChatList->m_nWidth,
		(float)(140 * m_nChatListSize + 60) * RenderDevice::m_fHeightRatio);
	m_pChatBack->SetSize(BASE_ScreenResize(10.0f) + m_pChatList->m_nWidth,
		m_pChatList->m_nHeight);
	m_pChatList->m_pScrollBar->SetSize(m_pChatList->m_pScrollBar->m_nWidth,
		(float)(140 * m_nChatListSize + 60) * RenderDevice::m_fHeightRatio);
	m_pChatList->m_pScrollBar->m_pBackground1->SetSize(m_pChatList->m_pScrollBar->m_nWidth,
		(float)(140 * m_nChatListSize + 60) * RenderDevice::m_fHeightRatio);
	m_pChatList->SetPos(m_pChatList->m_nPosX, (float)(pChatPanel->m_nPosY - m_pChatList->m_nHeight) - 4.0f);
	m_pChatBack->SetPos(m_pChatList->m_nPosX, (float)(pChatPanel->m_nPosY - m_pChatList->m_nHeight) - 4.0f);

	m_pChatSelectPanel = (SPanel*)m_pControlContainer->FindControl(90113);
	m_pChatListPanel = (SPanel*)m_pControlContainer->FindControl(90128);
	m_pChatType = (SButton*)m_pControlContainer->FindControl(90114);

	SButton* Button = (SButton*)m_pControlContainer->FindControl(90129);
	m_pChatType->SetText(Button->m_GCPanel.strString);
	m_pChatListPanel->SetVisible(0);
	m_pChatSelectPanel->SetVisible(0);
	m_pChatList->m_pScrollBar->m_pBackground1->SetVisible(0);
	m_pChatListnotice->SetVisible(1);
	m_pMainInfo2 = (SPanel*)m_pControlContainer->FindControl(65610);

	if (m_pMainInfo2)
	{
		m_pMainInfo2->SetAutoSize();
		m_pMainInfo2->SetStickLeft();
		m_pMainInfo2->SetStickTop();
		m_pMainInfo2_Name = (SText*)m_pControlContainer->FindControl(65611);
		m_pMainInfo2->SetVisible(0);
	}

	m_pMainInfo2_Lv = (SText*)m_pControlContainer->FindControl(65613);
	m_pEditChatPanel = (SPanel*)m_pControlContainer->FindControl(65670);

	if (m_pEditChatPanel)
	{
		m_pEditChatPanel->m_nPosY = m_pControlContainer->FindControl(65672)->m_nWidth - (float)(2.0f * RenderDevice::m_fHeightRatio);
		m_pEditChatPanel->m_nPosX = m_pChatSelectPanel->m_nPosX	+ m_pChatSelectPanel->m_nWidth;

		if (g_nKeyType != 1)
			g_nKeyType = 0;
		if (!g_nKeyType)
			m_pEditChatPanel->SetVisible(0);

		m_pChatPanel->SetVisible(1);
	}

	m_pMiniBtn = (SButton*)m_pControlContainer->FindControl(65787);
	m_pMiniPanel = (SPanel*)m_pControlContainer->FindControl(65788);

	if (m_pMiniPanel)
		m_pMiniPanel->SetVisible(0);

	m_pShortSkillPanel = (SPanel*)m_pControlContainer->FindControl(65642);
	m_pShortSkill_Txt = (SText*)m_pControlContainer->FindControl(65643);
	m_pCISp1Caption = (SText*)m_pControlContainer->FindControl(65755);
	m_pCISp2Caption = (SText*)m_pControlContainer->FindControl(65758);
	m_pCISp3Caption = (SText*)m_pControlContainer->FindControl(65761);
	m_pCISp4Caption = (SText*)m_pControlContainer->FindControl(65764);
	m_pCIGuild = (SText*)m_pControlContainer->FindControl(65705);
	m_pSkillSec1 = (SText*)m_pControlContainer->FindControl(65570);
	m_pSkillSec2 = (SText*)m_pControlContainer->FindControl(65571);
	m_pSkillSec3 = (SText*)m_pControlContainer->FindControl(65572);
	m_pSkillMSec1 = (SText*)m_pControlContainer->FindControl(65604);
	m_pSkillMSec2 = (SText*)m_pControlContainer->FindControl(65605);
	m_pSkillMSec3 = (SText*)m_pControlContainer->FindControl(65606);

	for (int id = 0; id < 32; ++id)
	{
		m_pAffectL[id] = (SText*)m_pControlContainer->FindControl(id + 1328);
		m_pAffect[id] = (SText*)m_pControlContainer->FindControl(id + 90432);
	}

	m_pCargoCoin = (SText*)m_pControlContainer->FindControl(65689);
	m_pMyCargoCoin = (SText*)m_pControlContainer->FindControl(812);

	SText* pMyGold = (SText*)m_pControlContainer->FindControl(619);
	SText* pOPGold = (SText*)m_pControlContainer->FindControl(603);
	pMyGold->m_cComma = 2;
	pOPGold->m_cComma = 2;
	pMyGold->SetText((char*)"         0", 0);
	pOPGold->SetText((char*)"         0", 0);
	m_pInvenPanel = (SPanel*)m_pControlContainer->FindControl(589832);

	SPanel* pPanel1 = (SPanel*)m_pControlContainer->FindControl(65565);

	m_pInvenPanel->SetPos(RenderDevice::m_fWidthRatio * 514.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	if (m_pInvenPanel)
	{
		m_pInvenPanel->SetVisible(0);
		pPanel1->m_bSelectEnable = 0;
	}

	m_pAutoTrade = (SPanel*)m_pControlContainer->FindControl(646);

	if (m_pAutoTrade)
	{
		m_pAutoTrade->SetVisible(0);
		for (int k = 0; k < 10; ++k)
		{
			m_pGridAutoTrade[k] = (SGridControl*)m_pControlContainer->FindControl(k + 653);
			if (m_pGridAutoTrade[k])
				m_pGridAutoTrade[k]->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
		}

		m_pAutoTrade->SetPos(RenderDevice::m_fWidthRatio * 254.0f,
			RenderDevice::m_fHeightRatio * 35.0f);
	}

	m_pItemMixPanel4 = (SPanel*)m_pControlContainer->FindControl(6432);
	m_pMix4Desc = (SListBox*)m_pControlContainer->FindControl(6439);
	m_pItemMixPanel = (SPanel*)m_pControlContainer->FindControl(65857);

	m_ItemMixClass.Read_MixListFile();
	m_ItemMixClass.TakeItResource(m_pControlContainer, g_pObjectManager->m_dwCharID);
	m_MissionClass.TakeItResource(m_pControlContainer, g_pObjectManager->m_dwCharID);

	if (m_pItemMixPanel4)
		m_pItemMixPanel4->SetPos(RenderDevice::m_fWidthRatio * 287.0f,
			RenderDevice::m_fHeightRatio * 35.0f);

	if(m_pItemMixPanel)
		m_pItemMixPanel->SetPos(RenderDevice::m_fWidthRatio * 287.0f,
			RenderDevice::m_fHeightRatio * 35.0f);

	if (m_pMix4Desc)
		LoadMsgText(m_pMix4Desc, (char*)"UI\\mix4desc.txt");

	if (m_pItemMixPanel)
	{
		m_pItemMixPanel->SetVisible(0);
		for (int l = 0; l < 8; ++l)
		{
			m_pGridItemMix[l] = (SGridControl*)m_pControlContainer->FindControl(l + 65861);
			if (m_pGridItemMix[l])
				m_pGridItemMix[l]->m_eGridType = TMEGRIDTYPE::GRID_ITEMMIX;
		}
	}

	if (m_pItemMixPanel4)
	{
		m_pItemMixPanel4->SetVisible(0);
		for (int m = 0; m < 3; ++m)
		{
			m_pGridItemMix4[m] = (SGridControl*)m_pControlContainer->FindControl(m + 6436);
			if (m_pGridItemMix4[m])
				m_pGridItemMix4[m]->m_eGridType = TMEGRIDTYPE::GRID_ITEMMIX4;
		}
	}

	m_pHellgateStore = (SPanel*)m_pControlContainer->FindControl(6185);
	m_pHellStoreDesc = (SListBox*)m_pControlContainer->FindControl(6201);
	m_pGridHellStore = (SGridControl*)m_pControlContainer->FindControl(6208);
	m_pGridHellStore->m_bDrawGrid = 0;
	m_pGridHellStore->m_eGridType = TMEGRIDTYPE::GRID_SHOP;

	if (m_pHellgateStore)
		m_pHellgateStore->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pHellgateStore->m_nWidth * 0.5f),
			((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pHellgateStore->m_nHeight * 0.5f));

	if (m_pHellgateStore)
		m_pHellgateStore->SetVisible(0);

	m_pGambleStore = (SPanel*)m_pControlContainer->FindControl(6400);
	if (m_pGambleStore)
		m_pGambleStore->SetVisible(0);

	m_pDescPanel = m_pControlContainer->FindControl(258);
	m_pDescPanel->m_bSelectEnable = 0;
	m_pDescPanel->SetVisible(0);
	m_pDescNameText = (SText*)m_pControlContainer->FindControl(772);
	m_pParamText[0] = (SText*)m_pControlContainer->FindControl(773);
	m_pParamText[1] = (SText*)m_pControlContainer->FindControl(774);
	m_pParamText[2] = (SText*)m_pControlContainer->FindControl(775);
	m_pParamText[3] = (SText*)m_pControlContainer->FindControl(776);
	m_pParamText[4] = (SText*)m_pControlContainer->FindControl(777);
	m_pParamText[5] = (SText*)m_pControlContainer->FindControl(784);
	m_pParamText[6] = (SText*)m_pControlContainer->FindControl(794);
	m_pParamText[7] = (SText*)m_pControlContainer->FindControl(795);
	m_pParamText[8] = (SText*)m_pControlContainer->FindControl(796);
	m_pParamText[9] = (SText*)m_pControlContainer->FindControl(797);
	m_pParamText[10] = (SText*)m_pControlContainer->FindControl(798);
	m_pParamText[11] = (SText*)m_pControlContainer->FindControl(799);
	m_pParamText[12] = (SText*)m_pControlContainer->FindControl(800);
	m_pParamText[13] = (SText*)m_pControlContainer->FindControl(801);
	m_pSystemPanel = (SPanel*)m_pControlContainer->FindControl(65879);

	if (m_pSystemPanel)
	{
		m_pSystemPanel->SetVisible(0);
		m_pSystemPanel->m_bModal = 1;
		m_pControlContainer->m_pModalControl[1] = m_pSystemPanel;
	}
	m_pPGTPanel = (SPanel*)m_pControlContainer->FindControl(640);
	if (m_pPGTPanel)
	{
		m_pPGTPanel->SetVisible(0);
		m_pPGTPanel->m_bModal = 1;
		m_pControlContainer->m_pModalControl[2] = m_pPGTPanel;
	}
	m_pInputGoldPanel = (SPanel*)m_pControlContainer->FindControl(65885);
	if (m_pInputGoldPanel)
	{
		m_pInputGoldPanel->SetVisible(0);
		m_pInputGoldPanel->m_bModal = 1;
		m_pControlContainer->m_pModalControl[3] = m_pInputGoldPanel;
	}

	m_pBtnGuildOnOff = (SButton*)m_pControlContainer->FindControl(299);
	m_pBtnMountRun = (SButton*)m_pControlContainer->FindControl(298);
	m_pBtnPGTParty = (SButton*)m_pControlContainer->FindControl(641);
	m_pBtnPGTGuild = (SButton*)m_pControlContainer->FindControl(642);
	m_pBtnPGTTrade = (SButton*)m_pControlContainer->FindControl(643);
	m_pBtnPGTChallenge = (SButton*)m_pControlContainer->FindControl(620);
	m_pBtnPGT1_V_1 = (SButton*)m_pControlContainer->FindControl(639);
	m_pBtnPGT5_V_5 = (SButton*)m_pControlContainer->FindControl(621);
	m_pBtnPGT10_V_10 = (SButton*)m_pControlContainer->FindControl(622);
	m_pBtnPGTAll_V_All = (SButton*)m_pControlContainer->FindControl(623);
	m_pBtnPGTGuildDrop = (SButton*)m_pControlContainer->FindControl(816);
	m_pBtnPGTGuildWar = (SButton*)m_pControlContainer->FindControl(817);
	m_pBtnPGTGuildAlly = (SButton*)m_pControlContainer->FindControl(862);
	m_pBtnPGTGuildInvite = (SButton*)m_pControlContainer->FindControl(863);
	m_pBtnPGTGICommon = (SButton*)m_pControlContainer->FindControl(912);
	m_pBtnPGTGIChief1 = (SButton*)m_pControlContainer->FindControl(913);
	m_pBtnPGTGIChief2 = (SButton*)m_pControlContainer->FindControl(914);
	m_pBtnPGTGIChief3 = (SButton*)m_pControlContainer->FindControl(915);
	SControl* pServer = m_pControlContainer->FindControl(65880);
	SControl* pChar = m_pControlContainer->FindControl(65881);
	SControl* pQuit = m_pControlContainer->FindControl(65882);
	SControl* pCancel = m_pControlContainer->FindControl(5883);
	m_pCPanel = (SPanel*)m_pControlContainer->FindControl(65696);

	SPanel* pCPanel1 = (SPanel*)m_pControlContainer->FindControl(65770);
	m_pCPanel->SetPos(RenderDevice::m_fWidthRatio * 60.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	m_pSystemPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pSystemPanel->m_nWidth * 0.5f),
		((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pSystemPanel->m_nHeight * 0.5f));

	m_pPGTPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pPGTPanel->m_nWidth * 0.5f),
		((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pPGTPanel->m_nHeight * 0.5f));

	m_pInputGoldPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pInputGoldPanel->m_nWidth * 0.5f),
		((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pInputGoldPanel->m_nHeight * 0.5f));

	if (m_pCPanel)
	{
		m_pCPanel->SetVisible(0);
		pCPanel1->m_bSelectEnable = 0;
	}

	m_pShopPanel = (SPanel*)m_pControlContainer->FindControl(65692);

	SPanel *pShopPanel1 = (SPanel*)m_pControlContainer->FindControl(65695);

	m_pShopPanel->SetPos(RenderDevice::m_fWidthRatio * 287.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	if (m_pShopPanel)
	{
		m_pShopPanel->SetVisible(0);
		pShopPanel1->m_bSelectEnable = 0;
	}
	m_pCargoPanel = (SPanel*)m_pControlContainer->FindControl(65686);
	m_pCargoPanel1 = (SPanel*)m_pControlContainer->FindControl(65692);

	SPanel* pCargoPanel1 = (SPanel*)m_pControlContainer->FindControl(65691);
	m_pCargoPanel->SetPos(RenderDevice::m_fWidthRatio * 287.0f,
		RenderDevice::m_fHeightRatio * 35.0f);
	m_pCargoPanel1->SetPos(RenderDevice::m_fWidthRatio * 287.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	if (m_pCargoPanel)
	{
		m_pCargoPanel->SetVisible(0);
		m_pCargoPanel1->SetVisible(0);
		pCargoPanel1->m_bSelectEnable = 0;
	}

	SPanel* pTradePanel = (SPanel*)m_pControlContainer->FindControl(576);
	SPanel* pTradePanel1 = (SPanel*)m_pControlContainer->FindControl(577);

	pTradePanel->SetPos(RenderDevice::m_fWidthRatio * 287.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	m_pTradePanel = pTradePanel;

	if (pTradePanel)
	{
		pTradePanel->SetVisible(0);
		pTradePanel1->m_bSelectEnable = 0;
	}

	m_pLottoPanel = (SPanel*)m_pControlContainer->FindControl(2048);

	if (m_pLottoPanel)
	{
		m_pLottoPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - ((m_pLottoPanel->m_nWidth + 40.0f) * 0.5f),
			((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pLottoPanel->m_nHeight * 0.5f));

		m_pLottoCost = (SText*)m_pControlContainer->FindControl(2051);
		for (int nLotto = 0; nLotto < 6; ++nLotto)
			m_pLottoNumber[nLotto] = (SText*)m_pControlContainer->FindControl(nLotto + 2053);

		m_pLottoPanel->m_bPickable = 1;
		m_pLottoPanel->m_bSelectEnable = 1;
		m_pLottoPanel->SetVisible(0);
	}

	m_pSkillMPanel = (SPanel*)m_pControlContainer->FindControl(65602);
	SPanel* pSkillMPanel1 = (SPanel*)m_pControlContainer->FindControl(65609);
	m_pSkillMDesc = (SListBox*)m_pControlContainer->FindControl(65608);

	m_pSkillMPanel->SetPos(RenderDevice::m_fWidthRatio * 60.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	if (m_pSkillMPanel)
	{
		m_pSkillMPanel->SetVisible(0);
		pSkillMPanel1->m_bSelectEnable = 0;
	}

	m_pSkillPanel = (SPanel*)m_pControlContainer->FindControl(65567);

	SPanel* pSkillPanel1 = (SPanel*)m_pControlContainer->FindControl(65601);
	SText* pSkillBonus = (SText*)m_pControlContainer->FindControl(65600);

	m_pSkillPanel->SetPos(RenderDevice::m_fWidthRatio * 514.0f,
		RenderDevice::m_fHeightRatio * 35.0f);

	SPanel* pSkillTitlePanel = (SPanel*)m_pControlContainer->FindControl(1912);
	SPanel* pSkillGridPanel = (SPanel*)m_pControlContainer->FindControl(1910);
	SPanel* pSkillGridPanel2 = (SPanel*)m_pControlContainer->FindControl(1911);
	if (m_pSkillPanel)
	{
		m_pSkillPanel->SetVisible(0);
		if (pSkillTitlePanel)
			pSkillTitlePanel->m_bSelectEnable = 0;
		if (pSkillGridPanel)
			pSkillGridPanel->m_bSelectEnable = 0;
		if (pSkillGridPanel2)
			pSkillGridPanel2->m_bSelectEnable = 0;
		pSkillBonus->m_bSelectEnable = 0;
		pSkillPanel1->m_bSelectEnable = 0;
	}

	m_pInvPageBtn1 = (SButton*)m_pControlContainer->FindControl(67076);
	m_pInvPageBtn2 = (SButton*)m_pControlContainer->FindControl(67077);
	m_pInvPageBtn3 = (SButton*)m_pControlContainer->FindControl(67078);
	m_pInvPageBtn4 = (SButton*)m_pControlContainer->FindControl(67079);
	m_pJPNBag_Day1 = (SText*)m_pControlContainer->FindControl(77834);
	m_pJPNBag_Day2 = (SText*)m_pControlContainer->FindControl(77835);
	m_pStorePageBtn1 = (SButton*)m_pControlContainer->FindControl(67332);
	m_pStorePageBtn2 = (SButton*)m_pControlContainer->FindControl(67333);
	m_pStorePageBtn3 = (SButton*)m_pControlContainer->FindControl(67334);
	m_pMGameAutoBtn = (SButton*)m_pControlContainer->FindControl(66818);
	m_pSetType = (SButton*)m_pControlContainer->FindControl(66821);
	m_pHPBar = (SProgressBar*)m_pControlContainer->FindControl(65621);
	m_pMPBar = (SProgressBar*)m_pControlContainer->FindControl(65623);
	m_pMHPBar = (SProgressBar*)m_pControlContainer->FindControl(65625);
	m_pMHPBarT = (SProgressBar*)m_pControlContainer->FindControl(65626);
	m_pMainCharName = (SText*)m_pControlContainer->FindControl(69635);
	m_pCurrentHPText = (SText*)m_pControlContainer->FindControl(65614);
	m_pMaxHPText = (SText*)m_pControlContainer->FindControl(65615);
	m_pCurrentMPText = (SText*)m_pControlContainer->FindControl(65616);
	m_pMaxMPText = (SText*)m_pControlContainer->FindControl(65617);
	m_pCurrentMHPText = (SText*)m_pControlContainer->FindControl(65618);
	m_pMaxMHPText = (SText*)m_pControlContainer->FindControl(65619);
	m_pExpHold = (SPanel*)m_pControlContainer->FindControl(65636);
	m_pInfoText = (SText*)m_pControlContainer->FindControl(770);

	if (m_pExpHold)
		m_pExpHold->SetVisible(0);
	m_pQuizPanel = (SPanel*)m_pControlContainer->FindControl(880);
	m_pQuizText[0] = (SText*)m_pControlContainer->FindControl(881);
	m_pQuizText[1] = (SText*)m_pControlContainer->FindControl(882);
	m_pQuizText[2] = (SText*)m_pControlContainer->FindControl(883);
	m_pQuizText[3] = (SText*)m_pControlContainer->FindControl(884);

	if (m_pQuizPanel)
		m_pQuizPanel->m_bSelectEnable = 0;
	if (m_pQuizPanel)
		m_pQuizPanel->SetVisible(0);

	m_pQuizCaption = (SText*)m_pControlContainer->FindControl(6108);

	m_pQuizPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pQuizPanel->m_nWidth * 0.5f),
		((float)g_pDevice->m_dwScreenHeight * 0.5f) - (200.0f * RenderDevice::m_fHeightRatio));

	m_pEventText = (SText*)m_pControlContainer->FindControl(65669);
	m_pEventPanel = (SPanel*)m_pControlContainer->FindControl(65668);

	m_pEventText->SetPos(300.0f, 300.0f);

	m_dwEventStartTime = g_pTimerManager->GetServerTime();
	m_nCurrEventTextIndex = 0;

	memset(m_szEventTextTemp, 0, sizeof(m_szEventTextTemp));

	STRUCT_MOB* pMobData = &g_pObjectManager->m_stMobData;
	int nTownX = (int)g_pObjectManager->m_stMobData.HomeTownX >> 7;
	int nTownY = (int)g_pObjectManager->m_stMobData.HomeTownY >> 7;
	char szMapPath[128]{};
	char szDataPath[128]{};
	sprintf(szMapPath, "env\\Field%02d%02d.trn", nTownX, nTownY);
	sprintf(szDataPath, "env\\Field%02d%02d.dat", nTownX, nTownY);

	m_pGroundList[0] = new TMGround();
	if (!m_pGroundList[0]->LoadTileMap(szMapPath))
	{
		if (!m_bCriticalError)
			LogMsgCriticalError(2, 0, 0, 0, 0);

		m_bCriticalError = 1;
	}

	m_pGround = m_pGroundList[0];
	m_pGround->SetMiniMapData();

	m_pObjectContainerList[0] = new TMObjectContainer(m_pGround);

	if (m_pObjectContainerList[0])
		m_pGroundObjectContainer->AddChild(m_pObjectContainerList[0]);

	SetMinimapPos();

	m_pMyHuman = new TMHuman(this);
	if (m_pMyHuman)
		m_pMyHuman->m_dwID = g_pObjectManager->m_dwCharID;

	m_pMyHuman->m_nTotalKill = ((unsigned char)pMobData->MobName[15] << 8) + (unsigned char)pMobData->MobName[14];
	m_pMyHuman->m_nCurrentKill = m_pMyHuman->m_nTotalKill;
	m_pMyHuman->m_ucChaosLevel = pMobData->MobName[12];
	pMobData->MobName[12] = 0;
	pMobData->MobName[15] = 0;

	sprintf(m_pMyHuman->m_szName, "%s", pMobData->MobName);

	m_pMyHuman->SetPacketMOBItem(pMobData);
	m_pMyHuman->SetSpeed(m_bMountDead);
	if (m_pMyHuman->m_cMount == 1 && 
		(m_pMyHuman->m_nMountSkinMeshType == 31 || m_pMyHuman->m_nMountSkinMeshType == 40 || m_pMyHuman->m_nMountSkinMeshType == 20 && 
		 m_pMyHuman->m_stMountLook.Mesh0 != 7 || m_pMyHuman->m_nMountSkinMeshType == 39))
	{
		m_pMyHuman->m_fMaxSpeed = 3.0f;
	}

	unsigned short usGuild = g_pObjectManager->m_stSelCharData.Guild[g_pObjectManager->m_cCharacterSlot];
	m_pMyHuman->m_sGuildLevel = (unsigned char)pMobData->GuildLevel;
	m_pMyHuman->m_usGuild = usGuild;

	SGridControl* pGridTradeOp1 = (SGridControl*)m_pControlContainer->FindControl(8192);
	SGridControl* pGridTradeOp2 = (SGridControl*)m_pControlContainer->FindControl(8193);
	SGridControl* pGridTradeOp3 = (SGridControl*)m_pControlContainer->FindControl(8194);
	SGridControl* pGridTradeOp4 = (SGridControl*)m_pControlContainer->FindControl(8195);
	SGridControl* pGridTradeOp5 = (SGridControl*)m_pControlContainer->FindControl(8196);
	SGridControl* pGridTradeOp6 = (SGridControl*)m_pControlContainer->FindControl(8197);
	SGridControl* pGridTradeOp7 = (SGridControl*)m_pControlContainer->FindControl(8198);
	SGridControl* pGridTradeOp8 = (SGridControl*)m_pControlContainer->FindControl(8199);
	SGridControl* pGridTradeOp9 = (SGridControl*)m_pControlContainer->FindControl(8200);
	SGridControl* pGridTradeOp10 = (SGridControl*)m_pControlContainer->FindControl(8201);

	pGridTradeOp1->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp2->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp3->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp4->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp5->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp6->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp7->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp8->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp9->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;
	pGridTradeOp10->m_eGridType = TMEGRIDTYPE::GRID_TRADEOP;

	SGridControl* pGridTradeMy1 = (SGridControl*)m_pControlContainer->FindControl(8448);
	SGridControl* pGridTradeMy2 = (SGridControl*)m_pControlContainer->FindControl(8449);
	SGridControl* pGridTradeMy3 = (SGridControl*)m_pControlContainer->FindControl(8450);
	SGridControl* pGridTradeMy4 = (SGridControl*)m_pControlContainer->FindControl(8451);
	SGridControl* pGridTradeMy5 = (SGridControl*)m_pControlContainer->FindControl(8452);
	SGridControl* pGridTradeMy6 = (SGridControl*)m_pControlContainer->FindControl(8453);
	SGridControl* pGridTradeMy7 = (SGridControl*)m_pControlContainer->FindControl(8454);
	SGridControl* pGridTradeMy8 = (SGridControl*)m_pControlContainer->FindControl(8455);
	SGridControl* pGridTradeMy9 = (SGridControl*)m_pControlContainer->FindControl(8456);
	SGridControl* pGridTradeMy10 = (SGridControl*)m_pControlContainer->FindControl(8457);

	pGridTradeMy1->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy2->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy3->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy4->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy5->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy6->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy7->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy8->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy9->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;
	pGridTradeMy10->m_eGridType = TMEGRIDTYPE::GRID_TRADEMY;

	SControl* pOpCheckButton = m_pControlContainer->FindControl(601);
	SControl* pMyCheckButton = m_pControlContainer->FindControl(617);

	m_pCargoGridList[0] = (SGridControl*)m_pControlContainer->FindControl(67328);
	m_pCargoGridList[1] = (SGridControl*)m_pControlContainer->FindControl(67329);
	m_pCargoGridList[2] = (SGridControl*)m_pControlContainer->FindControl(67330);
	m_pCargoGrid = m_pCargoGridList[0];
	m_pCargoGridList[0]->SetVisible(0);
	m_pCargoGridList[1]->SetVisible(0);
	m_pCargoGridList[2]->SetVisible(0);
	m_pCargoGrid->SetVisible(1);
	m_pCargoGridList[0]->m_bDrawGrid = 1;
	m_pCargoGridList[0]->m_eGridType = TMEGRIDTYPE::GRID_CARGO;
	m_pCargoGridList[1]->m_bDrawGrid = 1;
	m_pCargoGridList[1]->m_eGridType = TMEGRIDTYPE::GRID_CARGO;
	m_pCargoGridList[2]->m_bDrawGrid = 1;
	m_pCargoGridList[2]->m_eGridType = TMEGRIDTYPE::GRID_CARGO;

	m_pGridInvList[0] = (SGridControl*)m_pControlContainer->FindControl(67072);
	m_pGridInvList[1] = (SGridControl*)m_pControlContainer->FindControl(67073);
	m_pGridInvList[2] = (SGridControl*)m_pControlContainer->FindControl(67074);
	m_pGridInvList[3] = (SGridControl*)m_pControlContainer->FindControl(67075);
	m_pGridInvList[0]->SetVisible(0);
	m_pGridInvList[1]->SetVisible(0);
	m_pGridInvList[2]->SetVisible(0);
	m_pGridInvList[3]->SetVisible(0);
	m_pGridInv = m_pGridInvList[0];
	m_pGridInv->SetVisible(1);

	m_pQuicInvDelete = (SGridControl*)m_pControlContainer->FindControl(67080);
	m_pQuicInvDelete->m_eGridType = TMEGRIDTYPE::GRID_DELETE;
	m_pGridHelm = (SGridControl*)m_pControlContainer->FindControl(65555);
	m_pGridCoat = (SGridControl*)m_pControlContainer->FindControl(65558);
	m_pGridPants = (SGridControl*)m_pControlContainer->FindControl(65559);
	m_pGridGloves = (SGridControl*)m_pControlContainer->FindControl(65560);
	m_pGridBoots = (SGridControl*)m_pControlContainer->FindControl(65561);
	m_pGridRight = (SGridControl*)m_pControlContainer->FindControl(65556);
	m_pGridLeft = (SGridControl*)m_pControlContainer->FindControl(65557);
	m_pGridGuild = (SGridControl*)m_pControlContainer->FindControl(65548);
	m_pGridEvent = (SGridControl*)m_pControlContainer->FindControl(65549);
	m_pGridRing = (SGridControl*)m_pControlContainer->FindControl(65550);
	m_pGridNecklace = (SGridControl*)m_pControlContainer->FindControl(65551);
	m_pGridOrb = (SGridControl*)m_pControlContainer->FindControl(65552);
	m_pGridCabuncle = (SGridControl*)m_pControlContainer->FindControl(65553);
	m_pGridDRing = (SGridControl*)m_pControlContainer->FindControl(65546);
	m_pGridMantua = (SGridControl*)m_pControlContainer->FindControl(65547);
	m_pGridSkillMaster = (SGridControl*)m_pControlContainer->FindControl(65607);
	m_pGridShop = (SGridControl*)m_pControlContainer->FindControl(65694);

	m_pGridShop->m_bDrawGrid = 1;
	m_pGridShop->m_eGridType = TMEGRIDTYPE::GRID_SHOP;
	m_pGridMantua->m_eGridType = TMEGRIDTYPE::GRID_TRADENONE;
	m_pGridInvList[0]->m_bDrawGrid = 1;
	m_pGridInvList[1]->m_bDrawGrid = 1;
	m_pGridInvList[2]->m_bDrawGrid = 1;
	m_pGridInvList[3]->m_bDrawGrid = 1;
	m_pGridSkillMaster->m_bDrawGrid = 0;
	m_pGridSkillMaster->m_eGridType = TMEGRIDTYPE::GRID_SKILLM;
	m_pCargoGrid->m_bDrawGrid = 1;
	m_pCargoGrid->m_eGridType = TMEGRIDTYPE::GRID_CARGO;
	m_pGridSkillBelt = (SGridControl*)m_pControlContainer->FindControl(65598);
	m_pGridSkillBelt2 = (SGridControl*)m_pControlContainer->FindControl(65644);
	m_pGridSkillBelt2->m_eGridType = TMEGRIDTYPE::GRID_SKILLB;
	m_pGridSkillBelt3 = (SGridControl*)m_pControlContainer->FindControl(65645);
	m_pGridSkillBelt3->m_eGridType = TMEGRIDTYPE::GRID_SKILLB;
	m_pGridSkillBelt3->SetVisible(0);
	m_pShortSkillTglBtn1 = (SButton*)m_pControlContainer->FindControl(65646);
	m_pShortSkillTglBtn2 = (SButton*)m_pControlContainer->FindControl(65647);
	m_pQuick_Sloat[0] = (SGridControl*)m_pControlContainer->FindControl(66560);
	m_pQuick_Sloat[0]->m_eGridType = TMEGRIDTYPE::GRID_QUICKSLOAT1;
	m_pQuick_Sloat[1] = (SGridControl*)m_pControlContainer->FindControl(66561);
	m_pQuick_Sloat[1]->m_eGridType = TMEGRIDTYPE::GRID_QUICKSLOAT2;
	m_pQuick_Sloat[2] = (SGridControl*)m_pControlContainer->FindControl(66562);
	m_pQuick_Sloat[2]->m_eGridType = TMEGRIDTYPE::GRID_QUICKSLOAT3;
	m_pQuick_Sloat[3] = (SGridControl*)m_pControlContainer->FindControl(66563);
	m_pQuick_Sloat[3]->m_eGridType = TMEGRIDTYPE::GRID_QUICKSLOAT4;
	m_pQuick_Sloat[4] = (SGridControl*)m_pControlContainer->FindControl(66564);
	m_pQuick_Sloat[4]->m_eGridType = TMEGRIDTYPE::GRID_QUICKSLOAT5;
	m_pShortSkillTglBtn1->SetSelected(1);
	OnControlEvent(65646, 0);
	m_bSkillBeltSwitch = 0;

	int nClass = BASE_GetItemAbility(&pMobData->Equip[0], 18);

	if (pMobData->Equip[1].sIndex > 40 && nClass != 21)
	{
		STRUCT_ITEM* pItemHelm = new STRUCT_ITEM();
		memcpy(pItemHelm, &pMobData->Equip[1], 8);
				
		m_pGridHelm->AddItem(new SGridControlItem(nullptr, pItemHelm, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[2].sIndex > 40)
	{
		STRUCT_ITEM* pItemCoat = new STRUCT_ITEM();
		memcpy(pItemCoat, &pMobData->Equip[2], 8);

		m_pGridCoat->AddItem(new SGridControlItem(nullptr, pItemCoat, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[3].sIndex > 40)
	{
		STRUCT_ITEM* pItemPants = new STRUCT_ITEM();
		memcpy(pItemPants, &pMobData->Equip[3], 8);

		m_pGridPants->AddItem(new SGridControlItem(nullptr, pItemPants, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[4].sIndex > 40)
	{
		STRUCT_ITEM* pItemGloves = new STRUCT_ITEM();
		memcpy(pItemGloves, &pMobData->Equip[4], 8);

		m_pGridGloves->AddItem(new SGridControlItem(nullptr, pItemGloves, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[5].sIndex > 40)
	{
		STRUCT_ITEM* pItemBoots = new STRUCT_ITEM();
		memcpy(pItemBoots, &pMobData->Equip[5], 8);

		m_pGridBoots->AddItem(new SGridControlItem(nullptr, pItemBoots, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[7].sIndex > 40)
	{
		STRUCT_ITEM* pItemRight = new STRUCT_ITEM();
		memcpy(pItemRight, &pMobData->Equip[7], 8);

		m_pGridRight->AddItem(new SGridControlItem(nullptr, pItemRight, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[6].sIndex > 40)
	{
		STRUCT_ITEM* pItemLeft = new STRUCT_ITEM();
		memcpy(pItemLeft, &pMobData->Equip[6], 8);

		m_pGridLeft->AddItem(new SGridControlItem(nullptr, pItemLeft, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[12].sIndex > 40)
	{
		STRUCT_ITEM* pItemGuild = new STRUCT_ITEM();
		memcpy(pItemGuild, &pMobData->Equip[12], 8);

		m_pGridGuild->AddItem(new SGridControlItem(nullptr, pItemGuild, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[13].sIndex > 40)
	{
		STRUCT_ITEM* pItemEvent = new STRUCT_ITEM();
		memcpy(pItemEvent, &pMobData->Equip[13], 8);

		m_pGridEvent->AddItem(new SGridControlItem(nullptr, pItemEvent, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[14].sIndex > 40)
	{
		STRUCT_ITEM* pItemDRing = new STRUCT_ITEM();
		memcpy(pItemDRing, &pMobData->Equip[14], 8);

		m_pGridDRing->AddItem(new SGridControlItem(nullptr, pItemDRing, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[15].sIndex > 40)
	{
		STRUCT_ITEM* pItemMantua = new STRUCT_ITEM();
		memcpy(pItemMantua, &pMobData->Equip[15], 8);

		m_pGridMantua->AddItem(new SGridControlItem(nullptr, pItemMantua, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[8].sIndex > 40)
	{
		STRUCT_ITEM* pItemRing = new STRUCT_ITEM();
		memcpy(pItemRing, &pMobData->Equip[8], 8);

		m_pGridRing->AddItem(new SGridControlItem(nullptr, pItemRing, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[9].sIndex > 40)
	{
		STRUCT_ITEM* pItemNecklace = new STRUCT_ITEM();
		memcpy(pItemNecklace, &pMobData->Equip[9], 8);

		m_pGridNecklace->AddItem(new SGridControlItem(nullptr, pItemNecklace, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[10].sIndex > 40)
	{
		STRUCT_ITEM* pItemOrb = new STRUCT_ITEM();
		memcpy(pItemOrb, &pMobData->Equip[10], 8);

		m_pGridOrb->AddItem(new SGridControlItem(nullptr, pItemOrb, 0.0f, 0.0f), 0, 0);
	}
	if (pMobData->Equip[11].sIndex > 40)
	{
		STRUCT_ITEM* pItemCabuncle = new STRUCT_ITEM();
		memcpy(pItemCabuncle, &pMobData->Equip[11], 8);

		m_pGridCabuncle->AddItem(new SGridControlItem(nullptr, pItemCabuncle, 0.0f, 0.0f), 0, 0);
	}

	for (int nCarryIndex = 0; nCarryIndex < 64; ++nCarryIndex)
	{
		if (pMobData->Carry[nCarryIndex].sIndex > 40)
		{
			STRUCT_ITEM* pItemCarry = new STRUCT_ITEM();
			memcpy(pItemCarry, &pMobData->Carry[nCarryIndex], 8);
			
			int Page = nCarryIndex / 15;
			if (nCarryIndex / 15 > -1 && Page < 4)
			{
				m_pGridInvList[Page]->AddItem(new SGridControlItem(0, pItemCarry, 0.0f, 0.0f),
					nCarryIndex % 15 % 5,
					nCarryIndex % 15 / 5);
			}				
		}
	}

	STRUCT_ITEM* pCargo = g_pObjectManager->m_stItemCargo;
	for (int nCargoIndex = 0; nCargoIndex < 120; ++nCargoIndex)
	{
		if (g_pObjectManager->m_stItemCargo[nCargoIndex].sIndex)
		{
			STRUCT_ITEM* pItemCargo = new STRUCT_ITEM();
			memcpy(pItemCargo, &pCargo[nCargoIndex], 8);
			
			int Page = nCargoIndex / 40;
			if (nCargoIndex / 40 > -1 && Page < 3)
			{
				m_pCargoGridList[Page]->AddItem(new SGridControlItem(0, pItemCargo, 0.0f, 0.0f),
					nCargoIndex % 40 % 5,
					nCargoIndex % 40 / 5);
			}			
		}
	}

	m_pMyHuman->m_stScore = pMobData->CurrentScore;

	m_pMyHuman->SetCharHeight((float)m_pMyHuman->m_stScore.Con);
	m_pMyHuman->SetRace(pMobData->Equip[0].sIndex);

	if (BASE_GetItemAbility(&pMobData->Equip[6], 21) == 41)
	{
		m_pMyHuman->m_stLookInfo.RightMesh = m_pMyHuman->m_stLookInfo.LeftMesh;
		m_pMyHuman->m_stLookInfo.RightSkin = m_pMyHuman->m_stLookInfo.LeftSkin;
		m_pMyHuman->m_stSancInfo.Sanc6 = m_pMyHuman->m_stSancInfo.Sanc7;
		m_pMyHuman->m_stSancInfo.Legend6 = m_pMyHuman->m_stSancInfo.Legend7;
	}

	m_pMyHuman->InitObject(); 
	m_pMyHuman->CheckWeapon(pMobData->Equip[6].sIndex, pMobData->Equip[7].sIndex);
	m_pMyHuman->InitAngle(0.0f, 0.39269909f, 0.0f);
	m_pMyHuman->InitPosition((float)pMobData->HomeTownX + 0.5f, 0, (float)pMobData->HomeTownY + 0.5f);

	g_pObjectManager->m_pCamera->SetFocusedObject(m_pMyHuman);
	g_pObjectManager->m_pCamera->m_nQuaterView = 0;
	m_bLastMyAttr = BASE_GetAttr(pMobData->HomeTownX, pMobData->HomeTownY);
	UpdateScoreUI(0);
	UpdateSkillBelt();
	g_pObjectManager->m_cSelectShortSkill = 0;

	for (int ie = 0; ie < 10; ++ie)
	{
		if ((unsigned char)g_pObjectManager->m_cShortSkill[ie] < 248)
			OnKeyShortSkill(ie + 49, 0);
	}

	if (m_pMyHuman->Is2stClass() == 2 && g_pObjectManager->m_stMobData.CurrentScore.Level >= 79)
		g_pSpell[102].Delay = 1000;

	if (!m_pObjectContainerList[0]->Load(szDataPath))
	{
		LOG_WRITELOG("DataFile Not Found\r\n");
		if (!m_bCriticalError)
			LogMsgCriticalError(3, 0, 0, 0, 0);

		m_bCriticalError = 1;
	}

	for (int nY = 0; nY < 128; ++nY)
		memcpy(&m_HeightMapData[nY], m_pGround->m_pMaskData[nY], 128);

	g_HeightPosX = (int)m_pGround->m_vecOffset.x;
	g_HeightPosY = (int)m_pGround->m_vecOffset.y;
	BASE_ApplyAttribute((char*)&m_HeightMapData, 256);

	memcpy(m_GateMapData, m_HeightMapData, sizeof(m_HeightMapData));

	m_pItemContainer = new TreeNode(0);
	m_pGroundObjectContainer->AddChild(m_pGroundList[0]);
	m_pSun = new TMSun();

	if (m_pSun)
	{
		m_pSun->InitObject();
		m_pEffectContainer->AddChild(m_pSun);
	}

	m_pSky = new TMSky();	
	m_pSky->m_bVisible = 0;

	AddChild(m_pSky);
	AddChild(m_pItemContainer);

	SetSanc();

	m_pMyHuman->m_cHide = (m_pMyHuman->m_dwID > 0 && m_pMyHuman->m_dwID < 1000) == 1 && m_pMyHuman->m_stScore.Reserved & 1;
	m_pHumanContainer->AddChild(m_pMyHuman);

	auto pSoundManager = g_pSoundManager;
	if (pSoundManager)
	{
		auto pSoundData = pSoundManager->GetSoundData(102);
		if (pSoundData && !pSoundData->IsSoundPlaying())
			pSoundData->Play();
	}

	m_pRain = new TMRain();
	m_pRain->m_bVisible = 0;
	m_pEffectContainer->AddChild(m_pRain);

	m_pSnow = new TMSnow(1.0f);
	m_pSnow->m_bVisible = 0;
	m_pEffectContainer->AddChild(m_pSnow);

	m_pSnow2 = new TMSnow(2.0f);
	m_pSnow2->m_bVisible = 0;
	m_pEffectContainer->AddChild(m_pSnow2);

	m_pTarget1 = new TMEffectMesh(316, 0xFF111188, 0.0f, 0);
	m_pTarget1->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
	m_pEffectContainer->AddChild(m_pTarget1);

	m_pTarget2 = new TMEffectMesh(317, 0xFFFF0000, 0.0f, 0);
	m_pEffectContainer->AddChild(m_pTarget2);

	m_pTargetBill = new TMEffectBillBoard2(232, 0, 1.0f, 1.0f, 1.0f, 0.0005f, 0);
	m_pTargetBill->m_efAlphaType = EEFFECT_ALPHATYPE::EF_BRIGHT;
	m_pTargetBill->SetColor(0xFF9999AA);
	m_pEffectContainer->AddChild(m_pTargetBill);

	g_pDevice->m_colorLight.r = 1.0f;
	g_pDevice->m_colorLight.g = 1.0f;
	g_pDevice->m_colorLight.b = 1.0f;
	g_pDevice->m_colorBackLight.r = 0.0;
	g_pDevice->m_colorBackLight.g = 0.2f;
	g_pDevice->m_colorBackLight.b = 0.3f;

	m_pMiniMapPanel = (SPanel*)m_pControlContainer->FindControl(289);
	m_pMiniMapZoomIn = (SButton*)m_pControlContainer->FindControl(5714);
	m_pMiniMapZoomOut = (SButton*)m_pControlContainer->FindControl(5715);
	if (m_pMainInfo2_Name)
		m_pMainInfo2_Name->SetText(m_pMyHuman->m_szName, 1);

	m_pMiniMapServerPanel = (SPanel*)m_pControlContainer->FindControl(6136);
	m_pMiniMapServerText = (SText*)m_pControlContainer->FindControl(6137);
	m_pMiniMapDir = (SPanel*)m_pControlContainer->FindControl(291);

	SButton* pMiniMapBtn = (SButton*)m_pControlContainer->FindControl(296);
	if (m_pMiniMapPanel)
	{
		m_pMiniMapPanel->GetGeomControl()->fAngle = -0.78539819f;
		m_pMiniMapPanel->m_bSelectEnable = 0;

		if (m_pMiniMapDir)
			m_pMiniMapDir->m_bSelectEnable = 0;

		m_pMiniMapPanel->SetVisible(0);

		if (pMiniMapBtn)
			pMiniMapBtn->SetSelected(0);
		m_pMiniMapPanel->m_GCPanel.dwColor = 0x80FFFFFF;
	}

	for (int ig = 0; ig < 256; ++ig)
	{
		m_pInMiniMapPosPanel[ig] = new SPanel(-2, 0.0, 0.0, 4.0, 4.0, g_MinimapPos[ig].dwColor, RENDERCTRLTYPE::RENDER_IMAGE_STRETCH);

		if (m_pInMiniMapPosPanel[ig])
		{
			m_pInMiniMapPosPanel[ig]->m_bSelectEnable = 0;
			m_pInMiniMapPosPanel[ig]->SetVisible(0);
			m_pMiniMapPanel->AddChild(m_pInMiniMapPosPanel[ig]);
		}

		m_pInMiniMapPosText[ig] = new SText(-2,
			g_MinimapPos[ig].szTarget,
			g_MinimapPos[ig].dwColor,
			0.0f,
			0.0f,
			8.0f,
			12.0f,
			0,
			0x77777777u,
			1u,
			0);

		if (m_pInMiniMapPosText[ig])
		{
			m_pInMiniMapPosText[ig]->m_bSelectEnable = 0;
			m_pInMiniMapPosText[ig]->SetVisible(0);
			m_pMiniMapPanel->AddChild(m_pInMiniMapPosText[ig]);
		}
	}

	SPanel* pPartyPanel = (SPanel*)m_pControlContainer->FindControl(475136);
	SText* pPartyTitle = (SText*)m_pControlContainer->FindControl(475137);
	m_pPartyList = (SListBox*)m_pControlContainer->FindControl(475138);
	m_pPartyPanel = (SPanel*)pPartyPanel;
	m_pPartyBtn = (SButton*)m_pControlContainer->FindControl(5742);

	if (pPartyPanel)
	{
		pPartyPanel->SetStickLeft();
		pPartyPanel->SetStickTop();
		pPartyPanel->m_nPosY = pPartyPanel->m_nPosY + 135.0f;
	}

	if (m_pPartyBtn)
		m_pPartyBtn->SetPos(0.0f, ((float)g_pDevice->m_dwScreenHeight - pPartyPanel->m_nHeight) - 165.0f);

	if (m_pPartyBtn)
		m_pPartyBtn->m_pAltText->SetPos(m_pPartyBtn->m_pAltText->m_nPosX + 5.0f, (pPartyPanel->m_nHeight * 0.5f) - 13.0f);

	OnControlEvent(5742, 0);

	m_pMsgPanel = (SPanel*)m_pControlContainer->FindControl(669);
	m_pMsgList = (SListBox*)m_pControlContainer->FindControl(670);
	m_pMsgText = (SText*)m_pControlContainer->FindControl(638);
	m_pGMsgPanel = (SPanel*)m_pControlContainer->FindControl(819);
	m_pGMsgText = (SText*)m_pControlContainer->FindControl(820);
	m_pGMsgListPanel = (SPanel*)m_pControlContainer->FindControl(823);
	m_pGMsgViewPanel = (SPanel*)m_pControlContainer->FindControl(828);
	m_pGMsgWritePanel = (SPanel*)m_pControlContainer->FindControl(838);
	m_pGMsgList = (SListBox*)m_pControlContainer->FindControl(825);
	m_pGMsgRContext = (SListBox*)m_pControlContainer->FindControl(829);
	m_pGMsgReplyList = (SListBox*)m_pControlContainer->FindControl(830);
	m_pGMsgWContext = (SListBox*)m_pControlContainer->FindControl(840);
	m_pGMsgEditRelpy = (SEditableText*)m_pControlContainer->FindControl(837);
	m_pGMsgEditTitle = (SEditableText*)m_pControlContainer->FindControl(839);
	m_pGMsgTitile = (SText*)m_pControlContainer->FindControl(836);
	m_pBtnBoardModify = (SButton*)m_pControlContainer->FindControl(832);
	m_pBtnBoardDel = (SButton*)m_pControlContainer->FindControl(834);
	m_pBtnBoardSaveGM = (SButton*)m_pControlContainer->FindControl(842);
	m_pBtnSaveReply = (SButton*)m_pControlContainer->FindControl(831);
	m_pBtnWrite = (SButton*)m_pControlContainer->FindControl(827);

	m_pRPSGamePanel = (SPanel*)m_pControlContainer->FindControl(1616);
	m_pRPSGamePanel->SetVisible(0);
	m_pRPSGamePanel->m_bPickable = 0;
	m_pRPSGameRock = (SButton*)m_pControlContainer->FindControl(1617);
	m_pRPSGamePaper = (SButton*)m_pControlContainer->FindControl(1618);
	m_pRPSGameScissor = (SButton*)m_pControlContainer->FindControl(1619u);

	InitBoard();

	if (!LoadMsgText(m_pMsgList, (char*)"notice.txt"))
		m_pMsgPanel->SetVisible(0);

	m_pMsgPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pMsgPanel->m_nWidth * 0.5f),
		((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pMsgPanel->m_nHeight * 0.5f));

	m_pMsgPanel->SetVisible(0);

	SetWeather(g_nWeather);

	if (m_pHelpList[3])
	{
		int n;
		for (n = 0; n < 99 && (g_pObjectManager->m_stMemo[n].szString[0] || g_pObjectManager->m_stMemo[n + 1].szString[0]); ++n)
		{
			SListBoxItem* pItem = new SListBoxItem(g_pObjectManager->m_stMemo[n].szString,
				g_pObjectManager->m_stMemo[n].dwColor,
				0.0f,
				0.0f,
				300.0f,
				16.0f,
				0,
				0x77777777u,
				1u,
				0);

			m_pHelpList[3]->AddItem(pItem);
		}

		if (n > 0 && m_pHelpMemo)
			m_pHelpMemo->SetVisible(1);
	}

	m_pReelPanel = new SReelPanel(330, 21.0f, 79.0f, 62.0f, 62.0f, 1.0f);
	m_pReelPanel2 = new SReelPanel(340, 21.0f, 79.0f, 62.0f, 62.0f, 1.0f);

	m_pGambleStore->AddChild(m_pReelPanel);
	m_pGambleStore->AddChild(m_pReelPanel2);

	if (!strcmp(g_TempName, g_pObjectManager->m_stMobData.MobName))
	{
		if (strcmp(g_TempNick, " "))
		{
			MSG_MessageWhisper stWhisper{};
			stWhisper.Header.ID = g_pObjectManager->m_dwCharID;
			stWhisper.Header.Type = MSG_MessageWhisper_Opcode;

			sprintf(stWhisper.MobName, "tab");
			sprintf(stWhisper.String, g_TempNick);
			SendOneMessage((char*)&stWhisper, sizeof(stWhisper));
		}
	}

	m_pServerPanel = (SPanel*)m_pControlContainer->FindControl(12288);
	m_pServerList = (SListBox*)m_pControlContainer->FindControl(12289);

	m_pServerPanel->SetPos((float)(g_pDevice->m_dwScreenWidth >> 1) - (m_pServerPanel->m_nWidth / 2.0f),
		(float)(g_pDevice->m_dwScreenHeight >> 1) - (m_pServerPanel->m_nHeight / 2.0f));
	m_pServerPanel->SetVisible(0);

	if (g_nKeyType == 1)
		m_pControlContainer->SetFocusedControl(m_pEditChat);

	InitCameraView();
	SetCameraView();

	m_pAlphaNative->SetPos((float)(m_pEditChat->m_nWidth + m_pChatPanel->m_nWidth) - 40.0f,
		(float)(m_pChatPanel->m_nPosY + m_pEditChat->m_nPosY) - 2.0f);

	m_pFireWorkPanel = (SPanel*)m_pControlContainer->FindControl(8705);

	if (m_pFireWorkPanel)
	{
		for (int jj = 0; jj < 100; ++jj)
		{
			m_pFireWorkButton[jj] = new SButton(375,
				(float)(25 * (jj % 10)) + 3.0f,
				(float)(25 * (jj / 10)) + 3.0f,
				24.0f,
				24.0f,
				0x77777777u,
				1,
				(char*)"");

			m_pFireWorkButton[jj]->SetControlID(jj + 8706);
			m_pFireWorkButton[jj]->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);

			m_pFireWorkPanel->AddChild(m_pFireWorkButton[jj]);
		}

		m_pFireWorkPanel->m_bModal = 1;
		m_pControlContainer->m_pModalControl[5] = m_pFireWorkPanel;
		m_pFireWorkPanel->SetVisible(0);

		m_pFireWorkPanel->SetPos((float)(g_pDevice->m_dwScreenWidth) - (m_pFireWorkPanel->m_nWidth / 2.0f),
			(float)(g_pDevice->m_dwScreenHeight) - (m_pFireWorkPanel->m_nHeight / 2.0f));
	}

	m_pTotoPanel = (SPanel*)m_pControlContainer->FindControl(8961);

	if (m_pTotoPanel)
	{
		m_pTotoSelect_Btn = (SButton*)m_pControlContainer->FindControl(8964);
		m_pTotoBuy_Btn = (SButton*)m_pControlContainer->FindControl(8978);
		m_pTotoQuit_Btn = (SButton*)m_pControlContainer->FindControl(8966);
		m_pTotoNumber_Edit = (SEditableText*)m_pControlContainer->FindControl(8963);
		m_pTotoNumber_Edit->m_nMaxStringLen = 3;
		m_pTotoTime_Txt = (SText*)m_pControlContainer->FindControl(8968);
		m_pTotoTeamA_Txt = (SText*)m_pControlContainer->FindControl(8971);
		m_pTotoTeamB_Txt = (SText*)m_pControlContainer->FindControl(8972);
		m_pTotoScoreA_Edit = (SEditableText*)m_pControlContainer->FindControl(8973);
		m_pTotoScoreA_Edit->m_nMaxStringLen = 3;
		m_pTotoScoreB_Edit = (SEditableText*)m_pControlContainer->FindControl(8974);
		m_pTotoScoreB_Edit->m_nMaxStringLen = 3;
		m_pTotoPanel->m_bModal = 1;
		m_pControlContainer->m_pModalControl[6] = (SControl*)m_pTotoPanel;
		m_pTotoPanel->SetVisible(0);

		m_pTotoPanel->SetPos((float)(g_pDevice->m_dwScreenWidth) - (m_pTotoPanel->m_nWidth / 2.0f),
			(float)(g_pDevice->m_dwScreenHeight) - (m_pTotoPanel->m_nHeight / 2.0f));
	}

	BASE_ReadTOTOList((char*)"UI\\TOTOGame.csv");

	SetAutoTarget();

	memset(&m_stMoveStop, 0, sizeof(m_stMoveStop));

	m_dwLastCheckAutoMouse = g_pTimerManager->GetServerTime();
	m_dwLastCheckPlayTime = g_pTimerManager->GetServerTime();
	m_nPlayTime = 0;

	g_pTextureManager->Release_GuildMarkList();
	g_pObjectManager->m_pCamera->m_fMaxCamLen = 15.0f;
	if (m_pPartyPanel)
		m_pPartyPanel->SetVisible(0);

	for (int ih = 0; ih < 32; ++ih)
	{
		m_pAffectIcon[ih] = (SPanel*)m_pControlContainer->FindControl(ih + 90400);
		m_pTargetAffectIcon[ih] = (SPanel*)m_pControlContainer->FindControl(ih + 90369);
	}

	m_pAffectDesc = (SText*)m_pControlContainer->FindControl(65798);
	m_pAffectDescList[0] = (SText*)m_pControlContainer->FindControl(773);
	m_pAffectDescList[1] = (SText*)m_pControlContainer->FindControl(774);
	m_pAffectDescList[2] = (SText*)m_pControlContainer->FindControl(775);
	m_pAffectDescList[3] = (SText*)m_pControlContainer->FindControl(776);
	m_pAffectDescList[4] = (SText*)m_pControlContainer->FindControl(777);
	m_pAffectDescList[5] = (SText*)m_pControlContainer->FindControl(784);
	m_pAffectDescList[6] = (SText*)m_pControlContainer->FindControl(794);
	m_pAffectDescList[7] = (SText*)m_pControlContainer->FindControl(795);
	m_pAffectDescList[8] = (SText*)m_pControlContainer->FindControl(796);
	m_pAffectDescList[9] = (SText*)m_pControlContainer->FindControl(797);
	m_pAffectDescList[10] = (SText*)m_pControlContainer->FindControl(798);
	m_pAffectDescList[11] = (SText*)m_pControlContainer->FindControl(799);

	for (int j = 0; j < 13; ++j)
	{
		for (int ii = 0; ii < 32; ++ii)
			m_pPartyAffectIcon[j][ii] = (SPanel*)m_pControlContainer->FindControl(32 * j + ii + 475152);
	}

	m_pPartyAffectText = (SText*)m_pControlContainer->FindControl(7602193);
	m_pPartyAutoButton = (SButton*)m_pControlContainer->FindControl(7602194);
	m_pPartyAutoText = (SText*)m_pControlContainer->FindControl(7602195);
	
	SListBox* temp1 = (SListBox*)m_pControlContainer->FindControl(1054276u);
	SListBox* temp2 = (SListBox*)m_pControlContainer->FindControl(1054277u);

	m_pDailyQuestButton = (SButton*)m_pControlContainer->FindControl(1054278);

	if (temp1)
		temp1->SetVisible(0);
	if (temp2)
		temp2->SetVisible(0);

	if (m_pDailyQuestButton)
		m_pDailyQuestButton->SetVisible(0);

	LOG_WRITELOG(">> Init Field Scene::End\r\n");
	g_bEffectFirst = 1;
	return 1;
}

int TMFieldScene::OnControlEvent(unsigned int idwControlID, unsigned int idwEvent)
{
	return 0;
}

int TMFieldScene::OnCharEvent(char iCharCode, int lParam)
{
	if (m_bAirMove == 1)
		return 0;

	DWORD dwServerTime = g_pTimerManager->GetServerTime();

	if (dwServerTime < g_dwStartQuitGameTime + 6000)
		return 1;

	if (dwServerTime < m_dwLastLogout + 6000)
		return 1;

	if (dwServerTime < m_dwLastSelServer + 6000)
		return 1;

	if (dwServerTime < m_dwLastTown + 6000)
		return 1;

	if (dwServerTime < m_dwLastResurrect + 6000)
		return 1;

	if (dwServerTime < m_dwLastTeleport + 6000)
		return 1;

	if (dwServerTime < m_dwLastRelo + 6000)
		return 1;

	if (dwServerTime < m_dwLastWhisper + 6000)
		return 1;

	if (m_pMessageBox->IsVisible() == 1
		&& (m_pMessageBox->m_dwMessage == 601 || m_pMessageBox->m_dwMessage == 927)
		&& iCharCode == 13)
	{
		return 1;
	}

	if (g_nKeyType == 1)
	{
		if (iCharCode == 27)
		{
			OnESC();
			return 1;
		}

		if (TMScene::OnCharEvent(iCharCode, lParam) == 1)
			return 1;
	}
	else
	{
		if (TMScene::OnCharEvent(iCharCode, lParam) == 1)
			return 1;

		if (iCharCode == 27)
		{
			OnESC();
			return 1;
		}
	}

	if (m_bCriticalError == 1)
		return 1;

	if (OnKeyTotoTab(iCharCode, lParam))
		return 1;

	if (OnKeyCamView(iCharCode, lParam))
		return 1;

	if (g_nKeyType)
		return 0;

	if (UseQuickSloat(iCharCode))
		return 1;

	if (OnKeyTotoEnter(iCharCode, lParam))
		return 1;

	if (OnKeyDebug(iCharCode, lParam))
		return 1;

	if (OnKeySkill(iCharCode, lParam))
		return 1;

	if (OnKeyDash(iCharCode, lParam))
		return 1;

	if (OnKeyPlus(iCharCode, lParam))
		return 1;

	if (OnKeyPK(iCharCode, lParam))
		return 1;

	if (OnKeyName(iCharCode, lParam))
		return 1;

	if (OnKeyAutoTarget(iCharCode, lParam))
		return 1;

	if (OnKeyHelp(iCharCode, lParam))
		return 1;

	if (OnKeyRun(iCharCode, lParam))
		return 1;

	if (OnKeyFeedMount(iCharCode, lParam))
		return 1;

	if (g_pObjectManager->m_stMobData.CurrentScore.Hp > 0)
	{
		if (OnKeyHPotion(iCharCode, lParam))
			return 1;

		if (OnKeyMPotion(iCharCode, lParam))
			return 1;

		if (OnKeyPPotion(iCharCode, lParam))
			return 1;

		if (OnKeySkillPage(iCharCode, lParam))
			return 1;

		if (OnKeyQuestLog(iCharCode, lParam))
			return 1;

		if (OnKeyReverse(iCharCode, lParam))
			return 1;

		if (OnKeyAutoRun(iCharCode, lParam))
			return 1;

		if (OnKeyGuildOnOff(iCharCode, lParam))
			return 1;

		if (OnKeyShortSkill(iCharCode, lParam))
			return 1;
	}

	if (OnKeyVisibleSkill(iCharCode, lParam))
		return 1;

	if (OnKeyVisibleInven(iCharCode, lParam))
		return 1;

	if (OnKeyVisibleCharInfo(iCharCode, lParam))
		return 1;

	if (OnKeyVisibleMinimap(iCharCode, lParam))
		return 1;

	if (OnKeyVisibleParty(iCharCode, lParam))
		return 1;

	if (OnKeyReturn(iCharCode, lParam))
		return 1;
	
	return 0;
}

int TMFieldScene::OnKeyDownEvent(unsigned int iKeyCode)
{
	return 0;
}

int TMFieldScene::OnMouseEvent(unsigned int dwFlags, unsigned int wParam, int nX, int nY)
{
	DWORD dwServerTime = g_pTimerManager->GetServerTime();

	if (dwServerTime < g_dwStartQuitGameTime + 6000)
		return 1;

	if (dwServerTime < m_dwLastLogout + 6000)
		return 1;

	if (dwServerTime < m_dwLastSelServer + 6000)
		return 1;

	if (dwServerTime < m_dwLastTown + 6000)
		return 1;

	if (dwServerTime < m_dwLastResurrect + 6000)
		return 1;

	if (dwServerTime < m_dwLastTeleport + 6000)
		return 1;

	if (dwServerTime < m_dwLastRelo + 6000)
		return 1;

	if (dwServerTime < m_dwLastWhisper + 6000)
		return 1;

	if (dwServerTime < m_dwNPCClickTime + 1000)
		return 1;

	if (m_bAirMove == 1)
		return 0;

	if (TMScene::OnMouseEvent(dwFlags, wParam, nX, nY) == 1)
		return 1;

	if (g_bActiveWB == 1)
		return 1;

	if (m_bCriticalError == 1)
		return 1;

	for (int nModIndex = 0; nModIndex < 8; ++nModIndex)
	{
		if (m_pControlContainer->m_pModalControl[nModIndex] &&
			m_pControlContainer->m_pModalControl[nModIndex]->IsVisible())
		{
			if (m_pControlContainer->m_pModalControl[nModIndex] != static_cast<SControl*>(m_pMessageBox))
				return 1;

			if (m_pMessageBox->m_dwMessage != 601 && m_pMessageBox->m_dwMessage != 927)
				return 1;
		}
	}

	if (nX != m_nLastMousePosX || nY != m_nLastMousePosY || !g_pEventTranslator->button[0] && !g_pEventTranslator->button[1])
	{
		m_nLastMousePosX = nX;
		m_nLastMousePosY = nY;
		m_dwLastMousePosTime = dwServerTime;
	}

	if (m_pMessageBox->m_bVisible == 1 && 
		m_pMessageBox->m_dwMessage == 99 &&
		g_pObjectManager->m_stMobData.CurrentScore.Hp > 0 &&
		!m_pMyHuman->m_cDie)
	{
		m_pMessageBox->SetVisible(0);
	}

	auto pMobData = &g_pObjectManager->m_stMobData;

	if (m_cResurrect ||
		pMobData->Equip[13].sIndex == 769 ||
		g_pObjectManager->m_stMobData.CurrentScore.Hp > 0 && m_pMyHuman->m_cDie != 1 ||
		dwFlags != 516 ||
		wParam & 8 ||
		nX <= 0 ||
		nY <= 0 ||
		nX >= static_cast<int>(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift) ||
		nY >= static_cast<int>(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift))
	{
		if ((g_pObjectManager->m_stMobData.CurrentScore.Hp <= 0 || m_pMyHuman->m_cDie == 1)
			&& dwFlags == 513
			&& !m_pMyHuman->m_sFamCount)
		{
			POINT pt{};
			pt.x = static_cast<int>(m_pMyHuman->m_vecPosition.x);
			pt.y = static_cast<int>(m_pMyHuman->m_vecPosition.y);

			RECT rectTownInCastle{};//??

			if (!m_pMessageBox->IsVisible() && (!m_pMyHuman->IsInTown() || PtInRect(&rectTownInCastle, pt) == 1))
			{
				m_pMessageBox->SetMessage(g_pMessageStringTable[27], 11u, 0);
				m_pMessageBox->SetVisible(1);
				return 1;
			}
		}
		if (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_DEAD)
			return 1;

		if (wParam & 4 && dwFlags == 516)
		{
			if (m_pMouseOverHuman)
			{
				if (m_pMouseOverHuman->m_dwID < 1000)
				{
					char szStrTemp[128]{};
					sprintf_s(szStrTemp, "/%s ", m_pMouseOverHuman->m_szName);

					m_pEditChat->SetText(szStrTemp);

					m_dwOldAttackTime = dwServerTime;
					return 1;
				}
			}
		}

		auto vec = GroundGetPickPos();

		auto pPanel = m_pInvenPanel;

		if (m_pMyHuman->m_bSliding == 1)
			return 1;

		if (m_pMyHuman->m_cOnlyMove == 1 
			&& (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_STAND01 || 
				m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_STAND02 ||
				m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_LEVELUP))
		{
			m_pMyHuman->m_cOnlyMove = 0;
			m_pMyHuman->SetSpeed(m_bMountDead);
		}

		if (m_pMyHuman->m_cOnlyMove == 1)
			return 1;

		if (m_pMyHuman->m_cSameHeight == 1)
			return 1;

		if (dwFlags == 512)
			MouseMove(nX, nY);

		if (dwFlags == 513)
		{
			if (m_cLastFlagLButtonUp == 1)
				m_dwLastMouseDownTime = dwServerTime;

			m_cLastFlagLButtonUp = 0;
		}

		if (g_pObjectManager->m_stMobData.CurrentScore.Hp > 0)
		{
			int SWidth = g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift;
			int SHeight = g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift;

			if (nX > 0 && nY > 0 && nX < SWidth && nY < SHeight)
			{
				if (dwFlags == 517 && wParam & 8)
				{
					if (m_stAutoTrade.TargetID == m_pMyHuman->m_dwID)
						return 1;

					if (m_pMouseOverHuman && m_pMouseOverHuman->m_dwEdgeColor != 0x8800FF00)
						PGTVisible(dwServerTime);

					return 1;
				}

				if (dwFlags == 516 && !(wParam & 8))
				{
					if (wParam & 4)
						return SkillUse(nX, nY, vec, dwServerTime, 0, 0);
					else
						return SkillUse(nX, nY, vec, dwServerTime, 1, 0);
				}

				if (dwFlags == 514)
				{
					m_cLastFlagLButtonUp = 1;
					m_bMoveing = 0;

					if (m_pMyHuman->m_cHide == 1)
						return 1;

					if (m_stAutoTrade.TargetID == m_pMyHuman->m_dwID)
						return 1;

					return MouseClick_NPC(nX, nY, vec, dwServerTime);
				}

				if (dwFlags == 513 && !m_pMyHuman->m_cHide && (!m_bMoveing || wParam & 4))
				{
					int nRet = MobAttack(wParam, vec, dwServerTime);

					if (!nRet)
						nRet = CheckMerchant(m_pMouseOverHuman);

					float fHeight = static_cast<float>(GroundGetMask(TMVector2{ vec.x, vec.z })) * 0.1f;

					TMVector3 vecTar{ vec.x, fHeight + 0.30000001f, vec.z };

					m_pTarget1->m_vecPosition = vecTar;
					m_pTarget2->m_vecPosition = vecTar;
					m_pTargetBill->m_vecPosition = vecTar;

					m_pTargetBill->m_vecPosition.y -= 0.2f;

					if (nRet)
						return nRet;
				}

				if (dwFlags != 513 || wParam & 4 || g_pCursor->m_pAttachedItem || m_pMyHuman->m_cCantMove)
				{
					if (dwFlags == 513 && pPanel->IsVisible() == 1 && g_pCursor->m_pAttachedItem)
					{
						if (g_pCursor->m_pAttachedItem->m_pItem->sIndex >= 5000 && g_pCursor->m_pAttachedItem->m_pItem->sIndex < 5096)
							return 1;

						DropItem(dwServerTime);
						return 1;
					}
				}
				else if (m_pMyHuman->m_eMotion != ECHAR_MOTION::ECMOTION_SEATING && m_pMyHuman->m_eMotion != ECHAR_MOTION::ECMOTION_PUNISHING)
				{
					if (static_cast<float>(nX) >= (m_pChatBack->GetPos().x + 10.0f) &&
						abs(static_cast<int>(vec.x - m_pMyHuman->m_vecPosition.x)) < 15 &&
						abs(static_cast<int>(vec.y - m_pMyHuman->m_vecPosition.y)) > 15)
					{
						m_bMoveing = 1;

						float fHeight = static_cast<float>(GroundGetMask(TMVector2{ vec.x, vec.z })) * 0.1f;

						TMVector3 vecTar{ vec.x, fHeight + 0.30000001f, vec.z };

						m_pTarget1->m_vecPosition = vecTar;
						m_pTarget2->m_vecPosition = vecTar;
						m_pTargetBill->m_vecPosition = vecTar;

						m_pTargetBill->m_vecPosition.y -= 0.2f;
						
						MobMove(vec, dwServerTime);
					}
				}
				else
				{
					if (m_pMyHuman->m_SendeMotion != ECHAR_MOTION::ECMOTION_NONE)
						return 1;

					MSG_Motion stMotion{};

					stMotion.Header.ID = g_pObjectManager->m_dwCharID;
					stMotion.Header.Type = MSG_Motion_Opcode;

					if (m_pMyHuman->m_eMotion == ECHAR_MOTION::ECMOTION_SEATING)
						stMotion.Motion = 25;
					else
						stMotion.Motion = 27;

					stMotion.Direction = 0.0f;

					m_pMyHuman->m_SendeMotion = static_cast<ECHAR_MOTION>(stMotion.Motion);

					SendOneMessage((char*)&stMotion, sizeof(stMotion));

					m_dwKeyTime = dwServerTime;
				}
			}
		}
		return 0;
	}

	for (int i = 0; i < 20; ++i)
	{
		char cSkillIndex = g_pObjectManager->m_cShortSkill[i];

		if (cSkillIndex == 99)
		{
			g_pObjectManager->m_cSelectShortSkill = cSkillIndex;
			
			UpdateSkillBelt();

			m_pMessageBox->SetMessage(g_pMessageStringTable[227], 99u, 0);
			m_pMessageBox->SetVisible(1);
			return 1;
		}
	}

	return 1;
}

int TMFieldScene::OnPacketEvent(unsigned int dwCode, char* buf)
{
	return 0;
}

int TMFieldScene::FrameMove(unsigned int dwServerTime)
{
	TMScene::FrameMove(dwServerTime);
	return 1;
}

int TMFieldScene::OnAccel(int nMsg)
{
	return 0;
}

void TMFieldScene::PGTVisible(unsigned int dwServerTime)
{
}

void TMFieldScene::MouseMove(int nX, int nY)
{
	if (m_pMouseOverHuman && 
		m_pMouseOverHuman->m_pSkinMesh &&
		nX > 0 &&
		nY > 0 &&
		nX < static_cast<int>(g_pDevice->m_dwScreenWidth - g_pDevice->m_nWidthShift) &&
		nY < static_cast<int>(g_pDevice->m_dwScreenHeight - g_pDevice->m_nHeightShift))
	{
		if (m_pMouseOverHuman->m_pSkinMesh->m_materials.Emissive.r >= 0.99900001f &&
			m_pMouseOverHuman->m_pSkinMesh->m_materials.Emissive.g <= 0.001f &&
			m_pMouseOverHuman->m_pSkinMesh->m_materials.Emissive.b <= 0.001f)
		{
			g_pCursor->m_GCPanel.nTextureIndex = 1;
		}
		else if (g_pCursor->m_GCPanel.nTextureIndex == 1)
		{
			g_pCursor->m_GCPanel.nTextureIndex = 0;
		}
	}
	else if (g_pCursor->m_GCPanel.nTextureIndex == 1)
	{
		g_pCursor->m_GCPanel.nTextureIndex = 0;
	}
}

int TMFieldScene::SkillUse(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime, int bMoving, TMHuman* pTarget)
{
	return 0;
}

int TMFieldScene::AutoSkillUse(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime, int bMoving, TMHuman* pTarget)
{
	return 0;
}

int TMFieldScene::MouseClick_NPC(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::CheckMerchant(TMHuman* pOver)
{
	return 0;
}

int TMFieldScene::MouseLButtonDown(int nX, int nY, D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::MobAttack(unsigned int wParam, D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::MobMove(D3DXVECTOR3 vec, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::MobMove2(TMVector2 vec, unsigned int dwServerTime)
{
	return 0;
}

void TMFieldScene::DropItem(unsigned int dwServerTime)
{
}

int TMFieldScene::TimeDelay(unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::GetItem(TMItem* pItem)
{
	return 0;
}

void TMFieldScene::FrameMove_KhepraDieEffect(unsigned int dwServerTime)
{
}

void TMFieldScene::SetVisibleInventory()
{
	SGridControl::m_sLastMouseOverIndex = -1;

	auto pCargoPanel = m_pCargoPanel;
	auto pPanel = m_pInvenPanel;
	auto pCPanel = m_pCPanel;
	auto pSkillPanel = m_pSkillPanel;
	auto pSkillMPanel = m_pSkillMPanel;
	auto pTradePanel = m_pTradePanel;
	auto pATradePanel = m_pAutoTrade;
	auto pItemMixPanel = m_pItemMixPanel;
	auto pItemMixPanel4 = m_pItemMixPanel4;
	auto pHellgateStore = m_pHellgateStore;
	auto pGambleStore = m_pGambleStore;

	if (m_pGambleStore->IsVisible() == 1)
		pPanel->m_bVisible = 0;

	if (pGambleStore->IsVisible() == 1)
		pCPanel->m_bVisible = 0;

	int bInv = pPanel->m_bVisible == 0;

	if (pATradePanel && pATradePanel->IsVisible() == 1)
		SetVisibleAutoTrade(0, 0);

	if (pGambleStore && pGambleStore->IsVisible() == 1)
		SetVisibleGamble(0, 0);

	pPanel->SetVisible(bInv == 0);

	if (!bInv)
	{
		ClearCombine();
		ClearCombine4();
		ClearMixPannel();

		m_ItemMixClass.m_pMixPanel->SetVisible(0);

		if (m_ItemMixClass.m_pMixPanel)
			m_ItemMixClass.m_pMixPanel->SetVisible(0);

		ClearMissionPannel();

		m_MissionClass.m_pMissionPanel->SetVisible(0);

		if (m_MissionClass.m_pMissionPanel)
			m_MissionClass.m_pMissionPanel->SetVisible(0);

		SetVisibleShop(0);

		pCargoPanel->SetVisible(0);
		pItemMixPanel->SetVisible(0);
		pItemMixPanel4->SetVisible(0);
		pHellgateStore->SetVisible(0);

		SetGridState();

		m_pInputGoldPanel->SetVisible(0);

		if (pTradePanel->IsVisible() == 1)
			SetVisibleTrade(0);

		g_pCursor->DetachItem();
	}

	pPanel->SetVisible(bInv);

	if (g_pSoundManager)
	{
		auto pSoundData = g_pSoundManager->GetSoundData(51);

		if (pSoundData)
			pSoundData->Play(0, 0);
	}
}

void TMFieldScene::SetVisibleCharInfo()
{
}

void TMFieldScene::SetVisibleShop(int bShow)
{
}

void TMFieldScene::SetVisibleCargo(int bShow)
{
}

void TMFieldScene::SetVisibleCargo1(int bShow)
{
}

void TMFieldScene::SetVisibleTrade(int bShow)
{
}

void TMFieldScene::ClearCombine()
{
}

void TMFieldScene::ClearCombine4()
{
}

void TMFieldScene::DoCombine()
{
}

void TMFieldScene::DoCombine4()
{
}

void TMFieldScene::SetVisibleMixItem(int bShow)
{
}

void TMFieldScene::SetVisibleMixItemTiini(int bShow)
{
}

void TMFieldScene::SetVisibleHellGateStore(int bShow)
{
}

void TMFieldScene::SetVisibleGamble(int bShow, char cType)
{
}

void TMFieldScene::SetVisiblePotal(int bShow, int nPos)
{
}

void TMFieldScene::SetVisibleMiniMap()
{
}

void TMFieldScene::SetVisibleParty()
{
}

void TMFieldScene::SetVisibleSkillMaster()
{
}

void TMFieldScene::SetVisibleSkill()
{
}

void TMFieldScene::SetVisibleServerWar()
{
}

void TMFieldScene::SetVisibleRefuseServerWar()
{
}

void TMFieldScene::SetInVisibleInputCoin()
{
}

void TMFieldScene::SetGridState()
{
}

void TMFieldScene::SetEquipGridState(int bDefault)
{
}

void TMFieldScene::UpdateScoreUI(unsigned int unFlag)
{
}

void TMFieldScene::UpdateSkillBelt()
{
}

void TMFieldScene::UpdateMyHuman()
{
	STRUCT_MOB* pMobData = &g_pObjectManager->m_stMobData;
	
	SANC_INFO stSancInfo{};
	memcpy(&stSancInfo, &m_pMyHuman->m_stOldSancInfo, sizeof(stSancInfo));

	m_pMyHuman->SetPacketMOBItem(&g_pObjectManager->m_stMobData);

	if ((unsigned char)stSancInfo.Sanc0 > 0 && pMobData->Equip[0].sIndex != 32)
		memcpy(&m_pMyHuman->m_stSancInfo, &stSancInfo, sizeof(stSancInfo));

	float fCon = (float)m_pMyHuman->m_stScore.Con;
	m_pMyHuman->SetCharHeight(fCon);
	m_pMyHuman->SetRace(pMobData->Equip[0].sIndex);

	int nWeaponTypeL = BASE_GetItemAbility(&pMobData->Equip[6], 21);
	if (nWeaponTypeL == 41)
	{
		m_pMyHuman->m_stLookInfo.RightMesh = m_pMyHuman->m_stLookInfo.LeftMesh;
		m_pMyHuman->m_stLookInfo.RightSkin = m_pMyHuman->m_stLookInfo.LeftSkin;
		m_pMyHuman->m_stSancInfo.Sanc6 = m_pMyHuman->m_stSancInfo.Sanc7;
		m_pMyHuman->m_stSancInfo.Legend6 = m_pMyHuman->m_stSancInfo.Legend7;
	}

	m_pMyHuman->InitObject();
	m_pMyHuman->CheckWeapon(pMobData->Equip[6].sIndex, pMobData->Equip[7].sIndex);
	m_pMyHuman->InitAngle(0.0f, m_pMyHuman->m_fAngle, 0.0f);

	m_pMyHuman->CheckAffect();
	SetSanc();
}

void TMFieldScene::SetMyHumanExp(long long unExp, int nFakeExp)
{
}

void TMFieldScene::IncSkillSel()
{
}

void TMFieldScene::SetShortSkill(int nIndex, SGridControlItem* pGridItem)
{
}

void TMFieldScene::SetSkillColor(TMHuman* pAttacker, char cSkillIndex)
{
}

void TMFieldScene::OnESC()
{
}

void TMFieldScene::FindAuto()
{
}

int TMFieldScene::FindProcess(unsigned int processID)
{
	return 0;
}

void TMFieldScene::SetAutoOption(int nIndex, char* szString)
{
}

void TMFieldScene::SetAutoSkillNum(int nCount)
{
}

void TMFieldScene::SetCameraView()
{
}

void TMFieldScene::InitCameraView()
{
}

void TMFieldScene::SetPK()
{
}

void TMFieldScene::SetVisibleNameLabel()
{
}

void TMFieldScene::SetAutoTarget()
{
}

void TMFieldScene::SetVisibleAutoTrade(int bShow, int bCargo)
{
}

void TMFieldScene::SetWhisper(char cOn)
{
}

void TMFieldScene::SetPartyChat(char cOn)
{
}

void TMFieldScene::SetGuildChat(char cOn)
{
}

void TMFieldScene::SetKingDomChat(char cOn)
{
}

void TMFieldScene::SendReqBuy(unsigned int dwControlID)
{
}

void TMFieldScene::SetSanc()
{
}

void TMFieldScene::CreateGate(int nZoneIndex, int bInit)
{
}

int TMFieldScene::GetItemFromGround(unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::GetWeaponDamage()
{
	return 0;
}

void TMFieldScene::SetMyHumanMagic()
{
}

void TMFieldScene::SetWeather(int nWeather)
{
}

void TMFieldScene::SetVisibleKhepraPortal(bool bVisible)
{
}

void TMFieldScene::InitBoard()
{
	if (m_pGMsgPanel)
	{
		SListBoxBoardItem* pBoardItem = new SListBoxBoardItem((char*)"0",
			g_pMessageStringTable[176],
			g_pMessageStringTable[177],
			g_pMessageStringTable[178],
			g_pMessageStringTable[179],
			g_pMessageStringTable[180],
			0x5588FFFFu,
			1);

		pBoardItem->SetControlID(824);
		pBoardItem->SetPos(4.0f, 28.0f);
		m_pGMsgListPanel->AddChild(pBoardItem);

		m_pButtonBox = new SButtonBox(4.0f, 320.0f, 500.0f, 16.0f, 1, 10, 1, 1, 10, 1, 10);
		m_pButtonBox->SetControlID(826);
		m_pButtonBox->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);

		m_pGMsgListPanel->AddChild(m_pButtonBox);
		m_pGMsgPanel->SetVisible(0);
	}

	m_pHelpPanel = (SPanel*)m_pControlContainer->FindControl(864);
	if (m_pHelpPanel)
	{
		m_pHelpText = (SText*)m_pControlContainer->FindControl(865);
		m_pHelpButton[0] = (SButton*)m_pControlContainer->FindControl(867);
		m_pHelpList[0] = (SListBox*)m_pControlContainer->FindControl(868);
		m_pHelpButton[1] = (SButton*)m_pControlContainer->FindControl(869);
		m_pHelpList[1] = (SListBox*)m_pControlContainer->FindControl(870);
		m_pHelpButton[2] = (SButton*)m_pControlContainer->FindControl(871);
		m_pHelpList[2] = (SListBox*)m_pControlContainer->FindControl(872);
		m_pHelpButton[3] = (SButton*)m_pControlContainer->FindControl(873);
		m_pHelpList[3] = (SListBox*)m_pControlContainer->FindControl(874);
		m_pHelpMemo = (SButton*)m_pControlContainer->FindControl(875);
		m_pHelpSummon = (SButton*)m_pControlContainer->FindControl(878);

		m_pHelpSummon->m_cAlwaysAlt = 1;
		m_pHelpSummon->m_cBlink = 1;

		m_pHelpSummon->m_pAltText->SetPos(-26.0f * RenderDevice::m_fWidthRatio,
			-17.0f * RenderDevice::m_fHeightRatio);
		m_pHelpMemo->m_pAltText->SetPos(-26.0f * RenderDevice::m_fWidthRatio,
			-17.0f * RenderDevice::m_fHeightRatio);

		m_pHelpSummon->m_cAlwaysAlt = 0;
		m_pHelpMemo->m_nPosX = (float)(665.0f * RenderDevice::m_fWidthRatio)
			+ m_pMainInfo1->m_nPosX;
		m_pHelpMemo->m_nPosY = m_pMainInfo1->m_nPosY
			- (float)(105.0f * RenderDevice::m_fHeightRatio);
		m_pHelpMemo->m_cBlink = 1;
		m_pHelpSummon->m_nPosX = (float)(616.0f * RenderDevice::m_fWidthRatio)
			+ m_pMainInfo1->m_nPosX;
		m_pHelpSummon->m_nPosY = m_pMainInfo1->m_nPosY
			- (float)(90.0f * RenderDevice::m_fHeightRatio);

		LoadMsgText(m_pHelpList[0], (char*)"UI\\interface.txt");
		LoadMsgText(m_pHelpList[1], (char*)"UI\\command.txt");
		LoadMsgText(m_pHelpList[2], (char*)"UI\\etc.txt");

		if (m_pHelpList[1])
			m_pHelpList[1]->SetVisible(0);
		if (m_pHelpList[2])
			m_pHelpList[2]->SetVisible(0);
		if (m_pHelpList[3])
			m_pHelpList[3]->SetVisible(0);
		if (m_pHelpMemo)
			m_pHelpMemo->SetVisible(0);
		if (m_pHelpSummon)
			m_pHelpSummon->SetVisible(0);

		m_pHelpPanel->SetVisible(0);
		m_pHelpPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pHelpPanel->m_nWidth * 0.5f),
			((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pHelpPanel->m_nHeight * 0.6f));

		m_pHelpInterface = (SPanel*)m_pControlContainer->FindControl(6067);
		for (int i = 0; i < 3; ++i)
		{
			m_pHelpInterfacePanel[i] = (SPanel*)m_pControlContainer->FindControl(i + 6064);
			m_pHelpInterfaceList[i] = (SListBox*)m_pControlContainer->FindControl(i + 6074);
			if (i > 0)
				m_pHelpInterfacePanel[i]->SetVisible(0);
		}
		LoadMsgText(m_pHelpInterfaceList[0], (char*)"UI\\interface1.txt");
		LoadMsgText(m_pHelpInterfaceList[1], (char*)"UI\\interface2.txt");
		LoadMsgText(m_pHelpInterfaceList[2], (char*)"UI\\interface3.txt");
		m_nCurrInterfacePanelIndex = 0;
	}	

	m_pQuestPanel = (SPanel*)m_pControlContainer->FindControl(1054256);
	if (m_pQuestPanel)
	{
		m_pQuestButton[0] = (SButton*)m_pControlContainer->FindControl(1054259);
		m_pQuestList[0] = (SListBox*)m_pControlContainer->FindControl(1054260);
		m_pQuestContentList[0] = (SListBox*)m_pControlContainer->FindControl(1054261);
		m_pQuestButton[1] = (SButton*)m_pControlContainer->FindControl(1054262);
		m_pQuestList[1] = (SListBox*)m_pControlContainer->FindControl(1054263);
		m_pQuestContentList[1] = (SListBox*)m_pControlContainer->FindControl(1054264);
		m_pQuestButton[2] = (SButton*)m_pControlContainer->FindControl(1054265);
		m_pQuestList[2] = (SListBox*)m_pControlContainer->FindControl(1054266);
		m_pQuestContentList[2] = (SListBox*)m_pControlContainer->FindControl(1054267);
		m_pQuestButton[3] = (SButton*)m_pControlContainer->FindControl(1054268);
		m_pQuestList[3] = (SListBox*)m_pControlContainer->FindControl(1054269);
		m_pQuestContentList[3] = (SListBox*)m_pControlContainer->FindControl(1054271);

		if (m_pQuestList[0])
			m_pQuestList[0]->SetVisible(0);
		if (m_pQuestList[1])
			m_pQuestList[1]->SetVisible(0);
		if (m_pQuestList[2])
			m_pQuestList[2]->SetVisible(0);
		if (m_pQuestList[3])
			m_pQuestList[3]->SetVisible(0);

		if (m_pQuestContentList[0])
			m_pQuestContentList[0]->SetVisible(0);
		if (m_pQuestContentList[1])
			m_pQuestContentList[1]->SetVisible(0);
		if (m_pQuestContentList[2])
			m_pQuestContentList[2]->SetVisible(0);
		if (m_pQuestContentList[3])
			m_pQuestContentList[3]->SetVisible(0);

		m_pQuestPanel->SetVisible(0);

		m_pQuestList[0]->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);
		m_pQuestList[1]->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);
		m_pQuestList[2]->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);
		m_pQuestList[3]->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);

		m_pQuestPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pQuestPanel->m_nWidth * 0.5f),
			((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pQuestPanel->m_nHeight * 0.6f));

		memset(m_pLevelQuest, 0, sizeof(m_pLevelQuest));

		LoadMsgLevel(m_pLevelQuest, (char*)"UI\\QuestSubjects.txt", 97);
		LoadMsgLevel(m_pLevelQuest, (char*)"UI\\QuestSubjects2.txt", 98);
		LoadMsgLevel(m_pLevelQuest, (char*)"UI\\QuestSubjects3.txt", 99);
		LoadMsgLevel(m_pLevelQuest, (char*)"UI\\QuestSubjects4.txt", 101);
		LoadMsgLevel(m_pLevelQuest, (char*)"UI\\QuestMessage.txt", 100);

		m_pQuestMemo = (SButton*)m_pControlContainer->FindControl(1054273);
		m_pQuestMemo->m_cAlwaysAlt = 1;
		m_pQuestMemo->m_cBlink = 1;

		m_pQuestMemo->m_pAltText->SetPos(-20.0f, -10.0f);

		m_pQuestMemo->m_nPosX = (float)(700.0f * RenderDevice::m_fWidthRatio)
			+ m_pMainInfo1->m_nPosX;
		m_pQuestMemo->m_nPosY = m_pMainInfo1->m_nPosY
			- (float)(105.0f * RenderDevice::m_fHeightRatio);

		if (!g_pObjectManager->m_stMobData.CurrentScore.Level)
		{
			STRUCT_MOB* pMobData = &g_pObjectManager->m_stMobData;
			TMScene::LoadMsgText3(m_pQuestList[0], 
				(char*)"UI\\QuestSubjects.txt",	
				g_pObjectManager->m_stMobData.CurrentScore.Level + 1, 
				g_pObjectManager->m_stMobData.Equip[0].sIndex % 10);
			TMScene::LoadMsgText3(m_pQuestList[1],
				(char*)"UI\\QuestSubjects2.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);
			TMScene::LoadMsgText3(m_pQuestList[2],
				(char*)"UI\\QuestSubjects3.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);
			TMScene::LoadMsgText3(m_pQuestList[3],
				(char*)"UI\\QuestSubjects4.txt",
				pMobData->CurrentScore.Level + 1,
				pMobData->Equip[0].sIndex % 10);

			m_pQuestMemo->SetVisible(1);

			char szStr[128]{};
			unsigned int dwCol = 0xFFAAAAFF;
			if (m_pLevelQuest[pMobData->CurrentScore.Level] == 100)
				dwCol = TMScene::LoadMsgText4(					
					szStr,
					(char*)"UI\\QuestMessage.txt",
					pMobData->CurrentScore.Level + 1,
					pMobData->Equip[0].sIndex % 10);
			else
				sprintf(szStr, g_pMessageStringTable[307]);

			SListBoxItem* pChatItem = new SListBoxItem(szStr, dwCol, 0.0f, 0.0f, 300.0f, 16.0f, 0, 0x77777777, 1, 0);

			if (pChatItem && m_pChatList)
				m_pChatList->AddItem(pChatItem);
		}
		else if (m_pQuestMemo)
		{
			m_pQuestMemo->SetVisible(0);
		}
	}

	m_pPotalPanel = (SPanel*)m_pControlContainer->FindControl(12544);
	m_pPotalList = (SListBox*)m_pControlContainer->FindControl(12545);
	m_pPotalText = (SText*)m_pControlContainer->FindControl(12549);
	m_pPotalText1 = (SText*)m_pControlContainer->FindControl(12550);
	m_pPotalText2 = (SText*)m_pControlContainer->FindControl(12551);
	m_pPotalText3 = (SText*)m_pControlContainer->FindControl(12552);

	m_pPotalPanel->SetPos(((float)g_pDevice->m_dwScreenWidth * 0.5f) - (m_pQuestPanel->m_nWidth * 0.5f),
		((float)g_pDevice->m_dwScreenHeight * 0.5f) - (m_pQuestPanel->m_nHeight * 0.6f));

	if (m_pPotalList)
	{
		m_pPotalList->SetEventListener(m_pControlContainer ? m_pControlContainer : nullptr);
	}

	if (m_pPotalPanel)
		m_pPotalPanel->SetVisible(0);

	for (int j = 0; j < 4; ++j)
	{
		m_pQuestList[j]->SetSize(200.0f, m_pQuestList[j]->m_nHeight);
		m_pQuestContentList[j]->SetSize(300.0f, m_pQuestContentList[j]->m_nHeight);
	}
}

int TMFieldScene::LoadMsgText(SListBox* pListBox, char* szFileName)
{
	return 0;
}

void TMFieldScene::SetPosPKRun()
{
}

char TMFieldScene::UseHPotion()
{
	return 0;
}

char TMFieldScene::UseMPotion()
{
	return 0;
}

void TMFieldScene::UsePPotion()
{
}

int TMFieldScene::IsFeedPotion(short sMountIndex, short sItemIndex)
{
	return 0;
}

char TMFieldScene::FeedMount()
{
	return 0;
}

void TMFieldScene::SetRunMode()
{
}

void TMFieldScene::UseTicket(int nCellX, int nCellY)
{
}

char TMFieldScene::UseQuickSloat(char key)
{
	return 0;
}

void TMFieldScene::UpdateFireWorkButton(int nIndex)
{
}

void TMFieldScene::ClearFireWork()
{
}

void TMFieldScene::UseFireWork()
{
}

void TMFieldScene::DrawCustomFireWork(int nIndex)
{
}

void TMFieldScene::TotoSelect()
{
}

void TMFieldScene::TotoBuy()
{
}

void TMFieldScene::TotoClose()
{
}

void TMFieldScene::MobStop(D3DXVECTOR3 vec)
{
}

void TMFieldScene::VisibleInputTradeName()
{
}

void TMFieldScene::VisibleInputPass()
{
}

void TMFieldScene::VisibleInputGuildName()
{
}

void TMFieldScene::VisibleInputCharName(SGridControlItem* pItem, int nCellX, int nCellY)
{
}

void TMFieldScene::UseItem(SGridControlItem* pItem, int nType, int nItemSIndex, int nCellX, int nCellY)
{
}

void TMFieldScene::SendCapsuleItem()
{
}

void TMFieldScene::SetQuestStatus(bool bStart)
{
}

void TMFieldScene::UpdateQuestTime()
{
}

void TMFieldScene::SetButtonTextXY(SButton* pButton)
{
}

int TMFieldScene::OnMsgBoxEvent(unsigned int idwControlID, unsigned int idwEvent, unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::OnKeyDebug(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeySkill(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyDash(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyPlus(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyPK(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyName(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyAutoTarget(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyAuto(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyHelp(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyRun(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyFeedMount(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyHPotion(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyMPotion(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyPPotion(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeySkillPage(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyQuestLog(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyReverse(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyAutoRun(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyGuildOnOff(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyShortSkill(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleSkill(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyCamView(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleInven(char iCharCode, int lParam)
{
	if (iCharCode != 'i' && iCharCode != 'I' && iCharCode != 'g' && iCharCode != 'G')
		return 0;

	if (m_pAutoTrade->IsVisible())
		return 1;

	SetVisibleInventory();

	auto pPanel = m_pInvenPanel;
	auto pBtnEquip = static_cast<SButton*>(m_pControlContainer->FindControl(65791u));

	if (pBtnEquip)
		pBtnEquip->SetSelected(pPanel->m_bVisible);

	return 1;
}

int TMFieldScene::OnKeyVisibleCharInfo(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleMinimap(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyVisibleParty(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyReturn(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyNumPad(unsigned int iKeyCode)
{
	return 0;
}

int TMFieldScene::OnKeyTotoTab(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnKeyTotoEnter(char iCharCode, int lParam)
{
	return 0;
}

int TMFieldScene::OnPacketMessageChat(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketMessageChat_Index(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketMessageChat_Param(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketMessageWhisper(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketLongMessagePanel(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketReqSummon(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCancelSummon(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAction(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSoundEffect(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCreateMob(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFCharacterLogout(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFRemoveServer(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFAccountLogin(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFCharacterLogin(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketItemSold(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketUpdateCargoCoin(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketWeather(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCreateItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFDropItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFGetItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketUpdateItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRemoveItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAutoTrade(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSwapItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketShopList(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRMBShopList(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketBuy(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSell(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCNFMobKill(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketREQParty(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAddParty(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRemoveParty(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSetHpMode(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketDeposit(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketWithdraw(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketReqChallange(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCloseShop(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketSetShortSkill(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketClearMenu(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCombineComplete(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCastleState(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketStartTime(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRemainCount(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketWarInfo(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketGuildDisable(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketEnvEffect(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRemainNPCCount(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRESULTGAMBLE(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketREQArray(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAttack(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketNuke(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRandomQuiz(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketAutoKick(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketItemPrice(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketCapsuleInfo(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRunQuest12Start(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketRunQuest12Count(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketDelayQuit(MSG_STANDARDPARM* pStd)
{
	return 0;
}

int TMFieldScene::OnPacketUndoSellItem(MSG_STANDARD* pStd)
{
	return 0;
}

int TMFieldScene::Guildmark_Create(stGuildMarkInfo* pMark)
{
	return 0;
}

void TMFieldScene::Guildmark_MakeFileName(char* szStr, int nGuild, int nChief, int nChannel)
{
}

int TMFieldScene::Guildmark_Find_ArrayIndex(int nGuild)
{
	return 0;
}

int TMFieldScene::Guildmark_Find_EmptyArrayIndex()
{
	return 0;
}

int TMFieldScene::Guildmark_DeleteIdleGuildmark()
{
	return 0;
}

int TMFieldScene::Guildmark_IsCorrectBMP(char* szMarkBuffer)
{
	return 0;
}

void TMFieldScene::Guildmark_Link(SPanel* pPanel, int nMarkIndex, int nGuildIndex)
{
}

void TMFieldScene::SysMsgChat(char* str)
{
}

void TMFieldScene::GetTimeString(char* szVal, int sTime, int nTime, int i)
{
}

void TMFieldScene::Bag_View()
{
}

void TMFieldScene::AirMove_Main(unsigned int dwServerTime)
{
}

void TMFieldScene::AirMove_Start(int nIndex)
{
}

void TMFieldScene::AirMove_End()
{
}

int TMFieldScene::AirMove_ShowUI(bool bShow)
{
	return 0;
}

int TMFieldScene::Affect_Main(unsigned int dwServerTime)
{
	return 0;
}

int TMFieldScene::StrByteCheck(char* szString)
{
	return 0;
}

void TMFieldScene::SetVisibleMixPanel(int bShow)
{
}

void TMFieldScene::ClearMixPannel()
{
}

void TMFieldScene::SetVisibleMissionPanel(int bShow)
{
}

void TMFieldScene::ClearMissionPannel()
{
}

void TMFieldScene::GameAuto()
{
}

int TMFieldScene::MouseClick_MixNPC(TMHuman* pOver)
{
	return 0;
}

void TMFieldScene::MouseClick_PremiumNPC(TMHuman* pOver)
{
}

int TMFieldScene::MouseClick_SkillMasterNPC(unsigned int dwServerTime, TMHuman* pOver)
{
	return 0;
}

int TMFieldScene::MouseClick_QuestNPC(unsigned int dwServerTime, TMHuman* pOver)
{
	return 0;
}

void TMFieldScene::NewCCMode()
{
}
